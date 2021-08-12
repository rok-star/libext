#include <cassert>
#include <X11/Xlib.h>
#include <libext/ui/app.hpp>

extern "C" {
    auto __x11_current = (ext::ui::app*)nullptr;
    auto __x11_display = (Display*)nullptr;
    auto __x11_event = XEvent{};
}

namespace ext::ui {

app::~app() {
    XCloseDisplay(__x11_display);
    __x11_current = nullptr;
}

app::app(ext::ui::app_options const& options)
    : _events() {

    assert(__x11_current == nullptr);

    __x11_display = XOpenDisplay(NULL);

    if (__x11_display == NULL) {
        ext::abort("%s\n", "XOpenDisplay() failed");
    }

    __x11_current = this;
}

ext::array<ext::ui::app_event> const& app::poll(ext::ui::app_poll_options const& options) {
    _events.clear();

    for (;;) {
        if (XPending(__x11_display)) {
            XNextEvent(__x11_display, &__x11_event);
            _events.push_new();
        } else {
            break;
        }
    }

    return _events;
}

} /* namespace ext::ui */