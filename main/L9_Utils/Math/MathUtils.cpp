#include "MathUtils.hpp"

/* static */ int32_t MathUtils::Wrap(uint32_t index, uint32_t max_value) 
{
    return (index % max_value + max_value) % max_value;
}

