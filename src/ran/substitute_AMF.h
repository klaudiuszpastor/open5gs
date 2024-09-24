#ifndef substitute_AMF_H

#ifdef __cplusplus

extern "C" {

#endif

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rrc_establishment.c"

void receive_NGAP_Initial_UE_Message(nas_registration_request_t registrationRequest, uint8_t establishmentCause, uint32_t RAN_UE_NGAP_ID);


typedef struct registrationAccept_s{
    uint8_t out_of_limit;
} registrationAccept

typedef struct nas_registration_accept_s{
    registrationAccept
    uint8_t out_of_limit;
} nas_registration_accept_t



#ifdef __cplusplus
}
#endif

#endif //substitute_AMF_H



