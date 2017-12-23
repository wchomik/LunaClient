#ifndef NOISE_H
#define NOISE_H

#include <vector>

class Noise
{
public:
    Noise();
    float at(float x, float y, float z) const;
private:
    std::vector<unsigned> mP;
};

#endif // NOISE_H
