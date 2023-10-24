#pragma once

#include "../filters/utils.h"

#include <iostream>

namespace image_processor {
enum CLIArgs {
    CROP_FILTER = FiltersID::CROP,
    NEGATIVE_FILTER = FiltersID::NEGATIVE,
    GRAYSCALE_FILTER = FiltersID::GRAYSCALE,
    SHARPENING_FILTER = FiltersID::SHARPENING,
    EDGE_DETECTION_FILTER = FiltersID::EDGE_DETECTION,
    BLUR_FILTER = FiltersID::BLUR,
    MEDIAN_FILTER = FiltersID::MEDIAN,
    GLASS_FILTER = FiltersID::GLASS,
    INPUT_FILENAME_REQUIRED = FiltersID::LAST_FILTER + 1,
    OUTPUT_FILENAME_REQUIRED = FiltersID::LAST_FILTER + 2,
};

void PrintHeader();

void PrintUsage();

}  // namespace image_processor