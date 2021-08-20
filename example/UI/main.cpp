#include <libext/core.hpp>
#include <libext/ui.hpp>

auto const APP_TITLE = ext::string("libext UI example");

int main() {

    auto exit_ = false;
    auto sig = ext::signal({ SIGINT, SIGQUIT });
    auto app = ext::ui::app({ .title = APP_TITLE });

    for (;;) {
        for (auto const& event : sig.poll()) {
            if (event.signum() == SIGINT) {
                ext::output("%s\n", "exiting by SIGIN...");
                exit_ = true;
            } else if (event.signum() == SIGQUIT) {
                ext::output("%s\n", "exiting by SIGQUIT...");
                exit_ = true;
            }
        }

        for (auto const& event : app.poll({ .timeout = 1000 })) {
            ext::output("%s\n", "event");
            if (event.type() == ext::ui::event_type::exit) {
                ext::output("%s\n", "exiting by app\'s event...");
                exit_ = true;
            }
        }

        if (exit_) {
            break;
        }
    }

    return 0;
}