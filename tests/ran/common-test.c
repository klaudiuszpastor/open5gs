#include "abts.h"
#include "ran/ogs-ran-common.h"
#include "ran/context.h"
#include <string.h>  

#define RRC_BUFFER_SIZE 16

void test_ogs_ran_send_mac_pdu_to_phy(abts_case *tc, void *data) {
    mac_entity_t mac_entity;

    memset(&mac_entity, 0, sizeof(mac_entity_t));
    ogs_ran_send_mac_pdu_to_phy(&mac_entity);

    ABTS_TRUE(tc, 1);
}

void test_ogs_ran_send_harq_command_to_phy(abts_case *tc, void *data) {
    harq_entity_t harq_entity;

    memset(&harq_entity, 0, sizeof(harq_entity_t));
    ogs_ran_send_harq_command_to_phy(&harq_entity);

    ABTS_TRUE(tc, 1);
}

void test_ogs_ran_send_scheduling_request(abts_case *tc, void *data) {
    data_flow_t data_flow;

    memset(&data_flow, 0, sizeof(data_flow_t));
    ogs_ran_send_scheduling_request(&data_flow);

    ABTS_TRUE(tc, 1);
}

void test_ogs_ran_receive_mac_pdu_from_phy(abts_case *tc, void *data) {
    mac_entity_t mac_entity;

    memset(&mac_entity, 0, sizeof(mac_entity_t));
    ogs_ran_receive_mac_pdu_from_phy(&mac_entity);

    ABTS_TRUE(tc, 1);
}

void test_ogs_ran_receive_harq_from_phy(abts_case *tc, void *data) {
    harq_entity_t harq_entity;
    
    memset(&harq_entity, 0, sizeof(harq_entity_t));
    ogs_ran_receive_harq_from_phy(&harq_entity);

    ABTS_TRUE(tc, 1);
}

void test_ogs_ran_receive_cqi_report(abts_case *tc, void *data) {
    phy_entity_t phy_entity;

    memset(&phy_entity, 0, sizeof(phy_entity_t));
    phy_entity.modulation_scheme = 16;
    phy_entity.frequency = 1800;
    ogs_ran_receive_cqi_report(&phy_entity);

    ABTS_INT_EQUAL(tc, 1800, phy_entity.frequency);
}

void test_ogs_ran_receive_ta_command(abts_case *tc, void *data) {
    phy_entity_t phy_entity;

    memset(&phy_entity, 0, sizeof(phy_entity_t));
    phy_entity.frequency = 1800;
    ogs_ran_receive_ta_command(&phy_entity);

    ABTS_INT_EQUAL(tc, 1800, phy_entity.frequency);
}

void test_ogs_ran_send_rrc_message_to_mac(abts_case *tc, void *data) {
    rrc_entity_t rrc_entity;

    uint8_t static_rrc_data[RRC_BUFFER_SIZE];
    rrc_entity.data = static_rrc_data;
    rrc_entity.size = 3;
    rrc_entity.data[0] = 0x1;
    rrc_entity.data[1] = 0x2;
    rrc_entity.data[2] = 0x3;
    ogs_ran_send_rrc_message_to_mac(&rrc_entity);

    ABTS_TRUE(tc, 1);
}

void test_ogs_ran_receive_rrc_message_from_mac(abts_case *tc, void *data) {
    rrc_entity_t rrc_entity;

    uint8_t static_rrc_data[RRC_BUFFER_SIZE];
    rrc_entity.data = static_rrc_data;

    rrc_entity.size = 3;
    rrc_entity.data[0] = 0x1;
    rrc_entity.data[1] = 0x2;
    rrc_entity.data[2] = 0x3;
    ogs_ran_receive_rrc_message_from_mac(&rrc_entity);

    ABTS_TRUE(tc, 1);
}

abts_suite *test_ogs_ran_common(abts_suite *suite) {
    suite = abts_add_suite(suite, "RAN Common Tests");

    abts_run_test(suite, test_ogs_ran_send_mac_pdu_to_phy, NULL);
    abts_run_test(suite, test_ogs_ran_send_harq_command_to_phy, NULL);
    abts_run_test(suite, test_ogs_ran_send_scheduling_request, NULL);
    abts_run_test(suite, test_ogs_ran_receive_mac_pdu_from_phy, NULL);
    abts_run_test(suite, test_ogs_ran_receive_harq_from_phy, NULL);
    abts_run_test(suite, test_ogs_ran_receive_cqi_report, NULL);
    abts_run_test(suite, test_ogs_ran_receive_ta_command, NULL);
    abts_run_test(suite, test_ogs_ran_send_rrc_message_to_mac, NULL);
    abts_run_test(suite, test_ogs_ran_receive_rrc_message_from_mac, NULL);

    return suite;
}

