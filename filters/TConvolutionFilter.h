#pragma once

#include "IChannelWiseFilter.h"

#include "utils.h"

namespace image_processor {
class TConvolutionFilter : public IChannelWiseFilter {
public:
    using Kernel = std::vector<std::vector<double>>;
    ~TConvolutionFilter() override = default;

    explicit TConvolutionFilter(const std::vector<std::vector<double>> &matrix);

protected:
    void FilterImpl(TImage::Channel &channel) const final;

private:
    Kernel kernel_;
    int32_t kernel_width_ = static_cast<int32_t>(kernel_[0].size());
    int32_t kernel_height_ = static_cast<int32_t>(kernel_.size());
    int32_t kernel_radius_x_ = kernel_width_ / 2;
    int32_t kernel_radius_y_ = kernel_height_ / 2;
};
}  // namespace image_processor
