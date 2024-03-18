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
    }

    // -----------------------------------------------------------------------------------------------------------------
    constexpr ustring::ustring()
    {
        Symbols_Info.reserve(100);
        String.reserve(100);
    }

    // -----------------------------------------------------------------------------------------------------------------
    ustring::ustring(const char* utf8_str)
    {
        Symbols_Info.reserve(100);
        String.reserve(100);

        // TODO: redo this part
        std::size_t next_symbol_position{}; // next symbol position in bytes
        for (std::size_t i{}; utf8_str[i] != '\0'; ++i)
        {
            String.push_back(utf8_str[i]);
            if (next_symbol_position == i) // if it`s beginning of a symbol
            {
                std::uint8_t symbol_size{ Get_Size_Of_Symbol(utf8_str[i]) };
                Symbols_Info.push_back(SSymbol_Info{ symbol_size, next_symbol_position });

                next_symbol_position += symbol_size;
            }
        }
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
}