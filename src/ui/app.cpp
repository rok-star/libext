#include <libext/ui/app.hpp>

namespace ext::ui {

app_event::app_event()
    : _type(ext::ui::app_event_type::unknown) {}

ext::ui::app_event_type const& app_event::type() const {
    return _type;
}

} /* namespace ext::ui */