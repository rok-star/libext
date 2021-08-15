#include <iostream>
#include <libext/dom/element.hpp>

namespace ext::dom {

element::~element() {}

element::element()
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

void element::_update(
    ext::gfx::context const& context,
    ext::dom::document const& document,
    ext::optional<double> const& width,
    ext::optional<double> const& height
) {
    _clientRect = { 0.0, 0.0, 0.0, 0.0 };
    _marginRect = { 0.0, 0.0, 0.0, 0.0 };
    _contentSize = { 0.0, 0.0 };

    auto const position = _position.value_or(ext::dom::ElementPosition::Relative);
    auto const direction = _direction.value_or(ext::dom::ElementDirection::Column);
    auto const alignChildren = _alignChildren.value_or(ext::dom::ElementAlignChildren::Start);
    auto const justifyChildren = _justifyChildren.value_or(ext::dom::ElementJustifyChildren::Start);
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

        if (direction == ext::dom::ElementDirection::Column) {
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
        if (direction == ext::dom::ElementDirection::Column) {
            return ((_clientRect.size.height - paddingHeight) - _contentSize.height);
        } else {
            return ((_clientRect.size.width - paddingWidth) - _contentSize.width);
        }
    };

    auto const getOccupied = [&](std::vector<ext::dom::element*> const& items) {
        auto ret = 0.0;
        if (direction == ext::dom::ElementDirection::Column) {
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

    auto childWidth = ext::optional<double>(std::nullopt);
    auto childHeight = ext::optional<double>(std::nullopt);

    if (alignChildren == ext::dom::ElementAlignChildren::Stretch) {
        if ((direction == ext::dom::ElementDirection::Column)
        && (width.has_value() == true)) {
            applyWidth();
            childWidth = (_clientRect.size.width - paddingWidth);
        }

        if ((direction == ext::dom::ElementDirection::Row)
        && (height.has_value() == true)) {
            applyHeight();
            childHeight = (_clientRect.size.height - paddingHeight);
        }
    }

    auto const updateChildren = [&]() {
        ext::dom::element* prev = nullptr;

        for (auto& child : _children) {
            child->_update(
                context,
                document,
                ((direction == ext::dom::ElementDirection::Column) ? childWidth : std::nullopt),
                ((direction == ext::dom::ElementDirection::Row) ? childHeight : std::nullopt)
            );

            prev = child;
        }

        resolveSize();
    };

    auto const adjustChildren = [&]() {
        ext::dom::element* prev = nullptr;

        if (direction == ext::dom::ElementDirection::Column) {
            for (auto& child : _children) {
                child->_adjust(
                    context,
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
                    context,
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

    if (alignChildren == ext::dom::ElementAlignChildren::Stretch) {
        if ((direction == ext::dom::ElementDirection::Column)
        && (childWidth.has_value() == false)) {
            childWidth = (_clientRect.size.width - paddingWidth);
            updateChildren();
        }

        if ((direction == ext::dom::ElementDirection::Row)
        && (childHeight.has_value() == false)) {
            childHeight = (_clientRect.size.height - paddingHeight);
            updateChildren();
        }
    }

    auto flexItems = std::vector<ext::dom::element*>();

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

        if (direction == ext::dom::ElementDirection::Column) {
            for (int64_t i = (flexItems.size() - 1); i >= 0; i--) {
                flexItems[i]->_update(context, document, childWidth, share);

                if (flexItems[i]->_marginRect.size.height != share) {
                    help::removeIndex(flexItems, i);
                }
            }
        } else {
            for (int64_t i = (flexItems.size() - 1); i >= 0; i--) {
                flexItems[i]->_update(context, document, share, childHeight);

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

void element::_adjust(
    ext::gfx::context const& context,
    ext::dom::document const& document,
    ext::dom::Point const& origin
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

void element::_render(
    ext::gfx::context& context,
    ext::dom::document const& document,
    ext::dom::Point const& origin
) {
    auto rect = ext::dom::Rect({
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
        context.draw(shape);
    }

    for (auto& child : _children) {
        child->_render(context, document, rect.origin);
    }
}

std::string const& element::label() const {
    return _label;
}

ext::dom::Rect const& element::clientRect() const {
    return _clientRect;
}

ext::dom::Rect const& element::marginRect() const {
    return _marginRect;
}

ext::dom::Size const& element::contentSize() const {
    return _contentSize;
}

std::vector<element*> const& element::children() const {
    return _children;
}

ext::dom::element const* element::parent() const {
    return _parent;
}

ext::dom::element* element::parent() {
    return _parent;
}

ext::optional<bool> const& element::flex() const {
    return _flex;
}

ext::optional<double> const& element::width() const {
    return _width;
}

ext::optional<double> const& element::height() const {
    return _height;
}

ext::optional<double> const& element::left() const {
    return _left;
}

ext::optional<double> const& element::top() const {
    return _top;
}

ext::optional<double> const& element::right() const {
    return _right;
}

ext::optional<double> const& element::bottom() const {
    return _bottom;
}

ext::optional<double> const& element::maxWidth() const {
    return _maxWidth;
}

ext::optional<double> const& element::minWidth() const {
    return _minWidth;
}

ext::optional<double> const& element::maxHeight() const {
    return _maxHeight;
}

ext::optional<double> const& element::minHeight() const {
    return _minHeight;
}

ext::optional<double> const& element::marginLeft() const {
    return _marginLeft;
}

ext::optional<double> const& element::marginTop() const {
    return _marginTop;
}

ext::optional<double> const& element::marginRight() const {
    return _marginRight;
}

ext::optional<double> const& element::marginBottom() const {
    return _marginBottom;
}

ext::optional<double> const& element::paddingLeft() const {
    return _paddingLeft;
}

ext::optional<double> const& element::paddingTop() const {
    return _paddingTop;
}

ext::optional<double> const& element::paddingRight() const {
    return _paddingRight;
}

ext::optional<double> const& element::paddingBottom() const {
    return _paddingBottom;
}

ext::optional<ext::dom::ElementPosition> const& element::position() const {
    return _position;
}

ext::optional<ext::dom::ElementDirection> const& element::direction() const {
    return _direction;
}

ext::optional<ext::dom::ElementAlignChildren> const& element::alignChildren() const {
    return _alignChildren;
}

ext::optional<ext::dom::ElementJustifyChildren> const& element::justifyChildren() const {
    return _justifyChildren;
}

ext::optional<sf::Color> const& element::backgroundColor() const {
    return _backgroundColor;
}

ext::optional<sf::Color> const& element::borderColor() const {
    return _borderColor;
}

ext::optional<sf::Color> const& element::borderLeftColor() const {
    return _borderLeftColor;
}

ext::optional<sf::Color> const& element::borderTopColor() const {
    return _borderTopColor;
}

ext::optional<sf::Color> const& element::borderRightColor() const {
    return _borderRightColor;
}

ext::optional<sf::Color> const& element::borderBottomColor() const {
    return _borderBottomColor;
}

ext::optional<double> const& element::borderWidth() const {
    return _borderWidth;
}

ext::optional<double> const& element::borderLeftWidth() const {
    return _borderLeftWidth;
}

ext::optional<double> const& element::borderTopWidth() const {
    return _borderTopWidth;
}

ext::optional<double> const& element::borderRightWidth() const {
    return _borderRightWidth;
}

ext::optional<double> const& element::borderBottomWidth() const {
    return _borderBottomWidth;
}

ext::optional<ext::dom::Image*> const& element::backgroundImage() const {
    return _backgroundImage;
}

ext::optional<ext::dom::ElementBackgroundPosition> const& element::backgroundPosition() const {
    return _backgroundPosition;
}

void element::setLabel(std::string const& label) {
    _label = label;
}

void element::setFlex(ext::optional<bool> const& flex) {
    _flex = flex;
}

void element::setWidth(ext::optional<double> const& width) {
    _width = width;
}

void element::setHeight(ext::optional<double> const& height) {
    _height = height;
}

void element::setLeft(ext::optional<double> const& left) {
    _left = left;
}

void element::setTop(ext::optional<double> const& top) {
    _top = top;
}

void element::setRight(ext::optional<double> const& right) {
    _right = right;
}

void element::setBottom(ext::optional<double> const& bottom) {
    _bottom = bottom;
}

void element::setMaxWidth(ext::optional<double> const& maxWidth) {
    _maxWidth = maxWidth;
}

void element::setMinWidth(ext::optional<double> const& minWidth) {
    _minWidth = minWidth;
}

void element::setMaxHeight(ext::optional<double> const& maxHeight) {
    _maxHeight = maxHeight;
}

void element::setMinHeight(ext::optional<double> const& minHeight) {
    _minHeight = minHeight;
}

void element::setMarginLeft(ext::optional<double> const& marginLeft) {
    _marginLeft = marginLeft;
}

void element::setMarginTop(ext::optional<double> const& marginTop) {
    _marginTop = marginTop;
}

void element::setMarginRight(ext::optional<double> const& marginRight) {
    _marginRight = marginRight;
}

void element::setMarginBottom(ext::optional<double> const& marginBottom) {
    _marginBottom = marginBottom;
}

void element::setPaddingLeft(ext::optional<double> const& paddingLeft) {
    _paddingLeft = paddingLeft;
}

void element::setPaddingTop(ext::optional<double> const& paddingTop) {
    _paddingTop = paddingTop;
}

void element::setPaddingRight(ext::optional<double> const& paddingRight) {
    _paddingRight = paddingRight;
}

void element::setPaddingBottom(ext::optional<double> const& paddingBottom) {
    _paddingBottom = paddingBottom;
}

void element::setPosition(ext::optional<ext::dom::ElementPosition> const& position) {
    _position = position;
}

void element::setDirection(ext::optional<ext::dom::ElementDirection> const& direction) {
    _direction = direction;
}

void element::setAlignChildren(ext::optional<ext::dom::ElementAlignChildren> const& alignChildren) {
    _alignChildren = alignChildren;
}

void element::setJustifyChildren(ext::optional<ext::dom::ElementJustifyChildren> const& justifyChildren) {
    _justifyChildren = justifyChildren;
}

void element::setBackgroundColor(ext::optional<sf::Color> const& backgroundColor) {
    _backgroundColor = backgroundColor;
}

void element::setBorderColor(ext::optional<sf::Color> const& borderColor) {
    _borderColor = borderColor;
}

void element::setBorderLeftColor(ext::optional<sf::Color> const& borderLeftColor) {
    _borderLeftColor = borderLeftColor;
}

void element::setBorderTopColor(ext::optional<sf::Color> const& borderTopColor) {
    _borderTopColor = borderTopColor;
}

void element::setBorderRightColor(ext::optional<sf::Color> const& borderRightColor) {
    _borderRightColor = borderRightColor;
}

void element::setBorderBottomColor(ext::optional<sf::Color> const& borderBottomColor) {
    _borderBottomColor = borderBottomColor;
}

void element::setBorderWidth(ext::optional<double> const& borderWidth) {
    _borderWidth = borderWidth;
}

void element::setBorderLeftWidth(ext::optional<double> const& borderLeftWidth) {
    _borderLeftWidth = borderLeftWidth;
}

void element::setBorderTopWidth(ext::optional<double> const& borderTopWidth) {
    _borderTopWidth = borderTopWidth;
}

void element::setBorderRightWidth(ext::optional<double> const& borderRightWidth) {
    _borderRightWidth = borderRightWidth;
}

void element::setBorderBottomWidth(ext::optional<double> const& borderBottomWidth) {
    _borderBottomWidth = borderBottomWidth;
}

void element::setBackgroundImage(ext::optional<ext::dom::Image*> const& backgroundImage) {
    _backgroundImage = backgroundImage;
}

void element::setBackgroundPosition(ext::optional<ext::dom::ElementBackgroundPosition> const& backgroundPosition) {
    _backgroundPosition = backgroundPosition;
}

void element::addChild(ext::dom::element& element) {
    if (element.parent() != nullptr) {
        element.parent()->removeChild(element);
    }

    _children.push_back(&element);
    element._parent = this;
}

bool element::removeChild(ext::dom::element& element) {
    auto index = help::indexOf(_children, &element);

    if (index > -1) {
        help::removeIndex(_children, index);
        element._parent = nullptr;
        return true;
    } else {
        return false;
    }
}

} /* namespace ext::dom */