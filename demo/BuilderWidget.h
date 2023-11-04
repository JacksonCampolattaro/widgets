#ifndef WIDGETS_BUILDERWIDGET_H
#define WIDGETS_BUILDERWIDGET_H

#include <algorithm>
#include <iostream>

#include <gtkmm/widget.h>
#include <gtkmm/builder.h>

#include <glibmm/extraclassinit.h>
#include <gtk/gtk.h>

class TemplateWidget : public Glib::ExtraClassInit {
public:

    TemplateWidget(const Glib::ustring &resource) :
            Glib::ExtraClassInit(
                    class_init_function,
                    reinterpret_cast<void *>(&_resource),
                    instance_init_function
            ),
            _resource(resource) {}

private:

    static void class_init_function(void *g_class, void *class_data) {
        g_return_if_fail(GTK_IS_WIDGET_CLASS(g_class));

        const auto klass = static_cast<GtkWidgetClass *>(g_class);
        const auto resource = static_cast<Glib::ustring *>(class_data);
        gtk_widget_class_set_template_from_resource(
                klass,
                resource->c_str()
        );
    }

    static void instance_init_function(GTypeInstance *instance, void * /* g_class */) {
        g_return_if_fail(GTK_IS_WIDGET(instance));
        gtk_widget_init_template(GTK_WIDGET(instance));
    }

    Glib::ustring _resource;
};

template<std::size_t N>
struct ResourcePath {
    constexpr ResourcePath(const char (&str)[N]) {
        std::copy_n(str, N, value);
    }

    [[nodiscard]] Glib::ustring ustring() const {
        return {value};
    }

    char value[N];
};

template<ResourcePath Path, class W>
class BuilderWidget : public TemplateWidget, public W {
public:

    BuilderWidget() :
            TemplateWidget(Path.ustring()),
            Glib::ObjectBase("BuilderWidget"),
            W() {}

};

#endif //WIDGETS_BUILDERWIDGET_H
