#include "core/abts.h"

abts_suite *run_encoding_tests(abts_suite *suite);
abts_suite *run_decoding_tests(abts_suite *suite);

abts_suite *test_crc_encoding_suite(abts_suite *suite) {
    suite = run_encoding_tests(suite);
    return suite;
}

abts_suite *test_crc_decoding_suite(abts_suite *suite) {
    suite = run_decoding_tests(suite);
    return suite;
}

const struct testlist {
    abts_suite *(*func)(abts_suite *suite);
} alltests[] = {
    {test_crc_decoding_suite},  
    {test_crc_encoding_suite},  
    {NULL},
};

int main(int argc, const char *const argv[]) {
    int rv, i;
    const char *argv_out[argc+3]; 

    abts_suite *suite = NULL;

    rv = abts_main(argc, argv, argv_out);
    if (rv != 0) return rv;

    for (i = 0; alltests[i].func; i++) {
        suite = alltests[i].func(suite);
    }

    return abts_report(suite);
}
