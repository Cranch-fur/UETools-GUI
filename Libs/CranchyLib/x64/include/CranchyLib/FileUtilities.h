#pragma once

#include <string>
#include <stdexcept>
#include <vector>
#include <windows.h>






class FileUtilities
{
public:
	static std::string ReadFileContents(const std::string& filePath);
    static std::string ReadFileContents(const std::wstring& filePath);
	static std::vector<std::string> ReadFileLines(const std::string& filePath);
    static std::vector<std::string> ReadFileLines(const std::wstring& filePath);

    static std::wstring ReadFileWContents(const std::string& filePath);
	static std::wstring ReadFileWContents(const std::wstring& filePath);
    static std::vector<std::wstring> ReadFileWLines(const std::string& filePath);
	static std::vector<std::wstring> ReadFileWLines(const std::wstring& filePath);


	static bool WriteFileContents(const std::string& filePath, const std::string& content);
    static bool WriteFileContents(const std::wstring& filePath, const std::string& content);

    static bool WriteFileWContents(const std::string& filePath, const std::wstring& content);
	static bool WriteFileWContents(const std::wstring& filePath, const std::wstring& content);






    template<typename Container>
    static bool WriteFileLines(const std::string& filePath, const Container& lines)
    {
        std::string content;
        bool first = true;


        for (const auto& line : lines)
        {
            if (!first)
                content.append("\n");
            content.append(line);
            first = false;
        }


        return WriteFileContents(filePath, content);
    }
    template<typename Container>
    static bool WriteFileLines(const std::wstring& filePath, const Container& lines)
    {
        return WriteFileLines(std::string(filePath.begin(), filePath.end()), lines);
    }


    template<typename Container>
    static bool WriteFileAllWLines(const std::string& filePath, const Container& lines)
    {
        std::wstring content;
        bool first = true;


        for (const auto& line : lines)
        {
            if (!first)
                content.append(L"\n");
            content.append(line);
            first = false;
        }


        return WriteFileWContents(filePath, content);
    }
    template<typename Container>
    static bool WriteFileAllWLines(const std::wstring& filePath, const Container& lines)
    {
        return WriteFileAllWLines(std::string(filePath.begin(), filePath.end()), lines);
    }
};

