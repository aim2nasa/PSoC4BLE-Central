
#include <project.h>
#include <stdio.h>
#include "util.h"
#include "bleutil.h"
#include "ble-adv-utils.h"

const char *aBunchOfDashes = "--------------------------------------------------------------------------------------------------------------\n";
int sysTime;
char buff[128];

void incSysTime()
{
    sysTime = sysTime + 1;
}

typedef struct device {
    int lastSeen;
    uint8 bdAddr[6];
    int8 rssi;
    int advLength;
    int scanLength;
    CYBLE_GAPC_ADV_EVENT_T type;
    uint8  peerAddrType;
    uint8_t advData[32];
    uint8_t scanData[32];
    struct device *next;
} device_t;

#define MAX_DEVICES 10
device_t deviceList[MAX_DEVICES];
device_t *lastPrintList[MAX_DEVICES];
int deviceCount=0;
device_t headDevice;

void addAdvPacket(CYBLE_GAPC_ADV_REPORT_T * advPacket)
{
    device_t *current = headDevice.next;
    device_t *previous = &headDevice;
    
    
    while(current)
    {
        if(memcmp(advPacket->peerBdAddr,current->bdAddr,6) == 0)
        {   
            break;
        }
        previous = current;
        current = current->next;
    }
    
    // This is the first time we have seen the BD Addr
    if(current == 0)
    {
        if(deviceCount<MAX_DEVICES)
        {
        
            printf("Added %d %s\n",deviceCount+1,bleFormatBDAddr(buff,advPacket->peerBdAddr));
            memcpy(deviceList[deviceCount].bdAddr,advPacket->peerBdAddr,6);
            current->peerAddrType = advPacket->peerAddrType;
            current = &deviceList[deviceCount];
            current->next = 0;
            deviceCount = deviceCount + 1;
        }
        else // replace the last one... which is AKA previous
        {
            printf("Replace %s\n",bleFormatBDAddr(buff,advPacket->peerBdAddr));
            
            current = previous;
            current->peerAddrType = advPacket->peerAddrType;
            memcpy(current->bdAddr,advPacket->peerBdAddr,6);
            current->advLength=0;
            current->scanLength=0;
            current->next = 0; // last one
           
            // You need to find the previous one to the last element on the list
            // so that you can get the list reset
            device_t *findPointer = headDevice.next;
            previous = &headDevice;
            while(findPointer != current)
            {
                previous = findPointer;
                findPointer = findPointer->next;
            }
            
            
        }
        
    }
    
    current->lastSeen = sysTime;
    current->rssi = advPacket->rssi;
    
    // move the current one to the start of the list
    previous->next = current->next; 
    current->next = headDevice.next;
    headDevice.next = current;
    
    // copy the packet
    if(advPacket->eventType == CYBLE_GAPC_SCAN_RSP)
    {
        current->scanLength = advPacket->dataLen;
        memcpy(current->scanData,advPacket->data,advPacket->dataLen);
    }
    else
    {
        current->advLength = advPacket->dataLen;
        memcpy(current->advData,advPacket->data,advPacket->dataLen);
        current->type = advPacket->eventType;
    }
}

void printDeviceTable()
{
    int i=0;
    int j;
    device_t *current;
    current = headDevice.next;
    printf(aBunchOfDashes);
    printf("#  BDAddr\t\tRSSI\tLastSeen\tSize\tPacket\n");
    printf(aBunchOfDashes);

    while(current)
    {
        printf("%d  %s\t%d\t%d\t\t%d\t",i,bleFormatBDAddr(buff,current->bdAddr),
        current->rssi,
        (sysTime-current->lastSeen),current->advLength);
        
        for(j=0;j<current->advLength;j++)
        {
            printf("%02X",current->advData[j]);  
        }
        printf("\n");
        
        blePrintAdvPacketData(current->advData,current->advLength,"   \t\t\t\t\t\t\t") ;
        
        if(current->scanLength)
        {
            printf("   \t\t\t\t\t%d\t",current->scanLength);
            for(j=0;j<current->scanLength;j++)
            {
                printf("%02X",current->scanData[j]);  
            }
            printf("\n");
        
            blePrintAdvPacketData(current->scanData,current->scanLength,"   \t\t\t\t\t\t\t") ;
        }
        
        lastPrintList[i]=current;
        i += 1;
        current = current->next;
    }
    printf("\n\n");
        
}

void CyBle_AppCallback( uint32 eventCode, void *eventParam )
{
    if(eventCode != CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT)
    {
        printf(bleGetEventString(eventCode));
        printf("\n");
    }
    switch( eventCode )
    {
        /* Generic events */

        case CYBLE_EVT_STACK_ON:
            /* CyBle_GappStartAdvertisement( CYBLE_ADVERTISING_FAST ); */
        break;

        case CYBLE_EVT_TIMEOUT:
        break;


        /* GAP events */

        case CYBLE_EVT_GAP_AUTH_REQ:
        break;

        case CYBLE_EVT_GAP_PASSKEY_ENTRY_REQUEST:
        break;

        case CYBLE_EVT_GAP_PASSKEY_DISPLAY_REQUEST:
        break;

        case CYBLE_EVT_GAP_AUTH_COMPLETE:
        break;

        case CYBLE_EVT_GAP_AUTH_FAILED:
        break;

        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
        break;

        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            /* CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST); */
        break;

        case CYBLE_EVT_GAP_ENCRYPT_CHANGE:
        break;

        case CYBLE_EVT_GAP_CONNECTION_UPDATE_COMPLETE:
        break;

        case CYBLE_EVT_GAP_KEYINFO_EXCHNGE_CMPLT:
        break;

        case CYBLE_EVT_GAP_NUMERIC_COMPARISON_REQUEST:
        break;

        case CYBLE_EVT_GAP_KEYPRESS_NOTIFICATION:
        break;

        case CYBLE_EVT_GAP_DATA_LENGTH_CHANGE:
            
        break;

        case CYBLE_EVT_GAP_ENHANCE_CONN_COMPLETE:
        break;

        case CYBLE_EVT_GAP_SMP_NEGOTIATED_AUTH_INFO:
        break;


        /* GAP Peripheral events */

        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
        break;


        /* GAP Central events */

        case CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT:
            addAdvPacket((CYBLE_GAPC_ADV_REPORT_T *)eventParam);
            
        break;

        case CYBLE_EVT_GAPC_SCAN_START_STOP:
        break;

        case CYBLE_EVT_GAPC_DIRECT_ADV_REPORT:
        break;


        /* GATT events */

        case CYBLE_EVT_GATT_CONNECT_IND:
        break;

        case CYBLE_EVT_GATT_DISCONNECT_IND:
        break;


        /* GATT Client events */

        case CYBLE_EVT_GATTC_ERROR_RSP:
        break;

        case CYBLE_EVT_GATTC_XCHNG_MTU_RSP:
        break;

        case CYBLE_EVT_GATTC_READ_BY_GROUP_TYPE_RSP:
        break;

        case CYBLE_EVT_GATTC_READ_BY_TYPE_RSP:
        break;

        case CYBLE_EVT_GATTC_FIND_INFO_RSP:
        break;

        case CYBLE_EVT_GATTC_FIND_BY_TYPE_VALUE_RSP:
        break;

        case CYBLE_EVT_GATTC_READ_RSP:
        break;

        case CYBLE_EVT_GATTC_READ_BLOB_RSP:
        break;

        case CYBLE_EVT_GATTC_WRITE_RSP:
        break;

        case CYBLE_EVT_GATTC_EXEC_WRITE_RSP:
        break;

        case CYBLE_EVT_GATTC_HANDLE_VALUE_NTF:
        break;

        case CYBLE_EVT_GATTC_HANDLE_VALUE_IND:
        break;

        case CYBLE_EVT_GATTC_INDICATION:
        break;

        case CYBLE_EVT_GATTC_SRVC_DISCOVERY_FAILED:
        break;

        case CYBLE_EVT_GATTC_INCL_DISCOVERY_FAILED:
        break;

        case CYBLE_EVT_GATTC_CHAR_DISCOVERY_FAILED:
        break;

        case CYBLE_EVT_GATTC_DESCR_DISCOVERY_FAILED:
        break;

        case CYBLE_EVT_GATTC_SRVC_DUPLICATION:
        break;

        case CYBLE_EVT_GATTC_CHAR_DUPLICATION:
        break;

        case CYBLE_EVT_GATTC_DESCR_DUPLICATION:
        break;

        case CYBLE_EVT_GATTC_SRVC_DISCOVERY_COMPLETE:
        break;

        case CYBLE_EVT_GATTC_INCL_DISCOVERY_COMPLETE:
        break;

        case CYBLE_EVT_GATTC_CHAR_DISCOVERY_COMPLETE:
        break;

        case CYBLE_EVT_GATTC_DISCOVERY_COMPLETE:
        break;


        /* GATT Server events */

        case CYBLE_EVT_GATTS_XCNHG_MTU_REQ:
        break;

        case CYBLE_EVT_GATTS_WRITE_REQ:
        break;

        case CYBLE_EVT_GATTS_WRITE_CMD_REQ:
        break;

        case CYBLE_EVT_GATTS_PREP_WRITE_REQ:
        break;

        case CYBLE_EVT_GATTS_EXEC_WRITE_REQ:
        break;

        case CYBLE_EVT_GATTS_HANDLE_VALUE_CNF:
        break;

        case CYBLE_EVT_GATTS_INDICATION_ENABLED:
        break;

        case CYBLE_EVT_GATTS_INDICATION_DISABLED:
        break;

        case CYBLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ:
        break;


        /* L2CAP events */

        case CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_REQ:
        break;

        case CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP:
        break;


        /* default catch-all case */

        default:
        break;
    }
}
int main()
{
    CyGlobalIntEnable;
    UART_Start();
    clearDisplay();
    CySysTickStart();
    CySysTickSetCallback(0,incSysTime);
    headDevice.next =0;
    printf(aBunchOfDashes);
    printf("                       IOT Expert Bluetooth Explorer\n");
    printf(aBunchOfDashes);
    
    CyBle_Start(CyBle_AppCallback);
    for(;;)
    {
        char c;
        
        c = UART_UartGetChar();
        switch(c)
        {
            case 'd':
                printDeviceTable();
            break;
            case 's':
                CyBle_GapcStartScan(CYBLE_SCANNING_FAST );
                printf("Started Scanning\n");
            break;
            case 'S':
                CyBle_GapcStopScan();
                printf("Stopped Scanning\n");
            break;
            case 'c':
                clearDisplay();
            break;
            case 'p':
                printf(bleGetStateString());
                printf("\n");
            break;
            case 'r':
                CySoftwareReset();
            break;
                
            case '?':
                printf("--------------------\n");
                printf("c\tClear Display\n");
                printf("d\tPrint Device Table\n");
                printf("p\tPrint State\n");
                printf("r\tReset device\n");
                printf("s\tStart Scanning\n");
                printf("S\tStop Scanning\n"); 
                printf("?\thelp\n");
            break;
        }
        
        CyBle_ProcessEvents();
        CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);  
    }
}

/* [] END OF FILE */
