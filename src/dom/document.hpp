#pragma once

#include <libext/ui/app.hpp>
#include <libext/dom/element.hpp>

namespace ext::dom {

class document final : public ext::dom::element {
private:
    bool _keep_update;
public:
    document(ext::dom::document const&) = delete;
    document(ext::dom::document &&) = delete;
    ext::dom::document& operator=(ext::dom::document const&) = delete;
    ext::dom::document& operator=(ext::dom::document &&) = delete;
    document();
    void event(ext::gfx::context const&, ext::ui::event const&);
    void update(ext::gfx::context const&);
    void render(ext::gfx::context&);
};

} /* namespace ext::dom */