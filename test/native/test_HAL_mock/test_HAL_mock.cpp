#include <unity.h>

#include "../lib/HAL/HAL_mock.h"

HAL* hal;

void setUp(void) {
   if (hal != nullptr) {
      delete hal;
   }

   hal = new HAL_mock();
}

void tearDown(void) {
   if (hal != nullptr) {
      delete hal;
   }
}

void test_HAL_initialization() {
   const bool result = hal->Begin();

   TEST_ASSERT_TRUE(result);
   TEST_ASSERT_TRUE(hal->Good());
}

int main() {
   UNITY_BEGIN();

   RUN_TEST(test_HAL_initialization);

   return UNITY_END();
}
