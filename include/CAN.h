// can.h
#include <driver/twai.h>
#ifndef CAN_H
#define CAN_H

void setupTWAI();
void processCANMessage(twai_message_t *message);
void canTaskFunction(void *parameter);

#endif

