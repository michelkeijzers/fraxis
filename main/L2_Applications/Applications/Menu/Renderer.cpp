#include "Renderer.hpp"
#include "../../../L4_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include "../../../L9_Utilities/String/StringUtilities.hpp"
#include "../../../L9_Utilities/Assert/Assert.hpp"
#include "../../../L9_Utilities/Math/MathUtilities.hpp"
#include "../Application.hpp"
#include "../../ApplicationsManager.hpp"
#include <cstdio>
#include <cstdlib>

Renderer::Renderer(
    const ApplicationsManager& applicationsManager,
    States& states)
    :
    _applicationsManager(applicationsManager),
    _states(states),
    _previousResult({}),
    _currentResult({}),
    _iterationLines({})
{}

std::array<std::string, Renderer::NR_OF_LINES> Renderer::Render()
{
    _previousResult = _currentResult; // Copy by value
    for (uint8_t index = 0; index < NR_OF_LINES; index++)
    {
        _currentResult[index] = "";
    }

    switch (_states.GetCurrentState())
    {
    case States::EState::S000_Welcome:                   RenderS000(); break;
    case States::EState::S010_SelectAppType:             RenderS010(); break;
    case States::EState::S020_SelectViewMode:            RenderS020(); break;
    case States::EState::S021_SelectTag:                 RenderS021(); break;
    case States::EState::S030_SelectApp:                 RenderS030(); break;
    case States::EState::S040_AppMode:                   RenderS040(); break;
    default:                                             RenderDefault(); break;
    }

    for (uint8_t index = 0; index < NR_OF_LINES; index++)
    {
        _currentResult[index] = StringUtilities::LeftAlign(_currentResult[index], Lcd2004::LINE_WIDTH);
        Assert::Equals(
            Types::ETaskId::ApplicationsTask,
            _currentResult[index].size(),
            Lcd2004::LINE_WIDTH,
            "_currentResult.line" + std::to_string(index + 1));
    }

    return _currentResult;
}

void Renderer::RenderS000()
{
    _currentResult[0] = "--------------------";
    _currentResult[1] = "Welcome to";
    _currentResult[2] = "FRAXIS v0.1";
    _currentResult[3] = "--------------------";
}

void Renderer::RenderS010()
{
    _currentResult[0] = "Select App Type";
    auto appTypeIndex = static_cast<uint8_t>(_states.GetSelectedAppTypeIndex());
    const std::vector<std::string_view> lookupTable =
    { "Game", "Demo", "Tool", "Utility" };
    Assert::Equals(Types::ETaskId::ApplicationsTask,
        lookupTable.size(), static_cast<uint16_t>(Application::EType::Last), "S020 lookupTable");
    RenderItems(lookupTable, appTypeIndex);
}

void Renderer::RenderS020()
{
    _currentResult[0] = "Select View Mode";
    auto viewModeIndex = static_cast<uint8_t>(_states.GetSelectedViewModeIndex());
    const std::vector<std::string_view> lookupTable = {
        "Recent", "Most Used", "Favorites", "Alphabetic", "Tag", "New", "Random"
    };
    Assert::Equals(Types::ETaskId::ApplicationsTask,
        lookupTable.size(), static_cast<uint16_t>(States::EViewMode::Last), "S020 lookupTable");
    RenderItems(lookupTable, viewModeIndex);
}


void Renderer::RenderS021()
{
    _currentResult[0] = "Select Tag";
    auto tagIndex = _states.GetSelectedTagIndex();

    const std::vector<std::string_view> lookupTable =
    {
        "Arcade", "Audio", "Continuous", "Diagnostics", "Displays",
        "DistanceSensors", "HardwareTests", "Horizontal", "Info", "Interactive",
        "Joysticks", "Leds", "LedStrips", "Microphone", "Puzzle",
        "Racing", "ServiceTeste", "Shooter", "Speaker", "SinglePlayer", "Static",
        "TimeBased", "TurnBased", "TwoPlayers", "Vertical"
    };
    Assert::Equals(Types::ETaskId::ApplicationsTask,
        lookupTable.size(), static_cast<uint16_t>(Application::ETag::Last), "S021 Demo lookupTable");

    std::vector<std::string_view> filteredLookupTable = FilterTagsLookupTable(lookupTable);
    RenderItems(filteredLookupTable, tagIndex);
}

void Renderer::RenderS030()
{
    _currentResult[0] = "Select ";

    std::string appType = "";
    switch (_states.GetSelectedAppTypeIndex())
    {
    case Application::EType::Game:     appType = "Game";      break;
    case Application::EType::Demo:     appType = "Demo";      break;
    case Application::EType::Tool:     appType = "Tool";      break;
    case Application::EType::Utility:  appType = "Utility";   break;
    default:                           
        Assert::Fail(Types::ETaskId::ApplicationsTask, "Unknown app type index");
        break;
    }

    _currentResult[0] += appType;

    auto applicationIndex = _states.GetSelectedAppIndex();

    std::vector<std::string_view> lookupTable;
    for (auto& application : _states.GetSelectableApplications())
    {
        lookupTable.push_back(application->GetName());
    }
    _states.SortSelectableApplications();
    Assert::Equals(Types::ETaskId::ApplicationsTask,
        lookupTable.size(), _states.GetSelectableApplications().size(), "S030 application names");
    RenderItems(lookupTable, applicationIndex);
}

void Renderer::RenderS040()
{
    _currentResult[0] = GetCurrentApplicationName();

    std::vector<std::string_view> lookupTable =
    {
        "Start", "Running", "Resume", "Quit", "Settings", 
        "Highscore", "Make Favorite", "Reset Settings", "Reset Highscores", "Reset # Started", 
        "Reset Start Time"
    };
    Assert::Equals(Types::ETaskId::ApplicationsTask,
        lookupTable.size(), static_cast<uint16_t>(States::EAppMode::Last), "S040 App states"); 
    if ((_states.GetSelectedAppMode() == States::EAppMode::Favorite) &&
        (_applicationsManager.GetApplications()[_states.GetSelectedAppIndex()].get()->IsFavorite()))
    {
        lookupTable[static_cast<uint16_t>(_states.GetSelectedAppMode())] = "Reset Favorite";
    }

    std::vector<std::string_view> filteredLookupTable = FilterAppModesLookupTable(lookupTable);
    States::EAppMode adaptedAppMode = _states.GetSelectedAppMode();
    if ((adaptedAppMode == States::EAppMode::Idle) ||
        (adaptedAppMode == States::EAppMode::Running))
    {
        adaptedAppMode = static_cast<States::EAppMode>(0); // Map to first.
    }
    else if ((adaptedAppMode == States::EAppMode::Paused) ||
             (adaptedAppMode == States::EAppMode::Quit))
    {
        // Start and Running are filtered.
        adaptedAppMode = static_cast<States::EAppMode>(
            static_cast<uint16_t>(adaptedAppMode) - 2);
    }
    else
    {
        // Start, Running, Resume and Quit are filtered.
        adaptedAppMode = static_cast<States::EAppMode>(
            static_cast<uint16_t>(adaptedAppMode) - 3);
    }

    RenderItems(filteredLookupTable, static_cast<uint16_t>(adaptedAppMode));
}

//void Renderer::RenderS061()
//{
//    _currentResult[0] = GetCurrentApplicationName();
//
//    int displayIndex = _states.GetSelectedHighscoreIndex() + 1;
//    std::string name = GetHighscoreName(_states.GetSelectedHighscoreIndex());
//    int score = GetHighscoreValue(_states.GetSelectedHighscoreIndex());
//    // Format: " 1 MICHEL 123456"
//    snprintf(_currentResult[1].data(), Lcd2004::LINE_WIDTH, "%2d %-6.6s %6d", displayIndex, name.data(), score);
//}

void Renderer::RenderDefault()
{
    _currentResult[0] = "NOT IMPLEMENTED";
    _currentResult[1] = "YET";
}

void Renderer::RenderItems(
    const std::vector<std::string_view>& lookupTable,
    uint16_t selectedIndex)
{
    std::array<int16_t, NR_OF_ITEM_LINES> lineItemIndices = {};
    const auto nrOfItems = static_cast<uint16_t>(lookupTable.size()); 

    if (selectedIndex == 0) 
    {
        lineItemIndices[0] = 0;
        lineItemIndices[1] = 1;
        lineItemIndices[2] = 2;
    }
    else if ((selectedIndex == nrOfItems - 1) && (selectedIndex < lookupTable.size()))
    {
        lineItemIndices[0] = selectedIndex - 2;
        lineItemIndices[1] = selectedIndex - 1;
        lineItemIndices[2] = selectedIndex;
    }
    else 
    {
        lineItemIndices[0] = selectedIndex - 1;
        lineItemIndices[1] = selectedIndex;
        lineItemIndices[2] = selectedIndex + 1;
    }

    while (lineItemIndices[0] < 0)
    {
        lineItemIndices[0]++;
        lineItemIndices[1]++;
        lineItemIndices[2]++;
    }

    for (uint8_t index = 0; index < 3; index++)
    {
        if (lineItemIndices[index] >= lookupTable.size())
        {
            lineItemIndices[index] = -1;
        }
    }

    FillCurrentResult(lineItemIndices, selectedIndex, nrOfItems, lookupTable);
}

void Renderer::FillCurrentResult(
    const std::array<int16_t, NR_OF_ITEM_LINES>& lineItemIndices,
    int16_t selectedItemIndex,
    uint16_t nrOfItems,
    const std::vector<std::string_view>& lookupTable)
{
    for (uint8_t lineIndex = 0; lineIndex < NR_OF_ITEM_LINES; lineIndex++)
    {
        _iterationLines[lineIndex] =
        {
            CalculateSymbol(lineIndex, lineItemIndices[lineIndex],
                            selectedItemIndex, nrOfItems),
            lineItemIndices[lineIndex]
        };

        const int16_t itemIndex = _iterationLines[lineIndex].index;

        if (itemIndex >= 0 && itemIndex < nrOfItems)
        {
            _currentResult[lineIndex + 1] =
                std::string(1, _iterationLines[lineIndex].symbol) + " " +
                std::string(lookupTable[itemIndex]);
        }
    }
}

char Renderer::CalculateSymbol(
    uint8_t lineIndex,
    int16_t itemIndex,
    int16_t selectedItemIndex,
    uint16_t nrOfItems) const
{
    if (itemIndex == selectedItemIndex)
    {
        return '>';
    }
    else if (lineIndex == 0)
    {
        if (itemIndex == 0) return '-';
        return '^';
    }
    else if (lineIndex == 1)
    {
        if (itemIndex == nrOfItems - 1)
        {
            return '_';
        }
    }
    else if (lineIndex == 2)
    {
        if (itemIndex == nrOfItems - 1)
        {
            return '_';
        }
        return 'v';
    }

    return ' ';
};

std::string Renderer::GetHighscoreName(
    uint8_t index) const
{
    // Implement your logic to get the highscore name based on the index
    const char* name;
    switch (index)
    {
    case 0: name = "PL1"; break;
    case 1: name = "PL2"; break;
    case 2: name = "PL3"; break;
    case 3: name = "PL4"; break;
    default: name = "UNKNOWN"; break;
    }

    return name;
}

uint32_t Renderer::GetHighscoreValue(
    uint8_t index) const
{
    // Implement your logic to get the highscore value based on the index
    return 100'000 - 1000 * (index + 1);
}

bool Renderer::IsDirty() const
{
    return (_previousResult != _currentResult);
}

std::array<std::string, Renderer::NR_OF_LINES> Renderer::GetCurrentResult() const
{
    return _currentResult;
}

std::string_view Renderer::GetCurrentApplicationName() const
{
    return _applicationsManager.GetApplications()[_states.GetSelectedAppIndex()]->GetName();
}

std::vector<std::string_view> Renderer::FilterTagsLookupTable(
    const std::vector<std::string_view>& lookupTable) const
{
    std::vector<std::string_view> filteredLookupTable;
    for (auto& tag : _states.GetSelectableTags())
    {
        filteredLookupTable.push_back(lookupTable[static_cast<uint16_t>(tag)]);
    }

    return filteredLookupTable;
}

std::vector<std::string_view> Renderer::FilterAppModesLookupTable(
    const std::vector<std::string_view>& lookupTable) const
{
    std::vector<std::string_view> filteredLookupTable;
    States::EAppMode selectedAppMode = _states.GetSelectedAppMode();

    for (uint16_t appModeIndex = 0; appModeIndex < static_cast<uint16_t>(States::EAppMode::Last); appModeIndex++)
    {
        bool add = false;

        switch (selectedAppMode)
        {
        case States::EAppMode::Idle:
            add = ((appModeIndex != static_cast<uint16_t>(States::EAppMode::Running)) &&
                   (appModeIndex != static_cast<uint16_t>(States::EAppMode::Paused)) &&
                   (appModeIndex != static_cast<uint16_t>(States::EAppMode::Quit)));
            break;

        case States::EAppMode::Running:
            // Do not add any mode.
            break;

        case States::EAppMode::Paused:
            add = ((appModeIndex == static_cast<uint16_t>(States::EAppMode::Paused)) ||
                   (appModeIndex == static_cast<uint16_t>(States::EAppMode::Quit)));
            break;

        case States::EAppMode::Quit:
            add = ((appModeIndex == static_cast<uint16_t>(States::EAppMode::Paused)) ||
                   (appModeIndex == static_cast<uint16_t>(States::EAppMode::Quit)));
            break;

        default: // All others, only keep Idle
            add = ((appModeIndex != static_cast<uint16_t>(States::EAppMode::Running)) &&
                   (appModeIndex != static_cast<uint16_t>(States::EAppMode::Paused)) &&
                   (appModeIndex != static_cast<uint16_t>(States::EAppMode::Quit)));
            break;
        }

        if (add)
        {
            filteredLookupTable.push_back(lookupTable[appModeIndex]);
        }
    }

    return filteredLookupTable;
}
