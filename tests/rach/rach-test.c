#include "core/abts.h"
#include "ran/ogs-ran-rach.h"

void test_ogs_ran_calculate_ra_rnti(abts_case *tc, void *data) {
    ra_rnti_t ra_rnti_data = {
        .s_id = 1,
        .t_id = 2,
        .f_id = 3,
        .ul_carrier_id = 4
    };

    uint16_t expected_ra_rnti_value = 1 + 1 + 14 * 2 + 14 * 80 * 3 + 14 * 80 * 8 * 4;
    uint16_t ra_rnti_value = ogs_ran_calculate_ra_rnti(&ra_rnti_data);

    ABTS_INT_EQUAL(tc, expected_ra_rnti_value, ra_rnti_value);
}

void test_ogs_ran_send_ra_rnti(abts_case *tc, void *data) {
    uint16_t ra_rnti = 12345;
    
    ogs_ran_send_ra_rnti(ra_rnti);
    
    ABTS_TRUE(tc, 1);  
}

void test_ogs_ran_handle_prach_preamble(abts_case *tc, void *data) {
    uint8_t preamble = 0xAA;  // Przykładowa wartość preambuły PRACH

    ra_rnti_t expected_ra_rnti_data = {
        .s_id = RA_RNTI_S_ID,
        .t_id = RA_RNTI_T_ID,
        .f_id = RA_RNTI_F_ID,
        .ul_carrier_id = RA_RNTI_UL_CARRIER_ID
    };
    
    uint16_t expected_ra_rnti_value = ogs_ran_calculate_ra_rnti(&expected_ra_rnti_data);

    ogs_ran_handle_prach_preamble(preamble);
    
    ABTS_INT_EQUAL(tc, expected_ra_rnti_value, ogs_ran_calculate_ra_rnti(&expected_ra_rnti_data));
}


void test_ogs_ran_generate_ra_response(abts_case *tc, void *data) {
    rach_procedure_t rach_proc = {0};

    ogs_ran_generate_ra_response(&rach_proc);

    uint16_t expected_ra_rnti = ogs_ran_calculate_ra_rnti(&rach_proc.ra_rnti_data);
    ABTS_INT_EQUAL(tc, expected_ra_rnti, rach_proc.rar.ra_rnti);
    ABTS_INT_EQUAL(tc, UL_GRANT_VALUE, rach_proc.rar.ul_grant);
    ABTS_INT_EQUAL(tc, TIMING_ADVANCE_VALUE, rach_proc.rar.ta);
    ABTS_INT_EQUAL(tc, RAPID_VALUE, rach_proc.rar.rapid);
}

void test_ogs_ran_receive_msg3_from_phy(abts_case *tc, void *data) {
    rach_procedure_t rach_proc = {0};
    
    size_t msg3_len = ogs_ran_receive_msg3_from_phy(&rach_proc);
    size_t i;

    ABTS_SIZE_EQUAL(tc, CRI_LENGTH, msg3_len);
    ABTS_INT_EQUAL(tc, TEMP_C_RNTI, rach_proc.msg3.c_rnti);
    
    for (i = 0; i < msg3_len; i++) {
        ABTS_INT_EQUAL(tc, 0xAB, rach_proc.msg3.msg3_data[i]);
    }
}

void test_ogs_ran_process_msg3_mac(abts_case *tc, void *data) {
    rach_procedure_t rach_proc = {0};
    rach_proc.msg3.c_rnti = TEMP_C_RNTI;
    size_t i;  
    ogs_ran_process_msg3_mac(&rach_proc);

    ABTS_INT_EQUAL(tc, C_RNTI, rach_proc.assigned_c_rnti);
    ABTS_INT_EQUAL(tc, ACK, rach_proc.msg4.ack_nack);
    ABTS_INT_EQUAL(tc, TIMING_ADVANCE_VALUE, rach_proc.msg4.ta);
    ABTS_INT_EQUAL(tc, UL_GRANT_VALUE, rach_proc.msg4.ul_grant);

    for (i = 0; i < CRI_LENGTH; i++) {
        ABTS_INT_EQUAL(tc, rach_proc.msg3.msg3_data[i], rach_proc.msg4.cri[i]);
    }
}

void test_ogs_ran_send_msg4(abts_case *tc, void *data) {
    rach_procedure_t rach_proc = {0};
    rach_proc.msg4.c_rnti = C_RNTI;
    rach_proc.msg4.ul_grant = UL_GRANT_VALUE;
    rach_proc.msg4.ta = TIMING_ADVANCE_VALUE;
    rach_proc.msg4.ack_nack = ACK;

    ogs_ran_send_msg4(&rach_proc);
    
    ABTS_TRUE(tc, 1);  
}

abts_suite *test_rach(abts_suite *suite) {
    suite = abts_add_suite(suite, "rach_tests");
    abts_run_test(suite, test_ogs_ran_calculate_ra_rnti, NULL);
    abts_run_test(suite, test_ogs_ran_send_ra_rnti, NULL);
    abts_run_test(suite, test_ogs_ran_handle_prach_preamble, NULL);
    abts_run_test(suite, test_ogs_ran_generate_ra_response, NULL);
    abts_run_test(suite, test_ogs_ran_receive_msg3_from_phy, NULL);
    abts_run_test(suite, test_ogs_ran_process_msg3_mac, NULL);
    abts_run_test(suite, test_ogs_ran_send_msg4, NULL);

    return suite;
}
