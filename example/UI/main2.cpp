#include <libext/core.hpp>
#include <libext/ui.hpp>

auto const APP_TITLE = ext::string("libext UI example");

int main() {

	auto exit_ = false;
	auto app = ext::ui::app({ .title = APP_TITLE });
	// auto win = ext::ui::window({ .title = APP_TITLE });

	auto on_quit = [&]() {
		// ext::ui::confirm_box(APP_TITLE, "Do you really wanna exit?", [&](bool yes) {
		// 	if (yes) {
		// 		exit_ = true;
		// 	}
		// });
	};

	app.on_exit(on_quit);
	// win.on_close(on_quit);

	for (;;) {
		app.process({ .timeout = 1_sec });

		if (exit_) {
            break;
        }
	}

	return 0;
}