#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "ran/ogs-ran-rrc.h"
#include "ogs-core.h"

void send_message_to_mac(rrc_message_type_t msg_type, void* msg, uint16_t msg_size) {
    ogs_assert(msg != NULL);
    ogs_info("Sending message type %d to UE via MAC layer", msg_type);
}

void* receive_message_from_ue(rrc_message_type_t* msg_type) {
    ogs_info("Receiving message from UE");

    static rrc_setup_request_t received_setup_request = {
        .ueIdentity = { .mmeCode = 0x1234, .mTmsi = 0x56789 },
        .establishmentCause = 0x01
    };

    static rrc_setup_complete_t received_setup_complete = {
        .NASMessage = {
            .messageType = NAS_REGISTRATION_REQUEST,  
            .protocolDiscriminator = 0x07,
            .registrationRequest = {
                .ueIdentity = 0x44,
                .capability = 0x22,
                .requestedNSSAI = 0x10
            }
        }
    };

    static uint8_t step = 0;

    if (step == 0) {
        *msg_type = RRC_SETUP_REQUEST; 
        step++;
        return &received_setup_request;
    } else if (step == 1) {
        *msg_type = RRC_SETUP_COMPLETE;  
        step++;
        return &received_setup_complete;
    }

    return NULL; 
}

void handle_rrc_setup_request(rrc_setup_request_t* setup_request) {
    ogs_info("Handling RRC Setup Request");

    ogs_info("UE Identity: MME Code: 0x%x, M-TMSI: 0x%x", 
              setup_request->ueIdentity.mmeCode, setup_request->ueIdentity.mTmsi);
    ogs_info("Establishment Cause: 0x%x", setup_request->establishmentCause);

    ogs_debug("Preparing RRC Setup response");
    
    rrc_setup_t rrcSetup;
    memset(&rrcSetup, 0, sizeof(rrcSetup));

    rrcSetup.radioBearerConfig.macConfig.logicalChannelId = 3;  
    rrcSetup.radioBearerConfig.macConfig.priority = 1;
    rrcSetup.radioBearerConfig.macConfig.lcGroup = 0;
    rrcSetup.radioBearerConfig.pdcpConfig.pdcpSNSizeDL = 11;
    rrcSetup.radioBearerConfig.pdcpConfig.pdcpSNSizeUL = 11;
    rrcSetup.radioBearerConfig.pdcpConfig.cipheringAlgorithm = 2;
    rrcSetup.radioBearerConfig.pdcpConfig.integrityProtection = 1;




    send_message_to_mac(RRC_SETUP, &rrcSetup, sizeof(rrcSetup));
}

void handle_rrc_setup_complete(rrc_setup_complete_t* setup_complete) {
    ogs_info("Handling RRC Setup Complete");

    ogs_info("NAS Message Type: 0x%x", setup_complete->NASMessage.messageType);
    
    // Sprawdzenie, czy wiadomość NAS to Registration Request
    if (setup_complete->NASMessage.messageType == NAS_REGISTRATION_REQUEST) {
        ogs_info("Processing NAS Registration Request within RRC Setup Complete.");
        nas_registration_request_t *registration_request = &setup_complete->NASMessage.registrationRequest;
        
        ogs_info("UE Identity: 0x%x", registration_request->ueIdentity);
        ogs_info("UE Capability: 0x%x", registration_request->capability);
        ogs_info("Requested NSSAI: 0x%x", registration_request->requestedNSSAI);
        
        ogs_info("Registration complete.");
    } else {
        ogs_info("NAS message is not a Registration Request.");
    }
}

void rrc_dispatch_message(rrc_message_type_t msg_type, void* msg, uint16_t msg_size) {
    ogs_assert(msg != NULL);

    if (msg_size < sizeof(rrc_setup_request_t) && msg_type == RRC_SETUP_REQUEST) {
        ogs_error("Invalid message size for RRC_SETUP_REQUEST");
        return;
    }

    if (msg_size < sizeof(rrc_setup_complete_t) && msg_type == RRC_SETUP_COMPLETE) {
        ogs_error("Invalid message size for RRC_SETUP_REQUEST");
        return;
    }

    switch (msg_type) {
        case RRC_SETUP_REQUEST:
            ogs_info("RRC Setup Request received");
            handle_rrc_setup_request((rrc_setup_request_t*)msg);
            break;

        case RRC_SETUP_COMPLETE:
            ogs_info("RRC Setup Complete received");
            handle_rrc_setup_complete((rrc_setup_complete_t*)msg);
            break;

        default:
            ogs_error("Unknown RRC message type received: %d", msg_type);
            break;
    }
}

void rrc_connection_establishment(void) {
    rrc_message_type_t received_msg_type;
    void* received_msg;

    received_msg = receive_message_from_ue(&received_msg_type);
    if (received_msg != NULL && received_msg_type == RRC_SETUP_REQUEST) {
        rrc_dispatch_message(received_msg_type, received_msg, sizeof(received_msg));

        ogs_info("Waiting for RRC Setup Complete from UE...");

        received_msg = receive_message_from_ue(&received_msg_type);
        if (received_msg != NULL && received_msg_type == RRC_SETUP_COMPLETE) {
            rrc_dispatch_message(received_msg_type, received_msg, sizeof(received_msg));
        } else {
            ogs_error("Failed to receive RRC Setup Complete from UE");
        }
    } else {
        ogs_error("Failed to receive RRC Setup Request from UE");
    }
}
