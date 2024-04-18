#include <gtest/gtest.h>
#include "TimestampedFileManager.hpp"
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

// help function of changing a time_t type time to datetime in string
std::string timetToStringTimestamp(std::string timestampe_format, time_t time) {
    // Convert time_t to std::tm in UTC
    std::tm* currentTm = std::gmtime(&time);

    // Format the timestamp string
    std::stringstream ss;
    ss << std::put_time(currentTm, timestampe_format.c_str());

    return ss.str();
}

class TimestampedFileManagerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        tempDir = fs::temp_directory_path() / "TimestampedFileManagerTest";
        fs::create_directories(tempDir);

        // Get the current system time
        auto now = std::chrono::system_clock::now();
        // Convert the system time to time_t
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

        std::vector<std::string> filenames;

        for (int i = 0; i < 5; ++i)
        {
            auto time_to_change = currentTime + i * 1000;
            auto timestampe_string = timetToStringTimestamp(timestamp_format, time_to_change);
            filenames.push_back(file_prefix + timestampe_string + file_suffix);
        }
        // Create a temporary directory and populate it with files
        for (auto &element : filenames)
        {
            std::ofstream file(tempDir / element);
            std::string content = "Some data value"; //15 Bytes
            file << content;
        }
    }

    void TearDown() override
    {
        // Remove the temporary directory and its contents
        fs::remove_all(tempDir);
    }

    fs::path tempDir;
    std::string file_prefix = "telemetry_";
    std::string file_suffix = ".mcap";
    std::string timestamp_format = "%Y-%m-%dT%H:%M:%SZ";
};

class TimestampedFileManagerTest1 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        tempDir = fs::temp_directory_path() / "TimestampedFileManagerTest";
        fs::create_directories(tempDir);

        // Get the current system time
        auto now = std::chrono::system_clock::now();
        // Convert the system time to time_t
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

        std::vector<std::string> filenames;

        for (int i = 0; i < 5; ++i)
        {
            auto time_to_change = currentTime + i * 1000;
            auto timestampe_string = timetToStringTimestamp(timestamp_format, time_to_change);
            filenames.push_back(file_prefix + timestampe_string + file_suffix);
        }
        // Create a temporary directory and populate it with files
        for (auto &element : filenames)
        {
            std::ofstream file(tempDir / element);
            std::string content = "Some data value";
            file << content;
        }
    }

    void TearDown() override
    {
        // Remove the temporary directory and its contents
        fs::remove_all(tempDir);
    }

    fs::path tempDir;
    std::string file_prefix;
    std::string file_suffix = ".csv";
    std::string timestamp_format = "%Y-%b-%d %H:%M:%S";
};

class TimestampedFileManagerTest2 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        tempDir = fs::temp_directory_path() / "TimestampedFileManagerTest";
        fs::create_directories(tempDir);

        // Get the current system time
        auto now = std::chrono::system_clock::now();
        // Convert the system time to time_t
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

        std::vector<std::string> filenames;

        for (int i = 0; i < 5; ++i)
        {
            auto time_to_change = currentTime + i * 1000;
            auto timestampe_string = timetToStringTimestamp(timestamp_format, time_to_change);
            filenames.push_back(file_prefix + timestampe_string + file_suffix);
        }
        // Create a temporary directory and populate it with files
        for (auto &element : filenames)
        {
            std::ofstream file(tempDir / element);
            std::string content = "Some data value";
            file << content; // create file size of 15 Bytes
        }
    }

    void TearDown() override
    {
        // Remove the temporary directory and its contents
        fs::remove_all(tempDir);
    }

    fs::path tempDir;
    std::string file_prefix;
    std::string file_suffix;
    std::string timestamp_format = "%Y-%m-%dT%H:%M:%SZ";
};

// Test for .mcap datafiles with telemetry_ prefix and %Y-%m-%dT%H:%M:%SZ dateformat.
TEST_F(TimestampedFileManagerTest, DeleteMcapTelemetryYmdTHMSZ)
{
    long long max_bytes = 30; // Total size of 5 files is 75 bytes
    auto tsfm_ptr = std::make_unique<TimestampedFileManager>(tempDir, timestamp_format, max_bytes, file_prefix, file_suffix);
    tsfm_ptr->deleteOldestFiles();

    // Check that there are only 2 files remaining (total size = 30 bytes)
    int numRemainingFiles = 0;
    for (const auto& entry : fs::directory_iterator(tempDir)) {
        if (entry.path().extension() == file_suffix) {
            ++numRemainingFiles;
        }
    }
    ASSERT_EQ(numRemainingFiles, 2);
}

// Test for .csv datafiles with no prefix and %Y-%b-%d %H:%M:%S dateformat.
TEST_F(TimestampedFileManagerTest1, DeleteCsvYbdHMS)
{
    long long max_bytes = 30; // Total size of 5 files is 75 bytes
    auto tsfm_ptr = std::make_unique<TimestampedFileManager>(tempDir, timestamp_format, max_bytes, file_prefix, file_suffix);
    tsfm_ptr->deleteOldestFiles();

    // Check that there are only 2 files remaining (total size = 30 bytes)
    int numRemainingFiles = 0;
    for (const auto& entry : fs::directory_iterator(tempDir)) {
        if (entry.path().extension() == file_suffix) {
            ++numRemainingFiles;
        }
    }
    ASSERT_EQ(numRemainingFiles, 2);
}

// Test for datafiles with no prefix and extention of %Y-%b-%d %H:%M:%S dateformat.
TEST_F(TimestampedFileManagerTest2, DeleteYmdTHMSZ)
{
    long long max_bytes = 50; // Total size of 5 files is 75 bytes
    auto tsfm_ptr = std::make_unique<TimestampedFileManager>(tempDir, timestamp_format, max_bytes, file_prefix, file_suffix);
    tsfm_ptr->deleteOldestFiles();

    // Check that there are only 3 files remaining (total size = 45 bytes)
    int numRemainingFiles = 0;
    for (const auto& entry : fs::directory_iterator(tempDir)) {
        if (entry.path().extension() == file_suffix) {
            ++numRemainingFiles;
        }
    }
    ASSERT_EQ(numRemainingFiles, 3);
}