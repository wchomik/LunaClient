#ifndef LUNAPROVIDER_H
#define LUNAPROVIDER_H

#include <vector>
#include "lunacore_global.h"

namespace lunacore {
    class LUNACORESHARED_EXPORT Provider
    {
    public:
        virtual ~Provider();
        virtual void getData(std::vector<class Strand *> & strands) = 0;
    };
}

#endif // LUNAPROVIDER_H
