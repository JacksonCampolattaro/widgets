#ifndef WIDGETS_TEMPLATEWIDGET_H
#define WIDGETS_TEMPLATEWIDGET_H

#include <gtkmm/builder.h>

#include <cassert>
#include <iostream>

// todo: this doesn't work
//extern "C" void _gtk_builder_parser_parse_buffer(
//        GtkBuilder *builder,
//        const char *filename,
//        const char *buffer,
//        gssize length,
//        const char **requested_objs,
//        GError **error
//);

template<typename BaseWidget>
class TemplateWidget : public BaseWidget {
public:

    explicit TemplateWidget(const Glib::ustring &resource) :
            BaseWidget(),
            _builder(Gtk::Builder::create()) {
        setup(resource);
    }

    explicit TemplateWidget(BaseWidget::BaseObjectType *cobject,
                            const Glib::RefPtr<Gtk::Builder> &builder,
                            const Glib::ustring &resource) :
            BaseWidget(cobject),
            // todo: should I use the same builder here? It seems to cause problems.
            _builder(Gtk::Builder::create()) {
        setup(resource);
    }

    template<class W, typename... Args>
    W &get_widget(const Glib::ustring &name, Args &&... args) {

        // Determine if the widget is a user-created type, based on its constructor
        constexpr bool isDerived = requires(
                typename W::BaseObjectType *baseObject,
                const Glib::RefPtr<Gtk::Builder> &b,
                Args &&... a
        ) {
            W(baseObject, b, std::forward<Args>(a)...);
        };

        // Invoke the appropriate builder function, depending on whether the widget is a built-in
        W *widget;
        if constexpr (isDerived)
            widget = Gtk::Builder::get_widget_derived<W>(_builder, name, std::forward<Args>(args)...);
        else
            widget = _builder->get_widget<W>(name);

        // todo: in the future, it might be better to throw an error
        assert(widget);
        return *widget;
    };

private:

    Glib::RefPtr<Gtk::Builder> _builder;

    void setup(const Glib::ustring &resource) {
        assert(_builder);
        //std::cout << G_OBJECT_TYPE_NAME(this->gobj()) << std::endl;

        // Load the resource file
        GError *error = nullptr;
        auto bytes = g_resources_lookup_data(resource.c_str(), G_RESOURCE_LOOKUP_FLAGS_NONE, &error);
        if (!bytes) {
            g_warning (
                    "Failed to load resources from path id %s: %s",
                    resource.c_str(),
                    error->message
            );
            g_error_free(error);
            return;
        }

        // Construct the widgets in the file using the builder
        bool success = gtk_builder_extend_with_template(
                GTK_BUILDER(_builder->gobj()),
                G_OBJECT(this->gobj()),
                G_TYPE_FROM_INSTANCE(this->gobj()),
                (const char *) g_bytes_get_data(bytes, 0),
                g_bytes_get_size(bytes),
                &error
        );
        if (!success) {
            g_warning (
                    "Failed to construct composite widget from template: %s",
                    error->message
            );
            g_error_free(error);
            return;
        }

        // todo: if I can invoke the parsing method by hand instead, I can fix the prefix issue!

        //        auto name = g_type_name(G_TYPE_FROM_INSTANCE(this->gobj()));
        //        gtk_builder_expose_object(GTK_BUILDER(_builder->gobj()), name, G_OBJECT(this->gobj()));
        //        auto filename = g_strconcat("<", name, " template>", NULL);
        //        _gtk_builder_parser_parse_buffer(
        //                GTK_BUILDER(_builder->gobj()),
        //                filename,
        //                (const char *) g_bytes_get_data(bytes, 0),
        //                g_bytes_get_size(bytes),
        //                nullptr,
        //                &error
        //        );
        //        g_free(filename);
    }

};

#endif //WIDGETS_TEMPLATEWIDGET_H
