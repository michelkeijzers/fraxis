#include "Mcp23017Driver.hpp"

class Mcp23017Model;
class I2c;

Mcp23017Driver::Mcp23017Driver(Mcp23017Model& model, I2c& i2c)
: _model(model), _i2c(i2c)
{
}
