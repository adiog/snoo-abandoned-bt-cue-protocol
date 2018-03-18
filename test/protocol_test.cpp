#include <googletest>
#include <protocol.h>


TEST(protocol, setHeader_PAYLOAD_PING)
{
    // given
    PingPacket pingPacket = {0};

    // when
    setHeader((uint8_t *)&pingPacket, PAYLOAD_PING);

    // then
    EXPECT_EQ(pingPacket.header.startMarker, PACKET_HEADER_START_MARKER);
    EXPECT_EQ(pingPacket.header.payloadCrc, 0x01U);
    EXPECT_EQ(pingPacket.header.payloadId, PAYLOAD_PING);
    EXPECT_EQ(pingPacket.header.payloadLength, sizeof(PingPayload));
}

TEST(protocol, setHeader_verifyPacket)
{
    // given
    PingPacket pingPacket = {0};

    // when
    setHeader((uint8_t *)&pingPacket, PAYLOAD_PING);

    // then
    EXPECT_TRUE(verifyPacket((const uint8_t *)&pingPacket));
}

GTEST_MAIN()

