#ifndef BLEUTIL_H
#define BLEUTIL_H
#include <project.h>
    
char *bleFormatBDAddr(char *buff,uint8 *bdAddr);
const char *bleGetEventString(uint32_t event);
const char *bleGetStateString();
char *bleFormat128bitUUID(char *buff,uint8_t *bytes);
char *bleFormat32bitUUID(char *buff,uint8_t *bytes);
char *bleFormat16bitUUID(char *buff,uint8_t *bytes);
#endif