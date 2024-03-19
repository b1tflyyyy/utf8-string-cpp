## UTF-8 String For C++ (utf8::ustring)

## Brief Description:
This is an implementation of the UTF-8 encoding standard for C++, the implementation is based on the std::basic_string\<char\> class, this gives us the advantage of std::basic_string\<char\> class functions, as well as compatibility with some functions from the standard library.

## Code Style:
- C++ AStyle code style was used for this project.

## Technical Dependencies:
- C++ 20
- CMake 3.14

## Support Status On Systems:
- [X] Linux
- [ ] Windows (not yet verified)

## Library Features:
- Support for creating an object from: `std::string, std::string_view, const char*`
- Comparing an `utf8::ustring` with `utf8::ustring` (comparison with `const char*`, `std::string`, `std::string_view` will be added in the future)
- Copy/Move (<- assignment also) constructor implemented 
- O(1) Random Access
- Simple replacement of any character, e.g. a smaller character (1 byte) with a larger character (2-3-4 bytes).

## Performance Test:
| String-Version |        Test-Name        | iteration count | time (for all iterations) | 
|:--------------:|:-----------------------:|:---------------:|:-------------------------:|
|  std::string   |      replace_char       |     500'000     |          ~0.57s           |                          
| utf8::ustring  |      replace_char       |     500'000     |          ~0.60s           |

## Coming Soon:
- A more detailed test and description of the string speed.
- Test in Windows.
- Introduction of new functions.
- Code samples.

    <div style="text-align: center;">
        © 2024 Andrii (AKA b1tflyyyy). All rights reserved.
    </div>
