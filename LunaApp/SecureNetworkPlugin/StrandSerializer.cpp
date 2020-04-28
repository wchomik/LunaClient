#include "StrandSerializer.hpp"

#include <limits>
#include <QDebug>

StrandSerializer::StrandSerializer(std::unique_ptr<luna::interface::Strand> && strand) :
    mStrand(std::move(strand))
{}

StrandSerializer::~StrandSerializer() = default;

template<typename T>
StrandSerializerRGB<T>::StrandSerializerRGB(std::unique_ptr<luna::interface::Strand> && strand, prism::RGBColorSpace colorSpace, std::vector<Channel> channels) :
    StrandSerializer(std::move(strand)),
	mChannels(std::move(channels)),
    mColorSpace(colorSpace)
{}

template<typename T>
void StrandSerializerRGB<T>::serialize(luna::proto::Builder & builder, luna::proto::StrandData & dst)
{
    prism::Coefficients error = prism::Coefficients::Zero();
    auto pixelCount = mStrand->size();

    constexpr prism::ColorScalar range = std::numeric_limits<T>::max();

    using namespace luna::proto;

	auto const byteSize = pixelCount * mChannels.size() * sizeof(T);
    auto vec = builder.allocate<std::byte>(byteSize);
    dst.rawBytes.set(vec, byteSize);

	auto dest = reinterpret_cast<T *>(vec);
    
    auto transformation = prism::RGBColorSpaceTransformation(mColorSpace);

    for (size_t i = 0; i < pixelCount; ++i){
        auto pixel = (*mStrand)[i];
        auto rgb = transformation.transform(pixel.color());
        auto const maximum = rgb.maxCoeff();
        if (maximum > 1) {
            rgb /= maximum;
        }
        prism::Coefficients const corrected = rgb * range + error;
        prism::Coefficients const clampedRounded = corrected.array().max(0).min(range).round().matrix();
        error = corrected - clampedRounded;

		Eigen::Matrix<T, 4, 1> casted = clampedRounded.cast<T>();
		for (auto channel : mChannels) {
			*dest = casted[channel];
			++dest;
		}
    }
}

template class StrandSerializerRGB<uint8_t>;

template class StrandSerializerRGB<uint16_t>;

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
