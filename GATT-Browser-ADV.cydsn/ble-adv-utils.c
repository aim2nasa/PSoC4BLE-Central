#include <project.h>
#include "ble-adv-utils.h"
#include "bleutil.h"
#include <stdio.h>

char tempBuff[128];
// print each field on one line
// len f# name data
void blePrintAdvPacketData(uint8_t *data,int len,char *pad) 
{
    int pointer=0;
    
    uint8_t *adInfoPacket;
    
    while(pointer<len)
    {
        
        
        #ifdef DEBUG_ADINFO
        int fl;
        int i;
   
        printf(pad);
        // length
        adInfoPacket = &data[pointer];
        fl = data[pointer];
        printf("%02x ",fl);
        pointer = pointer + 1;
        
        //number of field
        printf("%02x ",data[pointer]);
        pointer = pointer + 1;
        
        for(i=0;i<fl -1 ;i++)
        {
            printf("%02X",data[pointer]);
            pointer = pointer + 1;
        }
        printf("\n");
        #else
        adInfoPacket = &data[pointer];
        pointer = pointer + data[pointer] + 1;     
        
        #endif
        
        printf(pad);
        printf(bleDecodeAdInfo(tempBuff,adInfoPacket));
        
        printf("\n");        
    }
    
}


struct advDecode_t {
    uint8_t code;
    char *name;
    char * (*fcn)(char *buff,uint8_t *bytes); 
};

char *bleAdInfoDecodeName(char *buff,uint8_t *bytes)
{
    uint8_t len = bytes[0];
    memcpy(buff,&bytes[2],len - 1);
    buff[len-1] = 0; // put a 0 to end the string
    return buff;
}

char *bleAdInfoDecodeUnknown(char *buff, uint8_t *bytes)
{
    sprintf(buff,"Len:%02X Type:%02X",bytes[0],bytes[1]);
    return buff;
}


char *bleAdInfoDecodeFlags(char *buff, uint8_t *bytes)
{
    int count = 0;
    
    count=sprintf(buff,"%02X ",bytes[2]);
    
    if(bytes[2] & 0x01)
        count += sprintf(&buff[count],"%s","LE Ltd Discoverable ");
    
    if(bytes[2] & 0x02)
        count += sprintf(&buff[count],"%s","LE General Discoverable ");
        
    if(bytes[2] & 0x04)
        count += sprintf(&buff[count],"%s","BR/EDR Not Supported ");
    
    if(bytes[2] & 0x08)
        count += sprintf(&buff[count],"%s","BR/EDR Controller ");

    if(bytes[2] & 0x10)
        count += sprintf(&buff[count],"%s","BR/EDR Host ");
        
   
    return buff;
}

char *bleAdInfoDumpBytes(char *buff, uint8_t *bytes)
{
    int i;
    for(i=0;i<bytes[0]-1;i++)
    {
        sprintf(&buff[i*2],"%02X",bytes[2+i]);
    }
    
    return buff;
}

char *bleAdInfoDecodeMfgData(char *buff, uint8_t *bytes)
{
    return bleAdInfoDumpBytes(buff,bytes);
}

char *bleAdInfoDecode16bitServiceUUID(char *buff, uint8_t *bytes)
{
        return bleFormat16bitUUID(buff,&bytes[2]);
}

char *bleAdInfoDecode32bitServiceUUID(char *buff, uint8_t *bytes)
{
        return bleFormat128bitUUID(buff,&bytes[2]);
}


char *bleAdInfoDecode128bitServiceUUID(char *buff, uint8_t *bytes)
{
        return bleFormat128bitUUID(buff,&bytes[2]);
}
char *bleAdInfoDecodePublicAddress(char *buff, uint8_t *bytes)
{
        return bleAdInfoDumpBytes(buff,bytes);
}

// https://www.bluetooth.com/specifications/assigned-numbers/generic-access-profile
struct advDecode_t advDecodeArray[] = {
    {0x01, "Flags",bleAdInfoDecodeFlags},
    {0x02, "16-bit Service UUID",bleAdInfoDecode16bitServiceUUID},
    {0x03, "16-bit Service UUID",bleAdInfoDecode16bitServiceUUID},
    {0x04, "32-bit Service UUID",bleAdInfoDecode32bitServiceUUID},
    {0x05, "32-bit Service UUID",bleAdInfoDecode32bitServiceUUID},
    {0x06, "128-bit Service UUIDs", bleAdInfoDecode128bitServiceUUID},
    {0x07, "128-bit Service UUIDs", bleAdInfoDecode128bitServiceUUID},
    {0x08, "Short Name", bleAdInfoDecodeName},
    {0x09, "Complete Name", bleAdInfoDecodeName},
    {0x0A, "Tx Power Level", bleAdInfoDumpBytes},
    {0x0D, "Device Class", bleAdInfoDumpBytes},
    {0x0D, "Pairing Hash C", bleAdInfoDumpBytes},
    {0x0E, "Pairing Hash C-192", bleAdInfoDumpBytes},
    {0x0F, "Pairing Randomizer R", bleAdInfoDumpBytes},
    {0x10, "Device ID", bleAdInfoDumpBytes},
    {0x11, "Security Manger Out of Band Flags", bleAdInfoDumpBytes},
    {0x12, "Slave Connection Interval Range", bleAdInfoDumpBytes},
    {0x14, "16-bit Service Solicitation UUIDs", bleAdInfoDecode16bitServiceUUID},
    {0x15, "128-bit Service Solicitation UUIDs", bleAdInfoDecode128bitServiceUUID},
    {0x16, "Service Data", bleAdInfoDumpBytes},
    {0x17, "Public Target Address", bleAdInfoDumpBytes},
    {0x18, "Random Target Address", bleAdInfoDumpBytes},
    {0x18, "Appearance", bleAdInfoDumpBytes},
    {0x1A, "Advertising Interval", bleAdInfoDumpBytes},
    {0x1B, "LE Bluetooth Device Address", bleAdInfoDumpBytes},
    {0x1C, "LE Role", bleAdInfoDumpBytes},
    {0x1D, "Simple Pairing Hash C-256", bleAdInfoDumpBytes},
    {0x1E, "Simple Pairing Randomizer R-256", bleAdInfoDumpBytes},
    {0x1F, "32-bit Service Solitication UUIDs",bleAdInfoDecode32bitServiceUUID},
    {0x20, "32-bit Service Data UUID",bleAdInfoDecode32bitServiceUUID},
    {0x21, "128-bit Service Data UUID",bleAdInfoDecode128bitServiceUUID},
    {0x22, "LE Secure Connection Confirmation Value",bleAdInfoDumpBytes},
    {0x23, "LE Connection Random Value",bleAdInfoDumpBytes},
    {0x24, "URI",bleAdInfoDumpBytes},
    {0x25, "Indoor Positioning",bleAdInfoDumpBytes},
    {0x26, "Transport Discovery Data",bleAdInfoDumpBytes},
    {0x27, "LE Supported Features",bleAdInfoDumpBytes},
    {0x28, "Channel Map Update Indication",bleAdInfoDumpBytes},
    {0x3D, "3D Information Data",bleAdInfoDumpBytes},
    {0xFF, "MFG Data", bleAdInfoDecodeMfgData}
};

char *bleDecodeAdInfo(char *buff, uint8_t *bytes)
{
    int numElements = sizeof(advDecodeArray)/sizeof(struct advDecode_t);
    int i;

    for(i = 0; i<numElements; i++)
    {
        if(bytes[1] == advDecodeArray[i].code)
        {
            int count=sprintf(buff,"%s:",advDecodeArray[i].name);  // Use the # of bytes to setup string cat
            buff[count] = ' ';                                    // turn the 0 into a space
            (*advDecodeArray[i].fcn)(&buff[count+1],bytes);       // ARH this is nuts... just a cheap concatenation
            return(buff);
        }
    }
    sprintf(buff,"Unknown");
    return(buff);
}

