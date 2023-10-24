#include "args_parser.h"

#include "cli/utils.h"
#include "cli/exceptions.h"
#include "filters/utils.h"

namespace image_processor {

TArgParser::TArgParser(TArgParser::OptionsDescriptor options_descriptor) : options_descriptor_(options_descriptor) {
    for (const auto& option : options_descriptor_) {
        if (option.is_required) {
            ++require_args_count_;
        } else {
            for (const auto& option_name : option.names) {
                supported_args_to_id_[option_name] = option.id;
            }
        }
    }
}

void TArgParser::Parse(int argc, char** argv) {
    if (argc == 1) {
        PrintHelp();
        std::exit(0);
    }

    if (argc < require_args_count_ + 1) {
        throw MissingRequiredArgsError();
    }

    //  Parsing required (positional) args
    int32_t curr_arg_index = 1;
    while (require_args_count_ > 0 && curr_arg_index < argc) {
        --require_args_count_;
        if (argv[curr_arg_index][0] == '-') {
            throw MissingRequiredArgsError();
        }
        result_options_.required_options.push_back(argv[curr_arg_index]);
        ++curr_arg_index;
    }

    // Parsing optional args
    while (curr_arg_index < argc) {
        std::string curr_arg = static_cast<std::string>(argv[curr_arg_index]);

        // Help option
        if (curr_arg == "-h" || curr_arg == "-help") {
            PrintHelp();
            std::exit(0);
        }

        // Verbose option
        if (curr_arg == "-v" || curr_arg == "--verbose") {
            result_options_.work_mode.is_need_verbose = true;
            ++curr_arg_index;
            continue;
        }

        if (curr_arg.empty() || curr_arg[0] != '-') {
            throw InvalidArgFormatError();
        }

        // Formatted current arg
        curr_arg.erase(0, 1);

        // Unsupported arg
        auto arg_it = supported_args_to_id_.find(curr_arg);
        if (arg_it == supported_args_to_id_.end()) {
            throw UnexpectedArgError();
        }

        ++curr_arg_index;

        // Add the arg id to the result_options_ optional_options vector
        result_options_.optional_options.push_back({arg_it->second, {}});

        // collecting argument parameters
        while (curr_arg_index < argc && argv[curr_arg_index][0] != '-') {
            result_options_.optional_options.back().second.push_back(static_cast<std::string>(argv[curr_arg_index]));
            ++curr_arg_index;
        }
    }
}

TArgParser::ResultOptions TArgParser::GetOptions() const {
    return result_options_;
}
void TArgParser::PrintHelp() {
    PrintHeader();
    PrintUsage();
    PrintFiltersInfo();
}

}  // namespace image_processor
