#include "StatesRenderer.hpp"
#include "Renderer.hpp"
#include "../../M20_Applications/Applications/ApplicationsInfo.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M90_Utilities/Array/ArrayUtilities.hpp"
#include <cstdint>
#include <vector>

StatesRenderer::StatesRenderer(
    Renderer& renderer,
    States& states) 
:
    _renderer(renderer),
    _states(states)
{
}

void StatesRenderer::RenderS000()
{
    _renderer.SetCurrentResultLine(0, "--------------------");
    _renderer.SetCurrentResultLine(1, "Welcome to");
    _renderer.SetCurrentResultLine(2, "FRAXIS v0.1");
    _renderer.SetCurrentResultLine(3, "--------------------");
}

void StatesRenderer::RenderS010()
{
    _renderer.SetCurrentResultLine(0, "Select Type");
    auto applicationTypeIndex = static_cast<uint8_t>(
        _states.GetApplicationSelectionStates().GetSelectedApplicationType());
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
    _renderer.RenderItems(applicationTypesToStrings, applicationTypeIndex);
}

void StatesRenderer::RenderS020()
{
    _renderer.SetCurrentResultLine(0, "Select View Mode");
    auto viewModeIndex = static_cast<uint8_t>(
        _states.GetApplicationSelectionStates().GetSelectedViewMode());
    const std::array<std::string_view, ApplicationSelectionStates::NR_OF_VIEW_MODES> 
        viewModesToStrings = 
    {
        "Recent", 
        "Most Used", 
        "Favorites", 
        "Alphabetic", 
        "Tag", 
        "New", 
        "Random"
    };
    _renderer.RenderItems(viewModesToStrings, viewModeIndex);
}

void StatesRenderer::RenderS021()
{
    _renderer.SetCurrentResultLine(0, "Select Tag");
    auto selectedTagIndex = _states.GetApplicationSelectionStates().GetSelectedTagIndex();

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
    for (auto tag : _states.GetApplicationSelectionStates().GetSelectableTags())
    {
        stringFilteredTags.push_back(tagToStrings[static_cast<uint16_t>(tag)]);
    }

    _renderer.RenderItems(stringFilteredTags, selectedTagIndex);
}

void StatesRenderer::RenderS030()
{
    _renderer.SetCurrentResultLine(0, "Select ");

    std::string applicationType = "";
    switch (_states.GetApplicationSelectionStates().GetSelectedApplicationType())
    {
    case Application::EType::Game:     applicationType = "Game";      break;
    case Application::EType::Demo:     applicationType = "Demo";      break;
    case Application::EType::Tool:     applicationType = "Tool";      break;
    case Application::EType::Utility:  applicationType = "Utility";   break;
    default:                           
        Assert::Fail(Types::ETaskId::ApplicationsTask, "Unknown application type index");
        break;
    }

    _renderer.AppendToCurrentResultLine(0, applicationType);

    std::vector<std::string_view> applicationNames;
    for (uint16_t selectableApplicationIndex :
        _states.GetApplicationSelectionStates().GetSelectableApplicationIndices())
    {
        applicationNames.push_back(ApplicationsInfo::GetNameByIndex(selectableApplicationIndex));
    }
    _states.GetApplicationSelectionStates().SortSelectableApplications();
    Assert::Equals(Types::ETaskId::ApplicationsTask,
        applicationNames.size(), 
        _states.GetApplicationSelectionStates().GetSelectableApplicationIndices().size(),
        "S030 application names");
    _renderer.RenderItems(
        applicationNames, _states.GetApplicationSelectionStates().GetSelectedApplicationIndex());
}

void StatesRenderer::RenderS040()
{
    _renderer.SetCurrentResultLine(0, _renderer.GetCurrentApplicationName());

    std::array<std::string_view, ApplicationModesStates::NR_OF_APPLICATION_MODES> 
        applicationModesToStrings =
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
    auto selectableApplicationModes =
        _states.GetApplicationModesStates().GetSelectableApplicationModes();
    for (auto applicationMode : selectableApplicationModes)
    {
        stringFilteredApplicationModes.push_back(
            applicationModesToStrings[static_cast<uint16_t>(applicationMode)]);
    }

    auto selectedApplicationModeIndex = static_cast<uint8_t>(
        ArrayUtilities::FindFirstIndexOf<ApplicationModesStates::EApplicationMode>(
            selectableApplicationModes, 
            _states.GetApplicationModesStates().GetSelectedApplicationMode()));

    _renderer.RenderItems(stringFilteredApplicationModes, selectedApplicationModeIndex);
}

/// @brief Format: 01234567890123456789
///                > NameOfPl: 12345678
///                v Next    :  9834576
void StatesRenderer::RenderS050()
{
    _renderer.SetCurrentResultLine(0, "Highscores");
    //std::vector<std::string> lookupTable;
    //lookupTable.reserve(Highscores::MAX_NR_OF_ENTRIES);
    //uint16_t applicationIndex = 
        _states.GetApplicationSelectionStates().GetSelectableApplicationIndices()
            [_states.GetApplicationSelectionStates().GetSelectedApplicationIndex()];
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

void StatesRenderer::RenderDefault()
{
    _renderer.SetCurrentResultLine(0, "NOT IMPLEMENTED");
    _renderer.SetCurrentResultLine(1, "YET");
}
