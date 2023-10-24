#include <catch.hpp>
#include "image.h"
#include "filter.h"
#include "filters/TCrop.h"
#include "filters/TNegativeFilter.h"
#include "filters/TSharpeningFilter.h"
#include "filters/TGaussianBlurFilter.h"

namespace {
static constexpr double EPS = 0.01;
}

TEST_CASE("Filters: Blur") {
    image_processor::TImage common_img;
    const std::string common_img_path =
        "/home/hexinf/projects/hse-course/tasks/image_processor/test_script/data/lenna.bmp";
    image_processor::TImage correct_img;
    const std::string correct_img_path =
        "/home/hexinf/projects/hse-course/tasks/image_processor/test_script/data/lenna_blur.bmp";

    common_img.LoadFromBMP(common_img_path);
    correct_img.LoadFromBMP(correct_img_path);

    image_processor::TGaussianBlurFilter filter(7.5);  // NOLINT

    filter.ApplyFilter(common_img);

    auto& common_img_channels = common_img.GetChannels();
    auto& correct_img_channels = correct_img.GetChannels();

    REQUIRE(common_img_channels.size() == correct_img_channels.size());
    REQUIRE(common_img.GetHeight() == correct_img.GetHeight());
    REQUIRE(common_img.GetWidth() == correct_img.GetWidth());

    for (size_t ch = 0; ch < 3; ++ch) {
        for (size_t y = 0; y < common_img.GetHeight(); ++y) {
            for (size_t x = 0; x < common_img.GetWidth(); ++x) {
                REQUIRE(std::abs(common_img_channels[ch][y][x] - correct_img_channels[ch][y][x]) < EPS);
            }
        }
    }
}

TEST_CASE("Filters: Crop") {
    image_processor::TImage common_img;
    const std::string common_img_path =
        "/home/hexinf/projects/hse-course/tasks/image_processor/test_script/data/lenna.bmp";
    image_processor::TImage correct_img;
    const std::string correct_img_path =
        "/home/hexinf/projects/hse-course/tasks/image_processor/test_script/data/lenna_crop.bmp";

    common_img.LoadFromBMP(common_img_path);
    correct_img.LoadFromBMP(correct_img_path);

    image_processor::TCrop filter(999, 1999);  // NOLINT

    filter.ApplyFilter(common_img);

    auto& common_img_channels = common_img.GetChannels();
    auto& correct_img_channels = correct_img.GetChannels();

    REQUIRE(common_img_channels.size() == correct_img_channels.size());
    REQUIRE(common_img.GetHeight() == 1999);
    REQUIRE(common_img.GetWidth() == 999);

    for (size_t ch = 0; ch < 3; ++ch) {
        for (size_t y = 0; y < common_img.GetHeight(); ++y) {
            for (size_t x = 0; x < common_img.GetWidth(); ++x) {
                REQUIRE(std::abs(common_img_channels[ch][y][x] - correct_img_channels[ch][y][x]) < EPS);
            }
        }
    }
}

TEST_CASE("Filters: Sharpening") {
    image_processor::TImage common_img;
    const std::string common_img_path =
        "/home/hexinf/projects/hse-course/tasks/image_processor/test_script/data/flag.bmp";
    image_processor::TImage correct_img;
    const std::string correct_img_path =
        "/home/hexinf/projects/hse-course/tasks/image_processor/test_script/data/flag_sharp.bmp";

    common_img.LoadFromBMP(common_img_path);
    correct_img.LoadFromBMP(correct_img_path);

    image_processor::TSharpeningFilter filter;  // NOLINT

    filter.ApplyFilter(common_img);

    auto& common_img_channels = common_img.GetChannels();
    auto& correct_img_channels = correct_img.GetChannels();

    REQUIRE(common_img_channels.size() == correct_img_channels.size());
    REQUIRE(common_img.GetHeight() == correct_img.GetHeight());
    REQUIRE(common_img.GetWidth() == correct_img.GetWidth());

    for (size_t ch = 0; ch < 3; ++ch) {
        for (size_t y = 0; y < common_img.GetHeight(); ++y) {
            for (size_t x = 0; x < common_img.GetWidth(); ++x) {
                REQUIRE(std::abs(common_img_channels[ch][y][x] - correct_img_channels[ch][y][x]) < EPS);
            }
        }
    }
}

TEST_CASE("Filters: Negative") {
    image_processor::TImage common_img;
    const std::string common_img_path =
        "/home/hexinf/projects/hse-course/tasks/image_processor/test_script/data/flag.bmp";
    image_processor::TImage correct_img;
    const std::string correct_img_path =
        "/home/hexinf/projects/hse-course/tasks/image_processor/test_script/data/flag_neg.bmp";

    common_img.LoadFromBMP(common_img_path);
    correct_img.LoadFromBMP(correct_img_path);

    image_processor::TNegativeFilter filter;  // NOLINT

    filter.ApplyFilter(common_img);

    auto& common_img_channels = common_img.GetChannels();
    auto& correct_img_channels = correct_img.GetChannels();

    REQUIRE(common_img.GetHeight() == correct_img.GetHeight());
    REQUIRE(common_img.GetWidth() == correct_img.GetWidth());

    for (size_t ch = 0; ch < 3; ++ch) {
        for (size_t y = 0; y < common_img.GetHeight(); ++y) {
            for (size_t x = 0; x < common_img.GetWidth(); ++x) {
                REQUIRE(std::abs(common_img_channels[ch][y][x] - correct_img_channels[ch][y][x]) < EPS);
            }
        }
    }
}
