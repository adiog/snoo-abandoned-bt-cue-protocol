#ifndef EMBED_USART_PROTOCOL_H
#define EMBED_USART_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

extern const uint8_t PACKET_HEADER_START_MARKER;

extern const uint8_t HEADER_START_MARKER_OFFSET;
extern const uint8_t HEADER_PAYLOAD_CRC_OFFSET;
extern const uint8_t HEADER_PAYLOAD_ID_OFFSET;
extern const uint8_t HEADER_PAYLOAD_LENGTH_OFFSET;

typedef enum {
    PAYLOAD_PING = 0x00U,
    PAYLOAD_PONG = 0x01U,
    PAYLOAD_SENSOR = 0x02U
} PayloadId;


extern const uint8_t payloadLengthById[8];
extern const uint8_t packetLengthById[8];

typedef struct
{
    uint8_t startMarker;
    uint8_t payloadCrc;
    uint8_t payloadId;
    uint8_t payloadLength;
} __attribute__((packed)) PacketHeader;


typedef struct
{
    uint8_t ping;
} __attribute__((packed)) PingPayload;

typedef struct
{
    PacketHeader header;
    PingPayload payload;
} __attribute__((packed)) PingPacket;

typedef struct
{
    uint8_t pong;
} __attribute__((packed)) PongPayload;

typedef struct
{
    PacketHeader header;
    PongPayload payload;
} __attribute__((packed)) PongPacket;

typedef struct
{
    float accelerometerMSS[3];
    float gyroscopeRads[3];
    float magnetometerMicroT[3];
    float temperatureCelcius;
} __attribute__((packed)) SensorPayload;

typedef struct
{
    PacketHeader header;
    SensorPayload payload;
} __attribute__((packed)) SensorPacket;

typedef void (*processIncomingPacket_t)(const uint8_t *);

int verifyPacket(const uint8_t *packet);

uint8_t getPacketLength(const uint8_t *packet);

void setHeader(uint8_t *buffer, uint8_t payloadId);

void processIncomingByte(
    uint8_t *buffer,
    uint8_t *bufferIndex,
    uint8_t bufferSize,
    uint32_t systemClockMillis,
    uint8_t incomingByte,
    processIncomingPacket_t processIncomingPacket);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
void processIncomingBuffer(
    uint8_t *buffer,
    uint8_t bufferSize,
    processIncomingPacket_t processIncomingPacket);
#endif

#endif
