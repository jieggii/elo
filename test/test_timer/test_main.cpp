#include <cstdint>

#include <unity.h>

#include "Timer.h"

void test_Timer_fromSeconds() {
    const uint32_t now = 1000;
    const uint16_t timerDurationSeconds = 10;

    Timer timer = Timer::fromSeconds(timerDurationSeconds);
    timer.set(now);

    const uint32_t timeLeft = timer.left(now);

    TEST_ASSERT_EQUAL_UINT32(timerDurationSeconds * 1000, timeLeft);
}

void test_Timer_set() {
    const uint32_t now = 9999;
    const uint16_t timerDuration = 1000;
    const uint32_t expectedElapsed = 200;

    Timer timer = Timer(timerDuration);
    timer.set(now);

    const uint32_t elapsed = timer.elapsed(now + expectedElapsed);

    TEST_ASSERT_EQUAL_UINT32(expectedElapsed, elapsed);
}

/**
 * Test Timer.elapsed method.
 */
void test_Timer_elapsed() {
    const uint32_t now = 9999;
    const uint16_t timerDuration = 1000;

    const uint32_t expectedElapsed = 200;

    Timer timer = Timer(timerDuration);
    timer.set(now);

    const uint32_t elapsed = timer.elapsed(now + expectedElapsed);

    TEST_ASSERT_EQUAL_UINT32(expectedElapsed, elapsed);
}

/**
 * Test Timer.elapsed method, when timer is paused.
 */
void test_Timer_elapsed_paused() {
    const uint32_t now = 9999;
    const uint16_t timerDuration = 1000;
    const uint32_t expectedElapsed = 200;

    Timer timer = Timer(timerDuration);
    timer.set(now);

    timer.pause(now + expectedElapsed);

    const uint32_t elapsed = timer.elapsed(now + expectedElapsed + 100);

    TEST_ASSERT_EQUAL_UINT32(expectedElapsed, elapsed);
}

/**
 * Test Timer.elapsed method, when timer is paused, and then resumed.
 */
void test_Timer_elapsed_paused_resumed() {
    const uint32_t now = 1000;
    const uint16_t timerDuration = 1000;

    const uint32_t delta1 = 100;
    const uint32_t delta2 = 200;
    const uint32_t delta3 = 300;

    const uint32_t expectedElapsed = delta1 + delta3;

    Timer timer = Timer(timerDuration);
    timer.set(now);

    timer.pause(now + delta1);
    timer.resume(now + delta1 + delta2);

    const uint32_t elapsed = timer.elapsed(now + delta1 + delta2 + delta3);

    TEST_ASSERT_EQUAL_UINT32(expectedElapsed, elapsed);
}

void test_Timer_left() {
    const uint32_t now = 9999;
    const uint16_t timerDuration = 1000;
    const uint32_t elapsed = 200;

    const uint32_t expectedLeft = timerDuration - elapsed;

    Timer timer = Timer(timerDuration);
    timer.set(now);

    const uint32_t left = timer.left(now + elapsed);

    TEST_ASSERT_EQUAL_UINT32(expectedLeft, left);
}

/**
 * Test isExpired method, when elapsed more time, than timer duration.
 */
void test_Timer_isExpired_elapsed_more_time_than_timer_duration() {
    const uint32_t now = 9999;
    const uint16_t timerDuration = 1000;
    const uint32_t elapsed = timerDuration + 1;

    Timer timer = Timer(timerDuration);
    timer.set(now);

    TEST_ASSERT_TRUE(timer.isExpired(now + elapsed));
}

/**
 * Test isExpired method, when elapsed less time, than timer duration.
 */
void test_Timer_isExpired_elapsed_less_time_than_timer_duration() {
    const uint32_t now = 9999;
    const uint16_t timerDuration = 1000;
    const uint32_t elapsed = timerDuration - 1;

    Timer timer = Timer(timerDuration);
    timer.set(now);

    TEST_ASSERT_FALSE(timer.isExpired(now + elapsed));
}

/**
 * Test isExpired method, when elapsed equal time to the timer duration.
 */
void test_Timer_isExpired_elapsed_equal_time_to_timer_duration() {
    const uint32_t now = 9999;
    const uint16_t timerDuration = 1000;
    const uint32_t elapsed = timerDuration;

    Timer timer = Timer(timerDuration);
    timer.set(now);

    TEST_ASSERT_TRUE(timer.isExpired(now + elapsed));
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_Timer_fromSeconds);
    RUN_TEST(test_Timer_set);

    {  // Test Timer.elapsed method:
        RUN_TEST(test_Timer_elapsed);
        RUN_TEST(test_Timer_elapsed_paused);
        RUN_TEST(test_Timer_elapsed_paused_resumed);
    }

    RUN_TEST(test_Timer_left);

    {  // Test Timer.isExpired method:
        RUN_TEST(test_Timer_isExpired_elapsed_more_time_than_timer_duration);
        RUN_TEST(test_Timer_isExpired_elapsed_less_time_than_timer_duration);
        RUN_TEST(test_Timer_isExpired_elapsed_equal_time_to_timer_duration);
    }

    return UNITY_END();
}
