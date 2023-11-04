#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>

#include "BuilderWidget.h"

//using DemoWindow = BuilderWidget<
//        "/campolattaro/jackson/widgets/demo.ui",
//        Gtk::ApplicationWindow
//>;

class DemoWindow : public TemplateWidget, public Gtk::ApplicationWindow {
public:

    DemoWindow() : Glib::ObjectBase("DemoWindow"),
                   TemplateWidget("/campolattaro/jackson/widgets/demo.ui"),
                   Gtk::ApplicationWindow() {}

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