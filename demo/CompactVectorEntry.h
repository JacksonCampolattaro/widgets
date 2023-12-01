#ifndef WIDGETS_COMPACTVECTORENTRY_H
#define WIDGETS_COMPACTVECTORENTRY_H

#include "VectorEntry.h"
#include "VectorView.h"

#include <gtkmm/button.h>
#include <gtkmm/popover.h>

class CompactVectorEntry : public Gtk::Button {
public:

    CompactVectorEntry() : Glib::ObjectBase("CompactVectorEntry") {
        setup();
    }

    CompactVectorEntry(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder) :
            Gtk::Button(cobject),
            Glib::ObjectBase("CompactVectorEntry") {
        setup();
    }

private:

    VectorView _preview;
    VectorEntry _entry;
    Gtk::Popover _popover;

    void setup () {

        set_child(_preview);

        _popover.set_child(_entry);
        _popover.set_parent(*this);

        signal_clicked().connect(sigc::mem_fun(_popover, &Gtk::Popover::popup));

    }

};

#endif //WIDGETS_COMPACTVECTORENTRY_H
