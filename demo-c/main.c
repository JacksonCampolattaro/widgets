#include <gtk/gtk.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Demo Window
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

G_DECLARE_FINAL_TYPE(DemoWindow, demo_window, DEMO, WINDOW, GtkApplicationWindow)

struct _DemoWindow {
    GtkApplicationWindow parent;
};

G_DEFINE_TYPE(DemoWindow, demo_window, GTK_TYPE_APPLICATION_WINDOW);

static void demo_window_class_init(DemoWindowClass *class) {
    gtk_widget_class_set_template_from_resource(
            GTK_WIDGET_CLASS (class),
            "/campolattaro/jackson/widgets/demo.ui"
    );
}

static void demo_window_init(DemoWindow *win) {
    gtk_widget_init_template(GTK_WIDGET (win));
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Demo Application
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

G_DECLARE_FINAL_TYPE (DemoApp, demo_app, DEMO, APP, GtkApplication)

struct _DemoApp {
    GtkApplication parent;
};

G_DEFINE_TYPE(DemoApp, demo_app, GTK_TYPE_APPLICATION);

static void demo_app_activate(GApplication *app) {
    DemoWindow *win = g_object_new(demo_window_get_type(), "application", app, NULL);
    gtk_window_present(GTK_WINDOW (win));
}

static void demo_app_class_init(DemoAppClass *class) {
    G_APPLICATION_CLASS (class)->activate = demo_app_activate;
}

static void demo_app_init(DemoApp *app) {}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// main
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, char **argv) {
    GApplication *app = g_object_new(
            demo_app_get_type(),
            "application-id", "demoapp",
            "flags", G_APPLICATION_HANDLES_OPEN,
            NULL
    );

    return g_application_run(G_APPLICATION (app), argc, argv);
}