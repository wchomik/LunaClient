#pragma once

#include <cstdint>

namespace luna::interface {
    class Strand
    {
    public:
        size_t size() const { return mColors.size(); }
        Pixel pixelAt(size_t index) { return Pixel(this, index); }
    private:
        class Pixel
        {
        public:
            explicit Pixel(Strand * parent, size_t index) :
                mParent(parent),
                mIndex(index)
            {}

            size_t index() const { return mIndex; }
            Color color() const { return mParent->mColors[index]; }
            void color(Color const & value) { mParent->mColors[index] = value; }
            Eigen::Vector3f position() const {
                auto t = static_cast<float>(mIndex) / static_cast<float>(mParent->mColors.size()); 
                return mParent->mBeginPosition + (mParent->mEndPosition - mParent->mBeginPosition) * t; 
            }
        private:
            Strand * const mParent;
            size_t const mIndex;
        };

        std::vector<Color> mColors;
        Eigen::Vector3f mBeginPosition;
        Eigen::Vector3f mEndPosition;
    };
}
