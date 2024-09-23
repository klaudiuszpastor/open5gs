#include "ogs-core.h"
#include "context.h"
#include "context.h"
#include <stdio.h>
#include <stdlib.h>  

#define MAC_SDU_BUFFER_SIZE 16
#define MAC_PDU_BUFFER_SIZE 16
#define RLC_SDU_BUFFER_SIZE 16
#define RLC_PDU_BUFFER_SIZE 16
#define PDCP_SDU_BUFFER_SIZE 16
#define PDCP_PDU_BUFFER_SIZE 16
#define SDAP_BUFFER_SIZE 16
#define PHY_BUFFER_SIZE 16

#define DEFAULT_LOGICAL_CHANNEL LOGICAL_CHANNEL_DCCH
#define DEFAULT_TRANSPORT_CHANNEL TRANSPORT_CHANNEL_DL_SCH
#define DEFAULT_RLC_MODE RLC_MODE_AM
#define DEFAULT_MODULATION_SCHEME 0  
#define DEFAULT_FREQUENCY 3600       
#define DEFAULT_TX_POWER 23          
#define DEFAULT_QFI 0
#define DEFAULT_HARQ_PROCESS_ID 0
#define DEFAULT_RETRANSMISSION_COUNT 0
#define DEFAULT_ARQ_ENABLED true
#define DEFAULT_SEGMENTATION_ENABLED true
#define DEFAULT_REASSEMBLY_ENABLED true
#define DEFAULT_ROHC_ENABLED false
#define DEFAULT_CIPHERING_ENABLED true
#define DEFAULT_INTEGRITY_PROTECTION_ENABLED true
#define DEFAULT_SIGNAL_SHAPED false
#define DEFAULT_IS_CONTROL_PLANE false
#define DEFAULT_SEQUENCE_NUMBER 0

void ogs_ran_mac_init(mac_entity_t *mac_entity) {
    ogs_assert(mac_entity != NULL);

    mac_entity->macConfig.logicalChannelId = DEFAULT_LOGICAL_CHANNEL;
    mac_entity->macConfig.transportChannelId = DEFAULT_TRANSPORT_CHANNEL;
    mac_entity->macConfig.priority = 0;
    mac_entity->macConfig.lcGroup = 0;
    mac_entity->macConfig.schedulingRequestConfig = 0;
}


void ogs_ran_rlc_init(rlc_entity_t *rlc_entity) {
    ogs_assert(rlc_entity != NULL);

    rlc_entity->rlcConfig.rlcMode = DEFAULT_RLC_MODE;
    rlc_entity->rlcConfig.snFieldLength = 0;
    rlc_entity->rlcConfig.reorderingEnabled = true;
    rlc_entity->rlcConfig.maxRetx = 0;
    rlc_entity->rlcConfig.pollPdu = 0;
    rlc_entity->rlcConfig.pollByte = 0;
    rlc_entity->rlcConfig.pollRetransmit = 0;
}

void ogs_ran_pdcp_init(pdcp_entity_t *pdcp_entity) {
    ogs_assert(pdcp_entity != NULL);

    pdcp_entity->pdcpConfig.pdcpSNSizeUL = 0;
    pdcp_entity->pdcpConfig.pdcpSNSizeDL = 0;
    pdcp_entity->pdcpConfig.integrityProtection = DEFAULT_INTEGRITY_PROTECTION_ENABLED;
    pdcp_entity->pdcpConfig.cipheringAlgorithm = 0;
}

void ogs_ran_sdap_init(sdap_entity_t *sdap_entity) {
    ogs_assert(sdap_entity != NULL);

    sdap_entity->h.data = (uint8_t *)malloc(SDAP_BUFFER_SIZE);
    ogs_assert(sdap_entity->h.data != NULL);
    sdap_entity->h.size = 0;
    sdap_entity->qfi = DEFAULT_QFI;
}

void ogs_ran_phy_init(phy_entity_t *phy_entity) {
    ogs_assert(phy_entity != NULL);

    phy_entity->h.data = (uint8_t *)malloc(PHY_BUFFER_SIZE);
    ogs_assert(phy_entity->h.data != NULL);
    phy_entity->h.size = 0;
    phy_entity->prb_allocation = 0;
    phy_entity->modulation_scheme = DEFAULT_MODULATION_SCHEME;
    phy_entity->frequency = DEFAULT_FREQUENCY;
    phy_entity->tx_power = DEFAULT_TX_POWER;
    phy_entity->is_signal_shaped = DEFAULT_SIGNAL_SHAPED;
}
