#include "registration_accept.h"
#include "registration_request.h"

    //from AMF to gNB/RRC by Initial Context Setup Request

    void Initial_Context_Setup_Request(registrationAccept_t *registrationAccept, uint32_t AMF_UE_NGAP_ID, uint32_t RAN_UE_NGAP_ID){
        ogs_info("Registration Request arrived from rrc_establishment.c file");
        receive_registration_accept (registrationAccept, AMF_UE_NGAP_ID, RAN_UE_NGAP_ID); //funkcja wywolywana w rrc_reconfiguration.c
    }

    void run_Initial_Context_Setup_Request(registrationAccept_t *registrationAccept, uint32_t AMF_UE_NGAP_ID, uint32_t RAN_UE_NGAP_ID){
        ogs_info("Registration Request arrived from rrc_establishment.c file");
        Initial_Context_Setup_Request(registrationAccept, AMF_UE_NGAP_ID, RAN_UE_NGAP_ID);
    }

    //run_Initial_Context_Setup_Request(&registrationAccept, AMF_UE_NGAP_ID, RAN_UE_NGAP_ID);






