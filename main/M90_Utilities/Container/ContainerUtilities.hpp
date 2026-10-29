#pragma once

#include "../Assert/Assert.hpp"
#include <span>

class ContainerUtilities
{
public:
    /// @brief Find first index of an item, or -1 if not found
    template<typename T>
    static int FindFirstIndexOf(
        std::span<const T> container,
        const T& value)
    {
        for (size_t index = 0; index < container.size(); ++index)
        {
            if (container[index] == value)
            {
                return static_cast<int>(index);
            }
        }

        return -1;
    }

    /// @brief Find first index of an item within two containers which are not equal, or -1 if not
    // found.
    template<typename TContainerA, typename TContainerB>
    static int FindFirstNonEqual(
        const TContainerA& containerA,
        const TContainerB& containerB)
    {
        if (containerA.size() != containerB.size())
        {
            return -1;
        }

        for (size_t i = 0; i < containerA.size(); ++i)
        {
            if (containerA[i] != containerB[i])
            {
                return static_cast<int>(i);
            }
        }

        return -1;
    }

    template<typename TContainerA, typename TContainerB>
    /// @brief Count the different items in two lists.
    static int CountDifferent(
        std::span<const TContainerA&> containerA,
        std::span<const TContainerB&> containerB)
    {
        // NOSONAR: TODO The System task is not fully true, maybe add an unknown taskId).
        Assert::Equals(
            Types::ETaskId::System, containerA.size(), containerB.size(), "container size");
        int count = 0;
        for (int index = 0; index < containerA.size(); index++)
        {
            if (!(containerA[index] == containerB[index]))
            {
                count++;
            }
        }

        return count;
    }
};
