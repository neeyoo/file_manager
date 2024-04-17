#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

/// @brief
class TimestampedFileManager
{

public:
    /// @brief Constructor of TimestampedFileManager
    /// @param directory_path
    /// @param file_suffix
    /// @param max_size
    TimestampedFileManager(std::string directory_path, std::string file_suffix, std::string file_prefix, long long max_size);

    // virtual ~TimestampedFileManager();
    /// @brief Delete olders telemetry files if total file size exceed alowable size
    void deleteOldestFiles();

private:
    /// @brief Retrive files from a directory based on their file suffix
    /// @return retrived file paths in a vector container
    std::vector<std::filesystem::path> retriveFiles();

    /// @brief Sort files based on their timestamp infomation
    void sortFilesByTimestamp(std::vector<std::filesystem::path> &files);

    /// @brief
    /// @param datestring
    /// @param format
    /// @return
    bool isValidDateFormat(const std::string &datestring, const std::string &format);

    std::string _directory_path;
    std::string _file_suffix;
    std::string _file_prefix;
    long long _max_size;
};
