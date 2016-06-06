#pragma once

typedef enum
{
	eDialogValue = 1,
	eIncValue,
	eAttValue,
} teAttType3Val;

typedef enum
{
	eUserVal = 1,
	eAttValue2,
	eCalcValue,
} teAttType2Val;

typedef enum
{
	eDlgValue = 1,
	eSameAsApproach,
	eAttribValue,
} teAttSameAsVal;

struct trMillFeatInfo
{
	trMillFeatInfo()
	{
		iProc = 0;

		dIncToolDepth = 0.0;
		dIncFeatDepth = 0.0;
		bDepthFromFeat = true;
		dAbsFeatDepth  = 0.0;
		dIncCP2        = 0.0;

		dExitClearance = 0.0;
		dEntryClearance = 0.0;
		dSurfZ = 0.0;
		dTipZ     = 0.0;
		eCP2Val = eDialogValue;
		eCP3Val = eDlgValue;
		eFeatVal    = eUserVal;
		eTopSurfVal = eUserVal;
		eMachCSVal  = eUserVal;

		wsCP2AttName[0] = 0;
		wsCP3AttName[0] = 0;
		wsTopSurfAttName[0] = 0;
		wsFeatDAttName[0] = 0;
		wsFeatMachCSAttName[0] = 0;
	}
	int iProc;

	double dIncToolDepth;
	double dIncFeatDepth;
	double dAbsFeatDepth;
	double dIncCP2;

	int bDepthFromFeat;
	int eCP2Val;
	int eCP3Val;
	int eFeatVal;
	int eTopSurfVal;
	int eMachCSVal;

	wchar_t wsCP2AttName[256];
	wchar_t wsCP3AttName[256];
	wchar_t wsTopSurfAttName[256];
	wchar_t wsFeatDAttName[256];
	wchar_t wsFeatMachCSAttName[256];
	//proc stuff
	double dExitClearance;
	double dEntryClearance;
	double dSurfZ;
	double dTipZ;
};


