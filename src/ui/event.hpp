#pragma once

namespace ext::ui {

enum class event_type {
    exit
};

class event {
private:
    ext::ui::event_type _type;
public:
    event();
    ext::ui::event_type const& type() const;
    static ext::ui::event basic_event(ext::ui::event_type const&);
};

} /* namespace ext::ui */