#pragma once

#include <libext/core/array.hpp>
#include <libext/core/string.hpp>
#include <libext/core/callback.hpp>
#include <libext/core/optional.hpp>
#include <libext/ui/event.hpp>

namespace ext::ui {

struct app_options {
    ext::string title = "";
};

struct app_poll_options {
    double timeout = 0;
};

struct app_process_options {
    double timeout = 0;
};

class app {
public:
    ext::callback<ext::ui::event const&> on_exit;
    app(ext::ui::app const&) = delete;
    app(ext::ui::app &&) = delete;
    ext::ui::app& operator=(ext::ui::app const&) = delete;
    ext::ui::app& operator=(ext::ui::app &&) = delete;
    ~app();
    app(ext::ui::app_options const&);
    ext::optional<ext::ui::event> poll_event(ext::ui::app_poll_options const&);
    void dispatch_event(ext::ui::event const&);
    void process(ext::ui::app_process_options const&);
};

} /* namespace ext::ui */