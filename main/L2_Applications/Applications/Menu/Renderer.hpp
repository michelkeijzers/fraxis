
#pragma once

#include "States.hpp"
#include <cstdint>
#include <array>
#include <string>
#include <string_view>
#include <vector>

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

private:
    static constexpr uint8_t NR_OF_ITEM_LINES = NR_OF_LINES - 1;
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

    template<typename T>
    void RenderItems(
        const std::vector<T>& lookupTable,
        uint16_t selectedIndex)
    {
        std::array<int16_t, NR_OF_ITEM_LINES> lineItemIndices = {};
        const auto nrOfItems = static_cast<uint16_t>(lookupTable.size());

        if (selectedIndex == 0)
        {
            lineItemIndices[0] = 0;
            lineItemIndices[1] = 1;
            lineItemIndices[2] = 2;
        }
        else if ((selectedIndex == nrOfItems - 1) && (selectedIndex < lookupTable.size()))
        {
            lineItemIndices[0] = selectedIndex - 2;
            lineItemIndices[1] = selectedIndex - 1;
            lineItemIndices[2] = selectedIndex;
        }
        else
        {
            lineItemIndices[0] = selectedIndex - 1;
            lineItemIndices[1] = selectedIndex;
            lineItemIndices[2] = selectedIndex + 1;
        }

        while (lineItemIndices[0] < 0)
        {
            lineItemIndices[0]++;
            lineItemIndices[1]++;
            lineItemIndices[2]++;
        }

        for (uint8_t index = 0; index < 3; index++)
        {
            if (lineItemIndices[index] >= lookupTable.size())
            {
                lineItemIndices[index] = -1;
            }
        }

        FillCurrentResult(lineItemIndices, selectedIndex, nrOfItems, lookupTable);
    }

    std::vector<std::string_view> FilterTagsLookupTable(
        const std::vector<std::string_view>& lookupTable) const;
    std::vector<std::string_view> FilterAppModesLookupTable(
        const std::vector<std::string_view>& lookupTable) const;

    template<typename T>
    void FillCurrentResult(
        const std::array<int16_t, NR_OF_ITEM_LINES>& lineItemIndices,
        int16_t selectedItemIndex,
        uint16_t nrOfItems,
        const std::vector<T>& lookupTable)
    {
        for (uint8_t lineIndex = 0; lineIndex < NR_OF_ITEM_LINES; lineIndex++)
        {
            _iterationLines[lineIndex] =
            {
                CalculateSymbol(lineIndex, lineItemIndices[lineIndex],
                                selectedItemIndex, nrOfItems),
                lineItemIndices[lineIndex]
            };

            const int16_t itemIndex = _iterationLines[lineIndex].index;

            if (itemIndex >= 0 && itemIndex < nrOfItems)
            {
                _currentResult[lineIndex + 1] =
                    std::string(1, _iterationLines[lineIndex].symbol) + " " +
                    std::string(lookupTable[itemIndex]);
            }
        }
    }

    char CalculateSymbol(
        uint8_t lineIndex,
        int16_t itemIndex,
        int16_t selectedItemIndex,
        uint16_t nrOfItems) const;

    void Cls(std::array<std::string, NR_OF_LINES>& result);

    std::string GetAppTypeString(
        Application::EType appType) const;
    std::string GetViewModeString(
        States::EViewMode viewMode) const; 
    std::string GetTagString(
        Application::ETag tag) const;
    std::string GetHighscoreName(
        uint8_t index) const;
    uint32_t GetHighscoreValue(
        uint8_t index) const;

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
