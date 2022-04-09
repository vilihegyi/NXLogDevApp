#include <string.h>

#include "Tlv.h"

Tlv::Tlv(TlvType type) : mType(type)
{
    Initialize(0, 0);
}

Tlv::Tlv(TlvType type, bool value) : mType(type)
{
    Initialize(&value, sizeof(bool));
}

Tlv::Tlv(TlvType type, char value) : mType(type)
{
    Initialize(&value, sizeof(char));
}

Tlv::Tlv(TlvType type, short value) : mType(type)
{
    Initialize(&value, sizeof(short));
}

Tlv::Tlv(TlvType type, int value) : mType(type)
{
    Initialize(&value, sizeof(int));
}

Tlv::Tlv(TlvType type, long value) : mType(type)
{
    Initialize(&value, sizeof(long));
}

Tlv::Tlv(TlvType type, long long value) : mType(type)
{
    Initialize(&value, sizeof(long long));
}

Tlv::Tlv(TlvType type, float value) : mType(type)
{
    Initialize(&value, sizeof(float));
}

Tlv::Tlv(TlvType type, double value) : mType(type)
{
    Initialize(&value, sizeof(double));
}

Tlv::Tlv(TlvType type, std::string value) : mType(type)
{
    Initialize(value.c_str(), value.size() + 1);
}

Tlv::~Tlv()
{
    delete[] mValue;
}

void Tlv::Initialize(const void *value, int length)
{
    mLength = length;
    mValue = new unsigned char[length];
    memcpy(mValue, value, length);
}

TlvType Tlv::GetType() const
{
    return mType;
}

size_t Tlv::GetLength() const
{
    return mLength;
}

unsigned char *Tlv::GetValue() const
{
    return mValue;
}