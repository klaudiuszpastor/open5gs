#include "ran/context.h"
#include "ran/ogs-ran-rach.h"
#include "ogs-core.h"
#include <string.h>
#include "ran/ogs-ran-rrc.h"

void initialize_2step_ra_variables(rach_procedure_t *rach_proc) {
    ogs_assert(rach_proc != NULL);
    ogs_info("Initializing variables for 2-step RA");
    // TODO
    // Initialization of 2-stepRA logic in 5.1.1a 
}

void initialize_4step_ra_variables(rach_procedure_t *rach_proc) {
    ogs_assert(rach_proc != NULL);
    ogs_info("Initializing variables for 4-step RA");
    //TODO
    // Intialization of 4-stepRA logic in 5.1.1a
}

void initialize_ra_variables(rach_procedure_t *rach_proc) {
    ogs_assert(rach_proc != NULL);

    if (rach_proc->ue_vars.ra_type == RA_TYPE_2STEP_RA) {
        initialize_2step_ra_variables(rach_proc);
    } else if (rach_proc->ue_vars.ra_type == RA_TYPE_4STEP_RA) {
        initialize_4step_ra_variables(rach_proc);
    } else {
        ogs_error("Unknown RA_TYPE: %d", rach_proc->ue_vars.ra_type);
    }
}

void select_random_access_resources_2step(rach_procedure_t *rach_proc) {
    ogs_info("Performing Random Access Resource selection for 2-step RA");
    // Logic to select resources for 2-step RA according to clause 5.1.2a
}

void select_random_access_resources_4step(rach_procedure_t *rach_proc) {
    ogs_info("Performing Random Access Resource selection for 4-step RA");
    // Logic to select resources for 4-step RA according to clause 5.1.2
}

void ogs_ran_init_random_access_procedure(rach_procedure_t *rach_proc) {
    ogs_assert(rach_proc != NULL);
    // Logic to initialize RA procedure according to clause 5.1.1
    // Initialize variables specific to the selected RA type
    initialize_ra_variables(rach_proc);
    if (rach_proc->ue_vars.ra_type == RA_TYPE_2STEP_RA) {
        select_random_access_resources_2step(rach_proc);
    } else {
        select_random_access_resources_4step(rach_proc);
    }
}

/* Msg1 Random Access Preamble Transmission */

void phy_send_preamble(phy_entity_t *phy_entity, uint8_t preamble) {
    ogs_info("Physical layer (ID: %d) processing PRACH preamble 0x%02X", phy_entity->id, preamble);
}

void ogs_ran_decode_prach_preamble(rach_procedure_t *rach_proc, uint8_t preamble) {
    ogs_info("Decoding PRACH Preamble: 0x%02X", preamble);

    // Simulating PRACH
    if (preamble == 0x1A || preamble == 0x1B || preamble == 0x1C) {
        ogs_info("PRACH preamble 0x%02X received and decoded successfully.", preamble);
        rach_proc->preamble.preamble_format = preamble;

        // Simulationg of sending preamble to physical layer 
        phy_entity_t phy_entity;
        phy_entity.id = rand() % 1000;  
        ogs_info("Sending PRACH preamble 0x%02X to physical layer entity with ID: %d", preamble, phy_entity.id);
        phy_send_preamble(&phy_entity, preamble);

        // uint8_t time_resource = rand() % 15; 
        // uint8_t freq_resource = rand() % 10; 
        // ogs_info("Assigned Time Resource: %d, Frequency Resource: %d for PRACH transmission.", time_resource, freq_resource);
    } else {
        ogs_error("Unknown PRACH preamble received.");
    }
}

uint16_t ogs_ran_calculate_ra_rnti(ra_rnti_t *ra_rnti_data) {
    uint16_t ra_rnti_value = 1 + ra_rnti_data->s_id + 14 * ra_rnti_data->t_id + 14 * 80 * ra_rnti_data->f_id + ra_rnti_data->ul_carrier_id;
    ogs_info("Calculated RA-RNTI: %d", ra_rnti_value);
    return ra_rnti_value;
}

/* Msg2 Random Access Response Reception */

// void transmit_dci_to_phy_layer(phy_entity_t *phy_entity, dci_t *dci) {
//     ogs_info("Transmitting DCI to Physical Layer (ID: %d), Resource Block: %d, MCS: %d",
//              phy_entity->id, dci->resource_block, dci->mcs);
// }

// void transmit_rar_to_phy_layer(phy_entity_t *phy_entity, rar_t *rar) {
//     ogs_info("Transmitting RAR to Physical Layer (ID: %d), RAPID: %d, TC-RNTI: %d, TA: %d, UL Grant: %d",
//              phy_entity->id, rar->rapid, rar->tc_rnti, rar->ta, rar->ul_grant);
// }

void ogs_ran_generate_dci_with_ra_rnti(rach_procedure_t *rach_proc, phy_entity_t *phy_entity) {
    ogs_info("Generating DCI with RA-RNTI: %d", rach_proc->preamble.ra_rnti);

    uint8_t resource_block = rand() % 100;  
    uint8_t modulation_and_coding_scheme = rand() % 28;  
    uint8_t time_domain_allocation = rand() % 10;  

    // DCI (Format 1_0) structure
    rach_proc->dci.resource_block = resource_block;
    rach_proc->dci.mcs = modulation_and_coding_scheme;
    rach_proc->dci.time_domain_allocation = time_domain_allocation;
    
    ogs_info("DCI Format 1_0 generated: Resource Block: %d, MCS: %d, Time Domain Allocation: %d",
             resource_block, modulation_and_coding_scheme, time_domain_allocation);
    ogs_info("DCI with RA-RNTI: %d transmitted on PDCCH with Resource Block: %d and MCS: %d",
             rach_proc->preamble.ra_rnti, resource_block, modulation_and_coding_scheme);

//     transmit_dci_to_phy_layer(phy_entity, &rach_proc->dci);
}

void ogs_ran_send_rar(rach_procedure_t *rach_proc, phy_entity_t *phy_entity) {
    ogs_info("Sending RAR on PDSCH for RA-RNTI: %d", rach_proc->preamble.ra_rnti);
    ogs_info("Transmitting RAR on Physical Layer (ID: %d) with Resource Block: %d and MCS: %d",
             phy_entity->id, rach_proc->dci.resource_block, rach_proc->dci.mcs);

//     transmit_rar_to_phy_layer(phy_entity, &rach_proc->rar);
}

void ogs_ran_process_msg2(rach_procedure_t *rach_proc, phy_entity_t *phy_entity) {
    ogs_info("Processing Msg2 for UE with RA-RNTI: %d", rach_proc->preamble.ra_rnti);

    ogs_ran_generate_dci_with_ra_rnti(rach_proc, phy_entity);
    uint8_t rapid = rand() % 64;  
    uint16_t t_crnti = rand() % 65536;  
    uint16_t ta = rand() % 128;  
    uint8_t ul_grant = rand() % 256;  
    ogs_ran_send_rar(rach_proc, phy_entity);
}

/* Msg3 Connection Request Transmission */

void ogs_ran_receive_msg3(rach_procedure_t *rach_proc) {
    ogs_info("Receiving Msg3 on PUSCH for UE with TC-RNTI: %d", rach_proc->rar.tc_rnti);

    uint8_t msg3_data[MSG3_DATA_BUFFOR]; 
    // Receiving data from PUSCH 
    size_t msg3_len = ogs_ran_simulate_receive_pusch(rach_proc, msg3_data, sizeof(msg3_data));

    if (msg3_len > 0) {
        bool crc_valid = ogs_ran_verify_crc_with_tc_rnti(rach_proc->rar.tc_rnti, msg3_data, msg3_len);

        if (crc_valid) {
            ogs_info("Msg3 successfully received and verified.");
            rrc_message_type_t msg_type = RRC_SETUP_REQUEST;
            rrc_dispatch_message(msg_type, msg3_data, msg3_len);

        } else {
            ogs_error("Msg3 CRC verification failed. Requesting HARQ retransmission.");
            ogs_ran_handle_harq_retransmission(rach_proc);
        }
    } else {
        ogs_error("Failed to receive Msg3 on PUSCH.");
    }
}

size_t ogs_ran_simulate_receive_pusch(rach_procedure_t *rach_proc, uint8_t *buffer, size_t buffer_size) {
    ogs_info("Simulating PUSCH reception for UE with TC-RNTI: %d", rach_proc->rar.tc_rnti);

    rrc_setup_request_t rrc_setup_req;
    rrc_setup_req.ueIdentity.mmeCode = 0x1234;
    rrc_setup_req.ueIdentity.mTmsi = 0x56789;

    size_t msg3_len = sizeof(rrc_setup_req);
    if (msg3_len <= buffer_size) {
        memcpy(buffer, &rrc_setup_req, msg3_len);
    }

    return msg3_len; 
}

bool ogs_ran_verify_crc_with_tc_rnti(uint16_t tc_rnti, uint8_t *msg_data, size_t msg_len) {
    bool crc_valid = true; 
    ogs_info("Verifying CRC with TC-RNTI: %d", tc_rnti);

    return crc_valid;
}

void ogs_ran_handle_harq_retransmission(rach_procedure_t *rach_proc) {
    ogs_info("Requesting HARQ retransmission for UE with TC-RNTI: %d", rach_proc->rar.tc_rnti);
}

/* Msg4 Contention Resolution Reception */

void ogs_ran_generate_msg4(rach_procedure_t *rach_proc) {
    ogs_info("Generating Msg4 for UE with TC-RNTI: %d", rach_proc->rar.tc_rnti);

    // Simulate: Generating Contention Resolution Indication (CRI) message
    contention_resolution_t cri;
    memset(&cri, 0, sizeof(cri));

    // Copy the first 32 bits of Msg3 (UE identifier)
    memcpy(cri.contention_resoultion_id, rach_proc->msg3_data, 4); 

    // Generate Msg4 with MAC CE: CRI
    ogs_info("Msg4 contains Contention Resolution Indication for UE.");
    
    // Send Msg4 to the physical layer
    ogs_ran_send_msg4(rach_proc, &cri);
}

void ogs_ran_send_msg4(rach_procedure_t *rach_proc, contention_resolution_t *cri) {
    ogs_info("Sending Msg4 on PDSCH for UE with TC-RNTI: %d", rach_proc->rar.tc_rnti);
    ogs_info("Msg4 with Contention Resolution Indication transmitted on PDSCH.");
}

bool ogs_ran_simulate_dci_reception(rach_procedure_t *rach_proc) {
    ogs_info("Simulating DCI reception for UE with TC-RNTI: %d", rach_proc->rar.tc_rnti);
    return true;
}

void ogs_ran_monitor_pdcch_for_msg4(rach_procedure_t *rach_proc) {
    ogs_info("Monitoring PDCCH for Msg4 addressed to UE with TC-RNTI: %d", rach_proc->rar.tc_rnti);

    // Simulate: Monitoring PDCCH
    bool dci_received = ogs_ran_simulate_dci_reception(rach_proc);

    if (dci_received) {
        ogs_info("DCI received on PDCCH. Decoding Msg4 from PDSCH.");
        
        // Decode the Msg4 from PDSCH
        ogs_ran_decode_msg4(rach_proc);
    } else {
        ogs_error("Failed to receive DCI for Msg4. Retrying or aborting.");
    }
}

void ogs_ran_decode_msg4(rach_procedure_t *rach_proc) {
    ogs_info("Decoding Msg4 for UE with TC-RNTI: %d", rach_proc->rar.tc_rnti);

    // Simulate decoding Msg4
    bool contention_resolved = ogs_ran_resolve_contention(rach_proc);

    if (contention_resolved) {
        // Promote TC-RNTI to C-RNTI
        rach_proc->c_rnti = rach_proc->rar.tc_rnti;
        ogs_info("Contention resolved. Promoting TC-RNTI to C-RNTI: %d", rach_proc->c_rnti);

        // UE transitions to RRC_CONNECTED mode
        ogs_ran_complete_contention_resolution(rach_proc);
    } else {
        ogs_error("Contention resolution failed. Aborting.");
    }
}

bool ogs_ran_resolve_contention(rach_procedure_t *rach_proc) {
    // Simulate: Checking if Msg4 contains the correct UE identifier
    ogs_info("Resolving contention for UE with TC-RNTI: %d", rach_proc->rar.tc_rnti);

    // Check if the first 32 bits of Msg4 (CRI) match Msg3
    if (memcmp(rach_proc->msg3_data, rach_proc->cri.contention_resoultion_id, 4) == 0) {
        return true; 
    }

    return false; 
}

void ogs_ran_complete_contention_resolution(rach_procedure_t *rach_proc) {
    ogs_info("Contention resolution completed. UE with C-RNTI: %d is now in RRC_CONNECTED mode.", rach_proc->c_rnti);
}


