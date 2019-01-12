#include "Noise.hpp"

#include <random>
#include <cmath>
#include <algorithm>
#include <chrono>

static float fade(float t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

static float grad(unsigned hash, float x, float y, float z)
{
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

static float lerp(float t, float a, float b) 
{
    return a + t * (b - a);
}

static void cube(float * v, unsigned * integral)
{
    float t = std::floor(*v);
    *integral = static_cast<unsigned>(static_cast<int>(t)) & 0xFF;
    *v = *v - t;
}

Noise::Noise()
{
    constexpr unsigned c = 256;
    mP.resize(c * 2);
    for (unsigned i = 0; i < c; ++i) {
        mP[i] = i;
    }

    std::random_device rd;
    std::seed_seq seed = {
        rd(),
        static_cast<uint32_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count())
    };
    std::default_random_engine re(seed);
    std::shuffle(mP.begin(), mP.begin() + c, re);
    for (unsigned i = 0; i < c; ++i) {
        mP[i + c] = mP[i];
    }
}

float Noise::at(float x, float y, float z) const
{
    unsigned X, Y, Z;
    cube(&x, &X);
    cube(&y, &Y);
    cube(&z, &Z);

    float u, v, w;
    u = fade(x);
    v = fade(y);
    w = fade(z);

    unsigned A  = mP[X] + Y;
    unsigned AA = mP[A] + Z;
    unsigned AB = mP[A + 1] + Z;
    unsigned B  = mP[X + 1] + Y;
    unsigned BA = mP[B] + Z;
    unsigned BB = mP[B + 1] + Z;

    return lerp(w, lerp(v, lerp(u, grad(mP[AA], x, y, z),
                                   grad(mP[BA], x - 1, y, z)),
                           lerp(u, grad(mP[AB], x, y - 1, z),
                                   grad(mP[BB], x - 1, y - 1, z))),
                   lerp(v, lerp(u, grad(mP[AA + 1], x, y, z - 1),
                                   grad(mP[BA + 1], x - 1, y, z - 1)),
                           lerp(u, grad(mP[AB + 1], x, y - 1, z - 1),
                                   grad(mP[BB + 1], x - 1, y - 1, z - 1))));
}
