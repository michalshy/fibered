#ifndef FIBEREDTYPES_HPP
#define FIBEREDTYPES_HPP

#include <atomic>

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

#endif // FIBEREDTYPES_HPP