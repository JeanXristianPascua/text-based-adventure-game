#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP

#include <string>
#include <algorithm>
#include <vector>

class StringUtils {
 public:
    // Convert string to lowercase
    static std::string toLower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(),
                      result.begin(), ::tolower);
        return result;
    }

    // Case-insensitive string comparison
    static bool equalsIgnoreCase(const std::string& str1,
                                 const std::string& str2) {
        return toLower(str1) == toLower(str2);
    }

    // Check if str contains substring (case-insensitive)
    static bool containsIgnoreCase(const std::string& str,
                                   const std::string& substring) {
        std::string lowerStr = toLower(str);
        std::string lowerSub = toLower(substring);
        return lowerStr.find(lowerSub) != std::string::npos;
    }

    // Trim whitespace from both ends
    static std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) {
            return "";
        }
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, (last - first + 1));
    }

    // Combine vector of strings with delimiter
    static std::string join(const std::vector<std::string>& strings,
                           const std::string& delimiter = " ",
                           size_t startIndex = 0) {
        if (strings.empty() || startIndex >= strings.size()) {
            return "";
        }

        std::string result = strings[startIndex];
        for (size_t i = startIndex + 1; i < strings.size(); ++i) {
            result += delimiter + strings[i];
        }
        return result;
    }

 private:
    // Prevent instantiation - this is a utility class
    StringUtils() = delete;
};

#endif  // STRINGUTILS_HPP
