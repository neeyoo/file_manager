#include <iostream>
#include <map>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "TimestampedFileManager.hpp"

TimestampedFileManager::TimestampedFileManager(std::string directory_path, std::string file_suffix, std::string file_prefix, long long max_size)
    : _directory_path(directory_path),
      _file_suffix(file_suffix),
      _file_prefix(file_prefix),
      _max_size(max_size)
{
    std::cout << "[INFO] "
              << "TimestampedFileManager for ."
              << _file_suffix << " files with prefix of " << _file_prefix
              << "_ in the directory: " << _directory_path << " is created! \n"
              << "[INFO] "
              << "Maximum total size allowed in this drectory is: " << _max_size << " Bytes \n";
}

void TimestampedFileManager::deleteOldestFiles()
{
    retriveFiles();
}

std::vector<std::filesystem::path> TimestampedFileManager::retriveFiles()
{
    std::vector<std::filesystem::path> retrieved_files;
    std::multimap<std::string, std::filesystem::path> time_sorted_files;

    // retrive_files based on prefix, suffix and timestamp validation
    for (const auto &file : std::filesystem::directory_iterator(_directory_path))
    {
        auto timestamp = file.path().stem().string().substr(_file_prefix.length(), 20);
        if (file.path().extension() == _file_suffix &&
            file.path().stem().string().substr(0, _file_prefix.length()) == _file_prefix &&
            isValidDateFormat(timestamp, "%Y-%m-%dT%H:%M:%SZ"))
        {
            time_sorted_files.insert({timestamp, file.path()});
            retrieved_files.push_back(file.path());
        }
    }
}

void TimestampedFileManager::sortFilesByTimestamp(std::vector<std::filesystem::path> &files)
{
}

bool TimestampedFileManager::isValidDateFormat(const std::string &datestring, const std::string &format)
{
    std::tm time_info;
    std::istringstream time_stream(datestring);
    time_stream >> std::get_time(&time_info, format.c_str());

    // Check if parsing was successful and if there are no remaining characters in the stream
    return !time_stream.fail() && time_stream.eof();
}
