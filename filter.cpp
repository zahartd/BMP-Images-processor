#include "filter.h"

#include <memory>
#include <iostream>

#include "filters/utils.h"
#include "filters/TCrop.h"
#include "filters/TNegativeFilter.h"
#include "filters/TGrayScaleFilter.h"
#include "filters/TSharpeningFilter.h"
#include "filters/TEdgeDetectionFilter.h"
#include "filters/TGaussianBlurFilter.h"
#include "filters/TMedianFilter.h"
#include "filters/TGlassFilter.h"

namespace image_processor {

template <typename T>
struct TFilterProxy {
    static std::unique_ptr<IFilter> Create(const std::vector<std::string>& s = {}) {
        return std::make_unique<T>(s);
    };
};

using TCreate = std::unique_ptr<IFilter> (*)(const std::vector<std::string>&);

const std::unordered_map<int, TCreate> SUPPORTED_FILTERS = {
    {image_processor::FiltersID::CROP, image_processor::TFilterProxy<image_processor::TCrop>::Create},
    {image_processor::FiltersID::NEGATIVE, image_processor::TFilterProxy<image_processor::TNegativeFilter>::Create},
    {image_processor::FiltersID::GRAYSCALE, image_processor::TFilterProxy<image_processor::TGrayScaleFilter>::Create},
    {image_processor::FiltersID::SHARPENING, image_processor::TFilterProxy<image_processor::TSharpeningFilter>::Create},
    {image_processor::FiltersID::EDGE_DETECTION,
     image_processor::TFilterProxy<image_processor::TEdgeDetectionFilter>::Create},
    {image_processor::FiltersID::BLUR, image_processor::TFilterProxy<image_processor::TGaussianBlurFilter>::Create},
    {image_processor::FiltersID::MEDIAN, image_processor::TFilterProxy<image_processor::TMedianFilter>::Create},
    {image_processor::FiltersID::GLASS, image_processor::TFilterProxy<image_processor::TGlassFilter>::Create},
};

TFilterManager::TFilterManager(const TArgParser::ResultOptions::OptionalOptions& filters_options) {
    for (const auto& [id, options] : filters_options) {
        CreateFilter(id, options);
    }
}

void TFilterManager::ApplyToImage(TImage& image, bool is_verbose) const {
    if (is_verbose) {
        std::cout << "Applying filters: " << std::endl;
    }
    for (const auto& filter : filters_) {
        if (is_verbose) {
            std::cout << "Start applying filter"
                      << ""
                      << " with params: " << std::endl;
        }
        filter->ApplyFilter(image);
        if (is_verbose) {
            std::cout << "Successful finish applying filter"
                      << "" << std::endl;
        }
    }
    std::cout << "Successful finish apply all filter!" << std::endl;
}
void TFilterManager::CreateFilter(const int id, const std::vector<std::string>& options) {
    filters_.push_back(SUPPORTED_FILTERS.at(id)(options));
}
}  // namespace image_processor