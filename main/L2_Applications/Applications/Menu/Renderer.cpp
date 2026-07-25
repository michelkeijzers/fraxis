#include "Renderer.hpp"
#include "../../../L4_DomainModels/Lcd2004/Lcd2004.hpp"
#include "../../../L9_Utils/String/StringUtils.hpp"
#include "../../../L9_Utils/Assert/Assert.hpp"
#include <cstdio>
#include <cstdlib>

Renderer::Renderer(const States& states) 
    : _states(states), _previousResult({}), _currentResult({ } )
{  
}

Renderer::Result Renderer::Render() 
{
    _previousResult = _currentResult;
    _currentResult.line1 = "";
    _currentResult.line2 = "";

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
    
    _currentResult.line1 = StringUtils::Center(_currentResult.line1, Lcd2004::LINE_WIDTH);
    _currentResult.line2 = StringUtils::Center(_currentResult.line2, Lcd2004::LINE_WIDTH);

    Assert::Equals(_currentResult.line1.size(), Lcd2004::LINE_WIDTH, "_currentResult.line1");
    Assert::Equals(_currentResult.line2.size(), Lcd2004::LINE_WIDTH, "_currentResult.line2");
    return _currentResult;
}

void Renderer::RenderS000()
{
    _currentResult.line1 = "Welcome to";
    _currentResult.line2 = "FRAXIS v0.0.1";
}

void Renderer::RenderS010()
{
    _currentResult.line1 = "Select App Type";
    _currentResult.line2 = GetAppTypeString(_states.GetSelectedAppTypeIndex());
}

void Renderer::RenderS020()
{
    _currentResult.line1 = "Select View Mode";
    _currentResult.line2 = GetViewModeString(_states.GetSelectedViewModeIndex());
}

void Renderer::RenderS021()
{
    _currentResult.line1 = "Select Tag";
    std::string name;
    switch (_states.GetSelectedAppTypeIndex()) 
    {
    case Application::EType::Game:
        name = GetGameTagString(static_cast<States::EGameTag>(_states.GetSelectedTagIndex()));
        break;
    case Application::EType::Demo:
        name = GetDemoTagString(static_cast<States::EDemoTag>(_states.GetSelectedTagIndex()));
        break;
    case Application::EType::Utility:
        name = GetUtilityTagString(static_cast<States::EUtilityTag>(_states.GetSelectedTagIndex()));
        break;
    case Application::EType::Tool:
        name = GetSetupAppTagString(static_cast<States::ESetupAppTag>(_states.GetSelectedTagIndex()));
        break;
    default:
        name = "UNKNOWN";
        break;
    }
    _currentResult.line2 = name;
}

void Renderer::RenderS030()
{
    _currentResult.line1 = "Select ";

    const char* appType;
    switch (_states.GetSelectedAppTypeIndex())
    {
    case Application::EType::Game:     appType = "GAME";      break;
    case Application::EType::Demo:     appType = "DEMO";      break;
    case Application::EType::Utility:  appType = "UTILITY";   break;
    case Application::EType::Tool:     appType = "TOOL";      break;
    default:                           appType = "UNKNOWN";   break;
    }

    _currentResult.line1 = appType;
    _currentResult.line2 = GetAppNameString(_states.GetSelectedAppNameIndex());
}

void Renderer::RenderS040()
{
    _currentResult.line1 = GetAppNameString(_states.GetSelectedAppNameIndex());
    _currentResult.line2 = "START";
}

void Renderer::RenderS041()
{
    _currentResult.line1 = GetAppNameString(_states.GetSelectedAppNameIndex());
    _currentResult.line2 = "RUNNING";
}

void Renderer::RenderS043()
{
    _currentResult.line1 = GetAppNameString(_states.GetSelectedAppNameIndex());
    _currentResult.line2 = "(PAUSED) RESUME";
}

void Renderer::RenderS044()
{
    _currentResult.line1 = GetAppNameString(_states.GetSelectedAppNameIndex());
    _currentResult.line2 = "QUIT";
}

void Renderer::RenderS045()
{
    _currentResult.line1 = GetAppNameString(_states.GetSelectedAppNameIndex());
    _currentResult.line2 = "CONFIRM?";
}

void Renderer::RenderS050()
{
    _currentResult.line1 = GetAppNameString(_states.GetSelectedAppNameIndex());
    _currentResult.line2 = "SETTINGS";
}

void Renderer::RenderS060()
{
    _currentResult.line1 = GetAppNameString(_states.GetSelectedAppNameIndex());
    _currentResult.line2 = "HIGHSCORES";
}

void Renderer::RenderS061()
{
    _currentResult.line1 = GetAppNameString(_states.GetSelectedAppNameIndex());

    int displayIndex = _states.GetSelectedHighscoreIndex() + 1;
    std::string name = GetHighscoreName(_states.GetSelectedHighscoreIndex());
    int score = GetHighscoreValue(_states.GetSelectedHighscoreIndex());
    // Format: " 1 MICHEL 123456"
    snprintf(_currentResult.line2.data(), Lcd2004::LINE_WIDTH, "%2d %-6.6s %6d", displayIndex, name.data(), score);
}

void Renderer::RenderS070()
{
    _currentResult.line1 = GetAppNameString(_states.GetSelectedAppNameIndex());
    _currentResult.line2 = "RESET HIGHSCORES";
}

void Renderer::RenderS071()
{
    _currentResult.line1 = GetAppNameString(_states.GetSelectedAppNameIndex());
    _currentResult.line2 = "CONFIRM RESET?";
}

void Renderer::RenderS072()
{
    _currentResult.line1 = GetAppNameString(_states.GetSelectedAppNameIndex());
    _currentResult.line2 = "HIGHSCORES RESET";
}

void Renderer::RenderS080()
{
    _currentResult.line1 = GetAppNameString(_states.GetSelectedAppNameIndex());
    _currentResult.line2 = "PLAYER SETUP";
}

void Renderer::RenderS090()
{
    _currentResult.line1 = GetAppNameString(_states.GetSelectedAppNameIndex());
    if (_states.GetSwapFavoriteStatus()) //TODO: Real implementation: Swap before, check state
    {
        _currentResult.line2 = "UNFAVORITE";
    }
    else
    {
        _currentResult.line2 = "SET AS FAVORITE";
    }
}

void Renderer::RenderDefault()
{
    _currentResult.line1 = "NOT IMPLEMENTED";
    _currentResult.line2 = "YET";
}

std::string Renderer::GetAppTypeString(Application::EType appType) const
{
    std::string name;
    switch (appType) 
    {
        case Application::EType::Game:      name = "Game";      break;
        case Application::EType::Demo:      name = "Demo";      break;
        case Application::EType::Utility:   name = "Utility";   break;
        case Application::EType::Tool:      name = "Tool";      break;
        default:                            name = "Unknown";   break;
    }
    return name;
}

std::string Renderer::GetViewModeString(States::EViewMode viewMode) const
{
    std::string name;
    switch (viewMode) {
    case States::EViewMode::Recent: name = "RECENT"; break;
    case States::EViewMode::MostUsed: name = "MOST USED"; break;
    case States::EViewMode::Favorites: name = "FAVORITES"; break;
    case States::EViewMode::Alphabetic: name = "ALPHABETIC"; break;
    case States::EViewMode::Tag: name = "TAG"; break;
    case States::EViewMode::New: name = "NEW"; break;
    case States::EViewMode::Random: name = "RANDOM"; break;
    default: name = "UNKNOWN"; break;
    }
	
    return name;
}

std::string Renderer::GetGameTagString(States::EGameTag tag) const
{
    std::string name;
    switch (tag) {
        case States::EGameTag::Arcade: name = "ARCADE"; break;
        case States::EGameTag::Audio: name = "AUDIO"; break;
        case States::EGameTag::Continuous: name = "CONTINUOUS"; break;
        case States::EGameTag::Horizontal: name = "HORIZONTAL"; break;
        case States::EGameTag::Microphone: name = "MICROPHONE"; break;
        case States::EGameTag::Puzzle: name = "PUZZLE"; break;
        case States::EGameTag::Racing: name = "RACING"; break;
        case States::EGameTag::Shooter: name = "SHOOTER"; break;
        case States::EGameTag::SinglePlayer: name = "SINGLE PLAYER"; break;
        case States::EGameTag::TurnBased: name = "TURN BASED"; break;
        case States::EGameTag::TwoPlayers: name = "TWO PLAYER"; break;
        case States::EGameTag::Vertical: name = "VERTICAL"; break;
        default: name = "UNKNOWN"; break;
    }

	return name;
}

std::string Renderer::GetDemoTagString(States::EDemoTag tag) const
{
    std::string name;
    switch (tag) {
        case States::EDemoTag::Audio: name = "AUDIO"; break;
        case States::EDemoTag::Interactive: name = "INTERACTIVE"; break;
        case States::EDemoTag::Static: name = "STATIC"; break;
        default: name = "UNKNOWN"; break;
    }

	return name;
}

std::string Renderer::GetUtilityTagString(States::EUtilityTag tag) const
{
    std::string name;
    switch (tag) {
        case States::EUtilityTag::Audio: name = "AUDIO"; break;
        case States::EUtilityTag::Clock: name = "CLOCK"; break;
        case States::EUtilityTag::LedStrips: name = "LED STRIPS"; break;
        case States::EUtilityTag::Microphone: name = "MICROPHONE"; break;
        case States::EUtilityTag::Speaker: name = "SPEAKER"; break;
        default: name = "UNKNOWN"; break;
    }

	return name;
}

std::string Renderer::GetSetupAppTagString(States::ESetupAppTag tag) const
{
    std::string name;
    switch (tag) {
        case States::ESetupAppTag::Audio: name = "AUDIO"; break;
        case States::ESetupAppTag::Clock: name = "CLOCK"; break;
        case States::ESetupAppTag::Diagnostics: name = "DIAGNOSTICS"; break;
        case States::ESetupAppTag::Displays: name = "DISPLAYS"; break;
        case States::ESetupAppTag::HardwareTest: name = "HARDWARE TEST"; break;
        case States::ESetupAppTag::Joysticks: name = "JOYSTICKS"; break;
        case States::ESetupAppTag::Leds: name = "LEDS"; break;
        case States::ESetupAppTag::LedStrips: name = "LED STRIPS"; break;
        case States::ESetupAppTag::Microphone: name = "MICROPHONE"; break;
        case States::ESetupAppTag::Speaker: name = "SPEAKER"; break;
        case States::ESetupAppTag::SystemButton: name = "SYSTEM BUTTON"; break;
        case States::ESetupAppTag::Info: name = "INFO"; break;
        default: name = "UNKNOWN"; break;
    }

	return name;
}

std::string Renderer::GetAppNameString(States::EAppName appName) const
{
    std::string name;
    switch (appName) 
    {
    case States::EAppName::OneDPong: name = "1D PONG"; break;
    case States::EAppName::LineRacer: name = "LINE RACER"; break;
    default: name = "UNKNOWN"; break;
    }
	
    return name;
}

bool Renderer::IsAppFavorite(States::EAppName appName) const
{
    // Implement your logic to check if the app is a favorite
    // For demonstration, let's assume 1D PONG is a favorite
    return appName == States::EAppName::OneDPong;
}

std::string Renderer::GetHighscoreName(uint8_t index) const
{
    // Implement your logic to get the highscore name based on the index
    const char* name;
    switch (index) {
        case 0: name = "PL1"; break;
        case 1: name = "PL2"; break;
        case 2: name = "PL3"; break;
        case 3: name = "PL4"; break;
        default: name = "UNKNOWN"; break;
    }

	return name;
}

uint32_t Renderer::GetHighscoreValue(uint8_t index) const
{
    // Implement your logic to get the highscore value based on the index
    return 100000 - 1000 * (index + 1);
}

bool Renderer::IsDirty() const
{
    return ((_previousResult.line1 != _currentResult.line1) ||
            (_previousResult.line2 != _currentResult.line2));
}

Renderer::Result Renderer::GetCurrentResult() const
{
    return _currentResult;
}
