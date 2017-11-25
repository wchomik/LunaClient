#ifndef LUNAPROVIDER_H
#define LUNAPROVIDER_H

#include <vector>
namespace luna {
    class Provider
    {
    public:
        virtual ~Provider();
        virtual void getData(std::vector<class Strand *> & strands) = 0;
    };
}

#endif // LUNAPROVIDER_H
