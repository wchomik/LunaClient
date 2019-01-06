#pragma once

#include "Strand.hpp"

namespace luna::interface {
    class Provider
    {
    public:
        virtual ~Provider() = default;
        virtual void getRGBData(Strand & strand) {}
        virtual void getRGBWData(Strand & strand) {}
        virtual void getGrayScaleData(Strand & strand) {}
    };
}
