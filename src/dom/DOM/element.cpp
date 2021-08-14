#include <iostream>
#include <fmt/core.h>
#include "Editor/Components/DOM/Document.hpp"
#include "Editor/Components/DOM/Element.hpp"
#include "Helpers/Vector.hpp"

namespace raz {

Element::~Element() {}

Element::Element()
    : _label("")
    , _clientRect({ 0, 0, 0, 0 })
    , _marginRect({ 0, 0, 0, 0 })
    , _contentSize({ 0, 0 })
    , _parent(nullptr)
    , _children({})
    , _flex(std::nullopt)
    , _width(std::nullopt)
    , _height(std::nullopt)
    , _left(std::nullopt)
    , _top(std::nullopt)
    , _right(std::nullopt)
    , _bottom(std::nullopt)
    , _maxWidth(std::nullopt)
    , _minWidth(std::nullopt)
    , _maxHeight(std::nullopt)
    , _minHeight(std::nullopt)
    , _marginLeft(0)
    , _marginTop(0)
    , _marginRight(0)
    , _marginBottom(0)
    , _paddingLeft(0)
    , _paddingTop(0)
    , _paddingRight(0)
    , _paddingBottom(0)
    , _position(std::nullopt)
    , _direction(std::nullopt)
    , _alignChildren(std::nullopt)
    , _justifyChildren(std::nullopt)
    , _backgroundColor(std::nullopt)
    , _borderColor(std::nullopt)
    , _borderLeftColor(std::nullopt)
    , _borderTopColor(std::nullopt)
    , _borderRightColor(std::nullopt)
    , _borderBottomColor(std::nullopt)
    , _borderWidth(std::nullopt)
    , _borderLeftWidth(std::nullopt)
    , _borderTopWidth(std::nullopt)
    , _borderRightWidth(std::nullopt)
    , _borderBottomWidth(std::nullopt)
    , _backgroundImage(std::nullopt)
    , _backgroundPosition(std::nullopt) {}

void Element::_update(
    sf::RenderWindow const& window,
    raz::Document const& document,
    std::optional<double> const& width,
    std::optional<double> const& height
) {
    _clientRect = { 0.0, 0.0, 0.0, 0.0 };
    _marginRect = { 0.0, 0.0, 0.0, 0.0 };
    _contentSize = { 0.0, 0.0 };

    auto const position = _position.value_or(raz::ElementPosition::Relative);
    auto const direction = _direction.value_or(raz::ElementDirection::Column);
    auto const alignChildren = _alignChildren.value_or(raz::ElementAlignChildren::Start);
    auto const justifyChildren = _justifyChildren.value_or(raz::ElementJustifyChildren::Start);
    auto const paddingLeft = _paddingLeft.value_or(0.0);
    auto const paddingTop = _paddingTop.value_or(0.0);
    auto const paddingRight = _paddingRight.value_or(0.0);
    auto const paddingBottom = _paddingBottom.value_or(0.0);
    auto const marginLeft = _marginLeft.value_or(0.0);
    auto const marginTop = _marginTop.value_or(0.0);
    auto const marginRight = _marginRight.value_or(0.0);
    auto const marginBottom = _marginBottom.value_or(0.0);
    auto const paddingWidth = (paddingLeft + paddingRight);
    auto const paddingHeight = (paddingTop + paddingBottom);
    auto const marginWidth = (marginLeft + marginRight);
    auto const marginHeight = (marginTop + marginBottom);

    auto const applyWidth = [&]() {
        if (width.has_value()) {
            _clientRect.size.width = (width.value() - marginWidth);
        }

        _clientRect.size.width = _width.value_or(_clientRect.size.width);
        _clientRect.size.width = _minWidth.has_value() ? std::max(_clientRect.size.width, _minWidth.value()) : _clientRect.size.width;
        _clientRect.size.width = _maxWidth.has_value() ? std::min(_clientRect.size.width, _maxWidth.value()) : _clientRect.size.width;
        _marginRect.size.width = (_clientRect.size.width + marginWidth);
    };

    auto const applyHeight = [&]() {
        if (height.has_value()) {
            _clientRect.size.height = (height.value() - marginHeight);
        }

        _clientRect.size.height = _height.value_or(_clientRect.size.height);
        _clientRect.size.height = _minHeight.has_value() ? std::max(_clientRect.size.height, _minHeight.value()) : _clientRect.size.height;
        _clientRect.size.height = _maxHeight.has_value() ? std::min(_clientRect.size.height, _maxHeight.value()) : _clientRect.size.height;
        _marginRect.size.height = (_clientRect.size.height + marginHeight);
    };

    auto const resolveSize = [&]() {
        _contentSize = { 0.0, 0.0 };

        if (direction == raz::ElementDirection::Column) {
            for (auto& child : _children) {
                _contentSize.width = std::max(_contentSize.width, child->_marginRect.size.width);
                _contentSize.height += child->_marginRect.size.height;
            }
        } else {
            for (auto& child : _children) {
                _contentSize.width += child->_marginRect.size.width;
                _contentSize.height += std::max(_contentSize.height, child->_marginRect.size.height);
            }
        }

        _clientRect.size = {
            (_contentSize.width + paddingWidth),
            (_contentSize.height + paddingHeight)
        };

        _marginRect.size = {
            (_clientRect.size.width + marginWidth),
            (_clientRect.size.height + marginHeight)
        };

        applyWidth();
        applyHeight();
    };

    auto const getRemained = [&]() {
        if (direction == raz::ElementDirection::Column) {
            return ((_clientRect.size.height - paddingHeight) - _contentSize.height);
        } else {
            return ((_clientRect.size.width - paddingWidth) - _contentSize.width);
        }
    };

    auto const getOccupied = [&](std::vector<raz::Element*> const& items) {
        auto ret = 0.0;
        if (direction == raz::ElementDirection::Column) {
            for (auto& child : items) {
                ret += child->_marginRect.size.height;
            }
        } else {
            for (auto& child : items) {
                ret += child->_marginRect.size.width;
            }
        }
        return ret;
    };

    auto childWidth = std::optional<double>(std::nullopt);
    auto childHeight = std::optional<double>(std::nullopt);

    if (alignChildren == raz::ElementAlignChildren::Stretch) {
        if ((direction == raz::ElementDirection::Column)
        && (width.has_value() == true)) {
            applyWidth();
            childWidth = (_clientRect.size.width - paddingWidth);
        }

        if ((direction == raz::ElementDirection::Row)
        && (height.has_value() == true)) {
            applyHeight();
            childHeight = (_clientRect.size.height - paddingHeight);
        }
    }

    auto const updateChildren = [&]() {
        raz::Element* prev = nullptr;

        for (auto& child : _children) {
            child->_update(
                window,
                document,
                ((direction == raz::ElementDirection::Column) ? childWidth : std::nullopt),
                ((direction == raz::ElementDirection::Row) ? childHeight : std::nullopt)
            );

            prev = child;
        }

        resolveSize();
    };

    auto const adjustChildren = [&]() {
        raz::Element* prev = nullptr;

        if (direction == raz::ElementDirection::Column) {
            for (auto& child : _children) {
                child->_adjust(
                    window,
                    document,
                    {
                        paddingLeft,
                        ((prev != nullptr) ? prev->_marginRect.bottom() : paddingTop)
                    }
                );

                prev = child;
            }
        } else {
            for (auto& child : _children) {
                child->_adjust(
                    window,
                    document,
                    {
                        ((prev != nullptr) ? prev->_marginRect.right() : paddingLeft),
                        paddingTop
                    }
                );

                prev = child;
            }
        }
    };

    updateChildren();

    if (alignChildren == raz::ElementAlignChildren::Stretch) {
        if ((direction == raz::ElementDirection::Column)
        && (childWidth.has_value() == false)) {
            childWidth = (_clientRect.size.width - paddingWidth);
            updateChildren();
        }

        if ((direction == raz::ElementDirection::Row)
        && (childHeight.has_value() == false)) {
            childHeight = (_clientRect.size.height - paddingHeight);
            updateChildren();
        }
    }

    auto flexItems = std::vector<raz::Element*>();

    for (auto& child : _children) {
        if (child->flex().value_or(false) == true) {
            flexItems.push_back(child);
        }
    }

    for (;;) {
        if (flexItems.size() == 0) {
            break;
        }

        auto remained = getRemained();

        if (remained <= 0.0) {
            break;
        }

        auto shareable = (getOccupied(flexItems) + remained);
        auto share = (shareable / static_cast<double>(flexItems.size()));

        if (direction == raz::ElementDirection::Column) {
            for (int64_t i = (flexItems.size() - 1); i >= 0; i--) {
                flexItems[i]->_update(window, document, childWidth, share);

                if (flexItems[i]->_marginRect.size.height != share) {
                    help::removeIndex(flexItems, i);
                }
            }
        } else {
            for (int64_t i = (flexItems.size() - 1); i >= 0; i--) {
                flexItems[i]->_update(window, document, share, childHeight);

                if (flexItems[i]->_marginRect.size.width != share) {
                    help::removeIndex(flexItems, i);
                }
            }
        }

        resolveSize();
    }

    // check justify Items...

    adjustChildren();
}

void Element::_adjust(
    sf::RenderWindow const& window,
    raz::Document const& document,
    raz::Point const& origin
) {
    _marginRect.origin = {
        origin.x,
        origin.y
    };

    _clientRect.origin = {
        (origin.x + _marginLeft.value_or(0.0)),
        (origin.y + _marginTop.value_or(0.0))
    };
}

void Element::_render(
    sf::RenderWindow& window,
    raz::Document const& document,
    raz::Point const& origin
) {
    auto rect = raz::Rect({
        .origin = (_clientRect.origin + origin),
        .size = _clientRect.size
    });

    auto draw = false;
    auto shape = sf::RectangleShape();
    shape.setPosition(rect.origin.Vector2f());
    shape.setSize(rect.size.Vector2f());
    shape.setFillColor(sf::Color::Red);

    if (_backgroundColor.has_value()) {
        shape.setFillColor(_backgroundColor.value());
        draw = true;
    }

    if (_borderColor.has_value() && (_borderWidth.value_or(1.0) > 0.0)) {
        shape.setOutlineColor(_borderColor.value());
        shape.setOutlineThickness(_borderWidth.value_or(1.0));
        draw = true;
    }

    if (draw) {
        window.draw(shape);
    }

    for (auto& child : _children) {
        child->_render(window, document, rect.origin);
    }
}

std::string const& Element::label() const {
    return _label;
}

raz::Rect const& Element::clientRect() const {
    return _clientRect;
}

raz::Rect const& Element::marginRect() const {
    return _marginRect;
}

raz::Size const& Element::contentSize() const {
    return _contentSize;
}

std::vector<Element*> const& Element::children() const {
    return _children;
}

raz::Element const* Element::parent() const {
    return _parent;
}

raz::Element* Element::parent() {
    return _parent;
}

std::optional<bool> const& Element::flex() const {
    return _flex;
}

std::optional<double> const& Element::width() const {
    return _width;
}

std::optional<double> const& Element::height() const {
    return _height;
}

std::optional<double> const& Element::left() const {
    return _left;
}

std::optional<double> const& Element::top() const {
    return _top;
}

std::optional<double> const& Element::right() const {
    return _right;
}

std::optional<double> const& Element::bottom() const {
    return _bottom;
}

std::optional<double> const& Element::maxWidth() const {
    return _maxWidth;
}

std::optional<double> const& Element::minWidth() const {
    return _minWidth;
}

std::optional<double> const& Element::maxHeight() const {
    return _maxHeight;
}

std::optional<double> const& Element::minHeight() const {
    return _minHeight;
}

std::optional<double> const& Element::marginLeft() const {
    return _marginLeft;
}

std::optional<double> const& Element::marginTop() const {
    return _marginTop;
}

std::optional<double> const& Element::marginRight() const {
    return _marginRight;
}

std::optional<double> const& Element::marginBottom() const {
    return _marginBottom;
}

std::optional<double> const& Element::paddingLeft() const {
    return _paddingLeft;
}

std::optional<double> const& Element::paddingTop() const {
    return _paddingTop;
}

std::optional<double> const& Element::paddingRight() const {
    return _paddingRight;
}

std::optional<double> const& Element::paddingBottom() const {
    return _paddingBottom;
}

std::optional<raz::ElementPosition> const& Element::position() const {
    return _position;
}

std::optional<raz::ElementDirection> const& Element::direction() const {
    return _direction;
}

std::optional<raz::ElementAlignChildren> const& Element::alignChildren() const {
    return _alignChildren;
}

std::optional<raz::ElementJustifyChildren> const& Element::justifyChildren() const {
    return _justifyChildren;
}

std::optional<sf::Color> const& Element::backgroundColor() const {
    return _backgroundColor;
}

std::optional<sf::Color> const& Element::borderColor() const {
    return _borderColor;
}

std::optional<sf::Color> const& Element::borderLeftColor() const {
    return _borderLeftColor;
}

std::optional<sf::Color> const& Element::borderTopColor() const {
    return _borderTopColor;
}

std::optional<sf::Color> const& Element::borderRightColor() const {
    return _borderRightColor;
}

std::optional<sf::Color> const& Element::borderBottomColor() const {
    return _borderBottomColor;
}

std::optional<double> const& Element::borderWidth() const {
    return _borderWidth;
}

std::optional<double> const& Element::borderLeftWidth() const {
    return _borderLeftWidth;
}

std::optional<double> const& Element::borderTopWidth() const {
    return _borderTopWidth;
}

std::optional<double> const& Element::borderRightWidth() const {
    return _borderRightWidth;
}

std::optional<double> const& Element::borderBottomWidth() const {
    return _borderBottomWidth;
}

std::optional<raz::Image*> const& Element::backgroundImage() const {
    return _backgroundImage;
}

std::optional<raz::ElementBackgroundPosition> const& Element::backgroundPosition() const {
    return _backgroundPosition;
}

void Element::setLabel(std::string const& label) {
    _label = label;
}

void Element::setFlex(std::optional<bool> const& flex) {
    _flex = flex;
}

void Element::setWidth(std::optional<double> const& width) {
    _width = width;
}

void Element::setHeight(std::optional<double> const& height) {
    _height = height;
}

void Element::setLeft(std::optional<double> const& left) {
    _left = left;
}

void Element::setTop(std::optional<double> const& top) {
    _top = top;
}

void Element::setRight(std::optional<double> const& right) {
    _right = right;
}

void Element::setBottom(std::optional<double> const& bottom) {
    _bottom = bottom;
}

void Element::setMaxWidth(std::optional<double> const& maxWidth) {
    _maxWidth = maxWidth;
}

void Element::setMinWidth(std::optional<double> const& minWidth) {
    _minWidth = minWidth;
}

void Element::setMaxHeight(std::optional<double> const& maxHeight) {
    _maxHeight = maxHeight;
}

void Element::setMinHeight(std::optional<double> const& minHeight) {
    _minHeight = minHeight;
}

void Element::setMarginLeft(std::optional<double> const& marginLeft) {
    _marginLeft = marginLeft;
}

void Element::setMarginTop(std::optional<double> const& marginTop) {
    _marginTop = marginTop;
}

void Element::setMarginRight(std::optional<double> const& marginRight) {
    _marginRight = marginRight;
}

void Element::setMarginBottom(std::optional<double> const& marginBottom) {
    _marginBottom = marginBottom;
}

void Element::setPaddingLeft(std::optional<double> const& paddingLeft) {
    _paddingLeft = paddingLeft;
}

void Element::setPaddingTop(std::optional<double> const& paddingTop) {
    _paddingTop = paddingTop;
}

void Element::setPaddingRight(std::optional<double> const& paddingRight) {
    _paddingRight = paddingRight;
}

void Element::setPaddingBottom(std::optional<double> const& paddingBottom) {
    _paddingBottom = paddingBottom;
}

void Element::setPosition(std::optional<raz::ElementPosition> const& position) {
    _position = position;
}

void Element::setDirection(std::optional<raz::ElementDirection> const& direction) {
    _direction = direction;
}

void Element::setAlignChildren(std::optional<raz::ElementAlignChildren> const& alignChildren) {
    _alignChildren = alignChildren;
}

void Element::setJustifyChildren(std::optional<raz::ElementJustifyChildren> const& justifyChildren) {
    _justifyChildren = justifyChildren;
}

void Element::setBackgroundColor(std::optional<sf::Color> const& backgroundColor) {
    _backgroundColor = backgroundColor;
}

void Element::setBorderColor(std::optional<sf::Color> const& borderColor) {
    _borderColor = borderColor;
}

void Element::setBorderLeftColor(std::optional<sf::Color> const& borderLeftColor) {
    _borderLeftColor = borderLeftColor;
}

void Element::setBorderTopColor(std::optional<sf::Color> const& borderTopColor) {
    _borderTopColor = borderTopColor;
}

void Element::setBorderRightColor(std::optional<sf::Color> const& borderRightColor) {
    _borderRightColor = borderRightColor;
}

void Element::setBorderBottomColor(std::optional<sf::Color> const& borderBottomColor) {
    _borderBottomColor = borderBottomColor;
}

void Element::setBorderWidth(std::optional<double> const& borderWidth) {
    _borderWidth = borderWidth;
}

void Element::setBorderLeftWidth(std::optional<double> const& borderLeftWidth) {
    _borderLeftWidth = borderLeftWidth;
}

void Element::setBorderTopWidth(std::optional<double> const& borderTopWidth) {
    _borderTopWidth = borderTopWidth;
}

void Element::setBorderRightWidth(std::optional<double> const& borderRightWidth) {
    _borderRightWidth = borderRightWidth;
}

void Element::setBorderBottomWidth(std::optional<double> const& borderBottomWidth) {
    _borderBottomWidth = borderBottomWidth;
}

void Element::setBackgroundImage(std::optional<raz::Image*> const& backgroundImage) {
    _backgroundImage = backgroundImage;
}

void Element::setBackgroundPosition(std::optional<raz::ElementBackgroundPosition> const& backgroundPosition) {
    _backgroundPosition = backgroundPosition;
}

void Element::addChild(raz::Element& element) {
    if (element.parent() != nullptr) {
        element.parent()->removeChild(element);
    }

    _children.push_back(&element);
    element._parent = this;
}

bool Element::removeChild(raz::Element& element) {
    auto index = help::indexOf(_children, &element);

    if (index > -1) {
        help::removeIndex(_children, index);
        element._parent = nullptr;
        return true;
    } else {
        return false;
    }
}

} /* namespace raz */