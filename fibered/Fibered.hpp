// MIT License
// Copyright (c) 2025 Michał Brodziak
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <cstdint>
#include <atomic>
#include <thread>
#include <cstdio>
#include <queue>
#include <Windows.h>

/**
 * @brief FiberedConfig is provided for simple overview for the most imporant
 * internal configuration tweaks like nr of fibers, size etc.
 */
struct FiberedConfig {

};

/**
 * @brief Main class of fibered, it is Job System per se
 */
class Fibered {
public:
    enum class Priority
    {
        LOW, MEDIUM, HIGH, CRITICAL
    };
    struct AtomicCounter {
        std::atomic<uint32_t> counter;
        AtomicCounter() : counter(0) {}
        AtomicCounter(uint32_t initial) : counter(initial) {}
    };
    struct Job {
        void (*entry)(void*);
        Priority priority;
        void* param;
        AtomicCounter* counter;
    };

    Fibered();
    void KickJob(Job job);
    ~Fibered();

    std::thread* GetThreads() { return workerThreads; }
    uint32_t GetThreadCount() { return threadCount; }
    std::priority_queue<Job, std::vector<Job>, std::greater<Priority>> GetJobQueue() { return jobQueue; }
    std::priority_queue<Job, std::vector<Job>, std::greater<Priority>> GetWaitList() { return waitList; };
protected:
    void WorkerLoop(uint32_t i);
private:
    std::thread* workerThreads;
    uint32_t threadCount;
    std::priority_queue<Job, std::vector<Job>, std::greater<Priority>> jobQueue;
    std::priority_queue<Job, std::vector<Job>, std::greater<Priority>> waitList;
    uint32_t GetCoreCount();
};

/// PUBLIC FUNCTIONS
inline Fibered::Fibered() {
    threadCount = GetCoreCount();
    workerThreads = new std::thread[threadCount];
    for (uint32_t i = 0; i < threadCount; ++i) {
        workerThreads[i] = std::thread(&Fibered::WorkerLoop, this, i);
    }
}

inline void Fibered::KickJob(Job job) {
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

inline Fibered::~Fibered() {
    for (uint32_t i = 0; i < threadCount; ++i) {
        workerThreads[i].join();
    }
    delete [] workerThreads;
}
/// PROTECTED FUNCTIONS
inline void Fibered::WorkerLoop(uint32_t i) {
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
