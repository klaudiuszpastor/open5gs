#include "abts.h"
#include <stdlib.h>
#include <stdio.h>

abts_suite *test_ogs_ran_context(abts_suite *suite);
abts_suite *test_ogs_ran_common(abts_suite *suite);

const struct testlist {
    abts_suite *(*func)(abts_suite *suite);
} alltests[] = {
    {test_ogs_ran_context},  
    {test_ogs_ran_common},  
    {NULL}  
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

