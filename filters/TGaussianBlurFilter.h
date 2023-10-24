#pragma once

#include "IChannelWiseFilter.h"

namespace image_processor {
class TGaussianBlurFilter : public IChannelWiseFilter {
public:
    ~TGaussianBlurFilter() override = default;
    explicit TGaussianBlurFilter(std::vector<std::string> filter_params = {});
    explicit TGaussianBlurFilter(double sigma);

protected:
    void FilterImpl(TImage::Channel &channel) const final;

private:
    double sigma_;
};
}  // namespace image_processor
