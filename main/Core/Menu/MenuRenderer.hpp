#pragma once

#include "MenuStates.hpp"
#include <array>
#include <span>

class MenuRenderer {
private:
    const MenuStates& menuStates;

public:
    struct Result {
        std::array<char,16> line1;
        std::array<char,16> line2;
    };

    MenuRenderer(const MenuStates& menuStates);
    Result Render();
    
private:
    void Cls(Result& result);

    void GetAppTypeString(MenuStates::EAppType appType, std::span<char, 16> outBuffer) const;
    void GetViewModeString(MenuStates::EViewMode viewMode, std::span<char, 16> outBuffer) const;
    void GetGameTagString(MenuStates::EGameTag tag, std::span<char, 16> outBuffer) const;
    void GetDemoTagString(MenuStates::EDemoTag tag, std::span<char, 16> outBuffer) const;
    void GetUtilityTagString(MenuStates::EUtilityTag tag, std::span<char, 16> outBuffer) const;
    void GetSetupAppTagString(MenuStates::ESetupAppTag tag, std::span<char, 16> outBuffer) const;
    void GetAppNameString(MenuStates::EAppName appName, std::span<char, 16> outBuffer) const;
    bool IsAppFavorite(MenuStates::EAppName appName) const;
    void GetHighscoreName(uint8_t index, std::span<char, 6> outBuffer) const;
    uint32_t GetHighscoreValue(uint8_t index) const;

    void CenterAlign(Result& result);
};
