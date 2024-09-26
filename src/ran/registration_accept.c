#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "registration_accept.h"
#include "registration_request.h"
#include "ogs-core.h"
#include "rrc_reconfiguration.c"

    //from AMF to gNB/RRC by Initial Context Setup Request

    void Initial_Context_Setup_Request(registrationAccept_t registrationAccept, uint32_t AMF_UE_NGAP_ID, uint32_t RAN_UE_NGAP_ID){
        rrc_reconfiguration_from_gNB(registrationAccept, AMF_UE_NGAP_ID, RAN_UE_NGAP_ID); //funkcja wywolywana w rrc_reconfiguration.c
    }

    void run_Initial_Context_Setup_Request(registrationAccept_t *registrationAccept, uint32_t *AMF_UE_NGAP_ID, uint32_t *RAN_UE_NGAP_ID){
        Initial_Context_Setup_Request(registrationAccept, AMF_UE_NGAP_ID, RAN_UE_NGAP_ID);
    }

    run_Initial_Context_Setup_Request(&registrationAccept, &AMF_UE_NGAP_ID, &RAN_UE_NGAP_ID);






