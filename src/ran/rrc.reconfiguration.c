#include <stdint.h>
#include "rrc.h"
#include "ogs-core.h"
#include "context.h"

void configure_rlc(rlc_config_t *config) {
    if (config->mode == RLC_AM) {
        ogs_debug("Configuring AM RLC");
        //TODO: apply am configurations
        ogs_info("SN Field Length: %d", config->sn_field_length);
        ogs_info("Poll Retransmit Timer: %d", config->t_poll_retransmit);
    } else if (config->mode == RLC_UM) {
        ogs_debug("Configuring UM RLC");
        //TODO: apply um configurations
        ogs_info("SN Field Length: %d", config->sn_field_length);
    }
    //TODO: general configuration steps
    ogs_info("Reassembly Timer: %d", config->t_reassembly);
    ogs_info("Status Prohibit Timer: %d", config->t_status_prohibit);
}

void configure_mac(mac_config_t *config) {
    ogs_debug("Configuring MAC Layer");
    ogs_info("Logical Channel ID: %d", config->logical_channel_id);
    ogs_info("Priority: %d", config->priority);
    ogs_info("Bucket Size Duration: %d", config->bucket_size_duration);
}


void rrc_reconfiguration(rlc_config_t *rlc_config, mac_config_t *mac_config, uint8_t sync_needed) {
    ogs_debug("Starting RRC Reconfiguration");

    configure_rlc(rlc_config);

    configure_mac(mac_config);

    if (sync_needed) {
        ogs_debug("Reconfiguration with sync");
        //TODO: sync handling, Random Access Procedure (RA)
    } else {
        ogs_debug("Reconfiguration without sync");
    }

    ogs_info("RRC Reconfiguration Completed.");
}