#include "I2cInputQueueWriter.hpp"
#include "IoPins/IoPins.hpp"
#include "IoPins/Joystick.hpp"
#include "IoPins/SystemButton.hpp"
#include "../../L3_Messages/I2cInputQueue.hpp"   
#include "../../L9_Utilities/Log/Log.hpp" 

I2cInputQueueWriter::I2cInputQueueWriter(
    I2cInputQueue& i2cInputQueue, 
    IoPins& ioPins)
:   _ioPins(ioPins) 
{
    SetQueue(i2cInputQueue);
}

I2cInputQueueWriter::~I2cInputQueueWriter()
{
}

I2cInputQueue& I2cInputQueueWriter::GetI2cInputQueue()
{
    return static_cast<I2cInputQueue&>(GetQueue());
}

void I2cInputQueueWriter::SendMessages()
{
    SendJoystickMessages(_ioPins.GetJoystick(Types::EJoystickId::Player1));
    SendJoystickMessages(_ioPins.GetJoystick(Types::EJoystickId::Player2));
    SendSystemButtonMessage(_ioPins.GetSystemButton());
}

void I2cInputQueueWriter::SendJoystickMessages(
    Joystick& joystick)
{
    if (joystick.GetButtonStateDirty().IsDirty())
    {
        I2cInputQueue::Message message;
        message.type = I2cInputQueue::Message::EType::JoystickButton;
        message.joystickButton.id = joystick.GetId();
        message.joystickButton.pressed = joystick.GetButtonState();
        GetI2cInputQueue().GetRtosQueue().Send(&message, 0);
        Log::Text(Types::ETaskId::I2cTask, "JS Button sent");
        joystick.GetButtonStateDirty().ClearDirty();
    }

    if (joystick.GetDirectionDirty().IsDirty())
    {
        I2cInputQueue::Message message;
        message.type = I2cInputQueue::Message::EType::JoystickDirection;
        message.joystickDirection.id = joystick.GetId();
        message.joystickDirection.direction = joystick.GetDirection();
        GetI2cInputQueue().GetRtosQueue().Send(&message, 0);
        Log::Text(Types::ETaskId::I2cTask, "JS Direction sent");
        joystick.GetDirectionDirty().ClearDirty();
    }
}

void I2cInputQueueWriter::SendSystemButtonMessage(
    SystemButton& systemButton)
{
    Dirty& dirty = systemButton.GetStateDirty();
    if (dirty.IsDirty())
    {
        I2cInputQueue::Message message;
        message.type = I2cInputQueue::Message::EType::SystemButton;
        message.systemButton.pressed = systemButton.GetState();
        GetI2cInputQueue().GetRtosQueue().Send(&message, 0);
        Log::Text(Types::ETaskId::I2cTask, "SystemButton sent");
        dirty.ClearDirty();
    }    
}

