#pragma once

#include "MenuStates.hpp"
#include <array>

class MenuRenderer {
private:
    const MenuStates& menuStates;

public:
    struct Result {
        std::array<char,17> line1;
        std::array<char,17> line2;
    };

    MenuRenderer(const MenuStates& menuStates);
    Result Render();
    bool IsDirty() const;

private:
    void Cls(Result& result);

    void GetAppTypeString(MenuStates::EAppType appType, std::array<char, 17>& outBuffer) const;
    void GetViewModeString(MenuStates::EViewMode viewMode, std::array<char, 17>& outBuffer) const; 
    void GetGameTagString(MenuStates::EGameTag tag, std::array<char, 17>& outBuffer) const;
    void GetDemoTagString(MenuStates::EDemoTag tag, std::array<char, 17>& outBuffer) const;
    void GetUtilityTagString(MenuStates::EUtilityTag tag, std::array<char, 17>& outBuffer) const;
    void GetSetupAppTagString(MenuStates::ESetupAppTag tag, std::array<char, 17>& outBuffer) const;
    void GetAppNameString(MenuStates::EAppName appName, std::array<char, 17>& outBuffer) const;
    bool IsAppFavorite(MenuStates::EAppName appName) const;
    void GetHighscoreName(uint8_t index, std::array<char, 7>& outBuffer) const;
    uint32_t GetHighscoreValue(uint8_t index) const;

    void CenterAlign(Result& result);

    Result _previousResult;
    Result _currentResult;
};
