#include "registration_request.h"
#include "registration_accept.h"

    //from gNB/RRC to AMF(L3) via NGAP_Initial_UE_Message:

    //The function below carries arguments to the AMF from rrc_establishment.c file and .
    void NGAP_Initial_UE_Message(nas_registration_request_t *registrationRequest, uint8_t establishmentCause, uint32_t RAN_UE_NGAP_ID){
        ogs_info("Registration Request is sending to AMF from gNB by NGAP_Initial_UE_Message");
        //receive_NGAP_Initial_UE_Message(registrationRequest, establishmentCause, RAN_UE_NGAP_ID) //to AMF

        AMF_temporary.AMF_registrationRequest = registrationRequest;
        AMF_temporary.AMF_establishmentCause = establishmentCause;
        AMF_temporary.AMF_RAN_UE_NGAP_ID = RAN_UE_NGAP_ID;
    }

    //The function below is lunched from rrc_establishment.c file.
    void run_NGAP_Initial_UE_Message(nas_registration_request_t *registrationRequest, uint8_t establishmentCause, uint32_t RAN_UE_NGAP_ID){
        ogs_info("Registration Request arrived from rrc_establishment.c file");
        NGAP_Initial_UE_Message(registrationRequest, establishmentCause, RAN_UE_NGAP_ID )
    }










