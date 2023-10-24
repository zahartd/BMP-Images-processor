#include "TCompositeFilter.h"

#include <vector>

namespace image_processor {
TCompositeFilter::TCompositeFilter(std::vector<std::unique_ptr<IFilter>> filters) : filters_(std::move(filters)) {
}

void TCompositeFilter::ApplyFilter(TImage& image) const {
    for (const auto& filter : filters_) {
        filter->ApplyFilter(image);
    }
}

void TCompositeFilter::AddFilter(std::unique_ptr<IFilter> filter_ptr) {
    filters_.push_back(std::move(filter_ptr));
}
}  // namespace image_processor
