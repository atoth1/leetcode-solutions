// https://leetcode.com/problems/building-h2o/

#include <condition_variable>
#include <mutex>

namespace {
    bool h1Released = false;
    bool h2Released = false;
}

class H2O {
public:
    H2O() {
        
    }

    void hydrogen(function<void()> releaseHydrogen) {
        {
            std::unique_lock<std::mutex> lk(m);
            
            // releaseHydrogen() outputs "H". Do not change or remove this line.
            if (!h1Released) {
                releaseHydrogen();
                h1Released = true;
            } else if (!h2Released) {
                releaseHydrogen();
                h2Released = true;
            } else {
                cv.wait(lk, [] { return !(h1Released && h2Released); });
                lk.unlock();
                cv.notify_all();
                hydrogen(releaseHydrogen);
            }
        }
        cv.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
        {
            std::unique_lock<std::mutex> lk(m);
            cv.wait(lk, [] { return h1Released && h2Released; });
            
            // releaseOxygen() outputs "O". Do not change or remove this line.
            releaseOxygen();
            
            // Reset hydrogen flags;
            h1Released = false;
            h2Released = false;
        }
        cv.notify_all();
    }
    
private:
    std::mutex m;
    std::condition_variable cv;
};
