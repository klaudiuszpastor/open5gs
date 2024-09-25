#include "ran/ogs-ran-rach.h"
#include "ogs-core.h"

uint16_t ogs_ran_calculate_ra_rnti(ra_rnti_t *ra_rnti_data) {
    ogs_assert(ra_rnti_data != NULL);
    uint16_t ra_rnti_value = 1 + ra_rnti_data->s_id +
                             14 * ra_rnti_data->t_id +
                             14 * 80 * ra_rnti_data->f_id +
                             14 * 80 * 8 * ra_rnti_data->ul_carrier_id;
    
    printf("Calculated RA-RNTI: %d\n", ra_rnti_value);
    return ra_rnti_value;
}

void ogs_ran_send_ra_rnti(uint16_t ra_rnti) {
    printf("RA-RNTI %d encoded and sent on PDCCH.\n", ra_rnti);
}

void ogs_ran_handle_prach_preamble(uint8_t preamble) {
    printf("Received PRACH preamble: 0x%02X\n", preamble);

    ra_rnti_t ra_rnti_data = {
        .s_id = RA_RNTI_S_ID,  
        .t_id = RA_RNTI_T_ID,
        .f_id = RA_RNTI_F_ID,
        .ul_carrier_id = RA_RNTI_UL_CARRIER_ID  
    };
    uint16_t ra_rnti = ogs_ran_calculate_ra_rnti(&ra_rnti_data);
    
    ogs_ran_send_ra_rnti(ra_rnti);
}

void ogs_ran_transmit_msg2_to_phy(rach_procedure_t *rach_proc) {
    ogs_info("Transmitting Msg2 (RAR) to PHY on PDSCH...");
    ogs_info("Msg2 (RAR) content:");
    ogs_info("RAPID: %d", rach_proc->rar.rapid);
    ogs_info("RA-RNTI: %d", rach_proc->rar.ra_rnti);
    ogs_info("Timing Advance (TA): %d", rach_proc->rar.ta);
    ogs_info("Uplink Grant: %d", rach_proc->rar.ul_grant);
}

// Function to generate Msg2 (RAR) based on RA-RNTI and network parameters
void ogs_ran_generate_ra_response(rach_procedure_t *rach_proc) {
    ogs_assert(rach_proc != NULL);

    ogs_ran_handle_prach_preamble(RAPID_VALUE);  
    uint16_t ra_rnti = ogs_ran_calculate_ra_rnti(&rach_proc->ra_rnti_data);
    rach_proc->rar.ra_rnti = ra_rnti;
    rach_proc->rar.ul_grant = UL_GRANT_VALUE;
    rach_proc->rar.ta = TIMING_ADVANCE_VALUE;
    rach_proc->rar.rapid = RAPID_VALUE;
    ogs_ran_transmit_msg2_to_phy(rach_proc);
}

// Function to simulate Msg3 reception from PHY layer (received over PUSCH)
size_t ogs_ran_receive_msg3_from_phy(rach_procedure_t *rach_proc) {
    ogs_info("Receiving Msg3 from UE on PUSCH...");

    // Simulate Msg3 reception with global Temporary C-RNTI
    uint16_t temp_c_rnti = TEMP_C_RNTI;
    rach_proc->msg3.c_rnti = temp_c_rnti;  

    size_t msg3_len = CRI_LENGTH;  
    if (msg3_len <= MSG3_DATA_BUFFER) {
        memset(rach_proc->msg3.msg3_data, 0xAB, msg3_len);  
        ogs_info("Received Msg3 with Temporary C-RNTI: %u", temp_c_rnti);
    } else {
        ogs_error("Msg3 buffer overflow.");
        return 0;
    }

    return msg3_len;
}

// Function to process Msg3 at the MAC layer in gNB
void ogs_ran_process_msg3_mac(rach_procedure_t *rach_proc) {
    ogs_assert(rach_proc != NULL);

    // Check if Msg3 contains Temporary C-RNTI (no RRC message, just MAC CE)
    if (rach_proc->msg3.c_rnti == TEMP_C_RNTI) {
        ogs_info("Processing Msg3 for UE with Temporary C-RNTI: %u", rach_proc->msg3.c_rnti);

        // Handle contention resolution (by sending MAC CE: CRI)
        // Copy the first 32 bits of Msg3 to CRI (Contention Resolution Indication)
        memcpy(rach_proc->msg4.cri, rach_proc->msg3.msg3_data, CRI_LENGTH);
        ogs_info("Contention Resolution Indication (CRI) created from first 32 bits of Msg3.");

        rach_proc->msg4.ul_grant = UL_GRANT_VALUE;  
        ogs_info("Allocated uplink resources for UE: %u, UL Grant: %d", rach_proc->msg3.c_rnti, rach_proc->msg4.ul_grant);
        rach_proc->msg4.ta = TIMING_ADVANCE_VALUE;  
        ogs_info("Timing Advance for UE: %u, TA: %d", rach_proc->msg3.c_rnti, rach_proc->msg4.ta);
        rach_proc->assigned_c_rnti = C_RNTI;
        ogs_info("Assigning new C-RNTI to UE: %u", rach_proc->assigned_c_rnti);
        rach_proc->msg4.c_rnti = rach_proc->assigned_c_rnti;
        rach_proc->msg4.ack_nack = ACK;  // Simulated ACK (1 = success)
    }
}

void ogs_ran_send_msg4(rach_procedure_t *rach_proc) {
    ogs_assert(rach_proc != NULL);
    ogs_info("Sending Msg4 to PDSCH: %u", rach_proc->msg4.c_rnti);
    ogs_info("Msg4 content: UL Grant: %d, Timing Advance: %d, ACK/NACK: %d",
             rach_proc->msg4.ul_grant, rach_proc->msg4.ta, rach_proc->msg4.ack_nack);
    ogs_info("CRI in Msg4 (Contention Resolution Indication): %02X%02X%02X%02X",
             rach_proc->msg4.cri[0], rach_proc->msg4.cri[1], rach_proc->msg4.cri[2], rach_proc->msg4.cri[3]);
}

void ogs_ran_handle_harq_retransmission(rach_procedure_t *rach_proc) {
    ogs_info("Monitoring HARQ feedback for Msg4...");

    if (rach_proc->msg4.ack_nack == ACK) {
        ogs_info("Msg4 successfully received by UE. No retransmission needed.");
    } else {
        ogs_error("Msg4 failed. Initiating retransmission...");
        ogs_ran_send_msg4(rach_proc);
    }
}

// Function to decode Msg3 and process Msg4 at the MAC layer
void ogs_ran_process(rach_procedure_t *rach_proc) {
    ogs_assert(rach_proc != NULL);

    // Receive Msg3 from the PHY layer (via PUSCH)
    size_t msg3_len = ogs_ran_receive_msg3_from_phy(rach_proc);
    if (msg3_len == 0) {
        ogs_error("Failed to receive Msg3.");
        return;
    }
    // Process Msg3 at the MAC layer (with contention resolution)
    ogs_ran_process_msg3_mac(rach_proc);
    // Create and send Msg4 (with CRI)
    ogs_ran_send_msg4(rach_proc);
    // Handle HARQ retransmission based on feedback
    ogs_ran_handle_harq_retransmission(rach_proc);
}
