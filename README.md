## ⚙️ UTF-8 String For C++ (utf8::ustring)

## 📜 Brief Description:
This is an implementation of the `UTF-8` encoding standard for `C++`, the implementation is based on the `std::basic_string<char>` class, this gives us the advantage of `std::basic_string<char>` class functions, as well as compatibility with some functions from the standard library.

## 📝 Code Style:
- `C++ AStyle` code style was used for this project.

## 🛠 Technical Dependencies:
- `C++ 20`
- `CMake 3.14`

## 🔗 Support Status On Systems:
- [X] Linux (verified on clang)
- [X] Windows (verified on gcc && clang)

## 💫 Library Features:
- Support for creating an object from: `std::string, std::string_view, const char*`
- Comparing an `utf8::ustring` with `utf8::ustring` (comparison with `const char*`, `std::string`, `std::string_view` will be added in the future)
- Copy/Move (<- assignment also) constructor implemented 
- O(1) Random Access
- Simple replacement of any character, e.g. a smaller character `(1 byte)` with a larger character `(2-3-4 bytes)`.

## ⚡️ Performance Test:
| String-Version |        Test-Name        | iteration count | time (for all iterations) | 
|:--------------:|:-----------------------:|:---------------:|:-------------------------:|
|  std::string   |      replace_char       |     500'000     |          ~0.57s           |                          
| utf8::ustring  |      replace_char       |     500'000     |          ~0.60s           |

## ❔ Replace Char O(1) ?
Yes and no, in the case where we replace a character with another `with the same size`, we have `O(1)`, in the other case we have `O(~N)`, where N is the length of the string.
But in any case we have `O(1) Random Access`.

## 📚 Code Samples:
```cpp
std::string str{ "hello world!" };
utf8::ustring ustr{ str };

ustr.replace_char("п", 0); // "пello world!"

ustr == "hi !"; // false
ustr == str; // false
```

## ⭐️ Coming Soon:
- Write/read to file.
- Add new features.
- Docs.

### © 2024 Andrii (AKA b1tflyyyy). All rights reserved.
