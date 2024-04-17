#include "TimestampedFileManager.hpp"

int main(int argc, char **argv)
{
    std::string directory_path = "place_holder";
    std::string file_suffix = "place_holder";
    std::string file_prefix = "place_holder";
    long long max_size = 1;
    auto filemanager = TimestampedFileManager(directory_path, file_suffix, file_prefix, max_size);
}