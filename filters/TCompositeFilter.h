#pragma once

#include "../filter.h"

#include <memory>

#include "../args_parser.h"

namespace image_processor {
class TCompositeFilter : public IFilter {
public:
    explicit TCompositeFilter(std::vector<std::unique_ptr<IFilter>> filters);

    ~TCompositeFilter() override = default;

    void ApplyFilter(TImage& image) const final;
    void AddFilter(std::unique_ptr<IFilter> filter_ptr);

private:
    std::vector<std::unique_ptr<IFilter>> filters_;
};
}  // namespace image_processor
