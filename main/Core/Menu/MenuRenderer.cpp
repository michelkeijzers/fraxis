#include "MenuRenderer.hpp"
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

MenuRenderer::MenuRenderer(const MenuStates & menuStates) 
    : menuStates(menuStates), _previousResult({}), _currentResult({ } )
{  
}

MenuRenderer::Result MenuRenderer::Render() 
{
    _previousResult = _currentResult;
    _currentResult.line1.fill(' ');
    _currentResult.line2.fill(' ');

    switch (menuStates._currentState)
    {
    case State::S000_WELCOME:                   RenderS000(); break;
    case State::S010_SELECT_APP_TYPE:           RenderS010(); break;
    case State::S020_SELECT_VIEW_MODE:          RenderS020(); break;
    case State::S021_SELECT_TAG:                RenderS021(); break;
    case State::S030_SELECT_APP:                RenderS030(); break;
    case State::S040_APP_START:                 RenderS040(); break;
    case State::S041_APP_RUNNING:               RenderS041(); break;
    case State::S043_APP_PAUSED:                RenderS043(); break;
    case State::S044_APP_QUIT:                  RenderS044(); break;
    case State::S045_APP_CONFIRM_QUIT:          RenderS045(); break;
    case State::S050_APP_SETTINGS:              RenderS050(); break;
    case State::S060_HIGHSCORES:                RenderS060(); break;
    case State::S061_HIGHSCORE_DETAILS:         RenderS061(); break;
    case State::S070_RESET_HIGHSCORES:          RenderS070(); break;
    case State::S071_CONFIRM_HIGHSCORES_RESET:  RenderS071(); break;
    case State::S072_HIGHSCORES_RESET_DONE:     RenderS072(); break;
    case State::S080_PLAYER_SETUP:              RenderS080(); break;
    case State::S090_SET_AS_FAVORITE:           RenderS090(); break;
    default:                                    RenderDefault(); break;
    }
    CenterAlign(_currentResult);
    return _currentResult;
}

void MenuRenderer::RenderS000()
{
    const char* line1 = "Welcome to";
    const char* line2 = "FRAXIS v0.0.1";
    SAFE_STRNCPY(_currentResult.line1, line1, _currentResult.line1.size());
    _currentResult.line1[_currentResult.line1.size() - 1] = '\0';
    SAFE_STRNCPY(_currentResult.line2, line2, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void MenuRenderer::RenderS010()
{
    const char* line1 = "Select App Type";
    SAFE_STRNCPY(_currentResult.line1, line1, _currentResult.line1.size());
    _currentResult.line1[_currentResult.line1.size() - 1] = '\0';
    GetAppTypeString(menuStates.GetSelectedAppTypeIndex(), _currentResult.line2);
}

void MenuRenderer::RenderS020()
{
    const char* line1 = "Select View Mode";
    SAFE_STRNCPY(_currentResult.line1, line1, _currentResult.line1.size());
    _currentResult.line1[_currentResult.line1.size() - 1] = '\0';
    GetViewModeString(menuStates.GetSelectedViewModeIndex(), _currentResult.line2);
}

void MenuRenderer::RenderS021()
{
    const char* line1 = "Select Tag";
    SAFE_STRNCPY(_currentResult.line1, line1, _currentResult.line1.size());
    _currentResult.line1[_currentResult.line1.size() - 1] = '\0';
    switch (menuStates.GetSelectedAppTypeIndex()) {
    case MenuStates::EAppType::GAME:
        GetGameTagString(static_cast<MenuStates::EGameTag>(menuStates.GetSelectedTagIndex()), _currentResult.line2);
        break;
    case MenuStates::EAppType::DEMO:
        GetDemoTagString(static_cast<MenuStates::EDemoTag>(menuStates.GetSelectedTagIndex()), _currentResult.line2);
        break;
    case MenuStates::EAppType::UTILITY:
        GetUtilityTagString(static_cast<MenuStates::EUtilityTag>(menuStates.GetSelectedTagIndex()), _currentResult.line2);
        break;
    case MenuStates::EAppType::SETUP_APP:
        GetSetupAppTagString(static_cast<MenuStates::ESetupAppTag>(menuStates.GetSelectedTagIndex()), _currentResult.line2);
        break;
    default:
        const char* line2 = "UNKNOWN";
        SAFE_STRNCPY(_currentResult.line2, line2, _currentResult.line2.size());
        break;
    }
}

void MenuRenderer::RenderS030()
{
    const char* select = "Select ";
    SAFE_STRNCPY(_currentResult.line1, select, _currentResult.line1.size());
    _currentResult.line1[_currentResult.line1.size() - 1] = '\0';

    const char* appType;
    switch (menuStates.GetSelectedAppTypeIndex())
    {
    case MenuStates::EAppType::GAME:      appType = "GAME";      break;
    case MenuStates::EAppType::DEMO:      appType = "DEMO";      break;
    case MenuStates::EAppType::UTILITY:   appType = "UTILITY";   break;
    case MenuStates::EAppType::SETUP_APP: appType = "SETUP APP"; break;
    default:                              appType = "UNKNOWN";   break;
    }

    SAFE_STRNCPY(_currentResult.line1, appType, _currentResult.line1.size());
    _currentResult.line1[_currentResult.line1.size() - 1] = '\0';
    GetAppNameString(menuStates.GetSelectedAppNameIndex(), _currentResult.line2);
}

void MenuRenderer::RenderS040()
{
    GetAppNameString(menuStates.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* start = "START";
    SAFE_STRNCPY(_currentResult.line2, start, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void MenuRenderer::RenderS041()
{
    GetAppNameString(menuStates.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* running = "RUNNING";
    SAFE_STRNCPY(_currentResult.line2, running, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void MenuRenderer::RenderS043()
{
    GetAppNameString(menuStates.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* paused = "(PAUSED) RESUME";
    SAFE_STRNCPY(_currentResult.line2, paused, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void MenuRenderer::RenderS044()
{
    GetAppNameString(menuStates._selectedAppNameIndex, _currentResult.line1);
    const char* quit = "QUIT";
    SAFE_STRNCPY(_currentResult.line2, quit, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void MenuRenderer::RenderS045()
{
    GetAppNameString(menuStates.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* confirm = "CONFIRM?";
    SAFE_STRNCPY(_currentResult.line2, confirm, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void MenuRenderer::RenderS050()
{
    GetAppNameString(menuStates.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* settings = "SETTINGS";
    SAFE_STRNCPY(_currentResult.line2, settings, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void MenuRenderer::RenderS060()
{
    GetAppNameString(menuStates.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* highscores = "HIGHSCORES";
    SAFE_STRNCPY(_currentResult.line2, highscores, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void MenuRenderer::RenderS061()
{
    GetAppNameString(menuStates.GetSelectedAppNameIndex(), _currentResult.line1);

    int displayIndex = menuStates.GetSelectedHighscoreIndex() + 1;
    std::array<char, 7> name;
    GetHighscoreName(menuStates.GetSelectedHighscoreIndex(), name);
    int score = GetHighscoreValue(menuStates.GetSelectedHighscoreIndex());
    // Format: " 1 MICHEL 123456"
    int written = snprintf(_currentResult.line2.data(), 16 + 1, "%2d %-6.6s %6d", displayIndex, name.data(), score);
    if (written != 16)
    {
        exit(1);
    }
}

void MenuRenderer::RenderS070()
{
    GetAppNameString(menuStates.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* reset = "RESET HIGHSCORES";
    SAFE_STRNCPY(_currentResult.line2, reset, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void MenuRenderer::RenderS071()
{
    GetAppNameString(menuStates.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* confirm = "CONFIRM RESET?";
    SAFE_STRNCPY(_currentResult.line2, confirm, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void MenuRenderer::RenderS072()
{

    GetAppNameString(menuStates.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* resetDone = "HIGHSCORES RESET";
    SAFE_STRNCPY(_currentResult.line2, resetDone, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void MenuRenderer::RenderS080()
{
    GetAppNameString(menuStates.GetSelectedAppNameIndex(), _currentResult.line1);
    const char* playerSetup = "PLAYER SETUP";
    SAFE_STRNCPY(_currentResult.line2, playerSetup, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void MenuRenderer::RenderS090()
{
    GetAppNameString(menuStates.GetSelectedAppNameIndex(), _currentResult.line1);
    if (menuStates.GetSwapFavoriteStatus()) //TODO: Real implementation: Swap before, check state
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

void MenuRenderer::RenderDefault()
{
    const char* notImplemented = "NOT IMPLEMENTED";
    SAFE_STRNCPY(_currentResult.line1, notImplemented, _currentResult.line1.size());
    _currentResult.line1[_currentResult.line1.size() - 1] = '\0';
    const char* yet = "YET";
    SAFE_STRNCPY(_currentResult.line2, yet, _currentResult.line2.size());
    _currentResult.line2[_currentResult.line2.size() - 1] = '\0';
}

void MenuRenderer::GetAppTypeString(MenuStates::EAppType appType, std::array<char, 17>& outBuffer) const
{
    const char* name;
    switch (appType) 
    {
        case MenuStates::EAppType::GAME:      name = "Game";      break;
        case MenuStates::EAppType::DEMO:      name = "Demo";      break;
        case MenuStates::EAppType::UTILITY:   name = "Utility";   break;
        case MenuStates::EAppType::SETUP_APP: name = "Setup App"; break;
        default:                              name = "Unknown";   break;
    }
	 SAFE_STRNCPY(outBuffer, name, outBuffer.size());
    outBuffer[outBuffer.size() - 1] = '\0';
}

void MenuRenderer::GetViewModeString(MenuStates::EViewMode viewMode, std::array<char, 17>& outBuffer) const
{
    const char* name;
    switch (viewMode) {
    case MenuStates::EViewMode::RECENT: name = "RECENT"; break;
    case MenuStates::EViewMode::MOST_USED: name = "MOST USED"; break;
    case MenuStates::EViewMode::FAVORITES: name = "FAVORITES"; break;
    case MenuStates::EViewMode::ALPHABETIC: name = "ALPHABETIC"; break;
    case MenuStates::EViewMode::TAG: name = "TAG"; break;
    case MenuStates::EViewMode::NEW: name = "NEW"; break;
    case MenuStates::EViewMode::RANDOM: name = "RANDOM"; break;
    default: name = "UNKNOWN"; break;
    }
	
    SAFE_STRNCPY(outBuffer, name, outBuffer.size());
    outBuffer[outBuffer.size() - 1] = '\0';
}

void MenuRenderer::GetGameTagString(MenuStates::EGameTag tag, std::array<char, 17>& outBuffer) const
{
    const char* name;
    switch (tag) {
        case MenuStates::EGameTag::ARCADE: name = "ARCADE"; break;
        case MenuStates::EGameTag::AUDIO: name = "AUDIO"; break;
        case MenuStates::EGameTag::CONTINUOUS: name = "CONTINUOUS"; break;
        case MenuStates::EGameTag::HORIZONTAL: name = "HORIZONTAL"; break;
        case MenuStates::EGameTag::MICROPHONE: name = "MICROPHONE"; break;
        case MenuStates::EGameTag::PUZZLE: name = "PUZZLE"; break;
        case MenuStates::EGameTag::RACING: name = "RACING"; break;
        case MenuStates::EGameTag::SHOOTER: name = "SHOOTER"; break;
        case MenuStates::EGameTag::SINGLE_PLAYER: name = "SINGLE PLAYER"; break;
        case MenuStates::EGameTag::TURN_BASED: name = "TURN BASED"; break;
        case MenuStates::EGameTag::TWO_PLAYER: name = "TWO PLAYER"; break;
        case MenuStates::EGameTag::VERTICAL: name = "VERTICAL"; break;
        default: name = "UNKNOWN"; break;
    }

	SAFE_STRNCPY(outBuffer, name, outBuffer.size());
    outBuffer[outBuffer.size() - 1] = '\0';
}

void MenuRenderer::GetDemoTagString(MenuStates::EDemoTag tag, std::array<char, 17>& outBuffer) const
{
    const char* name;
    switch (tag) {
        case MenuStates::EDemoTag::AUDIO: name = "AUDIO"; break;
        case MenuStates::EDemoTag::INTERACTIVE: name = "INTERACTIVE"; break;
        case MenuStates::EDemoTag::STATIC: name = "STATIC"; break;
        default: name = "UNKNOWN"; break;
    }

	SAFE_STRNCPY(outBuffer, name, outBuffer.size());
    outBuffer[outBuffer.size() - 1] = '\0';
}

void MenuRenderer::GetUtilityTagString(MenuStates::EUtilityTag tag, std::array<char, 17>& outBuffer) const
{
    const char* name;
    switch (tag) {
        case MenuStates::EUtilityTag::AUDIO: name = "AUDIO"; break;
        case MenuStates::EUtilityTag::CLOCK: name = "CLOCK"; break;
        case MenuStates::EUtilityTag::LED_STRIPS: name = "LED STRIPS"; break;
        case MenuStates::EUtilityTag::MICROPHONE: name = "MICROPHONE"; break;
        case MenuStates::EUtilityTag::SPEAKER: name = "SPEAKER"; break;
        default: name = "UNKNOWN"; break;
    }

	SAFE_STRNCPY(outBuffer, name, outBuffer.size());
    outBuffer[outBuffer.size() - 1] = '\0';
}


void MenuRenderer::GetSetupAppTagString(MenuStates::ESetupAppTag tag, std::array<char, 17>& outBuffer) const
{
    const char* name;
    switch (tag) {
        case MenuStates::ESetupAppTag::AUDIO: name = "AUDIO"; break;
        case MenuStates::ESetupAppTag::CLOCK: name = "CLOCK"; break;
        case MenuStates::ESetupAppTag::DIAGNOSTICS: name = "DIAGNOSTICS"; break;
        case MenuStates::ESetupAppTag::DISPLAYS: name = "DISPLAYS"; break;
        case MenuStates::ESetupAppTag::HARDWARE_TEST: name = "HARDWARE TEST"; break;
        case MenuStates::ESetupAppTag::JOYSTICKS: name = "JOYSTICKS"; break;
        case MenuStates::ESetupAppTag::LEDS: name = "LEDS"; break;
        case MenuStates::ESetupAppTag::LED_STRIPS: name = "LED STRIPS"; break;
        case MenuStates::ESetupAppTag::MICROPHONE: name = "MICROPHONE"; break;
        case MenuStates::ESetupAppTag::SPEAKER: name = "SPEAKER"; break;
        case MenuStates::ESetupAppTag::SYSTEM_BUTTON: name = "SYSTEM BUTTON"; break;
        case MenuStates::ESetupAppTag::INFO: name = "INFO"; break;
        default: name = "UNKNOWN"; break;
    }

	SAFE_STRNCPY(outBuffer, name, outBuffer.size());
    outBuffer[outBuffer.size() - 1] = '\0';
}

void MenuRenderer::GetAppNameString(MenuStates::EAppName appName, std::array<char, 17>& outBuffer) const
{
    const char* name;
    switch (appName) 
    {
    case MenuStates::EAppName::ONE_D_PONG: name = "1D PONG"; break;
    case MenuStates::EAppName::LINE_RACER: name = "LINE RACER"; break;
    default: name = "UNKNOWN"; break;
    }
	
    SAFE_STRNCPY(outBuffer, name, outBuffer.size());
    outBuffer[outBuffer.size() - 1] = '\0';
}

bool MenuRenderer::IsAppFavorite(MenuStates::EAppName appName) const
{
    // Implement your logic to check if the app is a favorite
    // For demonstration, let's assume 1D PONG is a favorite
    return appName == MenuStates::EAppName::ONE_D_PONG;
}

void MenuRenderer::GetHighscoreName(uint8_t index, std::array<char, 7>& outBuffer) const
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

uint32_t MenuRenderer::GetHighscoreValue(uint8_t index) const
{
    // Implement your logic to get the highscore value based on the index
    return 100000 - 1000 * (index + 1);
}

void MenuRenderer::CenterAlign(Result& result)
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

bool MenuRenderer::IsDirty() const
{
    return ((_previousResult.line1 != _currentResult.line1) ||
            (_previousResult.line2 != _currentResult.line2));
}