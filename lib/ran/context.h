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
    RLC_MODE_TM,
    RLC_MODE_UM,
    RLC_MODE_AM 
} rlc_mode_t;

typedef enum {
    DIRECTION_DL, 
    DIRECTION_UL 
} direction_t;

typedef uint8_t qfi_t;

typedef struct ogs_ran_header_s {
    uint8_t *data;
    uint8_t size;
} ogs_ran_header_t;

typedef struct ogs_ran_pdu_header_s {
    uint8_t *data;
    uint8_t size;
    uint8_t sequence_number;
} ogs_ran_pdu_header_t;

typedef struct ogs_ran_security_header_s {
    uint8_t extended_protocol_discriminator;
    uint8_t security_header_type;
    uint32_t message_authentication_code;
    uint8_t sequence_number;
} ogs_ran_security_header_t;

typedef struct {
    ogs_ran_header_t h;
    union{
        qfi_t qfi;
    };
} sdap_entity_t;

typedef struct {
    ogs_ran_header_t h;
    union{
        uint8_t harq_process_id;
        bool is_active;
        uint8_t retransmission_count;
    };
} harq_entity_t;

typedef struct {
    ogs_ran_header_t h;
    union{
        uint32_t prb_allocation;   
        uint32_t modulation_scheme;
        uint32_t frequency;         
        uint8_t tx_power;          
        bool is_signal_shaped;
    };
} phy_entity_t;

typedef struct {
    ogs_ran_header_t h;
    union {
        uint8_t seq_nr;
        bool is_control_plane;
    };
} pdcp_sdu_t;

typedef struct {
    ogs_ran_header_t h;
    union {
        uint8_t seq_nr;
    };
} rlc_sdu_t;

typedef struct {
    ogs_ran_header_t h;
    union {
        logical_channel_t logical_channel;
    };
} mac_sdu_t;

typedef struct {
    ogs_ran_pdu_header_t h;
    union{
        bool rohc_enabled;                
        bool ciphering_enabled;
        bool integrity_protection_enabled;
    };
} pdcp_pdu_t;

typedef struct {
    ogs_ran_pdu_header_t h;
    union {
        rlc_mode_t mode;
        bool arq_enabled;                  
        bool segmentation_enabled;
        bool reassembly_enabled;
    };
} rlc_pdu_t;

typedef struct {
    ogs_ran_pdu_header_t h;
    union {
        transport_channel_t transport_channel;
        uint8_t tb_size;
        harq_entity_t harq_entity;
    };
} mac_pdu_t;

typedef struct {
    ogs_ran_security_header_t h;
    union {
        direction_t direction;   
        mac_sdu_t mac_sdu;
        mac_pdu_t mac_pdu;
        rlc_sdu_t rlc_sdu;
        rlc_pdu_t rlc_pdu;
        pdcp_sdu_t pdcp_sdu;
        pdcp_pdu_t pdcp_pdu;
        sdap_entity_t sdap_entity;
        phy_entity_t phy_entity;
    };
} data_flow_t;

// typedef struct {
//     uint8_t mode;  // AM or UM
//    uint8_t sn_field_length;
//    uint8_t t_poll_retransmit;
//    uint8_t t_reassembly;
//    uint8_t t_status_prohibit;
//} rlc_config_t;

// typedef struct {
//     uint8_t logical_channel_id;
//     uint8_t priority;
//     uint8_t bucket_size_duration;
// } mac_config_t;

void ogs_ran_mac_init(mac_sdu_t *mac_sdu, mac_pdu_t *mac_pdu);
void ogs_ran_rlc_init(rlc_sdu_t *rlc_sdu, rlc_pdu_t *rlc_pdu);
void ogs_ran_pdcp_init(pdcp_sdu_t *pdcp_sdu, pdcp_pdu_t *pdcp_pdu);
void ogs_ran_sdap_init(sdap_entity_t *sdap_entity);
void ogs_ran_phy_init(phy_entity_t *phy_entity);

#ifdef __cplusplus
}
#endif

#endif /* __CONTEXT_H */

