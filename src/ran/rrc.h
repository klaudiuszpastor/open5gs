#ifndef __RRC_H
#define __RRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define RLC_AM 0
#define RLC_UM 1

typedef enum {
    RRC_SETUP_REQUEST,
    RRC_SETUP,
    RRC_SETUP_COMPLETE
} rrc_message_type_t;

typedef struct {
    uint8_t mode;  // AM or UM
    uint8_t sn_field_length;
    uint8_t t_poll_retransmit;
    uint8_t t_reassembly;
    uint8_t t_status_prohibit;
} rlc_config_t;

typedef struct {
    uint8_t logicalChannelId;
    uint8_t priority;
    uint8_t lchGroup;
    uint8_t bucketSizeDuration;
} mac_config_t;

typedef struct {
    uint32_t mmeCode;      
    uint32_t mTmsi;        
} ue_identity_t;

typedef struct {
    uint8_t logicalChannelId;
    uint8_t priority;
    uint8_t lcGroup;
    uint8_t pdcpConfig;    
    rlc_config_t rlcConfig;     
} rb_config_t;

typedef struct {
    uint8_t epsMobileIdentity;    
    uint8_t ueNetworkCapability;  
    uint8_t additionalUpdateType; 
    uint8_t lastVisitedRegisteredTAI; 
    uint8_t drxParameter;         
} nas_attach_request_content_t;

typedef struct {
    uint16_t rand;
    uint16_t autn;
} nas_authentication_request_content_t;

typedef struct {
    uint8_t selectedEncryptionAlgorithm;  
    uint8_t selectedIntegrityAlgorithm;   
    uint8_t nasSecurityAlgorithms;        
    uint8_t imeisvRequest;               
} nas_security_mode_command_content_t;

typedef struct {
    uint8_t messageType;
    uint8_t protocolDiscriminator;
    uint8_t securityHeaderType;
    uint8_t messageAuthenticationCode;
    union {
        nas_attach_request_content_t attachRequest;
        nas_authentication_request_content_t authenticationRequest;
        nas_security_mode_command_content_t securityModeCommand;
    };
} nas_message_content_t;

typedef struct {
    uint8_t messageType;
    uint8_t protocolDiscriminator;
    uint8_t nasSecurityHeader;
    nas_message_content_t messageContent; 
} nas_message_t;


typedef struct {
    ue_identity_t ueIdentity;            
    uint8_t establishmentCause;    //Establishment cause (e.g., emergency, highPriority)      
} rrc_setup_request_t;

typedef struct {
    rb_config_t radioBearerConfig; 
} rrc_setup_t;

typedef struct {
    nas_message_t NASMessage;  
} rrc_setup_complete_t;

//rrc_establishment.c
void send_message_to_mac(rrc_message_type_t msg_type, void* msg, uint16_t msg_size);
void* receive_message_from_mac(rrc_message_type_t* msg_type);
void rrc_connection_establishment();

//rrc_reconfiguration.c
void configure_rlc(rlc_config_t *config);
void configure_mac(mac_config_t *config);
void rrc_reconfiguration(rlc_config_t *rlc_config, mac_config_t *mac_config, uint8_t sync_needed);

#ifdef __cplusplus
}
#endif

#endif /* __RRC_H */