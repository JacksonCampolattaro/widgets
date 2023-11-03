#include <gtkmm/builder.h>
#include <gtkmm/application.h>

int main() {
    auto app = Gtk::Application::create("campolattaro.jackson.widgets.demo");
    auto builder = Gtk::Builder::create_from_resource("/campolattaro/jackson/widgets/demo.ui");
    // todo
}