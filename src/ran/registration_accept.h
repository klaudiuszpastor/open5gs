#ifndef registration_accept_h

#ifdef __cplusplus

extern "C" {

#endif

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ogs-core.h"
#include "ran/ogs-ran-rrc.h"

void Initial_Context_Setup_Request(registrationAccept_t*, uint32_t, uint32_t);
void run_Initial_Context_Setup_Request(registrationAccept_t*, uint32_t, uint32_t);

#ifdef __cplusplus
}
#endif

#endif //registration_accept_h



