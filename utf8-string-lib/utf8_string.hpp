#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <cstdint>
#include <cstddef>

#define ONE_BYTE   0b0000'0000 // first bit 0
#define TWO_BYTE   0b1100'0000 // first three bits 110
#define THREE_BYTE 0b1110'0000 // first four bits 1110
#define FOUR_BYTE  0b1111'0000 // first four bits 11110

namespace utf8
{
    class ustring
    {
    public:
        friend std::ostream& operator<<(std::ostream& os, const ustring& ustr);
        friend std::istream& operator>>(std::istream& is, ustring& ustr);

    public:
        constexpr ustring();
        explicit ustring(const char* utf8_str);

        void replace_char(std::basic_string_view<char> new_symbol, std::size_t idx);
        std::basic_string<char>& get_str();

    private:
        std::uint8_t Get_Size_Of_Symbol(std::uint8_t symbol);
        void Recalculate_Symbols_Offset(std::size_t start_pos, std::ptrdiff_t new_offset);

    private:
        struct SSymbol_Info
        {
            std::size_t Symbol_Size;
            std::size_t Symbol_Offset;
        };

        std::vector<SSymbol_Info> Symbols_Info;
        std::basic_string<char> String;
    };
}