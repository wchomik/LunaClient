#pragma once

#include "Strand.hpp"

namespace luna::interface {
    class Provider
    {
    public:
        virtual ~Provider() = default;
        virtual void getData(Strand & strand) = 0;
        virtual void update() = 0;
    };
}
