#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>

#include <adwaita.h>

#include "TemplateWidget.h"
#include "VectorView.h"
#include "VectorEntry.h"
#include "CompactVectorEntry.h"

class DemoWindow : public TemplateWidget<Gtk::ApplicationWindow> {

    VectorView &_vectorView;
    VectorEntry &_vectorEntry;
    CompactVectorEntry &_compactVectorEntry;

public:

    DemoWindow() : Glib::ObjectBase("DemoWindow"),
                   TemplateWidget("/campolattaro/jackson/widgets/demo.ui"),
                   _vectorView(get_widget<VectorView>("vector-view")),
                   _vectorEntry(get_widget<VectorEntry>("vector-entry")),
                   _compactVectorEntry(get_widget<CompactVectorEntry>("compact-vector-entry")) {}

};


class DemoApplication : public Gtk::Application {
protected:

    DemoApplication() : Gtk::Application("campolattaro.jackson.widgets.demo") {}

public:

    static Glib::RefPtr<DemoApplication> create() {
        return Glib::make_refptr_for_instance<DemoApplication>(new DemoApplication());
    }

protected:

    // Override default signal handlers:
    void on_activate() override {

        static_cast<void>(FloatView());
        static_cast<void>(FloatEntry());
        static_cast<void>(VectorView());
        static_cast<void>(VectorEntry());
        static_cast<void>(CompactVectorEntry());

        adw_style_manager_set_color_scheme(adw_style_manager_get_default(), ADW_COLOR_SCHEME_DEFAULT);

        auto window = Gtk::make_managed<DemoWindow>();
        add_window(*window);
        window->present();
    }

    void on_open(const Gio::Application::type_vec_files &files,
                 const Glib::ustring &hint) override {

    }

private:

    void on_hide_window(Gtk::Window *window);
};

int main() {
    auto app = DemoApplication::create();
    return app->run();
}