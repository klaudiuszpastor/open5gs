#ifndef __OGS_RAN_RACH_H 
#define __OGS_RAN_RACH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ogs-core.h"  // Import necessary structures
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t preamble_format;    
    uint16_t time_resources;      // Time resources for PRACH transmission
    uint16_t frequency_resources; // Frequency resources for PRACH transmission
    uint8_t ra_rnti;              // RNTI
} prach_config_t;

typedef struct {
    uint16_t root_sequence_index; 
    uint16_t cyclic_shift;        
    uint8_t set_type;             
} rach_preamble_t;

typedef struct {
    uint8_t msg1_preamble;       // Random access preamble (Msg1)
    uint8_t msg2_rar;            // Random Access Response (Msg2) on PDCCH/PDSCH
    uint8_t msg3_pusch_grant;    // PUSCH grant (Msg3) after Msg2
    bool contention_resolution;  // Indicates whether contention resolution is needed
} rach_type_1_proc_t;

typedef struct {
    uint8_t msg_a_preamble;       // Random access preamble (MsgA)
    uint8_t msg_b_rar;            // Random Access Response (MsgB) on PDCCH/PDSCH
    uint8_t fallback_pusch_grant; // Fallback PUSCH grant after MsgB
    bool contention_resolution;   
} rach_type_2_proc_t;

typedef struct {
    bool is_type_1;              
    prach_config_t prach_config; 
    rach_preamble_t preamble;    
    union {
        rach_type_1_proc_t type_1_proc; 
        rach_type_2_proc_t type_2_proc; 
    };
} rach_procedure_t;

void ogs_ran_initiate_rach_procedure(rach_procedure_t *rach_proc);

#ifdef __cplusplus
}
#endif

#endif /* __OGS_RAN_RACH_H */

