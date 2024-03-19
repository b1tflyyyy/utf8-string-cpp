#include <gtest/gtest.h>

#include <utf8_string.hpp>

// ---------------------------------------------------------------------------------------------------------------------
TEST(utf8_string, replace_char_case_1)
{
    utf8::ustring ustr1{ "привет" };
    ustr1.replace_char("g", 0);
    ASSERT_EQ(ustr1.get_str(), "gривет");

    utf8::ustring ustr2{ "😊 привет" };
    ustr2.replace_char("1", 0);
    ASSERT_EQ(ustr2.get_str(), "1 привет");

    utf8::ustring ustr3{ "ᩂж᧭s丒ы" };
    ustr3.replace_char("ы", 2);
    ASSERT_EQ(ustr3.get_str(), "ᩂжыs丒ы");

    utf8::ustring ustr4{ "Привет, мир!" };
    ustr4.replace_char("g", 8);
    ASSERT_EQ(ustr4.get_str(), "Привет, gир!");

    utf8::ustring ustr5{ "123456" };
    ustr5.replace_char(" ", 3);
    ASSERT_EQ(ustr5.get_str(), "123 56");

    utf8::ustring ustr6{ "😊 привет" };
    ustr6.replace_char("!", 0);
    ASSERT_EQ(ustr6.get_str(), "! привет");
}

// ---------------------------------------------------------------------------------------------------------------------
TEST(utf8_string, replace_char_case_2)
{
    utf8::ustring ustr{ "gжᩂ😊" };

    ustr.replace_char("п", 0);
    ASSERT_EQ(ustr.get_str(), "пжᩂ😊");

    ustr.replace_char("😊", 0);
    ASSERT_EQ(ustr.get_str(), "😊жᩂ😊");

    ustr.replace_char("s", 0);
    ASSERT_EQ(ustr.get_str(), "sжᩂ😊");
}

// ---------------------------------------------------------------------------------------------------------------------
TEST(utf8_string, replace_char_case_3)
{
    utf8::ustring ustr{ "привет" };

    ustr.replace_char("s", 0);
    ustr.replace_char("g", 0);
    ustr.replace_char("п", 0);
    ustr.replace_char("s", 3);
    ustr.replace_char("g", 4);
    ustr.replace_char("п", 3);
    ustr.replace_char("\xf0\x92\x8d\x87", 2);
    ustr.replace_char("g", 2);
    ustr.replace_char("مرحبا", 2);

    ASSERT_EQ(ustr.get_str(), "прمرحباпgт");
}

// ---------------------------------------------------------------------------------------------------------------------
TEST(utf8_string, ctors)
{
    // ----------------------------- const char* PART -----------------------------
    const char* c_str{ "привет" };

    utf8::ustring ustr_from_c_str{ c_str };
    ASSERT_EQ(c_str, ustr_from_c_str.get_c_str());

    ustr_from_c_str.replace_char("g", 0);
    ASSERT_NE(c_str, ustr_from_c_str.get_c_str());


    // ----------------------------- std::string PART -----------------------------
    std::string cpp_str{ "пока" };

    utf8::ustring ustr_from_cpp_str{ cpp_str };
    ASSERT_EQ(cpp_str, ustr_from_cpp_str.get_c_str());

    ustr_from_cpp_str.replace_char("h", 0);
    ASSERT_NE(cpp_str, ustr_from_cpp_str.get_c_str());


    // ----------------------------- std::string_view PART -----------------------------
    std::string_view cpp_str_view{ "что" };

    utf8::ustring ustr_from_cpp_str_view{ cpp_str_view };
    ASSERT_EQ(cpp_str_view, ustr_from_cpp_str_view.get_c_str());

    ustr_from_cpp_str_view.replace_char("L", 0);
    ASSERT_NE(cpp_str_view, ustr_from_cpp_str_view.get_c_str());


    // ----------------------------- move ctor PART -----------------------------
    const char* move_data{ "привет мир" };

    utf8::ustring ustr_move{ move_data };
    auto other_ustr_move{ std::move(ustr_move) };

    ASSERT_EQ(other_ustr_move.get_c_str(), move_data);
    ASSERT_NE(ustr_move.get_c_str(), move_data);


    // ----------------------------- copy ctor PART -----------------------------
    const char* copy_data{ "хеллоу ворлд" };

    utf8::ustring copy_data_first{ copy_data };
    utf8::ustring copy_data_second{ copy_data_first };

    ASSERT_EQ(copy_data, copy_data_first.get_c_str());
    ASSERT_EQ(copy_data, copy_data_second.get_c_str());
    ASSERT_EQ(copy_data_first, copy_data_second);

    // TODO: write for other ctors ....
}

// ---------------------------------------------------------------------------------------------------------------------
TEST(utf8_string, operators)
{
    // ----------------------------- move operator PART -----------------------------
    const char* move_data{ "hello world" };

    utf8::ustring ustr_move{ move_data };
    utf8::ustring other_ustr_move;
    other_ustr_move = std::move(ustr_move);

    ASSERT_EQ(other_ustr_move.get_c_str(), move_data);
    ASSERT_NE(ustr_move.get_c_str(), move_data);


    // ----------------------------- copy operator PART -----------------------------
    const char* copy_data{ "хеллоу ворлд" };

    utf8::ustring copy_data_first{ copy_data };
    utf8::ustring copy_data_second;
    copy_data_second = copy_data_first;

    ASSERT_EQ(copy_data, copy_data_first.get_c_str());
    ASSERT_EQ(copy_data, copy_data_second.get_c_str());
    ASSERT_EQ(copy_data_first, copy_data_second);
}