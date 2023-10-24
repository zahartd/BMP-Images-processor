#pragma once

#include "../filter.h"

namespace image_processor {
class TGrayScaleFilter : public IFilter {
public:
    explicit TGrayScaleFilter(std::vector<std::string> filter_params = {});
    ~TGrayScaleFilter() override = default;

    void ApplyFilter(TImage &image) const override;
};
}  // namespace image_processor
