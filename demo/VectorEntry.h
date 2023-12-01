#ifndef WIDGETS_VECTORENTRY_H
#define WIDGETS_VECTORENTRY_H

#include "TemplateWidget.h"
#include "FloatEntry.h"

#include <gtkmm/grid.h>

class VectorEntry : public TemplateWidget<Gtk::Box> {
public:

    VectorEntry() :
            Glib::ObjectBase("VectorEntry"),
            TemplateWidget("/campolattaro/jackson/widgets/vectorentry.ui"),
            _x(get_widget<FloatEntry>("x-entry")),
            _y(get_widget<FloatEntry>("y-entry")),
            _z(get_widget<FloatEntry>("z-entry")) {}

    VectorEntry(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder) :
            Glib::ObjectBase("VectorEntry"),
            TemplateWidget(cobject, builder, "/campolattaro/jackson/widgets/vectorentry.ui"),
            _x(get_widget<FloatEntry>("x-entry")),
            _y(get_widget<FloatEntry>("y-entry")),
            _z(get_widget<FloatEntry>("z-entry")) {}

private:

    FloatEntry &_x;
    FloatEntry &_y;
    FloatEntry &_z;
};

#endif //WIDGETS_VECTORENTRY_H
