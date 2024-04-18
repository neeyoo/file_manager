/**
 * @file TimestampedFileManager.hpp
 * @author Yang Zhang
 * @copyright  Released under the terms of the BSD 3-Clause License
 * @date 2024
 */

#ifndef TIMESTAMPED_FILE_MANAGER_HPP
#define TIMESTAMPED_FILE_MANAGER_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <map>

/// @brief
class TimestampedFileManager
{

public:
    /// @brief Constructor of TimestampedFileManager
    /// @param directory_path Path to dicectory inculding files need to be managed
    /// @param timestamp_formate Format of timestamp in file's name
    /// @param max_size Maximum allowable size of managed files
    /// @param file_prefix Prefix of the file
    /// @param file_suffix Extension name of the file
    TimestampedFileManager(const std::string &directory_path, const std::string &timestamp_format,
                           const long long &max_size, const std::string &file_prefix,
                           const std::string &file_suffix);
    virtual ~TimestampedFileManager();

    /// @brief Delete olders telemetry files if total file size exceed alowable size
    void deleteOldestFiles();

private:
    /// @brief Retrive files from a directory based on the prefix, suffix and if have valid timestamp information
    /// @return retrived file paths in a multimap container in sorted order based on time key
    std::multimap<time_t, std::filesystem::path> retriveFiles();

    /// @brief Helper function to convert string type of timestamp to time_t
    /// @param time_string Input timestamp string
    /// @param result time_t conversion result modified by reference
    /// @return Bool value indicate if conversion is success
    bool timeStringToTime(const std::string &time_string, time_t &result);

    std::string _directory_path;
    std::string _timestamp_format;
    std::string _file_suffix;
    std::string _file_prefix;
    long long _max_size;
};

#endif