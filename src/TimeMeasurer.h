#ifndef _VRS_TIME_MEASURER_H_
#define _VRS_TIME_MEASURER_H_

#include <time.h>

namespace vrs {

class TimeMeasurer
{
public:
    TimeMeasurer()
    {
        clock_gettime(CLOCK_MONOTONIC, &last_saved_time_);
    }

    void diff_with_last_call_timespec(timespec& diff)
    {
        timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        ts_sub(now, last_saved_time_, diff);
        last_saved_time_ = now;
    }

    double diff_with_last_call_seconds()
    {
        timespec diff;
        diff_with_last_call_timespec(diff);
        return diff.tv_sec*1000000000
            + diff.tv_nsec/double(1000000000);
    }

    ~TimeMeasurer(){}

private:
    inline void ts_sub(const timespec& a, const timespec& b, timespec& result)
    {
        (result).tv_sec  = a.tv_sec  - b.tv_sec;
        (result).tv_nsec = a.tv_nsec - b.tv_nsec;

        if (result.tv_nsec < 0)
        {
            --(result.tv_sec);
            result.tv_nsec += 1000000000;
        }
    }

    timespec last_saved_time_;
};

} // vrs


#endif /* _VRS_TIME_MEASURER_H_ */
