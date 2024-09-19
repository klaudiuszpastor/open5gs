#include "ogs-ran-common.h"
#include "ogs-core.h"

void ogs_ran_send_mac_pdu_to_phy(mac_pdu_t *mac_pdu) {
    ogs_assert(mac_pdu != NULL);
    ogs_assert(mac_pdu->h.data != NULL);

    ogs_debug("Sending MAC PDU to PHY...");
    ogs_info("PHY: Received MAC PDU. Size: %d, Transport Channel: %d", mac_pdu->tb_size, mac_pdu->transport_channel);
}

void ogs_ran_send_harq_command_to_phy(harq_entity_t *harq_entity) {
    ogs_assert(harq_entity != NULL); 

    ogs_debug("Sending HARQ command to PHY...");
    ogs_info("PHY: HARQ Process ID: %d, Retransmission Count: %d", harq_entity->harq_process_id, harq_entity->retransmission_count);
}

void ogs_ran_send_scheduling_request(data_flow_t *data_flow) {
    ogs_assert(data_flow != NULL);

    ogs_debug("Sending Scheduling Request to PHY...");
    ogs_info("PHY: Processing Scheduling Request for direction %d", data_flow->direction);
}

void ogs_ran_receive_mac_pdu_from_phy(mac_pdu_t *mac_pdu) {
    ogs_assert(mac_pdu != NULL); 
    ogs_assert(mac_pdu->h.data != NULL);  

    ogs_debug("Receiving MAC PDU from PHY...");
    ogs_info("MAC: Received MAC PDU. Size: %d, Transport Channel: %d", mac_pdu->tb_size, mac_pdu->transport_channel);
}

void ogs_ran_receive_harq_from_phy(harq_entity_t *harq_entity) {
    ogs_assert(harq_entity != NULL);

    ogs_debug("Receiving HARQ feedback from PHY...");
    ogs_info("MAC: HARQ Feedback - Process ID: %d, Is Active: %d", harq_entity->harq_process_id, harq_entity->is_active);
}

void ogs_ran_receive_cqi_report(phy_entity_t *phy_entity) {
    ogs_assert(phy_entity != NULL);

    ogs_debug("Receiving CQI report from PHY...");
    ogs_info("MAC: CQI Report - Modulation Scheme: %d, Frequency: %d", phy_entity->modulation_scheme, phy_entity->frequency);
}

void ogs_ran_receive_ta_command(phy_entity_t *phy_entity) {
    ogs_assert(phy_entity != NULL);

    ogs_debug("Receiving Timing Advance command from PHY...");
    ogs_info("MAC: Timing Advance Command - Frequency: %d", phy_entity->frequency);
}

