#pragma once

#include "../M40_DomainModels/Nvs/NvsQueueReader.hpp"
#include "../M40_DomainModels/Nvs/NvsQueueWriter.hpp"
#include "../M90_Utilities/Task/Task.hpp"

class Context;
class RtosTask;
class NvsQueue;

class NvsTask : public Task
{
public:
    explicit NvsTask(
        Context& context);
    ~NvsTask() = default;

    void Initialize() override;
    void Run() override;
    static void TaskEntry(
        void* param);

private:
    Context& _context;
    NvsQueue& _nvsQueue;
    NvsQueueReader _nvsQueueReader;
    NvsQueueWriter _nvsQueueWriter;
};
