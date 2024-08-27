#include "decoding.h"
#include "encoding.h" 

// Function to decode data and verify CRC
uint32_t decode_with_crc(const uint8_t* input, uint32_t input_size, uint8_t* output, uint32_t* output_size, uint32_t polynomial, uint8_t crc_size) {
    ogs_assert(input != NULL);
    ogs_assert(output != NULL);
    ogs_assert(output_size != NULL);

    ogs_info("Decoding data with CRC, input size: %u bytes, CRC size: %u bits", input_size, crc_size);
    
    if (input_size <= crc_size / BITS_IN_BYTE) {
        ogs_error("Input size is too small to contain CRC.");
        return OGS_ERROR;
    }

    uint32_t data_size = input_size - crc_size / BITS_IN_BYTE;
    uint8_t j;

    memcpy(output, input, data_size);

    uint32_t calculated_crc = calculate_crc(output, data_size, polynomial, crc_size);

    uint32_t received_crc = 0;
    for (j = 0; j < crc_size / BITS_IN_BYTE; j++) {
        received_crc |= ((uint32_t)input[data_size + j]) << ((crc_size / BITS_IN_BYTE - 1 - j) * BITS_IN_BYTE);
    }

    if (calculated_crc != received_crc) {
        ogs_error("CRC mismatch: calculated 0x%08X, received 0x%08X.",calculated_crc, received_crc);
        return OGS_ERROR;
    }
    *output_size = data_size;

    ogs_info("CRC decoding successful, output size: %u bytes", *output_size);

    return OGS_OK; 
}
