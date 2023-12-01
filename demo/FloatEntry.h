#ifndef WIDGETS_FLOATENTRY_H
#define WIDGETS_FLOATENTRY_H

#include <gtkmm/spinbutton.h>
#include <gtkmm/builder.h>

class FloatEntry : public Gtk::SpinButton {
public:

    FloatEntry() :
            Glib::ObjectBase("FloatEntry"),
            Gtk::SpinButton() {
    }

    FloatEntry(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder) :
            Glib::ObjectBase("FloatEntry"),
            Gtk::SpinButton(cobject) {
        // todo
        set_width_chars(10);
    }

};


#endif //WIDGETS_FLOATENTRY_H
