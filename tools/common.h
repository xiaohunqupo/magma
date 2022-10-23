#pragma once
#include <array>
#include <functional>
#include <string>
#include <fstream>

#define VK_SDK_PATH "VK_SDK_PATH"
#define VULKAN_SDK "VULKAN_SDK"
#define VULKAN_CORE_HEADER "\\Include\\vulkan\\vulkan_core.h"

// https://registry.khronos.org/vulkan/
const std::array<std::string, 18> vendors = {
    "AMD", "ANDROID", "ARM", "EXT", "FUCHSIA",
    "GGP", "GOOGLE", "HUAWEI", "IMG", "INTEL",
    "KHR", "MVK", "NN", "NV", "NVX", "QCOM",
    "SEC", "VALVE"
};

std::string::size_type findExtensionPrefix(const std::string& line, std::string& prefix)
{
    for (const auto& ext: vendors)
    {
        prefix = "VK_" + ext + "_";
        auto pos = line.find(prefix);
        if (pos != std::string::npos)
            return pos;
    }
    return std::string::npos;
}

std::string::size_type findExtensionSuffix(const std::string& line)
{
    for (const auto& ext: vendors)
    {
        auto pos = line.find(ext);
        if (pos != std::string::npos)
            return pos;
    }
    return std::string::npos;
}

std::string parseExtensionDefine(const std::string& line)
{
    std::string name;
    auto pos = findExtensionPrefix(line, name);
    if (pos != std::string::npos)
    {
        for (auto it = line.begin() + pos + name.length();
            it != line.end(); ++it)
        {
            char c = *it;
            if (isupper(c))
                return std::string();
            if (isspace(c))
                break;
            name.append(1, c);
        }
        return name;
    }
    return std::string();
}

std::string parseStructureName(const std::string& line)
{
    auto pos = line.find("VkPhysicalDevice");
    auto nextPos = line.find("VkPhysicalDevice", pos + 1);
    if ((nextPos > pos) && (nextPos < std::string::npos))
        pos = nextPos; // Go to extension typedef
    std::string name;
    for (auto it = line.begin() + pos;
        it != line.end(); ++it)
    {
        char c = *it;
        if (isspace(c) || c == '{' || c == ';')
            break;
        name.append(1, c);
    }
    return name;
}

bool isFeaturesStructure(const std::string& line) noexcept
{
    if (line.find("VkPhysicalDevice") == std::string::npos)
        return false;
    for (const auto& ext: vendors)
    {
        if (line.find("Features" + ext) != std::string::npos)
            return true;
    }
    return false;
}

bool isPropertiesStructure(const std::string& line) noexcept
{
    if (line.find("VkPhysicalDevice") == std::string::npos)
        return false;
    for (const auto& ext: vendors)
    {
        if (line.find("Properties" + ext) != std::string::npos)
            return true;
    }
    return false;
}

std::string fixupStructureTypeName(const std::string& name)
{
    const std::map<std::string, std::string> mapping = {
        {"VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16_BIT_STORAGE_FEATURES_KHR",
         "VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES_KHR"},
        {"VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8_BIT_STORAGE_FEATURES_KHR",
         "VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8BIT_STORAGE_FEATURES_KHR"},
        {"VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT_16_INT_8_FEATURES_KHR",
         "VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT16_INT8_FEATURES_KHR"},
        {"VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INDEX_TYPE_UINT_8_FEATURES_EXT",
         "VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INDEX_TYPE_UINT8_FEATURES_EXT"},
        {"VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RGBA_10X_6_FORMATS_FEATURES_EXT",
         "VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RGBA10X6_FORMATS_FEATURES_EXT"},
        {"VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_INT_64_FEATURES_KHR",
         "VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_INT64_FEATURES_KHR"},
        {"VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_ATOMIC_INT_64_FEATURES_EXT",
         "VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_ATOMIC_INT64_FEATURES_EXT"},
        {"VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXTURE_COMPRESSION_ASTCHDR_FEATURES_EXT",
         "VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXTURE_COMPRESSION_ASTC_HDR_FEATURES_EXT"},
    };
    // Vulkan naming convention doesn't follow strict rules about
    // underscores with digits and also has another issues,
    // so use this name mapping to fix conversion errors.
    auto it = mapping.find(name);
    if (it == mapping.end())
        return name;
    return it->second;
}

std::string convertStructureNameToStructureType(const std::string& structureName)
{
    constexpr size_t firstChar = 2; // Skip "Vk"
    bool prevLower = true;
    bool prevDigit = false;
    std::string name = "VK_STRUCTURE_TYPE_";
    for (size_t i = firstChar, len = structureName.length(); i < len; ++i)
    {
        char c = structureName.at(i);
        if (isupper(c) && i > firstChar)
        {
            if (prevLower)
                name.append(1, '_');
            else // Sequence of upper case sybmols
            {
                if (i + 1 < len)
                {   // Check if the next character is lower case
                    char c2 = structureName.at(i + 1);
                    if (islower(c2))
                        name.append(1, '_');
                }
            }
        }
        else
        {
            if (isdigit(c) && !prevDigit)
                name.append(1, '_');
        }
        name.append(1, toupper(c));
        prevLower = islower(c);
        prevDigit = isdigit(c);
    }
    return fixupStructureTypeName(name);
}

void writeGeneratedByUtilityToolWarning(std::ofstream& fs)
{
    fs << "// Generated by utility tool. DO NOT MODIFY!" << std::endl;
}