#include "encoding.h"

// Function to calculate CRC based on the given 3GPP polynomial
uint32_t calculate_crc(const uint8_t* data, uint32_t length, uint32_t polynomial, uint8_t crc_size) {
    ogs_assert(data != NULL);
    ogs_assert(length > 0);
    
    uint32_t crc = CRC_INITIAL_VALUE >> (BITS_IN_WORD - crc_size);
    uint32_t i;
    uint8_t j;

    ogs_debug("Initial CRC value: 0x%08X", crc);

    for (i = 0; i < length; i++) {
        crc ^= ((uint32_t)data[i]) << (crc_size - BITS_IN_BYTE);

        for (j = 0; j < BITS_IN_BYTE; j++) {
            if (crc & (1 << (crc_size - 1))) {
                crc = (crc << 1) ^ polynomial;
            } else {
                crc = crc << 1;
            }
        }
        ogs_trace("CRC after processing byte %u: 0x%08X", i, crc);
    }

    crc &= ((1 << crc_size) - 1);
    ogs_debug("Final CRC value: 0x%08X", crc);

    return crc;
}

// Function to encode data with CRC
uint32_t encode_with_crc(const uint8_t* input, uint32_t input_size, uint8_t* output, uint32_t* output_size, uint32_t polynomial, uint8_t crc_size) {
    ogs_assert(input != NULL);
    ogs_assert(output != NULL);
    ogs_assert(output_size != NULL);
    ogs_assert(*output_size >= input_size + crc_size / BITS_IN_BYTE);

    ogs_info("Encoding data with CRC, input size: %u bytes, CRC size: %u bits", input_size, crc_size);

    uint32_t i;
    uint8_t j;

    for (i = 0; i < input_size; i++) {
        output[i] = input[i];
    }

    uint32_t crc = calculate_crc(input, input_size, polynomial, crc_size);

    for (j = 0; j < crc_size / BITS_IN_BYTE; j++) {
        output[input_size + j] = (crc >> ((crc_size / BITS_IN_BYTE - 1 - j) * BITS_IN_BYTE)) & 0xFF;
    }

    *output_size = input_size + crc_size / BITS_IN_BYTE;

    ogs_info("CRC encoding completed, output size: %u bytes", *output_size);  

    return OGS_OK; 
}
