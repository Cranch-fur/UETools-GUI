#pragma once
#include "Utilities.h"

#include <filesystem>






class FileInstance
{
public:
    std::wstring _filePath;

    FileInstance(const std::string& filePath);
    FileInstance(const std::wstring& filePath);

    const bool Exists();

    const bool ReadText(std::string* outText);
    const bool SaveText(const std::string& text);

    const bool ReadLines(std::vector<std::string>* outLines);
    const bool SaveLines(const std::vector<std::string>& lines);

    const bool AppendLine(const std::string& line);
    const bool AppendLines(const std::vector<std::string>& lines);

    const bool Clear();
    const bool Destroy();

protected:
    const std::wstring GetAbsolutePath();
    const bool EnsureDirectoryExists();
};

