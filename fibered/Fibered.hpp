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

//TODO: Check headers for different platform check
#ifdef _WIN64
    #include <Windows.h>
#endif

/// STRUCTS DECL SPACE ///
struct Job;
struct AtomicCounter;
/// ENUMS DECL SPACE ///
enum class Priority;

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
    std::thread* workerThreads;
    uint32_t threadCount;
    std::priority_queue<Job, std::vector<Job>, std::greater<Priority>> jobQueue;
public:
    Fibered();
    void KickJob();
    ~Fibered();
protected:
    void WorkerLoop(uint32_t i);
private:
    uint32_t GetCoreCount();
};

/// PUBLIC FUNCTIONS
inline Fibered::Fibered() {
    threadCount = GetCoreCount();

    //TODO: Figure out thread affinity
    
    workerThreads = new std::thread[threadCount];
    for (uint32_t i = 0; i < threadCount; ++i) {
        workerThreads[i] = std::thread(&Fibered::WorkerLoop, this, i);
    }
}

inline void Fibered::KickJob() {

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
        printf("Running core %d\n", i);
        //sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(900));
    }
}
/// PRIVATE FUNCTIONS
inline uint32_t Fibered::GetCoreCount() {
    //Try C++11
    //may return 0 when not able to detect
    uint32_t processor_count = std::thread::hardware_concurrency();
    if (processor_count != 0) return processor_count;
    else {
        //Try different methods
        #if defined (_WIN64)
            SYSTEM_INFO sysinfo;
            GetSystemInfo(&sysinfo);
            return sysinfo.dwNumberOfProcessors;
        #elif defined (_WIN32)
            SYSTEM_INFO sysinfo;
            GetSystemInfo(&sysinfo);
            return sysinfo.dwNumberOfProcessors;
        #elif defined (__METAL__)
            int mib[4];
            int numCPU;
            std::size_t len = sizeof(numCPU); 
            
            /* set the mib for hw.ncpu */
            mib[0] = CTL_HW;
            mib[1] = HW_AVAILCPU;  // alternatively, try HW_NCPU;
            
            /* get the number of CPUs from the system */
            sysctl(mib, 2, &numCPU, &len, NULL, 0);
            
            if (numCPU < 1) 
            {
                mib[1] = HW_NCPU;
                sysctl(mib, 2, &numCPU, &len, NULL, 0);
                if (numCPU < 1)
                    numCPU = 1;
            }
            return numCPU;
        #elif defined (__linux__)
            return sysconf(_SC_NPROCESSORS_ONLN);
        #endif
    }
    return 1;
}
/// STRUCT DEF SPACE ///
struct Job {
    void (*entry)(void*);
    Priority priority;
    void* params[];
};
struct AtomicCounter {
    std::atomic<uint32_t> counter;
    AtomicCounter() : counter(0) {}
    AtomicCounter(uint32_t initial) : counter(initial) {}
};
/// ENUM DEF SPACE ///
enum class Priority
{
    LOW,
    MEDIUM,
    HIGH,
    CRITICAL
};