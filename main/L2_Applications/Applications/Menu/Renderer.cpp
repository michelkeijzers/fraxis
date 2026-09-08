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
    case States::EState::S040_AppStart:                  RenderS040(); break;
    case States::EState::S041_AppRunning:                RenderS041(); break;
    case States::EState::S043_AppPaused:                 RenderS043(); break;
    case States::EState::S044_AppQuit:                   RenderS044(); break;
    case States::EState::S045_AppConfirmQuit:            RenderS045(); break;
    case States::EState::S050_AppSettings:               RenderS050(); break;
    case States::EState::S060_Highscores:                RenderS060(); break;
    case States::EState::S061_HighscoreDetails:          RenderS061(); break;
    case States::EState::S070_ResetHighscores:           RenderS070(); break;
    case States::EState::S071_ConfirmHighscoresReset:    RenderS071(); break;
    case States::EState::S072_HighscoresResetDone:       RenderS072(); break;
    case States::EState::S080_PlayerSetup:               RenderS080(); break;
    case States::EState::S090_SetAsFavorite:             RenderS090(); break;
    default:                                  RenderDefault(); break;
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

    std::vector<std::string_view> filteredLookupTable = FilterLookupTable(lookupTable);
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
    _currentResult[1] = "START";
}

void Renderer::RenderS041()
{
    _currentResult[0] = GetCurrentApplicationName();
    _currentResult[1] = "RUNNING";
}

void Renderer::RenderS043()
{
    _currentResult[0] = GetCurrentApplicationName();
    _currentResult[1] = "(PAUSED) RESUME";
}

void Renderer::RenderS044()
{
    _currentResult[0] = GetCurrentApplicationName();
    _currentResult[1] = "QUIT";
}

void Renderer::RenderS045()
{
    _currentResult[0] = GetCurrentApplicationName();
    _currentResult[1] = "CONFIRM?";
}

void Renderer::RenderS050()
{
    _currentResult[0] = GetCurrentApplicationName();
    _currentResult[1] = "SETTINGS";
}

void Renderer::RenderS060()
{
    _currentResult[0] = GetCurrentApplicationName();
    _currentResult[1] = "HIGHSCORES";
}

void Renderer::RenderS061()
{
    _currentResult[0] = GetCurrentApplicationName();

    int displayIndex = _states.GetSelectedHighscoreIndex() + 1;
    std::string name = GetHighscoreName(_states.GetSelectedHighscoreIndex());
    int score = GetHighscoreValue(_states.GetSelectedHighscoreIndex());
    // Format: " 1 MICHEL 123456"
    snprintf(_currentResult[1].data(), Lcd2004::LINE_WIDTH, "%2d %-6.6s %6d", displayIndex, name.data(), score);
}

void Renderer::RenderS070()
{
    _currentResult[0] = GetCurrentApplicationName();
    _currentResult[1] = "RESET HIGHSCORES";
}

void Renderer::RenderS071()
{
    _currentResult[0] = GetCurrentApplicationName();
    _currentResult[1] = "CONFIRM RESET?";
}

void Renderer::RenderS072()
{
    _currentResult[0] = GetCurrentApplicationName();
    _currentResult[1] = "HIGHSCORES RESET";
}

void Renderer::RenderS080()
{
    _currentResult[0] = GetCurrentApplicationName();
    _currentResult[1] = "PLAYER SETUP";
}

/// @todo: Later: Real implementation: swap before, check state.
void Renderer::RenderS090()
{
    _currentResult[0] = GetCurrentApplicationName();
    if (_states.GetSwapFavoriteStatus())
    {
        _currentResult[1] = "UNFAVORITE";
    }
    else
    {
        _currentResult[1] = "SET AS FAVORITE";
    }
}

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

    if (selectedIndex == 0) {
        lineItemIndices[0] = 0;
        lineItemIndices[1] = (nrOfItems > 1 ? 1 : -1);
        lineItemIndices[2] = (nrOfItems > 2 ? 2 : lineItemIndices[1]);
    }
    else if (selectedIndex == nrOfItems - 1) {
        lineItemIndices[2] = nrOfItems - 1;
        lineItemIndices[1] = (nrOfItems >= 2 ? nrOfItems - 2 : lineItemIndices[2]);
        lineItemIndices[0] = (nrOfItems >= 3 ? nrOfItems - 3 : lineItemIndices[1]);
    }
    else {
        lineItemIndices[0] = selectedIndex - 1;
        lineItemIndices[1] = selectedIndex;
        lineItemIndices[2] = selectedIndex + 1;
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

    if (lineIndex == 0)
    {
        if (itemIndex == 0) return '-';
        return '^';
    }

    if (lineIndex == 2)
    {
        if (itemIndex == nrOfItems - 1) return '_';
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

std::vector<std::string_view> Renderer::FilterLookupTable(
    const std::vector<std::string_view>& lookupTable) const
{
    std::vector<std::string_view> filteredLookupTable;
    for (auto& tag : _states.GetSelectableTags())
    {
        filteredLookupTable.push_back(lookupTable[static_cast<uint16_t>(tag)]);
    }
    
    return filteredLookupTable;
}
