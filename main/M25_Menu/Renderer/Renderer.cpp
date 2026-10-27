#include "Renderer.hpp"
#include "StatesRenderer.hpp"
#include "../../M20_Applications/Games/Game.hpp"
#include "../../M20_Applications/Applications/Application.hpp"
#include "../../M20_Applications/ApplicationsManager.hpp"
#include "../../M40_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include "../../M90_Utilities/String/StringUtilities.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M90_Utilities/Math/MathUtilities.hpp"
#include "../../M90_Utilities/Array/ArrayUtilities.hpp"
#include <cstdio>
#include <cstdlib>
#include <algorithm>

Renderer::Renderer(
    const ApplicationsManager& applicationsManager,
    States& states)
:
    _statesRenderer(*this, states),
    _applicationsManager(applicationsManager),
    _states(states),
    _previousResult({}),
    _currentResult({}),
    _iterationLines({})
{}

std::array<std::string, Renderer::NR_OF_LINES> Renderer::Render()
{
    _previousResult = _currentResult; // Copy by value
    for (uint8_t index = 0; index < NR_OF_LINES; index++)
    {
        _currentResult[index] = "";
    }

    switch (_states.GetCurrentState())
    {
    case States::EState::S000_Welcome:                   _statesRenderer.RenderS000(); break;
    case States::EState::S010_SelectApplicationType:     _statesRenderer.RenderS010(); break;
    case States::EState::S020_SelectViewMode:            _statesRenderer.RenderS020(); break;
    case States::EState::S021_SelectTag:                 _statesRenderer.RenderS021(); break;
    case States::EState::S030_SelectApplication:         _statesRenderer.RenderS030(); break;
    case States::EState::S040_ApplicationMode:           _statesRenderer.RenderS040(); break;
    case States::EState::S050_Highscores:                _statesRenderer.RenderS050(); break;
    default:                                             _statesRenderer.RenderDefault(); break;
    }

    for (uint8_t index = 0; index < NR_OF_LINES; index++)
    {
    _currentResult[index] = 
        StringUtilities::LeftAlign(_currentResult[index], Lcd2004::LINE_WIDTH);
    Assert::Equals(
        Types::ETaskId::ApplicationsTask,
        _currentResult[index].size(),
        Lcd2004::LINE_WIDTH,
        "_currentResult.line" + std::to_string(index + 1)); // NONSONAR: No std::format
    }

    return _currentResult;
}

char Renderer::CalculateSymbol(
    uint8_t lineIndex,
    int16_t itemIndex,
    int16_t selectedItemIndex,
    uint16_t nrOfItems) const
{
    if (itemIndex == selectedItemIndex)
    {
        return '>';
    }
    else if (lineIndex == 0)
    {
        if (itemIndex == 0) return '-';
        return '^';
    }
    else if (lineIndex == 1)
    {
        if (itemIndex == nrOfItems - 1)
        {
            return '_';
        }
    }
    else if (lineIndex == 2)
    {
        if (itemIndex == nrOfItems - 1)
        {
            return '_';
        }
        return 'v';
    }

    return ' ';
};

std::string Renderer::GetHighscoreName(
    uint8_t index) const
{
    // Implement your logic to get the highscore name based on the index
    const char* name;
    switch (index)
    {
    case 0: name = "PM10"; break;
    case 1: name = "PM20"; break;
    case 2: name = "PM30"; break;
    case 3: name = "PM40"; break;
    default: name = "UNKNOWN"; break;
    }

    return name;
}

uint32_t Renderer::GetHighscoreValue(
    uint8_t index) const
{
    // Implement your logic to get the highscore value based on the index
    return 100'000 - 1000 * (index + 1);
}

bool Renderer::IsDirty() const
{
    return (_previousResult != _currentResult);
}

std::array<std::string, Renderer::NR_OF_LINES> Renderer::GetCurrentResult() const
{
    return _currentResult;
}

std::string_view Renderer::GetCurrentApplicationName() const
{
    return ApplicationsInfo::GetNameByIndex(
        _states.GetApplicationSelectionStates().GetSelectedApplicationIndex());
}


void Renderer::RenderItems(
    std::span<const std::string_view> stringsToShow,
    uint16_t selectedIndex)
{
    std::array<int16_t, NR_OF_ITEM_LINES> lineItemIndices = {};
    const auto nrOfItems = static_cast<uint16_t>(stringsToShow.size());

    if (selectedIndex == 0)
    {
        lineItemIndices[0] = 0;
        lineItemIndices[1] = 1;
        lineItemIndices[2] = 2;
    }
    else if ((selectedIndex == nrOfItems - 1) && (selectedIndex < stringsToShow.size()))
    {
        lineItemIndices[0] = static_cast<uint16_t>(selectedIndex - 2);
        lineItemIndices[1] = static_cast<uint16_t>(selectedIndex - 1);
        lineItemIndices[2] = static_cast<uint16_t>(selectedIndex);
    }
    else
    {
        lineItemIndices[0] = static_cast<uint16_t>(selectedIndex - 1);
        lineItemIndices[1] = static_cast<uint16_t>(selectedIndex);
        lineItemIndices[2] = static_cast<uint16_t>(selectedIndex + 1);
    }

    while (lineItemIndices[0] < 0)
    {
        lineItemIndices[0]++;
        lineItemIndices[1]++;
        lineItemIndices[2]++;
    }

    for (uint8_t index = 0; index < 3; index++)
    {
        if (lineItemIndices[index] >= stringsToShow.size())
        {
            lineItemIndices[index] = -1;
        }
    }

    FillCurrentResult(lineItemIndices, selectedIndex, nrOfItems, stringsToShow);
}

void Renderer::FillCurrentResult(
    const std::array<int16_t, NR_OF_ITEM_LINES>& lineItemIndices,
    int16_t selectedItemIndex,
    uint16_t nrOfItems,
    std::span<const std::string_view> stringsToShow)
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
                std::string(stringsToShow[itemIndex]);
        }
    }
}

void Renderer::SetCurrentResultLine(
    uint8_t lineIndex,
    std::string_view lineText)
{
    _currentResult[lineIndex] = lineText;
}

void Renderer::AppendToCurrentResultLine(
    uint8_t lineIndex,
    std::string_view lineText)
{
    _currentResult[lineIndex] += lineText;
}
