/*
 * at_com_fsm.h
 *
 *  Created on: Mar 17, 2013
 *      Author: konstantin
 */

#ifndef AT_COM_FSM_H_
#define AT_COM_FSM_H_


#define BT_ADDR 0015,E9,006DD9

enum AT_FSM
{
	start,
	sendINIT,
	waitINITresp,
	INITIALIZED,
	sendPAIR,
	waitPAIRresp,
	PAIRED,
	sendLINK,
	waitLINKresp,
	CONNECTED,
	ERROR_,
	waitUSERINPUT,
	sendRESET,
	waitRESETresp
};

#endif /* AT_COM_FSM_H_ */
