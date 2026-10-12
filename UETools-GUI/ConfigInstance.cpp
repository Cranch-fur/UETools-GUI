#include "ConfigInstance.h"






ConfigInstance::ConfigInstance(const std::string& filePath)
    : FileInstance(filePath)
{
}

ConfigInstance::ConfigInstance(const std::wstring& filePath)
    : FileInstance(filePath)
{
}




template <typename T>
struct IsSupportedConfigType
{
    /* Keep this in sync with ConfigInstance::Value (std::variant<...>). */
    static constexpr bool Value = std::is_same_v<T, bool>
                                  || std::is_same_v<T, int>
                                  || std::is_same_v<T, float>
                                  || std::is_same_v<T, std::array<float, 2>>
                                  || std::is_same_v<T, std::array<float, 3>>
                                  || std::is_same_v<T, std::array<float, 4>>
                                  || std::is_same_v<T, std::string>;
};




const bool ConfigInstance::Load()
{
    _values.clear();
    _keysOrder.clear(); // Clear key order array to avoid duplicates on re-load.

    std::vector<std::string> lines;
    if (ReadLines(&lines) == false) // Check if I/O error occurred (file missing, access denied, etc.).
    {
        return false;
    }

    for (const std::string& rawLine : lines)
    {
        const std::string line = Trim(rawLine);

        if (IsLineCommentOrEmpty(line)) // Check if line is blank or a full-line comment.
        {
            continue;
        }

        const std::optional<std::pair<std::string, std::string>> KeyValue = SplitKeyValue(line);
        if (KeyValue.has_value() == false) // Check if line is malformed (no "=").
        {
            continue;
        }

        const std::string key = Trim(KeyValue->first);
        if (key.empty()) // Check if key is empty.
        {
            continue;
        }

        const std::string rawValue = Trim(KeyValue->second);
        const std::optional<Value> value = ParseValueWithOptionalType(rawValue);
        if (value.has_value() == false) // Check if value token is invalid.
        {
            continue;
        }

        if (_values.find(key) == _values.end()) // Check if key is new to preserve order.
        {
            _keysOrder.push_back(key);
        }

        _values[key] = *value; // Last occurrence of entry (key) wins.
    }

    return true;
}

const bool ConfigInstance::Save()
{
    std::vector<std::string> lines;
    lines.reserve(_values.size());

    /* Serialize in "key = type:value" form following the original insertion order. */
    for (const std::string& key : _keysOrder)
    {
        const std::string line = Value_ToLine(key, _values.at(key));
        lines.push_back(line);
    }

    return SaveLines(lines);
}


template <typename T>
const std::optional<T> ConfigInstance::GetKey(const std::string& key)
{
    static_assert(IsSupportedConfigType<T>::Value, "Unsupported config type.");

    const auto value = _values.find(key);
    if (value == _values.end()) // Check if key is not found.
    {
        return std::nullopt;
    }

    /* Fast path: exact type match in the variant. */
    if (std::holds_alternative<T>(value->second))
    {
        return std::get<T>(value->second);
    }

    /* Backward/forward compatibility: allow reading typed values from stored strings. */
    if (std::holds_alternative<std::string>(value->second))
    {
        const std::string& text = std::get<std::string>(value->second);

        if constexpr (std::is_same_v<T, bool>)
            return TryParseBool(text);

        if constexpr (std::is_same_v<T, int>)
            return TryParseInt(text);

        if constexpr (std::is_same_v<T, float>)
            return TryParseFloat(text);

        if constexpr (std::is_same_v<T, std::array<float, 2>>)
            return TryParseFloat2(text);

        if constexpr (std::is_same_v<T, std::array<float, 3>>)
            return TryParseFloat3(text);

        if constexpr (std::is_same_v<T, std::array<float, 4>>)
            return TryParseFloat4(text);

        if constexpr (std::is_same_v<T, std::string>)
            return text;
    }

    return std::nullopt;
}

template <typename T>
void ConfigInstance::SetKey(const std::string& key, const T& value)
{
    static_assert(IsSupportedConfigType<T>::Value, "Unsupported config type.");

    if (key.empty()) // Check if key is invalid.
    {
        return;
    }

    if (_values.find(key) == _values.end())
    {
        _keysOrder.push_back(key);
    }

    _values[key] = value;
}

void ConfigInstance::SetKey(const std::string& key, const char* value)
{
    if (key.empty() || value == nullptr) // Check if key or value is invalid.
    {
        return;
    }

    if (_values.find(key) == _values.end())
    {
        _keysOrder.push_back(key);
    }

    _values[key] = std::string(value);
}

void ConfigInstance::SetKey(const std::string& key, const std::array<float, 2>& value)
{
    if (key.empty()) // Check if key is invalid.
    {
        return;
    }

    if (_values.find(key) == _values.end())
    {
        _keysOrder.push_back(key);
    }

    _values[key] = value;
}

void ConfigInstance::SetKey(const std::string& key, const std::array<float, 3>& value)
{
    if (key.empty()) // Check if key is invalid.
    {
        return;
    }

    if (_values.find(key) == _values.end())
    {
        _keysOrder.push_back(key);
    }

    _values[key] = value;
}

void ConfigInstance::SetKey(const std::string& key, const std::array<float, 4>& value)
{
    if (key.empty()) // Check if key is invalid.
    {
        return;
    }

    if (_values.find(key) == _values.end())
    {
        _keysOrder.push_back(key);
    }

    _values[key] = value;
}


const bool ConfigInstance::HasKey(const std::string& key)
{
    return _values.find(key) != _values.end();
}

void ConfigInstance::RemoveKey(const std::string& key)
{
    if (_values.find(key) != _values.end())
    {
        _values.erase(key);
        _keysOrder.erase(std::remove(_keysOrder.begin(), _keysOrder.end(), key), _keysOrder.end());
    }
}


void ConfigInstance::ClearKeys()
{
    _values.clear();
    _keysOrder.clear();
}




const std::string ConfigInstance::Trim(const std::string& text)
{
    size_t start = 0;
    size_t end = text.size();

    while (start < end && std::isspace(static_cast<unsigned char>(text[start])) != 0)
    {
        ++start;
    }

    while (end > start && std::isspace(static_cast<unsigned char>(text[end - 1])) != 0)
    {
        --end;
    }

    return text.substr(start, end - start);
}

const bool ConfigInstance::IsLineCommentOrEmpty(const std::string& line)
{
    if (line.empty()) // Check if empty line.
    {
        return true;
    }

    if (line.rfind("#", 0) == 0) // Check if shell-style comment.
    {
        return true;
    }

    if (line.rfind(";", 0) == 0) // Check if INI-style comment.
    {
        return true;
    }

    if (line.rfind("//", 0) == 0) // Check if C++-style comment.
    {
        return true;
    }

    return false;
}


const bool ConfigInstance::ReadFloat(const std::string& text, size_t inPos, size_t* outPos, float* outValue)
{
    if (outPos == nullptr || outValue == nullptr) // Check if output pointers are invalid.
    {
        return false;
    }

    size_t position = inPos;

    /* Skip separators between numbers: spaces/tabs/commas. */
    while (position < text.size() && (text[position] == ' ' || text[position] == '\t' || text[position] == ','))
    {
        ++position;
    }

    if (position >= text.size()) // Check if reached end of string before parsing.
    {
        return false;
    }

    const char* begin = text.data() + position;
    const char* end = text.data() + text.size();

    float value = 0.0f;
    std::from_chars_result fromCharsResult = std::from_chars(begin, end, value, std::chars_format::general);

    if (fromCharsResult.ec != std::errc()) // Check if float parsing failed.
    {
        return false;
    }

    *outPos = static_cast<size_t>(fromCharsResult.ptr - text.data());
    *outValue = value;

    return true;
}


const std::optional<std::pair<std::string, std::string>> ConfigInstance::SplitKeyValue(const std::string& line)
{
    const size_t pos = line.find('=');
    if (pos == std::string::npos) // Check if key/value delimiter is missing.
    {
        return std::nullopt;
    }

    const std::string left = line.substr(0, pos);
    const std::string right = line.substr(pos + 1);

    return std::make_pair(left, right);
}

const std::optional<ConfigInstance::Value> ConfigInstance::ParseValueWithOptionalType(const std::string& rawValue)
{
    const size_t colonPos = rawValue.find(':');

    if (colonPos == std::string::npos) // If no "type:" prefix is present, keep it as a string.
    {
        return Value(rawValue);
    }

    const std::string typePart = String_ToLower(Trim(rawValue.substr(0, colonPos)));
    const std::string valuePart = Trim(rawValue.substr(colonPos + 1));

    if (typePart == "bool")
    {
        const std::optional<bool> value = TryParseBool(valuePart);
        if (value.has_value() == false) // Check if bool token is invalid.
        {
            return std::nullopt;
        }

        return Value(*value);
    }

    if (typePart == "int")
    {
        const std::optional<int> value = TryParseInt(valuePart);
        if (value.has_value() == false) // Check if integer token is invalid.
        {
            return std::nullopt;
        }

        return Value(*value);
    }

    if (typePart == "float")
    {
        const std::optional<float> value = TryParseFloat(valuePart);
        if (value.has_value() == false) // Check if float token is invalid.
        {
            return std::nullopt;
        }

        return Value(*value);
    }

    if (typePart == "float2")
    {
        const std::optional<std::array<float, 2>> value = TryParseFloat2(valuePart);
        if (value.has_value() == false) // Check if float2 tokens are invalid.
        {
            return std::nullopt;
        }

        return Value(*value);
    }

    if (typePart == "float3")
    {
        const std::optional<std::array<float, 3>> value = TryParseFloat3(valuePart);
        if (value.has_value() == false) // Check if float3 tokens are invalid.
        {
            return std::nullopt;
        }

        return Value(*value);
    }

    if (typePart == "float4")
    {
        const std::optional<std::array<float, 4>> value = TryParseFloat4(valuePart);
        if (value.has_value() == false) // Check if float4 tokens are invalid.
        {
            return std::nullopt;
        }

        return Value(*value);
    }

    if (typePart == "string")
    {
        return Value(valuePart);
    }

    /* Unknown type token -> treat everything as string. */
    return Value(rawValue);
}


const std::string ConfigInstance::String_ToLower(const std::string& text)
{
    std::string outText = text;
    for (char& c : outText)
    {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }

    return outText;
}

const std::string ConfigInstance::Float_ToString(float value)
{
    std::ostringstream stringStream = {};
    stringStream << std::setprecision(9) << value;

    return stringStream.str();
}

const std::string ConfigInstance::Value_ToLine(const std::string& key, const Value& value)
{
    if (std::holds_alternative<bool>(value))
    {
        return key + " = bool:" + (std::get<bool>(value) ? "true" : "false");
    }

    if (std::holds_alternative<int>(value))
    {
        return key + " = int:" + std::to_string(std::get<int>(value));
    }

    if (std::holds_alternative<float>(value))
    {
        return key + " = float:" + Float_ToString(std::get<float>(value));
    }

    if (std::holds_alternative<std::array<float, 2>>(value))
    {
        const std::array<float, 2>& arr = std::get<std::array<float, 2>>(value);

        std::ostringstream stringStream;
        stringStream << key << " = float2:" // Fixed previous copy-paste bug (was float3).
            << std::setprecision(9) << arr[0] << " "
            << std::setprecision(9) << arr[1];

        return stringStream.str();
    }

    if (std::holds_alternative<std::array<float, 3>>(value))
    {
        const std::array<float, 3>& arr = std::get<std::array<float, 3>>(value);

        std::ostringstream stringStream;
        stringStream << key << " = float3:"
            << std::setprecision(9) << arr[0] << " "
            << std::setprecision(9) << arr[1] << " "
            << std::setprecision(9) << arr[2];

        return stringStream.str();
    }

    if (std::holds_alternative<std::array<float, 4>>(value))
    {
        const std::array<float, 4>& arr = std::get<std::array<float, 4>>(value);

        std::ostringstream stringStream;
        stringStream << key << " = float4:"
            << std::setprecision(9) << arr[0] << " "
            << std::setprecision(9) << arr[1] << " "
            << std::setprecision(9) << arr[2] << " "
            << std::setprecision(9) << arr[3];

        return stringStream.str();
    }

    /* Explicit type prefix keeps values like "C:\\..." or "int:5" intact on re-load. */
    return key + " = string:" + std::get<std::string>(value);
}


const std::optional<bool> ConfigInstance::TryParseBool(const std::string& text)
{
    const std::string v = String_ToLower(Trim(text));

    if (v == "true" || v == "1")
    {
        return true;
    }

    if (v == "false" || v == "0")
    {
        return false;
    }

    return std::nullopt;
}

const std::optional<int> ConfigInstance::TryParseInt(const std::string& text)
{
    const std::string token = Trim(text);
    if (token.empty()) // Check if token is invalid.
    {
        return std::nullopt;
    }

    int value = 0;

    const char* begin = token.data();
    const char* end = token.data() + token.size();

    std::from_chars_result fromCharsResult = std::from_chars(begin, end, value);
    if (fromCharsResult.ec != std::errc() || fromCharsResult.ptr != end) // Check if parse failed or has trailing garbage.
    {
        return std::nullopt;
    }

    return value;
}

const std::optional<float> ConfigInstance::TryParseFloat(const std::string& text)
{
    const std::string token = Trim(text);
    if (token.empty()) // Check if token is invalid.
    {
        return std::nullopt;
    }

    float value = 0.0f;

    const char* begin = token.data();
    const char* end = token.data() + token.size();

    std::from_chars_result fromCharsResult = std::from_chars(begin, end, value, std::chars_format::general);
    if (fromCharsResult.ec != std::errc() || fromCharsResult.ptr != end) // Check if parse failed or has trailing garbage.
    {
        return std::nullopt;
    }

    return value;
}

const std::optional<std::array<float, 2>> ConfigInstance::TryParseFloat2(const std::string& text)
{
    const std::string token = Trim(text);
    if (token.empty()) // Check if token is invalid.
    {
        return std::nullopt;
    }

    size_t pos = 0;
    std::array<float, 2> arr;

    for (int i = 0; i < 2; ++i)
    {
        if (ReadFloat(token, pos, &pos, &arr[i]) == false) // Check if reading float value failed.
        {
            return std::nullopt;
        }
    }

    return arr;
}

const std::optional<std::array<float, 3>> ConfigInstance::TryParseFloat3(const std::string& text)
{
    const std::string token = Trim(text);
    if (token.empty()) // Check if token is invalid.
    {
        return std::nullopt;
    }

    size_t pos = 0;
    std::array<float, 3> arr;

    for (int i = 0; i < 3; ++i)
    {
        if (ReadFloat(token, pos, &pos, &arr[i]) == false) // Check if reading float value failed.
        {
            return std::nullopt;
        }
    }

    return arr;
}

const std::optional<std::array<float, 4>> ConfigInstance::TryParseFloat4(const std::string& text)
{
    const std::string token = Trim(text);
    if (token.empty()) // Check if token is invalid.
    {
        return std::nullopt;
    }

    size_t pos = 0;
    std::array<float, 4> arr;

    for (int i = 0; i < 4; ++i)
    {
        if (ReadFloat(token, pos, &pos, &arr[i]) == false) // Check if reading float value failed.
        {
            return std::nullopt;
        }
    }

    return arr;
}

/* Explicit instantiations to keep all template logic in .cpp */
template const std::optional<bool> ConfigInstance::GetKey<bool>(const std::string& key);
template const std::optional<int> ConfigInstance::GetKey<int>(const std::string& key);
template const std::optional<float> ConfigInstance::GetKey<float>(const std::string& key);
template const std::optional<std::array<float, 2>> ConfigInstance::GetKey<std::array<float, 2>>(const std::string& key);
template const std::optional<std::array<float, 3>> ConfigInstance::GetKey<std::array<float, 3>>(const std::string& key);
template const std::optional<std::array<float, 4>> ConfigInstance::GetKey<std::array<float, 4>>(const std::string& key);
template const std::optional<std::string> ConfigInstance::GetKey<std::string>(const std::string& key);

template void ConfigInstance::SetKey<bool>(const std::string& key, const bool& value);
template void ConfigInstance::SetKey<int>(const std::string& key, const int& value);
template void ConfigInstance::SetKey<float>(const std::string& key, const float& value);
template void ConfigInstance::SetKey<std::array<float, 2>>(const std::string& key, const std::array<float, 2>& value);
template void ConfigInstance::SetKey<std::array<float, 3>>(const std::string& key, const std::array<float, 3>& value);
template void ConfigInstance::SetKey<std::array<float, 4>>(const std::string& key, const std::array<float, 4>& value);
template void ConfigInstance::SetKey<std::string>(const std::string& key, const std::string& value);