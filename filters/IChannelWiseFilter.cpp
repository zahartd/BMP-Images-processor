#include "IChannelWiseFilter.h"

namespace image_processor {
void IChannelWiseFilter::ApplyFilter(TImage& image) const {
    for (TImage::Channel& channel : image.GetChannels()) {
        FilterImpl(channel);
    }
}
}  // namespace image_processor