#pragma once

#include <stdexcept>
#include <string>

namespace image_processor {
class ErrorWithMessage : public std::exception {
public:
    explicit ErrorWithMessage(const std::string& message);
    const char* what() const noexcept override;

protected:
    std::string message_;
};
}  // namespace image_processor
