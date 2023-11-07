#ifndef WIDGETS_TEMPLATEWIDGET_H
#define WIDGETS_TEMPLATEWIDGET_H

#include <algorithm>
#include <iostream>
#include <cassert>

#include <gtk/gtk.h>

#include <glibmm/extraclassinit.h>
#include <giomm/charsetconverter.h>

#include <gtkmm/builderscope.h>
#include <gtkmm/builder.h>
#include <gtkmm/widget.h>

template<typename Implementation>
class TemplateWidget : public Glib::ExtraClassInit {
public:

    explicit TemplateWidget(const Glib::ustring &resource) :
            Glib::ExtraClassInit(
                    class_init_function,
                    reinterpret_cast<void *>(this),
                    instance_init_function
            ),
            _resource(resource) {}

    template<class W>
    W &get_widget(const Glib::ustring &name) {

        auto self = reinterpret_cast<Implementation *>(this);
        auto type = Implementation::get_base_type();
        //        std::cout << g_type_name(type) << std::endl;
        //        std::cout << name << std::endl;

        //        auto quark_children = g_quark_from_static_string("gtk-widget-auto-children");
        //        std::cout << quark_children << std::endl;
        //        auto children = (GHashTable *) g_object_get_qdata(G_OBJECT(self->gobj()), quark_children);
        //        assert(children);

        auto c_widget = gtk_widget_get_template_child(GTK_WIDGET(self->gobj()), type, name.c_str());
        assert(c_widget);
        auto widget = dynamic_cast<W *>(Glib::wrap(GTK_WIDGET(c_widget), false));
        assert(widget);
        return *widget;
    }

private:

    static void class_init_function(void *g_class, void *class_data) {
        g_return_if_fail(GTK_IS_WIDGET_CLASS(g_class));

        const auto klass = static_cast<GtkWidgetClass *>(g_class);
        const auto self = static_cast<TemplateWidget *>(class_data);
        gtk_widget_class_set_template_from_resource(
                klass,
                self->_resource.c_str()
        );

        //        gtk_widget_class_bind_template_child_private();
        //        gtk_widget_class_bind_template_child(klass, GtkWidget, first_button)
    }

    static void instance_init_function(GTypeInstance *instance, void *class_data) {
        g_return_if_fail(GTK_IS_WIDGET(instance));
        gtk_widget_init_template(GTK_WIDGET(instance));
    }

    Glib::ustring _resource;
};

#endif //WIDGETS_TEMPLATEWIDGET_H
