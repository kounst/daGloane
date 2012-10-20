/*
 * uAC.c
 *
 *  Created on: Sep 01, 2011
 *      Author: Thomas Weinhold
 */


/* Includes ------------------------------------------------------------------*/
#include "uAC.h"
#include <stdarg.h>


#ifndef uAC_CmdLibLength
#include <stdlib.h>
#endif /* uAC_CmdLibLength */

#define _uAC_LineLengthWithoutPrompt (_uAC_LineLength - sizeof(_uAC_Prompt) - 1)

//! The Status vars.
struct {
	unsigned char PromtIsWritten:1;
	unsigned char ReadyToResolveLine:1;
	unsigned char ReadyToExecute:1;
	unsigned char EscapeSequence:2;
} _status;

//!The uAC input buffer.
struct {
	unsigned int read;
	unsigned int write;
	unsigned int minfree;
	char buffer[_uAC_InBufferSize];
} volatile _inbuff;

//!The uAC output buffer.
struct {
	unsigned int read;
	unsigned int write;
	unsigned int minfree;
	char buffer[_uAC_OutBufferSize];
} volatile _outbuff;

//!Stores user input.
struct {
	unsigned int pointer;
	char buffer[_uAC_LineLengthWithoutPrompt+1];
} _history[_uAC_HistorySize+1];

//!Stores the attached commands
#ifdef uAC_CmdLibLength
struct {
	char *name;
	void (*function)(int,char*[]);
} _cmdlib[uAC_CmdLibLength];
#else /* uAC_CmdLibLength */
struct _lib_struct{
	struct _lib_struct * next;
	char *name;
	void (*function)(int,char*[]);
} *_cmdlib_p;
#endif /* uAC_CmdLibLength */

//!Indicates which history point is selected
unsigned int _history_pointer=0;

//!the underlying printf implementation
void _printf(char*, va_list, char /* 0-Ram, 1-Flash */);

//!Put a char into the outbuffer
void _putchar ( char);

//!Put a string to the outbuffer
inline void _putstring (char *);

//!Put a uint to the outbuffer.
void _putuint (unsigned int);

//!Put a uint to the outbuffer (hexadecimal)
void _putuint_hex (unsigned int, unsigned char);

//!Put a single number to the outbuffer
inline void _putnumber (char number);

//!Write the newline string.
inline void _newline (void);

//!Clear the prompt line.
void _prompt_clear (void);

//!Write the prompt line.
void _prompt_write (void);

//!Process an incoming char.
int _process_char (void);

//!Read the command line and execute the command.
void _resolve_line (void);

//!Push the actual command line into the history.
void _push_history (void);

//!The help command.
void _print_help (void);

void uac_init (void) {
	unsigned int i=0;
	_inbuff.read=0;
	_inbuff.write=0;
	_inbuff.minfree=(unsigned int) -1;
	_outbuff.read=0;
	_outbuff.write=0;
	_outbuff.minfree=(unsigned int) -1;

	for (i=0;i<=_uAC_HistorySize;i++) _history[i].pointer=0;
	_history_pointer=0;

#ifdef uAC_CmdLibLength
	for (i=0; i < uAC_CmdLibLength; i++)
	{
		_cmdlib[i].name=0;
	}
#else /* uAC_CmdLibLength */
	_cmdlib_p=0;
#endif /* uAC_CmdLibLength */

	_newline();
	_prompt_write();

	_status.ReadyToResolveLine=0;
	_status.ReadyToExecute=0;
	_status.EscapeSequence=0;
}

void uac_task (void) {
	if (_status.ReadyToResolveLine){
		_resolve_line(); //!execute command
	}
	else if (_inbuff.read != _inbuff.write) {
		_process_char(); //!read input buffer
	}
}

int uac_rx (char Rx) {
	unsigned int NextWrite = ( _inbuff.write + 1 ) & (_uAC_InBufferSize-1);
	unsigned int MinFree=0;
	int Ret=0;

	if(NextWrite != _inbuff.read) {
		_inbuff.write = NextWrite;
		_inbuff.buffer[NextWrite] = Rx;
		MinFree=(_inbuff.read - _inbuff.write - 1) & (_uAC_InBufferSize-1);
		if (MinFree < _inbuff.minfree) _inbuff.minfree=MinFree;
		Ret=1;
	}

	return Ret;
}

int uac_txavailable (void) {
	return ( (_outbuff.read == _outbuff.write) ? 0:1);
}

char uac_tx (void) {
	if (uac_txavailable()) {
		return _outbuff.buffer[_outbuff.read = (_outbuff.read + 1) & (_uAC_OutBufferSize-1)];
	}

	return 0;
}

int uac_attach(char *name, void (*func)(int,char*[])) {
#ifdef uAC_CmdLibLength
	unsigned int i=0;
	unsigned char cmd_stored=0;
	for (i=0;i<uAC_CmdLibLength;i++) {
		if (_cmdlib[i].name==0) {
			_cmdlib[i].name=name;
			_cmdlib[i].function=func;
			cmd_stored=1;
			break;
		}
	}
	if (!cmd_stored) return 0;
#else /* uAC_CmdLibLength */
	struct _lib_struct *help_p = _cmdlib_p;
	struct _lib_struct *new_p = 0;
	//check if name still exists
	while (help_p!=0) {
		if (uac_strcmp(help_p->name,name)) return 0;
		help_p = help_p->next;
	}

	//get some new space
	new_p = malloc(sizeof(struct _lib_struct));
	if (!new_p) return 0;
	new_p->next=0;
	new_p->name = name;
	new_p->function = func;

	//attach to the list
	if (!_cmdlib_p) {
		_cmdlib_p = new_p;
	}
	else {
		help_p = _cmdlib_p;
		while (help_p->next) help_p=help_p->next;
		help_p->next=new_p;
	}
#endif /* uAC_CmdLibLength */

	return 1;
}

void uac_printf(char* Format, ...)
{
	va_list ListPointer;
	va_start(ListPointer, Format);
	_printf(Format, ListPointer, 0);
	va_end(ListPointer);
}

void uac_printf_P(char* Format, ...)
{
	va_list ListPointer;
	va_start(ListPointer, Format);
	_printf(Format, ListPointer, 1);
	va_end(ListPointer);
}

int uac_strcmp (char *a, char *b)
{
	unsigned int i;
	int Ret=1;

	for (i=0;a[i]!='\0' && b[i]!='\0';i++) {
#ifdef uAC_strcmp_casesense
		if (a[i]!=b[i]) Ret=0;
#else
		if ((0x60 | a[i])!=(0x60 | b[i])) Ret=0;
#endif
	}
	if (a[i]!=b[i]) Ret=0;

	return Ret;
}

void _printf(char* Format, va_list ListPointer, char AdressType) //0-Ram, 1-Flash
{
	//!reminder vars / storage
	unsigned char RestorePrompt = _status.PromtIsWritten;
	char ActualChar, FormatLength=0;
	//!vars for dynamic parameters
	char *VaString;
	char VaChar;
	int VaInt;
#ifdef uAC_Print_f_Type
	float VaFloat;
	unsigned int ui2;
#endif /* uAC_Print_f_Type */
	unsigned int VaUInt;
	//!standard loop var
	unsigned int ui;

	//!clear prompt
	if (RestorePrompt) _prompt_clear();

	ui=0;
	//ActualChar = (AdressType)? pgm_read_byte(Format) : Format[0];
	ActualChar = Format[0];
	while (ActualChar!='\0')
	{
		if (ActualChar=='%')
		{
			//!get the first char after %
			ui++;
			//ActualChar = (AdressType)? pgm_read_byte(Format+ui) : Format[ui];
			ActualChar = Format[ui];
			if (ActualChar=='\0')
			{
				_putchar('%');
				break;
			}

			//!switch for getting FormatLength
			switch (ActualChar)
			{
			case '9': FormatLength=9; break;
			case '8': FormatLength=8; break;
			case '7': FormatLength=7; break;
			case '6': FormatLength=6; break;
			case '5': FormatLength=5; break;
			case '4': FormatLength=4; break;
			case '3': FormatLength=3; break;
			case '2': FormatLength=2; break;
			case '1': FormatLength=1; break;
			case '0': FormatLength=0; break;
			default:
				FormatLength=10;
				ui--;
			}

			//!get the next char
			ui++;
			//ActualChar = (AdressType)? pgm_read_byte(Format+ui) : Format[ui];
			ActualChar = Format[ui];
			if (ActualChar=='\0')
			{
				_putchar('%');
				break;
			}

			//!switch for the format type
			switch (ActualChar)
			{
			case 's':
				VaString = va_arg(ListPointer, char *);
				_putstring(VaString);
				break;
			case 'c':
				VaChar = (char) va_arg(ListPointer, int);
				_putchar(VaChar);
				break;
			case 'i':
				VaInt = va_arg(ListPointer, int);
				if (VaInt < 0) {
					_putchar('-');
					VaInt*=-1;
				}
				_putuint((unsigned int) VaInt);
				break;
			case 'u':
				VaUInt = va_arg(ListPointer, unsigned int);
				_putuint(VaUInt);
				break;
#ifdef uAC_Print_x_Type
			case 'x':
				VaUInt = va_arg(ListPointer, unsigned int);
				_putuint_hex(VaUInt,0);
				break;
			case 'X':
				VaUInt = va_arg(ListPointer, unsigned int);
				_putuint_hex(VaUInt,1);
				break;
#endif /* uAC_Print_x_Type */
#ifdef uAC_Print_f_Type
			case 'f':
				VaFloat = va_arg(ListPointer, double);
				VaInt = VaFloat;
				//if (VaInt < 0)	//this should probably fix the problem with numbers < 0 and > -1
				if (VaFloat < 0)
				{
					_putchar('-');
					VaInt *= -1;
					VaFloat *= -1;
				}
				_putuint(VaInt);
				if (FormatLength) _putchar(uAC_DecFracSign);

				for (ui2=0; VaFloat!=0 && ui2<FormatLength; ui2++)
				{
					VaFloat -= VaInt;
					VaFloat *= 10;
					VaInt = VaFloat;
					_putnumber((char) VaInt);
				}
				break;
#endif /* uAC_Print_f_Type */
			default:
				_putchar('%');
				_putchar(ActualChar);
			}
		}
		else if (ActualChar=='\n')
		{
			_newline();
		}
		else
		{
			_putchar(ActualChar);
		}

		ui++;
		//ActualChar = (AdressType)? pgm_read_byte(Format+ui) : Format[ui];
		ActualChar = Format[ui];
	}

	//!restore prompt
	if (RestorePrompt) _prompt_write();
}

void _putchar ( char C) {
	unsigned int NextWrite = ( _outbuff.write + 1 ) & (_uAC_OutBufferSize-1);
	unsigned int MinFree=0;

	if(NextWrite != _outbuff.read) {
		_outbuff.write = NextWrite;
		_outbuff.buffer[NextWrite] = C;
		MinFree=(_outbuff.read - _outbuff.write - 1) & (_uAC_OutBufferSize-1);
		if (MinFree < _outbuff.minfree) _outbuff.minfree=MinFree;
	}
}

inline void _putstring (char *s) {
	for (;*s!='\0';) _putchar(*(s++));
}

void _putuint (unsigned int ux) {
	if (ux==0) {
		_putchar('0');
		return;
	}
	char c_arr[11];
	int i=0;
	for (i=0; ux; i++) {
		c_arr[i]=(char) (ux%10);
		ux=(ux-((unsigned int)c_arr[i]))/10;
	}
	for (i--;i>=0;i--) _putnumber(c_arr[i]);
}

#ifdef uAC_Print_x_Type
void _putuint_hex (unsigned int ux, unsigned char Big) {
	if (ux==0) {
		_putchar('0');
		return;
	}
	char c_arr[11];
	int i=0;
	for (i=0; ux; i++) {
		c_arr[i]  = (ux & 0x0F);
		c_arr[i] += (c_arr[i]<=9)? '0' : ( (Big)? 'A'-10 : 'a'-10 );
		ux = ux>>4;
	}
	for (i--;i>=0;i--) _putchar(c_arr[i]);
}
#endif /* uAC_Print_x_Type */

inline void _putnumber (char number)
{
	_putchar(number+'0');
}

inline void _newline (void) {
	_putstring(_uAC_NewLineString);
}

void _prompt_clear (void) {
	int i;
	for (i=0;_uAC_Prompt[i]!='\0';i++) _putstring("\b \b");
	for (i=0; i < _history[0].pointer; i++) _putstring("\b \b");
	_status.PromtIsWritten=0;
}

void _prompt_write (void) {
	unsigned int i=0;
	_putstring(_uAC_Prompt);
	for (i=0; i < _history[0].pointer; i++) _putchar(_history[0].buffer[i]);
	_status.PromtIsWritten=1;
}

void _push_history (void) {
	if (!_uAC_HistorySize) return;

	unsigned int i=0,i2=0;
	unsigned char CmdIsEqual=1;

	//!Check if actual command line equals the last one in the history.
	if (_history[0].pointer != _history[1].pointer) {
		CmdIsEqual=0;
	}
	else {
		for (i=0;i<_history[0].pointer;i++) {
			if (_history[0].buffer[i]!=_history[1].buffer[i]) {
				CmdIsEqual=0;
				break;
			}
		}
	}

	//Push the actual line into the History
	if (!CmdIsEqual) {
		for (i=_uAC_HistorySize;i!=0;i--) {
			for (i2=0;i2<_history[i-1].pointer;i2++) {
				_history[i].buffer[i2]=_history[i-1].buffer[i2];
			}
			_history[i].pointer=_history[i-1].pointer;
		}
	}
}

void _print_help (void) {
#ifdef uAC_CmdLibLength
	unsigned int i;
	for (i=0;i<uAC_CmdLibLength;i++) {
		if(_cmdlib[i].name==0) break;
		uac_printf("%s\n",_cmdlib[i].name);
	}
	uac_printf("\n{free command attach slots: %u}\n",uAC_CmdLibLength-i);
#else /* uAC_CmdLibLength */
	struct _lib_struct *help_p = _cmdlib_p;
	unsigned int cmd_count=0;
	while (help_p) {
		uac_printf("%s\n",help_p->name);
		cmd_count++;
		help_p=help_p->next;
	}
	uac_printf("\n{attached commands: %u}\n",cmd_count);
#endif /* uAC_CmdLibLength */
	uac_printf("{free buffer: in %u / out %u}\n",_inbuff.minfree,_outbuff.minfree);
}

int _process_char(void)
{
	char pc=0; //!process char
	unsigned int i; //!Loop int

	//! Get a char from the input buffer.
	if (_inbuff.read != _inbuff.write) {
		pc = _inbuff.buffer[_inbuff.read = (_inbuff.read + 1) & (_uAC_InBufferSize-1)];
	}
	else {
		return 0;
	}

	//! Process escape sequences.
	if (_status.EscapeSequence==1) {
		if (pc=='[') {
			_status.EscapeSequence=2;
		}
		else {
			if (_history[0].pointer!=_uAC_LineLengthWithoutPrompt) {
				_history[0].buffer[_history[0].pointer++]=pc;
				_putchar(pc);
			}
			_status.EscapeSequence=0;
		}
		return 0;
	}
	else if (_status.EscapeSequence==2) {
		if (pc=='A') {
			_status.EscapeSequence=0;
			if (!_uAC_HistorySize) return 0;
			if (_history_pointer<_uAC_HistorySize) {
				_prompt_clear();
				_history_pointer++;
				for (i=0;i<_history[_history_pointer].pointer;i++)
					_history[0].buffer[i]=_history[_history_pointer].buffer[i];
				_history[0].pointer=_history[_history_pointer].pointer;
				_prompt_write();
			}
		}
		else if (pc=='B') {
			_status.EscapeSequence=0;
			if (!_uAC_HistorySize) return 0;
			if (_history_pointer>1) {
				_prompt_clear();
				_history_pointer--;
				for (i=0;i<_history[_history_pointer].pointer;i++)
					_history[0].buffer[i]=_history[_history_pointer].buffer[i];
				_history[0].pointer=_history[_history_pointer].pointer;
				_prompt_write();
			}
			else if (_history_pointer==1) {
				_prompt_clear();
				_history_pointer=0;
				_history[0].pointer=0;
				_prompt_write();
			}
		}
		else {
			_status.EscapeSequence=0;
		}
		return 0;
	}

	//! Process other chars.
	switch (pc) {
	case '\t':
		break;
	case 27:
		_status.EscapeSequence=1;
		break;
	case '\r':
	case '\n':
		_newline();
		_status.PromtIsWritten=0;
		_push_history();
		_history_pointer=0;
		_status.ReadyToResolveLine=1;
		break;
	case '\b':
		if (_history[0].pointer!=0) {
			_history[0].pointer--;
			_putstring("\b \b");
		}
		break;
	default:
		if (_history[0].pointer!=_uAC_LineLengthWithoutPrompt) {
			_history[0].buffer[_history[0].pointer++]=pc;
			_putchar(pc);
		}
	}

	return (1);
}

void _resolve_line (void) {
	//!terminate command line
	_history[0].buffer[_history[0].pointer]='\0';

	//!Reset Prompt
	unsigned int i=0,i2=0,argc=0,arg_begins=0;

	//!Count arguments
	for (i=0;i < _history[0].pointer;i++) {
		if (_history[0].buffer[i]==' ' || _history[0].buffer[i]=='\t') {
			arg_begins=0;
		}
		else {
			if (!arg_begins) {
				arg_begins=1;
				argc++;
			}
		}
	}

	//Exit if there are no arguments
	if (!argc) {
		_prompt_write();
		_status.ReadyToResolveLine=0;
		return;
	}

	//!The arguments vector.
	char *argv[argc];

	//!Get pointers
	i2=0;
	arg_begins=0;
	for (i=0;i < _history[0].pointer;i++) {
		if (_history[0].buffer[i]==' ' || _history[0].buffer[i]=='\t') {
			_history[0].buffer[i]='\0';
			arg_begins=0;
		}
		else {
			if (!arg_begins) {
				arg_begins=1;
				argv[i2++]=&_history[0].buffer[i];
			}
		}
	}

	//!search the cmd in the cmdlib
	if (uac_strcmp("help",argv[0])) {
		_print_help();
	}
	else {
#ifdef uAC_CmdLibLength
		for (i=0;i<uAC_CmdLibLength;i++) {
			if (uac_strcmp(argv[0],_cmdlib[i].name)) break;
		}
		if (i==uAC_CmdLibLength) {
			uac_printf("command not found!\n");
		}
		else {
			_cmdlib[i].function(argc-1,&argv[1]);
		}
#else /* uAC_CmdLibLength */
		struct _lib_struct *help_p = _cmdlib_p;
		unsigned char cmd_found=0;
		while (help_p) {
			if (uac_strcmp(help_p->name,argv[0])) {
				cmd_found=1;
				help_p->function(argc-1,&argv[1]);
			}
			help_p=help_p->next;
		}
		if (!cmd_found) uac_printf("command not found!\n");
#endif /* uAC_CmdLibLength */
	}

	//!replace '\0' with ' '
	for (i=0;i < _history[0].pointer;i++) {
		if (_history[0].buffer[i]=='\0') _history[0].buffer[i]=' ';
	}

	_newline();
	_history[0].pointer=0;
	_prompt_write();
	_status.ReadyToResolveLine=0;
}
