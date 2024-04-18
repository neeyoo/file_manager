/**
 * @file TimestampedFileManager.cpp
 * @author Yang Zhang
 * @copyright  Released under the terms of the BSD 3-Clause License
 * @date 2024
 */

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "TimestampedFileManager.hpp"

namespace fs = std::filesystem;

TimestampedFileManager::TimestampedFileManager(const std::string &directory_path, const std::string &timestamp_format,
                                               const long long &max_size, const std::string &file_prefix,
                                               const std::string &file_suffix)
    : _directory_path(directory_path),
      _timestamp_format(timestamp_format),
      _file_suffix(file_suffix),
      _file_prefix(file_prefix),
      _max_size(max_size)
{
    std::cout << "[INFO] "
              << "TimestampedFileManager for "
              << _file_suffix << " files with prefix of " << _file_prefix
              << " and timestamp format of " << _timestamp_format
              << " in the directory: " << _directory_path << " is created! \n"
              << "[INFO] "
              << "Maximum total size allowed in this drectory is: " << _max_size << " Bytes \n";
}

TimestampedFileManager::~TimestampedFileManager()
{
    std::cout << "[WARN] "
              << "TimestampedFileManager for "
              << _file_suffix << " files with prefix of " << _file_prefix
              << " in the directory: " << _directory_path << " is destroyed! \n";
}

void TimestampedFileManager::deleteOldestFiles()
{
    auto retrived_files = retriveFiles();
    // Calculate total size of files
    long long totalSize = 0;
    for (const auto &file : retrived_files)
    {
        totalSize += fs::file_size(file.second);
    }

    // Delete oldest files until total size is less than quota
    while (totalSize > _max_size && !retrived_files.empty())
    {
        size_t numFilesDeleted = 0;
        const fs::path &oldestFile = retrived_files.begin()->second;
        long long fileSize = fs::file_size(oldestFile);

        if (std::remove(oldestFile.c_str()) == 0)
        {
            std::cout << "[INFO] Deleted: " << oldestFile << " (" << fileSize << " bytes)" << std::endl;
            totalSize -= fileSize;
            ++numFilesDeleted;
            retrived_files.erase(retrived_files.begin());
        }
        else
        {
            std::cerr << "[ERROR] Error deleting file: " << oldestFile << std::endl;
            break;
        }
    }
}

std::multimap<time_t, fs::path> TimestampedFileManager::retriveFiles()
{
    std::multimap<time_t, fs::path> time_sorted_files;
    time_t file_time;

    // retrive_files based on prefix, suffix and timestamp validation
    for (const auto &file : fs::directory_iterator(_directory_path))
    {
        auto timestamp = file.path().stem().string().substr(_file_prefix.length());
        if (file.path().extension() == _file_suffix &&
            file.path().stem().string().substr(0, _file_prefix.length()) == _file_prefix &&
            timeStringToTime(timestamp, file_time))
        {
            time_sorted_files.insert({file_time, file.path()});
        }
    }

    return time_sorted_files;
}

bool TimestampedFileManager::timeStringToTime(const std::string &time_string, time_t &result)
{
    std::tm time_info;
    std::istringstream time_stream(time_string);
    time_stream >> std::get_time(&time_info, _timestamp_format.c_str());

    if (time_stream.fail())
    {
        std::cerr << "[ERROR] Failed to parse time string." << std::endl;
        return false;
    }
    else
    {
        time_t time = std::mktime(&time_info);

        if (time == -1)
        {
            std::cerr << "[ERROR] Failed to convert time." << std::endl;
            return false;
        }
        else
        {
            result = time;
            return true;
        }
    }
}