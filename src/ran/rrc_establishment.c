#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h> 
#include "ran/ogs-ran-rrc.h"
#include "ogs-core.h"

void send_message_to_mac(rrc_message_type_t msg_type, void* msg, uint16_t msg_size) {
    ogs_assert(msg != NULL);
    ogs_info("Sending message type %d to UE via MAC layer", msg_type);
}

void* receive_message_from_ue(rrc_message_type_t* msg_type) {
    ogs_info("Receiving message from UE");

    static uint8_t step = 0;

    if (step == 0) {
        static rrc_setup_request_t received_setup_request = {
            .ueIdentity = { .mmeCode = 0x1234, .mTmsi = 0x56789 },
        };
        *msg_type = RRC_SETUP_REQUEST; 
        step++;
        return &received_setup_request;
    } else if (step == 1) {
        static rrc_setup_complete_t received_setup_complete = {
            .NASMessage = {
                .messageType = NAS_REGISTRATION_REQUEST,  
                .protocolDiscriminator = 0x07,
                .registrationRequest = {
                    .ueIdentity = { .mmeCode = 0x1234, .mTmsi = 0x56789 },
                    .capability = 0x22,
                    .requestedNSSAI = 0x10
                }
            }
        };
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
        
        ogs_info("UE Identity: MME Code: 0x%x, M-TMSI: 0x%x", registration_request->ueIdentity.mmeCode,registration_request->ueIdentity.mTmsi);
        ogs_info("UE Capability: 0x%x", registration_request->capability);
        ogs_info("Requested NSSAI: 0x%x", registration_request->requestedNSSAI);
        
        ogs_info("Registration complete.");
    // Sprawdzenie, czy wiadomość NAS to Attach Request
    } else if (setup_complete->NASMessage.messageType == NAS_ATTACH_REQUEST) {
        ogs_info("Processing NAS Attach Request within RRC Setup Complete.");
        nas_attach_request_t *attach_request = &setup_complete->NASMessage.attachRequest;

        ogs_info("UE Identity: MME Code: 0x%x, M-TMSI: 0x%x", attach_request->epsMobileIdentity, setup_complete->ueIdentity.mTmsi);
        ogs_info("UE Network Capability: 0x%x", attach_request->ueNetworkCapability);

        initiate_authentication(setup_complete);
    } else {
        ogs_info("NAS message is not a Registration or Attach Request.");
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

