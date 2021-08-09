#pragma once

#include <libext/core/array.hpp>
#include <libext/core/string.hpp>

namespace ext::ui {

enum class app_event_type {
    unknown,
    exit
};

class app;

class app_event {
    friend app;
private:
    ext::ui::app_event_type _type;
    app_event();
    static ext::ui::app_event exit_event();
public:
    ext::ui::app_event_type const& type() const;
};

struct app_options {
    ext::string title = "";
};

struct app_process_options {
    double timeout = 0;
};

class app {
private:
    ext::array<ext::ui::app_event> _events;
public:
    app(ext::ui::app const&) = delete;
    app(ext::ui::app &&) = delete;
    ext::ui::app& operator=(ext::ui::app const&) = delete;
    ext::ui::app& operator=(ext::ui::app &&) = delete;
    ~app();
    app(ext::ui::app_options const&);
    ext::array<ext::ui::app_event> const& process(ext::ui::app_process_options const&);
};

} /* namespace ext::ui */