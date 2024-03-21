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

#include <iostream>
#include <chrono>

#include <utf8_string.hpp>

int main()
{
    std::string str{ };
    str.reserve(1'000);

    std::string a{ "s" };
    std::string b{ "п" };
    std::string c{ "\xf0\x92\x8d\x87" };

    for (std::size_t i{}; i < 5'000; ++i)
    {
        str += a;
        str += b;
        str += c;
    }

    std::chrono::duration<double> res{ };

#if 0
    auto start = std::chrono::high_resolution_clock::now();

    utf8::ustring tmp{ str };
    for (std::size_t i{}; i < 1'000'000'000; ++i)
    {
        tmp.replace_char("s", 0);
        tmp.replace_char("ы", 300);
        tmp.replace_char("\xf0\x92\x8d\x87", 1234);
        tmp.replace_char("ы", 789);
        tmp.replace_char("\xf0\x92\x8d\x87", 1900);
    }

    auto end = std::chrono::high_resolution_clock::now();
    res = end - start;

    std::cout << res.count() << "s\n";
    std::cout << tmp << '\n';
#endif

    return 0;
}