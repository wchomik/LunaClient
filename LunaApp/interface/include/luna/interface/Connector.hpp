#pragma once

#include "Strand.hpp"

#include <vector>

namespace luna::interface {
    class Connector {
    public:
        virtual ~Connector() = default;
        virtual void update() = 0;
        virtual std::vector<Strand *> getStrands() const = 0;
    };
}
