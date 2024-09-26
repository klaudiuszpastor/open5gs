#ifndef __OGS_RAN_COMMON_H
#define __OGS_RAN_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bits/stdint-uintn.h>
#include "ran/context.h"

typedef struct {
    uint8_t *data;  
    uint8_t size;    
} rrc_entity_t;

void ogs_ran_send_mac_pdu_to_phy(mac_entity_t *mac_entity);
void ogs_ran_send_harq_command_to_phy(harq_entity_t *harq_entity);
void ogs_ran_send_scheduling_request(data_flow_t *data_flow);
void ogs_ran_receive_mac_pdu_from_phy(mac_entity_t *mac_entity); 
void ogs_ran_receive_harq_from_phy(harq_entity_t *harq_entity); 
void ogs_ran_receive_cqi_report(phy_entity_t *phy_entity); 
void ogs_ran_receive_ta_command(phy_entity_t *phy_entity);

void ogs_ran_send_rrc_message_to_mac(rrc_entity_t *rrc_entity);
void ogs_ran_receive_rrc_message_from_mac(rrc_entity_t *rrc_entity);

#ifdef __cplusplus
}
#endif

#endif /* __OGS_RAN_COMMON_H */


