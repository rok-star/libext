#pragma once

#include <signal.h>
#include <cinttypes>
#include <libext/core/map.hpp>
#include <libext/core/array.hpp>

namespace ext {

class signal;

class signal_event {
    friend signal;
private:
    std::int32_t _signum;
    signal_event(std::int32_t const&);
public:
    std::int32_t const& signum() const;
};

class signal {
private:
    ext::array<ext::signal_event> _events;
    static ext::pair<ext::signal*, bool> _map[256];
    static void _handler(std::int32_t);
public:
    signal(ext::signal const&) = delete;
    signal(ext::signal &&) = delete;
    ext::signal& operator=(ext::signal const&) = delete;
    ext::signal& operator=(ext::signal &&) = delete;
    signal(ext::array<std::int32_t> const&);
    ext::array<ext::signal_event> const& poll();
};

} /* namespace ext */