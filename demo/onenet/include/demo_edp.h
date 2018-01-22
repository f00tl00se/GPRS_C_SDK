#ifndef __DEMO_EDP_H__
#define __DEMO_EDP_H__

uint8_t OneNet_EDP_DevLink(void);
void OneNet_EDP_SendData(void);
void OneNet_EDP_RevPro(uint8_t *cmd);
uint8_t OneNet_EDP_SendData_Heart(void);

#endif // __DEMO_EDP_H__