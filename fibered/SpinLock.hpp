#ifndef SPINLOCK_HPP
#define SPINLOCK_HPP

#include <atomic>

class SpinLock {
    std::atomic<bool> lock = false;
public:
    void Acquire() {
        while(true) {
            while(lock) {
                _mm_pause();
            }
            //exit if state change
            if(!lock.exchange(true))
                break;
        }
    }
    void Release() {
        lock.store(false);
    }
};

#endif