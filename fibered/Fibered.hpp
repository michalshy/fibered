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

#ifndef FIBERED_HPP
#define FIBERED_HPP

#include <queue>
#include <cstdint>
#include <thread>
#include <Windows.h>
#include <winbase.h>
#include <winnt.h>

#include "SpinLock.hpp"
#include "FiberedTypes.hpp"

/**
 * @brief FiberedConfig is provided for simple overview for the most imporant
 * internal configuration tweaks like nr of fibers, size etc.
 */
 namespace{
     struct FiberedConfig {
     
     } fibered_config; //default config
 }

/**
 * @brief Main class of fibered, it is Job System per se
 */
class Fibered {
public:
    Fibered();
    void Init();
    void KickJob(Job job);
    ~Fibered();

    std::thread* GetThreads() { return workerThreads; }
    uint32_t GetThreadCount() { return threadCount; }
    std::priority_queue<Job, std::vector<Job>, std::greater<Priority>> GetJobQueue() { return jobQueue; }
    std::priority_queue<Job, std::vector<Job>, std::greater<Priority>> GetWaitList() { return waitList; };
protected:
    void WorkerLoop(uint32_t i);
private:
    FiberedConfig config;
    std::thread* workerThreads;
    uint32_t threadCount;
    std::priority_queue<Job, std::vector<Job>, std::greater<Priority>> jobQueue;
    std::priority_queue<Job, std::vector<Job>, std::greater<Priority>> waitList;
    uint32_t GetCoreCount();
};



#endif // FIBERED_HPP