#ifndef _INCLUDE_TRIGGER_FLAGS_H_
#define _INCLUDE_TRIGGER_FLAGS_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "usart.h"
#include "keyboard.h"
#include "rtc.h"

typedef union
{
	uint8_t		uiByte[2];
	uint16_t	uiKeyCode;
}KEY_VALUE;

typedef struct
{
	KEY_VALUE	unKeyValue;
	bool		bIsTriggered;
	bool		bHalfRev;
}USART_INPUT;


void USARTReceiveProc(USART_INT_REASON eReason, uint8_t uiReceiveData);
bool UsartIsReceived(void);
uint16_t GetReceivedCode(void);
void UsartTriggerReset(void);

void TimerInterruptProc(void);
bool BaseTimerIsTrigger(void);
void BaseTimerTriggerReset(void);

void RTCInterruptProc(uint32_t uiTimeStamp);
bool RTCTimerIsTrigger(void);
void RTCTimerTriggerReset(void);

#endif

