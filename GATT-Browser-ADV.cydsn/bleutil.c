#include "bleutil.h"
#include <stdio.h>
#include <project.h>
const char *bleGetStateString()
{
    switch(CyBle_GetState())
    {
        case CYBLE_STATE_STOPPED:
        return "CYBLE_STATE_STOPPED";
        break;
        case CYBLE_STATE_INITIALIZING:
            return "CYBLE_STATE_INITIALIZING";
        break;
        case CYBLE_STATE_CONNECTED:
            return "CYBLE_STATE_CONNECTED";
        break;
        case CYBLE_STATE_SCANNING:
            return "CYBLE_STATE_SCANNING";
        break;
  
        case CYBLE_STATE_CONNECTING:
            return "CYBLE_STATE_CONNECTING";
        break;
        case CYBLE_STATE_DISCONNECTED:
            return "CYBLE_STATE_DISCONNECTED";
        break;
     
    }
    
    CYASSERT(1); // There is some mode that it "cant" be in
    return 0;
}
    
const char *bleGetEventString(uint32_t event)
{
	switch(event)
	{
		case CYBLE_EVT_HOST_INVALID :
			return("CYBLE_EVT_HOST_INVALID");
			break;
		
		case CYBLE_EVT_STACK_ON :
			return("CYBLE_EVT_STACK_ON");
			break;	
		case CYBLE_EVT_TIMEOUT :
			return("CYBLE_EVT_TIMEOUT");
			break;	
		case CYBLE_EVT_HARDWARE_ERROR :
			return("CYBLE_EVT_HARDWARE_ERROR");
			break;				
		case CYBLE_EVT_HCI_STATUS :
			return("CYBLE_EVT_HCI_STATUS");
			break;				
		case CYBLE_EVT_STACK_BUSY_STATUS :
			return("CYBLE_EVT_STACK_BUSY_STATUS");
			break;				
		case CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT :
			return("CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT");
			break;				
		case CYBLE_EVT_GAP_AUTH_REQ :
			return("CYBLE_EVT_GAP_AUTH_REQ");
			break;				
		case CYBLE_EVT_GAP_PASSKEY_ENTRY_REQUEST :
			return("CYBLE_EVT_GAP_PASSKEY_ENTRY_REQUEST");
			break;				
		case CYBLE_EVT_GAP_PASSKEY_DISPLAY_REQUEST :
			return("CYBLE_EVT_GAP_PASSKEY_DISPLAY_REQUEST");
			break;				
		case CYBLE_EVT_GAP_AUTH_COMPLETE :
			return("CYBLE_EVT_GAP_AUTH_COMPLETE");
			break;				
		case CYBLE_EVT_GAP_AUTH_FAILED :
			return("CYBLE_EVT_GAP_AUTH_FAILED");
			break;				
		case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP :
			return("CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP");
			break;				
		case CYBLE_EVT_GAP_DEVICE_CONNECTED :
			return("CYBLE_EVT_GAP_DEVICE_CONNECTED");
			break;				
		case CYBLE_EVT_GAP_DEVICE_DISCONNECTED :
			return("CYBLE_EVT_GAP_DEVICE_DISCONNECTED");
			break;				
		case CYBLE_EVT_GAP_ENCRYPT_CHANGE :
			return("CYBLE_EVT_GAP_ENCRYPT_CHANGE");
			break;				
		case CYBLE_EVT_GAP_CONNECTION_UPDATE_COMPLETE :
			return("CYBLE_EVT_GAP_CONNECTION_UPDATE_COMPLETE");
			break;				
		case CYBLE_EVT_GAPC_SCAN_START_STOP :
			return("CYBLE_EVT_GAPC_SCAN_START_STOP");
			break;				
		case CYBLE_EVT_GAP_KEYINFO_EXCHNGE_CMPLT :
			return("CYBLE_EVT_GAP_KEYINFO_EXCHNGE_CMPLT");
			break;				
		case CYBLE_EVT_GATTC_ERROR_RSP :
			return("CYBLE_EVT_GATTC_ERROR_RSP");
			break;				
		case CYBLE_EVT_GATT_CONNECT_IND :
			return("CYBLE_EVT_GATT_CONNECT_IND");
			break;				
		case CYBLE_EVT_GATT_DISCONNECT_IND :
			return("CYBLE_EVT_GATT_DISCONNECT_IND");
			break;				
		case CYBLE_EVT_GATTS_XCNHG_MTU_REQ :
			return("CYBLE_EVT_GATTS_XCNHG_MTU_REQ");
			break;				
		case CYBLE_EVT_GATTC_XCHNG_MTU_RSP :
			return("CYBLE_EVT_GATTC_XCHNG_MTU_RSP");
			break;				
		case CYBLE_EVT_GATTC_READ_BY_GROUP_TYPE_RSP :
			return("CYBLE_EVT_GATTC_READ_BY_GROUP_TYPE_RSP");
			break;				
		case CYBLE_EVT_GATTC_READ_BY_TYPE_RSP :
			return("CYBLE_EVT_GATTC_READ_BY_TYPE_RSP");
			break;				
		case CYBLE_EVT_GATTC_FIND_INFO_RSP :
			return("CYBLE_EVT_GATTC_FIND_INFO_RSP");
			break;				
		case CYBLE_EVT_GATTC_FIND_BY_TYPE_VALUE_RSP :
			return("CYBLE_EVT_GATTC_FIND_BY_TYPE_VALUE_RSP");
			break;				
		case CYBLE_EVT_GATTC_READ_RSP :
			return("CYBLE_EVT_GATTC_READ_RSP");
			break;				
		case CYBLE_EVT_GATTC_READ_BLOB_RSP :
			return("CYBLE_EVT_GATTC_READ_BLOB_RSP");
			break;				
		case CYBLE_EVT_GATTC_READ_MULTI_RSP :
			return("CYBLE_EVT_GATTC_READ_MULTI_RSP");
			break;				
		case CYBLE_EVT_GATTS_WRITE_REQ :
			return("CYBLE_EVT_GATTS_WRITE_REQ");
			break;				
		case CYBLE_EVT_GATTC_WRITE_RSP :
			return("CYBLE_EVT_GATTC_WRITE_RSP");
			break;				
		case CYBLE_EVT_GATTS_WRITE_CMD_REQ :
			return("CYBLE_EVT_GATTS_WRITE_CMD_REQ");
			break;				
		case CYBLE_EVT_GATTS_PREP_WRITE_REQ :
			return("CYBLE_EVT_GATTS_PREP_WRITE_REQ");
			break;				
		case CYBLE_EVT_GATTS_EXEC_WRITE_REQ :
			return("CYBLE_EVT_GATTS_EXEC_WRITE_REQ");
			break;				
		case CYBLE_EVT_GATTC_EXEC_WRITE_RSP :
			return("CYBLE_EVT_GATTC_EXEC_WRITE_RSP");
			break;				
		case CYBLE_EVT_GATTC_HANDLE_VALUE_NTF :
			return("CYBLE_EVT_GATTC_HANDLE_VALUE_NTF");
			break;				
		case CYBLE_EVT_GATTC_HANDLE_VALUE_IND :
			return("CYBLE_EVT_GATTC_HANDLE_VALUE_IND");
			break;				
		case CYBLE_EVT_GATTS_HANDLE_VALUE_CNF :
			return("CYBLE_EVT_GATTS_HANDLE_VALUE_CNF");
			break;				
		case CYBLE_EVT_GATTS_DATA_SIGNED_CMD_REQ :
			return("CYBLE_EVT_GATTS_DATA_SIGNED_CMD_REQ");
			break;				
		case CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_REQ :
			return("CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_REQ");
			break;				
		case CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP :
			return("CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP");
			break;				
		case CYBLE_EVT_L2CAP_COMMAND_REJ :
			return("CYBLE_EVT_L2CAP_COMMAND_REJ");
			break;				
		case CYBLE_EVT_L2CAP_CBFC_CONN_IND :
			return("CYBLE_EVT_L2CAP_CBFC_CONN_IND");
			break;				
		case CYBLE_EVT_L2CAP_CBFC_CONN_CNF :
			return("CYBLE_EVT_L2CAP_CBFC_CONN_CNF");
			break;				
		case CYBLE_EVT_L2CAP_CBFC_DISCONN_IND :
			return("CYBLE_EVT_L2CAP_CBFC_DISCONN_IND");
			break;				
		case CYBLE_EVT_L2CAP_CBFC_DISCONN_CNF :
			return("CYBLE_EVT_L2CAP_CBFC_DISCONN_CNF");
			break;				
		case CYBLE_EVT_L2CAP_CBFC_DATA_READ :
			return("CYBLE_EVT_L2CAP_CBFC_DATA_READ");
			break;				
		case CYBLE_EVT_L2CAP_CBFC_RX_CREDIT_IND :
			return("CYBLE_EVT_L2CAP_CBFC_RX_CREDIT_IND");
			break;				
		case CYBLE_EVT_L2CAP_CBFC_TX_CREDIT_IND :
			return("CYBLE_EVT_L2CAP_CBFC_TX_CREDIT_IND");
			break;				
		case CYBLE_EVT_L2CAP_CBFC_DATA_WRITE_IND :
			return("CYBLE_EVT_L2CAP_CBFC_DATA_WRITE_IND");
			break;				
		case CYBLE_EVT_PENDING_FLASH_WRITE :
			return("CYBLE_EVT_PENDING_FLASH_WRITE");
			break;				
		case CYBLE_EVT_MAX :
			return("CYBLE_EVT_MAX");
			break;				
			
		default:
            return 0;
		break;
	}
}

char *bleFormatBDAddr(char *buff,uint8 *bdAddr) 
{
    sprintf(buff,"%02X:%02X:%02X:%02X:%02X:%02X",bdAddr[5],bdAddr[4],bdAddr[3],bdAddr[2],bdAddr[1],bdAddr[0]);
    return buff;
}

char *bleFormat128bitUUID(char *buff,uint8_t *bytes)
{
    sprintf(buff,"%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
        bytes[15],bytes[14],bytes[13],bytes[12],
        bytes[11],bytes[10],
        bytes[9],bytes[8],
        bytes[7],bytes[6],
        bytes[5],bytes[4],bytes[3],bytes[2],bytes[1],bytes[0]);

    return buff;    
}

char *bleFormat32bitUUID(char *buff,uint8_t *bytes)
{
    sprintf(buff,"%02X%02X%02X%02X",
        bytes[3],bytes[2],bytes[1],bytes[0]);

    return buff;    
}

char *bleFormat16bitUUID(char *buff,uint8_t *bytes)
{
    sprintf(buff,"%02X%02X",
        bytes[1],bytes[0]);

    return buff;    
}