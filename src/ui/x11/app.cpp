#include <cassert>
#include <X11/Xlib.h>
#include <libext/ui/app.hpp>

extern "C" {
    auto __x11_current = (ext::ui::app*)nullptr;
    auto __x11_display = (Display*)nullptr;
    auto __x11_event = XEvent{};
    auto __x11_fd = (int)0;
}

namespace ext::ui {

app::~app() {
    XCloseDisplay(__x11_display);
    close(__x11_fd);
    __x11_current = nullptr;
}

app::app(ext::ui::app_options const& options)
    : _events() {

    assert(__x11_current == nullptr);

    __x11_display = XOpenDisplay(nullptr);

    if (__x11_display == nullptr) {
        ext::abort("%s\n", "XOpenDisplay() failed");
    }

    __x11_fd = ConnectionNumber(__x11_display);

    __x11_current = this;
}

ext::array<ext::ui::event> const& app::poll(ext::ui::app_poll_options const& options) {
    _events.clear();

    auto tv = (struct timeval){};
    auto fds = fd_set{};

    FD_SET(__x11_fd, &fds);

    tv.tv_usec = 0;
    tv.tv_sec = 1;

    auto num = select((__x11_fd + 1), &fds, NULL, NULL, &tv);
    if (num > 0) {
        for (;;) {
            if (XPending(__x11_display)) {
                XNextEvent(__x11_display, &__x11_event);
                _events.push_new();
            } else {
                break;
            }
        }
    }

    return _events;
}

} /* namespace ext::ui */