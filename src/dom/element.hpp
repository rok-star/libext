#pragma once

#include <cinttypes>
#include <libext/core/math.hpp>
#include <libext/core/string.hpp>
#include <libext/core/optional.hpp>
#include <libext/gfx/context.hpp>
#include <libext/gfx/texture.hpp>
#include <libext/gfx/color.hpp>

namespace ext::dom {

class document;

enum class element_position {
    relative,
    absolute
};

enum class element_direction {
    column,
    row
};

enum class element_align_children {
    start,
    center,
    end,
    stretch
};

enum class element_justify_children {
    start,
    center,
    end,
    space_between,
    space_around,
    space_evenly
};

enum class element_background_position {
    default_,
    stretch,
    cover,
    fit
};

class element {
    friend document;
private:
    ext::string _label;
    ext::rect<double> _client_rect;
    ext::rect<double> _margin_rect;
    ext::size<double> _content_size;
    ext::dom::element* _parent;
    ext::array<ext::dom::element*> _children;
    ext::optional<bool> _flex;
    ext::optional<double> _width;
    ext::optional<double> _height;
    ext::optional<double> _left;
    ext::optional<double> _top;
    ext::optional<double> _right;
    ext::optional<double> _bottom;
    ext::optional<double> _max_width;
    ext::optional<double> _min_width;
    ext::optional<double> _max_height;
    ext::optional<double> _min_height;
    ext::optional<double> _margin_left;
    ext::optional<double> _margin_top;
    ext::optional<double> _margin_right;
    ext::optional<double> _margin_bottom;
    ext::optional<double> _padding_left;
    ext::optional<double> _padding_top;
    ext::optional<double> _padding_right;
    ext::optional<double> _padding_bottom;
    ext::optional<ext::dom::element_position> _position;
    ext::optional<ext::dom::element_direction> _direction;
    ext::optional<ext::dom::element_align_children> _align_children;
    ext::optional<ext::dom::element_justify_children> _justify_children;
    ext::optional<ext::gfx::color> _background_color;
    ext::optional<ext::gfx::color> _border_color;
    ext::optional<ext::gfx::color> _border_left_color;
    ext::optional<ext::gfx::color> _border_top_color;
    ext::optional<ext::gfx::color> _border_right_color;
    ext::optional<ext::gfx::color> _border_bottom_color;
    ext::optional<double> _border_width;
    ext::optional<double> _border_left_width;
    ext::optional<double> _border_top_width;
    ext::optional<double> _border_right_width;
    ext::optional<double> _border_bottom_width;
    ext::optional<ext::gfx::texture*> _background_image;
    ext::optional<ext::dom::element_background_position> _background_position;
    void _update(
        ext::gfx::context const& context,
        ext::dom::document const& document,
        ext::optional<double> const& width,
        ext::optional<double> const& height
    );
    void _adjust(
        ext::gfx::context const& context,
        ext::dom::document const& document,
        ext::point<double> const& origin
    );
    void _render(
        ext::gfx::context& context,
        ext::dom::document const& document,
        ext::point<double> const& origin
    );
public:
    element(ext::dom::element const&) = delete;
    element(ext::dom::element &&) = delete;
    ext::dom::element& operator=(ext::dom::element const&) = delete;
    ext::dom::element& operator=(ext::dom::element &&) = delete;
    ~element();
    element();
    ext::string const& label() const;
    ext::rect<double> const& client_rect() const;
    ext::rect<double> const& margin_rect() const;
    ext::size<double> const& content_size() const;
    ext::array<element*> const& children() const;
    ext::dom::element const* parent() const;
    ext::dom::element* parent();
    ext::optional<bool> const& flex() const;
    ext::optional<double> const& width() const;
    ext::optional<double> const& height() const;
    ext::optional<double> const& left() const;
    ext::optional<double> const& top() const;
    ext::optional<double> const& right() const;
    ext::optional<double> const& bottom() const;
    ext::optional<double> const& max_width() const;
    ext::optional<double> const& min_width() const;
    ext::optional<double> const& max_height() const;
    ext::optional<double> const& min_height() const;
    ext::optional<double> const& margin_left() const;
    ext::optional<double> const& margin_top() const;
    ext::optional<double> const& margin_right() const;
    ext::optional<double> const& margin_bottom() const;
    ext::optional<double> const& padding_left() const;
    ext::optional<double> const& padding_top() const;
    ext::optional<double> const& padding_right() const;
    ext::optional<double> const& padding_bottom() const;
    ext::optional<ext::dom::element_position> const& position() const;
    ext::optional<ext::dom::element_direction> const& direction() const;
    ext::optional<ext::dom::element_align_children> const& align_children() const;
    ext::optional<ext::dom::element_justify_children> const& justify_children() const;
    ext::optional<ext::gfx::color> const& background_color() const;
    ext::optional<ext::gfx::color> const& border_color() const;
    ext::optional<ext::gfx::color> const& border_left_color() const;
    ext::optional<ext::gfx::color> const& border_top_color() const;
    ext::optional<ext::gfx::color> const& border_right_color() const;
    ext::optional<ext::gfx::color> const& border_bottom_color() const;
    ext::optional<double> const& border_width() const;
    ext::optional<double> const& border_left_width() const;
    ext::optional<double> const& border_top_width() const;
    ext::optional<double> const& border_right_width() const;
    ext::optional<double> const& border_bottom_width() const;
    ext::optional<ext::gfx::texture*> const& background_image() const;
    ext::optional<ext::dom::element_background_position> const& background_position() const;
    void set_label(ext::string const& label);
    void set_flex(ext::optional<bool> const& flex);
    void set_width(ext::optional<double> const& width);
    void set_height(ext::optional<double> const& height);
    void set_left(ext::optional<double> const& left);
    void set_top(ext::optional<double> const& top);
    void set_right(ext::optional<double> const& right);
    void set_bottom(ext::optional<double> const& bottom);
    void set_max_width(ext::optional<double> const& max_width);
    void set_min_width(ext::optional<double> const& min_width);
    void set_max_height(ext::optional<double> const& max_height);
    void set_min_height(ext::optional<double> const& min_height);
    void set_margin_left(ext::optional<double> const& margin_left);
    void set_margin_top(ext::optional<double> const& margin_top);
    void set_margin_right(ext::optional<double> const& margin_right);
    void set_margin_bottom(ext::optional<double> const& margin_bottom);
    void set_padding_left(ext::optional<double> const& padding_left);
    void set_padding_top(ext::optional<double> const& padding_top);
    void set_padding_right(ext::optional<double> const& padding_right);
    void set_padding_bottom(ext::optional<double> const& padding_bottom);
    void set_position(ext::optional<ext::dom::element_position> const& position);
    void set_direction(ext::optional<ext::dom::element_direction> const& direction);
    void set_align_children(ext::optional<ext::dom::element_align_children> const& align_children);
    void set_justify_children(ext::optional<ext::dom::element_justify_children> const& justify_children);
    void set_background_color(ext::optional<ext::gfx::color> const& background_color);
    void set_border_color(ext::optional<ext::gfx::color> const& border_color);
    void set_border_left_color(ext::optional<ext::gfx::color> const& border_left_color);
    void set_border_top_color(ext::optional<ext::gfx::color> const& border_top_color);
    void set_border_right_color(ext::optional<ext::gfx::color> const& border_right_color);
    void set_border_bottom_color(ext::optional<ext::gfx::color> const& border_bottom_color);
    void set_border_width(ext::optional<double> const& border_width);
    void set_border_left_width(ext::optional<double> const& border_left_width);
    void set_border_top_width(ext::optional<double> const& border_top_width);
    void set_border_right_width(ext::optional<double> const& border_right_width);
    void set_border_bottom_width(ext::optional<double> const& border_bottom_width);
    void set_background_image(ext::optional<ext::gfx::texture*> const& background_image);
    void set_background_position(ext::optional<ext::dom::element_background_position> const& background_position);
    void add_child(ext::dom::element& element);
    bool remove_child(ext::dom::element& element);
};

} /* namespace ext::dom */