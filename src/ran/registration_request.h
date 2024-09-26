#ifndef registration_request_h

#ifdef __cplusplus

extern "C" {

#endif

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ran/ogs-ran-rrc.h"
#include "ogs-core.h"

void NGAP_Initial_UE_Message(nas_registration_request_t*, uint8_t, uint32_t);
void run_NGAP_Initial_UE_Message(nas_registration_request_t*, uint8_t, uint32_t);

#ifdef __cplusplus
}
#endif

#endif //registration_request_h



