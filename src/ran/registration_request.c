#include "registration_request.h"
#include "registration_accept.h"
//from gNB/RRC to AMF(L3) via NGAP_Initial_UE_Message:

//The function below carries arguments to the AMF from rrc_establishment.c file and .
void NGAP_Initial_UE_Message(nas_registration_request_t *registrationRequest, uint8_t establishmentCause, uint32_t RAN_UE_NGAP_ID){
    //receive_NGAP_Initial_UE_Message(registrationRequest, establishmentCause, RAN_UE_NGAP_ID) //to AMF
    //AMF_temporary.AMF_registrationRequest = registrationRequest;
    //AMF_temporary.AMF_establishmentCause = establishmentCause;
}
//The function below is lunched from rrc_establishment.c file.
void run_NGAP_Initial_UE_Message(nas_registration_request_t *registrationRequest, uint8_t establishmentCause, uint32_t RAN_UE_NGAP_ID){
    NGAP_Initial_UE_Message(registrationRequest, establishmentCause, RAN_UE_NGAP_ID);
}










