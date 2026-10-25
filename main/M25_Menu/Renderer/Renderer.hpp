#pragma once

#include "../States/States.hpp"
#include "StatesRenderer.hpp"
#include <cstdint>
#include <array>
#include <string>
#include <string_view>
#include <vector>

class StatesRenderer;
class ApplicationsManager;

class Renderer {
public:
    static constexpr uint8_t NR_OF_LINES = 4;

    Renderer(
        const ApplicationsManager& applicationsManager,
        States& states);

    std::array<std::string, NR_OF_LINES> Render();
    bool IsDirty() const;

    std::string_view GetCurrentApplicationName() const;
    std::array<std::string, NR_OF_LINES> GetCurrentResult() const;

    void SetCurrentResultLine(
        uint8_t lineIndex,
        std::string_view lineText);
    void AppendToCurrentResultLine(
        uint8_t lineIndex,
        std::string_view lineText);

    void RenderItems(
        std::span<const std::string_view> stringsToShow,
        uint16_t selectedIndex);

private:
    static constexpr uint8_t NR_OF_ITEM_LINES = NR_OF_LINES - 1;

    void FillCurrentResult(
        const std::array<int16_t, NR_OF_ITEM_LINES>& lineItemIndices,
        int16_t selectedItemIndex,
        uint16_t nrOfItems,
        std::span<const std::string_view> stringsToShow);

    char CalculateSymbol(
        uint8_t lineIndex,
        int16_t itemIndex,
        int16_t selectedItemIndex,
        uint16_t nrOfItems) const;

    void Cls(std::array<std::string, NR_OF_LINES>& result);

    std::string GetHighscoreName(
        uint8_t index) const;
    uint32_t GetHighscoreValue(
        uint8_t index) const;

    StatesRenderer _statesRenderer;

    std::array<std::string, NR_OF_LINES> _lines;

    const ApplicationsManager& _applicationsManager;
    States& _states;

    std::array<std::string, NR_OF_LINES> _previousResult;
    std::array<std::string, NR_OF_LINES> _currentResult;

    /// @brief Contains (upto) three items for the user to select from
    struct IterationLine
    {
        char symbol;
        /// @brief -1 when not existing
        int16_t index;
    };

    std::array<IterationLine, 3> _iterationLines;
};
