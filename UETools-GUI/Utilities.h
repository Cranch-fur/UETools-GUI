#pragma once
#include "definitions.h"
#include "FileInstance.h"

#include <Windows.h>
#include <wincodec.h>
#include <cwctype>
#include <regex>
#include <iostream>
#include <chrono>

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "windowscodecs.lib")

#ifdef ENABLE_LOGGING
#define LOG(Format, ...) \
		do \
		{ \
			std::string timeString = Utilities::Time::GetUtcDate(); \
			char buffer[SIZE_BUFFER_SEARCHFILTER]; \
			\
			std::snprintf(buffer, sizeof(buffer), "[%s] [%s:%d %s] " Format, \
				timeString.c_str(), \
				__FILE__, \
				__LINE__, \
				__FUNCTION__, \
				##__VA_ARGS__); \
			\
			printf("%s\n", buffer); \
			\
			FileInstance logFile(PATH_LOG_GENERAL); \
			logFile.AppendLine(buffer); \
		} while (0)
#else
#define LOG(Format, ...) do {} while (0)
#endif

#define EXCEPTION() Utilities::Exception::Handle(GetExceptionInformation(), __FUNCSIG__)






namespace Utilities
{
	class Environment
	{
	public:
		static std::string GetEnvironmentValue(const std::string& variableName);
		static std::string GetEnvironmentValue(const std::wstring& variableName);
		static std::string GetEnvironmentValue(const char* variableName);
		static std::string GetEnvironmentValue(const wchar_t* variableName);

		static std::wstring GetEnvironmentValueUtf16(const std::string& variableName);
		static std::wstring GetEnvironmentValueUtf16(const std::wstring& variableName);
		static std::wstring GetEnvironmentValueUtf16(const char* variableName);
		static std::wstring GetEnvironmentValueUtf16(const wchar_t* variableName);

		static std::string GetExecutablePath();
		static std::wstring GetExecutablePathUtf16();

		static std::string GetExecutableName(bool includeFileExtension);
		static std::wstring GetExecutableNameUtf16(bool includeFileExtension);

		static std::string GetExecutableDirectory();
		static std::wstring GetExecutableDirectoryUtf16();

		static std::string GetProgramFilesDirectory();
		static std::wstring GetProgramFilesDirectoryUtf16();

		static std::string GetProgramFilesX86Directory();
		static std::wstring GetProgramFilesX86DirectoryUtf16();

		static std::string GetUserDirectory();
		static std::wstring GetUserDirectoryUtf16();

		static std::string GetDesktopDirectory();
		static std::wstring GetDesktopDirectoryUtf16();

		static std::string GetDownloadsDirectory();
		static std::wstring GetDownloadsDirectoryUtf16();

		static std::string GetDocumentsDirectory();
		static std::wstring GetDocumentsDirectoryUtf16();

		static std::string GetPicturesDirectory();
		static std::wstring GetPicturesDirectoryUtf16();

		static std::string GetVideosDirectory();
		static std::wstring GetVideosDirectoryUtf16();

		static std::string GetMusicDirectory();
		static std::wstring GetMusicDirectoryUtf16();

		static std::string GetAppDataLocalDirectory();
		static std::wstring GetAppDataLocalDirectoryUtf16();

		static std::string GetAppDataLocalLowDirectory();
		static std::wstring GetAppDataLocalLowDirectoryUtf16();

		static std::string GetAppDataRoamingDirectory();
		static std::wstring GetAppDataRoamingDirectoryUtf16();

		static std::string GetSystemPath();
		static std::wstring GetSystemPathUtf16();

		static std::string GetSystemDrive();
		static std::wstring GetSystemDriveUtf16();
	};




	class Console
	{
	public:
		static void Create(const std::string& title, bool redirectStreams = false);
		static void Create(const std::wstring& title, bool redirectStreams = false);
		static void Create(const char* title, bool redirectStreams = false);
		static void Create(const wchar_t* title, bool redirectStreams = false);
		static void Create(bool redirectStreams = false);

		static void SetBufferSize(short newBufferSize = SHRT_MAX);

		static void Clear();

		static void EncodingUTF8(); // Universal
		static void Encoding1252(); // Windows EN
		static void Encoding1251(); // Windows RU
		static void Encoding866();  // DOS
		static void Encoding437();  // IBM PC
	};




	class CommandLine
	{
	public:
		static std::string Get();
		static std::wstring GetUtf16();

		static std::vector<std::string> GetArguments();
		static std::vector<std::wstring> GetArgumentsUtf16();

		static int Count();

		static bool HasArgument(const std::string& argument);
		static bool HasArgument(const std::wstring& argument);
		static bool HasArgument(const char* argument);
		static bool HasArgument(const wchar_t* argument);
	};




	class Clipboard
	{
	public:
		static std::string GetText();
		static std::wstring GetTextUtf16();

		static bool SetText(const std::string& string);
		static bool SetText(const std::wstring& wString);
		static bool SetText(const char* cString);
		static bool SetText(const wchar_t* wcString);

		static bool Contains(const std::string& substring);
		static bool Contains(const std::wstring& substring);
		static bool Contains(const char* substring);
		static bool Contains(const wchar_t* substring);

		static bool ContainsRegex(const std::string& regexPattern);
		static bool ContainsRegex(const std::wstring& regexPattern);
		static bool ContainsRegex(const char* regexPattern);
		static bool ContainsRegex(const wchar_t* regexPattern);
	};




	class Message
	{
	public:
		enum class E_MessageResult
		{
			OK,
			Cancel,
			Abort,
			Retry,
			Ignore,
			Yes,
			No,
			Timeout,
			Unknown
		};

		enum class E_Buttons : UINT
		{
			OK = MB_OK,
			OKCancel = MB_OKCANCEL,
			AbortRetryIgnore = MB_ABORTRETRYIGNORE,
			YesNoCancel = MB_YESNOCANCEL,
			YesNo = MB_YESNO,
			RetryCancel = MB_RETRYCANCEL,
			CancelTryContinue = MB_CANCELTRYCONTINUE
		};

		enum class E_Icon : UINT
		{
			None = 0,
			Error = MB_ICONERROR,
			Question = MB_ICONQUESTION,
			Warning = MB_ICONWARNING,
			Information = MB_ICONINFORMATION
		};

		enum class E_DefaultButton : UINT
		{
			Button1 = MB_DEFBUTTON1,
			Button2 = MB_DEFBUTTON2,
			Button3 = MB_DEFBUTTON3,
			Button4 = MB_DEFBUTTON4
		};


		/* HWND, title, message, type (buttons/icon/defaultButton). */
		static E_MessageResult Show(HWND hwndOwner, const std::string& title, const std::string& message, E_Buttons buttons = E_Buttons::OK, E_Icon icon = E_Icon::None, E_DefaultButton defaultButton = E_DefaultButton::Button1);
		static E_MessageResult Show(HWND hwndOwner, const std::wstring& title, const std::wstring& message, E_Buttons buttons = E_Buttons::OK, E_Icon icon = E_Icon::None, E_DefaultButton defaultButton = E_DefaultButton::Button1);
		static E_MessageResult Show(HWND hwndOwner, const char* title, const char* message, E_Buttons buttons = E_Buttons::OK, E_Icon icon = E_Icon::None, E_DefaultButton defaultButton = E_DefaultButton::Button1);
		static E_MessageResult Show(HWND hwndOwner, const wchar_t* title, const wchar_t* message, E_Buttons buttons = E_Buttons::OK, E_Icon icon = E_Icon::None, E_DefaultButton defaultButton = E_DefaultButton::Button1);

		/* title, message, type (buttons/icon/defaultButton). */
		static E_MessageResult Show(const std::string& title, const std::string& message, E_Buttons buttons = E_Buttons::OK, E_Icon icon = E_Icon::None, E_DefaultButton defaultButton = E_DefaultButton::Button1);
		static E_MessageResult Show(const std::wstring& title, const std::wstring& message, E_Buttons buttons = E_Buttons::OK, E_Icon icon = E_Icon::None, E_DefaultButton defaultButton = E_DefaultButton::Button1);
		static E_MessageResult Show(const char* title, const char* message, E_Buttons buttons = E_Buttons::OK, E_Icon icon = E_Icon::None, E_DefaultButton defaultButton = E_DefaultButton::Button1);
		static E_MessageResult Show(const wchar_t* title, const wchar_t* message, E_Buttons buttons = E_Buttons::OK, E_Icon icon = E_Icon::None, E_DefaultButton defaultButton = E_DefaultButton::Button1);

		/* message, type (buttons/icon/defaultButton). */
		static E_MessageResult Show(const std::string& message, E_Buttons buttons = E_Buttons::OK, E_Icon icon = E_Icon::None, E_DefaultButton defaultButton = E_DefaultButton::Button1);
		static E_MessageResult Show(const std::wstring& message, E_Buttons buttons = E_Buttons::OK, E_Icon icon = E_Icon::None, E_DefaultButton defaultButton = E_DefaultButton::Button1);
		static E_MessageResult Show(const char* message, E_Buttons buttons = E_Buttons::OK, E_Icon icon = E_Icon::None, E_DefaultButton defaultButton = E_DefaultButton::Button1);
		static E_MessageResult Show(const wchar_t* message, E_Buttons buttons = E_Buttons::OK, E_Icon icon = E_Icon::None, E_DefaultButton defaultButton = E_DefaultButton::Button1);
	};




	class String
	{
	public:
		static std::string ToString(const std::wstring& wideString);
		static std::string ToString(const char* cString);
		static std::string ToString(const wchar_t* wcString);

		static std::wstring ToWString(const std::string& string);
		static std::wstring ToWString(const char* cString);
		static std::wstring ToWString(const wchar_t* wcString);

		static bool ToInt8(const std::string& string, int8_t* outValue);
		static bool ToInt8(const std::wstring& wString, int8_t* outValue);
		static bool ToInt8(const char* cString, int8_t* outValue);
		static bool ToInt8(const wchar_t* wcString, int8_t* outValue);

		static bool ToInt16(const std::string& string, int16_t* outValue);
		static bool ToInt16(const std::wstring& wString, int16_t* outValue);
		static bool ToInt16(const char* cString, int16_t* outValue);
		static bool ToInt16(const wchar_t* wcString, int16_t* outValue);

		static bool ToInt32(const std::string& string, int32_t* outValue);
		static bool ToInt32(const std::wstring& wString, int32_t* outValue);
		static bool ToInt32(const char* cString, int32_t* outValue);
		static bool ToInt32(const wchar_t* wcString, int32_t* outValue);

		static bool ToInt64(const std::string& string, int64_t* outValue);
		static bool ToInt64(const std::wstring& wString, int64_t* outValue);
		static bool ToInt64(const char* cString, int64_t* outValue);
		static bool ToInt64(const wchar_t* wcString, int64_t* outValue);

		static bool ToFloat(const std::string& string, float* outValue);
		static bool ToFloat(const std::wstring& wString, float* outValue);
		static bool ToFloat(const char* cString, float* outValue);
		static bool ToFloat(const wchar_t* wcString, float* outValue);

		static bool ToDouble(const std::string& string, double* outValue);
		static bool ToDouble(const std::wstring& wString, double* outValue);
		static bool ToDouble(const char* cString, double* outValue);
		static bool ToDouble(const wchar_t* wcString, double* outValue);


		static std::string ToLowerCase(std::string string);
		static std::wstring ToLowerCase(std::wstring wString);
		static std::string ToLowerCase(const char* cString);
		static std::wstring ToLowerCase(const wchar_t* wcString);

		static std::string ToUpperCase(std::string string);
		static std::wstring ToUpperCase(std::wstring wString);
		static std::string ToUpperCase(const char* cString);
		static std::wstring ToUpperCase(const wchar_t* wcString);


		static std::string Replace(std::string string, const std::string& from, const std::string& to);
		static std::string Replace(const std::string& string, const std::string& from, const std::wstring& to);
		static std::string Replace(const std::string& string, const std::wstring& from, const std::string& to);
		static std::string Replace(const std::string& string, const std::wstring& from, const std::wstring& to);
		static std::string Replace(const char* cString, const char* from, const char* to);

		static std::wstring Replace(std::wstring wString, const std::wstring& from, const std::wstring& to);
		static std::wstring Replace(const std::wstring& wString, const std::wstring& from, const std::string& to);
		static std::wstring Replace(const std::wstring& wString, const std::string& from, const std::wstring& to);
		static std::wstring Replace(const std::wstring& wString, const std::string& from, const std::string& to);
		static std::wstring Replace(const wchar_t* wcString, const wchar_t* from, const wchar_t* to);


		static std::string ReplaceFirstOf(std::string string, const std::string& from, const std::string& to);
		static std::string ReplaceFirstOf(const std::string& string, const std::string& from, const std::wstring& to);
		static std::string ReplaceFirstOf(const std::string& string, const std::wstring& from, const std::string& to);
		static std::string ReplaceFirstOf(const std::string& string, const std::wstring& from, const std::wstring& to);
		static std::string ReplaceFirstOf(const char* cString, const char* from, const char* to);

		static std::wstring ReplaceFirstOf(std::wstring wString, const std::wstring& from, const std::wstring& to);
		static std::wstring ReplaceFirstOf(const std::wstring& wString, const std::wstring& from, const std::string& to);
		static std::wstring ReplaceFirstOf(const std::wstring& wString, const std::string& from, const std::wstring& to);
		static std::wstring ReplaceFirstOf(const std::wstring& wString, const std::string& from, const std::string& to);
		static std::wstring ReplaceFirstOf(const wchar_t* wcString, const wchar_t* from, const wchar_t* to);


		static std::string ReplaceLastOf(std::string string, const std::string& from, const std::string& to);
		static std::string ReplaceLastOf(const std::string& string, const std::string& from, const std::wstring& to);
		static std::string ReplaceLastOf(const std::string& string, const std::wstring& from, const std::string& to);
		static std::string ReplaceLastOf(const std::string& string, const std::wstring& from, const std::wstring& to);
		static std::string ReplaceLastOf(const char* cString, const char* from, const char* to);

		static std::wstring ReplaceLastOf(std::wstring wString, const std::wstring& from, const std::wstring& to);
		static std::wstring ReplaceLastOf(const std::wstring& wString, const std::wstring& from, const std::string& to);
		static std::wstring ReplaceLastOf(const std::wstring& wString, const std::string& from, const std::wstring& to);
		static std::wstring ReplaceLastOf(const std::wstring& wString, const std::string& from, const std::string& to);
		static std::wstring ReplaceLastOf(const wchar_t* wcString, const wchar_t* from, const wchar_t* to);


		static bool Contains(const std::string& string, const std::string& substring, bool useCase = true);
		static bool Contains(const std::string& string, const std::wstring& substring, bool useCase = true);
		static bool Contains(const char* cString, const char* substring, bool useCase = true);

		static bool Contains(const std::wstring& wString, const std::wstring& substring, bool useCase = true);
		static bool Contains(const std::wstring& wString, const std::string& substring, bool useCase = true);
		static bool Contains(const wchar_t* wcString, const wchar_t* substring, bool useCase = true);


		static bool StartsWith(const std::string& string, const std::string& substring, bool useCase = true);
		static bool StartsWith(const std::string& string, const std::wstring& substring, bool useCase = true);
		static bool StartsWith(const char* cString, const char* substring, bool useCase = true);

		static bool StartsWith(const std::wstring& wString, const std::wstring& substring, bool useCase = true);
		static bool StartsWith(const std::wstring& wString, const std::string& substring, bool useCase = true);
		static bool StartsWith(const wchar_t* wcString, const wchar_t* substring, bool useCase = true);


		static bool EndsWith(const std::string& string, const std::string& substring, bool useCase = true);
		static bool EndsWith(const std::string& string, const std::wstring& substring, bool useCase = true);
		static bool EndsWith(const char* cString, const char* substring, bool useCase = true);

		static bool EndsWith(const std::wstring& wString, const std::wstring& substring, bool useCase = true);
		static bool EndsWith(const std::wstring& wString, const std::string& substring, bool useCase = true);
		static bool EndsWith(const wchar_t* wcString, const wchar_t* substring, bool useCase = true);


		static std::vector<std::string> Split(const std::string& string, const char& separator, bool removeSeparatorSpaces = true);
		static std::vector<std::string> Split(const std::wstring& wString, const char& separator, bool removeSeparatorSpaces = true);
		static std::vector<std::string> Split(const char* cString, const char& separator, bool removeSeparatorSpaces = true);
		static std::vector<std::string> Split(const wchar_t* wcString, const char& separator, bool removeSeparatorSpaces = true);

		static std::vector<std::wstring> Split(const std::string& string, const wchar_t& separator, bool removeSeparatorSpaces = true);
		static std::vector<std::wstring> Split(const std::wstring& wideString, const wchar_t& separator, bool removeSeparatorSpaces = true);
		static std::vector<std::wstring> Split(const char* cString, const wchar_t& separator, bool removeSeparatorSpaces = true);
		static std::vector<std::wstring> Split(const wchar_t* wcString, const wchar_t& separator, bool removeSeparatorSpaces = true);


		static std::string Reverse(std::string string);
		static std::wstring Reverse(std::wstring wString);
		static std::string Reverse(const char* cString);
		static std::wstring Reverse(const wchar_t* wcString);


		static bool IsNumeric(const std::string& string);
		static bool IsNumeric(const std::wstring& wString);
		static bool IsNumeric(const char* cString);
		static bool IsNumeric(const wchar_t* wcString);
	};




	class Directory
	{
	public:
		static bool Exists(const std::string& directoryPath);
		static bool Exists(const std::wstring& directoryPath);

		static bool Create(const std::string& directoryPath);
		static bool Create(const std::wstring& directoryPath);

		static bool Destroy(const std::string& directoryPath, bool deleteContents);
		static bool Destroy(const std::wstring& directoryPath, bool deleteContents);
	};




	class File
	{
	public:
		static bool Exists(const std::string& filePath);
		static bool Exists(const std::wstring& filePath);


		static bool ReadText(const std::string& filePath, std::string* outContents);
		static bool ReadText(const std::wstring& filePath, std::string* outContents);
		static bool ReadTextUtf16(const std::string& filePath, std::wstring* outContents);
		static bool ReadTextUtf16(const std::wstring& filePath, std::wstring* outContents);


		static bool ReadLines(const std::string& filePath, std::vector<std::string>* outLines);
		static bool ReadLines(const std::wstring& filePath, std::vector<std::string>* outLines);
		static bool ReadLinesUtf16(const std::string& filePath, std::vector<std::wstring>* outLines);
		static bool ReadLinesUtf16(const std::wstring& filePath, std::vector<std::wstring>* outLines);


		static bool WriteText(const std::string& filePath, const std::string& text);
		static bool WriteText(const std::wstring& filePath, const std::string& text);
		static bool WriteTextUtf16(const std::string& filePath, const std::wstring& text);
		static bool WriteTextUtf16(const std::wstring& filePath, const std::wstring& text);


		static bool WriteLines(const std::string& filePath, const std::vector<std::string>& lines);
		static bool WriteLines(const std::wstring& filePath, const std::vector<std::string>& lines);
		static bool WriteLinesUtf16(const std::string& filePath, const std::vector<std::wstring>& lines);
		static bool WriteLinesUtf16(const std::wstring& filePath, const std::vector<std::wstring>& lines);


		static bool AppendText(const std::string& filePath, const std::string& text);
		static bool AppendText(const std::wstring& filePath, const std::string& text);
		static bool AppendTextUtf16(const std::string& filePath, const std::wstring& text);
		static bool AppendTextUtf16(const std::wstring& filePath, const std::wstring& text);


		static bool AppendLine(const std::string& filePath, const std::string& line);
		static bool AppendLine(const std::wstring& filePath, const std::string& line);
		static bool AppendLineUtf16(const std::string& filePath, const std::wstring& line);
		static bool AppendLineUtf16(const std::wstring& filePath, const std::wstring& line);


		static bool AppendLines(const std::string& filePath, const std::vector<std::string>& lines);
		static bool AppendLines(const std::wstring& filePath, const std::vector<std::string>& lines);
		static bool AppendLinesUtf16(const std::string& filePath, const std::vector<std::wstring>& lines);
		static bool AppendLinesUtf16(const std::wstring& filePath, const std::vector<std::wstring>& lines);


		static bool Destroy(const std::string& filePath);
		static bool Destroy(const std::wstring& filePath);
	};




	class Time
	{
	public:
		static uint64_t GetUnixTimestamp();

		static std::string GetUtcDate(const uint64_t& timestamp);
		static std::string GetUtcDate();
	};




	class Resources
	{
	public:
		static bool LoadImageResource(const int32_t resourceId, const std::wstring& resourceType, std::vector<uint8_t>* outPixels, int32_t* outWidth, int32_t* outHeight);
		static bool LoadImageResource(const int32_t resourceId, const std::string& resourceType, std::vector<uint8_t>* outPixels, int32_t* outWidth, int32_t* outHeight);

		static bool LoadPNG(const int32_t resourceId, std::vector<uint8_t>* outPixels, int32_t* outWidth, int32_t* outHeight);
		static bool LoadJPG(const int32_t resourceId, std::vector<uint8_t>* outPixels, int32_t* outWidth, int32_t* outHeight);
		static bool LoadBMP(const int32_t resourceId, std::vector<uint8_t>* outPixels, int32_t* outWidth, int32_t* outHeight);
		static bool LoadGIF(const int32_t resourceId, std::vector<uint8_t>* outPixels, int32_t* outWidth, int32_t* outHeight);
		static bool LoadTIFF(const int32_t resourceId, std::vector<uint8_t>* outPixels, int32_t* outWidth, int32_t* outHeight);
		static bool LoadICO(const int32_t resourceId, std::vector<uint8_t>* outPixels, int32_t* outWidth, int32_t* outHeight);
	};




	class Exception
	{
	public:
		static LONG Handle(LPEXCEPTION_POINTERS exceptionInfo, const char* title);
	};




	namespace Memory
	{
		static HMODULE GetLocalModule();
		static HMODULE GetProcessModule();




		class Internal // Functions within the class allows to manipulate memory of process program is running in.
		{
		public:
			/**
			* @brief Determines whether a given pointer refers to a valid, committed, and readable (or executable) memory region.
			* @param memoryPtr - Pointer to the memory location to check.
			* @return true if the region is committed, and has read or execute+read permissions; false otherwise.
			*/
			static bool IsValidPtr(const void* memoryPtr);
			/**
			* @brief Determines whether a given memory address refers to a valid, committed, and readable (or executable) memory region.
			* @param memoryAddress - Address of the memory location to check.
			* @return true if the region is committed, and has read or execute+read permissions; false otherwise.
			*/
			static bool IsValidAddress(uintptr_t memoryAddress);

			/**
			* @brief Adds a byte offset to a base memory address and verifies that the resulting address range is readable.
			* @param memoryPtr - Pointer to the starting memory location to which the offset will be added.
			* @param offset - The number of bytes to add to the base address.
			* @return The new valid pointer to the memory location if both the beginning and end of the target region are readable;
			*         otherwise returns 'nullptr' to indicate an invalid or unreadable address.
			*/
			static void* PtrAddOffset(const void* memoryPtr, size_t offset);
			/**
			* @brief Adds a byte offset to a base memory address and verifies that the resulting address range is readable.
			* @param memoryAddress - Address of the memory location to which the offset will be added.
			* @param offset - The number of bytes to add to the base address.
			* @return The new valid pointer to the memory location if both the beginning and end of the target region are readable;
			*         otherwise returns 'nullptr' to indicate an invalid or unreadable address.
			*/
			static void* PtrAddOffset(uintptr_t memoryAddress, size_t offset);

			/**
			* @brief Adds a byte offset to a base memory address and verifies that the resulting address range is readable.
			* @param memoryPtr - Pointer to the starting memory location to which the offset will be added.
			* @param offset - The number of bytes to add to the base address.
			* @return The new valid memory address if both the beginning and end of the target region are readable;
			*         otherwise returns '0x0' to indicate an invalid or unreadable address.
			*/
			static uintptr_t AddressAddOffset(const void* memoryPtr, size_t offset);
			/**
			* @brief Adds a byte offset to a base memory address and verifies that the resulting address range is readable.
			* @param memoryAddress - Address of the memory location to which the offset will be added.
			* @param offset - The number of bytes to add to the base address.
			* @return The new valid memory address if both the beginning and end of the target region are readable;
			*         otherwise returns '0x0' to indicate an invalid or unreadable address.
			*/
			static uintptr_t AddressAddOffset(uintptr_t memoryAddress, size_t offset);

			/**
			* @brief Adds a byte offset to a base memory address, verifies readability, and dereferences it to read the next pointer.
			* @param memoryPtr - Pointer to the starting memory location.
			* @param offset - The number of bytes to add to the base address before dereferencing (default is 0).
			* @return The new valid pointer read from the memory location;
			*         otherwise returns 'nullptr' to indicate an invalid/unreadable address.
			*/
			static void* PtrDereference(const void* memoryPtr, size_t offset);
			/**
			* @brief Adds a byte offset to a base memory address, verifies readability, and dereferences it to read the next pointer.
			* @param memoryAddress - Address of the memory location.
			* @param offset - The number of bytes to add to the base address before dereferencing (default is 0).
			* @return The new valid pointer read from the memory location;
			*         otherwise returns 'nullptr' to indicate an invalid/unreadable address.
			*/
			static void* PtrDereference(uintptr_t memoryAddress, size_t offset);

			/**
			* @brief Adds a byte offset to a base memory address, verifies readability, and dereferences it to read the next pointer.
			* @param memoryPtr - Pointer to the starting memory location.
			* @param offset - The number of bytes to add to the base address before dereferencing (default is 0).
			* @return The new valid memory address read from the memory location;
			*         otherwise returns '0x0' to indicate an invalid/unreadable address.
			*/
			static uintptr_t AddressDereference(const void* memoryPtr, size_t offset);
			/**
			* @brief Adds a byte offset to a base memory address, verifies readability, and dereferences it to read the next pointer.
			* @param memoryAddress - Address of the memory location.
			* @param offset - The number of bytes to add to the base address before dereferencing (default is 0).
			* @return The new valid memory address read from the memory location;
			*         otherwise returns '0x0' to indicate an invalid/unreadable address.
			*/
			static uintptr_t AddressDereference(uintptr_t memoryAddress, size_t offset);

			/**
			* @brief Follows a chain of pointers starting from a base address, applying a sequence of offsets.
			* @param memoryPtr - Pointer to the starting memory location from which the pointer chain will be resolved.
			* @return The new valid memory address if pointer chain was successfully resolved and final destination was reached;
			*         otherwise returns 'nullptr' to indicate an invalid or unreadable address.
			*/
			static void* PtrFollowPointerChain(const void* memoryPtr, const std::vector<uintptr_t>& memoryOffsets);
			/**
			* @brief Follows a chain of pointers starting from a base address, applying a sequence of offsets.
			* @param memoryAddress - Address of the memory location from which the pointer chain will be resolved.
			* @return The new valid memory address if pointer chain was successfully resolved and final destination was reached;
			*         otherwise returns '0x0' to indicate an invalid or unreadable address.
			*/
			static uintptr_t AddressFollowPointerChain(uintptr_t memoryAddress, const std::vector<uintptr_t>& memoryOffsets);




			/* For when 'memoryAddress' contains the actual value. */
			static bool GetBool(const void* memoryPtr);
			static bool GetBool(uintptr_t memoryAddress);

			static bool SetBool(const void* memoryPtr, bool newValue);
			static bool SetBool(uintptr_t memoryAddress, bool newValue);

			static bool PatchBool(const void* memoryPtr, bool from, bool to);
			static bool PatchBool(uintptr_t memoryAddress, bool from, bool to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static bool IndirectGetBool(const void* memoryPtr);
			static bool IndirectGetBool(uintptr_t memoryAddress);

			static bool IndirectSetBool(const void* memoryPtr, bool newValue);
			static bool IndirectSetBool(uintptr_t memoryAddress, bool newValue);

			static bool IndirectPatchBool(const void* memoryPtr, bool from, bool to);
			static bool IndirectPatchBool(uintptr_t memoryAddress, bool from, bool to);




			/* For when 'memoryAddress' contains the actual value. */
			static int8_t GetInt8(const void* memoryPtr);
			static int8_t GetInt8(uintptr_t memoryAddress);

			static bool   SetInt8(const void* memoryPtr, int8_t newValue);
			static bool   SetInt8(uintptr_t memoryAddress, int8_t newValue);

			static bool   PatchInt8(const void* memoryPtr, int8_t from, int8_t to);
			static bool   PatchInt8(uintptr_t memoryAddress, int8_t from, int8_t to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static int8_t IndirectGetInt8(const void* memoryPtr);
			static int8_t IndirectGetInt8(uintptr_t memoryAddress);

			static bool   IndirectSetInt8(const void* memoryPtr, int8_t newValue);
			static bool   IndirectSetInt8(uintptr_t memoryAddress, int8_t newValue);

			static bool   IndirectPatchInt8(const void* memoryPtr, int8_t from, int8_t to);
			static bool   IndirectPatchInt8(uintptr_t memoryAddress, int8_t from, int8_t to);




			/* For when 'memoryAddress' contains the actual value. */
			static int16_t GetInt16(const void* memoryPtr);
			static int16_t GetInt16(uintptr_t memoryAddress);

			static bool    SetInt16(const void* memoryPtr, int16_t newValue);
			static bool    SetInt16(uintptr_t memoryAddress, int16_t newValue);

			static bool    PatchInt16(const void* memoryPtr, int16_t from, int16_t to);
			static bool    PatchInt16(uintptr_t memoryAddress, int16_t from, int16_t to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static int16_t IndirectGetInt16(const void* memoryPtr);
			static int16_t IndirectGetInt16(uintptr_t memoryAddress);

			static bool    IndirectSetInt16(const void* memoryPtr, int16_t newValue);
			static bool    IndirectSetInt16(uintptr_t memoryAddress, int16_t newValue);

			static bool    IndirectPatchInt16(const void* memoryPtr, int16_t from, int16_t to);
			static bool    IndirectPatchInt16(uintptr_t memoryAddress, int16_t from, int16_t to);




			/* For when 'memoryAddress' contains the actual value. */
			static int32_t GetInt32(const void* memoryPtr);
			static int32_t GetInt32(uintptr_t memoryAddress);

			static bool    SetInt32(const void* memoryPtr, int32_t newValue);
			static bool    SetInt32(uintptr_t memoryAddress, int32_t newValue);

			static bool    PatchInt32(const void* memoryPtr, int32_t from, int32_t to);
			static bool    PatchInt32(uintptr_t memoryAddress, int32_t from, int32_t to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static int32_t IndirectGetInt32(const void* memoryPtr);
			static int32_t IndirectGetInt32(uintptr_t memoryAddress);

			static bool	   IndirectSetInt32(const void* memoryPtr, int32_t newValue);
			static bool	   IndirectSetInt32(uintptr_t memoryAddress, int32_t newValue);

			static bool    IndirectPatchInt32(const void* memoryPtr, int32_t from, int32_t to);
			static bool    IndirectPatchInt32(uintptr_t memoryAddress, int32_t from, int32_t to);




			/* For when 'memoryAddress' contains the actual value. */
			static int64_t GetInt64(const void* memoryPtr);
			static int64_t GetInt64(uintptr_t memoryAddress);

			static bool    SetInt64(const void* memoryPtr, int64_t newValue);
			static bool    SetInt64(uintptr_t memoryAddress, int64_t newValue);

			static bool    PatchInt64(const void* memoryPtr, int64_t from, int64_t to);
			static bool    PatchInt64(uintptr_t memoryAddress, int64_t from, int64_t to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static int64_t IndirectGetInt64(const void* memoryPtr);
			static int64_t IndirectGetInt64(uintptr_t memoryAddress);

			static bool    IndirectSetInt64(const void* memoryPtr, int64_t newValue);
			static bool    IndirectSetInt64(uintptr_t memoryAddress, int64_t newValue);

			static bool    IndirectPatchInt64(const void* memoryPtr, int64_t from, int64_t to);
			static bool    IndirectPatchInt64(uintptr_t memoryAddress, int64_t from, int64_t to);




			/* For when 'memoryAddress' contains the actual value. */
			static float GetFloat(const void* memoryPtr);
			static float GetFloat(uintptr_t memoryAddress);

			static bool  SetFloat(const void* memoryPtr, float newValue);
			static bool  SetFloat(uintptr_t memoryAddress, float newValue);

			static bool  PatchFloat(const void* memoryPtr, float from, float to);
			static bool  PatchFloat(uintptr_t memoryAddress, float from, float to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static float IndirectGetFloat(const void* memoryPtr);
			static float IndirectGetFloat(uintptr_t memoryAddress);

			static bool  IndirectSetFloat(const void* memoryPtr, float newValue);
			static bool  IndirectSetFloat(uintptr_t memoryAddress, float newValue);

			static bool  IndirectPatchFloat(const void* memoryPtr, float from, float to);
			static bool  IndirectPatchFloat(uintptr_t memoryAddress, float from, float to);




			/* For when 'memoryAddress' contains the actual value. */
			static double GetDouble(const void* memoryPtr);
			static double GetDouble(uintptr_t memoryAddress);

			static bool   SetDouble(const void* memoryPtr, double newValue);
			static bool   SetDouble(uintptr_t memoryAddress, double newValue);

			static bool   PatchDouble(const void* memoryPtr, double from, double to);
			static bool   PatchDouble(uintptr_t memoryAddress, double from, double to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static double IndirectGetDouble(const void* memoryPtr);
			static double IndirectGetDouble(uintptr_t memoryAddress);

			static bool   IndirectSetDouble(const void* memoryPtr, double newValue);
			static bool   IndirectSetDouble(uintptr_t memoryAddress, double newValue);

			static bool   IndirectPatchDouble(const void* memoryPtr, double from, double to);
			static bool   IndirectPatchDouble(uintptr_t memoryAddress, double from, double to);




			/* For when 'memoryAddress' contains the actual value. */
			static std::string GetString(const void* memoryPtr);
			static std::string GetString(const void* memoryPtr, size_t maxLength);
			static std::string GetString(uintptr_t memoryAddress);
			static std::string GetString(uintptr_t memoryAddress, size_t maxLength);

			static bool		   SetString(const void* memoryPtr, const std::string& newValue);
			static bool		   SetString(uintptr_t memoryAddress, const std::string& newValue);

			static bool		   PatchString(const void* memoryPtr, const std::string& from, const std::string& to);
			static bool		   PatchString(uintptr_t memoryAddress, const std::string& from, const std::string& to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static std::string IndirectGetString(const void* memoryPtr);
			static std::string IndirectGetString(const void* memoryPtr, size_t maxLength);
			static std::string IndirectGetString(uintptr_t memoryAddress);
			static std::string IndirectGetString(uintptr_t memoryAddress, size_t maxLength);

			static bool		   IndirectSetString(const void* memoryPtr, const std::string& newValue);
			static bool		   IndirectSetString(uintptr_t memoryAddress, const std::string& newValue);

			static bool		   IndirectPatchString(const void* memoryPtr, const std::string& from, const std::string& to);
			static bool		   IndirectPatchString(uintptr_t memoryAddress, const std::string& from, const std::string& to);


			/* For when 'memoryAddress' contains the actual value. */
			static std::wstring GetWString(const void* memoryPtr);
			static std::wstring GetWString(const void* memoryPtr, size_t maxLength);
			static std::wstring GetWString(uintptr_t memoryAddress);
			static std::wstring GetWString(uintptr_t memoryAddress, size_t maxLength);

			static bool			SetWString(const void* memoryPtr, const std::wstring& newValue);
			static bool			SetWString(uintptr_t memoryAddress, const std::wstring& newValue);

			static bool			PatchWString(const void* memoryPtr, const std::wstring& from, const std::wstring& to);
			static bool			PatchWString(uintptr_t memoryAddress, const std::wstring& from, const std::wstring& to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static std::wstring IndirectGetWString(const void* memoryPtr);
			static std::wstring IndirectGetWString(const void* memoryPtr, size_t maxLength);
			static std::wstring IndirectGetWString(uintptr_t memoryAddress);
			static std::wstring IndirectGetWString(uintptr_t memoryAddress, size_t maxLength);

			static bool			IndirectSetWString(const void* memoryPtr, const std::wstring& newValue);
			static bool			IndirectSetWString(uintptr_t memoryAddress, const std::wstring& newValue);

			static bool			IndirectPatchWString(const void* memoryPtr, const std::wstring& from, const std::wstring& to);
			static bool			IndirectPatchWString(uintptr_t memoryAddress, const std::wstring& from, const std::wstring& to);




			/* For when 'memoryAddress' contains the actual value. */
			static std::vector<uint8_t> GetBytes(const void* memoryPtr, size_t byteCount);
			static std::vector<uint8_t> GetBytes(uintptr_t memoryAddress, size_t byteCount);

			static bool					SetBytes(const void* memoryPtr, const std::vector<uint8_t>& newBytes);
			static bool					SetBytes(uintptr_t memoryAddress, const std::vector<uint8_t>& newBytes);

			static bool					PatchBytes(const void* memoryPtr, const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes);
			static bool					PatchBytes(uintptr_t memoryAddress, const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static std::vector<uint8_t> IndirectGetBytes(const void* memoryPtr, size_t byteCount);
			static std::vector<uint8_t> IndirectGetBytes(uintptr_t memoryAddress, size_t byteCount);

			static bool					IndirectSetBytes(const void* memoryPtr, const std::vector<uint8_t>& newBytes);
			static bool					IndirectSetBytes(uintptr_t memoryAddress, const std::vector<uint8_t>& newBytes);

			static bool					IndirectPatchBytes(const void* memoryPtr, const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes);
			static bool					IndirectPatchBytes(uintptr_t memoryAddress, const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes);
		};






		class External // Functions within the class allows to manipulate memory of 3'rd party processes.
		{
		private:
			static std::string ReadRemoteString(const HANDLE& hProcess, uintptr_t memoryAddress, size_t maxLength = 256);
			static std::wstring ReadRemoteWString(const HANDLE& hProcess, uintptr_t memoryAddress, size_t maxLength = 256);




		public:
			/**
			* @brief Determines whether a given process HANDLE is valid and suitable for memory queries.
			* @param hProcess - Process HANDLE to check.
			* @param requireQueryRights - If true, additionally tries to query any region in the target
			*                             process (VirtualQueryEx) to ensure basic query rights. If false,
			*                             only basic handle validity is checked.
			* @return true if the handle is valid and can be used to query memory; false otherwise.
			*/
			static bool IsValidProcessHandle(const HANDLE& hProcess, bool requireQueryRights);
			/**
			* @brief Determines whether a given process HANDLE is valid and suitable for memory queries.
			* @param hProcess - Process HANDLE to check.
			* @return true if the handle is valid and can be used to query memory; false otherwise.
			*/
			static bool IsValidProcessHandle(const HANDLE& hProcess);

			/**
			* @brief Determines whether a given pointer refers to a valid, committed, and readable (or executable) memory region.
			* @param hProcess - Process HANDLE in whose address space to check.
			* @param memoryPtr - Pointer to the memory location to check.
			* @return true if the region is committed, and has read or execute+read permissions; false otherwise.
			*/
			static bool IsValidPtr(const HANDLE& hProcess, const void* memoryPtr);
			/**
			* @brief Determines whether a given memory address refers to a valid, committed, and readable (or executable) memory region.
			* @param hProcess - Process HANDLE in whose address space to check.
			* @param memoryAddress - Address of the memory location to check.
			* @return true if the region is committed, and has read or execute+read permissions; false otherwise.
			*/
			static bool IsValidAddress(const HANDLE& hProcess, uintptr_t memoryAddress);

			/**
			* @brief Adds a byte offset to a base memory address and verifies that the resulting address range is readable.
			* @param hProcess - Process HANDLE in whose address space to operate.
			* @param memoryPtr - Pointer to the starting memory location to which the offset will be added.
			* @param offset - The number of bytes to add to the base address.
			* @return The new valid pointer to the memory location if both the beginning and end of the target region are readable;
			*         otherwise returns 'nullptr' to indicate an invalid or unreadable address.
			*/
			static void* PtrAddOffset(const HANDLE& hProcess, const void* memoryPtr, size_t offset);
			/**
			* @brief Adds a byte offset to a base memory address and verifies that the resulting address range is readable.
			* @param hProcess - Process HANDLE in whose address space to operate.
			* @param memoryAddress - Address of the memory location to which the offset will be added.
			* @param offset - The number of bytes to add to the base address.
			* @return The new valid pointer to the memory location if both the beginning and end of the target region are readable;
			*         otherwise returns 'nullptr' to indicate an invalid or unreadable address.
			*/
			static void* PtrAddOffset(const HANDLE& hProcess, uintptr_t memoryAddress, size_t offset);

			/**
			* @brief Adds a byte offset to a base memory address and verifies that the resulting address range is readable.
			* @param hProcess - Process HANDLE in whose address space to operate.
			* @param memoryPtr - Pointer to the starting memory location to which the offset will be added.
			* @param offset - The number of bytes to add to the base address.
			* @return The new valid memory address if both the beginning and end of the target region are readable;
			*         otherwise returns '0x0' to indicate an invalid or unreadable address.
			*/
			static uintptr_t AddressAddOffset(const HANDLE& hProcess, const void* memoryPtr, size_t offset);
			/**
			* @brief Adds a byte offset to a base memory address and verifies that the resulting address range is readable.
			* @param hProcess - Process HANDLE in whose address space to operate.
			* @param memoryAddress - Address of the memory location to which the offset will be added.
			* @param offset - The number of bytes to add to the base address.
			* @return The new valid memory address if both the beginning and end of the target region are readable;
			*         otherwise returns '0x0' to indicate an invalid or unreadable address.
			*/
			static uintptr_t AddressAddOffset(const HANDLE& hProcess, uintptr_t memoryAddress, size_t offset);

			/**
			* @brief Adds a byte offset to a base memory address, verifies readability, and dereferences it to read the next pointer in an external process.
			* @param hProcess - Process HANDLE in whose address space to operate.
			* @param memoryPtr - Pointer to the starting memory location.
			* @param offset - The number of bytes to add to the base address before dereferencing (default is 0).
			* @return The new valid pointer read from the memory location;
			*         otherwise returns 'nullptr' to indicate an invalid/unreadable address.
			*/
			static void* PtrDereference(const HANDLE& hProcess, const void* memoryPtr, size_t offset);
			/**
			* @brief Adds a byte offset to a base memory address, verifies readability, and dereferences it to read the next pointer in an external process.
			* @param hProcess - Process HANDLE in whose address space to operate.
			* @param memoryAddress - Address of the memory location.
			* @param offset - The number of bytes to add to the base address before dereferencing (default is 0).
			* @return The new valid pointer read from the memory location;
			*         otherwise returns 'nullptr' to indicate an invalid/unreadable address.
			*/
			static void* PtrDereference(const HANDLE& hProcess, uintptr_t memoryAddress, size_t offset);

			/**
			* @brief Adds a byte offset to a base memory address, verifies readability, and dereferences it to read the next pointer in an external process.
			* @param hProcess - Process HANDLE in whose address space to operate.
			* @param memoryPtr - Pointer to the starting memory location.
			* @param offset - The number of bytes to add to the base address before dereferencing (default is 0).
			* @return The new valid memory address read from the memory location;
			*         otherwise returns '0x0' to indicate an invalid/unreadable address.
			*/
			static uintptr_t AddressDereference(const HANDLE& hProcess, const void* memoryPtr, size_t offset);
			/**
			* @brief Adds a byte offset to a base memory address, verifies readability, and dereferences it to read the next pointer in an external process.
			* @param hProcess - Process HANDLE in whose address space to operate.
			* @param memoryAddress - Address of the memory location.
			* @param offset - The number of bytes to add to the base address before dereferencing (default is 0).
			* @return The new valid memory address read from the memory location;
			*         otherwise returns '0x0' to indicate an invalid/unreadable address.
			*/
			static uintptr_t AddressDereference(const HANDLE& hProcess, uintptr_t memoryAddress, size_t offset);

			/**
			* @brief Follows a chain of pointers starting from a base address, applying a sequence of offsets.
			* @param hProcess - Process HANDLE in whose address space to operate.
			* @param memoryPtr - Pointer to the starting memory location from which the pointer chain will be resolved.
			* @return The new valid memory address if pointer chain was successfully resolved and final destination was reached;
			*         otherwise returns 'nullptr' to indicate an invalid or unreadable address.
			*/
			static void* PtrFollowPointerChain(const HANDLE& hProcess, const void* memoryPtr, const std::vector<uintptr_t>& memoryOffsets);
			/**
			* @brief Follows a chain of pointers starting from a base address, applying a sequence of offsets.
			* @param hProcess - Process HANDLE in whose address space to operate.
			* @param memoryAddress - Address of the memory location from which the pointer chain will be resolved.
			* @return The new valid memory address if pointer chain was successfully resolved and final destination was reached;
			*         otherwise returns '0x0' to indicate an invalid or unreadable address.
			*/
			static uintptr_t AddressFollowPointerChain(const HANDLE& hProcess, uintptr_t memoryAddress, const std::vector<uintptr_t>& memoryOffsets);




			/* For when 'memoryAddress' contains the actual value. */
			static bool GetBool(const HANDLE& hProcess, const void* memoryPtr);
			static bool GetBool(const HANDLE& hProcess, uintptr_t memoryAddress);

			static bool SetBool(const HANDLE& hProcess, const void* memoryPtr, bool newValue);
			static bool SetBool(const HANDLE& hProcess, uintptr_t memoryAddress, bool newValue);

			static bool PatchBool(const HANDLE& hProcess, const void* memoryPtr, bool from, bool to);
			static bool PatchBool(const HANDLE& hProcess, uintptr_t memoryAddress, bool from, bool to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static bool IndirectGetBool(const HANDLE& hProcess, const void* memoryPtr);
			static bool IndirectGetBool(const HANDLE& hProcess, uintptr_t memoryAddress);

			static bool IndirectSetBool(const HANDLE& hProcess, const void* memoryPtr, bool newValue);
			static bool IndirectSetBool(const HANDLE& hProcess, uintptr_t memoryAddress, bool newValue);

			static bool IndirectPatchBool(const HANDLE& hProcess, const void* memoryPtr, bool from, bool to);
			static bool IndirectPatchBool(const HANDLE& hProcess, uintptr_t memoryAddress, bool from, bool to);




			/* For when 'memoryAddress' contains the actual value. */
			static int8_t GetInt8(const HANDLE& hProcess, const void* memoryPtr);
			static int8_t GetInt8(const HANDLE& hProcess, uintptr_t memoryAddress);

			static bool   SetInt8(const HANDLE& hProcess, const void* memoryPtr, int8_t newValue);
			static bool   SetInt8(const HANDLE& hProcess, uintptr_t memoryAddress, int8_t newValue);

			static bool   PatchInt8(const HANDLE& hProcess, const void* memoryPtr, int8_t from, int8_t to);
			static bool   PatchInt8(const HANDLE& hProcess, uintptr_t memoryAddress, int8_t from, int8_t to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static int8_t IndirectGetInt8(const HANDLE& hProcess, const void* memoryPtr);
			static int8_t IndirectGetInt8(const HANDLE& hProcess, uintptr_t memoryAddress);

			static bool   IndirectSetInt8(const HANDLE& hProcess, const void* memoryPtr, int8_t newValue);
			static bool   IndirectSetInt8(const HANDLE& hProcess, uintptr_t memoryAddress, int8_t newValue);

			static bool   IndirectPatchInt8(const HANDLE& hProcess, const void* memoryPtr, int8_t from, int8_t to);
			static bool   IndirectPatchInt8(const HANDLE& hProcess, uintptr_t memoryAddress, int8_t from, int8_t to);




			/* For when 'memoryAddress' contains the actual value. */
			static int16_t GetInt16(const HANDLE& hProcess, const void* memoryPtr);
			static int16_t GetInt16(const HANDLE& hProcess, uintptr_t memoryAddress);

			static bool    SetInt16(const HANDLE& hProcess, const void* memoryPtr, int16_t newValue);
			static bool    SetInt16(const HANDLE& hProcess, uintptr_t memoryAddress, int16_t newValue);

			static bool    PatchInt16(const HANDLE& hProcess, const void* memoryPtr, int16_t from, int16_t to);
			static bool    PatchInt16(const HANDLE& hProcess, uintptr_t memoryAddress, int16_t from, int16_t to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static int16_t IndirectGetInt16(const HANDLE& hProcess, const void* memoryPtr);
			static int16_t IndirectGetInt16(const HANDLE& hProcess, uintptr_t memoryAddress);

			static bool    IndirectSetInt16(const HANDLE& hProcess, const void* memoryPtr, int16_t newValue);
			static bool    IndirectSetInt16(const HANDLE& hProcess, uintptr_t memoryAddress, int16_t newValue);

			static bool    IndirectPatchInt16(const HANDLE& hProcess, const void* memoryPtr, int16_t from, int16_t to);
			static bool    IndirectPatchInt16(const HANDLE& hProcess, uintptr_t memoryAddress, int16_t from, int16_t to);




			/* For when 'memoryAddress' contains the actual value. */
			static int32_t GetInt32(const HANDLE& hProcess, const void* memoryPtr);
			static int32_t GetInt32(const HANDLE& hProcess, uintptr_t memoryAddress);

			static bool    SetInt32(const HANDLE& hProcess, const void* memoryPtr, int32_t newValue);
			static bool    SetInt32(const HANDLE& hProcess, uintptr_t memoryAddress, int32_t newValue);

			static bool    PatchInt32(const HANDLE& hProcess, const void* memoryPtr, int32_t from, int32_t to);
			static bool    PatchInt32(const HANDLE& hProcess, uintptr_t memoryAddress, int32_t from, int32_t to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static int32_t IndirectGetInt32(const HANDLE& hProcess, const void* memoryPtr);
			static int32_t IndirectGetInt32(const HANDLE& hProcess, uintptr_t memoryAddress);

			static bool	   IndirectSetInt32(const HANDLE& hProcess, const void* memoryPtr, int32_t newValue);
			static bool	   IndirectSetInt32(const HANDLE& hProcess, uintptr_t memoryAddress, int32_t newValue);

			static bool    IndirectPatchInt32(const HANDLE& hProcess, const void* memoryPtr, int32_t from, int32_t to);
			static bool    IndirectPatchInt32(const HANDLE& hProcess, uintptr_t memoryAddress, int32_t from, int32_t to);




			/* For when 'memoryAddress' contains the actual value. */
			static int64_t GetInt64(const HANDLE& hProcess, const void* memoryPtr);
			static int64_t GetInt64(const HANDLE& hProcess, uintptr_t memoryAddress);

			static bool    SetInt64(const HANDLE& hProcess, const void* memoryPtr, int64_t newValue);
			static bool    SetInt64(const HANDLE& hProcess, uintptr_t memoryAddress, int64_t newValue);

			static bool    PatchInt64(const HANDLE& hProcess, const void* memoryPtr, int64_t from, int64_t to);
			static bool    PatchInt64(const HANDLE& hProcess, uintptr_t memoryAddress, int64_t from, int64_t to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static int64_t IndirectGetInt64(const HANDLE& hProcess, const void* memoryPtr);
			static int64_t IndirectGetInt64(const HANDLE& hProcess, uintptr_t memoryAddress);

			static bool	   IndirectSetInt64(const HANDLE& hProcess, const void* memoryPtr, int64_t newValue);
			static bool	   IndirectSetInt64(const HANDLE& hProcess, uintptr_t memoryAddress, int64_t newValue);

			static bool    IndirectPatchInt64(const HANDLE& hProcess, const void* memoryPtr, int64_t from, int64_t to);
			static bool    IndirectPatchInt64(const HANDLE& hProcess, uintptr_t memoryAddress, int64_t from, int64_t to);




			/* For when 'memoryAddress' contains the actual value. */
			static float GetFloat(const HANDLE& hProcess, const void* memoryPtr);
			static float GetFloat(const HANDLE& hProcess, uintptr_t memoryAddress);

			static bool  SetFloat(const HANDLE& hProcess, const void* memoryPtr, float newValue);
			static bool  SetFloat(const HANDLE& hProcess, uintptr_t memoryAddress, float newValue);

			static bool  PatchFloat(const HANDLE& hProcess, const void* memoryPtr, float from, float to);
			static bool  PatchFloat(const HANDLE& hProcess, uintptr_t memoryAddress, float from, float to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static float IndirectGetFloat(const HANDLE& hProcess, const void* memoryPtr);
			static float IndirectGetFloat(const HANDLE& hProcess, uintptr_t memoryAddress);

			static bool	 IndirectSetFloat(const HANDLE& hProcess, const void* memoryPtr, float newValue);
			static bool	 IndirectSetFloat(const HANDLE& hProcess, uintptr_t memoryAddress, float newValue);

			static bool  IndirectPatchFloat(const HANDLE& hProcess, const void* memoryPtr, float from, float to);
			static bool  IndirectPatchFloat(const HANDLE& hProcess, uintptr_t memoryAddress, float from, float to);




			/* For when 'memoryAddress' contains the actual value. */
			static double GetDouble(const HANDLE& hProcess, const void* memoryPtr);
			static double GetDouble(const HANDLE& hProcess, uintptr_t memoryAddress);

			static bool  SetDouble(const HANDLE& hProcess, const void* memoryPtr, double newValue);
			static bool  SetDouble(const HANDLE& hProcess, uintptr_t memoryAddress, double newValue);

			static bool  PatchDouble(const HANDLE& hProcess, const void* memoryPtr, double from, double to);
			static bool  PatchDouble(const HANDLE& hProcess, uintptr_t memoryAddress, double from, double to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static double IndirectGetDouble(const HANDLE& hProcess, const void* memoryPtr);
			static double IndirectGetDouble(const HANDLE& hProcess, uintptr_t memoryAddress);

			static bool	 IndirectSetDouble(const HANDLE& hProcess, const void* memoryPtr, double newValue);
			static bool	 IndirectSetDouble(const HANDLE& hProcess, uintptr_t memoryAddress, double newValue);

			static bool  IndirectPatchDouble(const HANDLE& hProcess, const void* memoryPtr, double from, double to);
			static bool  IndirectPatchDouble(const HANDLE& hProcess, uintptr_t memoryAddress, double from, double to);




			/* For when 'memoryAddress' contains the actual value. */
			static std::string GetString(const HANDLE& hProcess, const void* memoryPtr);
			static std::string GetString(const HANDLE& hProcess, const void* memoryPtr, size_t maxLength);
			static std::string GetString(const HANDLE& hProcess, uintptr_t memoryAddress);
			static std::string GetString(const HANDLE& hProcess, uintptr_t memoryAddress, size_t maxLength);

			static bool		   SetString(const HANDLE& hProcess, const void* memoryPtr, const std::string& newValue);
			static bool		   SetString(const HANDLE& hProcess, uintptr_t memoryAddress, const std::string& newValue);

			static bool		   PatchString(const HANDLE& hProcess, const void* memoryPtr, const std::string& from, const std::string& to);
			static bool		   PatchString(const HANDLE& hProcess, uintptr_t memoryAddress, const std::string& from, const std::string& to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static std::string IndirectGetString(const HANDLE& hProcess, const void* memoryPtr);
			static std::string IndirectGetString(const HANDLE& hProcess, const void* memoryPtr, size_t maxLength);
			static std::string IndirectGetString(const HANDLE& hProcess, uintptr_t memoryAddress);
			static std::string IndirectGetString(const HANDLE& hProcess, uintptr_t memoryAddress, size_t maxLength);

			static bool		   IndirectSetString(const HANDLE& hProcess, const void* memoryPtr, const std::string& newValue);
			static bool		   IndirectSetString(const HANDLE& hProcess, uintptr_t memoryAddress, const std::string& newValue);

			static bool		   IndirectPatchString(const HANDLE& hProcess, const void* memoryPtr, const std::string& from, const std::string& to);
			static bool		   IndirectPatchString(const HANDLE& hProcess, uintptr_t memoryAddress, const std::string& from, const std::string& to);




			/* For when 'memoryAddress' contains the actual value. */
			static std::wstring GetWString(const HANDLE& hProcess, const void* memoryPtr);
			static std::wstring GetWString(const HANDLE& hProcess, const void* memoryPtr, size_t maxLength);
			static std::wstring GetWString(const HANDLE& hProcess, uintptr_t memoryAddress);
			static std::wstring GetWString(const HANDLE& hProcess, uintptr_t memoryAddress, size_t maxLength);

			static bool		   SetWString(const HANDLE& hProcess, const void* memoryPtr, const std::wstring& newValue);
			static bool		   SetWString(const HANDLE& hProcess, uintptr_t memoryAddress, const std::wstring& newValue);

			static bool		   PatchWString(const HANDLE& hProcess, const void* memoryPtr, const std::wstring& from, const std::wstring& to);
			static bool		   PatchWString(const HANDLE& hProcess, uintptr_t memoryAddress, const std::wstring& from, const std::wstring& to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static std::wstring IndirectGetWString(const HANDLE& hProcess, const void* memoryPtr);
			static std::wstring IndirectGetWString(const HANDLE& hProcess, const void* memoryPtr, size_t maxLength);
			static std::wstring IndirectGetWString(const HANDLE& hProcess, uintptr_t memoryAddress);
			static std::wstring IndirectGetWString(const HANDLE& hProcess, uintptr_t memoryAddress, size_t maxLength);

			static bool		    IndirectSetWString(const HANDLE& hProcess, const void* memoryPtr, const std::wstring& newValue);
			static bool		    IndirectSetWString(const HANDLE& hProcess, uintptr_t memoryAddress, const std::wstring& newValue);

			static bool		    IndirectPatchWString(const HANDLE& hProcess, const void* memoryPtr, const std::wstring& from, const std::wstring& to);
			static bool		    IndirectPatchWString(const HANDLE& hProcess, uintptr_t memoryAddress, const std::wstring& from, const std::wstring& to);




			/* For when 'memoryAddress' contains the actual value. */
			static std::vector<uint8_t> GetBytes(const HANDLE& hProcess, const void* memoryPtr, size_t byteCount);
			static std::vector<uint8_t> GetBytes(const HANDLE& hProcess, uintptr_t memoryAddress, size_t byteCount);

			static bool					SetBytes(const HANDLE& hProcess, const void* memoryPtr, const std::vector<uint8_t>& newBytes);
			static bool					SetBytes(const HANDLE& hProcess, uintptr_t memoryAddress, const std::vector<uint8_t>& newBytes);

			static bool					PatchBytes(const HANDLE& hProcess, const void* memoryPtr, const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes);
			static bool					PatchBytes(const HANDLE& hProcess, uintptr_t memoryAddress, const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static std::vector<uint8_t> IndirectGetBytes(const HANDLE& hProcess, const void* memoryPtr, size_t byteCount);
			static std::vector<uint8_t> IndirectGetBytes(const HANDLE& hProcess, uintptr_t memoryAddress, size_t byteCount);

			static bool					IndirectSetBytes(const HANDLE& hProcess, const void* memoryPtr, const std::vector<uint8_t>& newBytes);
			static bool					IndirectSetBytes(const HANDLE& hProcess, uintptr_t memoryAddress, const std::vector<uint8_t>& newBytes);

			static bool					IndirectPatchBytes(const HANDLE& hProcess, const void* memoryPtr, const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes);
			static bool					IndirectPatchBytes(const HANDLE& hProcess, uintptr_t memoryAddress, const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes);
		};
	}
};