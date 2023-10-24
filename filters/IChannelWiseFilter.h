#pragma once

#include "../filter.h"

namespace image_processor {
class IChannelWiseFilter : public IFilter {
public:
    ~IChannelWiseFilter() override = default;

    void ApplyFilter(TImage &image) const final;

protected:
    virtual void FilterImpl(TImage::Channel &channel) const = 0;
};
}  // namespace image_processor
