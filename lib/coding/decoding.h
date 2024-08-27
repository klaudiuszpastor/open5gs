#ifndef DECODING_H
#define DECODING_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t decode_with_crc(const uint8_t* input, uint32_t input_size, uint8_t* output, uint32_t* output_size, uint32_t polynomial, uint8_t crc_size);

#ifdef __cplusplus
}
#endif

#endif // DECODING_H
