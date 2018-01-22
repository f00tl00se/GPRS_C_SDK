#ifndef __DEMO_ONENET_H__
#define __DEMO_ONENET_H__

void Net_Clear(void);

bool Net_SendData(uint8_t *data, uint16_t len);

uint8_t *Net_GetIPD(uint16_t timeOut);

#endif // __DEMO_ONENET_H__
