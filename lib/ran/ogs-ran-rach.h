#ifndef OGS_RAN_RACH_H
#define OGS_RAN_RACH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <bits/stdint-uintn.h>
#include <stdint.h>
#include <stdbool.h>

#define UL_GRANT_VALUE 100
#define TIMING_ADVANCE_VALUE 64
#define RAPID_VALUE 0x1A

#define RA_RNTI_S_ID 3           
#define RA_RNTI_T_ID 2           
#define RA_RNTI_F_ID 1           
#define RA_RNTI_UL_CARRIER_ID 0  

#define TEMP_C_RNTI 54321
#define C_RNTI 32678
#define MSG3_DATA_BUFFER 16
#define CRI_LENGTH 4
#define ACK 1
#define NACK 0

typedef struct {
    uint8_t s_id;           
    uint8_t t_id;           
    uint8_t f_id;           
    uint8_t ul_carrier_id;  
} ra_rnti_t;

typedef struct {
    uint8_t rapid;
    uint16_t tc_rnti;
    uint16_t ta;
    uint8_t ul_grant;
    uint16_t ra_rnti;
} rar_t;

typedef struct {
    uint8_t msg3_data[MSG3_DATA_BUFFER];  
    uint16_t c_rnti;                      // Temporary C-RNTI identifier
} connection_request_t;

typedef struct {
    uint16_t c_rnti;    // C-RNTI to be assigned
    uint16_t ta;        
    uint8_t ul_grant;   
    uint8_t ack_nack;   
    uint8_t cri[CRI_LENGTH]; // CRI containing first 32 bits of Msg3
} contention_resolution_t;

typedef struct {
    rar_t rar;
    ra_rnti_t ra_rnti_data;
    connection_request_t msg3;
    contention_resolution_t msg4;

    uint16_t assigned_c_rnti;
} rach_procedure_t;


uint16_t ogs_ran_calculate_ra_rnti(ra_rnti_t *ra_rnti);
void ogs_ran_send_ra_rnti(uint16_t ra_rnti); 
void ogs_ran_handle_prach_preamble(uint8_t preamble); 
void ogs_ran_transmit_msg2_to_phy(rach_procedure_t *rach_proc);
void ogs_ran_generate_ra_response(rach_procedure_t *rach_proc); 

size_t ogs_ran_receive_msg3_from_phy(rach_procedure_t *rach_proc);
void ogs_ran_process_msg3_mac(rach_procedure_t *rach_proc); 
void ogs_ran_send_msg4(rach_procedure_t *rach_proc); 
void ogs_ran_handle_harq_retransmission(rach_procedure_t *rach_proc); 
void ogs_ran_process(rach_procedure_t *rach_proc); 

#ifdef __cplusplus
}
#endif

#endif /* OGS_RAN_RACH_H */

