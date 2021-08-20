#ifdef __linux__
    #define _POSIX_C_SOURCE 200809L
#endif

#include <libext/core/signal.hpp>

namespace ext {

signal_event::signal_event(std::int32_t const& signum)
    : _signum(signum) {}

std::int32_t const& signal_event::signum() const {
    return _signum;
}

signal::signal(ext::array<std::int32_t> const& signums)
    : _events() {

    auto sigaction_s = (struct sigaction){};
    sigaction_s.sa_handler = signal::_handler;

	for (std::int64_t i = 0; i < signums.size(); i++) {
		auto signum = signums[i];

		assert(signum > 0);
		assert(signum < 255);

		_map[signum] = { this, false };
        auto err = sigaction(signum, &sigaction_s, nullptr);
        if (err != 0) {
            ext::abort("sigaction() failed: %s\n", strerror(err));
        }
	}
}

ext::pair<ext::signal*, bool> signal::_map[256] = {};

void signal::_handler(std::int32_t signum) {
	assert(signum > 0);
	assert(signum < 255);
    _map[signum].value() = true;
}

ext::array<ext::signal_event> const& signal::poll() {
    _events.clear();

    for (std::int32_t i = 0; i < 255; i++) {
        if ((_map[i].key() == this)
        && (_map[i].value() == true)) {
            _events.push(
                ext::signal_event(i)
            );
        }
    }

    return _events;
}

} /* namespace ext */