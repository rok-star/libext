#include <libext/app.hpp>
#include <libext/window.hpp>

auto const APP_TITLE = ext::string("libext UI example");

int main() {

    auto app = ext::ui::app({ .title = APP_TITLE });
    auto win = ext::ui::window({
        .title = APP_TITLE,
        .closable = true,
        .visible = true
    });

    ext::ui::app().run();
}