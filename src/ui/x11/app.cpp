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
    : on_exit() {

    assert(__x11_current == nullptr);

    __x11_display = XOpenDisplay(nullptr);

    if (__x11_display == nullptr) {
        ext::abort("%s\n", "XOpenDisplay() failed");
    }

    __x11_fd = ConnectionNumber(__x11_display);

    __x11_current = this;
}

ext::optional<ext::ui::event> app::poll_event(ext::ui::app_poll_options const& options) {
    auto fds = fd_set{};
    auto tv = (struct timeval){
        .tv_sec = 1,
        .tv_usec = 0
    };
    
    FD_SET(__x11_fd, &fds);

    auto num = select((__x11_fd + 1), &fds, NULL, NULL, &tv);
    if ((num > 0)
    && XPending(__x11_display)) {
        XNextEvent(__x11_display, &__x11_event);
        return ext::ui::event::basic_event(ext::ui::event_type::exit);
    }

    return ext::nullopt;
}

} /* namespace ext::ui */