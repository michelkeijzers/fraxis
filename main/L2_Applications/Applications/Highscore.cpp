#include "Highscore.hpp"
#include <cstring>
#include "../../L9_Utilities/String/StringUtilities.hpp"

Highscore::Highscore()
:
    _name{},
    _score(0)
{
}

std::string_view Highscore::GetName() const
{
    return _name;
}

uint32_t Highscore::GetScore() const
{
    return _score;
}

void Highscore::Set(
    std::string_view name,
    uint32_t score)
{
    StringUtilities::CopyToBuffer(name, _name, MAX_NAME_LENGTH);
    _score = score;
}

