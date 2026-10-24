#include "Renderer.hpp"
#include "../Games/Game.hpp"
#include "../Applications/Application.hpp"
#include "../ApplicationsManager.hpp"
#include "../../M40_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include "../../M90_Utilities/String/StringUtilities.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M90_Utilities/Math/MathUtilities.hpp"
#include "../../M90_Utilities/Array/ArrayUtilities.hpp"
#include <cstdio>
#include <cstdlib>
#include <algorithm>

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
    case States::EState::S010_SelectApplicationType:     RenderS010(); break;
    case States::EState::S020_SelectViewMode:            RenderS020(); break;
    case States::EState::S021_SelectTag:                 RenderS021(); break;
    case States::EState::S030_SelectApplication:         RenderS030(); break;
    case States::EState::S040_ApplicationMode:           RenderS040(); break;
    case States::EState::S050_Highscores:                RenderS050(); break;
    default:                                             RenderDefault(); break;
    }

    for (uint8_t index = 0; index < NR_OF_LINES; index++)
    {
        _currentResult[index] = 
        StringUtilities::LeftAlign(_currentResult[index], Lcd2004::LINE_WIDTH);
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
    _currentResult[0] = "Select Application Type";
    auto applicationTypeIndex = static_cast<uint8_t>(_states.GetSelectedApplicationType());
    const std::array<std::string_view, Application::NR_OF_TYPES> applicationTypesToStrings =
    { 
        "Game", 
        "Demo", 
        "Tool", 
        "Utility" 
    };
    Assert::Equals(
        Types::ETaskId::ApplicationsTask,
        applicationTypesToStrings.size(), 
        static_cast<uint16_t>(Application::EType::Last), "S020 applicationTypesToStrings");
    RenderItems(applicationTypesToStrings, applicationTypeIndex);
}

void Renderer::RenderS020()
{
    _currentResult[0] = "Select View Mode";
    auto viewModeIndex = static_cast<uint8_t>(_states.GetSelectedViewMode());
    const std::array<std::string_view, States::NR_OF_VIEW_MODES> viewModesToStrings = 
    {
        "Recent", 
        "Most Used", 
        "Favorites", 
        "Alphabetic", 
        "Tag", 
        "New", 
        "Random"
    };
    RenderItems(viewModesToStrings, viewModeIndex);
}

void Renderer::RenderS021()
{
    _currentResult[0] = "Select Tag";
    auto selectedTagIndex = _states.GetSelectedTagIndex();

    const std::array<std::string_view, Application::NR_OF_TAGS> tagToStrings =
    {
        "Arcade", 
        "Audio", 
        "Continuous", 
        "Diagnostics", 
        "Displays",
        "DistanceSensors", 
        "HardwareTests", 
        "Horizontal", 
        "Info", 
        "Interactive",
        "Joysticks", 
        "Leds", 
        "LedStrips", 
        "Microphone", 
        "Puzzle",
        "Racing", 
        "ServiceTest", 
        "Shooter", 
        "Speaker", 
        "SinglePlayer", 
        "Static",
        "TimeBased", 
        "TurnBased", 
        "TwoPlayers", 
        "Vertical"
    };

    std::vector<std::string_view> stringFilteredTags;
    for (auto tag : _states.GetSelectableTags())
    {
        stringFilteredTags.push_back(tagToStrings[static_cast<uint16_t>(tag)]);
    }

    RenderItems(stringFilteredTags, selectedTagIndex);
}

void Renderer::RenderS030()
{
    _currentResult[0] = "Select ";

    std::string applicationType = "";
    switch (_states.GetSelectedApplicationType())
    {
    case Application::EType::Game:     applicationType = "Game";      break;
    case Application::EType::Demo:     applicationType = "Demo";      break;
    case Application::EType::Tool:     applicationType = "Tool";      break;
    case Application::EType::Utility:  applicationType = "Utility";   break;
    default:                           
        Assert::Fail(Types::ETaskId::ApplicationsTask, "Unknown application type index");
        break;
    }

    _currentResult[0] += applicationType;

    std::vector<std::string_view> lookupTable;
    for (uint16_t selectableApplicationIndex : _states.GetSelectableApplicationIndices())
    {
        lookupTable.push_back(ApplicationsInfo::GetNameByIndex(selectableApplicationIndex));
    }
    _states.SortSelectableApplications();
    Assert::Equals(Types::ETaskId::ApplicationsTask,
        lookupTable.size(), 
        _states.GetSelectableApplicationIndices().size(),
        "S030 application names");
    RenderItems(lookupTable, _states.GetSelectedApplicationIndex());
}

void Renderer::RenderS040()
{
    _currentResult[0] = GetCurrentApplicationName();

    std::array<std::string_view, States::NR_OF_APPLICATION_MODES> applicationModesToStrings =
    {
        "Start",
        "Running", 
        "Resume",
        "Quit", 
        "Settings", 
        "Highscores", 
        "Make Favorite",
        "Reset Settings", 
        "Reset Highscores", 
        "Reset # Started", 
        "Reset Start Time"
    };

    std::vector<std::string_view> stringFilteredApplicationModes;
    for (auto applicationMode : _states.GetSelectableApplicationModes())
    {
        stringFilteredApplicationModes.push_back(
            applicationModesToStrings[static_cast<uint16_t>(applicationMode)]);
    }

    const auto& selectableApplicationModes = _states.GetSelectableApplicationModes();
    auto selectedApplicationModeIndex = static_cast<uint8_t>(
        ArrayUtilities::FindFirstIndexOf<States::EApplicationMode>(
        selectableApplicationModes, _states.GetSelectedApplicationMode()));

    RenderItems(stringFilteredApplicationModes, selectedApplicationModeIndex);
}

/// @brief Format: 01234567890123456789
///                > NameOfPl: 12345678
///                v Next    :  9834576
void Renderer::RenderS050()
{
    _currentResult[0] = "Highscores";
    //std::vector<std::string> lookupTable;
    //lookupTable.reserve(Highscores::MAX_NR_OF_ENTRIES);
    //uint16_t applicationIndex = 
        _states.GetSelectableApplicationIndices()[_states.GetSelectedApplicationIndex()];
    // const Game* game = static_cast<const Game*>(application);
    //Assert::IsNotNullptr(Types::ETaskId::ApplicationsTask, static_cast<const void*>(game), "game");

    //MA for (uint8_t entryIndex = 0; entryIndex < game->GetHighscores().GetEntries().size(); entryIndex++)
    //{
        //HS: use new application / load highscores
        //Highscore highscore = game->GetHighscores().GetEntries()[entryIndex];
        //std::string line;
        //line.reserve(Lcd2004::LINE_WIDTH);
        //line.append(highscore.GetName()); // TODO: -> pad left
        //line.append(":");
        //line.append(std::to_string(highscore.GetScore())); // TODO: -> pad right
        //lookupTable.push_back(std::move(line));
     //};
    //RenderItems(lookupTable, _states.GetSelectedHighscoreIndex());
}

void Renderer::RenderDefault()
{
    _currentResult[0] = "NOT IMPLEMENTED";
    _currentResult[1] = "YET";
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
    case 0: name = "PM10"; break;
    case 1: name = "PM20"; break;
    case 2: name = "PM30"; break;
    case 3: name = "PM40"; break;
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
    return ApplicationsInfo::GetNameByIndex(_states.GetSelectedApplicationIndex());
}


void Renderer::RenderItems(
    std::span<const std::string_view> stringsToShow,
    uint16_t selectedIndex)
{
    std::array<int16_t, NR_OF_ITEM_LINES> lineItemIndices = {};
    const auto nrOfItems = static_cast<uint16_t>(stringsToShow.size());

    if (selectedIndex == 0)
    {
        lineItemIndices[0] = 0;
        lineItemIndices[1] = 1;
        lineItemIndices[2] = 2;
    }
    else if ((selectedIndex == nrOfItems - 1) && (selectedIndex < stringsToShow.size()))
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
        if (lineItemIndices[index] >= stringsToShow.size())
        {
            lineItemIndices[index] = -1;
        }
    }

    FillCurrentResult(lineItemIndices, selectedIndex, nrOfItems, stringsToShow);
}

void Renderer::FillCurrentResult(
    const std::array<int16_t, NR_OF_ITEM_LINES>& lineItemIndices,
    int16_t selectedItemIndex,
    uint16_t nrOfItems,
    std::span<const std::string_view> stringsToShow)
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
                std::string(stringsToShow[itemIndex]);
        }
    }
}
