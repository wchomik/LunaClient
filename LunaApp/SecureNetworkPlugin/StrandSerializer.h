#ifndef STRANDSERIALIZER_H
#define STRANDSERIALIZER_H

#include <lunacore/strand.h>
#include <luna/ByteStream.hpp>
#include <luna/proto/SetColor.hpp>
#include <luna/proto/Builder.hpp>


class StrandSerializer
{
public:
    virtual ~StrandSerializer();
    virtual void serialize(luna::proto::Builder & builder, luna::proto::StrandData& dst, lunacore::Strand const & strand) const = 0;
};

class StrandSerializerRGB : public StrandSerializer
{
public:
    void serialize(luna::proto::Builder & builder, luna::proto::StrandData& dst, lunacore::Strand const & strand) const override;
};


#endif // STRANDSERIALIZER_H
