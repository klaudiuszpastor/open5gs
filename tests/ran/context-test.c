#include "abts.h"
#include "ran/context.h"
#include <string.h>  

void test_ogs_ran_mac_init(abts_case *tc, void *data) {
    mac_entity_t mac_entity;

    memset(&mac_entity, 0, sizeof(mac_entity_t));

    ogs_ran_mac_init(&mac_entity);

    ABTS_INT_EQUAL(tc, LOGICAL_CHANNEL_DCCH, mac_entity.macConfig.logicalChannelId);
    ABTS_INT_EQUAL(tc, TRANSPORT_CHANNEL_DL_SCH, mac_entity.macConfig.transportChannelId);
    ABTS_INT_EQUAL(tc, 0, mac_entity.macConfig.priority);
    ABTS_INT_EQUAL(tc, 0, mac_entity.macConfig.lcGroup);
    ABTS_INT_EQUAL(tc, 0, mac_entity.macConfig.schedulingRequestConfig);
}

void test_ogs_ran_rlc_init(abts_case *tc, void *data) {
    rlc_entity_t rlc_entity;

    memset(&rlc_entity, 0, sizeof(rlc_entity_t));

    ogs_ran_rlc_init(&rlc_entity);

    ABTS_INT_EQUAL(tc, RLC_MODE_AM, rlc_entity.rlcConfig.rlcMode);
    ABTS_INT_EQUAL(tc, 0, rlc_entity.rlcConfig.snFieldLength);
    ABTS_TRUE(tc, rlc_entity.rlcConfig.reorderingEnabled);
    ABTS_INT_EQUAL(tc, 0, rlc_entity.rlcConfig.maxRetx);
}

void test_ogs_ran_pdcp_init(abts_case *tc, void *data) {
    pdcp_entity_t pdcp_entity;

    memset(&pdcp_entity, 0, sizeof(pdcp_entity_t));

    ogs_ran_pdcp_init(&pdcp_entity);

    ABTS_INT_EQUAL(tc, 0, pdcp_entity.pdcpConfig.pdcpSNSizeUL);
    ABTS_INT_EQUAL(tc, 0, pdcp_entity.pdcpConfig.pdcpSNSizeDL);
    ABTS_TRUE(tc, pdcp_entity.pdcpConfig.integrityProtection);
    ABTS_INT_EQUAL(tc, 0, pdcp_entity.pdcpConfig.cipheringAlgorithm);
}

void test_ogs_ran_sdap_init(abts_case *tc, void *data) {
    sdap_entity_t sdap_entity;

    uint8_t static_sdap_data[SDAP_BUFFER_SIZE];
    sdap_entity.h.data = static_sdap_data;

    sdap_entity.h.size = 0;
    sdap_entity.qfi = DEFAULT_QFI;

    ogs_ran_sdap_init(&sdap_entity);

    ABTS_INT_EQUAL(tc, DEFAULT_QFI, sdap_entity.qfi);
    ABTS_INT_EQUAL(tc, 0, sdap_entity.h.size);
}

abts_suite *test_ogs_ran_context(abts_suite *suite) {
    suite = abts_add_suite(suite, "RAN Context Tests");

    abts_run_test(suite, test_ogs_ran_mac_init, NULL);
    abts_run_test(suite, test_ogs_ran_rlc_init, NULL);
    abts_run_test(suite, test_ogs_ran_pdcp_init, NULL);
    abts_run_test(suite, test_ogs_ran_sdap_init, NULL);

    return suite;
}

