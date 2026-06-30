#include "MenuRenderer.hpp"
#if defined(_WIN32) || defined(_WIN64)
    #include <iostream>
    using std::cout;
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
            std::string_view line1 = "Welcome to";
            std::string_view line2 = "FRAXIS v0.0.1";
            std::copy_n(line1.data(), line1.size(), result.line1.data());
            std::copy_n(line2.data(), line2.size(), result.line2.data());
        }
    break;

    case State::S010_SELECT_APP_TYPE:
        {
            std::string_view line1 = "Select App Type";
            std::copy_n(line1.data(), line1.size(), result.line1.data());
            GetAppTypeString(menuStates.selectedAppTypeIndex, result.line2);
        }
        break;

    case State::S020_SELECT_VIEW_MODE:
        {
            std::string_view line1 = "Select View Mode";
            std::copy_n(line1.data(), line1.size(), result.line1.data());
            GetViewModeString(menuStates.selectedViewModeIndex, result.line2);
        }
        break;

    case State::S021_SELECT_TAG:
        {
            std::string_view line1 = "Select Tag";
            std::copy_n(line1.data(), line1.size(), result.line1.data());

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
                std::string_view line2 = "UNKNOWN";
                std::copy_n(line2.data(), line2.size(), result.line2.data());
                break;
            }
        }
        break;

	 case State::S030_SELECT_APP:
	 {
		 std::string_view select = "Select ";
		 std::copy_n(select.data(), select.size(), result.line1.data());

		 std::string_view appType;
		 switch (menuStates.selectedAppTypeIndex)
		 {
		 case MenuStates::EAppType::GAME:      appType = "GAME";      break;
		 case MenuStates::EAppType::DEMO:      appType = "DEMO";      break;
		 case MenuStates::EAppType::UTILITY:   appType = "UTILITY";   break;
		 case MenuStates::EAppType::SETUP_APP: appType = "SETUP APP"; break;
		 default:                              appType = "UNKNOWN";   break;
		 }

		 size_t remainingSpace = 16 - select.size();
		 size_t copyLen = (std::min)(appType.size(), remainingSpace);

		 std::copy_n(appType.data(), copyLen, result.line1.data() + select.size());
		 GetAppNameString(menuStates.selectedAppNameIndex, result.line2);
	 }
	 break;


    case State::S040_APP_START:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            std::string_view start = "START";
            std::copy_n(start.data(), start.size(), result.line2.data());
        }
        break;

    case State::S041_APP_RUNNING:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            std::string_view running = "RUNNING";
            std::copy_n(running.data(), running.size(), result.line2.data());
        }
        break;

    case State::S043_APP_PAUSED:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            std::string_view paused = "(PAUSED) RESUME";
            std::copy_n(paused.data(), paused.size(), result.line2.data());
        }
        break;

    case State::S044_APP_QUIT:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            std::string_view quit = "QUIT";
            std::copy_n(quit.data(), quit.size(), result.line2.data());
        }
        break;

    case State::S045_APP_CONFIRM_QUIT:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            std::string_view confirm = "CONFIRM?";
            std::copy_n(confirm.data(), confirm.size(), result.line2.data());
        }
        break;

    case State::S050_APP_SETTINGS:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            std::string_view settings = "SETTINGS";
            std::copy_n(settings.data(), settings.size(), result.line2.data()); 
        }
        break;

    case State::S060_HIGHSCORES:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            std::string_view highscores = "HIGHSCORES";
            std::copy_n(highscores.data(), highscores.size(), result.line2.data());
        }
        break;

case State::S061_HIGHSCORE_DETAILS:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            
            int displayIndex = menuStates.selectedHighscoreIndex + 1;
            std::array<char, 6> name;
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
            std::string_view reset = "RESET HIGHSCORES";
            std::copy_n(reset.data(), reset.size(), result.line2.data());
        }
        break;

    case State::S071_CONFIRM_HIGHSCORES_RESET:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            std::string_view confirm = "CONFIRM RESET?";
            std::copy_n(confirm.data(), confirm.size(), result.line2.data());
        }
        break;

    case State::S072_HIGHSCORES_RESET_DONE:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            std::string_view resetDone = "HIGHSCORES RESET";
            std::copy_n(resetDone.data(), resetDone.size(), result.line2.data());
        }
        break;

    case State::S080_PLAYER_SETUP:
        {
            GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
            std::string_view playerSetup = "PLAYER SETUP";
            std::copy_n(playerSetup.data(), playerSetup.size(), result.line2.data());
        }
        break;

    case State::S090_SET_AS_FAVORITE:
        GetAppNameString(menuStates.selectedAppNameIndex, result.line1);
        if (menuStates.swapFavoriteStatus) //TODO: Real implementation: Swap before, check state
        { 
            std::string_view unfavorite = "UNFAVORITE";
            std::copy_n(unfavorite.data(), unfavorite.size(), result.line2.data());
        } 
        else 
        {
            std::string_view setAsFavorite = "SET AS FAVORITE";
            std::copy_n(setAsFavorite.data(), setAsFavorite.size(), result.line2.data());
        }
        break;

    default:
        {
            std::string_view notImplemented = "NOT IMPLEMENTED";
            std::copy_n(notImplemented.data(), notImplemented.size(), result.line1.data());
            std::string_view yet = "YET";
            std::copy_n(yet.data(), yet.size(), result.line2.data());
        }
        break;
    }
    
    CenterAlign(result);
    return result;
}

void MenuRenderer::GetAppTypeString(MenuStates::EAppType appType, std::span<char, 16> outBuffer) const
{
    std::string_view name;
    switch (appType) 
    {
        case MenuStates::EAppType::GAME:      name = "Game";      break;
        case MenuStates::EAppType::DEMO:      name = "Demo";      break;
        case MenuStates::EAppType::UTILITY:   name = "Utility";   break;
        case MenuStates::EAppType::SETUP_APP: name = "Setup App"; break;
        default:                              name = "Unknown";   break;
    }
    std::copy_n(name.data(), name.size(), outBuffer.data());
}

void MenuRenderer::GetViewModeString(MenuStates::EViewMode viewMode, std::span<char, 16> outBuffer) const
{
    std::string_view name;
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
    std::copy_n(name.data(), name.size(), outBuffer.data());
}

void MenuRenderer::GetGameTagString(MenuStates::EGameTag tag, std::span<char, 16> outBuffer) const
{
    std::string_view name;
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
    std::copy_n(name.data(), name.size(), outBuffer.data());
}

void MenuRenderer::GetDemoTagString(MenuStates::EDemoTag tag, std::span<char, 16> outBuffer) const
{
    std::string_view name;
    switch (tag) {
        case MenuStates::EDemoTag::AUDIO: name = "AUDIO"; break;
        case MenuStates::EDemoTag::INTERACTIVE: name = "INTERACTIVE"; break;
        case MenuStates::EDemoTag::STATIC: name = "STATIC"; break;
        default: name = "UNKNOWN"; break;
    }
    std::copy_n(name.data(), name.size(), outBuffer.data());
}

void MenuRenderer::GetUtilityTagString(MenuStates::EUtilityTag tag, std::span<char, 16> outBuffer) const
{
    std::string_view name;
    switch (tag) {
        case MenuStates::EUtilityTag::AUDIO: name = "AUDIO"; break;
        case MenuStates::EUtilityTag::CLOCK: name = "CLOCK"; break;
        case MenuStates::EUtilityTag::LED_STRIPS: name = "LED STRIPS"; break;
        case MenuStates::EUtilityTag::MICROPHONE: name = "MICROPHONE"; break;
        case MenuStates::EUtilityTag::SPEAKER: name = "SPEAKER"; break;
        default: name = "UNKNOWN"; break;
    }
    std::copy_n(name.data(), name.size(), outBuffer.data());
}


void MenuRenderer::GetSetupAppTagString(MenuStates::ESetupAppTag tag, std::span<char, 16> outBuffer) const
{
    std::string_view name;
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
    std::copy_n(name.data(), name.size(), outBuffer.data());
}

void MenuRenderer::GetAppNameString(MenuStates::EAppName appName, std::span<char, 16> outBuffer) const
{
    std::string_view name;
    switch (appName) 
    {
    case MenuStates::EAppName::ONE_D_PONG: name = "1D PONG"; break;
    case MenuStates::EAppName::LINE_RACER: name = "LINE RACER"; break;
    default: name = "UNKNOWN"; break;
    }
    std::copy_n(name.data(), name.size(), outBuffer.data());
}

bool MenuRenderer::IsAppFavorite(MenuStates::EAppName appName) const
{
    // Implement your logic to check if the app is a favorite
    // For demonstration, let's assume 1D PONG is a favorite
    return appName == MenuStates::EAppName::ONE_D_PONG;
}

void MenuRenderer::GetHighscoreName(uint8_t index, std::span<char, 6> outBuffer) const
{
    // Implement your logic to get the highscore name based on the index
    std::string name = "PL" + std::to_string(index + 1);
    std::copy_n(name.data(), name.size(), outBuffer.data());
}

uint32_t MenuRenderer::GetHighscoreValue(uint8_t index) const
{
    // Implement your logic to get the highscore value based on the index
    return 100000 - 1000 * (index + 1);
}

void MenuRenderer::CenterAlign(Result& result)
{
    auto center = [](std::array<char, 16>& line)
    {
        const size_t width = 16;
        
        // 1. Find the true length of the text by scanning backwards from the right 
        //    to find the last character that isn't a space.
        size_t len = width;
        while (len > 0 && line[len - 1] == ' ') {
            --len;
        }

        // If the line is completely empty or already full, nothing to center
        if (len == 0 || len == width) {
            return;
        }

        size_t leftPadding = (width - len) / 2;

        // 2. Move the text to its new centered position (shifting right)
        //    We go backwards to avoid overwriting our own data.
        std::copy_backward(line.begin(), line.begin() + len, line.begin() + leftPadding + len);

        // 3. Clean up the left margin with spaces
        std::fill_n(line.begin(), leftPadding, ' ');

        // 4. Clean up the right margin with spaces
        size_t rightPaddingStart = leftPadding + len;
        std::fill_n(line.begin() + rightPaddingStart, width - rightPaddingStart, ' ');
    };


    center(result.line1);
    center(result.line2);
}