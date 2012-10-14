/**
 * @file uAC.h
 * @author Thomas Weinhold
 * @date 12.06.2011
 * @version 0.5
 */

#ifndef UAC_H_
#define UAC_H_


//!Activate uac_print %<x>f support for float and double
#define uAC_Print_f_Type

//!Activate uac_print %x support
#define uAC_Print_x_Type

//!Makes uac_strcmp case sensitive
//#define uAC_strcmp_casesense

//! A string which defines the chars to signal a new line.
/**
 * If in a string "\n" is present, it will be replaced by this string.
 * The string can be, for example "\r\n" or something.
 */
#define _uAC_NewLineString "\r\n"

//! The prompt-string.
/**
 * A whitespace is not automatically added.
 * If desired, the string must conain it.
 */
#define _uAC_Prompt "daGloane> "

//! The size of the input char buffer.
/**
 * Must be a 2^n value. (2 4 8 16 32 ...)
 * Usual this can be a low value (2 - 16).
 * A normal user is not able to type that fast.
 * Maximum is 65536
 */
#define _uAC_InBufferSize 8

//! The size of the output char buffer.
/**
 * Must be a 2^n value. (2 4 8 16 32 ...)
 * The buffer must be large enough to store
 * all the chars which are generated before they can be send.
 * If the generated output is not complete
 * (chars are missing) you have to increase this value.
 * Usual values are 128 ore more.
 * Maximum is 65536
 */
#define _uAC_OutBufferSize 512

//!The maximum length of a input line.
/**
 * This length defines, how many chars a user can input to a single line.
 * Be aware, that the prompt is also included in this length,
 * so this must not be smaller then the length of the _uAC_Prompt string.
 *
 * @see _uAC_Prompt
 */
#define _uAC_LineLength 60

//!Amount of the input history.
/**
 * This defines, how many old commands are stored to use them again.
 * To reduce RAM usage, set this to low values!
 */
#define _uAC_HistorySize 2

//!Amount of attach-able commands.
/**
 * If this is not defined,
 * a dynamic list is used.
 */
//#define uAC_CmdLibLength 10

//!decimal fraction divider sign
#define uAC_DecFracSign ','

//!This init function must be called at first!
void uac_init (void);

//! The uAC processing function.
/**
 * This function must be called repeatedly.
 * It processes incoming and outgoing chars
 * and executes user commands.
 */
void uac_task (void);

//! Input a char
/**
 * Chars are not received automatically by uAC.
 * You have to write a external receiver (eg. USART)
 * to feed uAC with this function.
 * @param The received char.
 * @return 1 if the char was captured, 0 if not
 */
int uac_rx (char);

//! Check if there are chars to send
/**
 * Chars are not transmitted by uAC.
 * They must be collected and send by your own.
 * @return 1 if there are chars, 0 if not.
 * @see uac_tx()
 */
int uac_txavailable (void);

//!Get a char to send
/**
 * Chars are not transmitted by uAC.
 * They must be collected and send by your own.
 * This function returns a char you can send eg. by USART.
 * Be aware to use uAC_TxAvailable() to check if chars are present.
 * If there is no char present, this function returns 0
 * @return 1 for a valid char, 0 for a non-valid char
 * @see uAC_TxAvailable()
 */
char uac_tx (void);

//!A simplified printf implementation
/**
 * Supported Formats:
 * 	-%s (char*)
 * 	-%c (char)
 * 	-%i (int)
 * 	-%u (unsigned int)
 *  -%<x>f (float / double)
 *  -%x or %X (unsigned int)
 *
 * A \n char is automatically replaced with the specified newline string.
 * To support %<x>f the uAC_Print_f_Type define has to be set.
 * The <x> integer is the precision for float/double types (0..9).
 * @see _uAC_NewLineString
 * @param The Formatstring
 * @param Parameterlist
 */
void uac_printf(char *, ...);

//!Pintf with format string from flash.
/**
 * Works similar to the uac_printf() function.
 * The only difference is that the format string has to
 * lay in the flash memory.
 * @see uac_printf
 * @param The Formatstring
 * @param Parameterlist
 */
void uac_printf_P(char *, ...);

//!Compare two strings
/**
 * Be aware, that both strings must be terminated with '\0'
 * @param String 1
 * @param String 2
 * @return 1 if they are equal, 0 if not
 */
int uac_strcmp(char*,char*);

//!Attach functions to the console
/**
 * If the user types a command, a function has to be called.
 * With uAC_attach, you can add function to the console.
 * A function must be of a kind 'void foo_cmd(int argc,char *argv)'.
 * To get this example function attached you have o do something
 * like 'uAC_attach("foo",foo_cmd)'.
 *
 * @param A string which defines how to call the command.
 * @param A pointer to the function.
 * @return If the function was attached,1 is returned, else 0.
 */
int uac_attach(char*, void (*)(int,char*[]));



#endif /* UAC_H_ */
