#include "core/abts.h"
#include "coding/encoding.h"

// Test CRC calculation for a known input and polynomial
void test_calculate_crc(abts_case *tc, void *data) {
    uint8_t input[] = {0xAB, 0xCD, 0xEF};
    uint32_t expected_crc = 0x123456; 
    uint32_t actual_crc = calculate_crc(input, sizeof(input), CRC24A_POLYNOMIAL, 24);
    
    ABTS_INT_EQUAL(tc, expected_crc, actual_crc);
}

// Test encoding with CRC for a known input
void test_encode_with_crc(abts_case *tc, void *data) {
    uint8_t input[] = {0x12, 0x34, 0x56};
    uint8_t output[10];
    uint32_t output_size = sizeof(output);
    
    uint32_t result = encode_with_crc(input, sizeof(input), output, &output_size, CRC24A_POLYNOMIAL, 24);
    
    ABTS_INT_EQUAL(tc, OGS_OK, result);
    ABTS_INT_EQUAL(tc, output_size, sizeof(input) + 3);
}

// Test encode_with_crc with insufficient output buffer size
void test_encode_with_crc_insufficient_buffer(abts_case *tc, void *data) {
    uint8_t input[] = {0x12, 0x34, 0x56};
    uint8_t output[5]; // Intentionally small buffer
    uint32_t output_size = sizeof(output);
    
    uint32_t result = encode_with_crc(input, sizeof(input), output, &output_size, CRC24A_POLYNOMIAL, 24);
    
    ABTS_INT_EQUAL(tc, OGS_ERROR, result); 
}

// Main function to run the encoding tests
abts_suite *run_encoding_tests(abts_suite *suite) {
    suite = ADD_SUITE(suite);

    abts_run_test(suite, test_calculate_crc, NULL);
    abts_run_test(suite, test_encode_with_crc, NULL);
    abts_run_test(suite, test_encode_with_crc_insufficient_buffer, NULL);

    return suite;
}
