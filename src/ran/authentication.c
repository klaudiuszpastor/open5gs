#include "ogs-ran-common.h"
#include "ogs-core.h"
#include "ran/ogs-ran-rrc.h"

void initiate_authentication(rrc_setup_complete_t* setup_complete) {
    RAND_GLOBAL = setup_complete->NASMessage.authRequest.rand;
    AUTN_GLOBAL = setup_complete->NASMessage.authRequest.autn;
    NGKSI_GLOBAL = setup_complete->NASMessage.authRequest.ngKsi;

    ogs_info("RAND: 0x%x, AUTN: 0x%x, ngKsi: 0x%x",
        RAND_GLOBAL, AUTN_GLOBAL, NGKSI_GLOBAL);
}