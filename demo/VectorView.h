#ifndef WIDGETS_VECTORVIEW_H
#define WIDGETS_VECTORVIEW_H

#include "TemplateWidget.h"
#include "FloatView.h"

#include <gtkmm/box.h>
#include <gtkmm/label.h>

class VectorView : public TemplateWidget<Gtk::Box> {
public:

    VectorView() :
            Glib::ObjectBase("VectorView"),
            TemplateWidget("/campolattaro/jackson/widgets/vectorview.ui"),
            _x(get_widget<FloatView>("x-view")),
            _y(get_widget<FloatView>("y-view")),
            _z(get_widget<FloatView>("z-view")) {}

    VectorView(Box::BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder) :
            Glib::ObjectBase("VectorView"),
            TemplateWidget(cobject, builder, "/campolattaro/jackson/widgets/vectorview.ui"),
            _x(get_widget<FloatView>("x-view")),
            _y(get_widget<FloatView>("y-view")),
            _z(get_widget<FloatView>("z-view")) {
    }

private:

    FloatView &_x;
    FloatView &_y;
    FloatView &_z;
};

#endif //WIDGETS_VECTORVIEW_H
