/**
 * @file fm_test.cpp
 * @author Yang Zhang
 * @copyright  Released under the terms of the BSD 3-Clause License
 * @date 2024
 */

#include "TimestampedFileManager.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
namespace fs = std::filesystem;

int main(int argc, char **argv)
{
    auto tempDir = fs::current_path() / "TelemetryManagerTest";
    fs::create_directories(tempDir);

    std::vector<std::string> timestamps = {"telemetry_2023-11-09T10:59:26Z.mcap", "telemetry_2023-11-09T11:01:13Z.mcap",
                                           "telemetry_2023-11-09T11:03:41Z.mcap", "telemetry_2023-11-14T13:35:07Z.mcap",
                                           "telemetry_2023-11-14T13:37:15Z.mcap", "telemetry_2023-11-14T13:38:10Z.mcap"};
    
    // generate 6 files with a total size of 90 Bytes
    for (auto &element : timestamps)
    {
        std::ofstream file(tempDir / element);
        std::string content = "Some data value"; // 15 Bytes
        file << content;
        std::cout << element << "file generated in " << tempDir.string() << std::endl;
    }

    std::string directory_path = tempDir.string();
    std::string file_suffix = ".mcap";
    std::string file_prefix = "telemetry_";
    std::string timestamp_format = "%Y-%m-%dT%H:%M:%SZ";
    long long max_size = 20;

    if (argc > 1)
    {
        try
        {
            max_size = std::stoll(argv[1]);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid argument: " << argv[1] << std::endl;
            return 1;
        }
        catch (const std::out_of_range &e)
        {
            std::cerr << "Value out of range: " << argv[1] << std::endl;
            return 1;
        }
    }
    auto fm_prt = std::make_shared<TimestampedFileManager>(directory_path, timestamp_format, max_size, file_prefix, file_suffix);
    fm_prt->deleteOldestFiles();

    return 0;
}