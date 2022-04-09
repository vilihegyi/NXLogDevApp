#ifndef TLV_H
#define TLV_H

#include <string>

enum TlvType
{
    Null = 0,
    Bool = 1,
    Char = 2,
    Short = 3,
    Int = 4,
    Long = 5,
    LongLong = 6,
    Float = 7,
    Double = 8,
    CharP = 9,
    String = 10
};

class Tlv
{
public:
    // Construct a Type-Length-Value object
    // for each primitive and std::string
    Tlv(TlvType);
    Tlv(TlvType, bool);
    Tlv(TlvType, char);
    Tlv(TlvType, short);
    Tlv(TlvType, int);
    Tlv(TlvType, long);
    Tlv(TlvType, long long);
    Tlv(TlvType, float);
    Tlv(TlvType, double);
    Tlv(TlvType, char*);
    Tlv(TlvType, std::string);
    ~Tlv();

    TlvType GetType() const;
    size_t GetLength() const;
    unsigned char *GetValue() const;

private:
    void Initialize(const void *, int);

private:
    TlvType mType;
    size_t mLength;
    unsigned char *mValue;
};

#endif // TLV_H