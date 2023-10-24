#include "utils.h"

namespace image_processor {
void PrintHeader() {
    std::cout << "Cool Image Processor!" << std::endl
              << "A simple but very cool utility for image processing." << std::endl
              << std::endl;
}

void PrintUsage() {
    std::cout << "Usage:" << std::endl
              << "    "
              << "{program name} {path to input file} {path to output file} [-{filter name 1} [filter option 1] "
                 "[filter option 2] ...] [-{filter name 2} [filter option 1] [ filter parameter 2] ...] ..."
              << std::endl
              << std::endl;
}
}  // namespace image_processor
