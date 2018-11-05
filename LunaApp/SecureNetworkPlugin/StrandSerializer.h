#ifndef STRANDSERIALIZER_H
#define STRANDSERIALIZER_H

#include <lunacore/strand.h>
#include <luna/ByteStream.hpp>

class StrandSerializer
{
public:
    virtual ~StrandSerializer();
    virtual void serialize(lunacore::Strand const & strand, luna::ByteStream & stream) const = 0;
};

class StrandSerializer8Bit : public StrandSerializer
{
public:
    void serialize(lunacore::Strand const & strand, luna::ByteStream & stream) const override;
};

class StrandSerializer16Bit : public StrandSerializer
{
public:
    void serialize(lunacore::Strand const & strand, luna::ByteStream & stream) const override;
};

#endif // STRANDSERIALIZER_H
