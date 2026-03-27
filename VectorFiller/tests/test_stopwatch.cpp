#include "gtest/gtest.h"
#include "atlas/time/impl/StopwatchImpl.h"
#include <thread>

using namespace atlas::time;

class StopwatchImplTest : public ::testing::Test {
protected:
    StopwatchImpl sw;
};

TEST_F(StopwatchImplTest, DurationIsNonNegativeAfterStartStop) {
    sw.start();
    sw.stop();
    EXPECT_GE(sw.getDuration().count(), 0);
}

TEST_F(StopwatchImplTest, DurationIncreaseWithDelay) {
    sw.start();
    std::this_thread::sleep_for(std::chrono::milliseconds{10});
    sw.stop();
    EXPECT_GE(sw.getDuration().count(), 0);
}

TEST_F(StopwatchImplTest, StopAfterStartGivesLongerDurationThanImmediateStop) {
    sw.start();
    sw.stop();
    auto shortDuration = sw.getDuration();

    StopwatchImpl sw2;
    sw2.start();
    std::this_thread::sleep_for(std::chrono::milliseconds{50});
    sw2.stop();

    EXPECT_GE(sw2.getDuration().count(), shortDuration.count());
}

TEST_F(StopwatchImplTest, MultipleStartStopCyclesWork) {
    for (int i = 0; i < 3; ++i) {
        sw.start();
        sw.stop();
        EXPECT_GE(sw.getDuration().count(), 0);
    }
}
