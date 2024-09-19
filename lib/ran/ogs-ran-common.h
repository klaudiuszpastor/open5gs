#ifndef __OGS_RAN_COMMON_H
#define __OGS_RAN_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bits/stdint-uintn.h>
#include "context.h"
#include "ogs-ran-rrc.h"

// Dedicated NAS message with RRC message
typedef struct {
    uint16_t length;
    uint8_t *rrc_message;
    nas_dedicated_message_t nas_msg;
} ogs_ran_rrc_message_t;

// MAC-PHY Interface
void ogs_ran_send_mac_pdu_to_phy(mac_pdu_t *mac_pdu);
void ogs_ran_send_harq_command_to_phy(harq_entity_t *harq_entity);
void ogs_ran_send_scheduling_request(data_flow_t *data_flow);
void ogs_ran_receive_mac_pdu_from_phy(mac_pdu_t *mac_pdu); 
void ogs_ran_receive_harq_from_phy(harq_entity_t *harq_entity); 
void ogs_ran_receive_cqi_report(phy_entity_t *phy_entity); 
void ogs_ran_receive_ta_command(phy_entity_t *phy_entity);

// Encapsulation of dedicated NAS message in an RRC message
void ogs_ran_rrc_encapsulate_nas(ogs_ran_rrc_message_t *rrc_msg, nas_dedicated_message_t *nas_msg);
// NAS-MAC Interface
void ogs_ran_send_rrc_message_to_mac(ogs_ran_rrc_message_t *rrc_msg);
void ogs_ran_receive_rrc_message_from_mac(ogs_ran_rrc_message_t *rrc_msg);

#ifdef __cplusplus
}
#endif

#endif /* __OGS_RAN_COMMON_H */


