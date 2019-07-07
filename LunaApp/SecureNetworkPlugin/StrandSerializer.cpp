#include "StrandSerializer.hpp"

StrandSerializer::StrandSerializer(std::unique_ptr<luna::interface::Strand> && strand) :
    mStrand(std::move(strand))
{}

StrandSerializer::~StrandSerializer() = default;


StrandSerializerRGB::StrandSerializerRGB(std::unique_ptr<luna::interface::Strand> && strand, prism::RGBColorSpace colorSpace) :
    StrandSerializer(std::move(strand)),
    mColorSpace(colorSpace)
{}

void StrandSerializerRGB::serialize(luna::proto::Builder & builder, luna::proto::StrandData & dst)
{
    prism::Coefficients error = prism::Coefficients::Zero();
    auto pixelCount = mStrand->size();

    constexpr prism::ColorScalar range = (1 << 8) - 1;

    using namespace luna::proto;

    auto vec = builder.allocate<std::byte>(pixelCount * 3);
    dst.rawBytes.set(vec, pixelCount * 3);

    auto rgbDest = reinterpret_cast<Eigen::Matrix<uint8_t, 3, 1> *>(vec);

    for (size_t i = 0; i < pixelCount; ++i){
        auto pixel = (*mStrand)[i];
        auto rgb = mColorSpace.transform(pixel.color(), prism::RenderingIntent::RelativeColorimetric);
        auto const maximum = rgb.maxCoeff();
        if (maximum > 1) {
            rgb /= maximum;
        }
        prism::Coefficients const corrected = rgb * range + error;
        prism::Coefficients const clampedRounded = corrected.array().max(0).min(range).round().matrix();
        error = corrected - clampedRounded;

        rgbDest[i] = clampedRounded.cast<uint8_t>().head<3>();
    }
}


void StrandSerializerWhite::serialize(luna::proto::Builder & builder, luna::proto::StrandData & dst)
{
    prism::ColorScalar error = 0;
    auto pixelCount = mStrand->size();

    constexpr prism::ColorScalar range = (1 << 16) - 1;

    using namespace luna::proto;

    auto vec = builder.allocate<std::byte>(pixelCount * 2);
    dst.rawBytes.set(vec, pixelCount * 2);
    auto values = reinterpret_cast<Scalar<uint16_t> *>(vec);

    for (size_t i = 0; i < pixelCount; ++i){
        auto pixel = (*mStrand)[i];

        prism::ColorScalar const corrected = pixel.color()[3] * range + error;
        prism::ColorScalar const clampedRounded = std::clamp<prism::ColorScalar>(corrected, 0, range);
        error = corrected - clampedRounded;
        values[i] = uint16_t(clampedRounded);
    }
}
