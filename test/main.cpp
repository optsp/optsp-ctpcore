#include "test_logger.h"
#include "test_arch.h"
#include "test_config.h"
#include "test_callback.h"
#include "test_platctp.h"
#include "../include/magic.hpp"
#include <gtest/gtest.h>

/// TEST ORDER
///        arch            accepted - 2018/12/23 17:22:00
///        config            accepted - 2018/12/23 17:22:00
///        logger            accepted - 2018/12/23 21:18:00
///        platctp
///        stgroup
///        stdemo
///        master

#ifndef _OPTSP_CTPCORE_GTEST_BE_TESTED_
///lib test
///accepted - 2018/12/23 17:22:00
TEST(test_arch, test_arch_case_1) {
    ASSERT_TRUE(test_arch_GetHomePath());
    ASSERT_TRUE(test_arch_Sleep());
    ASSERT_TRUE(test_arch_GetTimeStamp());
    ASSERT_TRUE(test_arch_Str2TimeStamp());
    ASSERT_TRUE(test_arch_TimeStamp2Str());
}

///config test
///accepted - 2018/12/23 17:22:00
///update - 2019/01/09 13:56:00
TEST(test_config, test_config_case_1) {
    ASSERT_TRUE(test_Config());
}

///logger function test
///accepted - 2018/12/23 21:18:00
TEST(test_logger, test_logger_case_1) {
    ASSERT_EQ(0, test_Logger_level_off());
    ASSERT_EQ(100, test_Logger_level_error(100));
    ASSERT_EQ(100, test_Logger_level_warning(100));
    ASSERT_EQ(100, test_Logger_level_info(100));
    ASSERT_EQ(100, test_Logger_level_debug(100));
    ASSERT_EQ(100, test_Logger_level_trace(100));
}

///logger stress test
///accepted - 2018/12/23 21:18:00
TEST(test_logger, test_logger_case_2) {
    ASSERT_EQ(1000, test_Logger_stress_test(1000));
}

///tech. callback test
///accepted - 2018/12/23 22:44:00
TEST(test_callback, test_callback_case_1) {
    ASSERT_EQ(1000, test_Callback(1000));
}
#endif

///platctp: quotespi & quoteapi test
///accepted - 2019/01/09 14:56:00
TEST(test_platctp, test_platctp_case_1) {
    ASSERT_TRUE(test_PlatCtp());
}

int main(int argc, char**argv) {
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    getchar();
    return ret;
}