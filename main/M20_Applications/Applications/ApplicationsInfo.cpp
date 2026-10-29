#include "ApplicationsInfo.hpp"
#include "IApplication.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include <array>

static constexpr std::array<IApplication::ETag, 2> PongTags
{
    IApplication::ETag::Arcade,
    IApplication::ETag::Continuous
};

static constexpr std::array<IApplication::ETag, 2> AutoRunTags
{
    IApplication::ETag::LedStrips,
    IApplication::ETag::Continuous
};

/* static */ const std::array<
    ApplicationsInfo::ApplicationsInfoStruct, ApplicationsInfo::NR_OF_APPLICATIONS>
ApplicationsInfo::_applicationsInfo
{ {
    {
        EApplicationId::Menu,
        "Menu",
        IApplication::EType::Menu,
        {}
    },
    {
        EApplicationId::Pong,
        "Pong",
        IApplication::EType::Game,
        std::span<const IApplication::ETag>{PongTags}
    },
    {
        EApplicationId::AutoRun,
        "AutoRun",
        IApplication::EType::Utility,
        std::span<const IApplication::ETag>{AutoRunTags}
    }
} };

/* static */ uint16_t ApplicationsInfo::GetNrOfApplications()
{
    return static_cast<uint16_t>(_applicationsInfo.size());
}

/* static */ EApplicationId ApplicationsInfo::GetIdByIndex(
    uint16_t applicationIndex)
{
    return _applicationsInfo[applicationIndex].id;
}

/* static */ uint16_t ApplicationsInfo::GetIndexById(
    EApplicationId id)
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
    EApplicationId id)
{
    return _applicationsInfo[GetIndexById(id)].name;
}

/* static */ Application::EType ApplicationsInfo::GetTypeByIndex(
    uint16_t applicationIndex)
{
    return _applicationsInfo[applicationIndex].type;
}

/* static */ Application::EType ApplicationsInfo::GetTypeById(
    EApplicationId id)
{
    return _applicationsInfo[GetIndexById(id)].type;
}

/* static */ std::span<const Application::ETag> ApplicationsInfo::GetTagsByIndex(
    uint16_t applicationIndex)
{
    return _applicationsInfo[applicationIndex].tags;
}

/* static */ std::span<const Application::ETag> ApplicationsInfo::GetTagsById(
    EApplicationId id)
{
    return _applicationsInfo[GetIndexById(id)].tags;
}


/* static */ bool ApplicationsInfo::GetFavoriteByIndex(
    uint16_t /* NOSONAR TODO applicationIndex */)
{
    //MA: not static?
    return true;
}

/* static */ bool ApplicationsInfo::GetFavoriteById(
    EApplicationId /* NOSONAR TODO id */) //
{
    //MA : not static?
    return true;
}

/* static */ bool ApplicationsInfo::IsNewByIndex(
    uint16_t /* NOSONAR TODO applicationIndex */ )
{
    //MA
    return true; 
}

/* static */ bool ApplicationsInfo::IsNewById(
    EApplicationId /* NOSONAR TODO id */)
{
    //MA
    return true;
}

/* static */ uint16_t ApplicationsInfo::GetNrOfStartsByIndex(
    uint16_t /* NOSONAR TODO applicationIndex */ )
{
    //MA
    return 0;
}

/* static */ uint16_t ApplicationsInfo::GetNrOfStartsById(
    EApplicationId)
{
    //MA
    return 0;
}

/* static */ uint32_t ApplicationsInfo::GetLastStartTimeByIndex(
    uint16_t /* NOSONAR TODO applicationIndex */)
{
    //MA
    return 0;
}

/* static */ uint32_t ApplicationsInfo::GetLastStartTimeById(
    EApplicationId)
{
    //MA
    return 0;
}
