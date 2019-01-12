#pragma once

#include <vector>

class Noise
{
public:
    explicit Noise();
    float at(float x, float y, float z) const;
    template<typename T>
    float at(T p)
    {
        return at(p[0], p[1], p[2]);
    }
private:
    std::vector<unsigned> mP;
};
