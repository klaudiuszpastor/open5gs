#ifndef ENCODING_H
#define ENCODING_H

#include <bits/stdint-uintn.h>
#include "core/ogs-core.h"

#ifdef __cplusplus
extern "C" {
#endif

// Definitions of CRC polynomials as specified by 3GPP 38.212
#define CRC24A_POLYNOMIAL 0x864CFB
#define CRC24B_POLYNOMIAL 0x800063
#define CRC24C_POLYNOMIAL 0xD58237
#define CRC16_POLYNOMIAL  0x1021
#define CRC11_POLYNOMIAL  0x385
#define CRC6_POLYNOMIAL   0x27

#define CRC_INITIAL_VALUE 0xFFFFFFFF  

// CRC sizes 
#define CRC_SIZE_24_BITS 24
#define CRC_SIZE_16_BITS 16
#define CRC_SIZE_11_BITS 11
#define CRC_SIZE_6_BITS 6

#define BITS_IN_BYTE 8  
#define BITS_IN_WORD 32  

uint32_t calculate_crc(const uint8_t* data, uint32_t length, uint32_t polynomial, uint8_t crc_size);

uint32_t encode_with_crc(const uint8_t* input, uint32_t input_size, uint8_t* output, uint32_t* output_size, uint32_t polynomial, uint8_t crc_size);

#ifdef __cplusplus
}
#endif

#endif // ENCODING_H
