#include "utils.h"

#include <iostream>
#include <iomanip>

namespace image_processor {

void PrintFilterInfo(int filter_id) {
    static constexpr int PrintWeight = 30;
    FilterInfo filter_info = FILTERS_INFO.at(filter_id);
    std::cout << setiosflags(std::ios::left);
    std::cout << std::setw(PrintWeight) << filter_info.name;
    std::cout << std::setw(PrintWeight);
    for (const auto& cli_name : filter_info.cli_names) {
        std::cout << "-" + cli_name;
    }
    std::cout << std::endl;
    std::cout << "Description: " << filter_info.description << std::endl;
}

void PrintFiltersInfo() {
    for (const auto& [filter_id, filter_info] : FILTERS_INFO) {
        PrintFilterInfo(filter_id);
    }
    std::cout << std::endl;
}

double LuminancePx(double r, double g, double b) {
    static constexpr double RedCoefficient = 0.299;
    static constexpr double BlueCoefficient = 0.587;
    static constexpr double GreenCoefficient = 0.114;
    return RedCoefficient * r + BlueCoefficient * g + GreenCoefficient * b;
}
}  // namespace image_processor
