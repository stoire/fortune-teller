#include <unity.h>
#include <Arduino.h>

#include "utils.h"

void test_listSD(void) {
    String expected("/");
    String actual = listSD();

    TEST_ASSERT_EQUAL_STRING(expected.c_str(), actual.c_str());
}

void setup() {}

void loop() {
    UNITY_BEGIN();
    RUN_TEST(test_listSD);    
    UNITY_END(); 
}
