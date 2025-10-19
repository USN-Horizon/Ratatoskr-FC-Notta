#include <Arduino.h>
#include <unity.h>
#include "SX1280.h"
#include "mocks/MockSPI.h"

MockSPI mockSPI;
SX1280 radio(&mockSPI);

void test_init_should_succeed() {
    bool ok = radio.begin();
    TEST_ASSERT_TRUE_MESSAGE(ok, "SX1280 should initialize correctly");
}

void test_send_packet_should_not_crash() {
    const uint8_t payload[] = {0x01, 0x02, 0x03};
    bool ok = radio.sendPacket(payload, sizeof(payload));
    TEST_ASSERT_TRUE_MESSAGE(ok, "Packet send should succeed");
}

void test_receive_packet_should_return_expected_data() {
    uint8_t buffer[3] = {0};
    bool ok = radio.receivePacket(buffer, sizeof(buffer));
    TEST_ASSERT_TRUE_MESSAGE(ok, "Receive should succeed");
    TEST_ASSERT_EQUAL_UINT8(0xA0, buffer[0]);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_init_should_succeed);
    RUN_TEST(test_send_packet_should_not_crash);
    RUN_TEST(test_receive_packet_should_return_expected_data);
    UNITY_END();
}

void loop() {}
