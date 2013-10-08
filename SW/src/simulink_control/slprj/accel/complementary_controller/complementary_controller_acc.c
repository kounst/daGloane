#include "__cf_complementary_controller.h"
#include <math.h>
#include "complementary_controller_acc.h"
#include "complementary_controller_acc_private.h"
#include <stdio.h>
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
static void mdlOutputs ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER ( tid
) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER ( tid
) ; } static void mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S
, 0 , 1309120035U ) ; ssSetChecksumVal ( S , 1 , 767202357U ) ;
ssSetChecksumVal ( S , 2 , 4223848593U ) ; ssSetChecksumVal ( S , 3 ,
100232082U ) ; { mxArray * slVerStructMat = NULL ; mxArray * slStrMat =
mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status =
mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if ( status
== 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 , "Version" ) ;
if ( slVerMat == NULL ) { status = 1 ; } else { status = mxGetString (
slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "8.1" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; } static void mdlInitializeSampleTimes (
SimStruct * S ) { } static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
