#ifndef EMBED_USART_PROTOCOL_DEBUG_H
#define EMBED_USART_PROTOCOL_DEBUG_H


#ifdef __cplusplus
extern "C" {
#endif

#include <protocol.h>


int formatPacketHeader(char *outputBuffer, const uint8_t *packetHeader);

int formatSamplePayload(char *outputBuffer, const void *payload);

int formatPacket(char *outputBuffer, const uint8_t *packet);

#ifdef __cplusplus
}
#endif

#endif
