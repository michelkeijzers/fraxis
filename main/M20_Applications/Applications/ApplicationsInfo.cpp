#include "ApplicationsInfo.hpp"
#include "IApplication.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"

static constexpr IApplication::ETag PongTags[]
{
    IApplication::ETag::Arcade,
    IApplication::ETag::Continuous
};

/* static */ const std::array<ApplicationsInfo::ApplicationsInfoStruct, 2>
ApplicationsInfo::_applicationsInfo
{ {
    {
        IApplication::EId::Menu,
        "Menu",
        IApplication::EType::Menu,
        {}
    },
    {
        IApplication::EId::Pong,
        "Pong",
        IApplication::EType::Game,
        std::span<const IApplication::ETag>{PongTags}
    }
} };

/* static */ uint16_t ApplicationsInfo::GetNrOfApplications()
{
    return static_cast<uint16_t>(_applicationsInfo.size());
}

/* static */ IApplication::EId ApplicationsInfo::GetIdByIndex(
    uint16_t applicationIndex)
{
    return _applicationsInfo[applicationIndex].id;
}

/* static */ uint16_t ApplicationsInfo::GetIndexById(
    IApplication::EId id)
{
    for (uint16_t applicationIndex = 0; applicationIndex < ApplicationsInfo::GetNrOfApplications();
        applicationIndex++)
    {
        if (_applicationsInfo[applicationIndex].id == id)
        {
            return applicationIndex;
        }
    }

    Assert::Fail(Types::ETaskId::ApplicationsTask, "Illegal id");
    return 0;
}

/* static */  std::string_view ApplicationsInfo::GetNameByIndex(
    uint16_t applicationIndex)
{
    return _applicationsInfo[applicationIndex].name;
}

/* static */  std::string_view ApplicationsInfo::GetNameById(
    IApplication::EId id)
{
    return _applicationsInfo[GetIndexById(id)].name;
}

/* static */ Application::EType ApplicationsInfo::GetTypeByIndex(
    uint16_t applicationIndex)
{
    return _applicationsInfo[applicationIndex].type;
}

/* static */ Application::EType ApplicationsInfo::GetTypeById(
    IApplication::EId id)
{
    return _applicationsInfo[GetIndexById(id)].type;
}

/* static */ std::span<const Application::ETag> ApplicationsInfo::GetTagsByIndex(
    uint16_t applicationIndex)
{
    return _applicationsInfo[applicationIndex].tags;
}

/* static */ std::span<const Application::ETag> ApplicationsInfo::GetTagsById(
    IApplication::EId id)
{
    return _applicationsInfo[GetIndexById(id)].tags;
}


/* static */ bool ApplicationsInfo::GetFavoriteByIndex(
    uint16_t applicationIndex)
{
    //MA: not static?
    return true;
}

/* static */ bool ApplicationsInfo::GetFavoriteById(
    IApplication::EId id)
{
    //MA : not static?
    return true;
}

/* static */ bool ApplicationsInfo::IsNewByIndex(
    uint16_t applicationIndex)
{
    //MA
    return 0; 
}

/* static */ bool ApplicationsInfo::IsNewById(
    IApplication::EId id)
{
    //MA
    return 0;
}

/* static */ uint16_t ApplicationsInfo::GetNrOfStartsByIndex(
    uint16_t applicationIndex)
{
    //MA
    return 0;
}

/* static */ uint16_t ApplicationsInfo::GetNrOfStartsById(
    IApplication::EId id)
{
    //MA
    return 0;
}

/* static */ uint32_t ApplicationsInfo::GetLastStartTimeByIndex(
    uint16_t applicationIndex)
{
    //MA
    return 0;
}

/* static */ uint32_t ApplicationsInfo::GetLastStartTimeById(
    IApplication::EId id)
{
    //MA
    return 0;
}
