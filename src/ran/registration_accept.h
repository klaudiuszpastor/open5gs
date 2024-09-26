#ifndef registration_accept_h

#ifdef __cplusplus

extern "C" {

#endif

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "rrc_reconfiguration.c"

void Initial_Context_Setup_Request(registrationAccept_t, uint32_t, uint32_t);
void run_Initial_Context_Setup_Request(registrationAccept_t, uint32_t, uint32_t);


uint32_t RAN_UE_NGAP_ID = 4294967295;
uint32_t AMF_UE_NGAP_ID = 4294967294;

typedef struct registrationAccept_s{
    uint8_t out_of_scope_1;
}registrationAccept_t;

typedef struct nas_registration_accept_s{
    registrationAccept_t
    uint8_t out_of_scope_2;
}nas_registration_accept_t;

#ifdef __cplusplus
}
#endif

#endif //registration_accept_h



