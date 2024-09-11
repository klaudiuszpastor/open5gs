#ifndef L2_LAYER_H
#define L2_LAYER_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BCCH, // Broadcast Control Channel
    PCCH, // Paging Control Channel
    CCCH, // Common Control Channel
    DCCH, // Dedicated Control Channel
    DTCH  // Dedicated Traffic Channel
} LogicalChannelType;

typedef enum {
    BCH,    // Broadcast Channel
    PCH,    // Paging Channel
    DL_SCH, // Downlink Shared Channel
    UL_SCH  // Uplink Shared Channel
} TransportChannelType;

typedef enum {
    TM, // Transparent Mode
    UM, // Unacknowledged Mode
    AM  // Acknowledged Mode
} RLCMode;

typedef enum {
    DL, // Downlink
    UL  // Uplink
} Direction;

typedef uint8_t QFI;

typedef struct {
    QFI qfi;       
    uint8_t *data; 
    uint16_t size; 
} SDAPEntity;

typedef struct {
    uint8_t harq_process_id;
    bool is_active;
    uint8_t retransmission_count;
} HARQEntity;

typedef struct {
    uint32_t prb_allocation;    // Physical Resource Block allocation
    uint32_t modulation_scheme; // Modulation scheme (e.g., QPSK, 16QAM)
    uint32_t frequency;         // Carrier frequency
    uint8_t tx_power;           // Transmission power
    bool is_signal_shaped;
} PHYEntity;

// ---------------------------- SDU (Service Data Unit) Structures ---------------------------- //
typedef struct {
    uint16_t seq_nr;          
    bool is_control_plane;    
    uint8_t *data;            
    uint32_t size;            
} PDCPSDU;

typedef struct {
    uint32_t seq_nr;          
    uint8_t *data;            
    uint32_t size;            
} RLCSDU;

typedef struct {
    LogicalChannelType logical_channel; 
    uint8_t *data;                      
    uint16_t size;                                     
} MACSDU;

// ---------------------------- PDU (Protocol Data Unit) Structures ---------------------------- //
typedef struct {
    uint32_t seq_nr;   
    bool rohc_enabled;  // ROHC (Robust Header Compression) enabled
    bool ciphering_enabled;
    bool integrity_protection_enabled;
    uint8_t *data;      
    uint16_t size;      
} PDCPPDU;

typedef struct {
    RLCMode mode;              
    uint32_t seq_nr;
    bool arq_enabled;          // ARQ (Automatic Repeat reQuest) enabled (AM mode)
    bool segmentation_enabled;
    bool reassembly_enabled;
    uint8_t *data;             
    uint32_t size;             
} RLCPDU;

typedef struct {
    TransportChannelType transport_channel; 
    uint16_t tb_size;    
    HARQEntity harq_entity;                   
    uint8_t *data;                          
} MACPDU;

typedef struct {
    Direction direction;      // Direction (Uplink or Downlink)
    MACSDU mac_sdu;           
    MACPDU mac_pdu;           
    RLCSDU rlc_sdu;           
    RLCPDU rlc_pdu;           
    PDCPSDU pdcp_sdu;         
    PDCPPDU pdcp_pdu;  
    SDAPEntity sdap_entity;       
    PHYEntity phy_entity;     
} L2DataFlow;


void mac_init(MACSDU *mac_sdu, MACPDU *mac_pdu);
void mac_process(MACSDU *mac_sdu, MACPDU *mac_pdu);

void rlc_init(RLCSDU *rlc_sdu, RLCPDU *rlc_pdu);
void rlc_process(RLCSDU *rlc_sdu, RLCPDU *rlc_pdu);

void pdcp_init(PDCPSDU *pdcp_sdu, PDCPPDU pdcp_pdu);
void pdcp_process(PDCPSDU *pdcp_sdu, PDCPPDU pdcp_pdu);

void sdap_init(SDAPEntity *sdap_entity);
void sdap_process(SDAPEntity *sdap_entity);

void phy_init(PHYEntity *phy_entity);
void phy_process(PHYEntity *phy_entity);

void l2_uplink(L2DataFlow *flow);
void l2_downlink(L2DataFlow *flow);

#ifdef __cplusplus
}
#endif

#endif // L2_LAYER_H
