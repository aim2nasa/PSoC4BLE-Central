#ifndef BLE_ADV_UTILS_H
#define BLE_ADV_UTILS_H
#include <project.h>
    
void blePrintAdvPacketData(uint8_t *data,int len,char *pad) ;
char *bleDecodeAdInfo(char *buff, uint8_t *bytes);
    
#endif