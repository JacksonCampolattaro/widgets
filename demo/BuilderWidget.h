#ifndef WIDGETS_BUILDERWIDGET_H
#define WIDGETS_BUILDERWIDGET_H

#include <algorithm>

#include <gtkmm/widget.h>

template<std::size_t N>
struct ResourcePath {
    constexpr ResourcePath(const char (&str)[N]) {
        std::copy_n(str, N, value);
    }

    char value[N];
};

template<ResourcePath Path>
class BuilderWidget : public Gtk::Widget {

};

#endif //WIDGETS_BUILDERWIDGET_H
