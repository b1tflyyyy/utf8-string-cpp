// MIT License

// Copyright (c) 2024 Andrii

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <cstdint>
#include <cstddef>
#include <array>
#include <stdexcept>

#define ONE_BYTE   0b0000'0000 // first bit 0
#define TWO_BYTE   0b1100'0000 // first three bits 110
#define THREE_BYTE 0b1110'0000 // first four bits 1110
#define FOUR_BYTE  0b1111'0000 // first four bits 11110

namespace utf8
{
    class ustring
    {
    public:
        typedef std::array<char, 5> uchar;

    public:
        friend std::ostream& operator<<(std::ostream& os, const ustring& ustr);
        friend std::istream& operator>>(std::istream& is, ustring& ustr);

    public:
        ustring();
        explicit ustring(const std::size_t bytes_reserve);
        explicit ustring(const char* default_string);
        explicit ustring(const char* default_string, const std::size_t bytes_reserve);
        explicit ustring(const std::basic_string<char>& default_string);
        explicit ustring(const std::basic_string_view<char>& default_string);

        constexpr ~ustring() = default;

        explicit ustring(const ustring& other);
        explicit ustring(ustring&& other) noexcept;

        ustring& operator=(const ustring& other);
        ustring& operator=(ustring&& other) noexcept;

        bool operator==(const ustring& other) const;
        bool operator==(const char* other) const;
        bool operator==(const std::basic_string<char>& other) const;
        bool operator==(const std::basic_string_view<char>& other) const;

        bool operator!=(const ustring& other) const;
        bool operator!=(const char* other) const;
        bool operator!=(const std::basic_string<char>& other) const;
        bool operator!=(const std::basic_string_view<char>& other) const;

        const ustring::uchar operator[](std::size_t index) const;

        void replace_char(std::basic_string_view<char> new_symbol, std::size_t idx);

        std::basic_string<char>& get_str();
        [[nodiscard]] const std::basic_string<char>& get_c_str() const;

    private:
        std::uint8_t Get_Size_Of_Symbol(std::uint8_t symbol);
        void Recalculate_Symbols_Offset(std::size_t start_pos, std::ptrdiff_t new_offset);
        void Copy_With_Metadata_To_Internal_String(const char* default_string);

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