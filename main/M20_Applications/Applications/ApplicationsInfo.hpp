#pragma once

#include "IApplication.hpp"
#include "Application.hpp"

class ApplicationsInfo
{
public:
    static constexpr uint8_t NR_OF_APPLICATIONS = 3;

    struct ApplicationsInfoStruct
    {
        EApplicationId id;
        const char* name;
        IApplication::EType type; 
        std::span<const IApplication::ETag> tags;
    };

    static uint16_t GetNrOfApplications();
    
    static EApplicationId GetIdByIndex(
        uint16_t applicationIndex);

    static uint16_t GetIndexById(
        EApplicationId id);

    static std::string_view GetNameByIndex(
        uint16_t applicationIndex);

    static std::string_view GetNameById(
        EApplicationId id);

    static Application::EType GetTypeByIndex(
        uint16_t applicationIndex);

    static Application::EType GetTypeById(
        EApplicationId id);

    static std::span<const Application::ETag> GetTagsByIndex(
        uint16_t applicationIndex);

    static std::span<const Application::ETag> GetTagsById(
        EApplicationId id);

    static bool GetFavoriteByIndex(
        uint16_t applicationIndex);
    
    static bool GetFavoriteById(
        EApplicationId id);

    static bool IsNewByIndex(
        uint16_t applicationIndex);

    static bool IsNewById(
        EApplicationId id);

    static uint16_t GetNrOfStartsByIndex(
        uint16_t applicationIndex);
        
    static uint16_t GetNrOfStartsById(
        EApplicationId id);

    static uint32_t GetLastStartTimeByIndex(
        uint16_t applicationIndex);

    static uint32_t GetLastStartTimeById(
        EApplicationId id);

private:
    ApplicationsInfo(); // not used

    static const std::array<ApplicationsInfoStruct, NR_OF_APPLICATIONS> _applicationsInfo;
};
