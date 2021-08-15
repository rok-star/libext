#include <vector>
#include <iostream>
#include <libext/dom/document.hpp>

namespace ext::dom {

document::document()
    : _keep_update(false) {
    _label = "document";
}

void document::event(ext::gfx::context const& context, ext::ui::event const& event) {

}

void document::update(ext::gfx::context const& context) {
    _position = ext::dom::element_position::absolute;
    _max_width = ext::nullopt;
    _max_height = ext::nullopt;
    _min_width = ext::nullopt;
    _min_height = ext::nullopt;
    _margin_left = ext::nullopt;
    _margin_top = ext::nullopt;
    _margin_right = ext::nullopt;
    _margin_bottom = ext::nullopt;
    _bottom = ext::nullopt;
    _right = ext::nullopt;
    _left = ext::nullopt;
    _top = ext::nullopt;
    _width = context.size().width;
    _height = context.size().height;

    _update(
        context,
        *this,
        context.size().width,
        context.size().height
    );

    _adjust(
        context,
        *this,
        { 0.0, 0.0 }
    );
}

void document::render(ext::gfx::context& context) {
    context.fill_rect(
        { 0.0, 0.0, context.size() },
        ext::gfx::color::white_color()
    );

    _render(context, *this, { 0, 0 });
}

} /* namespace ext::dom */