#include "exceptions.h"

namespace image_processor {
ErrorWithMessage::ErrorWithMessage(const std::string& message) : message_(message) {
}

const char* ErrorWithMessage::what() const noexcept {
    return message_.c_str();
}

}  // namespace image_processor
