#ifndef OGS_RAN_RACH_H
#define OGS_RAN_RACH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <bits/stdint-uintn.h>
#include <stdint.h>
#include <stdbool.h>
#include "ran/context.h"

#define RA_TYPE_2STEP_RA 1
#define RA_TYPE_4STEP_RA 2
#define MSG3_DATA_BUFFOR 16
#define CONTENTION_RESOLUTION_IDENTIFIER 4

typedef struct {
    uint8_t preamble_format;    
    uint16_t time_resources;    
    uint16_t frequency_resources;
    uint8_t ra_rnti;           
} prach_config_t;

typedef struct {
    uint16_t root_sequence_index; 
    uint16_t cyclic_shift;        
    uint8_t set_type;             
    uint8_t preamble_format;
    uint8_t ra_rnti;
} rach_preamble_t;

typedef struct {
    uint8_t msg1_preamble;       
    uint8_t msg2_rar;            
    uint8_t msg3_pusch_grant;    
    bool contention_resolution;  
} rach_type_1_proc_t;

typedef struct {
    uint8_t msg_a_preamble;      
    uint8_t msg_b_rar;           
    uint8_t fallback_pusch_grant;
    bool contention_resolution;   
} rach_type_2_proc_t;

typedef struct {
    uint8_t ra_type;
} ue_vars_t;

typedef struct {
    uint8_t s_id;           
    uint8_t t_id;           
    uint8_t f_id;           
    uint8_t ul_carrier_id;  
} ra_rnti_t;

typedef struct {
    uint8_t resource_block;
    uint8_t mcs;
    uint8_t time_domain_allocation;
    uint16_t crc;
} dci_t;

typedef struct {
    uint8_t rapid;
    uint16_t tc_rnti;
    uint16_t ta;
    uint8_t ul_grant;
} rar_t;

typedef struct {
    uint8_t contention_resoultion_id[CONTENTION_RESOLUTION_IDENTIFIER];
} contention_resolution_t;

typedef struct {
    bool is_type_1;              
    prach_config_t prach_config;  
    rach_preamble_t preamble;    
    union {
        rach_type_1_proc_t type_1_proc;
        rach_type_2_proc_t type_2_proc;
    };
    ue_vars_t ue_vars;
    dci_t dci;
    rar_t rar;
    contention_resolution_t cri;
    uint8_t msg3_data[MSG3_DATA_BUFFOR];
    uint16_t c_rnti;
} rach_procedure_t;

void initialize_2step_ra_variables(rach_procedure_t *rach_proc); 
void initialize_4step_ra_variables(rach_procedure_t *rach_proc);
void initialize_ra_variables(rach_procedure_t *rach_proc);
void select_random_access_resources_2step(rach_procedure_t *rach_proc);
void select_random_access_resources_4step(rach_procedure_t *rach_proc);
void ogs_ran_init_random_access_procedure(rach_procedure_t *rach_proc); 
void ogs_ran_decode_prach_preamble(rach_procedure_t *rach_proc, uint8_t preamble);
uint16_t ogs_ran_calculate_ra_rnti(ra_rnti_t *ra_rnti);
void phy_send_preamble(phy_entity_t *phy_entity, uint8_t preamble); 
void ogs_ran_generate_dci_with_ra_rnti(rach_procedure_t *rach_proc, phy_entity_t *phy_entity);
void ogs_ran_send_rar(rach_procedure_t *rach_proc, phy_entity_t *phy_entity);
void ogs_ran_process_msg2(rach_procedure_t *rach_proc, phy_entity_t *phy_entity); 
size_t ogs_ran_simulate_receive_pusch(rach_procedure_t *rach_proc, uint8_t *buffer, size_t buffer_size); 
void ogs_ran_receive_msg3(rach_procedure_t *rach_proc);
bool ogs_ran_verify_crc_with_tc_rnti(uint16_t tc_rnti, uint8_t *msg_data, size_t msg_len);
void ogs_ran_handle_harq_retransmission(rach_procedure_t *rach_proc);
void ogs_ran_generate_msg4(rach_procedure_t *rach_proc); 
void ogs_ran_send_msg4(rach_procedure_t *rach_proc, contention_resolution_t *cri); 
bool ogs_ran_simulate_dci_reception(rach_procedure_t *rach_proc); 
void ogs_ran_monitor_pdcch_for_msg4(rach_procedure_t *rach_proc); 
void ogs_ran_decode_msg4(rach_procedure_t *rach_proc); 
bool ogs_ran_resolve_contention(rach_procedure_t *rach_proc); 
void ogs_ran_complete_contention_resolution(rach_procedure_t *rach_proc);

#ifdef __cplusplus
}
#endif

#endif /* OGS_RAN_RACH_H */

