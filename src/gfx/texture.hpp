#pragma once

#include <libext/core/math.hpp>

namespace ext::gfx {

class texture {
private:
    ext::size<double> _size;
public:
    ext::size<double> const& size() const;
};

} /* namespace ext::gfx */