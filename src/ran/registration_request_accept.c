#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "registration_request_accept.h"
#include "substitute_AMF.h"
#include "substitute_AMF.c"
#include "rrc_establishment.c"

    //from gNB/RRC to AMF(L3) via NGAP_Initial_UE_Message:

    void NGAP_Initial_UE_Message(nas_registration_request_t registrationRequest, uint8_t establishmentCause, uint32_t RAN_UE_NGAP_ID){
        receive_NGAP_Initial_UE_Message(registrationRequest, establishmentCause, RAN_UE_NGAP_ID)
    }

    void run_NGAP_Initial_UE_Message(nas_registration_request_t registrationRequest, uint8_t establishmentCause){
        uint32_t RAN_UE_NGAP_ID = 4294967295;
        NGAP_Initial_UE_Message(registrationRequest, establishmentCause, RAN_UE_NGAP_ID)
    }

    //from AMF to gNB/RRC by Initial Context Setup Request
    void run_registration_accept_t_to(nas_registration_request_t registrationRequest, uint8_t establishmentCause){
        uint32_t RAN_UE_NGAP_ID = 4294967295;
        NGAP_Initial_UE_Message(registrationRequest, establishmentCause, RAN_UE_NGAP_ID)
    }

    void receive_Initial_Context_Setup_Request(){

    }

    //Michal: you have to run my function in gNB, from your RRC
    //insert this code into your (probably) rrc_establishment.c:
    #include "registration_request_accept.c"
    void RRCSetupComplete(nas_registration_request_t registrationRequest, uint8_t rrc_setup_complete_t.establishmentCause){
        run_NGAP_Initial_UE_Message(registrationRequest, rrc_setup_complete_t.establishmentCause);
    }




