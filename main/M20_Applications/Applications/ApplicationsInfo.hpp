#pragma once

#include "IApplication.hpp"
#include "Application.hpp"

class ApplicationsInfo
{
public:
    struct ApplicationsInfoStruct
    {
        IApplication::EId id;
        const char* name;
        IApplication::EType type; 
        std::span<const IApplication::ETag> tags;
    };

    static uint16_t GetNrOfApplications();
    
    static IApplication::EId GetIdByIndex(
        uint16_t applicationIndex);

    static uint16_t GetIndexById(
        IApplication::EId id);

    static std::string_view GetNameByIndex(
        uint16_t applicationIndex);

    static std::string_view GetNameById(
        IApplication::EId id);

    static Application::EType GetTypeByIndex(
        uint16_t applicationIndex);

    static Application::EType GetTypeById(
        IApplication::EId id);

    static std::span<const Application::ETag> GetTagsByIndex(
        uint16_t applicationIndex);

    static std::span<const Application::ETag> GetTagsById(
        IApplication::EId id);

    static bool GetFavoriteByIndex(
        uint16_t applicationIndex);
    
    static bool GetFavoriteById(
        IApplication::EId id);

    static bool IsNewByIndex(
        uint16_t applicationIndex);

    static bool IsNewById(
        IApplication::EId id);

    static uint16_t GetNrOfStartsByIndex(
        uint16_t applicationIndex);
        
    static uint16_t GetNrOfStartsById(
        IApplication::EId id);

    static uint32_t GetLastStartTimeByIndex(
        uint16_t applicationIndex);

    static uint32_t GetLastStartTimeById(
        IApplication::EId id);

private:
    ApplicationsInfo(); // not used

    static const std::array<ApplicationsInfoStruct, 2> _applicationsInfo;
};
