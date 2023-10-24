#pragma once

#include <vector>
#include <array>
#include <string>

namespace image_processor {
class TImage {
public:
    using Channel = std::vector<std::vector<double>>;
    using Channels = std::vector<Channel>;

#pragma pack(push, 1)
    struct BmpHeader {
        char type[2];
        uint32_t file_size;
        uint32_t reserved;
        uint32_t data_offset;
        void PrintInfo() const;
    };

    struct BmpInfo {
        uint32_t info_size;
        int32_t width;
        int32_t height;
        uint16_t planes;
        uint16_t bit_count;
        uint32_t compression;
        uint32_t image_size;
        int32_t x_pixels_per_meter;
        int32_t y_pixels_per_meter;
        uint32_t colors_used;
        uint32_t colors_important;
        void PrintInfo() const;
    };
#pragma pack(pop)

    std::vector<Channel>& GetChannels();

    size_t GetWidth();
    size_t GetHeight();

    void LoadFromBMP(const std::string& filename, bool is_verbose = false);

    void SaveToBMP(const std::string& filename, bool is_verbose = false);

private:
    Channels channels_;
};
}  // namespace image_processor