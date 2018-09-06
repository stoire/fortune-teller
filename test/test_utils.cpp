#include <unity.h>
#include <Arduino.h>

#include "sd_handler.h"
#include "utils.h"


void test_listSD(void) {
    String expected("/\n");    
    cleanSD();
    String actual = listSD();

    TEST_ASSERT_EQUAL_STRING(expected.c_str(), actual.c_str());
}

void test_writer(void) {
    cleanSD();

    SDWriter writer(SD_PIN);
    writer.begin();
    writer.write<String>("dummy", "test.txt");
    
    SDReader reader(SD_PIN);
    reader.begin(); 
    String actual = reader.readfile("test.txt");
    String expected = String("------\ntest.txt:\ndummy\n------\n");    
}

void setup() {}

void loop() {
    UNITY_BEGIN();
    RUN_TEST(test_listSD);
    RUN_TEST(test_writer);    
    UNITY_END(); 
}
