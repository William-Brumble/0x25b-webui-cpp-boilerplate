#include <argparse/argparse.hpp>

#include "features/arguments/models/arguments_model.h"

Arguments init_args(const int argc, char** argv)
{
    argparse::ArgumentParser program("program");

    program.add_argument("--debug").flag();

    try {
        program.parse_args(argc, argv);
    } catch (const std::exception& err) {
        std::cerr << "Failed to parge the arguments" << std::endl;
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    spdlog::level::level_enum log_level = spdlog::level::info;
    if (program["--debug"] == true) {
        log_level = spdlog::level::debug;
    }

    return Arguments{
        log_level,
    };
}