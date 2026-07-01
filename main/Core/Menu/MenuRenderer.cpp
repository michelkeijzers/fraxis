#include "MenuRenderer.hpp"
#include <cstring>
#include <cstdio>
#include <cstdlib>

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

MenuRenderer::MenuRenderer(const MenuStates& menuStates) : menuStates(menuStates) 
{  
}

void MenuRenderer::Cls(Result& result) 
{
    // system("cls");
}

MenuRenderer::Result MenuRenderer::Render() 
{
    Result result;

    if (menuStates.current == menuStates.previousScanState && 
        !menuStates.forceRender) 
    {
        return result;
    }

    result.line1.fill(' ');
    result.line2.fill(' ');

#if defined(_WIN32) || defined(_WIN64)
    cout << "State: " << static_cast<int>(menuStates.current) << "\n";
#endif    

    switch (menuStates.current) {

    case State::S000_WELCOME:
        {
            const char* line1 = "Welcome to";
            const char* line2 = "FRAXIS v0.0.1";
				SAFE_STRNCPY(result.line1, line1, result.line1.size());
				result.line1[result.line1.size() - 1] = '\0';
				SAFE_STRNCPY(result.line2, line2, result.line2.size());
				result.line2[result.line2.size() - 1] = '\0';
        }
    break;

    case State::S010_SELECT_APP_TYPE:
        {
            const char* line1 = "Select App Type";
				SAFE_STRNCPY(result.line1, line1, result.line1.size());
			result.line1[result.line1.size() - 1] = '\0';
            GetAppTypeString(menuStates.selectedAppTypeIndex, result.line2);
        }
        break;

    case State::S020_SELECT_VIEW_MODE:
        {
            const char* line1 = "Select View Mode";
				SAFE_STRNCPY(result.line1, line1, result.line1.size());
            result.line1[result.line1.size() - 1] = '\0';
            GetViewModeString(menuStates.selectedViewModeIndex, result.line2);
        }
        break;

    case State::S021_SELECT_TAG:
        {
            const char* line1 = "Select Tag";
				SAFE_STRNCPY(result.line1, line1, result.line1.size());
            result.line1[result.line1.size() - 1] = '\0';
            switch (menuStates.selectedAppTypeIndex) {
            case MenuStates::EAppType::GAME:
                GetGameTagString(static_cast<MenuStates::EGameTag>(menuStates.selectedTagIndex), result.line2);
                break;
            case MenuStates::EAppType::DEMO:
                GetDemoTagString(static_cast<MenuStates::EDemoTag>(menuStates.selectedTagIndex), result.line2);
                break;
            case MenuStates::EAppType::UTILITY:
                GetUtilityTagString(static_cast<MenuStates::EUtilityTag>(menuStates.selectedTagIndex), result.line2);
                break;
            case MenuStates::EAppType::SETUP_APP:
                GetSetupAppTagString(static_cast<MenuStates::ESetupAppTag>(menuStates.selectedTagIndex), result.line2);
                break;
            default:
                const char* line2 = "UNKNOWN";
                SAFE_STRNCPY(result.line2, line2, result.line2.size());
                break;
            }
        }
        break;

	 case State::S030_SELECT_APP:
	 {
		 const char* select = "Select ";
		 SAFE_STRNCPY(result.line1, select, result.line1.size());
		 result.line1[result.line1.size() - 1] = '\0';

		 const char* appType;
		 switch (menuStates.selectedAppTypeIndex)
		 {
		 case MenuStates::EAppType::GAME:      appType = "GAME";      break;
		 case MenuStates::EAppType::DEMO:      appType = "DEMO";      break;
		 case MenuStates::EAppType::UTILITY:   appType = "UTILITY";   break;
		 case MenuStates::EAppType::SETUP_APP: appType = "SETUP APP"; break;
		 default:                              appType = "UNKNOWN";   break;
		 }

		 //size_t remainingSpace = 16 - strlen(select);
		 //size_t copyLen = (std::min)(strlen(appType), remainingSpace);

		 SAFE_STRNCPY(result.line1 , appType, result.line1.size()); // TODO? + strlen(select) after result.line1
		 result.line1[result.line1.size() - 1] = '\0';
		 GetAppNameString(menuStates.selectedAppNameIndex, result.line2);
	 }
	 break;


    case State::S040_APP_START:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            const char* start = "START";
				SAFE_STRNCPY(result.line2, start, result.line2.size());
            result.line2[result.line2.size() - 1] = '\0';
        }
        break;

    case State::S041_APP_RUNNING:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            const char* running = "RUNNING";
				SAFE_STRNCPY(result.line2, running, result.line2.size());
            result.line2[result.line2.size() - 1] = '\0';
        }
        break;

    case State::S043_APP_PAUSED:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            const char* paused = "(PAUSED) RESUME";
				SAFE_STRNCPY(result.line2, paused, result.line2.size());
            result.line2[result.line2.size() - 1] = '\0';
        }
        break;

    case State::S044_APP_QUIT:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            const char* quit = "QUIT";
				SAFE_STRNCPY(result.line2, quit, result.line2.size());
            result.line2[result.line2.size() - 1] = '\0';
        }
        break;

    case State::S045_APP_CONFIRM_QUIT:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            const char* confirm = "CONFIRM?";
				SAFE_STRNCPY(result.line2, confirm, result.line2.size());
            result.line2[result.line2.size() - 1] = '\0';
        }
        break;

    case State::S050_APP_SETTINGS:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            const char* settings = "SETTINGS";
				SAFE_STRNCPY(result.line2, settings, result.line2.size());
            result.line2[result.line2.size() - 1] = '\0';
        }
        break;

    case State::S060_HIGHSCORES:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            const char* highscores = "HIGHSCORES";
				SAFE_STRNCPY(result.line2, highscores, result.line2.size());
            result.line2[result.line2.size() - 1] = '\0';
        }
        break;

case State::S061_HIGHSCORE_DETAILS:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            
            int displayIndex = menuStates.selectedHighscoreIndex + 1;
            std::array<char, 7> name;
            GetHighscoreName(menuStates.selectedHighscoreIndex, name);
            int score        = GetHighscoreValue(menuStates.selectedHighscoreIndex);
            // Format: " 1 MICHEL 123456"
            int written = snprintf(result.line2.data(), 16 + 1, "%2d %-6.6s %6d", displayIndex, name.data(), score);
            if (written != 16)
            {
                exit(1);
            }
        }
        break;

    case State::S070_RESET_HIGHSCORES:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            const char* reset = "RESET HIGHSCORES";
				SAFE_STRNCPY(result.line2, reset, result.line2.size());
            result.line2[result.line2.size() - 1] = '\0';
        }
        break;

    case State::S071_CONFIRM_HIGHSCORES_RESET:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            const char* confirm = "CONFIRM RESET?";
				SAFE_STRNCPY(result.line2, confirm, result.line2.size());
            result.line2[result.line2.size() - 1] = '\0';
        }
        break;

    case State::S072_HIGHSCORES_RESET_DONE:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            const char* resetDone = "HIGHSCORES RESET";
				SAFE_STRNCPY(result.line2, resetDone, result.line2.size());
            result.line2[result.line2.size() - 1] = '\0';
        }
        break;

    case State::S080_PLAYER_SETUP:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            const char* playerSetup = "PLAYER SETUP";
				SAFE_STRNCPY(result.line2, playerSetup, result.line2.size());
            result.line2[result.line2.size() - 1] = '\0';
        }
        break;

    case State::S090_SET_AS_FAVORITE:
        GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
        if (menuStates.swapFavoriteStatus) //TODO: Real implementation: Swap before, check state
        { 
            const char* unfavorite = "UNFAVORITE";
				SAFE_STRNCPY(result.line2, unfavorite, result.line2.size());
            result.line2[result.line2.size() - 1] = '\0';
        } 
        else 
        {
            const char* setAsFavorite = "SET AS FAVORITE";
				SAFE_STRNCPY(result.line2, setAsFavorite, result.line2.size());
            result.line2[result.line2.size() - 1] = '\0';
        }
        break;

    default:
        {
            const char* notImplemented = "NOT IMPLEMENTED";
				SAFE_STRNCPY(result.line1, notImplemented, result.line1.size());
            result.line1[result.line1.size() - 1] = '\0';
            const char* yet = "YET";
				SAFE_STRNCPY(result.line2, yet, result.line2.size());
            result.line2[result.line2.size() - 1] = '\0';
        }
        break;
    }
    
    CenterAlign(result);
    return result;
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
			const size_t visible = 16;   // LCD width

			// Real text length
			size_t len = std::strlen(line.data());
			if (len == 0 || len >= visible)
				return;

			size_t leftPadding = (visible - len) / 2;

			// Shift text right inside the visible region
			std::copy_backward(line.begin(),
				line.begin() + len,
				line.begin() + leftPadding + len);

			// Fill left side
			std::fill_n(line.begin(), leftPadding, ' ');

			// Fill right side
			size_t rightPaddingStart = leftPadding + len;
			std::fill_n(line.begin() + rightPaddingStart,
				visible - rightPaddingStart,
				' ');

			// Restore null terminator
			line[visible] = '\0';
		};

	center(result.line1);
	center(result.line2);
}
