#include "ran/ogs-ran-rach.h"

// Function to initiate the RACH procedure (Type-1 or Type-2)
void ogs_ran_initiate_rach_procedure(rach_procedure_t *rach_proc) {
    ogs_assert(rach_proc != NULL);

    ogs_info("Initiating RACH procedure: Type %d", rach_proc->is_type_1 ? 1 : 2);

    if (rach_proc->is_type_1) {
        ogs_info("Sending Msg1: Preamble %d", rach_proc->type_1_proc.msg1_preamble);
    } else {
        ogs_info("Sending MsgA: Preamble %d", rach_proc->type_2_proc.msg_a_preamble);
    }
}

