#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "registration_request.h"
#include "ogs-core.h"
#include "rrc_establishment.c"

    //from gNB/RRC to AMF(L3) via NGAP_Initial_UE_Message:

    //The function below carries arguments to the AMF from rrc_establishment.c file and .
    void NGAP_Initial_UE_Message(nas_registration_request_t *registrationRequest, uint8_t establishmentCause, uint32_t *RAN_UE_NGAP_ID){
        //receive_NGAP_Initial_UE_Message(registrationRequest, establishmentCause, RAN_UE_NGAP_ID) //to AMF

    }
    //The function below is lunched from rrc_establishment.c file.
    void run_NGAP_Initial_UE_Message(nas_registration_request_t *registrationRequest, uint8_t *establishmentCause){
        NGAP_Initial_UE_Message(registrationRequest, establishmentCause, &RAN_UE_NGAP_ID)
    }










