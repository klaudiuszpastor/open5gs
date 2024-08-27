#include "core/abts.h"
#include "coding/encoding.h"
#include "coding/decoding.h"

// Test decoding with CRC for a known valid input
void test_decode_with_crc(abts_case *tc, void *data) {
    uint8_t input[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC}; 
    uint8_t output[10];
    uint32_t output_size = sizeof(output);
    
    uint32_t result = decode_with_crc(input, sizeof(input), output, &output_size, CRC24A_POLYNOMIAL, 24);
    
    ABTS_INT_EQUAL(tc, OGS_OK, result);
    ABTS_INT_EQUAL(tc, output_size, sizeof(input) - 3); 
}

// Test decoding with CRC for input that has CRC mismatch
void test_decode_with_crc_mismatch(abts_case *tc, void *data) {
    uint8_t input[] = {0x12, 0x34, 0x56, 0xDE, 0xAD, 0xBE}; // Intentionally wrong CRC
    uint8_t output[10];
    uint32_t output_size = sizeof(output);
    
    uint32_t result = decode_with_crc(input, sizeof(input), output, &output_size, CRC24A_POLYNOMIAL, 24);
    
    ABTS_INT_EQUAL(tc, OGS_ERROR, result);
}

// Test decode_with_crc with insufficient input size
void test_decode_with_crc_insufficient_input(abts_case *tc, void *data) {
    uint8_t input[] = {0x12, 0x34}; // Too small to contain CRC
    uint8_t output[10];
    uint32_t output_size = sizeof(output);
    
    uint32_t result = decode_with_crc(input, sizeof(input), output, &output_size, CRC24A_POLYNOMIAL, 24);
    
    ABTS_INT_EQUAL(tc, OGS_ERROR, result);
}

// Main function to run the decoding tests
abts_suite *run_decoding_tests(abts_suite *suite) {
    suite = ADD_SUITE(suite);

    abts_run_test(suite, test_decode_with_crc, NULL);
    abts_run_test(suite, test_decode_with_crc_mismatch, NULL);
    abts_run_test(suite, test_decode_with_crc_insufficient_input, NULL);

    return suite;
}