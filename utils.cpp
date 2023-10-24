#include "utils.h"

namespace image_processor {
bool IsNumeric(std::string str) {
    return std::all_of(str.begin(), str.end(), [](char c) { return std::isdigit(c); });
}
}  // namespace image_processor
