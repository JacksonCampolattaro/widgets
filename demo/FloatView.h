#ifndef WIDGETS_FLOATVIEW_H
#define WIDGETS_FLOATVIEW_H

#include <gtkmm/label.h>
#include <gtkmm/builder.h>

class FloatView : public Gtk::Label {
public:

    FloatView() :
            Glib::ObjectBase("FloatView"),
            Gtk::Label("float.fff") {
        set_tooltip_text("FFF.fffffff");
    }

    FloatView(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder) :
            Glib::ObjectBase("FloatView"),
            Gtk::Label(cobject) {
        set_tooltip_text("FFF.fffffff");
    }

};

#endif //WIDGETS_FLOATVIEW_H
