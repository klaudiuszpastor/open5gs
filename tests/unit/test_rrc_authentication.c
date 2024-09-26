/*
 * Copyright (C) 2024 by Your Name <your.email@example.com>
 *
 * This file is part of Your Project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "ogs-core.h"
#include "core/abts.h"
#include "ran/ogs-ran-rrc.h"

static void test_rrc_auth_success(abts_case *tc, void *data)
{
    ogs_info("Testing successful authentication");

    rrc_setup_complete_t setup_complete = {
        .NASMessage = {
            .messageType = NAS_ATTACH_REQUEST,
            .authRequest = {
                .rand = 0xA1B2,   
                .autn = 0xC3D4,
                .ngKsi = 0x05    
            }
        }
    };

    perform_authentication(&setup_complete);

    ABTS_INT_EQUAL(tc, RAND_GLOBAL, 0xA1B2);
    ABTS_INT_EQUAL(tc, AUTN_GLOBAL, 0xC3D4);
    ABTS_INT_EQUAL(tc, NGKSI_GLOBAL, 0x05);  

    uint16_t ue_res = 0x1234;
    ABTS_TRUE(tc, handle_authentication_response(ue_res));
}


abts_suite *test_rrc_authentication(abts_suite *suite)
{
    suite = abts_add_suite(suite, "RRC Authentication Test");

    abts_run_test(suite, test_rrc_auth_success, NULL);

    return suite;
}