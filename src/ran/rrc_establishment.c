#include <stdint.h>
#include <stdbool.h>
#include "rrc.h"
#include "ogs-core.h"

void send_message_to_mac(rrc_message_type_t msg_type, void *msg, uint16_t msg_size) {
    ogs_assert(msg_type != NULL);
    ogs_info("Sending message type %d to MAC layer", msg_type);
}

void* receive_message_from_mac(rrc_message_type_t* msg_type) {
    *msg_type = RRC_SETUP;
    return NULL;
}

void rrc_connection_establishment(void) {
    //Initialize variables
    bool is_rrc_setup_complete = false;
    rrc_message_type_t received_msg_type;

    //Prepare and send RRCSetupRequest message
    rrc_setup_request_t rrcSetupRequest;
    memset(&rrcSetupRequest, 0, sizeof(rrcSetupRequest));

    //Set UE identity
    rrcSetupRequest.ueIdentity.mmeCode = 0x1234;  
    rrcSetupRequest.ueIdentity.mTmsi = 0x56789;   

    //Set establishment cause
    rrcSetupRequest.establishmentCause = 0x01; 

    ogs_debug("Sending RRCSetupRequest to MAC layer");
    send_message_to_mac(RRC_SETUP_REQUEST, &rrcSetupRequest, sizeof(rrcSetupRequest));

    void* received_msg = receive_message_from_mac(&received_msg_type);
    ogs_assert(received_msg != NULL);

    if (received_msg_type == RRC_SETUP) {
        ogs_info("RRCSetup message received.");

        //Prepare and send RRCSetupComplete message
        rrc_setup_complete_t rrcSetupComplete;
        memset(&rrcSetupComplete, 0, sizeof(rrcSetupComplete));

        //Set NAS dedicated information
        rrcSetupComplete.NASMessage.messageType = 0x01;
        rrcSetupComplete.NASMessage.protocolDiscriminator = 0x07;
        rrcSetupComplete.NASMessage.messageContent.attachRequest.epsMobileIdentity = 0x11;
        rrcSetupComplete.NASMessage.messageContent.attachRequest.ueNetworkCapability = 0x22;

        ogs_debug("Sending RRCSetupComplete to MAC layer");
        send_message_to_mac(RRC_SETUP_COMPLETE, &rrcSetupComplete, sizeof(rrcSetupComplete));

        is_rrc_setup_complete = true;

    } else {
        ogs_info("RRCSetup message not received");
    }

    if (is_rrc_setup_complete) {
        ogs_info("RRC connection established successfully");
    } else {
        ogs_info("RRC connection establishment failed");
    }
}
