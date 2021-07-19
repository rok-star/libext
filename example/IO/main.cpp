#include <libext/???.hpp>

bool _exit = false;

int main() {

    auto status = ext::status();
    auto stdin = ext::io::open("//stdin", status);

    if (status.type() == ext::status_type::failure) {
        ext::abort("%s\n", status.message().c_string());
    }

    auto poller = ext::io::poller({ &stdin });

    for (;;) {
        for (auto const& event : poller.poll({ .timeout = 1_ms })) {
            if (event.type() == ext::io::event_type::readable) {
                auto chunk = event.stream.read(); // ext::array<char>

                ;
            }
        }

        if (_exit) {
            break;
        }
    }

}