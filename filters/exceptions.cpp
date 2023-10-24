#include "exceptions.h"

#include <vector>

namespace image_processor {

UnexpectedParamsCountError::UnexpectedParamsCountError(std::string filter_name, size_t expected_params_count,
                                                       size_t provided_params_count)
    : FilterError("Filter " + filter_name + " after -{filter name} expected " + std::to_string(expected_params_count) +
                  " params, but it provided " + std::to_string(provided_params_count)) {
}
UnexpectedParamsTypeError::UnexpectedParamsTypeError(
    std::string filter_name, std::vector<std::pair<std::string, std::string>> expected_params_types)
    : FilterError("Filter " + filter_name + " expected " + std::to_string(expected_params_types.size()) +
                  " params with this types: ") {
    for (const auto& [param_name, param_type] : expected_params_types) {
        message_ += param_type + " type " + " <" + param_name + ">" + ",";
    }
    message_ += "but provided params not.";
}
UnexpectedParamsValueRangeError::UnexpectedParamsValueRangeError(
    std::string filter_name,
    std::vector<std::pair<std::string, std::pair<std::string, std::string>>> expected_params_ranges)
    : FilterError("Filter " + filter_name + " expected " + std::to_string(expected_params_ranges.size()) +
                  " params with this ranges: ") {
    for (const auto& [param_name, param_ranges] : expected_params_ranges) {
        message_ += "<" + param_name + ">" + " from " + param_ranges.first + " to " + param_ranges.second + ",";
    }
    message_ += "but provided params not.";
}
}  // namespace image_processor
