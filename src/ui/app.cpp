#include <libext/ui/app.hpp>

namespace ext::ui {

app_event::app_event()
    : _type(ext::ui::app_event_type::unknown) {}

ext::ui::app_event_type const& app_event::type() const {
    return _type;
}

app::~app() {

}

app::app()
    : _events() {}

ext::array<ext::ui::app_event> const& app::process(ext::ui::app_process_options const& options) {
    _events.clear();

    return _events;
}

} /* namespace ext::ui */