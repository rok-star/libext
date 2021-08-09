#include <libext/core.hpp>
#include <libext/ui.hpp>

auto const APP_TITLE = ext::string("libext UI example");

int main() {

    auto exit_ = false;
    auto app = ext::ui::app({ .title = APP_TITLE });
    // auto win = ext::ui::window({
    //     .title = APP_TITLE,
    //     .closable = true,
    //     .visible = true
    // });

    for (;;) {
        for (auto const& event : app.poll({ .timeout = 1000 })) {
            if (event.type() == ext::ui::app_event_type::exit) {
                exit_ = true;
            }
        }

        if (exit_) {
            break;
        }
    }

    ext::output("%s\n", "exiting...");
    return 0;
}