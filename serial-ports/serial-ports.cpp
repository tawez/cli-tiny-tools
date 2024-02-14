// Serial ports enumerator / finder
// OS: Ubuntu
// REF: https://stackoverflow.com/questions/15342804/c-linux-detect-all-serial-ports

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>

struct Args {
    std::string_view pattern;
};

void usage(std::filesystem::path prog)
{
    std::cout
        << "List available serial ports or find serial ports of which ID contains given pattern" << "\n"
        << "Usage: " << prog.filename().string() << " [options] [pattern]" << "\n"
        << "Options:" << "\n"
        << "  -h/--help:  Show this screen" << std::endl;
}

Args parse_args(int argc, char *argv[])
{
    Args args = {};
    if (argc > 1) {
        std::string_view arg{argv[1]};
        if (arg == "-h" || arg == "--help")
        {
            usage(argv[0]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            args.pattern = arg;
        }
    }
    return args;
}

void list_ports(std::string_view pattern)
{
    std::filesystem::path dir{"/dev/serial/by-id"};

    if (!std::filesystem::exists(dir))
    {
        throw std::runtime_error(dir.generic_string() + " does not exist");
    }
    else
    {
        // dir_entry is a full path to /dev/serial/by-id/<entry>
        for (auto const& dir_entry : std::filesystem::directory_iterator(dir))
        {
            // continue if pattern is not empty and dir_entry does not contain the pattern
            if (!pattern.empty() && dir_entry.path().string().find(pattern) == std::string::npos)
            {
                continue;
            }

            if (dir_entry.is_symlink())
            {
                // symlink_points_at is a relative path from dir_entry
                std::filesystem::path symlink_points_at = std::filesystem::read_symlink(dir_entry);
                // canonical_path is a full path to /dev/<port>
                std::filesystem::path canonical_path = std::filesystem::canonical(dir/symlink_points_at);
                std::cout << canonical_path.string() << " [" << dir_entry.path().filename().string() << "]" << std::endl;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    Args args = parse_args(argc, argv);

    if (args.pattern.empty())
    {
        std::cout << "Enumerating serial ports..." << std::endl;
    }
    else
    {
        std::cout << "Searching for serial ports containing \"" << args.pattern << "\"" << std:: endl;
    }

    try
    {
        list_ports(args.pattern);
    }
    catch (const std::exception& ex)
    {
        std::cerr << "ERROR: " << ex.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "DONE!" << std::endl;

    exit(EXIT_SUCCESS);
}
