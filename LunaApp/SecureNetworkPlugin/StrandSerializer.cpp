#include "StrandSerializer.h"

#include <bitset>

StrandSerializer::~StrandSerializer() = default;

static size_t countSet(lunacore::ColorChannels channels)
{
    return std::bitset<4>(channels).count();
}

void StrandSerializerRGB::serialize(luna::proto::Builder & builder, luna::proto::StrandData& dst, lunacore::Strand const & strand) const
{
    lunacore::Color const * pixels = strand.pixels();
    lunacore::Color error = lunacore::Color::Zero();
    size_t const pixelCount = strand.config().count;

    constexpr lunacore::ColorScalar range = (1 << 8) - 1;

    using namespace luna::proto;


    auto vector = builder.allocate<Array<RGB>>();
    auto vec = builder.allocate<RGB>(pixelCount);
    vector->set(vec, pixelCount);

    for (size_t i = 0; i < pixelCount; ++i){
        lunacore::Color const corrected = pixels[i] * range + error;
        lunacore::Color const clampedRounded = corrected.array().max(0).min(range).round().matrix();
        error = corrected - clampedRounded;

        Eigen::Matrix<uint8_t, 4, 1> color = clampedRounded.cast<uint8_t>();

        vec[i].r = color.x();
        vec[i].g = color.y();
        vec[i].b = color.z();
    }

    dst.data.set(vector);
}
