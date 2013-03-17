/*
 * at_com_fsm.c
 *
 *  Created on: Mar 17, 2013
 *      Author: konstantin
 */

#include "stm32f10x.h"
#include "at_com_fsm.h"
#include "UART.h"
#include "GPIO.h"

enum AT_FSM at_fsm_state = start;
extern enum _at_resp AT_resp;


void AT_FMS_fct(void)
{
	switch(at_fsm_state)
	{
	case start:
		at_fsm_state = sendINIT;
		break;

	case sendINIT:
		AT_resp = none;
		BT_send_AT_command("AT+init");
		at_fsm_state = waitINITresp;
		break;

	case waitINITresp:
		switch(AT_resp)
		{
		case none:		at_fsm_state = waitINITresp;	break;
		case OK: 		at_fsm_state = INITIALIZED; 	break;
		case ERROR_17: 	at_fsm_state = INITIALIZED; 	break;
		default:		at_fsm_state = ERROR_;			break;
		}
		break;

	case INITIALIZED:
		at_fsm_state = sendPAIR;
		break;

	case sendPAIR:
		AT_resp = none;
		BT_send_AT_command("AT+pair=BT_ADDR,5");
		at_fsm_state = waitPAIRresp;
		break;

	case waitPAIRresp:
		switch(AT_resp)
		{
		case none:		at_fsm_state = waitPAIRresp;	break;
		case OK: 		at_fsm_state = PAIRED; 			break;
		default:		at_fsm_state = ERROR_;			break;
		}
		break;

	case PAIRED:
		at_fsm_state = sendLINK;
		break;

	case sendLINK:
		AT_resp = none;
		BT_send_AT_command("AT+link=BT_ADDR");
		at_fsm_state = waitLINKresp;
		break;

	case waitLINKresp:
		switch(AT_resp)
		{
		case none:		at_fsm_state = waitLINKresp;	break;
		case OK: 		at_fsm_state = CONNECTED;		break;
		default:		at_fsm_state = ERROR_;			break;
		}
		break;

	case CONNECTED:
		switch(AT_resp)
		{
		case none:	at_fsm_state = CONNECTED;
					LEDOn(LED2);
					break;
		default:	at_fsm_state = ERROR_;
					LEDOff(LED2);
					break;
		}
		break;

	case ERROR_:
		LEDOn(LED1);
		at_fsm_state = waitUSERINPUT;
		break;

	case waitUSERINPUT:
		//if(button == 1)
		at_fsm_state = sendRESET;
		break;

	case sendRESET:
		LEDOff(LED1);
		AT_resp = none;
		BT_send_AT_command("AT+RESET");
		at_fsm_state = waitRESETresp;
		break;

	case waitRESETresp:
		switch(AT_resp)
		{
		case none:		at_fsm_state = waitRESETresp; 	break;
		case OK: 		at_fsm_state = sendINIT; 		break;
		default:		at_fsm_state = ERROR_;			break;
		}
		break;
	}
}
