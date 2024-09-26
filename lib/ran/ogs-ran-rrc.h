#ifndef __OGS_RAN_RRC_H
#define __OGS_RAN_RRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define NAS_ATTACH_REQUEST           0x01
#define NAS_AUTHENTICATION_REQUEST   0x02
#define NAS_SECURITY_MODE_COMMAND    0x03
#define NAS_REGISTRATION_REQUEST     0x04

typedef enum {
    RRC_SETUP_REQUEST,
    RRC_SETUP,
    RRC_SETUP_COMPLETE
} rrc_message_type_t;

typedef struct {
    uint8_t rlcMode;  
    uint8_t snFieldLength;  
    bool reorderingEnabled;  
    uint16_t maxRetx;  
    uint8_t pollPdu;  
    uint8_t pollByte;  
    uint16_t pollRetransmit;  
} rlc_config_t;

typedef struct {
    uint8_t pdcpSNSizeUL;
    uint8_t pdcpSNSizeDL;
    uint8_t integrityProtection;
    uint8_t cipheringAlgorithm;
} pdcp_config_t;

typedef struct {
    uint8_t logicalChannelId;
    uint8_t priority;
    uint8_t lcGroup;
    uint8_t schedulingRequestConfig;
} mac_config_t;

typedef struct {
    uint8_t rbId;
    pdcp_config_t pdcpConfig;    
    rlc_config_t rlcConfig; 
    mac_config_t macConfig;    
} rb_config_t;

typedef struct {
    uint32_t mmeCode;      
    uint32_t mTmsi;        
} ue_identity_t;

typedef struct {
    rb_config_t radioBearerConfig; 
} rrc_setup_t;

typedef struct {
    ue_identity_t ueIdentity;            
        
} rrc_setup_request_t;

typedef struct {
    ue_identity_t ueIdentity;  
    uint8_t capability;  
    uint8_t requestedNSSAI; 
    uint8_t lastVisitedTAI; 
    bool isEmergency;
} nas_registration_request_t;

typedef struct {
    uint8_t epsMobileIdentity;    
    uint8_t ueNetworkCapability;  
    uint8_t additionalUpdateType; 
    uint8_t lastVisitedRegisteredTAI; 
    uint8_t drxParameter; 
    bool isInitialAttach;
    uint8_t attachType;        
} nas_attach_request_t;

typedef struct {
    uint16_t rand;
    uint16_t autn;
    uint8_t ngKsi;
} nas_authentication_request_t;

typedef struct {
    uint8_t selectedEncryptionAlgorithm;  
    uint8_t selectedIntegrityAlgorithm;   
    uint8_t nasSecurityAlgorithms;        
    uint8_t imeisvRequest;               
} nas_security_mode_command_t;

typedef struct {
    uint8_t messageType;
    uint8_t protocolDiscriminator;
    uint8_t securityHeaderType;
    uint8_t messageAuthenticationCode;
    bool integrityProtected;
    bool ciphered;
    union {
        nas_registration_request_t registrationRequest;
        nas_attach_request_t attachRequest;
        nas_authentication_request_t authRequest;
        nas_security_mode_command_t securityModeCommand;
    };
} nas_dedicated_message_t;

typedef struct {
    ue_identity_t ueIdentity; 
    uint8_t establishmentCause;  // Establishment cause (e.g., emergency, highPriority)  
    nas_dedicated_message_t NASMessage;  
} rrc_setup_complete_t;

//rrc_establishment.c
void handle_rrc_setup_request(rrc_setup_request_t* setup_request);
void handle_rrc_setup_complete(rrc_setup_complete_t* setup_complete);

void rrc_dispatch_message(rrc_message_type_t msg_type, void* msg, uint16_t msg_size);
void rrc_connection_establishment(void); 
void send_message_to_mac(rrc_message_type_t msg_type, void* msg, uint16_t msg_size);
void* receive_message_from_ue(rrc_message_type_t* msg_type);

//rrc_reconfiguration.c
void configure_rlc(rlc_config_t *config);
void configure_mac(mac_config_t *config);
void configure_pdcp(pdcp_config_t *config);
void rrc_reconfiguration(rb_config_t *rbConfig);

//authentication.c
void initiate_authentication(rrc_setup_complete_t* setup_complete);
uint16_t RAND_GLOBAL;
uint16_t AUTN_GLOBAL;
uint8_t NGKSI_GLOBAL;

#ifdef __cplusplus
}
#endif

#endif /* __OGS_RAN_RRC_H */
