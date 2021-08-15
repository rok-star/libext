#include <iostream>
#include "Editor/Components/Theme.hpp"

namespace raz {

raz::Theme const* Theme::_current = nullptr;

Theme::~Theme() {}

Theme::Theme(
    nlohmann::json const& config,
    raz::Image const& atlas,
    bool setCurrent
)   : _buttonDefaultNormalImage()
    , _buttonDefaultHoverImage()
    , _buttonDefaultActiveImage()
    , _buttonDefaultDisabledImage()
    , _buttonPrimaryNormalImage()
    , _buttonPrimaryHoverImage()
    , _buttonPrimaryActiveImage()
    , _buttonPrimaryDisabledImage()
    , _buttonWarningNormalImage()
    , _buttonWarningHoverImage()
    , _buttonWarningActiveImage()
    , _buttonWarningDisabledImage()
    , _buttonDangerNormalImage()
    , _buttonDangerHoverImage()
    , _buttonDangerActiveImage()
    , _buttonDangerDisabledImage() {

    std::cout << config.dump() << std::endl;

    if (setCurrent) {
        _current = this;
    }
}

raz::Image const& Theme::buttonDefaultNormalImage() const {
    return _buttonDefaultNormalImage;
}

raz::Image const& Theme::buttonDefaultHoverImage() const {
    return _buttonDefaultHoverImage;
}

raz::Image const& Theme::buttonDefaultActiveImage() const {
    return _buttonDefaultActiveImage;
}

raz::Image const& Theme::buttonDefaultDisabledImage() const {
    return _buttonDefaultDisabledImage;
}

raz::Image const& Theme::buttonPrimaryNormalImage() const {
    return _buttonPrimaryNormalImage;
}

raz::Image const& Theme::buttonPrimaryHoverImage() const {
    return _buttonPrimaryHoverImage;
}

raz::Image const& Theme::buttonPrimaryActiveImage() const {
    return _buttonPrimaryActiveImage;
}

raz::Image const& Theme::buttonPrimaryDisabledImage() const {
    return _buttonPrimaryDisabledImage;
}

raz::Image const& Theme::buttonWarningNormalImage() const {
    return _buttonWarningNormalImage;
}

raz::Image const& Theme::buttonWarningHoverImage() const {
    return _buttonWarningHoverImage;
}

raz::Image const& Theme::buttonWarningActiveImage() const {
    return _buttonWarningActiveImage;
}

raz::Image const& Theme::buttonWarningDisabledImage() const {
    return _buttonWarningDisabledImage;
}

raz::Image const& Theme::buttonDangerNormalImage() const {
    return _buttonDangerNormalImage;
}

raz::Image const& Theme::buttonDangerHoverImage() const {
    return _buttonDangerHoverImage;
}

raz::Image const& Theme::buttonDangerActiveImage() const {
    return _buttonDangerActiveImage;
}

raz::Image const& Theme::buttonDangerDisabledImage() const {
    return _buttonDangerDisabledImage;
}

void Theme::setCurrent(raz::Theme const& theme) {
    _current = &theme;
}

raz::Theme const& Theme::current() {
    assert(_current != nullptr);
    return *_current;
}

} /* namespace raz */