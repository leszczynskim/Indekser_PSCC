/* CustomDrillCyclesAPI.h
 *
 * 21 april 2011 : Mike O
 *
 */

#ifndef _API_CDC_H_
#define _API_CDC_H_

#ifdef INSIDE_VIRTUAL
	#define GC_CDC_API extern "C" __declspec( dllexport )
#else
	#define GC_CDC_API extern "C" __declspec( dllimport )
#endif

// custom process and operation data streams

GC_CDC_API bool gc_cdc_IsCustomDrillCycleMacroNameValid(char *szMacroName);

GC_CDC_API int gc_cdc_GetProcessNumCustomDataStreams(int iProcess);
GC_CDC_API int gc_cdc_GetProcessCustomDataStreamNames(int iProcess, char *szNames, int *iLengths, int iMax);

GC_CDC_API int gc_cdc_GetOpNumCustomDataStreams(int iOp);
GC_CDC_API int gc_cdc_GetOpCustomDataStreamNames(int iOp, char *szNames, int *iLengths, int iMax);

GC_CDC_API bool gc_cdc_IsCustomDrillCycleStreamName(const char *szStreamName);

GC_CDC_API int gc_cdc_GetCustomDrillCycleStreamName(const char *szMacroName, char *szStreamName);
GC_CDC_API int gc_cdc_GetCustomDrillCycleMacroName(const char *szStreamName, char *szMacroName);

GC_CDC_API int gc_cdc_GetProcessCustomDrillCycleMacroName(int iProcess, char *szMacroName);
GC_CDC_API int gc_cdc_GetOpCustomDrillCycleMacroName(int iOp, char *szMacroName);

GC_CDC_API int gc_cdc_CreateCustomDrillCycleDataDescriptor(int iOp, char *szMacroName);

// custom cycle names

GC_CDC_API int gc_cdc_GetCustomCycleNumber(int iDrillEntry, char *szMacroName);
GC_CDC_API int gc_cdc_GetCustomMacroName(int iMenuItem, char *szMacroName);

GC_CDC_API int gc_cdc_ParseCustomCycleMacroName(const char *szMacroName, char *szAuthor, char *szName, char *szType);
GC_CDC_API int gc_cdc_MatchCustomCycleMacroName(int iProcess, int *iMatch);

// change process custom cycle data

GC_CDC_API int gc_cdc_ChangeProcessCustomDrillCycleData(int iProc, int iMenuItem);

// init extended drill cycle availability

GC_CDC_API void gc_cdc_InitExtDrillCycles();

// get standard drill dialog flags

#define	gc_cdc_sDialogFlagUseMacro  "UseMacroDialog"
#define	gc_cdc_sDialogFlagPeck      "DrillDialogPeck"
#define	gc_cdc_sDialogFlagClearance "DrillDialogClearance"
#define	gc_cdc_sDialogFlagRetract   "DrillDialogRetract"
#define	gc_cdc_sDialogFlagTap       "DrillDialogTap"
#define	gc_cdc_sDialogFlagRigidTap  "DrillDialogRigidTap"
#define	gc_cdc_sDialogFlagPullOff   "DrillDialogPullOff"
#define	gc_cdc_sDialogFlagDrillUp   "DrillDialogDrillUp"
#define	gc_cdc_sDialogFlagDwell     "DrillDialogDwell"

enum
{
	gc_cdc_iDialogFlagUseMacro = 0,
	gc_cdc_iDialogFlagPeck,
	gc_cdc_iDialogFlagClearance,
	gc_cdc_iDialogFlagRetract,
	gc_cdc_iDialogFlagTap,
	gc_cdc_iDialogFlagRigidTap,
	gc_cdc_iDialogFlagPullOff,	
	gc_cdc_iDialogFlagDrillUp,
	gc_cdc_iDialogFlagDwell,
	gc_cdc_iNumDialogFlags,		// must be last
};

GC_CDC_API int gc_cdc_GetProcessDialogFlags(int iMachineType, int iProcess);
GC_CDC_API int gc_cdc_GetOpDialogFlags(int iMachineType, int iOp);
GC_CDC_API int gc_cdc_GetMenuItemDialogFlags(int iMachineType, int iMenuItem);

GC_CDC_API bool gc_cdc_GetDialogUseMacro();
GC_CDC_API bool gc_cdc_GetDialogPeck();
GC_CDC_API bool gc_cdc_GetDialogClearance();
GC_CDC_API bool gc_cdc_GetDialogRetract();
GC_CDC_API bool gc_cdc_GetDialogTap();
GC_CDC_API bool gc_cdc_GetDialogRigidTap();
GC_CDC_API bool gc_cdc_GetDialogPulloff();
GC_CDC_API bool gc_cdc_GetDialogDrillUp();
GC_CDC_API bool gc_cdc_GetDialogDwell();

#endif //_API_CDC_H_
