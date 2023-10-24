#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

namespace image_processor {
// Constants
using Kernel = std::vector<std::vector<double>>;
const Kernel SHARPENING_FILTER_KERNEL = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
const Kernel EDGE_DETECTION_FILTER_KERNEL = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
const Kernel EMBOSSING_FILTER_KERNEL = {{-2, -1, 0}, {-1, 1, 1}, {0, 1, 2}};
static const double DEFAULT_BLUR_SIGMA = 0.5;
static const double EMBOSSING_EDGE_DETECTION_THRESHOLD = 0.5;

// Filters Info

enum FiltersID { CROP, NEGATIVE, GRAYSCALE, SHARPENING, EDGE_DETECTION, BLUR, MEDIAN, GLASS, OIL_PRINT, LAST_FILTER };

struct FilterInfo {
    std::string name = "Filter";
    std::vector<std::string> cli_names = {"-filter"};
    std::vector<std::string> params = {"None"};
    std::string description = "Image filter";
};

const FilterInfo CROP_INFO{.name = "Crop",
                           .cli_names = {"crop"},
                           .params = {"width", "height"},
                           .description =
                               "Reduces the size of the image to the specified width and height. The top left of the "
                               "image is used. If the requested width or height exceeds the dimensions of the original "
                               "image, the available portion of the image is returned."};

const FilterInfo NEGATIVE_INFO{
    .name = "Negative",
    .cli_names = {"neg"},
    .description = "Invert each image pixel across all channels (new_px_value = 1 - old_px_value)."};

const FilterInfo GRAYSCALE_INFO{
    .name = "Grayscale",
    .cli_names = {"gs"},
    .description = "Converts an image to grayscale using a formula R' = G' = B' = 0.299R + 0.587G + 0.114B."};

const FilterInfo SHARPENING_INFO{.name = "Sharpening", .cli_names = {"sharp"}, .description = "Image sharpening."};

const FilterInfo EDGE_DETECTION_INFO{.name = "Edge Detection",
                                     .cli_names = {"edge"},
                                     .params = {"threshold"},
                                     .description =
                                         "Boundary selection. The image is converted to grayscale. Pixels with a value "
                                         "that exceeds the threshold are painted white, the rest are black."};

const FilterInfo BLUR_INFO{
    .name = "Gaussian Blur",
    .cli_names = {"blur"},
    .params = {"sigma"},
    .description = "Blur image with Gaussian function. The sigma parameter determines the strength of the blur."};

const FilterInfo MEDIAN_INFO{.name = "Median",
                             .cli_names = {"median"},
                             .params = {"radius"},
                             .description =
                                 "Converts each channel of each pixel in the image to the median of the pixels in the "
                                 "given radius (denoising)."};

const FilterInfo GLASS_INFO{
    .name = "Glass",
    .cli_names = {"glass"},
    .params = {"radius"},
    .description = "Applies a glass effect to the image, the radius parameter sets the strength of the effect."};

const FilterInfo OIL_PRINT_INFO{
    .name = "Oil paint",
    .cli_names = {"oil"},
    .params = {"radius"},
    .description =
        "Applies the effect of oil paints to the image, the radius parameter sets the strength of the effect."};

const std::unordered_map<int, FilterInfo> FILTERS_INFO = {
    {FiltersID::CROP, CROP_INFO},
    {FiltersID::NEGATIVE, NEGATIVE_INFO},
    {FiltersID::GRAYSCALE, GRAYSCALE_INFO},
    {FiltersID::SHARPENING, SHARPENING_INFO},
    {FiltersID::EDGE_DETECTION, EDGE_DETECTION_INFO},
    {FiltersID::BLUR, BLUR_INFO},
    {FiltersID::MEDIAN, MEDIAN_INFO},
    {FiltersID::GLASS, GLASS_INFO},
    {FiltersID::OIL_PRINT, OIL_PRINT_INFO},
};

// CLI

void PrintFilterInfo(int filter_id);
void PrintFiltersInfo();

// Other

double LuminancePx(double r, double g, double b);
}  // namespace image_processor
