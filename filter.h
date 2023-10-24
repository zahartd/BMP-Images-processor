#pragma once

#include <memory>
#include <unordered_map>
#include <functional>

#include "image.h"
#include "args_parser.h"

namespace image_processor {
class IFilter {
public:
    virtual void ApplyFilter(TImage& image) const = 0;

    virtual ~IFilter() = default;
};

class TFilterManager {
public:
    explicit TFilterManager(const TArgParser::ResultOptions::OptionalOptions& filters_options);
    void CreateFilter(const int id, const std::vector<std::string>& options);
    void ApplyToImage(TImage& image, bool is_verbose = false) const;

private:
    std::vector<std::unique_ptr<IFilter>> filters_;
};

}  // namespace image_processor