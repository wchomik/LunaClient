#include "StrandSerializer.h"

#include <bitset>

StrandSerializer::~StrandSerializer() = default;

static size_t countSet(lunacore::ColorChannels channels)
{
    return std::bitset<4>(channels).count();
}


void StrandSerializer8Bit::serialize(lunacore::Strand const & strand, luna::ByteStream & stream) const
{
    lunacore::Color const * pixels = strand.pixels();
    lunacore::Color error = lunacore::Color::Zero();
    lunacore::ColorChannels channels = strand.config().colorChannels;
    size_t const pixelCount = strand.config().count;

    constexpr lunacore::ColorScalar range = (1 << 8) - 1;

    stream << static_cast<uint16_t>(pixelCount * countSet(channels));

    for (size_t i = 0; i < pixelCount; ++i){
        lunacore::Color const corrected = pixels[i] * range + error;
        lunacore::Color const clampedRounded = corrected.array().max(0).min(range).round().matrix();
        error = corrected - clampedRounded;

        for (int j = 0; j < 4; ++j) {
            if (0 != ((1 << j) & channels)) {
                stream << static_cast<uint8_t>(clampedRounded(j));
            }
        }
    }
}

void StrandSerializer16Bit::serialize(lunacore::Strand const & strand, luna::ByteStream & stream) const
{
    lunacore::Color const * pixels = strand.pixels();
    lunacore::ColorChannels channels = strand.config().colorChannels;
    size_t const pixelCount = strand.config().count;

    constexpr lunacore::ColorScalar range = (1 << 16) - 1;

    stream << static_cast<uint16_t>(pixelCount * countSet(channels));

    for (size_t i = 0; i < pixelCount; ++i){
        lunacore::Color const corrected = pixels[i] * range;
        lunacore::Color const clampedRounded = corrected.array().max(0).min(range).round().matrix();

        for (int j = 0; j < 4; ++j) {
            if (0 != ((1 << j) & channels)) {
                stream << static_cast<uint8_t>(clampedRounded(j));
            }
        }
    }
}
