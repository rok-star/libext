#pragma once

#include <libext/core/math.hpp>
#include <libext/gfx/color.hpp>

namespace ext::gfx {

class context {
private:
    ext::size<double> _size;
public:

    void fill_rect(ext::rect<double> const&, ext::gfx::color const&);
    ext::size<double> const& size() const;
};

} /* namespace ext::gfx */