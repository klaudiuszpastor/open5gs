#include "ogs-core.h"
#include "context.h"
#include "context.h"
#include <stdio.h>
#include <stdlib.h>  

#define MAC_SDU_BUFFER_SIZE 100
#define MAC_PDU_BUFFER_SIZE 100
#define RLC_SDU_BUFFER_SIZE 100
#define RLC_PDU_BUFFER_SIZE 100
#define PDCP_SDU_BUFFER_SIZE 100
#define PDCP_PDU_BUFFER_SIZE 100
#define SDAP_BUFFER_SIZE 100
#define PHY_BUFFER_SIZE 100

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

void ogs_ran_mac_init(mac_sdu_t *mac_sdu, mac_pdu_t *mac_pdu) {
    ogs_assert(mac_sdu != NULL && mac_pdu != NULL);

    mac_sdu->h.data = (uint8_t *)malloc(MAC_SDU_BUFFER_SIZE);
    ogs_assert(mac_sdu->h.data != NULL);
    mac_sdu->h.size = 0;
    mac_sdu->logical_channel = DEFAULT_LOGICAL_CHANNEL;

    mac_pdu->h.data = (uint8_t *)malloc(MAC_PDU_BUFFER_SIZE);
    ogs_assert(mac_pdu->h.data != NULL);
    mac_pdu->h.size = 0;
    mac_pdu->transport_channel = DEFAULT_TRANSPORT_CHANNEL;
    mac_pdu->tb_size = 0;
    mac_pdu->harq_entity.harq_process_id = DEFAULT_HARQ_PROCESS_ID;
    mac_pdu->harq_entity.is_active = false;
    mac_pdu->harq_entity.retransmission_count = DEFAULT_RETRANSMISSION_COUNT;
}

void ogs_ran_rlc_init(rlc_sdu_t *rlc_sdu, rlc_pdu_t *rlc_pdu) {
    ogs_assert(rlc_sdu != NULL && rlc_pdu != NULL);

    rlc_sdu->h.data = (uint8_t *)malloc(RLC_SDU_BUFFER_SIZE);
    ogs_assert(rlc_sdu->h.data != NULL);
    rlc_sdu->h.size = 0;
    rlc_sdu->seq_nr = DEFAULT_SEQUENCE_NUMBER;

    rlc_pdu->h.data = (uint8_t *)malloc(RLC_PDU_BUFFER_SIZE);
    ogs_assert(rlc_pdu->h.data != NULL);
    rlc_pdu->h.size = 0;
    rlc_pdu->mode = DEFAULT_RLC_MODE;
    rlc_pdu->arq_enabled = DEFAULT_ARQ_ENABLED;
    rlc_pdu->segmentation_enabled = DEFAULT_SEGMENTATION_ENABLED;
    rlc_pdu->reassembly_enabled = DEFAULT_REASSEMBLY_ENABLED;
}

void ogs_ran_pdcp_init(pdcp_sdu_t *pdcp_sdu, pdcp_pdu_t *pdcp_pdu) {
    ogs_assert(pdcp_sdu != NULL && pdcp_pdu != NULL);

    pdcp_sdu->h.data = (uint8_t *)malloc(PDCP_SDU_BUFFER_SIZE);
    ogs_assert(pdcp_sdu->h.data != NULL);
    pdcp_sdu->h.size = 0;
    pdcp_sdu->seq_nr = DEFAULT_SEQUENCE_NUMBER;
    pdcp_sdu->is_control_plane = DEFAULT_IS_CONTROL_PLANE;

    pdcp_pdu->h.data = (uint8_t *)malloc(PDCP_PDU_BUFFER_SIZE);
    ogs_assert(pdcp_pdu->h.data != NULL);
    pdcp_pdu->h.size = 0;
    pdcp_pdu->rohc_enabled = DEFAULT_ROHC_ENABLED;
    pdcp_pdu->ciphering_enabled = DEFAULT_CIPHERING_ENABLED;
    pdcp_pdu->integrity_protection_enabled = DEFAULT_INTEGRITY_PROTECTION_ENABLED;
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



