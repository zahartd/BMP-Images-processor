#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <string_view>

#include "../exceptions.h"

namespace image_processor {
class FilterError : public ErrorWithMessage {
public:
    using ErrorWithMessage::ErrorWithMessage;
};

class UnexpectedParamsCountError : public FilterError {
public:
    UnexpectedParamsCountError(std::string filter_name, size_t expected_params_count, size_t provided_params_count);
};

class UnexpectedParamsTypeError : public FilterError {
public:
    UnexpectedParamsTypeError(std::string filter_name,
                              std::vector<std::pair<std::string, std::string>> expected_params_types);
};

class UnexpectedParamsValueRangeError : public FilterError {
public:
    UnexpectedParamsValueRangeError(
        std::string filter_name,
        std::vector<std::pair<std::string, std::pair<std::string, std::string>>> expected_params_ranges);
};

}  // namespace image_processor