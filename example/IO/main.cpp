#include <libext/???.hpp>

#define ABORT_ON_FAILURE() { \
    if (status.type() === ext::status_type::failure) { \
        ext::abort("%s\n", status.message().c_string()); \
    } \
}

bool exit_ = false;

int main() {

    auto status = ext::status();
    auto stdin = ext::io::open("//stdin", status);              ABORT_ON_FAILURE();
    auto signal = ext::io::open("//signals", status);           ABORT_ON_FAILURE();
    auto poller = ext::io::poller({ &stdin, &signal }, status); ABORT_ON_FAILURE();

    for (;;) {
        for (auto const& event : poller.poll({ .timeout = 1_ms })) {
            if (event.type() == ext::io::event_type::readable) {
                auto chunk = event.stream().read(); // ext::array<char> ...

                ;
            } else if (event.type() == ext::io::event_type::signal) {
                auto signum = event.stream().signal(); // int32_t ...

                if (signum == SIGINT) {
                    break;
                }
            }
        }

        if (exit_) {
            break;
        }
    }

}