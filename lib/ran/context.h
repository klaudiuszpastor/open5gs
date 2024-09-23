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
    rlc_mode_t rlcMode;  
    uint8_t snFieldLength;  
    bool reorderingEnabled;  
    uint16_t maxRetx;  
    uint8_t pollPdu;  
    uint8_t pollByte;  
    uint16_t pollRetransmit;  
} rlc_config_t;

typedef struct {
    ogs_ran_header_t h;
    rlc_config_t rlcConfig;
} rlc_entity_t;

typedef struct {
    uint8_t pdcpSNSizeUL;
    uint8_t pdcpSNSizeDL;
    uint8_t integrityProtection;
    uint8_t cipheringAlgorithm;
} pdcp_config_t;

typedef struct {
    ogs_ran_header_t h;
    pdcp_config_t pdcpConfig;
} pdcp_entity_t;

typedef struct {
    logical_channel_t logicalChannelId;
    transport_channel_t transportChannelId;
    uint8_t priority;
    uint8_t lcGroup;
    uint8_t schedulingRequestConfig;
} mac_config_t;

typedef struct {
    ogs_ran_header_t h;
    mac_config_t macConfig;
} mac_entity_t;

typedef struct {
    uint8_t rbId;
    union {
        pdcp_config_t pdcpConfig;    
        rlc_config_t rlcConfig; 
        mac_config_t macConfig;
    };
} rb_config_t;

typedef struct {
    uint32_t mmeCode;      
    uint32_t mTmsi;        
} ue_identity_t;

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
    ogs_ran_security_header_t h;
    union {
        direction_t direction;   
        sdap_entity_t sdap_entity;
        phy_entity_t phy_entity;
    };
} data_flow_t;

void ogs_ran_mac_init(mac_entity_t *mac_entity);
void ogs_ran_rlc_init(rlc_entity_t *rlc_entity);
void ogs_ran_pdcp_init(pdcp_entity_t *pdcp_entity);
void ogs_ran_sdap_init(sdap_entity_t *sdap_entity);
void ogs_ran_phy_init(phy_entity_t *phy_entity);

#ifdef __cplusplus
}
#endif

#endif /* __CONTEXT_H */

