#include "Renderer.hpp"
#include <cstdio>
#include <cstdlib>

#if !defined(_WIN32) && !defined(_WIN64)
    #include <cstring>
#endif

#if defined(_WIN32) || defined(_WIN64)
    #include <iostream>
    using std::cout;

#endif

#if defined(_WIN32) || defined(_WIN64)
    #define SAFE_STRNCPY(dst, src, size) strncpy_s((dst).data(), (size), (src), _TRUNCATE)
#else
    #define SAFE_STRNCPY(dst, src, size) do { \
        std::strncpy((dst).data(), (src), (size)); \
        (dst).data()[(size) - 1] = '\0'; \
    } while(0)
#endif

Renderer::Renderer(const States& states) 
    : _states(states), _previousResult({}), _currentResult({ } )
{  
}

Renderer::Result Renderer::Render() 
{
    _previousResult = _currentResult;
    _currentResult.line1.fill(' ');
    _currentResult.line2.fill(' ');

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
    CenterAlign(_currentResult);
    return _currentResult;
}

void Renderer::RenderS000()
{
    const char* line1 = "Welcome to";
    const char* line2 = "FRAXIS v0.0.1";
    SAFE_STRNCPY(_currentResult.line1, line1, _currentResult.line1.size());
    _currentResult.line1[_currentResult.line1.size() - 1] = '\0';
    SAFE_STRNCPY(_currentResult.line2, line2, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void Renderer::RenderS010()
{
    const char* line1 = "Select App Type";
    SAFE_STRNCPY(_currentResult.line1, line1, _currentResult.line1.size());
    _currentResult.line1[_currentResult.line1.size() - 1] = '\0';
    GetAppTypeString(_states.GetSelectedAppTypeIndex(), _currentResult.line2);
}

void Renderer::RenderS020()
{
    const char* line1 = "Select View Mode";
    SAFE_STRNCPY(_currentResult.line1, line1, _currentResult.line1.size());
    _currentResult.line1[_currentResult.line1.size() - 1] = '\0';
    GetViewModeString(_states.GetSelectedViewModeIndex(), _currentResult.line2);
}

void Renderer::RenderS021()
{
    const char* line1 = "Select Tag";
    SAFE_STRNCPY(_currentResult.line1, line1, _currentResult.line1.size());
    _currentResult.line1[_currentResult.line1.size() - 1] = '\0';
    switch (_states.GetSelectedAppTypeIndex()) {
    case Application::EType::Game:
        GetGameTagString(static_cast<States::EGameTag>(_states.GetSelectedTagIndex()), _currentResult.line2);
        break;
    case Application::EType::Demo:
        GetDemoTagString(static_cast<States::EDemoTag>(_states.GetSelectedTagIndex()), _currentResult.line2);
        break;
    case Application::EType::Utility:
        GetUtilityTagString(static_cast<States::EUtilityTag>(_states.GetSelectedTagIndex()), _currentResult.line2);
        break;
    case Application::EType::Tool:
        GetSetupAppTagString(static_cast<States::ESetupAppTag>(_states.GetSelectedTagIndex()), _currentResult.line2);
        break;
    default:
        const char* line2 = "UNKNOWN";
        SAFE_STRNCPY(_currentResult.line2, line2, _currentResult.line2.size());
        break;
    }
}

void Renderer::RenderS030()
{
    const char* select = "Select ";
    SAFE_STRNCPY(_currentResult.line1, select, _currentResult.line1.size());
    _currentResult.line1[_currentResult.line1.size() - 1] = '\0';

    const char* appType;
    switch (_states.GetSelectedAppTypeIndex())
    {
    case Application::EType::Game:     appType = "GAME";      break;
    case Application::EType::Demo:     appType = "DEMO";      break;
    case Application::EType::Utility:  appType = "UTILITY";   break;
    case Application::EType::Tool:     appType = "TOOL";      break;
    default:                           appType = "UNKNOWN";   break;
    }

    SAFE_STRNCPY(_currentResult.line1, appType, _currentResult.line1.size());
    _currentResult.line1[_currentResult.line1.size() - 1] = '\0';
    GetAppNameString(_states.GetSelectedAppNameIndex(), _currentResult.line2);
}

void Renderer::RenderS040()
{
    GetAppNameString(_states.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* start = "START";
    SAFE_STRNCPY(_currentResult.line2, start, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void Renderer::RenderS041()
{
    GetAppNameString(_states.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* running = "RUNNING";
    SAFE_STRNCPY(_currentResult.line2, running, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void Renderer::RenderS043()
{
    GetAppNameString(_states.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* paused = "(PAUSED) RESUME";
    SAFE_STRNCPY(_currentResult.line2, paused, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void Renderer::RenderS044()
{
    GetAppNameString(_states.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* quit = "QUIT";
    SAFE_STRNCPY(_currentResult.line2, quit, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void Renderer::RenderS045()
{
    GetAppNameString(_states.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* confirm = "CONFIRM?";
    SAFE_STRNCPY(_currentResult.line2, confirm, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void Renderer::RenderS050()
{
    GetAppNameString(_states.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* settings = "SETTINGS";
    SAFE_STRNCPY(_currentResult.line2, settings, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void Renderer::RenderS060()
{
    GetAppNameString(_states.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* highscores = "HIGHSCORES";
    SAFE_STRNCPY(_currentResult.line2, highscores, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void Renderer::RenderS061()
{
    GetAppNameString(_states.GetSelectedAppNameIndex(), _currentResult.line1);

    int displayIndex = _states.GetSelectedHighscoreIndex() + 1;
    std::array<char, 7> name;
    GetHighscoreName(_states.GetSelectedHighscoreIndex(), name);
    int score = GetHighscoreValue(_states.GetSelectedHighscoreIndex());
    // Format: " 1 MICHEL 123456"
    int written = snprintf(_currentResult.line2.data(), 16 + 1, "%2d %-6.6s %6d", displayIndex, name.data(), score);
    if (written != 16)
    {
        exit(1);
    }
}

void Renderer::RenderS070()
{
    GetAppNameString(_states.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* reset = "RESET HIGHSCORES";
    SAFE_STRNCPY(_currentResult.line2, reset, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void Renderer::RenderS071()
{
    GetAppNameString(_states.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* confirm = "CONFIRM RESET?";
    SAFE_STRNCPY(_currentResult.line2, confirm, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void Renderer::RenderS072()
{

    GetAppNameString(_states.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* resetDone = "HIGHSCORES RESET";
    SAFE_STRNCPY(_currentResult.line2, resetDone, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void Renderer::RenderS080()
{
    GetAppNameString(_states.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* playerSetup = "PLAYER SETUP";
    SAFE_STRNCPY(_currentResult.line2, playerSetup, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void Renderer::RenderS090()
{
    GetAppNameString(_states.GetSelectedAppNameIndex(), _currentResult.line1);
    if (_states.GetSwapFavoriteStatus()) //TODO: Real implementation: Swap before, check state
    {
        const char* unfavorite = "UNFAVORITE";
        SAFE_STRNCPY(_currentResult.line2, unfavorite, _currentResult.line2.size());
        _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
    }
    else
    {
        const char* setAsFavorite = "SET AS FAVORITE";
        SAFE_STRNCPY(_currentResult.line2, setAsFavorite, _currentResult.line2.size());
        _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
    }
}

void Renderer::RenderDefault()
{
    const char* notImplemented = "NOT IMPLEMENTED";
    SAFE_STRNCPY(_currentResult.line1, notImplemented, _currentResult.line1.size());
    _currentResult.line1[_currentResult.line1.size() - 1] = '\0';
    const char* yet = "YET";
    SAFE_STRNCPY(_currentResult.line2, yet, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void Renderer::GetAppTypeString(Application::EType appType, std::array<char, 17>& outBuffer) const
{
    const char* name;
    switch (appType) 
    {
        case Application::EType::Game:      name = "Game";      break;
        case Application::EType::Demo:      name = "Demo";      break;
        case Application::EType::Utility:   name = "Utility";   break;
        case Application::EType::Tool:      name = "Tool";      break;
        default:                            name = "Unknown";   break;
    }
	 SAFE_STRNCPY(outBuffer, name, outBuffer.size());
    outBuffer[outBuffer.size() - 1] = '\0';
}

void Renderer::GetViewModeString(States::EViewMode viewMode, std::array<char, 17>& outBuffer) const
{
    const char* name;
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
	
    SAFE_STRNCPY(outBuffer, name, outBuffer.size());
    outBuffer[outBuffer.size() - 1] = '\0';
}

void Renderer::GetGameTagString(States::EGameTag tag, std::array<char, 17>& outBuffer) const
{
    const char* name;
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

	SAFE_STRNCPY(outBuffer, name, outBuffer.size());
    outBuffer[outBuffer.size() - 1] = '\0';
}

void Renderer::GetDemoTagString(States::EDemoTag tag, std::array<char, 17>& outBuffer) const
{
    const char* name;
    switch (tag) {
        case States::EDemoTag::Audio: name = "AUDIO"; break;
        case States::EDemoTag::Interactive: name = "INTERACTIVE"; break;
        case States::EDemoTag::Static: name = "STATIC"; break;
        default: name = "UNKNOWN"; break;
    }

	SAFE_STRNCPY(outBuffer, name, outBuffer.size());
    outBuffer[outBuffer.size() - 1] = '\0';
}

void Renderer::GetUtilityTagString(States::EUtilityTag tag, std::array<char, 17>& outBuffer) const
{
    const char* name;
    switch (tag) {
        case States::EUtilityTag::Audio: name = "AUDIO"; break;
        case States::EUtilityTag::Clock: name = "CLOCK"; break;
        case States::EUtilityTag::LedStrips: name = "LED STRIPS"; break;
        case States::EUtilityTag::Microphone: name = "MICROPHONE"; break;
        case States::EUtilityTag::Speaker: name = "SPEAKER"; break;
        default: name = "UNKNOWN"; break;
    }

	SAFE_STRNCPY(outBuffer, name, outBuffer.size());
    outBuffer[outBuffer.size() - 1] = '\0';
}


void Renderer::GetSetupAppTagString(States::ESetupAppTag tag, std::array<char, 17>& outBuffer) const
{
    const char* name;
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

	SAFE_STRNCPY(outBuffer, name, outBuffer.size());
    outBuffer[outBuffer.size() - 1] = '\0';
}

void Renderer::GetAppNameString(States::EAppName appName, std::array<char, 17>& outBuffer) const
{
    const char* name;
    switch (appName) 
    {
    case States::EAppName::OneDPong: name = "1D PONG"; break;
    case States::EAppName::LineRacer: name = "LINE RACER"; break;
    default: name = "UNKNOWN"; break;
    }
	
    SAFE_STRNCPY(outBuffer, name, outBuffer.size());
    outBuffer[outBuffer.size() - 1] = '\0';
}

bool Renderer::IsAppFavorite(States::EAppName appName) const
{
    // Implement your logic to check if the app is a favorite
    // For demonstration, let's assume 1D PONG is a favorite
    return appName == States::EAppName::OneDPong;
}

void Renderer::GetHighscoreName(uint8_t index, std::array<char, 7>& outBuffer) const
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

	SAFE_STRNCPY(outBuffer, name, outBuffer.size());
    outBuffer[outBuffer.size() - 1] = '\0';
}

uint32_t Renderer::GetHighscoreValue(uint8_t index) const
{
    // Implement your logic to get the highscore value based on the index
    return 100000 - 1000 * (index + 1);
}

void Renderer::CenterAlign(Result& result)
{
	auto center = [](std::array<char, 17>& line)
    {
		const size_t visible = 16;

		// Real text length
		size_t len = std::strlen(line.data());
        if (len == 0 || len >= visible)
        {
            return;
        }

		size_t leftPadding = (visible - len) / 2;

		// Shift text right inside the visible region
		std::copy_backward(line.begin(), line.begin() + len, line.begin() + leftPadding + len);

		// Fill left side
		std::fill_n(line.begin(), leftPadding, ' ');

		// Fill right side
		size_t rightPaddingStart = leftPadding + len;
		std::fill_n(line.begin() + rightPaddingStart, visible - rightPaddingStart, ' ');

		line[visible] = '\0';
	};

	center(result.line1);
	center(result.line2);
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
