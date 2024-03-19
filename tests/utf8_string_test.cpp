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