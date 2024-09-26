#include "abts.h"
#include "ran/ogs-ran-rrc.h"
#include <string.h>

void test_configure_pdcp(abts_case *tc, void *data) {
    pdcp_config_t pdcp_config;
    memset(&pdcp_config, 0, sizeof(pdcp_config_t));

    configure_pdcp(&pdcp_config);

    ABTS_INT_EQUAL(tc, 12, pdcp_config.pdcpSNSizeUL);
    ABTS_INT_EQUAL(tc, 12, pdcp_config.pdcpSNSizeDL);
    ABTS_INT_EQUAL(tc, 1, pdcp_config.integrityProtection);
    ABTS_INT_EQUAL(tc, 2, pdcp_config.cipheringAlgorithm);
}

void test_configure_rlc(abts_case *tc, void *data) {
    rlc_config_t rlc_config;
    memset(&rlc_config, 0, sizeof(rlc_config_t));

    configure_rlc(&rlc_config);

    ABTS_INT_EQUAL(tc, 1, rlc_config.rlcMode);
    ABTS_INT_EQUAL(tc, 4, rlc_config.maxRetx);
    ABTS_INT_EQUAL(tc, 30, rlc_config.snFieldLength);
    ABTS_INT_EQUAL(tc, 50, rlc_config.pollRetransmit);
    ABTS_INT_EQUAL(tc, 1, rlc_config.pollByte);
    ABTS_INT_EQUAL(tc, 2, rlc_config.pollPdu);
}

void test_configure_mac(abts_case *tc, void *data) {
    mac_config_t mac_config;
    memset(&mac_config, 0, sizeof(mac_config_t));

    configure_mac(&mac_config);

    ABTS_INT_EQUAL(tc, 1, mac_config.logicalChannelId);
    ABTS_INT_EQUAL(tc, 5, mac_config.priority);
    ABTS_INT_EQUAL(tc, 1, mac_config.lcGroup);
    ABTS_INT_EQUAL(tc, 1, mac_config.schedulingRequestConfig);
}

void test_rrc_reconfiguration(abts_case *tc, void *data) {
    rb_config_t rb_config;
    memset(&rb_config, 0, sizeof(rb_config_t));

    rrc_reconfiguration(&rb_config);

    ABTS_INT_EQUAL(tc, 1, rb_config.rbId);
    ABTS_INT_EQUAL(tc, 12, rb_config.pdcpConfig.pdcpSNSizeUL);
    ABTS_INT_EQUAL(tc, 12, rb_config.pdcpConfig.pdcpSNSizeDL);
    ABTS_INT_EQUAL(tc, 1, rb_config.pdcpConfig.integrityProtection);
    ABTS_INT_EQUAL(tc, 2, rb_config.pdcpConfig.cipheringAlgorithm);

    ABTS_INT_EQUAL(tc, 1, rb_config.rlcConfig.rlcMode);
    ABTS_INT_EQUAL(tc, 4, rb_config.rlcConfig.maxRetx);
    ABTS_INT_EQUAL(tc, 30, rb_config.rlcConfig.snFieldLength);

    ABTS_INT_EQUAL(tc, 1, rb_config.macConfig.logicalChannelId);
    ABTS_INT_EQUAL(tc, 5, rb_config.macConfig.priority);
}

void test_send_rrc_reconfiguration_message(abts_case *tc, void *data) {
    rrc_reconfiguration_t rrc_config;
    memset(&rrc_config, 0, sizeof(rrc_reconfiguration_t));

    rrc_config.rbId = 1;
    send_rrc_reconfiguration_message(&rrc_config);

    ABTS_INT_EQUAL(tc, 1, rrc_config.rbId);
}

abts_suite *test_ogs_ran_rrc_reconfiguration(abts_suite *suite) {
    suite = abts_add_suite(suite, "RAN RRC Reconfiguration Tests");
    abts_run_test(suite, test_configure_pdcp, NULL);
    abts_run_test(suite, test_configure_rlc, NULL);
    abts_run_test(suite, test_configure_mac, NULL);
    abts_run_test(suite, test_rrc_reconfiguration, NULL);
    abts_run_test(suite, test_send_rrc_reconfiguration_message, NULL);
    return suite;
}
