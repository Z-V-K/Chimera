#pragma once

inline constexpr DWORD FNV1A32Lower(std::string_view text)
{
    constexpr DWORD FNV_OFFSET_BASIS = 0x811C9DC5;
    constexpr DWORD FNV_PRIME = 0x01000193;

    auto toLower = [](char c) -> char {
        if (c >= 'A' && c <= 'Z')
            return c + ' ';
        else
            return c;
    };

    DWORD hash = FNV_OFFSET_BASIS;
    for (const auto& c : text)
    {
        hash = hash ^ toLower(c);
        hash = hash * FNV_PRIME;
    }
    return hash;
}

template <typename Type>
class EncryptedBuffer
{
    BYTE& GetIsFilled() const noexcept
    {
        return *(BYTE*)((uintptr_t)this + 0x0);
    }

    BYTE& GetLengthXor32() const noexcept
    {
        return *(BYTE*)((uintptr_t)this + 0x1);
    }

    BYTE& GetLengthXor8() const noexcept
    {
        return *(BYTE*)((uintptr_t)this + 0x2);
    }

    BYTE* GetKeyArray() const noexcept
    {
        if constexpr (sizeof Type % 4 == 0)
        {
            return (BYTE*)((uintptr_t)this + 0x8);
        }

        return (BYTE*)((uintptr_t)this + 0x3);
    }
    BYTE& GetIndex() const noexcept
    { 
        if constexpr (sizeof Type % 4 == 0)
        {
            return *(BYTE*)((uintptr_t)this + 0x10);
        }
        return *(BYTE*)((uintptr_t)this + 0x4);
    }

    Type* GetValuesArray() const noexcept
    {
        if constexpr (sizeof Type % 4 == 0)
            return (Type*)((uintptr_t)this + 0x18);

        return (Type*)((uintptr_t)this + 0x5);
    }
public:
    __forceinline void ZeroCurrentValue() const noexcept
    {
        auto array = GetValuesArray();

        array[GetIndex()] = 0x0 ^ ~GetKeyArray()[0];
    }

    __forceinline Type Decrypt() const noexcept
    {
        auto result = GetValuesArray()[GetIndex()];

        if (const auto& xor32 = GetLengthXor32())
        {
            for (unsigned char i = 0; i < xor32; ++i)
            {
                reinterpret_cast<uintptr_t*>(&result)[i] ^= ~reinterpret_cast<uintptr_t*>(GetKeyArray())[i];
            }
        }
        else if (const auto& xor8 = GetLengthXor8())
        {
            for (unsigned char i = sizeof Type - xor8; i < sizeof Type; ++i)
            {
                reinterpret_cast<PBYTE>(&result)[i] ^= ~GetKeyArray()[i];
            }
        }
        return result;
    }
};