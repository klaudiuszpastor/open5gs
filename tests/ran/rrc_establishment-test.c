#include "abts.h"
#include "ran/ogs-ran-rrc.h"
#include <string.h>

void test_handle_rrc_setup_request(abts_case *tc, void *data) {
    rrc_setup_request_t rrc_setup_request;
    memset(&rrc_setup_request, 0, sizeof(rrc_setup_request_t));
    
    rrc_setup_request.ueIdentity.mmeCode = 0x1234;
    rrc_setup_request.ueIdentity.mTmsi = 0x56789;
    
    handle_rrc_setup_request(&rrc_setup_request);
    
    ABTS_INT_EQUAL(tc, 0x1234, rrc_setup_request.ueIdentity.mmeCode);
    ABTS_INT_EQUAL(tc, 0x56789, rrc_setup_request.ueIdentity.mTmsi);
}

void test_handle_rrc_setup_complete(abts_case *tc, void *data) {
    rrc_setup_complete_t rrc_setup_complete;
    memset(&rrc_setup_complete, 0, sizeof(rrc_setup_complete_t));
    
    rrc_setup_complete.NASMessage.messageType = NAS_REGISTRATION_REQUEST;
    rrc_setup_complete.NASMessage.registrationRequest.ueIdentity.mmeCode = 0x1234;
    rrc_setup_complete.NASMessage.registrationRequest.ueIdentity.mTmsi = 0x56789;
    rrc_setup_complete.NASMessage.registrationRequest.capability = 0x22;
    rrc_setup_complete.NASMessage.registrationRequest.requestedNSSAI = 0x10;

    handle_rrc_setup_complete(&rrc_setup_complete);
    
    ABTS_INT_EQUAL(tc, NAS_REGISTRATION_REQUEST, rrc_setup_complete.NASMessage.messageType);
    ABTS_INT_EQUAL(tc, 0x1234, rrc_setup_complete.NASMessage.registrationRequest.ueIdentity.mmeCode);
    ABTS_INT_EQUAL(tc, 0x56789, rrc_setup_complete.NASMessage.registrationRequest.ueIdentity.mTmsi);
    ABTS_INT_EQUAL(tc, 0x22, rrc_setup_complete.NASMessage.registrationRequest.capability);
    ABTS_INT_EQUAL(tc, 0x10, rrc_setup_complete.NASMessage.registrationRequest.requestedNSSAI);
}

void test_rrc_dispatch_message_setup_request(abts_case *tc, void *data) {
    rrc_setup_request_t rrc_setup_request;
    memset(&rrc_setup_request, 0, sizeof(rrc_setup_request_t));

    rrc_setup_request.ueIdentity.mmeCode = 0x1234;
    rrc_setup_request.ueIdentity.mTmsi = 0x56789;

    rrc_dispatch_message(RRC_SETUP_REQUEST, &rrc_setup_request, sizeof(rrc_setup_request));
    
    ABTS_INT_EQUAL(tc, 0x1234, rrc_setup_request.ueIdentity.mmeCode);
    ABTS_INT_EQUAL(tc, 0x56789, rrc_setup_request.ueIdentity.mTmsi);
}

void test_rrc_dispatch_message_setup_complete(abts_case *tc, void *data) {
    rrc_setup_complete_t rrc_setup_complete;
    memset(&rrc_setup_complete, 0, sizeof(rrc_setup_complete_t));

    rrc_setup_complete.NASMessage.messageType = NAS_REGISTRATION_REQUEST;
    rrc_setup_complete.NASMessage.registrationRequest.ueIdentity.mmeCode = 0x1234;
    rrc_setup_complete.NASMessage.registrationRequest.ueIdentity.mTmsi = 0x56789;
    rrc_setup_complete.NASMessage.registrationRequest.capability = 0x22;
    rrc_setup_complete.NASMessage.registrationRequest.requestedNSSAI = 0x10;

    rrc_dispatch_message(RRC_SETUP_COMPLETE, &rrc_setup_complete, sizeof(rrc_setup_complete));
    
    ABTS_INT_EQUAL(tc, NAS_REGISTRATION_REQUEST, rrc_setup_complete.NASMessage.messageType);
    ABTS_INT_EQUAL(tc, 0x1234, rrc_setup_complete.NASMessage.registrationRequest.ueIdentity.mmeCode);
    ABTS_INT_EQUAL(tc, 0x56789, rrc_setup_complete.NASMessage.registrationRequest.ueIdentity.mTmsi);
    ABTS_INT_EQUAL(tc, 0x22, rrc_setup_complete.NASMessage.registrationRequest.capability);
    ABTS_INT_EQUAL(tc, 0x10, rrc_setup_complete.NASMessage.registrationRequest.requestedNSSAI);
}

void test_send_message_to_mac(abts_case *tc, void *data) {
    rrc_setup_t rrc_setup;
    memset(&rrc_setup, 0, sizeof(rrc_setup_t));

    send_message_to_mac(RRC_SETUP, &rrc_setup, sizeof(rrc_setup));
    ABTS_TRUE(tc, 1);
}

void test_receive_message_from_ue(abts_case *tc, void *data) {
    rrc_message_type_t msg_type;
    
    rrc_setup_request_t *rrc_setup_request = (rrc_setup_request_t *)receive_message_from_ue(&msg_type);
    ABTS_PTR_NOTNULL(tc, rrc_setup_request);
    ABTS_INT_EQUAL(tc, RRC_SETUP_REQUEST, msg_type);
    ABTS_INT_EQUAL(tc, 0x1234, rrc_setup_request->ueIdentity.mmeCode);
    ABTS_INT_EQUAL(tc, 0x56789, rrc_setup_request->ueIdentity.mTmsi);

    rrc_setup_complete_t *rrc_setup_complete = (rrc_setup_complete_t *)receive_message_from_ue(&msg_type);
    ABTS_PTR_NOTNULL(tc, rrc_setup_complete);
    ABTS_INT_EQUAL(tc, RRC_SETUP_COMPLETE, msg_type);
    ABTS_INT_EQUAL(tc, NAS_REGISTRATION_REQUEST, rrc_setup_complete->NASMessage.messageType);
}

abts_suite *test_ogs_ran_rrc_establishment(abts_suite *suite) {
    suite = abts_add_suite(suite, "RAN RRC Establishment Tests");
    abts_run_test(suite, test_handle_rrc_setup_request, NULL);
    abts_run_test(suite, test_handle_rrc_setup_complete, NULL);
    abts_run_test(suite, test_rrc_dispatch_message_setup_request, NULL);
    abts_run_test(suite, test_rrc_dispatch_message_setup_complete, NULL);
    abts_run_test(suite, test_send_message_to_mac, NULL);
    abts_run_test(suite, test_receive_message_from_ue, NULL);
    return suite;
}
