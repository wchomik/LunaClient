#pragma once

#include "Application.hpp"

#include <string>

namespace luna::interface {
    class Plugin  {
    public:
        virtual ~Plugin() = default;

        virtual std::string name() const = 0;
        virtual void initialize(Application * application) = 0;
        virtual void finalize(Application * application) = 0;
    };
}

Q_DECLARE_INTERFACE(luna::interface::Plugin, "org.luna.plugin")
