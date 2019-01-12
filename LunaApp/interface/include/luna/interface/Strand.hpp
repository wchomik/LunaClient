#pragma once

#include <prism/Prism.hpp>

#include <cstdint>
#include <vector>

namespace luna::interface {
    class Strand
    {
    private:
        class Pixel
        {
        public:
            explicit Pixel(Strand * parent, size_t index) :
                mParent(parent),
                mIndex(index)
            {}

            size_t index() const { return mIndex; }
            prism::CieXYZ color() const { return mParent->mColors[mIndex]; }
            void color(prism::CieXYZ  const & value) { mParent->mColors[mIndex] = value; }
            Eigen::Vector3f position() const {
                auto t = static_cast<float>(mIndex) / static_cast<float>(mParent->mColors.size());
                return mParent->mBeginPosition + (mParent->mEndPosition - mParent->mBeginPosition) * t;
            }
        private:
            Strand * const mParent;
            size_t const mIndex;
        };
    public:
        explicit Strand(size_t size, Eigen::Vector3f begin, Eigen::Vector3f end) :
            mColors(size),
            mBeginPosition(begin),
            mEndPosition(end)
        {}

        size_t size() const { return mColors.size(); }
        Pixel operator[](size_t index) { return Pixel(this, index); }
        
        Eigen::Vector3f beginPosition() const { return mBeginPosition; }
        Eigen::Vector3f endPosition() const { return mEndPosition; }
    private:
        std::vector<prism::CieXYZ> mColors;
        Eigen::Vector3f mBeginPosition;
        Eigen::Vector3f mEndPosition;
    };
}
