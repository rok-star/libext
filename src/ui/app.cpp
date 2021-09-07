#include <libext/ui/app.hpp>

namespace ext::ui {

void app::dispatch_event(ext::ui::event const& event) {
    if (event.type() == ext::ui::event_type::exit) {
        on_exit.trigger(event);
    }
}

void app::process(ext::ui::app_process_options const& options) {
    for (;;) {
        auto const ret = poll_event({ .timeout = options.timeout });
        if (ret.has_value()) {
            dispatch_event(ret.value());
        } else {
            break;
        }
    }
}

} /* namespace ext::ui */