#include <stdint.h>
#include "rrc_ver2.h"
#include "ogs-core.h"
#include "context.h"

void configure_pdcp(pdcp_config_t *pdcpConfig) {
    ogs_debug("Configuring PDCP Layer:\n");

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
    ogs_debug("Configuring RLC Layer:\n");

    rlcConfig->rlcMode = 1;
    rlcConfig->maxRetx = 4;
    rlcConfig->snFieldLength = 30;
    rlcConfig->PollRetransmit = 50;
    rlcConfig->pollByte = 1;
    rlcConfig->pollPdu = 2;

    ogs_info("RLC Mode: %d\n", rlcConfig->rlcMode);
    ogs_info("Max Retransmissions: %d\n", rlcConfig->maxRetx);
    ogs_info("PollRetransmit: %d\n", rlcConfig->PollRetransmit);
    ogs_info("pollByte: %d\n", rlcConfig->pollByte);
    ogs_info("pollPdu: %d\n", rlcConfig->pollPdu);
}

void configure_mac(mac_config_t *macConfig) {
    ogs_debug("Configuring MAC Layer:\n");
    rbConfig.macConfig.priority = 5;
    rbConfig.macConfig.lchGroup = 1;
    rbConfig.macConfig.schedulingRequestConfig = 1;
    rbConfig.macConfig.logicalChannelConfig = 1;
    
    ogs_info("Logical Channel id: %d\n", macConfig->logicalChannelId);
    ogs_info("Priority: %d\n", macConfig->priority);
    ogs_info("Logical Channel Group: %d\n", macConfig->lchGroup);
    ogs_info("Scheduling Request Config: %d\n", macConfig->schedulingRequestConfig);
    
}

void rrc_reconfiguration(rb_config_t *rbConfig) {
    rbConfig->rbId = 1;

    ogs_info("Starting RRC Reconfiguration for RB ID: %d\n", rbConfig->rbId);
    
    configurePDCP(&rbConfig->pdcpConfig);
    
    configureRLC(&rbConfig->rlcConfig);
    
    configureMAC(&rbConfig->macConfig);
    
    ogs_info("RRC Reconfiguration for RB ID %d completed.\n", rbConfig->rbId);
}