#include "ogs-core.h"
#include "context.h"
#include "context.h"
#include <stdio.h>
#include <stdlib.h>  

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

    sdap_entity->h.size = 0;
    sdap_entity->qfi = DEFAULT_QFI;

}

void ogs_ran_phy_init(phy_entity_t *phy_entity) {
    ogs_assert(phy_entity != NULL);

    phy_entity->h.size = 0;
    phy_entity->frequency = DEFAULT_FREQUENCY;  
    phy_entity->prb_allocation = 0;
    phy_entity->modulation_scheme = DEFAULT_MODULATION_SCHEME;
    phy_entity->tx_power = DEFAULT_TX_POWER;
    phy_entity->is_signal_shaped = DEFAULT_SIGNAL_SHAPED;
}


