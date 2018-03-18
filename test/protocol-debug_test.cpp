#include <googletest>
#include <protocol.h>
#include <protocol_debug.h>


TEST(protocol_debug, formatPingPacket)
{
    // given
    char buffer[256];
    PingPacket pingPacket = {0};
    setHeader((uint8_t *)&pingPacket, PAYLOAD_PING);

    // when
    int bufferSize = formatPacket(buffer, (uint8_t *)&pingPacket);

    // then
    EXPECT_EQ(bufferSize, 34U);
    EXPECT_STREQ(buffer, "0xFF 0x01 PAYLOAD_PING 0x01 [0x00]");
}

GTEST_MAIN()

