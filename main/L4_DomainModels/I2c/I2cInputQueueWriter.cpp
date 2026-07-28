#include "I2cInputQueueWriter.hpp"
#include "IoPins/IoPins.hpp"
#include "IoPins/Joystick.hpp"
#include "IoPins/SystemButton.hpp"
#include "../../L3_Messages/I2cInputQueue.hpp"   


I2cInputQueueWriter::I2cInputQueueWriter(I2cInputQueue& i2cInputQueue, IoPins& ioPins)
: _i2cInputQueue(i2cInputQueue), _ioPins(ioPins) 
{
}

I2cInputQueueWriter::~I2cInputQueueWriter()
{
}

void I2cInputQueueWriter::SendMessages()
{
    SendJoystickMessages(_ioPins.GetJoystick(Types::EJoystickId::Player1));
    SendJoystickMessages(_ioPins.GetJoystick(Types::EJoystickId::Player2));
    SendSystemButtonMessage(_ioPins.GetSystemButton());
}

void I2cInputQueueWriter::SendJoystickMessages(Joystick& joystick)
{
    if (joystick.GetButtonStateDirty().IsDirty())
    {
        I2cInputQueue::InputMessage message;
        message.type = I2cInputQueue::InputMessage::EType::JoystickButton;
        message.joystickButton.id = joystick.GetId();
        message.joystickButton.pressed = joystick.GetButtonState();
        _i2cInputQueue.GetRtosQueue().Send(&message, 0);
        joystick.GetButtonStateDirty().ClearDirty();
    }

    if (joystick.GetDirectionDirty().IsDirty())
    {
        I2cInputQueue::InputMessage message;
        message.type = I2cInputQueue::InputMessage::EType::JoystickDirection;
        message.joystickDirection.id = joystick.GetId();
        message.joystickDirection.direction = joystick.GetDirection();
        _i2cInputQueue.GetRtosQueue().Send(&message, 0);
        joystick.GetDirectionDirty().ClearDirty();
    }
}

void I2cInputQueueWriter::SendSystemButtonMessage(SystemButton& systemButton)
{
    Dirty& dirty = systemButton.GetStateDirty();
    if (dirty.IsDirty())
    {
        I2cInputQueue::InputMessage message;
        message.type = I2cInputQueue::InputMessage::EType::SystemButton;
        message.systemButton.pressed = systemButton.GetState();
        _i2cInputQueue.GetRtosQueue().Send(&message, 0);
        dirty.ClearDirty();
    }    
}

