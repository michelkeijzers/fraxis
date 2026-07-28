#include "MathUtilities.hpp"

/* static */ int32_t MathUtilities::Wrap(uint32_t index, uint32_t max_value) 
{
    return (index % max_value + max_value) % max_value;
}

