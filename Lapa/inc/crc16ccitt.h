#ifndef CRC16CCITT_H
#define CRC16CCITT_H

#include <main.h>

unsigned short get_crc16_ccitt(const uint32_t *buf, int len);
unsigned short get_crc16_ccitt_arr(const uint8_t *buf, int len);

#endif
