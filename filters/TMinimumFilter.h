#pragma once

#include "IChannelWiseFilter.h"

namespace image_processor {
class TMinimumFilter final : public IChannelWiseFilter {
public:
    ~TMinimumFilter() override = default;
    explicit TMinimumFilter(std::vector<std::string> filter_params);
    explicit TMinimumFilter(int32_t radius);

protected:
    void FilterImpl(TImage::Channel &channel) const final;

private:
    int32_t radius_;
};
}  // namespace image_processor
