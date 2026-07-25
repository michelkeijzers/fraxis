
#pragma once

#include "States.hpp"
#include <array>

class Renderer {
public:
    struct Result {
        std::array<char,17> line1;
        std::array<char,17> line2;
    };

    Renderer(const States& states);
    Result Render();
    bool IsDirty() const;

    Result GetCurrentResult() const;

private:
    void RenderS000();
    void RenderS010();
    void RenderS020();
    void RenderS021();
    void RenderS030();
    void RenderS040();
    void RenderS041();
    void RenderS043();
    void RenderS044();
    void RenderS045();
    void RenderS050();
    void RenderS060();
    void RenderS061();
    void RenderS070();
    void RenderS071();
    void RenderS072();
    void RenderS080();
    void RenderS090();
    void RenderDefault();

    void Cls(Result& result);

    void GetAppTypeString(Application::EType appType, std::array<char, 17>& outBuffer) const;
    void GetViewModeString(States::EViewMode viewMode, std::array<char, 17>& outBuffer) const; 
    void GetGameTagString(States::EGameTag tag, std::array<char, 17>& outBuffer) const;
    void GetDemoTagString(States::EDemoTag tag, std::array<char, 17>& outBuffer) const;
    void GetUtilityTagString(States::EUtilityTag tag, std::array<char, 17>& outBuffer) const;
    void GetSetupAppTagString(States::ESetupAppTag tag, std::array<char, 17>& outBuffer) const;
    void GetAppNameString(States::EAppName appName, std::array<char, 17>& outBuffer) const;
    bool IsAppFavorite(States::EAppName appName) const;
    void GetHighscoreName(uint8_t index, std::array<char, 7>& outBuffer) const;
    uint32_t GetHighscoreValue(uint8_t index) const;

    void CenterAlign(Result& result);

    const States& _states;

    Result _previousResult;
    Result _currentResult;
};
