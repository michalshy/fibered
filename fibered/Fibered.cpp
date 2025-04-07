#include "Fibered.hpp"
#include <cstdio>

/// PUBLIC FUNCTIONS
Fibered::Fibered() {
    threadCount = GetCoreCount();
    workerThreads = new std::thread[threadCount];
    for (uint32_t i = 0; i < threadCount; ++i) {
        workerThreads[i] = std::thread(&Fibered::WorkerLoop, this, i);
    }
}

//Convert main thread to fiber and start the worker threads
void Fibered::Init() {

}

void Fibered::KickJob(Job job) {
    job.entry(job.param);
    if(job.counter->counter > 0)
    {
        job.counter->counter--;
    }
    while(job.counter->counter > 0)
    {
        continue;
    }
    printf("exiting job");
    return;
}

Fibered::~Fibered() {
    for (uint32_t i = 0; i < threadCount; ++i) {
        workerThreads[i].join();
    }
    delete [] workerThreads;
}

/// PROTECTED FUNCTIONS
void Fibered::WorkerLoop(uint32_t i) {
    while(true)
    {
        if(jobQueue.empty())
        {
            //nothing new to do
            continue;
        }
    }
}

/// PRIVATE FUNCTIONS
inline uint32_t Fibered::GetCoreCount() {
    uint32_t processor_count = std::thread::hardware_concurrency();
    if(processor_count == 0) return 1; 
    return processor_count;
}