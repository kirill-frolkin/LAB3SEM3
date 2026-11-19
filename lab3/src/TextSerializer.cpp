#include "TextSerializer.h"
#include <fstream>
#include <iostream>

std::string TextSerializer::escape(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (char c : s) {
        if (c == '\\') {
            out += "\\\\";
        } else if (c == '\n') {
            out += "\\n";
        } else if (c == '\r') {
            out += "\\r";
        } else {
            out += c;
        }
    }
    return out;
}

std::string TextSerializer::unescape(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '\\' && i + 1 < s.size()) {
            char next = s[i + 1];
            if (next == 'n') {
                out += '\n';
                ++i;
            } else if (next == 'r') {
                out += '\r';
                ++i;
            } else if (next == '\\') {
                out += '\\';
                ++i;
            } else {
                out += s[i];
            }
        } else {
            out += s[i];
        }
    }
    return out;
}

bool TextSerializer::saveText(const SinglyList& list, const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Не удалось открыть файл для записи: " << filename << "\n";
        return false;
    }

    out << list.getSize() << "\n";
    for (int i = 0; i < list.getSize(); ++i) {
        out << escape(list.get(i)) << "\n";
    }

    return static_cast<bool>(out);
}

SinglyList TextSerializer::loadText(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Не удалось открыть файл для чтения: " << filename << "\n";
        return SinglyList();
    }

    int count = 0;
    if (!(in >> count) || count < 0) {
        return SinglyList();
    }
    in.ignore();

    SinglyList list;
    for (int i = 0; i < count; ++i) {
        std::string line;
        if (!std::getline(in, line)) {
            return SinglyList();
        }
        list.pushBack(unescape(line));
    }

    return list;
}
