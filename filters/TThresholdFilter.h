#pragma once

#include "IChannelWiseFilter.h"

namespace image_processor {
class TThresholdFilter final : public IChannelWiseFilter {
public:
    explicit TThresholdFilter(std::vector<std::string> filter_params);
    explicit TThresholdFilter(float threshold);
    ~TThresholdFilter() override = default;

protected:
    void FilterImpl(TImage::Channel &channel) const override;

private:
    float threshold_;
};
}  // namespace image_processor
