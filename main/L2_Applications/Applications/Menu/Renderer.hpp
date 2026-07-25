
#pragma once

#include "States.hpp"
#include <array>
#include <string>

class Renderer {
public:
    struct Result {
        std::string line1;
        std::string line2;
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

    std::string GetAppTypeString(Application::EType appType) const;
    std::string GetViewModeString(States::EViewMode viewMode) const; 
    std::string GetGameTagString(States::EGameTag tag) const;
    std::string GetDemoTagString(States::EDemoTag tag) const;
    std::string GetUtilityTagString(States::EUtilityTag tag) const;
    std::string GetSetupAppTagString(States::ESetupAppTag tag) const;
    std::string GetAppNameString(States::EAppName appName) const;
    bool IsAppFavorite(States::EAppName appName) const;
    std::string GetHighscoreName(uint8_t index) const;
    uint32_t GetHighscoreValue(uint8_t index) const;

    const States& _states;

    Result _previousResult;
    Result _currentResult;
};
