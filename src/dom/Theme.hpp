#pragma once

#include <nlohmann/json.hpp>
#include "Editor/Components/DOM/Base.hpp"
#include "Editor/Components/DOM/Image.hpp"

namespace raz {

class Theme {
private:
    raz::Image _buttonDefaultNormalImage;
    raz::Image _buttonDefaultHoverImage;
    raz::Image _buttonDefaultActiveImage;
    raz::Image _buttonDefaultDisabledImage;
    raz::Image _buttonPrimaryNormalImage;
    raz::Image _buttonPrimaryHoverImage;
    raz::Image _buttonPrimaryActiveImage;
    raz::Image _buttonPrimaryDisabledImage;
    raz::Image _buttonWarningNormalImage;
    raz::Image _buttonWarningHoverImage;
    raz::Image _buttonWarningActiveImage;
    raz::Image _buttonWarningDisabledImage;
    raz::Image _buttonDangerNormalImage;
    raz::Image _buttonDangerHoverImage;
    raz::Image _buttonDangerActiveImage;
    raz::Image _buttonDangerDisabledImage;
    static raz::Theme const* _current;
public:
    Theme(raz::Theme const&) = delete;
    Theme(raz::Theme &&) = delete;
    raz::Theme& operator=(raz::Theme const&) = delete;
    raz::Theme& operator=(raz::Theme &&) = delete;
    ~Theme();
    Theme(
        nlohmann::json const& config,
        raz::Image const& atlas,
        bool setCurrent = false
    );
    raz::Image const& buttonDefaultNormalImage() const;
    raz::Image const& buttonDefaultHoverImage() const;
    raz::Image const& buttonDefaultActiveImage() const;
    raz::Image const& buttonDefaultDisabledImage() const;
    raz::Image const& buttonPrimaryNormalImage() const;
    raz::Image const& buttonPrimaryHoverImage() const;
    raz::Image const& buttonPrimaryActiveImage() const;
    raz::Image const& buttonPrimaryDisabledImage() const;
    raz::Image const& buttonWarningNormalImage() const;
    raz::Image const& buttonWarningHoverImage() const;
    raz::Image const& buttonWarningActiveImage() const;
    raz::Image const& buttonWarningDisabledImage() const;
    raz::Image const& buttonDangerNormalImage() const;
    raz::Image const& buttonDangerHoverImage() const;
    raz::Image const& buttonDangerActiveImage() const;
    raz::Image const& buttonDangerDisabledImage() const;
    static void setCurrent(raz::Theme const& theme);
    static raz::Theme const& current();
};

} /* namespace raz */