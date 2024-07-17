#include "smf/context.h"
#include "core/abts.h"

/*                  Flow description took from ./configs/open5gs/pcrf.yaml.in              */

/*
#          flow:
#            - direction: 2
#              description: "permit out icmp from any to assigned"
#            - direction: 1
#              description: "permit out icmp from any to assigned"
#            - direction: 2
#              description: "permit out udp from 10.200.136.98/32 23455 to assigned 1-65535"
#            - direction: 1
#              description: "permit out udp from 10.200.136.98/32 1-65535 to assigned 50021"
*/


/*                                      Test functions                                    */

void test_smf_bearer_tft_update_downlink_case1(abts_case *tc, void *data) {
    smf_bearer_t bearer;
    ogs_pfcp_pdr_t dl_pdr, ul_pdr;
    smf_pf_t pf_downlink, pf_downlink2;
    char *flow_description = "permit out icmp from any to assigned";

    memset(&bearer, 0, sizeof(smf_bearer_t));
    memset(&dl_pdr, 0, sizeof(ogs_pfcp_pdr_t));
    memset(&ul_pdr, 0, sizeof(ogs_pfcp_pdr_t));
    memset(&pf_downlink2, 0, sizeof(smf_pf_t));

    bearer.dl_pdr = &dl_pdr;
    bearer.ul_pdr = &ul_pdr;

    ogs_list_init(&bearer.pf_list);
    pf_downlink.direction = OGS_FLOW_DOWNLINK_ONLY;
    pf_downlink2.direction = OGS_FLOW_DOWNLINK_ONLY;
    pf_downlink.flow_description = flow_description;
    ogs_list_add(&bearer.pf_list, &pf_downlink.lnode);

    smf_bearer_tft_update(&bearer);

    ABTS_INT_EQUAL(tc, 1, dl_pdr.num_of_flow);
    ABTS_STR_EQUAL(tc, flow_description, dl_pdr.flow[0].description);
    ABTS_INT_EQUAL(tc, 1, dl_pdr.flow[0].fd);

    // Increment test
    ogs_list_add(&bearer.pf_list, &pf_downlink2.lnode);
    smf_bearer_tft_update(&bearer);
    ABTS_INT_EQUAL(tc, 2, dl_pdr.num_of_flow);
}

void test_smf_bearer_tft_update_downlink_case2(abts_case *tc, void *data) {
    smf_bearer_t bearer;
    ogs_pfcp_pdr_t dl_pdr, ul_pdr;
    smf_pf_t pf_downlink, pf_downlink2;
    char *flow_description = "permit out udp from 10.200.136.98/32 1-65535 to assigned 50021";

    memset(&bearer, 0, sizeof(smf_bearer_t));
    memset(&dl_pdr, 0, sizeof(ogs_pfcp_pdr_t));
    memset(&ul_pdr, 0, sizeof(ogs_pfcp_pdr_t));
    memset(&pf_downlink2, 0, sizeof(smf_pf_t));

    bearer.dl_pdr = &dl_pdr;
    bearer.ul_pdr = &ul_pdr;

    ogs_list_init(&bearer.pf_list);
    pf_downlink.direction = OGS_FLOW_DOWNLINK_ONLY;
    pf_downlink2.direction = OGS_FLOW_DOWNLINK_ONLY;
    pf_downlink.flow_description = flow_description;
    ogs_list_add(&bearer.pf_list, &pf_downlink.lnode);

    smf_bearer_tft_update(&bearer);

    ABTS_INT_EQUAL(tc, 1, dl_pdr.num_of_flow);
    ABTS_STR_EQUAL(tc, flow_description, dl_pdr.flow[0].description);
    ABTS_INT_EQUAL(tc, 1, dl_pdr.flow[0].fd);

    ogs_list_add(&bearer.pf_list, &pf_downlink2.lnode);
    smf_bearer_tft_update(&bearer);

    ABTS_INT_EQUAL(tc, 2, dl_pdr.num_of_flow);
}

void test_smf_bearer_tft_update_uplink_case1(abts_case *tc, void *data) {
    smf_bearer_t bearer;
    ogs_pfcp_pdr_t dl_pdr, ul_pdr;
    smf_pf_t pf_uplink, pf_uplink2;
    char *flow_description = "permit out icmp from any to assigned";

    memset(&bearer, 0, sizeof(smf_bearer_t));
    memset(&dl_pdr, 0, sizeof(ogs_pfcp_pdr_t));
    memset(&ul_pdr, 0, sizeof(ogs_pfcp_pdr_t));
    memset(&pf_uplink2, 0, sizeof(smf_pf_t));

    bearer.dl_pdr = &dl_pdr;
    bearer.ul_pdr = &ul_pdr;

    ogs_list_init(&bearer.pf_list);
    pf_uplink.direction = OGS_FLOW_UPLINK_ONLY;
    pf_uplink2.direction = OGS_FLOW_UPLINK_ONLY;
    pf_uplink.flow_description = flow_description;
    ogs_list_add(&bearer.pf_list, &pf_uplink.lnode);

    smf_bearer_tft_update(&bearer);

    ABTS_INT_EQUAL(tc, 1, ul_pdr.num_of_flow);
    ABTS_STR_EQUAL(tc, flow_description, ul_pdr.flow[0].description);
    ABTS_INT_EQUAL(tc, 1, ul_pdr.flow[0].fd);

    ogs_list_add(&bearer.pf_list, &pf_uplink2.lnode);
    smf_bearer_tft_update(&bearer);

    ABTS_INT_EQUAL(tc, 2, ul_pdr.num_of_flow);
}


void test_smf_bearer_tft_update_uplink_case2(abts_case *tc, void *data) {
    smf_bearer_t bearer;
    ogs_pfcp_pdr_t dl_pdr, ul_pdr;
    smf_pf_t pf_uplink, pf_uplink2;
    char *flow_description = "permit out udp from 10.200.136.98/32 23455 to assigned 1-65535";

    memset(&bearer, 0, sizeof(smf_bearer_t));
    memset(&dl_pdr, 0, sizeof(ogs_pfcp_pdr_t));
    memset(&ul_pdr, 0, sizeof(ogs_pfcp_pdr_t));
    memset(&pf_uplink2, 0, sizeof(smf_pf_t));

    bearer.dl_pdr = &dl_pdr;
    bearer.ul_pdr = &ul_pdr;

    ogs_list_init(&bearer.pf_list);
    pf_uplink.direction = OGS_FLOW_UPLINK_ONLY;
    pf_uplink2.direction = OGS_FLOW_UPLINK_ONLY;
    pf_uplink.flow_description = flow_description;
    ogs_list_add(&bearer.pf_list, &pf_uplink.lnode);

    smf_bearer_tft_update(&bearer);

    ABTS_INT_EQUAL(tc, 1, ul_pdr.num_of_flow);
    ABTS_STR_EQUAL(tc, flow_description, ul_pdr.flow[0].description);
    ABTS_INT_EQUAL(tc, 1, ul_pdr.flow[0].fd);

    ogs_list_add(&bearer.pf_list, &pf_uplink2.lnode);
    smf_bearer_tft_update(&bearer);

    ABTS_INT_EQUAL(tc, 2, ul_pdr.num_of_flow);
}

void test_smf_bearer_tft_update_bidirectional(abts_case *tc, void *data) {
    smf_bearer_t bearer;
    ogs_pfcp_pdr_t dl_pdr, ul_pdr;
    smf_pf_t pf_bidirectional, pf_bidirectional2;

    memset(&bearer, 0, sizeof(smf_bearer_t));
    memset(&dl_pdr, 0, sizeof(ogs_pfcp_pdr_t));
    memset(&ul_pdr, 0, sizeof(ogs_pfcp_pdr_t));
    memset(&pf_bidirectional2, 0, sizeof(smf_pf_t));

    bearer.dl_pdr = &dl_pdr;
    bearer.ul_pdr = &ul_pdr;

    ogs_list_init(&bearer.pf_list);
    pf_bidirectional.direction = OGS_FLOW_BIDIRECTIONAL;
    pf_bidirectional2.direction = OGS_FLOW_BIDIRECTIONAL;
    ogs_list_add(&bearer.pf_list, &pf_bidirectional.lnode);

    smf_bearer_tft_update(&bearer);

    ABTS_INT_EQUAL(tc, 1, dl_pdr.num_of_flow);
    ABTS_INT_EQUAL(tc, 1, dl_pdr.flow[0].fd);
    ABTS_INT_EQUAL(tc, 1, dl_pdr.flow[0].bid);
    ABTS_INT_EQUAL(tc, 1, ul_pdr.num_of_flow);
    ABTS_INT_EQUAL(tc, 1, ul_pdr.flow[0].bid);

    ogs_list_add(&bearer.pf_list, &pf_bidirectional2.lnode);
    smf_bearer_tft_update(&bearer);

    ABTS_INT_EQUAL(tc, 2, dl_pdr.num_of_flow);
    ABTS_INT_EQUAL(tc, 2, ul_pdr.num_of_flow);
}

void test_smf_bearer_tft_update_empty_filter_list(abts_case *tc, void *data) {
    smf_bearer_t bearer;
    ogs_pfcp_pdr_t dl_pdr, ul_pdr;

    memset(&bearer, 0, sizeof(smf_bearer_t));
    memset(&dl_pdr, 0, sizeof(ogs_pfcp_pdr_t));
    memset(&ul_pdr, 0, sizeof(ogs_pfcp_pdr_t));

    bearer.dl_pdr = &dl_pdr;
    bearer.ul_pdr = &ul_pdr;

    ogs_list_init(&bearer.pf_list);

    smf_bearer_tft_update(&bearer);

    ABTS_INT_EQUAL(tc, 0, dl_pdr.num_of_flow);
    ABTS_INT_EQUAL(tc, 0, ul_pdr.num_of_flow);
}

void test_smf_bearer_tft_update_multiple_filters(abts_case *tc, void *data) {
    smf_bearer_t bearer;
    ogs_pfcp_pdr_t dl_pdr, ul_pdr;
    smf_pf_t pf_downlink1, pf_downlink2;
    char *flow_description1 = "permit out icmp from any to assigned";
    char *flow_description2 = "permit out udp from 10.200.136.98/32 1-65535 to assigned 50021";

    memset(&bearer, 0, sizeof(smf_bearer_t));
    memset(&dl_pdr, 0, sizeof(ogs_pfcp_pdr_t));
    memset(&ul_pdr, 0, sizeof(ogs_pfcp_pdr_t));

    bearer.dl_pdr = &dl_pdr;
    bearer.ul_pdr = &ul_pdr;

    ogs_list_init(&bearer.pf_list);
    pf_downlink1.direction = OGS_FLOW_DOWNLINK_ONLY;
    pf_downlink1.flow_description = flow_description1;
    ogs_list_add(&bearer.pf_list, &pf_downlink1.lnode);

    pf_downlink2.direction = OGS_FLOW_DOWNLINK_ONLY;
    pf_downlink2.flow_description = flow_description2;
    ogs_list_add(&bearer.pf_list, &pf_downlink2.lnode);

    smf_bearer_tft_update(&bearer);

    ABTS_INT_EQUAL(tc, 2, dl_pdr.num_of_flow);
    ABTS_STR_EQUAL(tc, flow_description1, dl_pdr.flow[0].description);
    ABTS_STR_EQUAL(tc, flow_description2, dl_pdr.flow[1].description);
}

void test_smf_bearer_tft_update_mixed_filters(abts_case *tc, void *data) {
    smf_bearer_t bearer;
    ogs_pfcp_pdr_t dl_pdr, ul_pdr;
    smf_pf_t pf_downlink, pf_uplink;
    char *flow_description1 = "permit out icmp from any to assigned";
    char *flow_description2 = "permit out udp from 10.200.136.98/32 1-65535 to assigned 50021";

    memset(&bearer, 0, sizeof(smf_bearer_t));
    memset(&dl_pdr, 0, sizeof(ogs_pfcp_pdr_t));
    memset(&ul_pdr, 0, sizeof(ogs_pfcp_pdr_t));

    bearer.dl_pdr = &dl_pdr;
    bearer.ul_pdr = &ul_pdr;

    ogs_list_init(&bearer.pf_list);
    pf_downlink.direction = OGS_FLOW_DOWNLINK_ONLY;
    pf_downlink.flow_description = flow_description1;
    ogs_list_add(&bearer.pf_list, &pf_downlink.lnode);

    pf_uplink.direction = OGS_FLOW_UPLINK_ONLY;
    pf_uplink.flow_description = flow_description2;
    ogs_list_add(&bearer.pf_list, &pf_uplink.lnode);

    smf_bearer_tft_update(&bearer);

    ABTS_INT_EQUAL(tc, 1, dl_pdr.num_of_flow);
    ABTS_STR_EQUAL(tc, flow_description1, dl_pdr.flow[0].description);

    ABTS_INT_EQUAL(tc, 1, ul_pdr.num_of_flow);
    ABTS_STR_EQUAL(tc, flow_description2, ul_pdr.flow[0].description);
}

void test_smf_bearer_tft_update_large_number_of_filters(abts_case *tc, void *data) {
    smf_bearer_t bearer;
    ogs_pfcp_pdr_t dl_pdr, ul_pdr;
    smf_pf_t pf_downlink[100];
    char *flow_description = "permit out icmp from any to assigned";

    memset(&bearer, 0, sizeof(smf_bearer_t));
    memset(&dl_pdr, 0, sizeof(ogs_pfcp_pdr_t));
    memset(&ul_pdr, 0, sizeof(ogs_pfcp_pdr_t));

    bearer.dl_pdr = &dl_pdr;
    bearer.ul_pdr = &ul_pdr;

    ogs_list_init(&bearer.pf_list);

    for (int i = 0; i < 100; i++) {
        pf_downlink[i].direction = OGS_FLOW_DOWNLINK_ONLY;
        pf_downlink[i].flow_description = flow_description;
        ogs_list_add(&bearer.pf_list, &pf_downlink[i].lnode);
    }

    smf_bearer_tft_update(&bearer);

    ABTS_INT_EQUAL(tc, 100, dl_pdr.num_of_flow);
    for (int i = 0; i < 100; i++) {
        ABTS_STR_EQUAL(tc, flow_description, dl_pdr.flow[i].description);
    }
}

/*                           Test functions added to suite                             */

abts_suite *test_smf_bearer_tft_update(abts_suite *suite) {
    suite = abts_add_suite(suite, "smf_bearer_tft_update_tests");
    abts_run_test(suite, test_smf_bearer_tft_update_downlink_case1, NULL);
    abts_run_test(suite, test_smf_bearer_tft_update_downlink_case2, NULL);
    abts_run_test(suite, test_smf_bearer_tft_update_uplink_case1, NULL);
    abts_run_test(suite, test_smf_bearer_tft_update_uplink_case2, NULL);
    abts_run_test(suite, test_smf_bearer_tft_update_bidirectional, NULL);
    abts_run_test(suite, test_smf_bearer_tft_update_empty_filter_list, NULL);
    abts_run_test(suite, test_smf_bearer_tft_update_multiple_filters, NULL);
    abts_run_test(suite, test_smf_bearer_tft_update_mixed_filters, NULL);
    abts_run_test(suite, test_smf_bearer_tft_update_large_number_of_filters, NULL);
    return suite;
}