#include "SevenSegmentsDisplaysQueueReader.hpp"
#include "../SevenSegmentsDisplays/Tm1637.hpp"
#include "../../M50_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../M30_Messages/SevenSegmentsDisplays/SevenSegmentsDisplaysQueue.hpp"
#include "../../M81_RtosServices/RtosQueue/RtosQueue.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"

SevenSegmentsDisplaysQueueReader::SevenSegmentsDisplaysQueueReader(
    M90::Assert::IAssert &assert,
    M90::String::IStringUtilities& stringUtilities,
    SevenSegmentsDisplaysQueue& sevenSegmentsDisplaysQueue,
    Tm1637& tm1637CentralPanel, 
    Tm1637& tm1637Player1, 
    Tm1637& tm1637Player2)
:  
    QueueProcessor(assert, stringUtilities),
    _tm1637CentralPanel(tm1637CentralPanel), 
    _tm1637Player1(tm1637Player1), 
    _tm1637Player2(tm1637Player2)
{
    SetQueue(sevenSegmentsDisplaysQueue);
}

SevenSegmentsDisplaysQueue& 
    SevenSegmentsDisplaysQueueReader::GetSevenSegmentsDisplaysQueue()
{
    return static_cast<SevenSegmentsDisplaysQueue&>(GetQueue());
}

bool SevenSegmentsDisplaysQueueReader::HandleMessage()
{
    bool handled = false;

    SevenSegmentsDisplaysQueue::Message message = {};
    auto& queue = GetSevenSegmentsDisplaysQueue();
    if (auto& rtosQueue = queue.GetRtosQueue(); rtosQueue.Receive(&message, 0))
    {
        switch (message.type)
        {
            case SevenSegmentsDisplaysQueue::Message::EType::Tm1637Enable:
            {
                Tm1637& tm1637 = GetTm1637ById(message.tm1637Enable.id);
                tm1637.Enable(message.tm1637Enable.on);
            }
            break;

            case SevenSegmentsDisplaysQueue::Message::EType::Tm1637Brightness:
            {
                Tm1637& tm1637 = GetTm1637ById(message.tm1637Brightness.id);
                tm1637.SetBrightness(message.tm1637Brightness.brightness);
            }
            break;

            case SevenSegmentsDisplaysQueue::Message::EType::Tm1637Value:
            {
                Tm1637& tm1637 = GetTm1637ById(message.tm1637Value.id);
                tm1637.SetValue(message.tm1637Value.value);
            }
            break;

            case SevenSegmentsDisplaysQueue::Message::EType::Tm1637Time:
            {
                Tm1637& tm1637 = GetTm1637ById(message.tm1637Time.id);
                GetAssert().Equals(
                    Types::ETaskId::SevenSegmentsDisplaysTask,
                    tm1637.GetTm1637DeviceModel().GetNumberOfDigits(),
                    4, 
                    "digits");
                tm1637.SetTime(message.tm1637Time.first, message.tm1637Time.second);
            }
            break;

            default:
                GetAssert().Fail(Types::ETaskId::SevenSegmentsDisplaysTask, "Unknown message type");
                break;
        }
        handled = true;
    }
    return handled;
}

Tm1637& SevenSegmentsDisplaysQueueReader::GetTm1637ById(
    Types::ETm1637Id tm1637Id)
{
    using enum Types::ETm1637Id;

    Tm1637* tm1637 = nullptr;
    switch (tm1637Id)
    {
        case CentralPanel: 
            tm1637 = &_tm1637CentralPanel; 
            break;
        
        case Player1:  
            tm1637 = &_tm1637Player1;      
            break;
        
        case Player2:  
            tm1637 = &_tm1637Player2;      
            break;
        
        default:
            GetAssert().Fail(Types::ETaskId::SevenSegmentsDisplaysTask, "Unknown tm1637 id");
    }
    
    return *tm1637;
}
