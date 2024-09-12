#ifndef __CONTEXT_H
#define __CONTEXT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    LOGICAL_CHANNEL_BCCH,  /* Broadcast Control Channel */
    LOGICAL_CHANNEL_PCCH,  /* Paging Control Channel */
    LOGICAL_CHANNEL_CCCH,  /* Common Control Channel */
    LOGICAL_CHANNEL_DCCH,  /* Dedicated Control Channel */
    LOGICAL_CHANNEL_DTCH   /* Dedicated Traffic Channel */
} logical_channel_t;

typedef enum {
    TRANSPORT_CHANNEL_BCH,     /* Broadcast Channel */
    TRANSPORT_CHANNEL_PCH,     /* Paging Channel */
    TRANSPORT_CHANNEL_DL_SCH,  /* Downlink Shared Channel */
    TRANSPORT_CHANNEL_UL_SCH   /* Uplink Shared Channel */
} transport_channel_t;

typedef enum {
    RLC_MODE_TM, /* Transparent Mode */
    RLC_MODE_UM, /* Unacknowledged Mode */
    RLC_MODE_AM  /* Acknowledged Mode */
} rlc_mode_t;

typedef enum {
    DIRECTION_DL, 
    DIRECTION_UL 
} direction_t;

typedef uint8_t qfi_t;

typedef struct {
    qfi_t qfi;
    uint8_t *data;
    uint16_t size;
} sdap_entity_t;

typedef struct {
    uint8_t harq_process_id;
    bool is_active;
    uint8_t retransmission_count;
} harq_entity_t;

typedef struct {
    uint32_t prb_allocation;    /* Physical Resource Block allocation */
    uint32_t modulation_scheme; /* Modulation scheme (e.g., QPSK, 16QAM) */
    uint32_t frequency;         /* Carrier frequency */
    uint8_t tx_power;           /* Transmission power */
    bool is_signal_shaped;
} phy_entity_t;

typedef struct {
    uint16_t seq_nr;
    bool is_control_plane;
    uint8_t *data;
    uint32_t size;
} pdcp_sdu_t;

typedef struct {
    uint32_t seq_nr;
    uint8_t *data;
    uint32_t size;
} rlc_sdu_t;

typedef struct {
    logical_channel_t logical_channel;
    uint8_t *data;
    uint16_t size;
} mac_sdu_t;

typedef struct {
    uint32_t seq_nr;
    bool rohc_enabled;                
    bool ciphering_enabled;
    bool integrity_protection_enabled;
    uint8_t *data;
    uint16_t size;
} pdcp_pdu_t;

typedef struct {
    rlc_mode_t mode;
    uint32_t seq_nr; 
    bool arq_enabled;                  
    bool segmentation_enabled;
    bool reassembly_enabled;
    uint8_t *data;
    uint32_t size;
} rlc_pdu_t;

typedef struct {
    transport_channel_t transport_channel;
    uint16_t tb_size;
    harq_entity_t harq_entity;
    uint8_t *data;
} mac_pdu_t;

typedef struct {
    direction_t direction;   
    mac_sdu_t mac_sdu;
    mac_pdu_t mac_pdu;
    rlc_sdu_t rlc_sdu;
    rlc_pdu_t rlc_pdu;
    pdcp_sdu_t pdcp_sdu;
    pdcp_pdu_t pdcp_pdu;
    sdap_entity_t sdap_entity;
    phy_entity_t phy_entity;
} data_flow_t;

/* Function Prototypes */
void mac_init(mac_sdu_t *mac_sdu, mac_pdu_t *mac_pdu);
void mac_process(mac_sdu_t *mac_sdu, mac_pdu_t *mac_pdu);

void rlc_init(rlc_sdu_t *rlc_sdu, rlc_pdu_t *rlc_pdu);
void rlc_process(rlc_sdu_t *rlc_sdu, rlc_pdu_t *rlc_pdu);

void pdcp_init(pdcp_sdu_t *pdcp_sdu, pdcp_pdu_t *pdcp_pdu);
void pdcp_process(pdcp_sdu_t *pdcp_sdu, pdcp_pdu_t *pdcp_pdu);

void sdap_init(sdap_entity_t *sdap_entity);
void sdap_process(sdap_entity_t *sdap_entity);

void phy_init(phy_entity_t *phy_entity);
void phy_process(phy_entity_t *phy_entity);

#ifdef __cplusplus
}
#endif

#endif /* __CONTEXT_H */

