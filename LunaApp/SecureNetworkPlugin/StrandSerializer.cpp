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
        prism::Coefficients const corrected = rgb.values * range + error;
        prism::Coefficients const clampedRounded = corrected.array().max(0).min(range).round().matrix();
        error = corrected - clampedRounded;

        Eigen::Matrix<uint8_t, 4, 1> rgb8 = clampedRounded.cast<uint8_t>();

        vec[i].r = rgb8.x();
        vec[i].g = rgb8.y();
        vec[i].b = rgb8.z();
    }

    dst.data.set(vector);
}
