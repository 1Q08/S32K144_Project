#ifndef UART_H_
#define UART_H_

extern uint8_t buffer[200];
extern uint8_t rxdata[200];
extern uint8_t triger;

void u1_printf(char* fmt,...);
void LPUART1_RX_ISR (void *driverState, uart_event_t event, void *userData);

#endif
