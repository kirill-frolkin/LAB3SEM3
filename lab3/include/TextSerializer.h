#pragma once

#include <string>
#include "SinglyList.h"

class TextSerializer {
private:
    static std::string escape(const std::string& s);
    static std::string unescape(const std::string& s);

public:
    static bool saveText(const SinglyList& list, const std::string& filename);
    static SinglyList loadText(const std::string& filename);
};
