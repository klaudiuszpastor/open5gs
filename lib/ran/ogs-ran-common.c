#include "ogs-ran-common.h"
#include "ogs-core.h"
#include "ogs-ran-rrc.h"
#include <bits/stdint-uintn.h>

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

void ogs_ran_rrc_encapsulate_nas(ogs_ran_rrc_message_t *rrc_msg, nas_dedicated_message_t *nas_msg) {
    ogs_assert(rrc_msg != NULL);
    ogs_assert(nas_msg != NULL);

    rrc_msg->nas_msg = *nas_msg;
    rrc_msg->length = sizeof(nas_dedicated_message_t);
    rrc_msg->rrc_message = (uint8_t*)nas_msg;

    ogs_info("Encapsulated NAS message in RRC message. NAS message length: %d",rrc_msg->length);
}

void ogs_ran_send_rrc_message_to_mac(ogs_ran_rrc_message_t *rrc_msg) {
    ogs_assert(rrc_msg != NULL);

    ogs_info("Sending RRC message with NAS content to MAC.");
    ogs_debug("RRC Message Length: %d", rrc_msg->length);
    ogs_debug("NAS Message Type: %d", rrc_msg->nas_msg.messageType);

    send_message_to_mac(RRC_SETUP_COMPLETE, rrc_msg, rrc_msg->length);
}

void ogs_ran_receive_rrc_message_from_mac(ogs_ran_rrc_message_t *rrc_msg) {
    ogs_assert(rrc_msg != NULL);

    ogs_info("Received RRC message from MAC.");
    ogs_debug("RRC Message Length: %d", rrc_msg->length);
    ogs_debug("NAS Message Length: %lu", sizeof(rrc_msg->nas_msg));

    if (rrc_msg->length > 0) {
        nas_dedicated_message_t *nas_msg = &rrc_msg->nas_msg;
        ogs_info("Processing NAS message of type: %d", nas_msg->messageType);
    }
}


