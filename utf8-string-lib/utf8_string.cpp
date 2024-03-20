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

#include "utf8_string.hpp"

// ---------------------------------------------------------------------------------------------------------------------
namespace utf8
{
    // -----------------------------------------------------------------------------------------------------------------
    std::ostream& operator<<(std::ostream& os, const ustring& ustr)
    {
        os << ustr.String;
        return os;
    }

    // -----------------------------------------------------------------------------------------------------------------
    std::istream& operator>>(std::istream& is, ustring& ustr)
    {
        // TODO: .............................................
        throw std::runtime_error("operator >> for utf8::ustring not implemented yet !");
    }

    // -----------------------------------------------------------------------------------------------------------------
    ustring::ustring()
    {
        Symbols_Info.reserve(100);
        String.reserve(100);
    }

    // -----------------------------------------------------------------------------------------------------------------
    ustring::ustring(const std::size_t bytes_reserve)
    {
        Symbols_Info.reserve(bytes_reserve);
        String.reserve(bytes_reserve);
    }

    // -----------------------------------------------------------------------------------------------------------------
    ustring::ustring(const char* default_string) : ustring(100)
    {
        Copy_With_Metadata_To_Internal_String(default_string);
    }

    // -----------------------------------------------------------------------------------------------------------------
    ustring::ustring(const char* default_string, const std::size_t bytes_reserve) : ustring(bytes_reserve)
    {
        Copy_With_Metadata_To_Internal_String(default_string);
    }

    // -----------------------------------------------------------------------------------------------------------------
    ustring::ustring(const std::basic_string<char>& default_string) : ustring(default_string.c_str(), default_string.size() * 2)
    { }

    // -----------------------------------------------------------------------------------------------------------------
    ustring::ustring(const std::basic_string_view<char>& default_string) : ustring(default_string.data(), default_string.size() *  2)
    { }

    // -----------------------------------------------------------------------------------------------------------------
    ustring::ustring(const ustring& other)
    {
        String = other.String;
        Symbols_Info = other.Symbols_Info;
    }

    // -----------------------------------------------------------------------------------------------------------------
    ustring::ustring(ustring&& other) noexcept
    {
        String = std::move(other.String);
        Symbols_Info = std::move(other.Symbols_Info);
    }

    // -----------------------------------------------------------------------------------------------------------------
    ustring& ustring::operator=(const ustring& other)
    {
        if (this != &other)
        {
            String = other.String;
            Symbols_Info = other.Symbols_Info;
        }

        return *this;
    }

    // -----------------------------------------------------------------------------------------------------------------
    ustring& ustring::operator=(ustring&& other) noexcept
    {
        String = std::move(other.String);
        Symbols_Info = std::move(other.Symbols_Info);

        return *this;
    }

    // -----------------------------------------------------------------------------------------------------------------
    bool ustring::operator==(const ustring& other) const
    {
        return (String == other.String);
    }

    // -----------------------------------------------------------------------------------------------------------------
    bool ustring::operator==(const char* other) const
    {
        return (String == other);
    }

    // -----------------------------------------------------------------------------------------------------------------
    bool ustring::operator==(const std::basic_string<char>& other) const
    {
        return (String == other);
    }

    // -----------------------------------------------------------------------------------------------------------------
    bool ustring::operator==(const std::basic_string_view<char>& other) const
    {
        return (String == other);
    }

    // -----------------------------------------------------------------------------------------------------------------
    bool ustring::operator!=(const ustring& other) const
    {
        return (String != other.String);
    }

    // -----------------------------------------------------------------------------------------------------------------
    bool ustring::operator!=(const char* other) const
    {
        return (String != other);
    }

    // -----------------------------------------------------------------------------------------------------------------
    bool ustring::operator!=(const std::basic_string<char>& other) const
    {
        return (String != other);
    }

    // -----------------------------------------------------------------------------------------------------------------
    bool ustring::operator!=(const std::basic_string_view<char>& other) const
    {
        return (String != other);
    }

    // -----------------------------------------------------------------------------------------------------------------
    void ustring::replace_char(std::basic_string_view<char> new_symbol, std::size_t idx)
    {
        SSymbol_Info& old_symbol_info{ Symbols_Info[idx] };
        std::size_t new_symbol_size{ new_symbol.size() };

        if (old_symbol_info.Symbol_Size != new_symbol_size)
        {
            std::size_t replace_position{ old_symbol_info.Symbol_Offset };
            std::size_t old_string_size{ String.size() };

            std::basic_string<char> new_string{ };
            new_string.resize(old_string_size + new_symbol_size - old_symbol_info.Symbol_Size); // calculate & resize new string size

            std::memcpy(new_string.data(), String.c_str(), replace_position); // copy bytes to a new string before idx
            std::memcpy((new_string.data() + replace_position), new_symbol.data(), new_symbol_size); // insert a new symbol by idx
            std::memcpy((new_string.data() + replace_position + new_symbol_size), (String.c_str() + replace_position + old_symbol_info.Symbol_Size), old_string_size - replace_position); // copy bytes after inserted symbol

            auto new_offset{ static_cast<std::ptrdiff_t>(new_symbol_size) - static_cast<std::ptrdiff_t>(old_symbol_info.Symbol_Size) };
            Recalculate_Symbols_Offset(idx + 1, new_offset);

            old_symbol_info.Symbol_Size = new_symbol_size;
            String = std::move(new_string);

            return;
        }

        std::memcpy(String.data() + old_symbol_info.Symbol_Offset, new_symbol.data(), old_symbol_info.Symbol_Size);
    }

    // -----------------------------------------------------------------------------------------------------------------
    std::basic_string<char>& ustring::get_str()
    {
        return String;
    }

    // -----------------------------------------------------------------------------------------------------------------
    const std::basic_string<char>& ustring::get_c_str() const
    {
        return String;
    }

    // -----------------------------------------------------------------------------------------------------------------
    std::uint8_t ustring::Get_Size_Of_Symbol(std::uint8_t symbol)
    {
        if (!((symbol ^ ONE_BYTE) >> 7))
        {
            return 1;
        }
        if (!((symbol ^ TWO_BYTE) >> 5))
        {
            return 2;
        }
        if (!((symbol ^ THREE_BYTE) >> 3))
        {
            return 3;
        }
        if (!((symbol ^ FOUR_BYTE) >> 1))
        {
            return 4;
        }

        return 0;
    }

    // -----------------------------------------------------------------------------------------------------------------
    void ustring::Recalculate_Symbols_Offset(std::size_t start_pos, std::ptrdiff_t new_offset)
    {
        for (std::size_t i{ start_pos }; i < Symbols_Info.size(); ++i)
        {
            Symbols_Info[i].Symbol_Offset += new_offset;
        }
    }

    // -----------------------------------------------------------------------------------------------------------------
    void ustring::Copy_With_Metadata_To_Internal_String(const char* default_string)
    {
        std::size_t next_symbol_position{}; // next symbol position in bytes
        for (std::size_t i{}; default_string[i] != '\0'; ++i)
        {
            String.push_back(default_string[i]);
            if (next_symbol_position == i) // if it`s beginning of a symbol
            {
                std::uint8_t symbol_size{ Get_Size_Of_Symbol(default_string[i]) };
                Symbols_Info.push_back(SSymbol_Info{ symbol_size, next_symbol_position });

                next_symbol_position += symbol_size;
            }
        }
    }
}