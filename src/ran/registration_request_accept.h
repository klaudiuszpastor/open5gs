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

void run_NGAP_Initial_UE_Message(void *NGAP_Initial_UE_Message, nas_registration_request_t registrationRequest, uint8_t establishmentCause);
void NGAP_Initial_UE_Message(registrationRequest, establishmentCause, RAN_UE_NGAP_ID);


#ifdef __cplusplus
}
#endif

#endif //substitute_gNB_H



