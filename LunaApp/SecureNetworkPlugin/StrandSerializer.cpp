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

    auto vector = builder.allocate<Array<RGB>>();
    auto vec = builder.allocate<RGB>(pixelCount);
    vector->set(vec, pixelCount);

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

        Eigen::Matrix<uint8_t, 4, 1> rgb8 = clampedRounded.cast<uint8_t>();

        vec[i].r = rgb8.x();
        vec[i].g = rgb8.y();
        vec[i].b = rgb8.z();
    }

    dst.data.set(vector);
}


void StrandSerializerWhite::serialize(luna::proto::Builder & builder, luna::proto::StrandData & dst)
{
    prism::ColorScalar error = 0;
    auto pixelCount = mStrand->size();

    constexpr prism::ColorScalar range = (1 << 16) - 1;

    using namespace luna::proto;

    auto vector = builder.allocate<Array<Scalar<uint16_t>>>();
    auto values = builder.allocate<Scalar<uint16_t>>(pixelCount);
    vector->set(values, pixelCount);

    for (size_t i = 0; i < pixelCount; ++i){
        auto pixel = (*mStrand)[i];

        prism::ColorScalar const corrected = pixel.color()[3] * range + error;
        prism::ColorScalar const clampedRounded = std::clamp<prism::ColorScalar>(corrected, 0, range);
        error = corrected - clampedRounded;
        values[i] = uint16_t(clampedRounded);
    }

    dst.data.set(vector);
}
