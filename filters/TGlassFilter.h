#pragma once

#include "IChannelWiseFilter.h"

namespace image_processor {
class TGlassFilter final : public IChannelWiseFilter {
public:
    ~TGlassFilter() override = default;
    explicit TGlassFilter(std::vector<std::string> filter_params);
    explicit TGlassFilter(int32_t radius);

protected:
    void FilterImpl(TImage::Channel &channel) const final;

private:
    int32_t radius_;
};
}  // namespace image_processor
