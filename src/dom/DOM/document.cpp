#include <vector>
#include <iostream>
#include "Editor/Components/DOM/Document.hpp"

namespace raz {

Document::Document()
    : _keepUpdate(false) {
    _label = "document";
}

void Document::postEvent(sf::RenderWindow const& window, sf::Event const& event) {

}

void Document::update(sf::RenderWindow const& window) {
    auto const sizeU = window.getSize();

    _position = raz::ElementPosition::Absolute;
    _maxWidth = std::nullopt;
    _maxHeight = std::nullopt;
    _minWidth = std::nullopt;
    _minHeight = std::nullopt;
    _marginLeft = std::nullopt;
    _marginTop = std::nullopt;
    _marginRight = std::nullopt;
    _marginBottom = std::nullopt;
    _bottom = std::nullopt;
    _right = std::nullopt;
    _left = std::nullopt;
    _top = std::nullopt;
    _width = static_cast<double>(sizeU.x);
    _height = static_cast<double>(sizeU.y);

    _update(
        window,
        *this,
        static_cast<double>(sizeU.x),
        static_cast<double>(sizeU.y)
    );

    _adjust(
        window,
        *this,
        { 0.0, 0.0 }
    );
}

void Document::render(sf::RenderWindow& window) {
    window.clear();

    _render(window, *this, { 0, 0 });
}

} /* namespace raz */