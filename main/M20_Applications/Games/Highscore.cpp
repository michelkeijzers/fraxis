#include "Highscore.hpp"
#include <cstring>
#include "../../M90_Utilities/String/StringUtilities.hpp"

Highscore::Highscore()
:
    _name {},
    _score(0)
{
}

std::string_view Highscore::GetName() const
{
    return _name.data();
}

uint32_t Highscore::GetScore() const
{
    return _score;
}
