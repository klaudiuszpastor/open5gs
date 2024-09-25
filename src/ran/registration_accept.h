#ifndef substitute_gNB_H

#ifdef __cplusplus

extern "C" {

#endif

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "rrc_establishment.c"
#include "rrc_reconfiguration.c"

void run_NGAP_Initial_UE_Message(void NGAP_Initial_UE_Message, nas_registration_request_t, uint8_t);
void NGAP_Initial_UE_Message(registrationRequest, establishmentCause, RAN_UE_NGAP_ID);

void run_Initial_Context_Setup_Request(registrationAccept_t *registrationAccept, uint32_t *AMF_UE_NGAP_ID, uint32_t *RAN_UE_NGAP_ID)




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

#endif //substitute_gNB_H



