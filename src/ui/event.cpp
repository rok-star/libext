#include <libext/ui/event.hpp>

namespace ext::ui {

event::event()
    : _type(ext::ui::event_type::unknown) {}

ext::ui::event_type const& event::type() const {
    return _type;
}

ext::ui::event event::basic_event(ext::ui::event_type const& type) {
    auto event = ext::ui::event();
    event._type = type;
    return event;
}

} /* namespace ext::ui */