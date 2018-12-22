#ifndef STRANDSERIALIZER_H
#define STRANDSERIALIZER_H

#include <lunacore/strand.h>
#include <luna/ByteStream.hpp>
#include <luna/proto/SetColor_generated.h>

class StrandSerializer
{
public:
    virtual ~StrandSerializer();
    virtual luna::proto::StrandDataBuilder serialize(flatbuffers::FlatBufferBuilder & builder, lunacore::Strand const & strand) const = 0;
};

class StrandSerializerRGB : public StrandSerializer
{
public:
    luna::proto::StrandDataBuilder serialize(flatbuffers::FlatBufferBuilder & builder, lunacore::Strand const & strand) const override;
};


#endif // STRANDSERIALIZER_H
