#pragma once

#include <luna/interface/Strand.hpp>
#include <prism/Prism.hpp>
#include <luna/proto/SetColor.hpp>
#include <luna/proto/Builder.hpp>

#include <memory>

struct StrandSerializer
{
    explicit StrandSerializer(std::unique_ptr<luna::interface::Strand> && strand);
    virtual ~StrandSerializer();
    virtual void serialize(luna::proto::Builder & builder, luna::proto::StrandData & dst) = 0;
    luna::interface::Strand * strand() { return mStrand.get(); }
protected:
    std::unique_ptr<luna::interface::Strand> mStrand;
};

struct StrandSerializerRGB : StrandSerializer
{
    explicit StrandSerializerRGB(std::unique_ptr<luna::interface::Strand> && strand, prism::RGBColorSpace colorSpace);
    void serialize(luna::proto::Builder & builder, luna::proto::StrandData & dst) override;
private:
    prism::RGBColorSpace mColorSpace;
};

struct StrandSerializerWhite : StrandSerializer
{
    using StrandSerializer::StrandSerializer;
    void serialize(luna::proto::Builder & builder, luna::proto::StrandData & dst) override;
};
