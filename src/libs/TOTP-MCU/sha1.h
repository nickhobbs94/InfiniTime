#ifndef SHA1_H_
#define SHA1_H_

#include <inttypes.h>

#define HASH_LENGTH 20
#define BLOCK_LENGTH 64

void init(void);
void initHmac(const uint8_t* secret, uint8_t secretLength);
uint8_t* result(void);
uint8_t* resultHmac(void);
void writeArray(uint8_t *buffer, uint8_t size);

#endif // SHA1_H
