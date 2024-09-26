
A
    //Michal: you have to run my function, from your rrc_establishment.c file
    //insert this code into your file.

    #include "registration_request.c"

    run_NGAP_Initial_UE_Message(&registrationRequest, &rrc_setup_complete_t.establishmentCause); //my function is running

B
    //Michal: you have to receive arguments from my function, in your rrc_reconfiguration.c file

    #include "registration_accept.c"

    rrc_reconfiguration_from_gNB(registrationAccept, AMF_UE_NGAP_ID, RAN_UE_NGAP_ID); //The induction (in my file) of function in your rrc_reconfiguration.c file.

    //This function should look like this one below or similar:

    void rrc_reconfiguration_from_gNB(registrationAccept_t registrationAccept, uint32_t AMF_UE_NGAP_ID, uint32_t RAN_UE_NGAP_ID){
        //do something or nothing;
    }












