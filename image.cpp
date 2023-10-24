#include "image.h"

#include <fstream>
#include <iostream>
#include <array>

#include "image/utils.h"
#include "image/exceptions.h"
#include "image/bmpexceptions.h"

namespace image_processor {
std::vector<TImage::Channel>& TImage::GetChannels() {
    return channels_;
}

size_t TImage::GetWidth() {
    return channels_[0][0].size();
}
size_t TImage::GetHeight() {
    return channels_[0].size();
}

void TImage::LoadFromBMP(const std::string& filename, bool is_verbose) {
    if (filename.substr(filename.size() - 4, 4) != ".bmp") {
        throw InvalidFileFormatError(filename, ".bmp");
    }
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw FileOpenError(filename);
    }

    if (is_verbose) {
        std::cout << "Successful open file " << filename << " to read." << std::endl;
    }

    // read BMP header
    BmpHeader bmp_header;
    file.read(reinterpret_cast<char*>(&bmp_header), sizeof(bmp_header));

    // read information about BMP
    BmpInfo bmp_info;
    file.read(reinterpret_cast<char*>(&bmp_info), sizeof(bmp_info));

    if (is_verbose) {
        std::cout << "Read data from " << filename << ": " << std::endl;
        bmp_header.PrintInfo();
        bmp_info.PrintInfo();
    }

    // validate BMP
    if (bmp_header.type[0] != 'B' || bmp_header.type[1] != 'M') {
        throw NotBMPFileError(filename, bmp_header.type);
    }

    if (bmp_info.width < 0) {
        throw InvalidWidthBMPError(filename);
    }

    if (bmp_info.info_size != sizeof(bmp_info)) {
        throw InvalidBMPFormatError(filename);
    }

    if (bmp_info.bit_count != BMP_BIT_COUNT) {
        throw InvalidBMPBitCountError(filename, bmp_info.bit_count);
    }

    if (bmp_info.compression != 0) {
        throw NotSupportedBMPCompressionModeError(filename, bmp_info.compression);
    }

    if (bmp_info.colors_used != 0 || bmp_info.colors_important != 0) {
        throw NotSupportedBMPColorTableError(filename);
    }

    if (is_verbose) {
        std::cout << "BMP file" << filename << " is valid" << std::endl;
    }

    // allocate memory for image channels
    channels_.resize(3);
    for (int32_t i = 0; i < 3; ++i) {
        channels_[i].resize(std::abs(bmp_info.height), std::vector<double>(bmp_info.width));
    }

    file.seekg(bmp_header.data_offset, std::ios::beg);

    // read bitmap data
    const int row_size = bmp_info.width * 3;
    const int padding_size = (4 - row_size % 4) % 4;
    for (int32_t row = 0; row < std::abs(bmp_info.height); ++row) {
        for (int32_t col = 0; col < bmp_info.width; ++col) {
            std::array<std::uint8_t, 3> color;
            int32_t new_row = bmp_info.height > 0 ? bmp_info.height - row - 1 : col;
            file.read(reinterpret_cast<char*>(&color), color.size());
            channels_[0][new_row][col] = static_cast<double>(color[2]) / MAX_COLOR_CHANNEL_VALUE;
            channels_[1][new_row][col] = static_cast<double>(color[1]) / MAX_COLOR_CHANNEL_VALUE;
            channels_[2][new_row][col] = static_cast<double>(color[0]) / MAX_COLOR_CHANNEL_VALUE;
        }
        file.seekg(padding_size, std::ios::cur);
    }

    if (is_verbose) {
        std::cout << "Read bitmap data from " << filename << "." << std::endl;
    }

    // Close file
    file.close();
}
void TImage::SaveToBMP(const std::string& filename, bool is_verbose) {
    if (filename.substr(filename.size() - 4, 4) != ".bmp") {
        throw InvalidFileFormatError(filename, ".bmp");
    }
    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        throw FileCloseError(filename);
    }

    if (is_verbose) {
        std::cout << "Successful open file " << filename << " to write." << std::endl;
    }

    // write BMP header
    BmpHeader bmp_header;
    bmp_header.type[0] = 'B';
    bmp_header.type[1] = 'M';
    bmp_header.reserved = 0;
    bmp_header.file_size = sizeof(BmpHeader) + sizeof(BmpInfo) + channels_[0].size() * channels_[0][0].size() * 3;
    bmp_header.data_offset = sizeof(BmpHeader) + sizeof(BmpInfo);
    file.write(reinterpret_cast<const char*>(&bmp_header), sizeof(BmpHeader));

    // write BMP info
    BmpInfo bmp_info;
    bmp_info.info_size = sizeof(BmpInfo);
    bmp_info.width = static_cast<int32_t>(GetWidth());
    bmp_info.height = static_cast<int32_t>(GetHeight());
    bmp_info.planes = 1;
    bmp_info.bit_count = BMP_BIT_COUNT;
    bmp_info.compression = 0;
    bmp_info.image_size = bmp_header.file_size - bmp_header.data_offset;
    bmp_info.x_pixels_per_meter = 0;
    bmp_info.y_pixels_per_meter = 0;
    bmp_info.colors_used = 0;
    bmp_info.colors_important = 0;
    file.write(reinterpret_cast<const char*>(&bmp_info), sizeof(BmpInfo));

    if (is_verbose) {
        std::cout << "Write data to " << filename << ": " << std::endl;
        bmp_header.PrintInfo();
        bmp_info.PrintInfo();
    }

    // Write bitmap data
    const int32_t row_size = bmp_info.width * 3;
    const int32_t padding_size = (4 - row_size % 4) % 4;
    for (int32_t row = 0; row < bmp_info.height; ++row) {
        for (int32_t col = 0; col < bmp_info.width; ++col) {
            uint8_t b = 0;
            uint8_t g = 0;
            uint8_t r = 0;
            int32_t new_row = bmp_info.height - row - 1;
            if (channels_.size() == 3) {
                b = static_cast<uint8_t>(channels_[2][new_row][col] * MAX_COLOR_CHANNEL_VALUE);
                g = static_cast<uint8_t>(channels_[1][new_row][col] * MAX_COLOR_CHANNEL_VALUE);
                r = static_cast<uint8_t>(channels_[0][new_row][col] * MAX_COLOR_CHANNEL_VALUE);
            } else if (channels_.size() == 1) {
                r = g = b = static_cast<uint8_t>(channels_[0][new_row][col] * MAX_COLOR_CHANNEL_VALUE);
            } else {
                throw BMPInvalidColorChannelCountError(channels_.size());
            }
            file.write(reinterpret_cast<const char*>(&b), 1);
            file.write(reinterpret_cast<const char*>(&g), 1);
            file.write(reinterpret_cast<const char*>(&r), 1);
        }
        uint8_t padding[3];
        file.write(reinterpret_cast<char*>(*&(padding)), padding_size);
    }

    if (is_verbose) {
        std::cout << "Write bitmap data to " << filename << "." << std::endl;
    }

    file.close();
}

void TImage::BmpHeader::PrintInfo() const {
    std::cout << "==== BMP HEADER block ====" << std::endl
              << "Type: " << type << std::endl
              << "File size: " << file_size << std::endl
              << "Reserved: " << reserved << std::endl
              << "Data offset: " << data_offset << std::endl;
}
void TImage::BmpInfo::PrintInfo() const {
    std::cout << "==== BMP INFO block ====" << std::endl
              << "Info size: " << info_size << std::endl
              << "Width: " << width << std::endl
              << "Height: " << height << std::endl
              << "Planes: " << planes << std::endl
              << "Bit count: " << bit_count << std::endl
              << "Compression; " << compression << std::endl
              << "Image size: " << image_size << std::endl
              << "X pixels per meter: " << x_pixels_per_meter << std::endl
              << "Y pixels per meter: " << y_pixels_per_meter << std::endl
              << "Colors used: " << colors_used << std::endl
              << "Colors important: " << colors_important << std::endl;
}
}  // namespace image_processor
