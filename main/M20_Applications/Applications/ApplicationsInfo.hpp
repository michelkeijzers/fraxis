#pragma once

#include "IApplication.hpp"
#include "Application.hpp"

class ApplicationsInfo
{
public:
    static constexpr uint8_t NR_OF_APPLICATIONS = 3;

    struct ApplicationsInfoStruct
    {
        EApplicationId id = EApplicationId::Count;
        const char* name = "";
        IApplication::EType type = IApplication::EType::Last; 
        std::span<const IApplication::ETag> tags = {};
    };

    static uint16_t GetNrOfApplications();
    
    static EApplicationId GetIdByIndex(
        uint16_t applicationIndex);

    static uint16_t GetIndexById(
        EApplicationId applicationId);

    static std::string_view GetNameByIndex(
        uint16_t applicationIndex);

    static std::string_view GetNameById(
        EApplicationId applicationId);

    static Application::EType GetTypeByIndex(
        uint16_t applicationIndex);

    static Application::EType GetTypeById(
        EApplicationId applicationId);

    static std::span<const Application::ETag> GetTagsByIndex(
        uint16_t applicationIndex);

    static std::span<const Application::ETag> GetTagsById(
        EApplicationId applicationId);

    static bool GetFavoriteByIndex(
        uint16_t applicationIndex);
    
    static bool GetFavoriteById(
        EApplicationId applicationId);

    static bool IsNewByIndex(
        uint16_t applicationIndex);

    static bool IsNewById(
        EApplicationId applicationId);

    static uint16_t GetNrOfStartsByIndex(
        uint16_t applicationIndex);
        
    static uint16_t GetNrOfStartsById(
        EApplicationId applicationId);

    static uint32_t GetLastStartTimeByIndex(
        uint16_t applicationIndex);

    static uint32_t GetLastStartTimeById(
        EApplicationId applicationId);

private:
    ApplicationsInfo(); // not used

    static const std::array<ApplicationsInfoStruct, NR_OF_APPLICATIONS> _applicationsInfo;
};
