#include <stdint.h>
#include "ran/ogs-ran-rrc.h"
#include "ogs-core.h"
#include "ran/context.h"
#include "registration_accept.h"
#include "registration_request.h"

void send_rrc_reconfiguration_message(rb_config_t *rrcConfig) {
    ogs_info("Sending RRC Reconfiguration message to UE...");
    
    send_message_to_mac(RRC_RECONFIGURATION, rrcConfig, sizeof(*rrcConfig));

    ogs_info("RRC Reconfiguration message sent for RB ID: %d", rrcConfig->rbId);
}

void receive_registration_accept(registrationAccept_t* registrationAccept, uint32_t AMF_UE_NGAP_ID, uint32_t RAN_UE_NGAP_ID){
        //something
}

void configure_registration_acccept(nas_registration_accept_t registrationAccept){
    ogs_info("Configuring Registration Accept");
    registrationAccept.regAccept.out_of_scope_1 = 1;
    registrationAccept.out_of_scope_2 = 2;

    ogs_info("Configured Registration Accept: out_of_scope_1 = %d", registrationAccept.regAccept.out_of_scope_1);
    ogs_info("Configured Registration Accept: out_of_scope_2 = %d", registrationAccept.out_of_scope_2);
}

void configure_pdcp(pdcp_config_t *pdcpConfig) {
    ogs_info("Configuring PDCP Layer:\n");

    pdcpConfig->pdcpSNSizeUL = 12;
    pdcpConfig->pdcpSNSizeDL = 12;
    pdcpConfig->integrityProtection = 1;
    pdcpConfig->cipheringAlgorithm = 2;
    
    ogs_info("PDCP SN Size UL: %d\n", pdcpConfig->pdcpSNSizeUL);
    ogs_info("PDCP SN Size DL: %d\n", pdcpConfig->pdcpSNSizeDL);
    ogs_info("Integrity Protection: %d\n", pdcpConfig->integrityProtection);
    ogs_info("Ciphering Algorithm: %d\n", pdcpConfig->cipheringAlgorithm);
}

void configure_rlc(rlc_config_t *rlcConfig) {
    ogs_info("Configuring RLC Layer:\n");

    rlcConfig->rlcMode = 1;
    rlcConfig->maxRetx = 4;
    rlcConfig->snFieldLength = 30;
    rlcConfig->pollRetransmit = 50;
    rlcConfig->pollByte = 1;
    rlcConfig->pollPdu = 2;

    ogs_info("RLC Mode: %d\n", rlcConfig->rlcMode);
    ogs_info("Max Retransmissions: %d\n", rlcConfig->maxRetx);
    ogs_info("PollRetransmit: %d\n", rlcConfig->pollRetransmit);
    ogs_info("pollByte: %d\n", rlcConfig->pollByte);
    ogs_info("pollPdu: %d\n", rlcConfig->pollPdu);
}

void configure_mac(mac_config_t *macConfig) {
    ogs_info("Configuring MAC Layer:\n");
    macConfig->priority = 5;
    macConfig->lcGroup = 1;
    macConfig->schedulingRequestConfig = 1;
    macConfig->logicalChannelId = 1;
    
    ogs_info("Logical Channel id: %d\n", macConfig->logicalChannelId);
    ogs_info("Priority: %d\n", macConfig->priority);
    ogs_info("Logical Channel Group: %d\n", macConfig->lcGroup);
    ogs_info("Scheduling Request Config: %d\n", macConfig->schedulingRequestConfig);
    
}

void rrc_reconfiguration(rb_config_t *rbConfig) {
    rbConfig->rbId = 1;

    ogs_info("Starting RRC Reconfiguration for RB ID: %d\n", rbConfig->rbId);
    
    configure_pdcp(&rbConfig->pdcpConfig);
    
    configure_rlc(&rbConfig->rlcConfig);
    
    configure_mac(&rbConfig->macConfig);
    
    nas_registration_accept_t registrationAccept;
    memset(&registrationAccept, 0, sizeof(registrationAccept));
    configure_registration_acccept(registrationAccept);   

    rb_config_t rrcConfig;
    memset(&rrcConfig, 0, sizeof(rrcConfig));
    
    rrcConfig.rbId = rbConfig->rbId;
    rrcConfig.pdcpConfig = rbConfig->pdcpConfig;
    rrcConfig.rlcConfig = rbConfig->rlcConfig;
    rrcConfig.macConfig = rbConfig->macConfig;

    send_rrc_reconfiguration_message(&rrcConfig);
    
    ogs_info("RRC Reconfiguration for RB ID %d completed.\n", rbConfig->rbId);
}
