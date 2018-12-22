#include "StrandSerializer.h"

#include <bitset>

StrandSerializer::~StrandSerializer() = default;

static size_t countSet(lunacore::ColorChannels channels)
{
    return std::bitset<4>(channels).count();
}

luna::proto::StrandDataBuilder StrandSerializerRGB::serialize(flatbuffers::FlatBufferBuilder & builder, lunacore::Strand const & strand) const
{
    lunacore::Color const * pixels = strand.pixels();
    lunacore::Color error = lunacore::Color::Zero();
    size_t const pixelCount = strand.config().count;

    constexpr lunacore::ColorScalar range = (1 << 8) - 1;

    using namespace luna::proto;


    std::vector<RGB> rgb;

    for (size_t i = 0; i < pixelCount; ++i){
        lunacore::Color const corrected = pixels[i] * range + error;
        lunacore::Color const clampedRounded = corrected.array().max(0).min(range).round().matrix();
        error = corrected - clampedRounded;

        Eigen::Matrix<uint8_t, 4, 1> color = clampedRounded.cast<uint8_t>();

        rgb.emplace_back(color.x(), color.y(), color.z());
    }

    auto rgbdata = CreateRGBDataDirect(builder, &rgb);

    StrandDataBuilder sdb(builder);
    sdb.add_data(rgbdata.Union());
    sdb.add_data_type(RawData_RGBData);

    return sdb;
}
