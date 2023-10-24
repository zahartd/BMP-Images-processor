#include <iostream>
#include <memory>

#include "args_parser.h"
#include "image.h"
#include "filter.h"
#include "cli/utils.h"
#include "cli/exceptions.h"
#include "image/exceptions.h"
#include "image/bmpexceptions.h"
#include "filters/exceptions.h"

int main(int argc, char** argv) {
    try {
        image_processor::TArgParser::OptionsDescriptor options_descriptor = {
            {image_processor::CLIArgs::INPUT_FILENAME_REQUIRED, {}, true},
            {image_processor::CLIArgs::OUTPUT_FILENAME_REQUIRED, {}, true},
            {image_processor::CLIArgs::CROP_FILTER,
             image_processor::FILTERS_INFO.at(image_processor::CLIArgs::CROP_FILTER).cli_names, false},
            {image_processor::CLIArgs::NEGATIVE_FILTER,
             image_processor::FILTERS_INFO.at(image_processor::CLIArgs::NEGATIVE_FILTER).cli_names, false},
            {image_processor::CLIArgs::SHARPENING_FILTER,
             image_processor::FILTERS_INFO.at(image_processor::CLIArgs::SHARPENING_FILTER).cli_names, false},
            {image_processor::CLIArgs::GRAYSCALE_FILTER,
             image_processor::FILTERS_INFO.at(image_processor::CLIArgs::GRAYSCALE_FILTER).cli_names, false},
            {image_processor::CLIArgs::EDGE_DETECTION_FILTER,
             image_processor::FILTERS_INFO.at(image_processor::CLIArgs::EDGE_DETECTION_FILTER).cli_names, false},
            {image_processor::CLIArgs::BLUR_FILTER,
             image_processor::FILTERS_INFO.at(image_processor::CLIArgs::BLUR_FILTER).cli_names, false},
            {image_processor::CLIArgs::MEDIAN_FILTER,
             image_processor::FILTERS_INFO.at(image_processor::CLIArgs::MEDIAN_FILTER).cli_names, false},
            {image_processor::CLIArgs::GLASS_FILTER,
             image_processor::FILTERS_INFO.at(image_processor::CLIArgs::GLASS_FILTER).cli_names, false},
        };

        // Parsing CLI
        image_processor::TArgParser parser(options_descriptor);
        parser.Parse(argc, argv);
        image_processor::TArgParser::ResultOptions user_query = parser.GetOptions();

        // Load image
        image_processor::TImage image;
        auto [input_filename, output_filename] =
            std::tuple<std::string, std::string>(user_query.required_options[0], user_query.required_options[1]);
        image.LoadFromBMP(input_filename, user_query.work_mode.is_need_verbose);

        // Create main filter (compositor) with other
        image_processor::TFilterManager filter_manager(user_query.optional_options);
        // Apply it to image
        filter_manager.ApplyToImage(image, user_query.work_mode.is_need_verbose);

        // Save image
        image.SaveToBMP(output_filename, user_query.work_mode.is_need_verbose);
        return 0;
    } catch (const image_processor::FileError& error) {
        std::cerr << "File Error: " << error.what() << std::endl;
        std::cout << "Hint: "
                  << "check that no other process is currently running on the given file and that the file is readable "
                     "and writable."
                  << std::endl;
        std::exit(-1);
    } catch (const image_processor::BMPError& error) {
        std::cerr << "BMP Error: " << error.what() << std::endl;
        std::cout << "Hint: "
                  << "read the help for using the program." << std::endl;
        image_processor::TArgParser::PrintHelp();
        std::exit(-1);
    } catch (const image_processor::ParserError& error) {
        std::cerr << "Parser Error: " << error.what() << std::endl;
        std::cout << "Hint: "
                  << "read the help for how using the program." << std::endl;
        image_processor::TArgParser::PrintHelp();
        std::exit(-1);
    } catch (const image_processor::FilterError& error) {
        std::cerr << "Filter Error: " << error.what() << std::endl;
        std::cout << "Hint: "
                  << "read the help for using the filters." << std::endl;
        image_processor::TArgParser::PrintHelp();
        std::exit(-1);
    } catch (const std::exception& error) {
        std::cerr << "Unknown Error: " << error.what() << std::endl;
        std::cout << "Hint: "
                  << "read the help for using the program." << std::endl;
        image_processor::TArgParser::PrintHelp();
        std::exit(-1);
    }
}
