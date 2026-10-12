#pragma once
#include "FileInstance.h"

#include <array>
#include <unordered_map>
#include <variant>






class ConfigInstance : public FileInstance
{
public:
    using Value = std::variant<bool, int, float, std::array<float, 2>, std::array<float, 3>, std::array<float, 4>, std::string>;

    ConfigInstance(const std::string& filePath);
    ConfigInstance(const std::wstring& filePath);

    const bool Load();
    const bool Save();

    template <typename T>
    const std::optional<T> GetKey(const std::string& key);

    template <typename T>
    void SetKey(const std::string& key, const T& value);
    void SetKey(const std::string& key, const char* value);
    void SetKey(const std::string& key, const std::array<float, 2>& value);
    void SetKey(const std::string& key, const std::array<float, 3>& value);
    void SetKey(const std::string& key, const std::array<float, 4>& value);

    const bool HasKey(const std::string& key);
    void RemoveKey(const std::string& key);

    void ClearKeys();

private:
    std::unordered_map<std::string, Value> _values;
    std::vector<std::string> _keysOrder;

    static const std::string Trim(const std::string& text);
    static const bool IsLineCommentOrEmpty(const std::string& line);
    static const bool ReadFloat(const std::string& text, size_t inPos, size_t* outPos, float* outValue);

    static const std::optional<std::pair<std::string, std::string>> SplitKeyValue(const std::string& line);
    static const std::optional<Value> ParseValueWithOptionalType(const std::string& rawValue);

    static const std::string String_ToLower(const std::string& text);
    static const std::string Float_ToString(float value);
    static const std::string Value_ToLine(const std::string& key, const Value& value);

    static const std::optional<bool> TryParseBool(const std::string& text);
    static const std::optional<int> TryParseInt(const std::string& text);
    static const std::optional<float> TryParseFloat(const std::string& text);
    static const std::optional<std::array<float, 2>> TryParseFloat2(const std::string& text);
    static const std::optional<std::array<float, 3>> TryParseFloat3(const std::string& text);
    static const std::optional<std::array<float, 4>> TryParseFloat4(const std::string& text);
};

