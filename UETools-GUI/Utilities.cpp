#include "Utilities.h"






std::string Utilities::Environment::GetEnvironmentValue(const std::string& variableName)
{
	char* directoryPath = nullptr;
	size_t len = 0;

	if (_dupenv_s(&directoryPath, &len, variableName.c_str()) != 0 || directoryPath == nullptr)
	{
		return std::string();
	}

	std::string outPath(directoryPath);
	free(directoryPath);

	return outPath;
}

std::string Utilities::Environment::GetEnvironmentValue(const std::wstring& variableName)
{
    return GetEnvironmentValue(String::ToString(variableName));
}

std::string Utilities::Environment::GetEnvironmentValue(const char* variableName)
{
    return GetEnvironmentValue(String::ToString(variableName));
}

std::string Utilities::Environment::GetEnvironmentValue(const wchar_t* variableName)
{
    return GetEnvironmentValue(String::ToString(variableName));
}


std::wstring Utilities::Environment::GetEnvironmentValueUtf16(const std::string& variableName)
{
    return GetEnvironmentValueUtf16(String::ToWString(variableName));
}

std::wstring Utilities::Environment::GetEnvironmentValueUtf16(const std::wstring& variableName)
{
    wchar_t* directoryPath = nullptr;
    size_t len = 0;

    if (_wdupenv_s(&directoryPath, &len, variableName.c_str()) != 0 || directoryPath == nullptr)
    {
        return std::wstring();
    }

    std::wstring outPath(directoryPath);
    free(directoryPath);

    return outPath;
}

std::wstring Utilities::Environment::GetEnvironmentValueUtf16(const char* variableName)
{
    return GetEnvironmentValueUtf16(String::ToWString(variableName));
}

std::wstring Utilities::Environment::GetEnvironmentValueUtf16(const wchar_t* variableName)
{
    return GetEnvironmentValueUtf16(String::ToWString(variableName));
}


std::string Utilities::Environment::GetExecutablePath()
{
	char executablePath[MAX_PATH] = { 0 };

	if (GetModuleFileNameA(NULL, executablePath, MAX_PATH) == 0)
	{
		return std::string();
	}

	return std::string(executablePath);
}

std::wstring Utilities::Environment::GetExecutablePathUtf16()
{
    wchar_t executablePath[MAX_PATH] = { 0 };

    if (GetModuleFileNameW(NULL, executablePath, MAX_PATH) == 0)
    {
        return std::wstring();
    }

    return std::wstring(executablePath);
}


std::string Utilities::Environment::GetExecutableName(bool includeFileExtension)
{
	std::string executablePath = GetExecutablePath();
	if (executablePath.empty() == true)
	{
		return std::string();
	}

	std::filesystem::path fsPath(executablePath);
	return includeFileExtension ? fsPath.filename().string() : fsPath.stem().string();
}

std::wstring Utilities::Environment::GetExecutableNameUtf16(bool includeFileExtension)
{
    std::wstring executablePath = GetExecutablePathUtf16();
    if (executablePath.empty() == true)
    {
        return std::wstring();
    }

    std::filesystem::path fsPath(executablePath);
    return includeFileExtension ? fsPath.filename().wstring() : fsPath.stem().wstring();
}


std::string Utilities::Environment::GetExecutableDirectory()
{
	std::string executablePath = GetExecutablePath();
	if (executablePath.empty() == true)
	{
		return std::string();
	}

	std::filesystem::path fsPath(executablePath);
	return fsPath.parent_path().string();
}

std::wstring Utilities::Environment::GetExecutableDirectoryUtf16()
{
    std::wstring executablePath = GetExecutablePathUtf16();
    if (executablePath.empty() == true)
    {
        return std::wstring();
    }

    std::filesystem::path fsPath(executablePath);
    return fsPath.parent_path().wstring();
}


std::string Utilities::Environment::GetProgramFilesDirectory()
{
	return GetEnvironmentValue("ProgramFiles");
}

std::wstring Utilities::Environment::GetProgramFilesDirectoryUtf16()
{
    return GetEnvironmentValueUtf16(L"ProgramFiles");
}


std::string Utilities::Environment::GetProgramFilesX86Directory()
{
	return GetEnvironmentValue("ProgramFiles(x86)");
}

std::wstring Utilities::Environment::GetProgramFilesX86DirectoryUtf16()
{
    return GetEnvironmentValueUtf16(L"ProgramFiles(x86)");
}


std::string Utilities::Environment::GetUserDirectory()
{
	return GetEnvironmentValue("USERPROFILE");
}

std::wstring Utilities::Environment::GetUserDirectoryUtf16()
{
    return GetEnvironmentValueUtf16(L"USERPROFILE");
}


std::string Utilities::Environment::GetDesktopDirectory()
{
    std::string outPath = GetUserDirectory();
	if (outPath.empty() == false)
	{
		outPath += "\\Desktop";
		return outPath;
	}

	return std::string();
}

std::wstring Utilities::Environment::GetDesktopDirectoryUtf16()
{
    std::wstring outPath = GetUserDirectoryUtf16();
    if (outPath.empty() == false)
    {
        outPath += L"\\Desktop";
        return outPath;
    }

    return std::wstring();
}


std::string Utilities::Environment::GetDownloadsDirectory()
{
    std::string outPath = GetUserDirectory();
	if (outPath.empty() == false)
	{
		outPath += "\\Downloads";
		return outPath;
	}

	return std::string();
}

std::wstring Utilities::Environment::GetDownloadsDirectoryUtf16()
{
    std::wstring outPath = GetUserDirectoryUtf16();
    if (outPath.empty() == false)
    {
        outPath += L"\\Downloads";
        return outPath;
    }

    return std::wstring();
}


std::string Utilities::Environment::GetDocumentsDirectory()
{
	std::string outPath = GetUserDirectory();
	if (outPath.empty() == false)
	{
		outPath += "\\Documents";
		return outPath;
	}

	return std::string();
}

std::wstring Utilities::Environment::GetDocumentsDirectoryUtf16()
{
    std::wstring outPath = GetUserDirectoryUtf16();
    if (outPath.empty() == false)
    {
        outPath += L"\\Documents";
        return outPath;
    }
    return std::wstring();
}


std::string Utilities::Environment::GetPicturesDirectory()
{
	std::string outPath = GetUserDirectory();
	if (outPath.empty() == false)
	{
		outPath += "\\Pictures";
		return outPath;
	}

	return std::string();
}

std::wstring Utilities::Environment::GetPicturesDirectoryUtf16()
{
    std::wstring outPath = GetUserDirectoryUtf16();
    if (outPath.empty() == false)
    {
        outPath += L"\\Pictures";
        return outPath;
    }

    return std::wstring();
}


std::string Utilities::Environment::GetVideosDirectory()
{
	std::string outPath = GetUserDirectory();
	if (outPath.empty() == false)
	{
		outPath += "\\Videos";
		return outPath;
	}

	return std::string();
}

std::wstring Utilities::Environment::GetVideosDirectoryUtf16()
{
    std::wstring outPath = GetUserDirectoryUtf16();
    if (outPath.empty() == false)
    {
        outPath += L"\\Videos";
        return outPath;
    }

    return std::wstring();
}


std::string Utilities::Environment::GetMusicDirectory()
{
	std::string outPath = GetUserDirectory();
	if (outPath.empty() == false)
	{
		outPath += "\\Music";
		return outPath;
	}

	return std::string();
}

std::wstring Utilities::Environment::GetMusicDirectoryUtf16()
{
    std::wstring outPath = GetUserDirectoryUtf16();
    if (outPath.empty() == false)
    {
        outPath += L"\\Music";
        return outPath;
    }

    return std::wstring();
}


std::string Utilities::Environment::GetAppDataLocalDirectory()
{
	return GetEnvironmentValue("LOCALAPPDATA");
}

std::wstring Utilities::Environment::GetAppDataLocalDirectoryUtf16()
{
    return GetEnvironmentValueUtf16(L"LOCALAPPDATA");
}


std::string Utilities::Environment::GetAppDataLocalLowDirectory()
{
	std::string outPath = GetUserDirectory();
	if (outPath.empty() == false)
	{
		outPath += "\\AppData\\LocalLow";
		return outPath;
	}

	return std::string();
}

std::wstring Utilities::Environment::GetAppDataLocalLowDirectoryUtf16()
{
    std::wstring outPath = GetUserDirectoryUtf16();
    if (outPath.empty() == false)
    {
        outPath += L"\\AppData\\LocalLow";
        return outPath;
    }

    return std::wstring();
}


std::string Utilities::Environment::GetAppDataRoamingDirectory()
{
	return GetEnvironmentValue("APPDATA");
}

std::wstring Utilities::Environment::GetAppDataRoamingDirectoryUtf16()
{
    return GetEnvironmentValueUtf16(L"APPDATA");
}


std::string Utilities::Environment::GetSystemPath()
{
	char buffer[MAX_PATH];
	if (GetSystemDirectoryA(buffer, MAX_PATH) == 0)
	{
		return std::string();
	}

	return std::string(buffer);
}

std::wstring Utilities::Environment::GetSystemPathUtf16()
{
    wchar_t buffer[MAX_PATH];
    if (GetSystemDirectoryW(buffer, MAX_PATH) == 0)
    {
        return std::wstring();
    }

    return std::wstring(buffer);
}


std::string Utilities::Environment::GetSystemDrive()
{
	std::string systemPath = GetSystemPath();
	if ((systemPath.empty() == false) && (systemPath.size() >= 3))
	{
		return systemPath.substr(0, 3);
	}

	return std::string();
}

std::wstring Utilities::Environment::GetSystemDriveUtf16()
{
    std::wstring systemPath = GetSystemPathUtf16();
    if ((systemPath.empty() == false) && (systemPath.size() >= 3))
    {
        return systemPath.substr(0, 3);
    }

    return std::wstring();
}




void Utilities::Console::Create(const std::string& title, bool redirectStreams)
{
    Create(String::ToWString(title), redirectStreams);
}

void Utilities::Console::Create(const std::wstring& title, bool redirectStreams)
{
    bool consoleExists = (GetConsoleWindow() != nullptr);
    if (consoleExists == false)
    {
        AllocConsole();

        HWND hConsole = GetConsoleWindow();
        if (hConsole != nullptr)
        {
            std::wstring executablePath = Environment::GetExecutablePathUtf16();
            if (executablePath.empty() == false)
            {
                HICON hIconBig = nullptr;
                HICON hIconSmall = nullptr;

                ExtractIconExW(executablePath.c_str(), 0, &hIconBig, &hIconSmall, 1);

                if (hIconBig != nullptr)
                    SendMessageW(hConsole, WM_SETICON, ICON_BIG, (LPARAM)hIconBig);

                if (hIconSmall != nullptr)
                    SendMessageW(hConsole, WM_SETICON, ICON_SMALL, (LPARAM)hIconSmall);
            }
        }
    }

    SetConsoleTitleW(title.empty() ? L"Console" : title.c_str());

    if (redirectStreams)
    {
        FILE* fConsole;
        freopen_s(&fConsole, "CONIN$", "r", stdin);
        freopen_s(&fConsole, "CONOUT$", "w", stdout);
        freopen_s(&fConsole, "CONOUT$", "w", stderr);

        std::cout.clear();
        std::clog.clear();
        std::cerr.clear();
        std::cin.clear();
    }
}

void Utilities::Console::Create(const char* title, bool redirectStreams)
{
    Create(String::ToString(title), redirectStreams);
}

void Utilities::Console::Create(const wchar_t* title, bool redirectStreams)
{
    Create(String::ToWString(title), redirectStreams);
}

void Utilities::Console::Create(bool redirectStreams)
{
    Create(std::wstring(), redirectStreams);
}


void Utilities::Console::SetBufferSize(short newBufferSize)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(hConsole, &csbi))
		{
			short minHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
			short maxHeight = 32767;

			newBufferSize = std::clamp(newBufferSize, minHeight, maxHeight);

			COORD newSize;
			newSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
			newSize.Y = newBufferSize;
			SetConsoleScreenBufferSize(hConsole, newSize);
		}
	}
}


void Utilities::Console::Clear()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(hConsole, &csbi))
		{
			DWORD count;
			DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
			COORD homeCoords = { 0, 0 };

			if (!FillConsoleOutputCharacter( // == false.
				hConsole,        // Handle to console screen buffer
				(TCHAR)' ',      // Character to write to the buffer
				cellCount,       // Number of cells to write
				homeCoords,      // Coordinates of first cell
				&count           // Receive number of characters written
			)) return;

			if (!FillConsoleOutputAttribute( // == false.
				hConsole,        // Handle to console screen buffer
				csbi.wAttributes,// Character attributes to use
				cellCount,       // Number of cells to set attribute
				homeCoords,      // Coordinates of first cell
				&count           // Receive number of attributes written
			)) return;

			SetConsoleCursorPosition(hConsole, homeCoords);
		}
	}
}


void Utilities::Console::EncodingUTF8()
{
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
}

void Utilities::Console::Encoding1252()
{
	SetConsoleOutputCP(1252);
	SetConsoleCP(1252);
}

void Utilities::Console::Encoding1251()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
}

void Utilities::Console::Encoding866()
{
	SetConsoleOutputCP(866);
	SetConsoleCP(866);
}

void Utilities::Console::Encoding437()
{
	SetConsoleOutputCP(437);
	SetConsoleCP(437);
}




std::string Utilities::CommandLine::Get()
{
    if (LPSTR cmdLine = GetCommandLineA())
        return std::string(cmdLine);

    return std::string();
}

std::wstring Utilities::CommandLine::GetUtf16()
{
    if (LPWSTR cmdLine = GetCommandLineW())
        return std::wstring(cmdLine);

    return std::wstring();
}


std::vector<std::string> Utilities::CommandLine::GetArguments()
{
    std::vector<std::string> outArguments;
    
    std::vector<std::wstring> arguments = GetArgumentsUtf16();
    for (std::wstring& arg : arguments)
    {
        outArguments.push_back(String::ToString(arg));
    }

    return outArguments;
}

std::vector<std::wstring> Utilities::CommandLine::GetArgumentsUtf16()
{
    std::vector<std::wstring> outArguments;
    int32_t argCount = 0;

    if (LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argCount))
    {
        for (int32_t argId = 0; argId < argCount; ++argId)
        {
            if (argv[argId])
                outArguments.push_back(std::wstring(argv[argId]));
        }

        LocalFree(argv);
    }

    return outArguments;
}


int Utilities::CommandLine::Count()
{
    int32_t argCount = 0;

    if (LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argCount))
        LocalFree(argv);

    return argCount;
}


bool Utilities::CommandLine::HasArgument(const std::string& argument)
{
    if (argument.empty())
        return false;

    std::vector<std::string> arguments = GetArguments();
    for (std::string& arg : arguments)
    {
        if (arg == argument)
            return true;
    }

    return false;
}

bool Utilities::CommandLine::HasArgument(const std::wstring& argument)
{
    if (argument.empty())
        return false;

    std::vector<std::wstring> arguments = GetArgumentsUtf16();
    for (std::wstring& arg : arguments)
    {
        if (arg == argument)
            return true;
    }

    return false;
}

bool Utilities::CommandLine::HasArgument(const char* argument)
{
    return HasArgument(String::ToString(argument));
}

bool Utilities::CommandLine::HasArgument(const wchar_t* argument)
{
    return HasArgument(String::ToWString(argument));
}




std::string Utilities::Clipboard::GetText()
{
    return String::ToString(GetTextUtf16());
}

std::wstring Utilities::Clipboard::GetTextUtf16()
{
    if (OpenClipboard(nullptr))
    {
        HANDLE hData = GetClipboardData(CF_UNICODETEXT);
        if (hData)
        {
            wchar_t* pData = static_cast<wchar_t*>(GlobalLock(hData));
            if (pData)
            {
                std::wstring text(pData);
                GlobalUnlock(hData);

                CloseClipboard();
                return text;
            }
            GlobalUnlock(hData);
        }
        CloseClipboard();
    }

    return std::wstring();
}


bool Utilities::Clipboard::SetText(const std::string& string)
{
    if (OpenClipboard(nullptr))
    {
        EmptyClipboard();
        size_t textSize = string.size() + 1;

        HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, textSize);
        if (hGlobal)
        {
            void* pMem = GlobalLock(hGlobal);
            if (pMem)
            {
                std::memcpy(pMem, string.c_str(), textSize);
                GlobalUnlock(hGlobal);

                if (SetClipboardData(CF_TEXT, hGlobal) == nullptr)
                {
                    GlobalFree(hGlobal);
                    CloseClipboard();
                    return false;
                }

                CloseClipboard();
                return true;
            }
            GlobalFree(hGlobal);
        }
        CloseClipboard();
    }

    return false;
}

bool Utilities::Clipboard::SetText(const std::wstring& wString)
{
    if (OpenClipboard(nullptr))
    {
        EmptyClipboard();
        size_t textSize = (wString.size() + 1) * sizeof(wchar_t);

        HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, textSize);
        if (hGlobal)
        {
            void* pMem = GlobalLock(hGlobal);
            if (pMem)
            {
                std::memcpy(pMem, wString.c_str(), textSize);
                GlobalUnlock(hGlobal);

                if (SetClipboardData(CF_UNICODETEXT, hGlobal) == nullptr)
                {
                    GlobalFree(hGlobal);
                    CloseClipboard();
                    return false;
                }

                CloseClipboard();
                return true;
            }
            GlobalFree(hGlobal);
        }
        CloseClipboard();
    }

    return false; 
}

bool Utilities::Clipboard::SetText(const char* cString)
{
    return SetText(String::ToString(cString));
}

bool Utilities::Clipboard::SetText(const wchar_t* wcString)
{
    return SetText(String::ToWString(wcString));
}


bool Utilities::Clipboard::Contains(const std::string& substring)
{
    std::string text = Clipboard::GetText();
    return (text.find(substring) != std::string::npos);
}

bool Utilities::Clipboard::Contains(const std::wstring& substring)
{
    std::wstring text = GetTextUtf16();
    return (text.find(substring) != std::wstring::npos);
}

bool Utilities::Clipboard::Contains(const char* substring)
{
    return Contains(String::ToString(substring));
}

bool Utilities::Clipboard::Contains(const wchar_t* substring)
{
    return Contains(String::ToWString(substring));
}


bool Utilities::Clipboard::ContainsRegex(const std::string& regexPattern)
{
    std::string text = String::ToString(GetTextUtf16());
    try
    {
        std::regex re(regexPattern);
        return std::regex_search(text, re);
    }
    catch (std::regex_error&)
    {
        return false;
    }
}

bool Utilities::Clipboard::ContainsRegex(const std::wstring& regexPattern)
{
    std::wstring text = GetTextUtf16();
    try
    {
        std::wregex re(regexPattern);
        return std::regex_search(text, re);
    }
    catch (std::regex_error&)
    {
        return false;
    }
}

bool Utilities::Clipboard::ContainsRegex(const char* regexPattern)
{
    return ContainsRegex(String::ToString(regexPattern));
}

bool Utilities::Clipboard::ContainsRegex(const wchar_t* regexPattern)
{
    return ContainsRegex(String::ToWString(regexPattern));
}




Utilities::Message::E_MessageResult Utilities::Message::Show(HWND hwndOwner, const std::string& title, const std::string& message, E_Buttons buttons, E_Icon icon, E_DefaultButton defaultButton)
{
    return Show(hwndOwner, String::ToWString(title), String::ToWString(message), buttons, icon, defaultButton);
}

Utilities::Message::E_MessageResult Utilities::Message::Show(HWND hwndOwner, const std::wstring& title, const std::wstring& message, E_Buttons buttons, E_Icon icon, E_DefaultButton defaultButton)
{
    UINT type = static_cast<UINT>(buttons) | static_cast<UINT>(icon) | static_cast<UINT>(defaultButton);
    int messageResult = MessageBoxW(hwndOwner, message.c_str(), title.c_str(), type);

    switch (messageResult)
    {
        case IDOK:      return E_MessageResult::OK;
        case IDCANCEL:  return E_MessageResult::Cancel;
        case IDABORT:   return E_MessageResult::Abort;
        case IDRETRY:   return E_MessageResult::Retry;
        case IDIGNORE:  return E_MessageResult::Ignore;
        case IDYES:     return E_MessageResult::Yes;
        case IDNO:      return E_MessageResult::No;
        case 0:         return E_MessageResult::Timeout;
        default:        return E_MessageResult::Unknown;
    }
}

Utilities::Message::E_MessageResult Utilities::Message::Show(HWND hwndOwner, const char* title, const char* message, E_Buttons buttons, E_Icon icon, E_DefaultButton defaultButton)
{
    return Show(hwndOwner, String::ToString(title), String::ToString(message), buttons, icon, defaultButton);
}

Utilities::Message::E_MessageResult Utilities::Message::Show(HWND hwndOwner, const wchar_t* title, const wchar_t* message, E_Buttons buttons, E_Icon icon, E_DefaultButton defaultButton)
{
    return Show(hwndOwner, String::ToWString(title), String::ToWString(message), buttons, icon, defaultButton);
}


Utilities::Message::E_MessageResult Utilities::Message::Show(const std::string& title, const std::string& message, E_Buttons buttons, E_Icon icon, E_DefaultButton defaultButton)
{
	return Show(nullptr, title, message, buttons, icon, defaultButton);
}

Utilities::Message::E_MessageResult Utilities::Message::Show(const std::wstring& title, const std::wstring& message, E_Buttons buttons, E_Icon icon, E_DefaultButton defaultButton)
{
    return Show(nullptr, title, message, buttons, icon, defaultButton);
}

Utilities::Message::E_MessageResult Utilities::Message::Show(const char* title, const char* message, E_Buttons buttons, E_Icon icon, E_DefaultButton defaultButton)
{
    return Show(nullptr, title, message, buttons, icon, defaultButton);
}

Utilities::Message::E_MessageResult Utilities::Message::Show(const wchar_t* title, const wchar_t* message, E_Buttons buttons, E_Icon icon, E_DefaultButton defaultButton)
{
    return Show(nullptr, title, message, buttons, icon, defaultButton);
}


Utilities::Message::E_MessageResult Utilities::Message::Show(const std::string& message, E_Buttons buttons, E_Icon icon, E_DefaultButton defaultButton)
{
	return Show(nullptr, Environment::GetExecutableName(false), message, buttons, icon, defaultButton);
}

Utilities::Message::E_MessageResult Utilities::Message::Show(const std::wstring& message, E_Buttons buttons, E_Icon icon, E_DefaultButton defaultButton)
{
    return Show(nullptr, Environment::GetExecutableNameUtf16(false), message, buttons, icon, defaultButton);
}

Utilities::Message::E_MessageResult Utilities::Message::Show(const char* message, E_Buttons buttons, E_Icon icon, E_DefaultButton defaultButton)
{
    return Show(nullptr, Environment::GetExecutableName(false), String::ToString(message), buttons, icon, defaultButton);
}

Utilities::Message::E_MessageResult Utilities::Message::Show(const wchar_t* message, E_Buttons buttons, E_Icon icon, E_DefaultButton defaultButton)
{
    return Show(nullptr, Environment::GetExecutableNameUtf16(false), String::ToWString(message), buttons, icon, defaultButton);
}




std::string Utilities::String::ToString(const std::wstring& wideString)
{
	if (wideString.empty())
	{
		return std::string();
	}

	const wchar_t* wcString = wideString.c_str();
	return ToString(wcString);
}

std::string Utilities::String::ToString(const char* cString)
{
	if (cString == nullptr)
	{
		return std::string();
	}

	return std::string(cString);
}

std::string Utilities::String::ToString(const wchar_t* wcString)
{
	if (wcString == nullptr)
	{
		return std::string();
	}

	size_t convertedCount = 0;
	errno_t errorCode = wcstombs_s(&convertedCount, nullptr, 0, wcString, 0);

	if (errorCode != 0 || convertedCount == 0)
	{
		return std::string();
	}

	std::vector<char> buffer(convertedCount);
	errorCode = wcstombs_s(&convertedCount, buffer.data(), buffer.size(), wcString, _TRUNCATE);

	if (errorCode != 0)
	{
		return std::string();
	}

	/* Return string excluding the null terminator. */
	return std::string(buffer.data(), convertedCount - 1);
}


std::wstring Utilities::String::ToWString(const std::string& string)
{
	if (string.empty())
	{
		return std::wstring();
	}

	const char* cString = string.c_str();
	return ToWString(cString);
}

std::wstring Utilities::String::ToWString(const char* cString)
{
	if (cString == nullptr)
	{
		return std::wstring();
	}

	size_t convertedCount = 0;
	errno_t errorCode = mbstowcs_s(&convertedCount, nullptr, 0, cString, 0);

	if (errorCode != 0 || convertedCount == 0)
	{
		return std::wstring();
	}

	std::vector<wchar_t> buffer(convertedCount);
	errorCode = mbstowcs_s(&convertedCount, buffer.data(), buffer.size(), cString, _TRUNCATE);

	if (errorCode != 0)
	{
		return std::wstring();
	}

	/* Return wide string excluding the null terminator. */
	return std::wstring(buffer.data(), convertedCount - 1);
}

std::wstring Utilities::String::ToWString(const wchar_t* wcString)
{
	if (wcString == nullptr)
	{
		return std::wstring();
	}

	return std::wstring(wcString);
}


bool Utilities::String::ToInt8(const std::string& string, int8_t* outValue)
{
    if (outValue == nullptr)
        return false;

    int64_t value;
    if (ToInt64(string, &value) == false)
        return false;

    if (value < INT8_MIN || value > INT8_MAX)
        return false;

    *outValue = static_cast<int8_t>(value);
    return true;
}

bool Utilities::String::ToInt8(const std::wstring& wString, int8_t* outValue)
{
    return ToInt8(ToString(wString), outValue);
}

bool Utilities::String::ToInt8(const char* cString, int8_t* outValue)
{
    return ToInt8(ToString(cString), outValue);
}

bool Utilities::String::ToInt8(const wchar_t* wcString, int8_t* outValue)
{
    return ToInt8(ToString(wcString), outValue);
}


bool Utilities::String::ToInt16(const std::string& string, int16_t* outValue)
{
    if (outValue == nullptr)
        return false;

    int64_t value;
    if (ToInt64(string, &value) == false)
        return false;

    if (value < INT16_MIN || value > INT16_MAX)
        return false;

    *outValue = static_cast<int16_t>(value);
    return true;
}

bool Utilities::String::ToInt16(const std::wstring& wString, int16_t* outValue)
{
    return ToInt16(ToString(wString), outValue);
}

bool Utilities::String::ToInt16(const char* cString, int16_t* outValue)
{
    return ToInt16(ToString(cString), outValue);
}

bool Utilities::String::ToInt16(const wchar_t* wcString, int16_t* outValue)
{
    return ToInt16(ToString(wcString), outValue);
}


bool Utilities::String::ToInt32(const std::string& string, int32_t* outValue)
{
    if (outValue == nullptr)
        return false;

    int64_t value;
    if (ToInt64(string, &value) == false)
        return false;

    if (value < INT32_MIN || value > INT32_MAX)
        return false;

    *outValue = static_cast<int32_t>(value);
    return true;
}

bool Utilities::String::ToInt32(const std::wstring& wString, int32_t* outValue)
{
    return ToInt32(ToString(wString), outValue);
}

bool Utilities::String::ToInt32(const char* cString, int32_t* outValue)
{
    return ToInt32(ToString(cString), outValue);
}

bool Utilities::String::ToInt32(const wchar_t* wcString, int32_t* outValue)
{
    return ToInt32(ToString(wcString), outValue);
}


bool Utilities::String::ToInt64(const std::string& string, int64_t* outValue)
{
    if (outValue == nullptr)
        return false;

    if (string.empty())
        return false;

    size_t startIndex = 0;
    bool startsWithSign = false;

    /* Check for an optional leading sign. */
    if (string[0] == '-' || string[0] == '+')
    {
        if (string.length() == 1)
            return false;

        startIndex = 1;
        startsWithSign = true;
    }

    for (size_t index = startIndex; index < string.length(); ++index)
    {
        if (std::isdigit(static_cast<unsigned char>(string[index])) == false)
        {
            return false;
        }
    }

    const char* startPtr = startsWithSign ? string.data() + 1 : string.data();
    auto [ptr, ec] = std::from_chars(startPtr, string.data() + string.length(), *outValue);
    return ec == std::errc();
}

bool Utilities::String::ToInt64(const std::wstring& wString, int64_t* outValue)
{
    return false;
}

bool Utilities::String::ToInt64(const char* cString, int64_t* outValue)
{
    return false;
}

bool Utilities::String::ToInt64(const wchar_t* wcString, int64_t* outValue)
{
    return false;
}


bool Utilities::String::ToFloat(const std::string& string, float* outValue)
{
    if (outValue == nullptr)
        return false;

    double value;
    if (ToDouble(string, &value) == false)
        return false;

    if (value < static_cast<double>((std::numeric_limits<float>::lowest)()) || value > static_cast<double>((std::numeric_limits<float>::max)()))
        return false;

    *outValue = static_cast<float>(value);
    return true;
}

bool Utilities::String::ToFloat(const std::wstring& wString, float* outValue)
{
    return false;
}

bool Utilities::String::ToFloat(const char* cString, float* outValue)
{
    return false;
}

bool Utilities::String::ToFloat(const wchar_t* wcString, float* outValue)
{
    return false;
}


bool Utilities::String::ToDouble(const std::string& string, double* outValue)
{
    if (outValue == nullptr)
        return false;

    if (string.empty())
        return false;

    size_t startIndex = 0;
    bool startsWithSign = false;

    /* Check for an optional leading sign. */
    if (string[0] == '-' || string[0] == '+')
    {
        if (string.length() == 1)
            return false;

        startIndex = 1;
        startsWithSign = true;
    }

    bool hasDecimal = false;
    bool hasDigits = false;
    size_t parseLength = string.length();
    for (size_t index = startIndex; index < string.length(); ++index)
    {
        const char c = string[index];

        if (std::isdigit(static_cast<unsigned char>(c)))
        {
            hasDigits = true;
        }
        else if (c == '.')
        {
            if (hasDecimal)
                return false;

            hasDecimal = true;
        }
        else if ((c == 'f' || c == 'F') && index == string.length() - 1)
        {
            if (hasDigits == false)
                return false;

            /* Do not pass the 'f' suffix to std::from_chars(). */
            parseLength = string.length() - 1;
        }
        else
        {
            return false;
        }
    }

    /* Prevent strings like '.' or '+.' from passing. */
    if (hasDigits == false)
        return false;

    const char* startPtr = startsWithSign ? string.data() + 1 : string.data();
    auto [ptr, ec] = std::from_chars(startPtr, string.data() + parseLength, *outValue);
    return ec == std::errc();
}

bool Utilities::String::ToDouble(const std::wstring& wString, double* outValue)
{
    return ToDouble(ToString(wString), outValue);
}

bool Utilities::String::ToDouble(const char* cString, double* outValue)
{
    return ToDouble(ToString(cString), outValue);
}

bool Utilities::String::ToDouble(const wchar_t* wcString, double* outValue)
{
    return ToDouble(ToString(wcString), outValue);
}




std::string Utilities::String::ToLowerCase(std::string string)
{
    std::transform(string.begin(), string.end(), string.begin(), [](unsigned char c)
    {
        return std::tolower(c);
    });

    return string;
}

std::wstring Utilities::String::ToLowerCase(std::wstring wString)
{
	std::transform(wString.begin(), wString.end(), wString.begin(), [](wchar_t c)
	{
		return std::towlower(c);
	});

	return wString;
}

std::string Utilities::String::ToLowerCase(const char* cString)
{
    return ToLowerCase(String::ToString(cString));
}

std::wstring Utilities::String::ToLowerCase(const wchar_t* wcString)
{
    return ToLowerCase(String::ToWString(wcString));
}




std::string Utilities::String::ToUpperCase(std::string string)
{
    std::transform(string.begin(), string.end(), string.begin(), [](unsigned char c)
    { 
        return std::toupper(c); 
    });

    return string;
}

std::wstring Utilities::String::ToUpperCase(std::wstring wString)
{
	std::transform(wString.begin(), wString.end(), wString.begin(), [](wchar_t c)
	{
		return std::towupper(c);
	});

	return wString;
}

std::string Utilities::String::ToUpperCase(const char* cString)
{
    return ToUpperCase(String::ToString(cString));
}

std::wstring Utilities::String::ToUpperCase(const wchar_t* wcString)
{
    return ToUpperCase(String::ToWString(wcString));
}




std::string Utilities::String::Replace(std::string string, const std::string& from, const std::string& to)
{
	if (from.empty())
	{
		return string;
	}

	size_t start_pos = 0;
	while ((start_pos = string.find(from, start_pos)) != std::string::npos)
	{
		string.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}

	return string;
}

std::string Utilities::String::Replace(const std::string& string, const std::string& from, const std::wstring& to)
{
	return Replace(string, from, ToString(to));
}

std::string Utilities::String::Replace(const std::string& string, const std::wstring& from, const std::string& to)
{
	return Replace(string, ToString(from), to);
}

std::string Utilities::String::Replace(const std::string& string, const std::wstring& from, const std::wstring& to)
{
	return Replace(string, ToString(from), ToString(to));
}

std::string Utilities::String::Replace(const char* cString, const char* from, const char* to)
{
    return Replace(ToString(cString), ToString(from), ToString(to));
}


std::wstring Utilities::String::Replace(std::wstring wString, const std::wstring& from, const std::wstring& to)
{
	if (from.empty())
	{
		return wString;
	}

	size_t start_pos = 0;
	while ((start_pos = wString.find(from, start_pos)) != std::wstring::npos)
	{
		wString.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}

	return wString;
}

std::wstring Utilities::String::Replace(const std::wstring& wString, const std::wstring& from, const std::string& to)
{
	return Replace(wString, from, ToWString(to));
}

std::wstring Utilities::String::Replace(const std::wstring& wString, const std::string& from, const std::wstring& to)
{
	return Replace(wString, ToWString(from), to);
}

std::wstring Utilities::String::Replace(const std::wstring& wString, const std::string& from, const std::string& to)
{
	return Replace(wString, ToWString(from), ToWString(to));
}

std::wstring Utilities::String::Replace(const wchar_t* wcString, const wchar_t* from, const wchar_t* to)
{
    return Replace(ToWString(wcString), ToWString(from), ToWString(to));
}




std::string Utilities::String::ReplaceFirstOf(std::string string, const std::string& from, const std::string& to)
{
	if (from.empty())
	{
		return string;
	}

	size_t start_pos = string.find(from);
	if (start_pos != std::string::npos)
	{
		string.replace(start_pos, from.length(), to);
	}

	return string;
}

std::string Utilities::String::ReplaceFirstOf(const std::string& string, const std::string& from, const std::wstring& to)
{
	return ReplaceFirstOf(string, from, ToString(to));
}

std::string Utilities::String::ReplaceFirstOf(const std::string& string, const std::wstring& from, const std::string& to)
{
	return ReplaceFirstOf(string, ToString(from), to);
}

std::string Utilities::String::ReplaceFirstOf(const std::string& string, const std::wstring& from, const std::wstring& to)
{
	return ReplaceFirstOf(string, ToString(from), ToString(to));
}

std::string Utilities::String::ReplaceFirstOf(const char* cString, const char* from, const char* to)
{
    return ReplaceFirstOf(ToString(cString), ToString(from), ToString(to));
}


std::wstring Utilities::String::ReplaceFirstOf(std::wstring wString, const std::wstring& from, const std::wstring& to)
{
	if (from.empty())
	{
		return wString;
	}

	size_t start_pos = wString.find(from);
	if (start_pos != std::wstring::npos)
	{
		wString.replace(start_pos, from.length(), to);
	}

	return wString;
}

std::wstring Utilities::String::ReplaceFirstOf(const std::wstring& wString, const std::wstring& from, const std::string& to)
{
	return ReplaceFirstOf(wString, from, ToWString(to));
}

std::wstring Utilities::String::ReplaceFirstOf(const std::wstring& wString, const std::string& from, const std::wstring& to)
{
	return ReplaceFirstOf(wString, ToWString(from), to);
}

std::wstring Utilities::String::ReplaceFirstOf(const std::wstring& wString, const std::string& from, const std::string& to)
{
	return ReplaceFirstOf(wString, ToWString(from), ToWString(to));
}

std::wstring Utilities::String::ReplaceFirstOf(const wchar_t* wcString, const wchar_t* from, const wchar_t* to)
{
    return ReplaceFirstOf(ToWString(wcString), ToWString(from), ToWString(to));
}


std::string Utilities::String::ReplaceLastOf(std::string string, const std::string& from, const std::string& to)
{
	if (from.empty())
	{
		return string;
	}

	size_t start_pos = string.rfind(from);
	if (start_pos != std::string::npos)
	{
		string.replace(start_pos, from.length(), to);
	}

	return string;
}

std::string Utilities::String::ReplaceLastOf(const std::string& string, const std::string& from, const std::wstring& to)
{
	return ReplaceLastOf(string, from, ToString(to));
}

std::string Utilities::String::ReplaceLastOf(const std::string& string, const std::wstring& from, const std::string& to)
{
	return ReplaceLastOf(string, ToString(from), to);
}

std::string Utilities::String::ReplaceLastOf(const std::string& string, const std::wstring& from, const std::wstring& to)
{
	return ReplaceLastOf(string, ToString(from), ToString(to));
}

std::string Utilities::String::ReplaceLastOf(const char* cString, const char* from, const char* to)
{
    return ReplaceLastOf(ToString(cString), ToString(from), ToString(to));
}


std::wstring Utilities::String::ReplaceLastOf(std::wstring wString, const std::wstring& from, const std::wstring& to)
{
	if (from.empty())
	{
		return wString;
	}

	size_t start_pos = wString.rfind(from);
	if (start_pos != std::wstring::npos)
	{
		wString.replace(start_pos, from.length(), to);
	}

	return wString;
}

std::wstring Utilities::String::ReplaceLastOf(const std::wstring& wString, const std::wstring& from, const std::string& to)
{
	return ReplaceLastOf(wString, from, ToWString(to));
}

std::wstring Utilities::String::ReplaceLastOf(const std::wstring& wString, const std::string& from, const std::wstring& to)
{
	return ReplaceLastOf(wString, ToWString(from), to);
}

std::wstring Utilities::String::ReplaceLastOf(const std::wstring& wString, const std::string& from, const std::string& to)
{
	return ReplaceLastOf(wString, ToWString(from), ToWString(to));
}

std::wstring Utilities::String::ReplaceLastOf(const wchar_t* wcString, const wchar_t* from, const wchar_t* to)
{
    return ReplaceLastOf(ToWString(wcString), ToWString(from), ToWString(to));
}




bool Utilities::String::Contains(const std::string& string, const std::string& substring, const bool& useCase)
{
    if (string.empty() || substring.empty())
        return false;

    if (useCase)
        return string.find(substring) != std::string::npos;

    std::string stringLower = ToLowerCase(string);
    std::string substringLower = ToLowerCase(substring);
    return stringLower.find(substringLower) != std::string::npos;
}

bool Utilities::String::Contains(const std::string& string, const std::wstring& substring, const bool& useCase)
{
    return Contains(string, ToString(substring), useCase);
}

bool Utilities::String::Contains(const char* cString, const char* substring, const bool& useCase)
{
    return Contains(ToString(cString), ToString(substring), useCase);
}


bool Utilities::String::Contains(const std::wstring& wString, const std::wstring& substring, const bool& useCase)
{
    if (wString.empty() || substring.empty())
        return false;

    if (useCase)
        return wString.find(substring) != std::wstring::npos;

    std::wstring wStringLower = ToLowerCase(wString);
    std::wstring substringLower = ToLowerCase(substring);
    return wStringLower.find(substringLower) != std::wstring::npos;
}

bool Utilities::String::Contains(const std::wstring& wString, const std::string& substring, const bool& useCase)
{
    return Contains(wString, ToWString(substring), useCase);
}

bool Utilities::String::Contains(const wchar_t* wcString, const wchar_t* substring, const bool& useCase)
{
    return Contains(ToWString(wcString), ToWString(substring), useCase);
}




bool Utilities::String::StartsWith(const std::string& string, const std::string& substring, const bool& useCase)
{
    if (substring.empty())
        return true;

    if (string.empty() || string.length() < substring.length())
        return false;

    if (useCase)
        return string.compare(0, substring.length(), substring) == 0;

    std::string stringLower = ToLowerCase(string);
    std::string substringLower = ToLowerCase(substring);
    return stringLower.compare(0, substringLower.length(), substringLower) == 0;
}

bool Utilities::String::StartsWith(const std::string& string, const std::wstring& substring, const bool& useCase)
{
    return StartsWith(string, ToString(substring), useCase);
}

bool Utilities::String::StartsWith(const char* cString, const char* substring, const bool& useCase)
{
    return StartsWith(ToString(cString), ToString(substring), useCase);
}


bool Utilities::String::StartsWith(const std::wstring& wString, const std::wstring& substring, const bool& useCase)
{
    if (substring.empty())
        return true;

    if (wString.empty() || wString.length() < substring.length())
        return false;

    if (useCase)
        return wString.compare(0, substring.length(), substring) == 0;

    std::wstring wStringLower = ToLowerCase(wString);
    std::wstring substringLower = ToLowerCase(substring);
    return wStringLower.compare(0, substringLower.length(), substringLower) == 0;
}

bool Utilities::String::StartsWith(const std::wstring& wString, const std::string& substring, const bool& useCase)
{
    return StartsWith(wString, ToWString(substring), useCase);
}

bool Utilities::String::StartsWith(const wchar_t* wcString, const wchar_t* substring, const bool& useCase)
{
    return StartsWith(ToWString(wcString), ToWString(substring), useCase);
}




bool Utilities::String::EndsWith(const std::string& string, const std::string& substring, const bool& useCase)
{
    if (substring.empty())
        return true;

    if (string.empty() || string.length() < substring.length())
        return false;

    if (useCase)
        return string.compare(string.length() - substring.length(), substring.length(), substring) == 0;

    std::string stringLower = ToLowerCase(string);
    std::string substringLower = ToLowerCase(substring);
    return stringLower.compare(stringLower.length() - substringLower.length(), substringLower.length(), substringLower) == 0;
}

bool Utilities::String::EndsWith(const std::string& string, const std::wstring& substring, const bool& useCase)
{
    return EndsWith(string, ToString(substring), useCase);
}

bool Utilities::String::EndsWith(const char* cString, const char* substring, const bool& useCase)
{
    return EndsWith(ToString(cString), ToString(substring), useCase);
}


bool Utilities::String::EndsWith(const std::wstring& wString, const std::wstring& substring, const bool& useCase)
{
    if (substring.empty())
        return true;

    if (wString.empty() || wString.length() < substring.length())
        return false;

    if (useCase)
        return wString.compare(wString.length() - substring.length(), substring.length(), substring) == 0;

    std::wstring wStringLower = ToLowerCase(wString);
    std::wstring substringLower = ToLowerCase(substring);
    return wStringLower.compare(wStringLower.length() - substringLower.length(), substringLower.length(), substringLower) == 0;
}

bool Utilities::String::EndsWith(const std::wstring& wString, const std::string& substring, const bool& useCase)
{
    return EndsWith(wString, ToWString(substring), useCase);
}

bool Utilities::String::EndsWith(const wchar_t* wcString, const wchar_t* substring, const bool& useCase)
{
    return EndsWith(ToWString(wcString), ToWString(substring), useCase);
}




std::vector<std::string> Utilities::String::Split(const std::string& string, const char& separator, const bool& removeSeparatorSpaces)
{
	std::vector<std::string> outCollection;

	if (string.empty())
		return outCollection;

	size_t position = 0;
	while (true)
	{
		const size_t separatorPosition = string.find(separator, position);

		std::string token = (separatorPosition == std::string::npos)
			? string.substr(position)
			: string.substr(position, separatorPosition - position);

		if (removeSeparatorSpaces)
		{
			size_t first = 0;
			while (first < token.size() && std::isspace(token[first]))
				++first;

			size_t last = token.size();
			while (last > first && std::isspace(token[last - 1]))
				--last;

			token = token.substr(first, last - first);
		}

		if (token.empty() == false)
			outCollection.push_back(token);

		if (separatorPosition == std::string::npos)
			break;

		position = separatorPosition + 1;
	}

	return outCollection;
}

std::vector<std::string> Utilities::String::Split(const std::wstring& wString, const char& separator, const bool& removeSeparatorSpaces)
{
	std::string string = ToString(wString);
	return Split(string, separator, removeSeparatorSpaces);
}

std::vector<std::string> Utilities::String::Split(const char* cString, const char& separator, const bool& removeSeparatorSpaces)
{
	std::string string = ToString(cString);
	return Split(string, separator, removeSeparatorSpaces);
}

std::vector<std::string> Utilities::String::Split(const wchar_t* wcString, const char& separator, const bool& removeSeparatorSpaces)
{
	std::string string = ToString(wcString);
	return Split(string, separator, removeSeparatorSpaces);
}


std::vector<std::wstring> Utilities::String::Split(const std::string& string, const wchar_t& separator, const bool& removeSeparatorSpaces)
{
	std::wstring wString = ToWString(string);
	return Split(wString, separator, removeSeparatorSpaces);
}

std::vector<std::wstring> Utilities::String::Split(const std::wstring& wideString, const wchar_t& separator, const bool& removeSeparatorSpaces)
{
	std::vector<std::wstring> outCollection;

	if (wideString.empty())
		return outCollection;

	size_t position = 0;
	while (true)
	{
		const size_t separatorPosition = wideString.find(separator, position);

		std::wstring token = (separatorPosition == std::wstring::npos)
			? wideString.substr(position)
			: wideString.substr(position, separatorPosition - position);

		if (removeSeparatorSpaces)
		{
			size_t first = 0;
			while (first < token.size() && std::iswspace(token[first]))
				++first;

			size_t last = token.size();
			while (last > first && std::iswspace(token[last - 1]))
				--last;

			token = token.substr(first, last - first);
		}

		if (token.empty() == false)
			outCollection.push_back(token);

		if (separatorPosition == std::wstring::npos)
			break;

		position = separatorPosition + 1;
	}

	return outCollection;
}

std::vector<std::wstring> Utilities::String::Split(const char* cString, const wchar_t& separator, const bool& removeSeparatorSpaces)
{
	std::wstring wString = ToWString(cString);
	return Split(wString, separator, removeSeparatorSpaces);
}

std::vector<std::wstring> Utilities::String::Split(const wchar_t* wcString, const wchar_t& separator, const bool& removeSeparatorSpaces)
{
	std::wstring wString = ToWString(wcString);
	return Split(wString, separator, removeSeparatorSpaces);
}




std::string Utilities::String::Reverse(std::string string)
{
    std::reverse(string.begin(), string.end());
    return string;
}

std::wstring Utilities::String::Reverse(std::wstring wString)
{
    std::reverse(wString.begin(), wString.end());
    return wString;
}

std::string Utilities::String::Reverse(const char* cString)
{
    return Reverse(ToString(cString));
}

std::wstring Utilities::String::Reverse(const wchar_t* wcString)
{
    return Reverse(ToWString(wcString));
}




bool Utilities::String::IsNumeric(const std::string& string)
{
    if (string.empty())
        return false;

    int64_t intValue;
    double doubleValue;

    return (ToInt64(string, &intValue) || ToDouble(string, &doubleValue));
}

bool Utilities::String::IsNumeric(const std::wstring& wString)
{
    return IsNumeric(ToString(wString));
}

bool Utilities::String::IsNumeric(const char* cString)
{
    return IsNumeric(ToString(cString));
}

bool Utilities::String::IsNumeric(const wchar_t* wcString)
{
    return IsNumeric(ToWString(wcString));
}




bool Utilities::Directory::Exists(const std::string& directoryPath)
{
    return Directory::Exists(String::ToWString(directoryPath));
}

bool Utilities::Directory::Exists(const std::wstring& directoryPath)
{
    DWORD fileAttributes = GetFileAttributesW(directoryPath.c_str());

    if (fileAttributes == INVALID_FILE_ATTRIBUTES) // Check if path doesn't exist or is inaccessible.
    {
        return false;
    }

    if ((fileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) // Check if path isn't a directory.
    {
        return false;
    }

    return true;
}


bool Utilities::Directory::Create(const std::string& directoryPath)
{
    return Directory::Create(String::ToWString(directoryPath));
}

bool Utilities::Directory::Create(const std::wstring& directoryPath)
{
    if (CreateDirectoryW(directoryPath.c_str(), nullptr) == false) // Check if directory creation failed.
    {
        return false;
    }

    return true;
}


bool Utilities::Directory::Destroy(const std::string& directoryPath, const bool& deleteContents)
{
    return Directory::Destroy(String::ToWString(directoryPath), deleteContents);
}

bool Utilities::Directory::Destroy(const std::wstring& directoryPath, const bool& deleteContents)
{
    if (deleteContents)
    {
        std::wstring searchPath = directoryPath + L"\\*";
        WIN32_FIND_DATAW findData;
        HANDLE hFind = FindFirstFileW(searchPath.c_str(), &findData);

        if (hFind != INVALID_HANDLE_VALUE) // Check if directory can be read.
        {
            do
            {
                // Skip current and parent directory markers.
                if ((wcscmp(findData.cFileName, L".") == 0) || (wcscmp(findData.cFileName, L"..") == 0))
                {
                    continue;
                }

                std::wstring itemPath = directoryPath + L"\\" + findData.cFileName;

                if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    Directory::Destroy(itemPath, true);
                }
                else
                {
                    File::Destroy(itemPath);
                }

            } while (FindNextFileW(hFind, &findData) != 0);

            FindClose(hFind);
        }
    }

    if (RemoveDirectoryW(directoryPath.c_str()) == false) // Check if directory removal failed (e.g., if it's not empty and deleteContents is false).
    {
        return false;
    }

    return true;
}






bool Utilities::File::Exists(const std::string& filePath)
{
    return File::Exists(String::ToWString(filePath));
}

bool Utilities::File::Exists(const std::wstring& filePath)
{
    DWORD fileAttributes = GetFileAttributesW(filePath.c_str());

    if (fileAttributes == INVALID_FILE_ATTRIBUTES) // Check if path doesn't exist or is inaccessible.
    {
        return false;
    }

    if (fileAttributes & FILE_ATTRIBUTE_DIRECTORY) // Check if path is a directory rather than a file.
    {
        return false;
    }

    return true;
}


bool Utilities::File::ReadText(const std::string& filePath, std::string* outContents)
{
    return File::ReadText(String::ToWString(filePath), outContents);
}

bool Utilities::File::ReadText(const std::wstring& filePath, std::string* outContents)
{
    if (outContents == nullptr)
    {
        return false;
    }

    HANDLE hFile = CreateFileW(
        filePath.c_str(),      // File path.
        GENERIC_READ,          // Desired access.
        FILE_SHARE_READ,       // Shared access.
        nullptr,               // Security attributes.
        OPEN_EXISTING,         // Creation disposition.
        FILE_ATTRIBUTE_NORMAL, // Flags and attributes.
        nullptr                // Template file.
    );

    if (hFile == INVALID_HANDLE_VALUE) // Check if handle isn't valid.
    {
        return false;
    }

    LARGE_INTEGER fileSize;
    if (GetFileSizeEx(hFile, &fileSize) == false)
    {
        CloseHandle(hFile);
        return false;
    }

    outContents->resize(fileSize.QuadPart);

    DWORD bytesRead;
    if (ReadFile(hFile, outContents->data(), static_cast<DWORD>(fileSize.QuadPart), &bytesRead, nullptr) == false)
    {
        outContents->clear();
        CloseHandle(hFile);
        return false;
    }

    CloseHandle(hFile);
    return true;
}


bool Utilities::File::ReadTextUtf16(const std::string& filePath, std::wstring* outContents)
{
    return File::ReadTextUtf16(String::ToWString(filePath), outContents);
}

bool Utilities::File::ReadTextUtf16(const std::wstring& filePath, std::wstring* outContents)
{
    if (outContents == nullptr)
    {
        return false;
    }

    HANDLE hFile = CreateFileW(
        filePath.c_str(),      // File path.
        GENERIC_READ,          // Desired access.
        FILE_SHARE_READ,       // Shared access.
        nullptr,               // Security attributes.
        OPEN_EXISTING,         // Creation disposition.
        FILE_ATTRIBUTE_NORMAL, // Flags and attributes.
        nullptr                // Template file.
    );

    if (hFile == INVALID_HANDLE_VALUE) // Check if handle isn't valid.
    {
        return false;
    }

    LARGE_INTEGER fileSize;
    if (GetFileSizeEx(hFile, &fileSize) == false)
    {
        CloseHandle(hFile);
        return false;
    }

    if (fileSize.QuadPart % sizeof(wchar_t) != 0) // File size must be multiple of sizeof(wchar_t).
    {
        CloseHandle(hFile);
        return false;
    }

    size_t wCharCount = fileSize.QuadPart / sizeof(wchar_t);

    outContents->resize(wCharCount);

    DWORD bytesRead;
    if (ReadFile(hFile, outContents->data(), static_cast<DWORD>(fileSize.QuadPart), &bytesRead, nullptr) == false)
    {
        outContents->clear();
        CloseHandle(hFile);
        return false;
    }

    CloseHandle(hFile);
    return true;
}


bool Utilities::File::ReadLines(const std::string& filePath, std::vector<std::string>* outLines)
{
    return File::ReadLines(String::ToWString(filePath), outLines);
}

bool Utilities::File::ReadLines(const std::wstring& filePath, std::vector<std::string>* outLines)
{
    if (outLines == nullptr)
    {
        return false;
    }

    std::string fileContents;
    if (File::ReadText(filePath, &fileContents) == false)
    {
        return false;
    }

    outLines->clear();
    size_t start = 0;
    size_t pos = 0;

    while ((pos = fileContents.find('\n', start)) != std::string::npos)
    {
        std::string line = fileContents.substr(start, pos - start);

        if ((line.empty() == false) && line.back() == '\r')
        {
            line.pop_back();
        }

        outLines->push_back(std::move(line));
        start = pos + 1;
    }

    /* Add last line if it isn't empty. */
    if (start < fileContents.size())
    {
        std::string line = fileContents.substr(start);

        if ((line.empty() == false) && line.back() == '\r')
        {
            line.pop_back();
        }

        outLines->push_back(std::move(line));
    }

    return true;
}


bool Utilities::File::ReadLinesUtf16(const std::string& filePath, std::vector<std::wstring>* outLines)
{
    return File::ReadLinesUtf16(String::ToWString(filePath), outLines);
}

bool Utilities::File::ReadLinesUtf16(const std::wstring& filePath, std::vector<std::wstring>* outLines)
{
    if (outLines == nullptr)
    {
        return false;
    }

    std::wstring fileContents;
    if (File::ReadTextUtf16(filePath, &fileContents) == false)
    {
        return false;
    }

    outLines->clear();
    size_t start = 0;
    size_t pos = 0;

    while ((pos = fileContents.find(L'\n', start)) != std::wstring::npos)
    {
        std::wstring line = fileContents.substr(start, pos - start);

        if ((line.empty() == false) && line.back() == L'\r')
        {
            line.pop_back();
        }

        outLines->push_back(std::move(line));
        start = pos + 1;
    }

    if (start < fileContents.size())
    {
        std::wstring line = fileContents.substr(start);

        if ((line.empty() == false) && line.back() == L'\r')
        {
            line.pop_back();
        }

        outLines->push_back(std::move(line));
    }

    return true;
}


bool Utilities::File::WriteText(const std::string& filePath, const std::string& text)
{
    return File::WriteText(String::ToWString(filePath), text);
}

bool Utilities::File::WriteText(const std::wstring& filePath, const std::string& text)
{
    HANDLE hFile = CreateFileW(
        filePath.c_str(),      // File path.
        GENERIC_WRITE,         // Desired access.
        0,                     // Shared access.
        nullptr,               // Security attributes.
        CREATE_ALWAYS,         // Creation disposition.
        FILE_ATTRIBUTE_NORMAL, // Flags and attributes.
        nullptr                // Template file.
    );

    if (hFile == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD bytesWritten;
    if (WriteFile(hFile, text.c_str(), static_cast<DWORD>(text.size()), &bytesWritten, nullptr) == false)
    {
        CloseHandle(hFile);
        return false;
    }

    CloseHandle(hFile);
    return true;
}


bool Utilities::File::WriteTextUtf16(const std::string& filePath, const std::wstring& text)
{
    return File::WriteTextUtf16(String::ToWString(filePath), text);
}

bool Utilities::File::WriteTextUtf16(const std::wstring& filePath, const std::wstring& text)
{
    HANDLE hFile = CreateFileW(
        filePath.c_str(),      // File path.
        GENERIC_WRITE,         // Desired access.
        0,                     // Shared access.
        nullptr,               // Security attributes.
        CREATE_ALWAYS,         // Creation disposition.
        FILE_ATTRIBUTE_NORMAL, // Flags and attributes.
        nullptr                // Template file.
    );

    if (hFile == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD bytesWritten;
    if (WriteFile(hFile, text.c_str(), static_cast<DWORD>(text.size() * sizeof(wchar_t)), &bytesWritten, nullptr) == false)
    {
        CloseHandle(hFile);
        return false;
    }

    CloseHandle(hFile);
    return true;
}


bool Utilities::File::WriteLines(const std::string& filePath, const std::vector<std::string>& lines)
{
    return WriteLines(String::ToWString(filePath), lines);
}

bool Utilities::File::WriteLines(const std::wstring& filePath, const std::vector<std::string>& lines)
{
    std::string content;

    size_t totalSize = 0;
    for (const auto& line : lines)
    {
        totalSize += line.size() + 1; // Account for potential '\n'.
    }

    content.reserve(totalSize);
    bool first = true;

    for (const auto& line : lines)
    {
        if (first == false)
            content.append("\n");

        content.append(line);
        first = false;
    }

    return WriteText(filePath, content);
}

bool Utilities::File::WriteLinesUtf16(const std::string& filePath, const std::vector<std::wstring>& lines)
{
    return WriteLinesUtf16(String::ToWString(filePath), lines);
}

bool Utilities::File::WriteLinesUtf16(const std::wstring& filePath, const std::vector<std::wstring>& lines)
{
    std::wstring content;

    size_t totalSize = 0;
    for (const auto& line : lines)
    {
        totalSize += line.size() + 1; // Account for potential '\n'.
    }

    content.reserve(totalSize);
    bool first = true;

    for (const auto& line : lines)
    {
        if (first == false)
            content.append(L"\n");

        content.append(line);
        first = false;
    }

    return WriteTextUtf16(filePath, content);
}


bool Utilities::File::AppendText(const std::string& filePath, const std::string& text)
{
    return File::AppendText(String::ToWString(filePath), text);
}

bool Utilities::File::AppendText(const std::wstring& filePath, const std::string& text)
{
    HANDLE hFile = CreateFileW(
        filePath.c_str(),      // File path.
        FILE_APPEND_DATA,      // Desired access (Append only).
        0,                     // Shared access.
        nullptr,               // Security attributes.
        OPEN_ALWAYS,           // Creation disposition (Open existing or create new).
        FILE_ATTRIBUTE_NORMAL, // Flags and attributes.
        nullptr                // Template file.
    );

    if (hFile == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD bytesWritten;
    if (WriteFile(hFile, text.c_str(), static_cast<DWORD>(text.size()), &bytesWritten, nullptr) == false)
    {
        CloseHandle(hFile);
        return false;
    }

    CloseHandle(hFile);
    return true;
}

bool Utilities::File::AppendTextUtf16(const std::string& filePath, const std::wstring& text)
{
    return File::AppendTextUtf16(String::ToWString(filePath), text);
}

bool Utilities::File::AppendTextUtf16(const std::wstring& filePath, const std::wstring& text)
{
    HANDLE hFile = CreateFileW(
        filePath.c_str(),      // File path.
        FILE_APPEND_DATA,      // Desired access (Append only).
        0,                     // Shared access.
        nullptr,               // Security attributes.
        OPEN_ALWAYS,           // Creation disposition (Open existing or create new).
        FILE_ATTRIBUTE_NORMAL, // Flags and attributes.
        nullptr                // Template file.
    );

    if (hFile == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD bytesWritten;
    if (WriteFile(hFile, text.c_str(), static_cast<DWORD>(text.size() * sizeof(wchar_t)), &bytesWritten, nullptr) == false)
    {
        CloseHandle(hFile);
        return false;
    }

    CloseHandle(hFile);
    return true;
}


bool Utilities::File::AppendLine(const std::string& filePath, const std::string& line)
{
    return File::AppendLine(String::ToWString(filePath), line);
}

bool Utilities::File::AppendLine(const std::wstring& filePath, const std::string& line)
{
    std::string content = line + '\n';
    return File::AppendText(filePath, content);
}

bool Utilities::File::AppendLineUtf16(const std::string& filePath, const std::wstring& line)
{
    return File::AppendLineUtf16(String::ToWString(filePath), line);
}

bool Utilities::File::AppendLineUtf16(const std::wstring& filePath, const std::wstring& line)
{
    std::wstring content = line + L'\n';
    return File::AppendTextUtf16(filePath, content);
}


bool Utilities::File::AppendLines(const std::string& filePath, const std::vector<std::string>& lines)
{
    return File::AppendLines(String::ToWString(filePath), lines);
}

bool Utilities::File::AppendLines(const std::wstring& filePath, const std::vector<std::string>& lines)
{
    std::string content;

    size_t totalSize = 0;
    for (const std::string& line : lines)
    {
        totalSize += line.size() + 1; // +1 for '\n'.
    }

    content.reserve(totalSize);

    for (const std::string& line : lines)
    {
        content += line;
        content += '\n';
    }

    return File::AppendText(filePath, content);
}

bool Utilities::File::AppendLinesUtf16(const std::string& filePath, const std::vector<std::wstring>& lines)
{
    return File::AppendLinesUtf16(String::ToWString(filePath), lines);
}

bool Utilities::File::AppendLinesUtf16(const std::wstring& filePath, const std::vector<std::wstring>& lines)
{
    std::wstring content;

    size_t totalSize = 0;
    for (const std::wstring& line : lines)
    {
        totalSize += line.size() + 1; // +1 for L'\n'.
    }

    content.reserve(totalSize);

    for (const std::wstring& line : lines)
    {
        content += line;
        content += L'\n';
    }

    return File::AppendTextUtf16(filePath, content);
}


bool Utilities::File::Destroy(const std::string& filePath)
{
    return File::Destroy(String::ToWString(filePath));
}

bool Utilities::File::Destroy(const std::wstring& filePath)
{
    if (DeleteFileW(filePath.c_str()) == false) // Check if file deletion failed.
    {
        return false;
    }

    return true;
}




LONG Utilities::Exception::Handle(LPEXCEPTION_POINTERS exceptionInfo, const char* title)
{
#ifdef ENABLE_LOGGING
    void* crashAddress = exceptionInfo->ExceptionRecord->ExceptionAddress;

    HMODULE hModule = GetModuleHandle(nullptr);
    uintptr_t baseAddress = (uintptr_t)hModule;
    uintptr_t relativeOffset = (uintptr_t)crashAddress - baseAddress;

    std::string exceptionTitle = title != nullptr ? title : "FAILED TO READ TITLE";
    std::stringstream stringStream;
    stringStream << "[" << exceptionTitle << "]\n";
    stringStream << "Exception Code: 0x" << std::hex << std::uppercase << exceptionInfo->ExceptionRecord->ExceptionCode << "\n";
    stringStream << "Absolute Address: 0x" << crashAddress << "\n";
    stringStream << "Module Base:      0x" << (void*)baseAddress << "\n";
    stringStream << "Relative Offset:  +0x" << relativeOffset << "\n";
    stringStream << Utilities::Time::GetUtcDate() << "\n";
    stringStream << "\n--------------------------------------------------\n";

    std::string outString = stringStream.str();
    printf(outString.c_str());

    FileInstance exceptionsFile(PATH_LOG_EXCEPTIONS);
    exceptionsFile.AppendLine(stringStream.str());
#endif

    return EXCEPTION_EXECUTE_HANDLER;
}






// ========================================================
// |                      #INTERNAL                       |
// ========================================================
bool Utilities::Memory::Internal::IsValidPtr(const void* memoryPtr)
{
    MEMORY_BASIC_INFORMATION mbi;

    if (VirtualQuery(memoryPtr, &mbi, sizeof(mbi)) != sizeof(mbi)) // Try to request (query) information about the given memory region, return False if attempt fails.
        return false;

    if (mbi.State != MEM_COMMIT) // Memory region must be commited (actually backed by physical memory). Return False if it's not.
        return false;

    /* Strip out guard and cache flags to examine the core protection flags. */
    DWORD protectionFlags = mbi.Protect & ~(PAGE_GUARD | PAGE_NOCACHE | PAGE_WRITECOMBINE);
    if ((protectionFlags & (PAGE_READONLY | PAGE_READWRITE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE)) == false) // See if we're able to request one of the read permissions (readable or executable+read), return False if we aren't.
        return false;

    return true;
}

bool Utilities::Memory::Internal::IsValidAddress(const uintptr_t& memoryAddress)
{
    void* memoryPtr = reinterpret_cast<void*>(memoryAddress);
    return IsValidPtr(memoryPtr);
}




void* Utilities::Memory::Internal::PtrAddOffset(const void* memoryPtr, size_t offset)
{
    /* Since void* doesn't support pointer arithmetics, we need to convert it to uintptr_t first. */
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PtrAddOffset(memoryAddress, offset);
}

void* Utilities::Memory::Internal::PtrAddOffset(const uintptr_t& memoryAddress, size_t offset)
{
    /* Calculate the new address by adding the offset. */
    uintptr_t newMemoryAddress = AddressAddOffset(memoryAddress, offset);
    if (newMemoryAddress == 0x0) // Return null pointer if memory region is invalid.
        return nullptr;

    return reinterpret_cast<void*>(newMemoryAddress);
}


uintptr_t Utilities::Memory::Internal::AddressAddOffset(const void* memoryPtr, size_t offset)
{
    /* Since void* doesn't support pointer arithmetics, we need to convert it to uintptr_t first. */
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return AddressAddOffset(memoryAddress, offset);
}

uintptr_t Utilities::Memory::Internal::AddressAddOffset(const uintptr_t& memoryAddress, size_t offset)
{
    /* Calculate the new address by adding the offset. */
    uintptr_t newMemoryAddress = memoryAddress + offset;

    /* Before dereferencing, verify we can read sizeof(uintptr_t) bytes at 'newMemoryAddress'. */
    /* Abort and return 0 if memory isn't readable */
    if (IsValidAddress(newMemoryAddress) == false ||
        IsValidAddress((newMemoryAddress + sizeof(uintptr_t) - 1)) == false)
        return 0x0;

    /* Return the valid address */
    return newMemoryAddress;
}




void* Utilities::Memory::Internal::PtrDereference(const void* memoryPtr, size_t offset)
{
    /* Since void* doesn't support pointer arithmetics, we need to convert it to uintptr_t first. */
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PtrDereference(memoryAddress, offset);
}

void* Utilities::Memory::Internal::PtrDereference(const uintptr_t& memoryAddress, size_t offset)
{
    /* Get the dereferenced address. */
    uintptr_t newMemoryAddress = AddressDereference(memoryAddress, offset);
    if (newMemoryAddress == 0x0) // Return null pointer if memory region is invalid.
        return nullptr;

    return reinterpret_cast<void*>(newMemoryAddress);
}

uintptr_t Utilities::Memory::Internal::AddressDereference(const void* memoryPtr, size_t offset)
{
    /* Since void* doesn't support pointer arithmetics, we need to convert it to uintptr_t first. */
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return AddressDereference(memoryAddress, offset);
}

uintptr_t Utilities::Memory::Internal::AddressDereference(const uintptr_t& memoryAddress, size_t offset)
{
    /* Calculate the target address by adding the offset. */
    uintptr_t targetAddress = memoryAddress + offset;

    /* Verify we can safely read sizeof(uintptr_t) bytes at 'targetAddress'. */
    if (IsValidAddress(targetAddress) == false ||
        IsValidAddress((targetAddress + sizeof(uintptr_t) - 1)) == false)
        return 0x0;

    /* Dereference and return the read value. */
    return *reinterpret_cast<uintptr_t*>(targetAddress);
}




void* Utilities::Memory::Internal::PtrFollowPointerChain(const void* memoryPtr, const std::vector<uintptr_t>& memoryOffsets)
{
    /* Since void* doesn't support pointer arithmetics, we need to convert it to uintptr_t first. */
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);

    /* Calculate the new address by following the pointer chain. */
    uintptr_t newMemoryAddress = AddressFollowPointerChain(memoryAddress, memoryOffsets);
    if (newMemoryAddress == 0x0) // Return null pointer if memory region is invalid.
        return nullptr;

    return reinterpret_cast<void*>(newMemoryAddress);
}

uintptr_t Utilities::Memory::Internal::AddressFollowPointerChain(const uintptr_t& memoryAddress, const std::vector<uintptr_t>& memoryOffsets)
{
    uintptr_t newMemoryAddress = memoryAddress;
    size_t offsetsCount = memoryOffsets.size();

    for (size_t i = 0; i < offsetsCount; ++i)
    {
        /* Before dereferencing, verify we can read sizeof(uintptr_t) bytes at 'newMemoryAddress'. */
        /* Abort and return 0 if memory isn't readable */
        if (IsValidAddress(newMemoryAddress) == false ||
            IsValidAddress((newMemoryAddress + sizeof(uintptr_t) - 1)) == false)
            return 0x0;

        /* Read the next pointer value from memory and add the current offset to advance to the next address in the chain. */
        newMemoryAddress = *reinterpret_cast<uintptr_t*>(newMemoryAddress);
        newMemoryAddress += memoryOffsets[i];
    }

    /* After processing all offsets, 'ptr' should point to the final data. */
    return newMemoryAddress;
}




bool Utilities::Memory::Internal::GetBool(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetBool(memoryAddress);
}

bool Utilities::Memory::Internal::GetBool(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read and return the boolean value from the target address. */
    return *reinterpret_cast<bool*>(memoryAddress);
}

bool Utilities::Memory::Internal::SetBool(const void* memoryPtr, bool newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetBool(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::SetBool(const uintptr_t& memoryAddress, bool newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Cast the address to bool* */
    bool* targetBool = reinterpret_cast<bool*>(memoryAddress);
    size_t byteSize = sizeof(bool);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetBool, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new boolean value. */
    *targetBool = newValue;

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetBool, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::PatchBool(const void* memoryPtr, bool from, bool to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchBool(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::PatchBool(const uintptr_t& memoryAddress, bool from, bool to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    bool* targetBool = reinterpret_cast<bool*>(memoryAddress);
    if (*targetBool != from) // Only patch if the current value matches 'from'.
        return false;
    size_t byteSize = sizeof(bool);

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(targetBool, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new boolean value */
    *targetBool = to;

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(targetBool, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::IndirectGetBool(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetBool(memoryAddress);
}

bool Utilities::Memory::Internal::IndirectGetBool(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (!IsValidAddress(dataAddress))
        return false;

    /* Read and return the boolean value from the target address. */
    return *reinterpret_cast<bool*>(dataAddress);
}

bool Utilities::Memory::Internal::IndirectSetBool(const void* memoryPtr, bool newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetBool(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::IndirectSetBool(const uintptr_t& memoryAddress, bool newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Cast the address to bool* */
    bool* targetBool = reinterpret_cast<bool*>(dataAddress);
    size_t byteSize = sizeof(bool);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetBool, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new boolean value. */
    *targetBool = newValue;

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetBool, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::IndirectPatchBool(const void* memoryPtr, bool from, bool to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchBool(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::IndirectPatchBool(const uintptr_t& memoryAddress, bool from, bool to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    bool* targetBool = reinterpret_cast<bool*>(dataAddress);
    if (*targetBool != from) // Only patch if the current value matches 'from'.
        return false;
    size_t byteSize = sizeof(bool);

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(targetBool, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new boolean value */
    *targetBool = to;

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(targetBool, byteSize, oldProtect, &tmp);

    return true;
}




int8_t Utilities::Memory::Internal::GetInt8(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetInt8(memoryAddress);
}

int8_t Utilities::Memory::Internal::GetInt8(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return -1;

    /* Read and return the 8-bit integer from the target address. */
    return *reinterpret_cast<int8_t*>(memoryAddress);
}

bool Utilities::Memory::Internal::SetInt8(const void* memoryPtr, int8_t newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetInt8(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::SetInt8(const uintptr_t& memoryAddress, int8_t newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Cast the address to int8_t* */
    int8_t* targetInt = reinterpret_cast<int8_t*>(memoryAddress);
    size_t byteSize = sizeof(int8_t);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value. */
    *targetInt = newValue;

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetInt, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::PatchInt8(const void* memoryPtr, int8_t from, int8_t to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchInt8(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::PatchInt8(const uintptr_t& memoryAddress, int8_t from, int8_t to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    int8_t* targetInt = reinterpret_cast<int8_t*>(memoryAddress);
    if (*targetInt != from) // Only patch if the current value matches 'from'.
        return false;
    size_t byteSize = sizeof(int8_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value */
    *targetInt = to;

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(targetInt, byteSize, oldProtect, &tmp);

    return true;
}

int8_t Utilities::Memory::Internal::IndirectGetInt8(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetInt8(memoryAddress);
}

int8_t Utilities::Memory::Internal::IndirectGetInt8(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return -1;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (!IsValidAddress(dataAddress))
        return -1;

    /* Read and return the 8-bit integer from the target address. */
    return *reinterpret_cast<int8_t*>(dataAddress);
}

bool Utilities::Memory::Internal::IndirectSetInt8(const void* memoryPtr, int8_t newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetInt8(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::IndirectSetInt8(const uintptr_t& memoryAddress, int8_t newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Cast the address to int8_t* */
    int8_t* targetInt = reinterpret_cast<int8_t*>(dataAddress);
    size_t byteSize = sizeof(int8_t);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value. */
    *targetInt = newValue;

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetInt, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::IndirectPatchInt8(const void* memoryPtr, int8_t from, int8_t to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchInt8(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::IndirectPatchInt8(const uintptr_t& memoryAddress, int8_t from, int8_t to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    int8_t* targetInt = reinterpret_cast<int8_t*>(dataAddress);
    if (*targetInt != from) // Only patch if the current value matches 'from'.
        return false;
    size_t byteSize = sizeof(int8_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value */
    *targetInt = to;

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(targetInt, byteSize, oldProtect, &tmp);

    return true;
}





int16_t Utilities::Memory::Internal::GetInt16(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetInt16(memoryAddress);
}

int16_t Utilities::Memory::Internal::GetInt16(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return -1;

    /* Read and return the 16-bit integer from the target address. */
    return *reinterpret_cast<int16_t*>(memoryAddress);
}

bool Utilities::Memory::Internal::SetInt16(const void* memoryPtr, int16_t newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetInt16(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::SetInt16(const uintptr_t& memoryAddress, int16_t newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Cast the address to int16_t* */
    int16_t* targetInt = reinterpret_cast<int16_t*>(memoryAddress);
    size_t byteSize = sizeof(int16_t);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value. */
    *targetInt = newValue;

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetInt, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::PatchInt16(const void* memoryPtr, int16_t from, int16_t to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchInt16(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::PatchInt16(const uintptr_t& memoryAddress, int16_t from, int16_t to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    int16_t* targetInt = reinterpret_cast<int16_t*>(memoryAddress);
    if (*targetInt != from) // Only patch if the current value matches 'from'.
        return false;
    size_t byteSize = sizeof(int16_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value */
    *targetInt = to;

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(targetInt, byteSize, oldProtect, &tmp);

    return true;
}

int16_t Utilities::Memory::Internal::IndirectGetInt16(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetInt16(memoryAddress);
}

int16_t Utilities::Memory::Internal::IndirectGetInt16(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return -1;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (!IsValidAddress(dataAddress))
        return -1;

    /* Read and return the 16-bit integer from the target address. */
    return *reinterpret_cast<int16_t*>(dataAddress);
}

bool Utilities::Memory::Internal::IndirectSetInt16(const void* memoryPtr, int16_t newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetInt16(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::IndirectSetInt16(const uintptr_t& memoryAddress, int16_t newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Cast the address to int16_t* */
    int16_t* targetInt = reinterpret_cast<int16_t*>(dataAddress);
    size_t byteSize = sizeof(int16_t);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value. */
    *targetInt = newValue;

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetInt, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::IndirectPatchInt16(const void* memoryPtr, int16_t from, int16_t to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchInt16(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::IndirectPatchInt16(const uintptr_t& memoryAddress, int16_t from, int16_t to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    int16_t* targetInt = reinterpret_cast<int16_t*>(dataAddress);
    if (*targetInt != from) // Only patch if the current value matches 'from'.
        return false;
    size_t byteSize = sizeof(int16_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value */
    *targetInt = to;

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(targetInt, byteSize, oldProtect, &tmp);

    return true;
}





int32_t Utilities::Memory::Internal::GetInt32(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetInt32(memoryAddress);

}

int32_t Utilities::Memory::Internal::GetInt32(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return -1;

    /* Read and return the 32-bit integer from the target address. */
    return *reinterpret_cast<int32_t*>(memoryAddress);
}

bool Utilities::Memory::Internal::SetInt32(const void* memoryPtr, int32_t newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetInt32(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::SetInt32(const uintptr_t& memoryAddress, int32_t newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Cast the address to int32_t* */
    int32_t* targetInt = reinterpret_cast<int32_t*>(memoryAddress);
    size_t byteSize = sizeof(int32_t);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value. */
    *targetInt = newValue;

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetInt, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::PatchInt32(const void* memoryPtr, int32_t from, int32_t to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchInt32(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::PatchInt32(const uintptr_t& memoryAddress, int32_t from, int32_t to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    int32_t* targetInt = reinterpret_cast<int32_t*>(memoryAddress);
    if (*targetInt != from) // Only patch if the current value matches 'from'.
        return false;
    size_t byteSize = sizeof(int32_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value */
    *targetInt = to;

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(targetInt, byteSize, oldProtect, &tmp);

    return true;
}




int32_t Utilities::Memory::Internal::IndirectGetInt32(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetInt32(memoryAddress);
}

int32_t Utilities::Memory::Internal::IndirectGetInt32(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return -1;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (!IsValidAddress(dataAddress))
        return -1;

    /* Read and return the 32-bit integer from the target address. */
    return *reinterpret_cast<int32_t*>(dataAddress);
}

bool Utilities::Memory::Internal::IndirectSetInt32(const void* memoryPtr, int32_t newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetInt32(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::IndirectSetInt32(const uintptr_t& memoryAddress, int32_t newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Cast the address to int32_t* */
    int32_t* targetInt = reinterpret_cast<int32_t*>(dataAddress);
    size_t byteSize = sizeof(int32_t);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value. */
    *targetInt = newValue;

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetInt, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::IndirectPatchInt32(const void* memoryPtr, int32_t from, int32_t to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchInt32(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::IndirectPatchInt32(const uintptr_t& memoryAddress, int32_t from, int32_t to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    int32_t* targetInt = reinterpret_cast<int32_t*>(dataAddress);
    if (*targetInt != from) // Only patch if the current value matches 'from'.
        return false;
    size_t byteSize = sizeof(int32_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value */
    *targetInt = to;

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(targetInt, byteSize, oldProtect, &tmp);

    return true;
}




int64_t Utilities::Memory::Internal::GetInt64(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetInt64(memoryAddress);
}

int64_t Utilities::Memory::Internal::GetInt64(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return -1;

    /* Read and return the 64-bit integer from the target address. */
    return *reinterpret_cast<int64_t*>(memoryAddress);
}

bool Utilities::Memory::Internal::SetInt64(const void* memoryPtr, int64_t newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetInt64(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::SetInt64(const uintptr_t& memoryAddress, int64_t newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Cast the address to int64_t* */
    int64_t* targetInt = reinterpret_cast<int64_t*>(memoryAddress);
    size_t byteSize = sizeof(int64_t);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value. */
    *targetInt = newValue;

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetInt, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::PatchInt64(const void* memoryPtr, int64_t from, int64_t to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchInt64(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::PatchInt64(const uintptr_t& memoryAddress, int64_t from, int64_t to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    int64_t* targetInt = reinterpret_cast<int64_t*>(memoryAddress);
    if (*targetInt != from) // Only patch if the current value matches 'from'.
        return false;
    size_t byteSize = sizeof(int64_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value */
    *targetInt = to;

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(targetInt, byteSize, oldProtect, &tmp);

    return true;
}

int64_t Utilities::Memory::Internal::IndirectGetInt64(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetInt64(memoryAddress);
}

int64_t Utilities::Memory::Internal::IndirectGetInt64(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return -1;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (!IsValidAddress(dataAddress))
        return -1;

    /* Read and return the 64-bit integer from the target address. */
    return *reinterpret_cast<int64_t*>(dataAddress);
}

bool Utilities::Memory::Internal::IndirectSetInt64(const void* memoryPtr, int64_t newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetInt64(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::IndirectSetInt64(const uintptr_t& memoryAddress, int64_t newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Cast the address to int64_t* */
    int64_t* targetInt = reinterpret_cast<int64_t*>(dataAddress);
    size_t byteSize = sizeof(int64_t);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value. */
    *targetInt = newValue;

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetInt, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::IndirectPatchInt64(const void* memoryPtr, int64_t from, int64_t to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchInt64(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::IndirectPatchInt64(const uintptr_t& memoryAddress, int64_t from, int64_t to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    int64_t* targetInt = reinterpret_cast<int64_t*>(dataAddress);
    if (*targetInt != from) // Only patch if the current value matches 'from'.
        return false;
    size_t byteSize = sizeof(int64_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value */
    *targetInt = to;

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(targetInt, byteSize, oldProtect, &tmp);

    return true;
}




float Utilities::Memory::Internal::GetFloat(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetFloat(memoryAddress);
}

float Utilities::Memory::Internal::GetFloat(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return -1.0f;

    /* Read and return the 32-bit float from the target address. */
    return *reinterpret_cast<float*>(memoryAddress);
}

bool Utilities::Memory::Internal::SetFloat(const void* memoryPtr, float newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetFloat(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::SetFloat(const uintptr_t& memoryAddress, float newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Cast the address to float* */
    float* targetFloat = reinterpret_cast<float*>(memoryAddress);
    size_t byteSize = sizeof(float);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetFloat, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new float value. */
    *targetFloat = newValue;

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetFloat, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::PatchFloat(const void* memoryPtr, float from, float to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchFloat(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::PatchFloat(const uintptr_t& memoryAddress, float from, float to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    float* targetFloat = reinterpret_cast<float*>(memoryAddress);
    if (*targetFloat != from) // Only patch if the current value matches 'from'.
        return false;
    size_t byteSize = sizeof(float);

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(targetFloat, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new float value */
    *targetFloat = to;

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(targetFloat, byteSize, oldProtect, &tmp);

    return true;
}

float Utilities::Memory::Internal::IndirectGetFloat(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetFloat(memoryAddress);
}

float Utilities::Memory::Internal::IndirectGetFloat(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return -1.0f;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (!IsValidAddress(dataAddress))
        return -1.0f;

    /* Read and return the 32-bit float from the target address. */
    return *reinterpret_cast<float*>(dataAddress);
}

bool Utilities::Memory::Internal::IndirectSetFloat(const void* memoryPtr, float newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetFloat(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::IndirectSetFloat(const uintptr_t& memoryAddress, float newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Cast the address to float* */
    float* targetFloat = reinterpret_cast<float*>(dataAddress);
    size_t byteSize = sizeof(float);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetFloat, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new float value. */
    *targetFloat = newValue;

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetFloat, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::IndirectPatchFloat(const void* memoryPtr, float from, float to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchFloat(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::IndirectPatchFloat(const uintptr_t& memoryAddress, float from, float to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    float* targetFloat = reinterpret_cast<float*>(dataAddress);
    if (*targetFloat != from) // Only patch if the current value matches 'from'.
        return false;
    size_t byteSize = sizeof(float);

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(targetFloat, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new float value */
    *targetFloat = to;

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(targetFloat, byteSize, oldProtect, &tmp);

    return true;
}




double Utilities::Memory::Internal::GetDouble(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetDouble(memoryAddress);
}

double Utilities::Memory::Internal::GetDouble(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return -1.0;

    /* Read and return the double value from the target address. */
    return *reinterpret_cast<double*>(memoryAddress);
}

bool Utilities::Memory::Internal::SetDouble(const void* memoryPtr, double newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetDouble(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::SetDouble(const uintptr_t& memoryAddress, double newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Cast the address to double* */
    double* targetDouble = reinterpret_cast<double*>(memoryAddress);
    size_t byteSize = sizeof(double);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetDouble, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new double value. */
    *targetDouble = newValue;

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetDouble, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::PatchDouble(const void* memoryPtr, double from, double to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchDouble(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::PatchDouble(const uintptr_t& memoryAddress, double from, double to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    double* targetDouble = reinterpret_cast<double*>(memoryAddress);
    if (*targetDouble != from) // Only patch if the current value matches 'from'.
        return false;
    size_t byteSize = sizeof(double);

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(targetDouble, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new double value */
    *targetDouble = to;

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(targetDouble, byteSize, oldProtect, &tmp);

    return true;
}

double Utilities::Memory::Internal::IndirectGetDouble(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetDouble(memoryAddress);
}

double Utilities::Memory::Internal::IndirectGetDouble(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return -1.0;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (!IsValidAddress(dataAddress))
        return -1.0;

    /* Read and return the double value from the target address. */
    return *reinterpret_cast<double*>(dataAddress);
}

bool Utilities::Memory::Internal::IndirectSetDouble(const void* memoryPtr, double newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetDouble(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::IndirectSetDouble(const uintptr_t& memoryAddress, double newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Cast the address to double* */
    double* targetDouble = reinterpret_cast<double*>(dataAddress);
    size_t byteSize = sizeof(double);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetDouble, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new double value. */
    *targetDouble = newValue;

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetDouble, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::IndirectPatchDouble(const void* memoryPtr, double from, double to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchDouble(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::IndirectPatchDouble(const uintptr_t& memoryAddress, double from, double to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    double* targetDouble = reinterpret_cast<double*>(dataAddress);
    if (*targetDouble != from) // Only patch if the current value matches 'from'.
        return false;
    size_t byteSize = sizeof(double);

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(targetDouble, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new double value */
    *targetDouble = to;

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(targetDouble, byteSize, oldProtect, &tmp);

    return true;
}




std::string Utilities::Memory::Internal::GetString(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetString(memoryAddress);
}

std::string Utilities::Memory::Internal::GetString(const void* memoryPtr, size_t maxLength)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetString(memoryAddress, maxLength);
}

std::string Utilities::Memory::Internal::GetString(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return std::string();

    /* Read and return the string from the target address. */
    const char* strPtr = reinterpret_cast<const char*>(memoryAddress);
    return std::string(strPtr);
}

std::string Utilities::Memory::Internal::GetString(const uintptr_t& memoryAddress, size_t maxLength)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return std::string();

    /* Read and return the string from the target address. */
    const char* strPtr = reinterpret_cast<const char*>(memoryAddress);
    return std::string(strPtr, strnlen_s(strPtr, maxLength));
}

bool Utilities::Memory::Internal::SetString(const void* memoryPtr, const std::string& newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetString(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::SetString(const uintptr_t& memoryAddress, const std::string& newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Cast the address to char* */
    char* targetStr = reinterpret_cast<char*>(memoryAddress);
    size_t byteSize = newValue.size() + 1; // +1 for null terminator

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetStr, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new string value. */
    memcpy(targetStr, newValue.c_str(), byteSize);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetStr, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::PatchString(const void* memoryPtr, const std::string& from, const std::string& to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchString(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::PatchString(const uintptr_t& memoryAddress, const std::string& from, const std::string& to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    const char* currentStr = reinterpret_cast<const char*>(memoryAddress);
    if (strncmp(currentStr, from.c_str(), from.size()) != 0)
        return false;

    size_t byteSize = to.size() + 1;

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(reinterpret_cast<void*>(memoryAddress), byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new string value */
    memcpy(reinterpret_cast<void*>(memoryAddress), to.c_str(), byteSize);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(reinterpret_cast<void*>(memoryAddress), byteSize, oldProtect, &tmp);

    return true;
}




std::string Utilities::Memory::Internal::IndirectGetString(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetString(memoryAddress);
}

std::string Utilities::Memory::Internal::IndirectGetString(const void* memoryPtr, size_t maxLength)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetString(memoryAddress, maxLength);
}

std::string Utilities::Memory::Internal::IndirectGetString(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return std::string();

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (!IsValidAddress(dataAddress))
        return std::string();

    /* Read and return the string from the target address. */
    const char* strPtr = reinterpret_cast<const char*>(dataAddress);
    return std::string(strPtr);
}

std::string Utilities::Memory::Internal::IndirectGetString(const uintptr_t& memoryAddress, size_t maxLength)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return std::string();

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (!IsValidAddress(dataAddress))
        return std::string();

    /* Read and return the string from the target address. */
    const char* strPtr = reinterpret_cast<const char*>(dataAddress);
    return std::string(strPtr, strnlen_s(strPtr, maxLength));
}

bool Utilities::Memory::Internal::IndirectSetString(const void* memoryPtr, const std::string& newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetString(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::IndirectSetString(const uintptr_t& memoryAddress, const std::string& newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Cast the address to char* */
    char* targetStr = reinterpret_cast<char*>(dataAddress);
    size_t byteSize = newValue.size() + 1;

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetStr, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new string value. */
    memcpy(targetStr, newValue.c_str(), byteSize);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetStr, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::IndirectPatchString(const void* memoryPtr, const std::string& from, const std::string& to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchString(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::IndirectPatchString(const uintptr_t& memoryAddress, const std::string& from, const std::string& to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    const char* currentStr = reinterpret_cast<const char*>(dataAddress);
    if (strncmp(currentStr, from.c_str(), from.size()) != 0)
        return false;

    size_t byteSize = to.size() + 1;

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(reinterpret_cast<void*>(dataAddress), byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new string value */
    memcpy(reinterpret_cast<void*>(dataAddress), to.c_str(), byteSize);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(reinterpret_cast<void*>(dataAddress), byteSize, oldProtect, &tmp);

    return true;
}




std::wstring Utilities::Memory::Internal::GetWString(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetWString(memoryAddress);
}

std::wstring Utilities::Memory::Internal::GetWString(const void* memoryPtr, size_t maxLength)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetWString(memoryAddress, maxLength);
}

std::wstring Utilities::Memory::Internal::GetWString(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return std::wstring();

    /* Read and return the wide string from the target address. */
    const wchar_t* wStrPtr = reinterpret_cast<const wchar_t*>(memoryAddress);
    return std::wstring(wStrPtr);
}

std::wstring Utilities::Memory::Internal::GetWString(const uintptr_t& memoryAddress, size_t maxLength)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return std::wstring();

    /* Read and return the wide string from the target address. */
    const wchar_t* wStrPtr = reinterpret_cast<const wchar_t*>(memoryAddress);
    return std::wstring(wStrPtr, wcsnlen_s(wStrPtr, maxLength));
}

bool Utilities::Memory::Internal::SetWString(const void* memoryPtr, const std::wstring& newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetWString(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::SetWString(const uintptr_t& memoryAddress, const std::wstring& newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Cast the address to wchar_t* */
    wchar_t* targetStr = reinterpret_cast<wchar_t*>(memoryAddress);
    size_t byteSize = (newValue.size() + 1) * sizeof(wchar_t); // +1 for null terminator

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetStr, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new string value. */
    memcpy(targetStr, newValue.c_str(), byteSize);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetStr, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::PatchWString(const void* memoryPtr, const std::wstring& from, const std::wstring& to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchWString(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::PatchWString(const uintptr_t& memoryAddress, const std::wstring& from, const std::wstring& to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    const wchar_t* currentStr = reinterpret_cast<const wchar_t*>(memoryAddress);
    if (wcsncmp(currentStr, from.c_str(), from.size()) != 0)
        return false;

    size_t byteSize = (to.size() + 1) * sizeof(wchar_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(reinterpret_cast<void*>(memoryAddress), byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new string value */
    memcpy(reinterpret_cast<void*>(memoryAddress), to.c_str(), byteSize);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(reinterpret_cast<void*>(memoryAddress), byteSize, oldProtect, &tmp);

    return true;
}

std::wstring Utilities::Memory::Internal::IndirectGetWString(const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetWString(memoryAddress);
}

std::wstring Utilities::Memory::Internal::IndirectGetWString(const void* memoryPtr, size_t maxLength)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetWString(memoryAddress, maxLength);
}

std::wstring Utilities::Memory::Internal::IndirectGetWString(const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return std::wstring();

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (!IsValidAddress(dataAddress))
        return std::wstring();

    /* Read and return the wide string from the target address. */
    const wchar_t* wStrPtr = reinterpret_cast<const wchar_t*>(dataAddress);
    return std::wstring(wStrPtr);
}

std::wstring Utilities::Memory::Internal::IndirectGetWString(const uintptr_t& memoryAddress, size_t maxLength)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return std::wstring();

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (!IsValidAddress(dataAddress))
        return std::wstring();

    /* Read and return the wide string from the target address. */
    const wchar_t* wStrPtr = reinterpret_cast<const wchar_t*>(dataAddress);
    return std::wstring(wStrPtr, wcsnlen_s(wStrPtr, maxLength));
}

bool Utilities::Memory::Internal::IndirectSetWString(const void* memoryPtr, const std::wstring& newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetWString(memoryAddress, newValue);
}

bool Utilities::Memory::Internal::IndirectSetWString(const uintptr_t& memoryAddress, const std::wstring& newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Cast the address to wchar_t* */
    wchar_t* targetStr = reinterpret_cast<wchar_t*>(dataAddress);
    size_t byteSize = (newValue.size() + 1) * sizeof(wchar_t);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(targetStr, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new string value. */
    memcpy(targetStr, newValue.c_str(), byteSize);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(targetStr, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::IndirectPatchWString(const void* memoryPtr, const std::wstring& from, const std::wstring& to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchWString(memoryAddress, from, to);
}

bool Utilities::Memory::Internal::IndirectPatchWString(const uintptr_t& memoryAddress, const std::wstring& from, const std::wstring& to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    const wchar_t* currentStr = reinterpret_cast<const wchar_t*>(dataAddress);
    if (wcsncmp(currentStr, from.c_str(), from.size()) != 0)
        return false;

    size_t byteSize = (to.size() + 1) * sizeof(wchar_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    if (VirtualProtect(reinterpret_cast<void*>(dataAddress), byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new string value */
    memcpy(reinterpret_cast<void*>(dataAddress), to.c_str(), byteSize);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtect(reinterpret_cast<void*>(dataAddress), byteSize, oldProtect, &tmp);

    return true;
}




std::vector<uint8_t> Utilities::Memory::Internal::GetBytes(const void* memoryPtr, size_t byteCount)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetBytes(memoryAddress, byteCount);
}

std::vector<uint8_t> Utilities::Memory::Internal::GetBytes(const uintptr_t& memoryAddress, size_t byteCount)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return {};

    std::vector<uint8_t> buffer(byteCount);
    /* Read and return the bytes from the target address. */
    memcpy(buffer.data(), reinterpret_cast<void*>(memoryAddress), byteCount);
    return buffer;
}

bool Utilities::Memory::Internal::SetBytes(const void* memoryPtr, const std::vector<uint8_t>& newBytes)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetBytes(memoryAddress, newBytes);
}

bool Utilities::Memory::Internal::SetBytes(const uintptr_t& memoryAddress, const std::vector<uint8_t>& newBytes)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false || newBytes.empty())
        return false;

    LPVOID target = reinterpret_cast<LPVOID>(memoryAddress);
    size_t byteSize = newBytes.size();

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(target, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new bytes. */
    std::memcpy(target, newBytes.data(), byteSize);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(target, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::PatchBytes(const void* memoryPtr, const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchBytes(memoryAddress, fromBytes, toBytes);
}

bool Utilities::Memory::Internal::PatchBytes(const uintptr_t& memoryAddress, const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Sizes must match to patch deterministically. */
    if (fromBytes.size() != toBytes.size())
        return false;

    /* Nothing to patch -> succeed. */
    if (fromBytes.empty())
        return true;

    LPVOID target = reinterpret_cast<LPVOID>(memoryAddress);

    /* Verify that the current bytes match the expected ones. */
    if (std::memcmp(target, fromBytes.data(), fromBytes.size()) != 0)
        return false;

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(target, toBytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new bytes. */
    std::memcpy(target, toBytes.data(), toBytes.size());

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(target, toBytes.size(), oldProtect, &tmp);

    return true;
}

std::vector<uint8_t> Utilities::Memory::Internal::IndirectGetBytes(const void* memoryPtr, size_t byteCount)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetBytes(memoryAddress, byteCount);
}

std::vector<uint8_t> Utilities::Memory::Internal::IndirectGetBytes(const uintptr_t& memoryAddress, size_t byteCount)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return {};

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return {};

    std::vector<uint8_t> buffer(byteCount);
    /* Read and return the bytes from the target address. */
    memcpy(buffer.data(), reinterpret_cast<void*>(dataAddress), byteCount);
    return buffer;
}

bool Utilities::Memory::Internal::IndirectSetBytes(const void* memoryPtr, const std::vector<uint8_t>& newBytes)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetBytes(memoryAddress, newBytes);
}

bool Utilities::Memory::Internal::IndirectSetBytes(const uintptr_t& memoryAddress, const std::vector<uint8_t>& newBytes)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Nothing to write -> succeed. */
    if (newBytes.empty())
        return true;

    LPVOID target = reinterpret_cast<LPVOID>(dataAddress);
    size_t byteSize = newBytes.size();

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(target, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new bytes. */
    std::memcpy(target, newBytes.data(), byteSize);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(target, byteSize, oldProtect, &tmp);

    return true;
}

bool Utilities::Memory::Internal::IndirectPatchBytes(const void* memoryPtr, const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchBytes(memoryAddress, fromBytes, toBytes);
}

bool Utilities::Memory::Internal::IndirectPatchBytes(const uintptr_t& memoryAddress, const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = *reinterpret_cast<uintptr_t*>(memoryAddress);
    if (IsValidAddress(dataAddress) == false)
        return false;

    /* Sizes must match. */
    if (fromBytes.size() != toBytes.size())
        return false;

    /* Nothing to patch -> succeed. */
    if (fromBytes.empty())
        return true;

    LPVOID target = reinterpret_cast<LPVOID>(dataAddress);

    /* Verify that the current bytes match the expected ones. */
    if (std::memcmp(target, fromBytes.data(), fromBytes.size()) != 0)
        return false;

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtect(target, toBytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new bytes. */
    std::memcpy(target, toBytes.data(), toBytes.size());

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtect(target, toBytes.size(), oldProtect, &tmp);

    return true;
}






// ========================================================
// |                      #EXTERNAL                       |
// ========================================================
std::string Utilities::Memory::External::ReadRemoteString(const HANDLE& hProcess, const uintptr_t memoryAddress, size_t maxLength)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false || maxLength == 0)
        return std::string();

    const size_t kChunk = 256; // number of char_t per chunk.
    std::string result;
    result.reserve(std::min<size_t>(maxLength, kChunk));

    uintptr_t cursor = memoryAddress;
    size_t remaining = maxLength;
    std::vector<char> buf(kChunk);

    while (remaining > 0)
    {
        size_t toRead = std::min<size_t>(remaining, kChunk);
        SIZE_T bytesRead = 0;

        if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(cursor),
            buf.data(), toRead, &bytesRead)
            || bytesRead == 0)
            break; // Could not read further; return what we have.

        // Look for '\0' in the portion we actually read.
        void* nulPos = std::memchr(buf.data(), '\0', bytesRead);
        if (nulPos)
        {
            const size_t chunkLen = static_cast<char*>(nulPos) - buf.data();
            result.append(buf.data(), chunkLen);
            return result;
        }

        // No NUL; append all bytes read and continue until we hit maxLength.
        result.append(buf.data(), static_cast<size_t>(bytesRead));

        cursor += bytesRead;
        remaining -= static_cast<size_t>(bytesRead);

        if (bytesRead < toRead)
            break; // Likely hit an unreadable boundary.
    }

    return result; // May be exactly maxLength or shorter if we hit a boundary.
}

std::wstring Utilities::Memory::External::ReadRemoteWString(const HANDLE& hProcess, const uintptr_t memoryAddress, size_t maxLength /*= 256*/)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false || maxLength == 0)
        return std::wstring();

    const size_t kChunk = 256; // number of wchar_t per chunk.
    std::wstring result;
    result.reserve(std::min<size_t>(maxLength, kChunk));

    uintptr_t cursor = memoryAddress;
    size_t remaining = maxLength;
    std::vector<wchar_t> buf(kChunk);

    while (remaining > 0)
    {
        size_t toReadChars = std::min<size_t>(remaining, kChunk);
        size_t toReadBytes = toReadChars * static_cast<size_t>(sizeof(wchar_t));
        SIZE_T bytesRead = 0;

        if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(cursor),
            buf.data(), toReadBytes, &bytesRead)
            || bytesRead == 0)
            break; // Could not read further; return what we have.

        // Work only with the full wchar_t elements we actually read.
        size_t elemsRead = bytesRead / sizeof(wchar_t);
        if (elemsRead == 0)
            break; // Partial wchar_t or unreadable; stop.

        // Look for L'\0' in the portion we actually read.
        auto begin = buf.begin();
        auto end = buf.begin() + elemsRead;
        auto nulIt = std::find(begin, end, L'\0');
        if (nulIt != end)
        {
            const size_t chunkLen = static_cast<size_t>(std::distance(begin, nulIt));
            result.append(buf.data(), chunkLen);
            return result;
        }

        // No NUL; append all characters read and continue until we hit maxLength.
        result.append(buf.data(), static_cast<size_t>(elemsRead));

        cursor += bytesRead;
        remaining -= static_cast<size_t>(elemsRead);

        if (elemsRead < toReadChars)
            break; // Likely hit an unreadable boundary.
    }

    return result; // May be exactly maxLength or shorter if we hit a boundary.
}




bool Utilities::Memory::External::IsValidProcessHandle(const HANDLE& hProcess, const bool& requireQueryRights)
{
    if (hProcess == nullptr || hProcess == INVALID_HANDLE_VALUE) // Handle must be non-null and not INVALID_HANDLE_VALUE. Return False if it's not.
        return false;

    if (GetProcessId(hProcess) == 0) // Must be a process handle (GetProcessId returns 0 on failure). Return False if it isn't.
        return false;

    DWORD exitCode = 0;
    if (GetExitCodeProcess(hProcess, &exitCode) == false || exitCode != STILL_ACTIVE)
        return false;

    if (requireQueryRights)
    {
        MEMORY_BASIC_INFORMATION mbi{};
        if (VirtualQueryEx(hProcess, nullptr, &mbi, sizeof(mbi)) != sizeof(mbi))
            return false;
    }

    return true;
}

bool Utilities::Memory::External::IsValidProcessHandle(const HANDLE& hProcess)
{
    return IsValidProcessHandle(hProcess, false);
}




bool Utilities::Memory::External::IsValidPtr(const HANDLE& hProcess, const void* memoryPtr)
{
    if (!IsValidProcessHandle(hProcess)) // Process handle must be valid and suitable. Return False if it's not.
        return false;

    MEMORY_BASIC_INFORMATION mbi{};

    if (VirtualQueryEx(hProcess, memoryPtr, &mbi, sizeof(mbi)) != sizeof(mbi)) // Try to request (query) information about the given memory region, return False if attempt fails.
        return false;

    if (mbi.State != MEM_COMMIT) // Memory region must be committed (actually backed by physical memory). Return False if it's not.
        return false;

    /* Strip out guard and cache flags to examine the core protection flags. */
    DWORD protectionFlags = mbi.Protect & ~(PAGE_GUARD | PAGE_NOCACHE | PAGE_WRITECOMBINE);
    if ((protectionFlags & (PAGE_READONLY | PAGE_READWRITE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE)) == false) // See if we're able to request one of the read permissions (readable or executable+read), return False if we aren't.
        return false;

    return true;
}

bool Utilities::Memory::External::IsValidAddress(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    void* memoryPtr = reinterpret_cast<void*>(memoryAddress);
    return IsValidPtr(hProcess, memoryPtr);
}




void* Utilities::Memory::External::PtrAddOffset(const HANDLE& hProcess, const void* memoryPtr, size_t offset)
{
    /* Since void* doesn't support pointer arithmetics, we need to convert it to uintptr_t first. */
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PtrAddOffset(hProcess, memoryAddress, offset);
}

void* Utilities::Memory::External::PtrAddOffset(const HANDLE& hProcess, const uintptr_t& memoryAddress, size_t offset)
{
    /* Calculate the new address by adding the offset. */
    uintptr_t newMemoryAddress = AddressAddOffset(hProcess, memoryAddress, offset);
    if (newMemoryAddress == 0x0) // Return null pointer if memory region is invalid.
        return nullptr;

    return reinterpret_cast<void*>(newMemoryAddress);
}


uintptr_t Utilities::Memory::External::AddressAddOffset(const HANDLE& hProcess, const void* memoryPtr, size_t offset)
{
    /* Since void* doesn't support pointer arithmetics, we need to convert it to uintptr_t first. */
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return AddressAddOffset(hProcess, memoryAddress, offset);
}

uintptr_t Utilities::Memory::External::AddressAddOffset(const HANDLE& hProcess, const uintptr_t& memoryAddress, size_t offset)
{
    /* Calculate the new address by adding the offset. */
    uintptr_t newMemoryAddress = memoryAddress + offset;

    /* Before dereferencing, verify we can read sizeof(uintptr_t) bytes at 'newMemoryAddress'. */
    /* Abort and return 0 if memory isn't readable */
    if (IsValidAddress(hProcess, newMemoryAddress) == false ||
        IsValidAddress(hProcess, (newMemoryAddress + sizeof(uintptr_t) - 1)) == false)
        return 0x0;

    /* Return the valid address */
    return newMemoryAddress;
}




void* Utilities::Memory::External::PtrDereference(const HANDLE& hProcess, const void* memoryPtr, size_t offset)
{
    /* Since void* doesn't support pointer arithmetics, we need to convert it to uintptr_t first. */
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PtrDereference(hProcess, memoryAddress, offset);
}

void* Utilities::Memory::External::PtrDereference(const HANDLE& hProcess, const uintptr_t& memoryAddress, size_t offset)
{
    /* Get the dereferenced address. */
    uintptr_t newMemoryAddress = AddressDereference(hProcess, memoryAddress, offset);
    if (newMemoryAddress == 0x0) // Return null pointer if memory region is invalid.
        return nullptr;

    return reinterpret_cast<void*>(newMemoryAddress);
}


uintptr_t Utilities::Memory::External::AddressDereference(const HANDLE& hProcess, const void* memoryPtr, size_t offset)
{
    /* Since void* doesn't support pointer arithmetics, we need to convert it to uintptr_t first. */
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return AddressDereference(hProcess, memoryAddress, offset);
}

uintptr_t Utilities::Memory::External::AddressDereference(const HANDLE& hProcess, const uintptr_t& memoryAddress, size_t offset)
{
    /* Calculate the target address by adding the offset. */
    uintptr_t targetAddress = memoryAddress + offset;

    /* Verify we can safely read from 'targetAddress' in the target process. */
    if (IsValidAddress(hProcess, targetAddress) == false ||
        IsValidAddress(hProcess, (targetAddress + sizeof(uintptr_t) - 1)) == false)
        return 0x0;

    /* Read and return the pointer value from the target address. */
    uintptr_t dereferencedAddress = 0x0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(targetAddress),
        &dereferencedAddress, sizeof(dereferencedAddress), &bytesRead)
        || bytesRead != sizeof(dereferencedAddress))
        return 0x0;

    return dereferencedAddress;
}




void* Utilities::Memory::External::PtrFollowPointerChain(const HANDLE& hProcess, const void* memoryPtr, const std::vector<uintptr_t>& memoryOffsets)
{
    /* Since void* doesn't support pointer arithmetics, we need to convert it to uintptr_t first. */
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);

    /* Calculate the new address by following the pointer chain. */
    uintptr_t newMemoryAddress = AddressFollowPointerChain(hProcess, memoryAddress, memoryOffsets);
    if (newMemoryAddress == 0x0) // Return null pointer if memory region is invalid.
        return nullptr;

    return reinterpret_cast<void*>(newMemoryAddress);
}

uintptr_t Utilities::Memory::External::AddressFollowPointerChain(const HANDLE& hProcess, const uintptr_t& memoryAddress, const std::vector<uintptr_t>& memoryOffsets)
{
    uintptr_t newMemoryAddress = memoryAddress;
    size_t offsetsCount = memoryOffsets.size();

    for (size_t i = 0; i < offsetsCount; ++i)
    {
        /* Before dereferencing, verify we can read sizeof(uintptr_t) bytes at 'newMemoryAddress'. */
        /* Abort and return 0 if memory isn't readable */
        if (IsValidAddress(hProcess, newMemoryAddress) == false ||
            IsValidAddress(hProcess, (newMemoryAddress + sizeof(uintptr_t) - 1)) == false)
            return 0x0;

        /* Read the next pointer value from memory and add the current offset to advance to the next address in the chain. */
        uintptr_t nextPtr = 0;
        SIZE_T bytesRead = 0;
        if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(newMemoryAddress),
            &nextPtr, sizeof(nextPtr), &bytesRead)
            || bytesRead != sizeof(nextPtr))
            return 0x0;

        newMemoryAddress = nextPtr;
        newMemoryAddress += memoryOffsets[i];
    }

    /* After processing all offsets, 'ptr' should point to the final data. */
    return newMemoryAddress;
}




bool Utilities::Memory::External::GetBool(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetBool(hProcess, memoryAddress);
}

bool Utilities::Memory::External::GetBool(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read and return the boolean value from the target address. */
    bool value = false;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &value, sizeof(value), &bytesRead)
        || bytesRead != sizeof(value))
        return false;

    return value;
}

bool Utilities::Memory::External::SetBool(const HANDLE& hProcess, const void* memoryPtr, bool newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetBool(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::SetBool(const HANDLE& hProcess, const uintptr_t& memoryAddress, bool newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Cast the address to bool* */
    LPVOID targetBool = reinterpret_cast<LPVOID>(memoryAddress);
    size_t byteSize = sizeof(bool);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetBool, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new boolean value. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetBool, &newValue, byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetBool, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::PatchBool(const HANDLE& hProcess, const void* memoryPtr, bool from, bool to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchBool(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::PatchBool(const HANDLE& hProcess, const uintptr_t& memoryAddress, bool from, bool to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    bool current = false;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &current, sizeof(current), &bytesRead)
        || bytesRead != sizeof(current))
        return false;

    if (current != from) // Only patch if the current value matches 'from'.
        return false;

    size_t byteSize = sizeof(bool);

    /* Make the memory region writable */
    DWORD oldProtect;
    LPVOID targetBool = reinterpret_cast<LPVOID>(memoryAddress);
    if (VirtualProtectEx(hProcess, targetBool, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new boolean value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetBool, &to, byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetBool, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::IndirectGetBool(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetBool(hProcess, memoryAddress);
}

bool Utilities::Memory::External::IndirectGetBool(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Read and return the boolean value from the target address. */
    bool value = false;
    bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        &value, sizeof(value), &bytesRead)
        || bytesRead != sizeof(value))
        return false;

    return value;
}

bool Utilities::Memory::External::IndirectSetBool(const HANDLE& hProcess, const void* memoryPtr, bool newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetBool(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::IndirectSetBool(const HANDLE& hProcess, const uintptr_t& memoryAddress, bool newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Cast the address to bool* */
    LPVOID targetBool = reinterpret_cast<LPVOID>(dataAddress);
    size_t byteSize = sizeof(bool);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetBool, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new boolean value. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetBool, &newValue, byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetBool, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::IndirectPatchBool(const HANDLE& hProcess, const void* memoryPtr, bool from, bool to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchBool(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::IndirectPatchBool(const HANDLE& hProcess, const uintptr_t& memoryAddress, bool from, bool to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    bool current = false;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        &current, sizeof(current), &bytesRead) || bytesRead != sizeof(current))
        return false;

    if (current != from) // Only patch if the current value matches 'from'.
        return false;

    size_t byteSize = sizeof(bool);

    /* Make the memory region writable */
    DWORD oldProtect;
    LPVOID targetBool = reinterpret_cast<LPVOID>(dataAddress);
    if (VirtualProtectEx(hProcess, targetBool, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new boolean value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetBool, &to, byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetBool, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}




int8_t Utilities::Memory::External::GetInt8(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetInt8(hProcess, memoryAddress);
}

int8_t Utilities::Memory::External::GetInt8(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return -1;

    /* Read and return the 8-bit integer from the target address. */
    int8_t value = -1;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &value, sizeof(value), &bytesRead)
        || bytesRead != sizeof(value))
        return -1;

    return value;
}

bool Utilities::Memory::External::SetInt8(const HANDLE& hProcess, const void* memoryPtr, int8_t newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetInt8(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::SetInt8(const HANDLE& hProcess, const uintptr_t& memoryAddress, int8_t newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Cast the address to int8_t* */
    LPVOID targetInt = reinterpret_cast<LPVOID>(memoryAddress);
    size_t byteSize = sizeof(int8_t);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetInt, &newValue, byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetInt, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::PatchInt8(const HANDLE& hProcess, const void* memoryPtr, int8_t from, int8_t to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchInt8(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::PatchInt8(const HANDLE& hProcess, const uintptr_t& memoryAddress, int8_t from, int8_t to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    int8_t current = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &current, sizeof(current), &bytesRead)
        || bytesRead != sizeof(current))
        return false;

    if (current != from) // Only patch if the current value matches 'from'.
        return false;

    size_t byteSize = sizeof(int8_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    LPVOID targetInt = reinterpret_cast<LPVOID>(memoryAddress);
    if (VirtualProtectEx(hProcess, targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetInt, &to, byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetInt, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

int8_t Utilities::Memory::External::IndirectGetInt8(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetInt8(hProcess, memoryAddress);
}

int8_t Utilities::Memory::External::IndirectGetInt8(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return -1;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead) || bytesRead != sizeof(dataAddress))
        return -1;

    if (!IsValidAddress(hProcess, dataAddress))
        return -1;

    /* Read and return the 8-bit integer from the target address. */
    int8_t value = -1;
    bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        &value, sizeof(value), &bytesRead)
        || bytesRead != sizeof(value))
        return -1;

    return value;
}

bool Utilities::Memory::External::IndirectSetInt8(const HANDLE& hProcess, const void* memoryPtr, int8_t newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetInt8(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::IndirectSetInt8(const HANDLE& hProcess, const uintptr_t& memoryAddress, int8_t newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Cast the address to int8_t* */
    LPVOID targetInt = reinterpret_cast<LPVOID>(dataAddress);
    size_t byteSize = sizeof(int8_t);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new integer value. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetInt, &newValue, byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetInt, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::IndirectPatchInt8(const HANDLE& hProcess, const void* memoryPtr, int8_t from, int8_t to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchInt8(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::IndirectPatchInt8(const HANDLE& hProcess, const uintptr_t& memoryAddress, int8_t from, int8_t to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    int8_t current = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        &current, sizeof(current), &bytesRead)
        || bytesRead != sizeof(current))
        return false;

    if (current != from) // Only patch if the current value matches 'from'.
        return false;

    size_t byteSize = sizeof(int8_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    LPVOID targetInt = reinterpret_cast<LPVOID>(dataAddress);
    if (VirtualProtectEx(hProcess, targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetInt, &to, byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetInt, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}




int16_t Utilities::Memory::External::GetInt16(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetInt16(hProcess, memoryAddress);
}

int16_t Utilities::Memory::External::GetInt16(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return -1;

    /* Read and return the 16-bit integer from the target address. */
    int16_t value = -1;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &value, sizeof(value), &bytesRead)
        || bytesRead != sizeof(value))
        return -1;

    return value;
}

bool Utilities::Memory::External::SetInt16(const HANDLE& hProcess, const void* memoryPtr, int16_t newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetInt16(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::SetInt16(const HANDLE& hProcess, const uintptr_t& memoryAddress, int16_t newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Cast the address to int16_t* */
    LPVOID targetInt = reinterpret_cast<LPVOID>(memoryAddress);
    size_t byteSize = sizeof(int16_t);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetInt, &newValue, byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetInt, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::PatchInt16(const HANDLE& hProcess, const void* memoryPtr, int16_t from, int16_t to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchInt16(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::PatchInt16(const HANDLE& hProcess, const uintptr_t& memoryAddress, int16_t from, int16_t to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    int16_t current = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &current, sizeof(current), &bytesRead)
        || bytesRead != sizeof(current))
        return false;

    if (current != from) // Only patch if the current value matches 'from'.
        return false;

    size_t byteSize = sizeof(int16_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    LPVOID targetInt = reinterpret_cast<LPVOID>(memoryAddress);
    if (VirtualProtectEx(hProcess, targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetInt, &to, byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetInt, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

int16_t Utilities::Memory::External::IndirectGetInt16(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetInt16(hProcess, memoryAddress);
}

int16_t Utilities::Memory::External::IndirectGetInt16(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return -1;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead) || bytesRead != sizeof(dataAddress))
        return -1;

    if (!IsValidAddress(hProcess, dataAddress))
        return -1;

    /* Read and return the 16-bit integer from the target address. */
    int16_t value = -1;
    bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        &value, sizeof(value), &bytesRead)
        || bytesRead != sizeof(value))
        return -1;

    return value;
}

bool Utilities::Memory::External::IndirectSetInt16(const HANDLE& hProcess, const void* memoryPtr, int16_t newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetInt16(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::IndirectSetInt16(const HANDLE& hProcess, const uintptr_t& memoryAddress, int16_t newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Cast the address to int16_t* */
    LPVOID targetInt = reinterpret_cast<LPVOID>(dataAddress);
    size_t byteSize = sizeof(int16_t);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new integer value. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetInt, &newValue, byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetInt, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::IndirectPatchInt16(const HANDLE& hProcess, const void* memoryPtr, int16_t from, int16_t to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchInt16(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::IndirectPatchInt16(const HANDLE& hProcess, const uintptr_t& memoryAddress, int16_t from, int16_t to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    int16_t current = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        &current, sizeof(current), &bytesRead)
        || bytesRead != sizeof(current))
        return false;

    if (current != from) // Only patch if the current value matches 'from'.
        return false;

    size_t byteSize = sizeof(int16_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    LPVOID targetInt = reinterpret_cast<LPVOID>(dataAddress);
    if (VirtualProtectEx(hProcess, targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetInt, &to, byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetInt, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}




int32_t Utilities::Memory::External::GetInt32(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetInt32(hProcess, memoryAddress);
}

int32_t Utilities::Memory::External::GetInt32(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return -1;

    /* Read and return the 32-bit integer from the target address. */
    int32_t value = -1;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &value, sizeof(value), &bytesRead)
        || bytesRead != sizeof(value))
        return -1;

    return value;
}

bool Utilities::Memory::External::SetInt32(const HANDLE& hProcess, const void* memoryPtr, int32_t newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetInt32(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::SetInt32(const HANDLE& hProcess, const uintptr_t& memoryAddress, int32_t newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Cast the address to int32_t* */
    LPVOID targetInt = reinterpret_cast<LPVOID>(memoryAddress);
    size_t byteSize = sizeof(int32_t);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetInt, &newValue, byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetInt, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::PatchInt32(const HANDLE& hProcess, const void* memoryPtr, int32_t from, int32_t to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchInt32(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::PatchInt32(const HANDLE& hProcess, const uintptr_t& memoryAddress, int32_t from, int32_t to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    int32_t current = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &current, sizeof(current), &bytesRead)
        || bytesRead != sizeof(current))
        return false;

    if (current != from) // Only patch if the current value matches 'from'.
        return false;

    size_t byteSize = sizeof(int32_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    LPVOID targetInt = reinterpret_cast<LPVOID>(memoryAddress);
    if (VirtualProtectEx(hProcess, targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetInt, &to, byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetInt, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

int32_t Utilities::Memory::External::IndirectGetInt32(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetInt32(hProcess, memoryAddress);
}

int32_t Utilities::Memory::External::IndirectGetInt32(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return -1;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return -1;

    if (!IsValidAddress(hProcess, dataAddress))
        return -1;

    /* Read and return the 32-bit integer from the target address. */
    int32_t value = -1;
    bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        &value, sizeof(value), &bytesRead)
        || bytesRead != sizeof(value))
        return -1;

    return value;
}

bool Utilities::Memory::External::IndirectSetInt32(const HANDLE& hProcess, const void* memoryPtr, int32_t newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetInt32(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::IndirectSetInt32(const HANDLE& hProcess, const uintptr_t& memoryAddress, int32_t newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Cast the address to int32_t* */
    LPVOID targetInt = reinterpret_cast<LPVOID>(dataAddress);
    size_t byteSize = sizeof(int32_t);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new integer value. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetInt, &newValue, byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetInt, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::IndirectPatchInt32(const HANDLE& hProcess, const void* memoryPtr, int32_t from, int32_t to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchInt32(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::IndirectPatchInt32(const HANDLE& hProcess, const uintptr_t& memoryAddress, int32_t from, int32_t to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    int32_t current = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        &current, sizeof(current), &bytesRead)
        || bytesRead != sizeof(current))
        return false;

    if (current != from) // Only patch if the current value matches 'from'.
        return false;

    size_t byteSize = sizeof(int32_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    LPVOID targetInt = reinterpret_cast<LPVOID>(dataAddress);
    if (VirtualProtectEx(hProcess, targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetInt, &to, byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetInt, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}




int64_t Utilities::Memory::External::GetInt64(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetInt64(hProcess, memoryAddress);
}

int64_t Utilities::Memory::External::GetInt64(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return -1;

    /* Read and return the 64-bit integer from the target address. */
    int64_t value = -1;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &value, sizeof(value), &bytesRead)
        || bytesRead != sizeof(value))
        return -1;

    return value;
}

bool Utilities::Memory::External::SetInt64(const HANDLE& hProcess, const void* memoryPtr, int64_t newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetInt64(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::SetInt64(const HANDLE& hProcess, const uintptr_t& memoryAddress, int64_t newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Cast the address to int64_t* */
    LPVOID targetInt = reinterpret_cast<LPVOID>(memoryAddress);
    size_t byteSize = sizeof(int64_t);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetInt, &newValue, byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetInt, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::PatchInt64(const HANDLE& hProcess, const void* memoryPtr, int64_t from, int64_t to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchInt64(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::PatchInt64(const HANDLE& hProcess, const uintptr_t& memoryAddress, int64_t from, int64_t to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    int64_t current = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &current, sizeof(current), &bytesRead)
        || bytesRead != sizeof(current))
        return false;

    if (current != from) // Only patch if the current value matches 'from'.
        return false;

    size_t byteSize = sizeof(int64_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    LPVOID targetInt = reinterpret_cast<LPVOID>(memoryAddress);
    if (VirtualProtectEx(hProcess, targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetInt, &to, byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetInt, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

int64_t Utilities::Memory::External::IndirectGetInt64(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetInt64(hProcess, memoryAddress);
}

int64_t Utilities::Memory::External::IndirectGetInt64(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return -1;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return -1;

    if (!IsValidAddress(hProcess, dataAddress))
        return -1;

    /* Read and return the 64-bit integer from the target address. */
    int64_t value = -1;
    bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        &value, sizeof(value), &bytesRead)
        || bytesRead != sizeof(value))
        return -1;

    return value;
}

bool Utilities::Memory::External::IndirectSetInt64(const HANDLE& hProcess, const void* memoryPtr, int64_t newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetInt64(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::IndirectSetInt64(const HANDLE& hProcess, const uintptr_t& memoryAddress, int64_t newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Cast the address to int64_t* */
    LPVOID targetInt = reinterpret_cast<LPVOID>(dataAddress);
    size_t byteSize = sizeof(int64_t);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new integer value. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetInt, &newValue, byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetInt, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::IndirectPatchInt64(const HANDLE& hProcess, const void* memoryPtr, int64_t from, int64_t to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchInt64(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::IndirectPatchInt64(const HANDLE& hProcess, const uintptr_t& memoryAddress, int64_t from, int64_t to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    int64_t current = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        &current, sizeof(current), &bytesRead)
        || bytesRead != sizeof(current))
        return false;

    if (current != from) // Only patch if the current value matches 'from'.
        return false;

    size_t byteSize = sizeof(int64_t);

    /* Make the memory region writable */
    DWORD oldProtect;
    LPVOID targetInt = reinterpret_cast<LPVOID>(dataAddress);
    if (VirtualProtectEx(hProcess, targetInt, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new integer value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetInt, &to, byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetInt, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}




float Utilities::Memory::External::GetFloat(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetFloat(hProcess, memoryAddress);
}

float Utilities::Memory::External::GetFloat(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return -1.0f;

    /* Read and return the 32-bit floating-point value from the target address. */
    float value = -1.0f;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &value, sizeof(value), &bytesRead)
        || bytesRead != sizeof(value))
        return -1.0f;

    return value;
}

bool Utilities::Memory::External::SetFloat(const HANDLE& hProcess, const void* memoryPtr, float newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetFloat(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::SetFloat(const HANDLE& hProcess, const uintptr_t& memoryAddress, float newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Cast the address to float* */
    LPVOID targetFloat = reinterpret_cast<LPVOID>(memoryAddress);
    size_t byteSize = sizeof(float);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetFloat, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new floating-point value. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetFloat, &newValue, byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetFloat, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::PatchFloat(const HANDLE& hProcess, const void* memoryPtr, float from, float to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchFloat(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::PatchFloat(const HANDLE& hProcess, const uintptr_t& memoryAddress, float from, float to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    float current = 0.0f;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &current, sizeof(current), &bytesRead)
        || bytesRead != sizeof(current))
        return false;

    if (current != from) // Only patch if the current value matches 'from'.
        return false;

    size_t byteSize = sizeof(float);

    /* Make the memory region writable */
    DWORD oldProtect;
    LPVOID targetFloat = reinterpret_cast<LPVOID>(memoryAddress);
    if (VirtualProtectEx(hProcess, targetFloat, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new floating-point value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetFloat, &to, byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetFloat, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

float Utilities::Memory::External::IndirectGetFloat(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetFloat(hProcess, memoryAddress);
}

float Utilities::Memory::External::IndirectGetFloat(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return -1.0f;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return -1.0f;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return -1.0f;

    /* Read and return the 32-bit floating-point value from the target address. */
    float value = -1.0f;
    bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        &value, sizeof(value), &bytesRead)
        || bytesRead != sizeof(value))
        return -1.0f;

    return value;
}

bool Utilities::Memory::External::IndirectSetFloat(const HANDLE& hProcess, const void* memoryPtr, float newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetFloat(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::IndirectSetFloat(const HANDLE& hProcess, const uintptr_t& memoryAddress, float newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Cast the address to float* */
    LPVOID targetFloat = reinterpret_cast<LPVOID>(dataAddress);
    size_t byteSize = sizeof(float);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetFloat, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new floating-point value. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetFloat, &newValue, byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetFloat, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::IndirectPatchFloat(const HANDLE& hProcess, const void* memoryPtr, float from, float to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchFloat(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::IndirectPatchFloat(const HANDLE& hProcess, const uintptr_t& memoryAddress, float from, float to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    float current = 0.0f;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        &current, sizeof(current), &bytesRead)
        || bytesRead != sizeof(current))
        return false;

    if (current != from) // Only patch if the current value matches 'from'.
        return false;

    size_t byteSize = sizeof(float);

    /* Make the memory region writable */
    DWORD oldProtect;
    LPVOID targetFloat = reinterpret_cast<LPVOID>(dataAddress);
    if (VirtualProtectEx(hProcess, targetFloat, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new floating-point value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetFloat, &to, byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetFloat, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}




double Utilities::Memory::External::GetDouble(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetDouble(hProcess, memoryAddress);
}

double Utilities::Memory::External::GetDouble(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return -1.0;

    /* Read and return the 64-bit floating-point value from the target address. */
    double value = -1.0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &value, sizeof(value), &bytesRead)
        || bytesRead != sizeof(value))
        return -1.0;

    return value;
}

bool Utilities::Memory::External::SetDouble(const HANDLE& hProcess, const void* memoryPtr, double newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetDouble(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::SetDouble(const HANDLE& hProcess, const uintptr_t& memoryAddress, double newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Cast the address to double* */
    LPVOID targetDouble = reinterpret_cast<LPVOID>(memoryAddress);
    size_t byteSize = sizeof(double);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetDouble, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new floating-point value. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetDouble, &newValue, byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetDouble, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::PatchDouble(const HANDLE& hProcess, const void* memoryPtr, double from, double to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchDouble(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::PatchDouble(const HANDLE& hProcess, const uintptr_t& memoryAddress, double from, double to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    double current = 0.0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &current, sizeof(current), &bytesRead)
        || bytesRead != sizeof(current))
        return false;

    if (current != from) // Only patch if the current value matches 'from'.
        return false;

    size_t byteSize = sizeof(double);

    /* Make the memory region writable */
    DWORD oldProtect;
    LPVOID targetDouble = reinterpret_cast<LPVOID>(memoryAddress);
    if (VirtualProtectEx(hProcess, targetDouble, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new floating-point value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetDouble, &to, byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetDouble, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

double Utilities::Memory::External::IndirectGetDouble(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetDouble(hProcess, memoryAddress);
}

double Utilities::Memory::External::IndirectGetDouble(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return -1.0;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return -1.0;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return -1.0;

    /* Read and return the 64-bit floating-point value from the target address. */
    double value = -1.0;
    bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        &value, sizeof(value), &bytesRead)
        || bytesRead != sizeof(value))
        return -1.0;

    return value;
}

bool Utilities::Memory::External::IndirectSetDouble(const HANDLE& hProcess, const void* memoryPtr, double newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetDouble(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::IndirectSetDouble(const HANDLE& hProcess, const uintptr_t& memoryAddress, double newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Cast the address to double* */
    LPVOID targetDouble = reinterpret_cast<LPVOID>(dataAddress);
    size_t byteSize = sizeof(double);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetDouble, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new floating-point value. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetDouble, &newValue, byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetDouble, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::IndirectPatchDouble(const HANDLE& hProcess, const void* memoryPtr, double from, double to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchDouble(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::IndirectPatchDouble(const HANDLE& hProcess, const uintptr_t& memoryAddress, double from, double to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    double current = 0.0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        &current, sizeof(current), &bytesRead)
        || bytesRead != sizeof(current))
        return false;

    if (current != from) // Only patch if the current value matches 'from'.
        return false;

    size_t byteSize = sizeof(double);

    /* Make the memory region writable */
    DWORD oldProtect;
    LPVOID targetDouble = reinterpret_cast<LPVOID>(dataAddress);
    if (VirtualProtectEx(hProcess, targetDouble, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == false)
        return false;

    /* Write the new floating-point value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetDouble, &to, byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetDouble, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}




std::string Utilities::Memory::External::GetString(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetString(hProcess, memoryAddress);
}

std::string Utilities::Memory::External::GetString(const HANDLE& hProcess, const void* memoryPtr, size_t maxLength)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetString(hProcess, memoryAddress, maxLength);
}

std::string Utilities::Memory::External::GetString(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid and read a NUL-terminated string. */
    return ReadRemoteString(hProcess, memoryAddress);
}

std::string Utilities::Memory::External::GetString(const HANDLE& hProcess, const uintptr_t& memoryAddress, size_t maxLength)
{
    /* Verify that the address is valid and read up to maxLength (or until NUL). */
    return ReadRemoteString(hProcess, memoryAddress, maxLength);
}

bool Utilities::Memory::External::SetString(const HANDLE& hProcess, const void* memoryPtr, const std::string& newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetString(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::SetString(const HANDLE& hProcess, const uintptr_t& memoryAddress, const std::string& newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Cast the address to char* */
    char* targetStr = reinterpret_cast<char*>(memoryAddress);
    size_t byteSize = newValue.size() + 1; // +1 for null terminator

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetStr, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new string value. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetStr, newValue.c_str(), byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetStr, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::PatchString(const HANDLE& hProcess, const void* memoryPtr, const std::string& from, const std::string& to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchString(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::PatchString(const HANDLE& hProcess, const uintptr_t& memoryAddress, const std::string& from, const std::string& to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    std::vector<char> current(from.size());
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        current.data(), static_cast<size_t>(current.size()), &bytesRead)
        || bytesRead != current.size())
        return false;

    if (std::memcmp(current.data(), from.c_str(), current.size()) != 0)
        return false;

    LPVOID target = reinterpret_cast<LPVOID>(memoryAddress);
    size_t byteSize = static_cast<size_t>(to.size() + 1);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, target, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new string value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, target, to.c_str(), byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, target, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

std::string Utilities::Memory::External::IndirectGetString(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetString(hProcess, memoryAddress);
}

std::string Utilities::Memory::External::IndirectGetString(const HANDLE& hProcess, const void* memoryPtr, size_t maxLength)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetString(hProcess, memoryAddress, maxLength);
}

std::string Utilities::Memory::External::IndirectGetString(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return std::string();

    /* Read the data pointer from memoryAddress. */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return std::string();

    if (IsValidAddress(hProcess, dataAddress) == false)
        return std::string();

    /* Read and return the string from the target address. */
    return ReadRemoteString(hProcess, dataAddress);
}

std::string Utilities::Memory::External::IndirectGetString(const HANDLE& hProcess, const uintptr_t& memoryAddress, size_t maxLength)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return std::string();

    /* Read the data pointer from memoryAddress. */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return std::string();

    if (IsValidAddress(hProcess, dataAddress) == false)
        return std::string();

    /* Read and return up to maxLength (or until NUL) from the target address. */
    return ReadRemoteString(hProcess, dataAddress, maxLength);
}

bool Utilities::Memory::External::IndirectSetString(const HANDLE& hProcess, const void* memoryPtr, const std::string& newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetString(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::IndirectSetString(const HANDLE& hProcess, const uintptr_t& memoryAddress, const std::string& newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress. */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Make the memory region writable and write the new string (+1 for null terminator). */
    LPVOID targetStr = reinterpret_cast<LPVOID>(dataAddress);
    size_t byteSize = static_cast<size_t>(newValue.size() + 1);

    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetStr, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetStr, newValue.c_str(), byteSize, &bytesWritten);

    DWORD tmp;
    VirtualProtectEx(hProcess, targetStr, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::IndirectPatchString(const HANDLE& hProcess, const void* memoryPtr, const std::string& from, const std::string& to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchString(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::IndirectPatchString(const HANDLE& hProcess, const uintptr_t& memoryAddress, const std::string& from, const std::string& to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress. */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one (first 'from.size()' bytes). */
    std::vector<char> current(from.size());
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        current.data(), static_cast<size_t>(current.size()), &bytesRead)
        || bytesRead != current.size())
        return false;

    if (std::memcmp(current.data(), from.c_str(), current.size()) != 0)
        return false;

    LPVOID target = reinterpret_cast<LPVOID>(dataAddress);
    size_t byteSize = static_cast<size_t>(to.size() + 1);

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, target, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new string value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, target, to.c_str(), byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, target, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}




std::wstring Utilities::Memory::External::GetWString(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetWString(hProcess, memoryAddress);
}

std::wstring Utilities::Memory::External::GetWString(const HANDLE& hProcess, const void* memoryPtr, size_t maxLength)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetWString(hProcess, memoryAddress, maxLength);
}

std::wstring Utilities::Memory::External::GetWString(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid and read a NUL-terminated string. */
    return ReadRemoteWString(hProcess, memoryAddress);
}

std::wstring Utilities::Memory::External::GetWString(const HANDLE& hProcess, const uintptr_t& memoryAddress, size_t maxLength)
{
    /* Verify that the address is valid and read up to maxLength (or until NUL). */
    return ReadRemoteWString(hProcess, memoryAddress, maxLength);
}

bool Utilities::Memory::External::SetWString(const HANDLE& hProcess, const void* memoryPtr, const std::wstring& newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetWString(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::SetWString(const HANDLE& hProcess, const uintptr_t& memoryAddress, const std::wstring& newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Cast the address to wchar_t* */
    wchar_t* targetStr = reinterpret_cast<wchar_t*>(memoryAddress);
    size_t byteSize = static_cast<size_t>((newValue.size() + 1) * sizeof(wchar_t)); // +1 for null terminator

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetStr, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new string value. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetStr, newValue.c_str(), byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, targetStr, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::PatchWString(const HANDLE& hProcess, const void* memoryPtr, const std::wstring& from, const std::wstring& to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchWString(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::PatchWString(const HANDLE& hProcess, const uintptr_t& memoryAddress, const std::wstring& from, const std::wstring& to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Verify that the current value matches the expected one. */
    std::vector<wchar_t> current(from.size());
    SIZE_T bytesRead = 0;
    size_t expectBytes = static_cast<size_t>(current.size() * sizeof(wchar_t));
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        current.data(), expectBytes, &bytesRead)
        || bytesRead != expectBytes)
        return false;

    if (std::char_traits<wchar_t>::compare(current.data(), from.c_str(), current.size()) != 0)
        return false;

    LPVOID target = reinterpret_cast<LPVOID>(memoryAddress);
    size_t byteSize = static_cast<size_t>((to.size() + 1) * sizeof(wchar_t));

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, target, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new string value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, target, to.c_str(), byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, target, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

std::wstring Utilities::Memory::External::IndirectGetWString(const HANDLE& hProcess, const void* memoryPtr)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetWString(hProcess, memoryAddress);
}

std::wstring Utilities::Memory::External::IndirectGetWString(const HANDLE& hProcess, const void* memoryPtr, size_t maxLength)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetWString(hProcess, memoryAddress, maxLength);
}

std::wstring Utilities::Memory::External::IndirectGetWString(const HANDLE& hProcess, const uintptr_t& memoryAddress)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return std::wstring();

    /* Read the data pointer from memoryAddress. */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return std::wstring();

    if (IsValidAddress(hProcess, dataAddress) == false)
        return std::wstring();

    /* Read and return the string from the target address. */
    return ReadRemoteWString(hProcess, dataAddress);
}

std::wstring Utilities::Memory::External::IndirectGetWString(const HANDLE& hProcess, const uintptr_t& memoryAddress, size_t maxLength)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return std::wstring();

    /* Read the data pointer from memoryAddress. */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return std::wstring();

    if (IsValidAddress(hProcess, dataAddress) == false)
        return std::wstring();

    /* Read and return up to maxLength (or until NUL) from the target address. */
    return ReadRemoteWString(hProcess, dataAddress, maxLength);
}

bool Utilities::Memory::External::IndirectSetWString(const HANDLE& hProcess, const void* memoryPtr, const std::wstring& newValue)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetWString(hProcess, memoryAddress, newValue);
}

bool Utilities::Memory::External::IndirectSetWString(const HANDLE& hProcess, const uintptr_t& memoryAddress, const std::wstring& newValue)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress. */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Make the memory region writable and write the new string (+1 for null terminator). */
    LPVOID targetStr = reinterpret_cast<LPVOID>(dataAddress);
    size_t byteSize = static_cast<size_t>((newValue.size() + 1) * sizeof(wchar_t));

    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, targetStr, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, targetStr, newValue.c_str(), byteSize, &bytesWritten);

    DWORD tmp;
    VirtualProtectEx(hProcess, targetStr, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::IndirectPatchWString(const HANDLE& hProcess, const void* memoryPtr, const std::wstring& from, const std::wstring& to)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchWString(hProcess, memoryAddress, from, to);
}

bool Utilities::Memory::External::IndirectPatchWString(const HANDLE& hProcess, const uintptr_t& memoryAddress, const std::wstring& from, const std::wstring& to)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress. */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Verify that the current value matches the expected one (first 'from.size()' wchar_t). */
    std::vector<wchar_t> current(from.size());
    size_t expectBytes = static_cast<size_t>(current.size() * sizeof(wchar_t));
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        current.data(), expectBytes, &bytesRead)
        || bytesRead != expectBytes)
        return false;

    if (std::char_traits<wchar_t>::compare(current.data(), from.c_str(), current.size()) != 0)
        return false;

    LPVOID target = reinterpret_cast<LPVOID>(dataAddress);
    size_t byteSize = static_cast<size_t>((to.size() + 1) * sizeof(wchar_t));

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, target, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new string value */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, target, to.c_str(), byteSize, &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, target, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}




std::vector<uint8_t> Utilities::Memory::External::GetBytes(const HANDLE& hProcess, const void* memoryPtr, size_t byteCount)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return GetBytes(hProcess, memoryAddress, byteCount);
}

std::vector<uint8_t> Utilities::Memory::External::GetBytes(const HANDLE& hProcess, const uintptr_t& memoryAddress, size_t byteCount)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false || byteCount == 0)
        return {};

    std::vector<uint8_t> buffer(byteCount);

    /* Read and return the bytes from the target address. */
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        buffer.data(), buffer.size(), &bytesRead)
        || bytesRead != buffer.size())
        return {};

    return buffer;
}

bool Utilities::Memory::External::SetBytes(const HANDLE& hProcess, const void* memoryPtr, const std::vector<uint8_t>& newBytes)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return SetBytes(hProcess, memoryAddress, newBytes);
}

bool Utilities::Memory::External::SetBytes(const HANDLE& hProcess, const uintptr_t& memoryAddress, const std::vector<uint8_t>& newBytes)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false || newBytes.empty())
        return false;

    LPVOID target = reinterpret_cast<LPVOID>(memoryAddress);
    size_t byteSize = newBytes.size();

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, target, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new bytes. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, target, newBytes.data(), byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, target, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::PatchBytes(const HANDLE& hProcess, const void* memoryPtr, const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return PatchBytes(hProcess, memoryAddress, fromBytes, toBytes);
}

bool Utilities::Memory::External::PatchBytes(const HANDLE& hProcess, const uintptr_t& memoryAddress,
    const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Sizes must match and be non-zero. */
    if (fromBytes.size() == 0 || fromBytes.size() != toBytes.size())
        return false;

    /* Verify that the current bytes match the expected ones. */
    std::vector<uint8_t> current(fromBytes.size());
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        current.data(), current.size(), &bytesRead)
        || bytesRead != current.size())
        return false;

    if (!std::equal(current.begin(), current.end(), fromBytes.begin())) // Only patch if the current bytes match 'fromBytes'.
        return false;

    /* Make the memory region writable */
    LPVOID target = reinterpret_cast<LPVOID>(memoryAddress);
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, target, static_cast<size_t>(toBytes.size()), PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new bytes */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, target, toBytes.data(),
        static_cast<size_t>(toBytes.size()), &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, target, static_cast<size_t>(toBytes.size()), oldProtect, &tmp);

    return ok && bytesWritten == toBytes.size();
}

std::vector<uint8_t> Utilities::Memory::External::IndirectGetBytes(const HANDLE& hProcess, const void* memoryPtr, size_t byteCount)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectGetBytes(hProcess, memoryAddress, byteCount);
}

std::vector<uint8_t> Utilities::Memory::External::IndirectGetBytes(const HANDLE& hProcess, const uintptr_t& memoryAddress, size_t byteCount)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false || byteCount == 0)
        return {};

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return {};

    if (IsValidAddress(hProcess, dataAddress) == false)
        return {};

    std::vector<uint8_t> buffer(byteCount);

    /* Read and return the bytes from the target address. */
    bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        buffer.data(), buffer.size(), &bytesRead)
        || bytesRead != buffer.size())
        return {};

    return buffer;
}

bool Utilities::Memory::External::IndirectSetBytes(const HANDLE& hProcess, const void* memoryPtr, const std::vector<uint8_t>& newBytes)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectSetBytes(hProcess, memoryAddress, newBytes);
}

bool Utilities::Memory::External::IndirectSetBytes(const HANDLE& hProcess, const uintptr_t& memoryAddress, const std::vector<uint8_t>& newBytes)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false || newBytes.empty())
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    LPVOID target = reinterpret_cast<LPVOID>(dataAddress);
    size_t byteSize = newBytes.size();

    /* Make the memory region writable. */
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, target, byteSize, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new bytes. */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, target, newBytes.data(), byteSize, &bytesWritten);

    /* Restore the original protection. */
    DWORD tmp;
    VirtualProtectEx(hProcess, target, byteSize, oldProtect, &tmp);

    return ok && bytesWritten == byteSize;
}

bool Utilities::Memory::External::IndirectPatchBytes(const HANDLE& hProcess, const void* memoryPtr,
    const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes)
{
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(memoryPtr);
    return IndirectPatchBytes(hProcess, memoryAddress, fromBytes, toBytes);
}

bool Utilities::Memory::External::IndirectPatchBytes(const HANDLE& hProcess, const uintptr_t& memoryAddress,
    const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes)
{
    /* Verify that the address is valid. */
    if (IsValidAddress(hProcess, memoryAddress) == false)
        return false;

    /* Read the data pointer from memoryAddress */
    uintptr_t dataAddress = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(memoryAddress),
        &dataAddress, sizeof(dataAddress), &bytesRead)
        || bytesRead != sizeof(dataAddress))
        return false;

    if (IsValidAddress(hProcess, dataAddress) == false)
        return false;

    /* Sizes must match and be non-zero. */
    if (fromBytes.size() == 0 || fromBytes.size() != toBytes.size())
        return false;

    /* Verify that the current bytes match the expected ones. */
    std::vector<uint8_t> current(fromBytes.size());
    bytesRead = 0;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dataAddress),
        current.data(), current.size(), &bytesRead)
        || bytesRead != current.size())
        return false;

    if (!std::equal(current.begin(), current.end(), fromBytes.begin())) // Only patch if the current bytes match 'fromBytes'.
        return false;

    /* Make the memory region writable */
    LPVOID target = reinterpret_cast<LPVOID>(dataAddress);
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, target, static_cast<size_t>(toBytes.size()), PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE)
        return false;

    /* Write the new bytes */
    SIZE_T bytesWritten = 0;
    BOOL ok = WriteProcessMemory(hProcess, target, toBytes.data(),
        static_cast<size_t>(toBytes.size()), &bytesWritten);

    /* Restore the original protection */
    DWORD tmp;
    VirtualProtectEx(hProcess, target, static_cast<size_t>(toBytes.size()), oldProtect, &tmp);

    return ok && bytesWritten == toBytes.size();
}




uint64_t Utilities::Time::GetUnixTimestamp()
{
    std::chrono::time_point now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
}


std::string Utilities::Time::GetUtcDate(const uint64_t& timestamp)
{
    std::chrono::sys_seconds timePoint{ std::chrono::seconds(timestamp) };
    return std::format("{:%Y-%m-%dT%H:%M:%S.000Z}", timePoint);
}

std::string Utilities::Time::GetUtcDate()
{
    return GetUtcDate(GetUnixTimestamp());
}