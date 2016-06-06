#pragma once

#include "CManagedDialog.h"
#include "UAtrApi.h"	//also includes api.h
#include "millfeat.h"


static const double xMaxSingle		= 3.4e+38;

struct trMFUIItems{
	int iFromFeatRB;			// radio button - depth from feature
	int iFromToolRB;			// radio button - depth from tool
	int iCP2ET;					// edit text - entry clear
	int iIncCP2ET;				// edit text - incremental entry clear
	int iTopSurfZET;			// edit text - top surface z

	int iIncFeatDepthET;		// edit text - incremental feature depth, measured from top surface z
	int iCP3ET;					// edit text - exit clear
	int iIncToolDepthET;		// edit text - incremental finish depth, measured from top surface z
	int iAbsToolDepthET;		// edit text - absolute finish depth
	int iAbsFeatDepthET;		// edit text - absolute finish depth, from feature

	int iRedFrameIncFeat;		// frame - red box around incremental feature
	int iRedFrameAbsFeat;		// frame - red box around absolute feature
	int iPictTool;				// frame - absolute down
	int iCP2DownPict;			// frame - entry clear down
	int iCP2UpPict;				// frame - entry clear up

	int iIncCP2DownPict;		// frame - incremental entry clear down
	int iIncCP2UpPict;			// frame - incremental entry clear up
	int iCP3UpPict;				// frame - exit clear up

	int iMachCSDropDown;

	int iPict3800;				// bitmap - depth from tool, absolute entry clear
	int iPict3802;				// bitmap - depth from tool, incremental entry clear

	int iPict3803;				// bitmap - down arrow
	int iPict3804;				// bitmap - up arrow

	int iPict3820;				// bitmap - depth from feature, absolute entry clear
	int iPict3830;				// bitmap - depth from feature, incremental entry clear

	// these 4 images are used to replace 3800, 3802, 3820 and 3830
	// when machining on the OD of a turned part

	int iPict3850;
	int iPict3852;
	int iPict3870;
	int iPict3880;
	CString automatic;

	bool bRotaryTab;			// true if your dialog has a separate rotary tab

	int iRedArrowCtrlID;

	int iPict3821;
	int iPict3822;
	int iPict3823;

	trMFUIItems() {}

	trMFUIItems( int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11, int arg12, int arg13, int arg14,
		int arg15, int arg16, int arg17, int arg18, int arg19, int arg20, int arg21, int arg22, int arg23, int arg24, int arg25, int arg26, int arg27, int arg28, int arg29, CString arg30 )
	{
		iFromFeatRB = arg1; iFromToolRB = arg2; iCP2ET = arg3; iIncCP2ET = arg4; iTopSurfZET = arg5; 
		iIncFeatDepthET = arg6; iCP3ET = arg7; iIncToolDepthET = arg8; iAbsToolDepthET = arg9; iAbsFeatDepthET = arg10; 
		iRedFrameIncFeat = arg11; iRedFrameAbsFeat = arg12; iPictTool = arg13; iCP2DownPict = arg14; iCP2UpPict = arg15; 
		iIncCP2DownPict = arg16; iIncCP2UpPict = arg17; iCP3UpPict = arg18; iMachCSDropDown = arg19; iPict3800 = arg20; 
		iPict3802 = arg21; iPict3803 = arg22; iPict3804 = arg23; iPict3820 = arg24; iPict3830 = arg25; 
		iPict3850 = arg26; iPict3852 = arg27; iPict3870 = arg28; iPict3880 = arg29;
		automatic = CString(arg30); bRotaryTab = true;

		iRedArrowCtrlID = -1; iPict3821 = -1; iPict3822 = -1; iPict3823 = -1;
	}

	trMFUIItems( int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11, int arg12, int arg13, int arg14,
		int arg15, int arg16, int arg17, int arg18, int arg19, int arg20, int arg21, int arg22, int arg23, int arg24, int arg25, int arg26, int arg27, int arg28, int arg29, CString arg30, bool arg31 )
	{
		iFromFeatRB = arg1; iFromToolRB = arg2; iCP2ET = arg3; iIncCP2ET = arg4; iTopSurfZET = arg5; 
		iIncFeatDepthET = arg6; iCP3ET = arg7; iIncToolDepthET = arg8; iAbsToolDepthET = arg9; iAbsFeatDepthET = arg10; 
		iRedFrameIncFeat = arg11; iRedFrameAbsFeat = arg12; iPictTool = arg13; iCP2DownPict = arg14; iCP2UpPict = arg15; 
		iIncCP2DownPict = arg16; iIncCP2UpPict = arg17; iCP3UpPict = arg18; iMachCSDropDown = arg19; iPict3800 = arg20; 
		iPict3802 = arg21; iPict3803 = arg22; iPict3804 = arg23; iPict3820 = arg24; iPict3830 = arg25; 
		iPict3850 = arg26; iPict3852 = arg27; iPict3870 = arg28; iPict3880 = arg29;
		automatic = CString(arg30); bRotaryTab = arg31;

		iRedArrowCtrlID = -1; iPict3821 = -1; iPict3822 = -1; iPict3823 = -1;
	}

	trMFUIItems( int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11, int arg12, int arg13, int arg14,
		int arg15, int arg16, int arg17, int arg18, int arg19, int arg20, int arg21, int arg22, int arg23, int arg24, int arg25, int arg26, int arg27, int arg28, int arg29, CString arg30, bool arg31,
		int arg32, int arg33, int arg34, int arg35 )
	{
		iFromFeatRB = arg1; iFromToolRB = arg2; iCP2ET = arg3; iIncCP2ET = arg4; iTopSurfZET = arg5; 
		iIncFeatDepthET = arg6; iCP3ET = arg7; iIncToolDepthET = arg8; iAbsToolDepthET = arg9; iAbsFeatDepthET = arg10; 
		iRedFrameIncFeat = arg11; iRedFrameAbsFeat = arg12; iPictTool = arg13; iCP2DownPict = arg14; iCP2UpPict = arg15; 
		iIncCP2DownPict = arg16; iIncCP2UpPict = arg17; iCP3UpPict = arg18; iMachCSDropDown = arg19; iPict3800 = arg20; 
		iPict3802 = arg21; iPict3803 = arg22; iPict3804 = arg23; iPict3820 = arg24; iPict3830 = arg25; 
		iPict3850 = arg26; iPict3852 = arg27; iPict3870 = arg28; iPict3880 = arg29;
		automatic = CString(arg30); bRotaryTab = arg31;
		iRedArrowCtrlID = arg32; iPict3821 = arg33; iPict3822 = arg34; iPict3823 = arg35;
	}
};

inline bool RotaryODCS()
{
	bool bRotaryODCS = false;
	if (gc_IsLathePart() == 1)
	{
		int iCS = 0, iWP = -1;
		gc_GetCurOpCS(&iCS);
		gc_GetCSWP(iCS, &iWP);
		
		int iAxis4th = -1, iAxis5th = -1;
		double dAxis[3] = {0.0, 0.0, 1.0};
		if (gc_GetWPRotAxes(iWP, &iAxis4th, &iAxis5th) > 0)
		{
			gc_GetWPRotAxisInfo(iWP, (iAxis4th != -1) ? gc_eiMachRot4 : gc_eiMachRot5, 0, dAxis, 0);
		}

		int iXYCS = -1;
		gc_GetWPXYCS(iWP, &iXYCS);
		gc_CSTransformVec(iXYCS, iCS, dAxis);
		
		if (fabs(dAxis[2]) < 5.0e-5)
			bRotaryODCS = true;
	}
	return bRotaryODCS;
}

inline double GetAttValue( const wchar_t* att_name, bool bReal = true, bool bSync = false)
{
	//get all the currently selected features via Feature Manager
	int* feats;
	int num_feats = UATR::GetNumSelFeaturesEx(bSync);
	if( num_feats > 0 )
	{
		feats = new int[num_feats];
		UATR::GetSelectedFeatureIDs( feats, num_feats, bSync );
		//get the first feature
		UATR::AttrTable attr;
		UATR::GetAttrsFromFeature( UATR::FeatureID(feats[0]), attr );
		UATR::AttrTable::iterator attr_itr = attr.begin();
		while( attr_itr != attr.end() )
		{
			if( attr_itr->eType == UATR::eAttType_NumericReal || attr_itr->eType == UATR::eAttType_NumericInteger )
			{
				//to get the name, need to pull it from the all attribute table
				UATR::AttrTable sel_feats_atts = UATR::GetGlobalAttrs(0, bReal ? UATR::eAttTypeMask_NumericReal : UATR::eAttTypeMask_NumericInteger );
				UATR::AttrTable::iterator sel_atts_itr = sel_feats_atts.begin();
				for( ; sel_atts_itr != sel_feats_atts.end(); sel_atts_itr++ )
				{
					if( sel_atts_itr->tableName == attr_itr->tableName )
					{
						if( _wcsicmp( sel_atts_itr->name.c_str(), att_name ) == 0 )
						{
							if( bReal )
								return (attr_itr->GetValF());
							else
								return (double)(attr_itr->GetValI());
						}
					}
				}
			}
			attr_itr++;
		}

		delete []feats;
	}
	else
	{
		UATR::AttrTable all_atts = UATR::GetGlobalAttrs(0, bReal ? UATR::eAttTypeMask_NumericReal : UATR::eAttTypeMask_NumericInteger );
		UATR::AttrTable::iterator itr = all_atts.begin();
		while( itr != all_atts.end() )
		{
			if( _wcsicmp( itr->name.c_str(), att_name ) == 0 )
			{
				if( bReal )
					return (itr->GetValF());
				else
					return (double)(itr->GetValI());
			}
			itr++;
		}
	}
	return 0.0;
}

inline void StripZeros(char* sValue)
{
	int	i;
	/* remove trailing zeros... */
	for (i=(int)strlen(sValue)-1; i>=0; i--)
		if (sValue[i] != '0')
			break;
		else
			sValue[i] = 0;
	/* remove trailing decimal point... */
	if (sValue[i] == '.')
		sValue[i] = 0;
	/* remove minus sign from zero... */
	if ((strlen(sValue) == 2) && (sValue[0] == '-') && (sValue[1] == '0'))
	{
		sValue[0] = '0';
		sValue[1] = 0;
	}
}

class MFDataControl
{
private:
	trMFUIItems millfeat_items;
	CManagedPropertyPage* dlog_window;
	int proc_num;
	int m_iCurPictID;
	int m_iCurRedPictID;
	BOOL m_InUpdate;
	trMillFeatInfo m_feat_data;

public:
	MFDataControl() { dlog_window = NULL; };
	MFDataControl( trMFUIItems _input, CManagedPropertyPage* _window, int _proc )
	{ 
		ASSERT(_window); 
		millfeat_items = _input; 
		dlog_window = _window;
		proc_num = _proc;
		m_iCurPictID = -1;
		m_iCurRedPictID = -1;
		m_InUpdate = false;
		m_feat_data = trMillFeatInfo();
	}

	~MFDataControl() {};

	void SetDlgItemDouble( int id, double xValue )
	{
		char sValue[256] = {0};

		bool bMetric = false;
		int iUnit = 0;
		gc_GetPartInfoI(eiPartUnit, &iUnit);
		bMetric = (iUnit == 0) ? true : false;
		short		iPrec =	(bMetric ? 3 : 5);
		if ((xValue > xMaxSingle) || (xValue < - xMaxSingle))
		{
			char	sError[256] = {0};
			//???getlocalresstr(sError, 3, 11);	// "Invalid"
			sprintf_s(sValue, "%s", sError);
		}
		else
			sprintf_s(sValue, "%.*f", iPrec, xValue);
		StripZeros(sValue);
		m_InUpdate = true;
		SetDlgItemText(dlog_window->m_hWnd, id, sValue);
		m_InUpdate = false;
	}

	double GetDlgItemDouble( int id )
	{
		CString str;
		dlog_window->GetDlgItemText(id, str);
		return atof(str);
	}

	void FromToolToData()
	{
		if( m_InUpdate )
			return;

		trMillFeatInfo feat_data = GetMFInfo();
		if( feat_data.bDepthFromFeat )
		{
			feat_data.bDepthFromFeat = ( dlog_window->IsDlgButtonChecked( millfeat_items.iFromToolRB ) == 1 ? false : true );
			feat_data.dTipZ = feat_data.dAbsFeatDepth + feat_data.dIncToolDepth;
			SetDlgItemDouble( millfeat_items.iAbsToolDepthET, feat_data.dTipZ );
		}
		UpdateData( feat_data );
	}

	void FromFeatToData()
	{
		if( m_InUpdate )
			return;

		trMillFeatInfo feat_data = GetMFInfo();
		if( !feat_data.bDepthFromFeat )
		{
			feat_data.bDepthFromFeat = ( dlog_window->IsDlgButtonChecked( millfeat_items.iFromFeatRB ) == 1 ? true : false );
			feat_data.dAbsFeatDepth = feat_data.dTipZ - feat_data.dIncToolDepth;
			feat_data.dIncFeatDepth = feat_data.dAbsFeatDepth - feat_data.dSurfZ;
			SetDlgItemDouble( millfeat_items.iAbsFeatDepthET, feat_data.dAbsFeatDepth );
			SetDlgItemDouble( millfeat_items.iIncToolDepthET, feat_data.dIncToolDepth );
			SetDlgItemDouble( millfeat_items.iIncFeatDepthET, feat_data.dIncFeatDepth );
		}
		UpdateData( feat_data );
	}

	void CP2ToData()
	{
		if( m_InUpdate )
			return;

		trMillFeatInfo feat_data = GetMFInfo();

		feat_data.dEntryClearance = GetDlgItemDouble( millfeat_items.iCP2ET );

		UpdateData( feat_data );
	}

	void IncCP2ToData()
	{
		if( m_InUpdate )
			return;

		trMillFeatInfo feat_data = GetMFInfo();

		if( feat_data.eCP2Val == eIncValue )
			feat_data.dIncCP2 = GetDlgItemDouble( millfeat_items.iIncCP2ET );

		UpdateData( feat_data );
	}

	void TopSurfToData()
	{
		if( m_InUpdate )
			return;

		trMillFeatInfo feat_data = GetMFInfo();
		feat_data.dSurfZ = GetDlgItemDouble( millfeat_items.iTopSurfZET );
		if( feat_data.bDepthFromFeat )
		{
			feat_data.dIncFeatDepth = feat_data.dAbsFeatDepth - feat_data.dSurfZ;
			SetDlgItemDouble( millfeat_items.iIncFeatDepthET, feat_data.dIncFeatDepth );
		}

		UpdateData( feat_data );
	}

	void IncFeatDToData()
	{
		if( m_InUpdate )
			return;

		trMillFeatInfo feat_data = GetMFInfo();

		feat_data.dIncFeatDepth = GetDlgItemDouble( millfeat_items.iIncFeatDepthET );
		if( feat_data.bDepthFromFeat )
		{
			feat_data.dTipZ = feat_data.dAbsFeatDepth = feat_data.dIncFeatDepth + feat_data.dSurfZ;
			SetDlgItemDouble( millfeat_items.iAbsFeatDepthET, feat_data.dAbsFeatDepth );
		}

		UpdateData( feat_data );
	}

	void CP3ToData()
	{
		if( m_InUpdate )
			return;

		trMillFeatInfo feat_data = GetMFInfo();

		feat_data.dExitClearance = GetDlgItemDouble( millfeat_items.iCP3ET );

		UpdateData( feat_data );
	}

	void IncToolDToData()
	{
		if( m_InUpdate )
			return;

		trMillFeatInfo feat_data = GetMFInfo();
		if( feat_data.bDepthFromFeat )
		{
			feat_data.dIncToolDepth = GetDlgItemDouble( millfeat_items.iIncToolDepthET );
			feat_data.dTipZ = feat_data.dAbsFeatDepth + feat_data.dIncToolDepth;
		}

		UpdateData( feat_data );
	}

	void AbsToolDToData()
	{
		if( m_InUpdate )
			return;

		trMillFeatInfo feat_data = GetMFInfo();

		feat_data.dTipZ = GetDlgItemDouble( millfeat_items.iAbsToolDepthET );
		if( !feat_data.bDepthFromFeat )
		{
			feat_data.dIncFeatDepth = feat_data.dTipZ - feat_data.dSurfZ;
			feat_data.dAbsFeatDepth = feat_data.dTipZ;
		}

		UpdateData(feat_data);
	}

	void AbsFeatDToData()
	{
		if( m_InUpdate )
			return;

		trMillFeatInfo feat_data = GetMFInfo();
		if( feat_data.bDepthFromFeat )
		{
			feat_data.dAbsFeatDepth = GetDlgItemDouble( millfeat_items.iAbsFeatDepthET );
			feat_data.dTipZ = feat_data.dAbsFeatDepth + feat_data.dIncToolDepth;
			feat_data.dIncFeatDepth = feat_data.dAbsFeatDepth - feat_data.dSurfZ;

			SetDlgItemDouble( millfeat_items.iIncFeatDepthET, feat_data.dIncFeatDepth );
		}

		UpdateData( feat_data );
	}

	void DataToItems( void )
	{
		m_InUpdate = true;
		trMillFeatInfo feat_data = GetMFInfo();
		double dCP3Val = 0.0, dCP2Val = 0.0, dTopSurfZ = 0.0, dFeatVal = 0.0;

		if( feat_data.eCP3Val == eAttribValue )
		{
			dCP3Val = GetAttValue( feat_data.wsCP3AttName );
			SetDlgItemDouble(millfeat_items.iCP3ET, dCP3Val);
		}

		if( feat_data.eCP2Val == eAttValue )
		{
			dCP2Val = GetAttValue( feat_data.wsCP2AttName );
			SetDlgItemDouble(millfeat_items.iCP2ET, dCP2Val);
		}

		if( feat_data.eTopSurfVal == eAttValue2 )
		{
			dTopSurfZ = GetAttValue( feat_data.wsTopSurfAttName );
			SetDlgItemDouble(millfeat_items.iTopSurfZET, dTopSurfZ);
		}
		else
			dFeatVal = GetDlgItemDouble(millfeat_items.iTopSurfZET);

		dTopSurfZ = GetDlgItemDouble( millfeat_items.iTopSurfZET );
		if( feat_data.eFeatVal == eAttValue2 )
		{
			dFeatVal = GetAttValue( feat_data.wsFeatDAttName );
			if( feat_data.bDepthFromFeat )
			{
				SetDlgItemDouble(millfeat_items.iAbsFeatDepthET, dFeatVal);
				SetDlgItemDouble(millfeat_items.iIncFeatDepthET, dFeatVal - dTopSurfZ );
			}
			else
				SetDlgItemDouble(millfeat_items.iAbsToolDepthET, dFeatVal);
		}
		else
			dFeatVal = GetDlgItemDouble(millfeat_items.iAbsFeatDepthET);

		if( feat_data.eTopSurfVal == eAttValue2 || feat_data.eFeatVal == eAttValue2 )
		{
			if( feat_data.eTopSurfVal == eCalcValue || feat_data.eFeatVal == eCalcValue )
			{
				dlog_window->SetDlgItemText(millfeat_items.iIncFeatDepthET, millfeat_items.automatic );
				dlog_window->GetDlgItem(millfeat_items.iIncFeatDepthET)->EnableWindow( false );
			}
			else
			{
				SetDlgItemDouble( millfeat_items.iIncFeatDepthET, (dFeatVal - dTopSurfZ) );
				dlog_window->GetDlgItem(millfeat_items.iIncFeatDepthET)->EnableWindow( true );
			}
		}

		BOOL success = FALSE;
		success = CheckDlgButton(dlog_window->m_hWnd, millfeat_items.iFromToolRB, !feat_data.bDepthFromFeat );
		success = CheckDlgButton(dlog_window->m_hWnd, millfeat_items.iFromFeatRB, feat_data.bDepthFromFeat );

		SetDlgItemDouble( millfeat_items.iCP2ET, feat_data.dEntryClearance );
		SetDlgItemDouble( millfeat_items.iCP3ET, feat_data.dExitClearance );

		SetDlgItemDouble( millfeat_items.iIncCP2ET, feat_data.dIncCP2 );

		if( feat_data.eTopSurfVal == eUserVal )
			SetDlgItemDouble( millfeat_items.iTopSurfZET, feat_data.dSurfZ );

		SetDlgItemDouble( millfeat_items.iIncToolDepthET, feat_data.dIncToolDepth );
		SetDlgItemDouble( millfeat_items.iAbsToolDepthET, feat_data.dTipZ );		

		if( feat_data.eTopSurfVal == eUserVal && feat_data.eFeatVal == eUserVal )
			SetDlgItemDouble( millfeat_items.iIncFeatDepthET, feat_data.dIncFeatDepth );

		if(feat_data.eFeatVal == eUserVal)
			SetDlgItemDouble( millfeat_items.iAbsFeatDepthET, feat_data.dAbsFeatDepth );

		if( feat_data.eMachCSVal == eAttValue2 && millfeat_items.iMachCSDropDown > 0 && !gc_HasRotary())
		{
			double iMachCS = GetAttValue( feat_data.wsFeatMachCSAttName );

			char name[256] = {0};
			if (gc_GetCSName(int(iMachCS), name) == -2)
			{
				int iCS;
				gc_GetCSNumber(0, &iCS);
				iMachCS = double(iCS);
			}

			CComboBox *combo = (CComboBox*)dlog_window->GetDlgItem(millfeat_items.iMachCSDropDown);
			int count = combo->GetCount();
			bool found = FALSE;
			for( int i = 0; i < count; i++ )
			{
				CString lbl;
				combo->GetLBText(i, lbl);
				if( lbl.CompareNoCase( name ) == 0 )
				{
					combo->SetCurSel(i);
					found = TRUE;
					break;
				}
			}
		}

		memcpy( &m_feat_data, &feat_data, sizeof( trMillFeatInfo ) );
		m_InUpdate = false;
		ShowItems();
	}

	void UpdateData( const trMillFeatInfo &feat_info )
	{
		SetMFInfo( feat_info );
		ShowItems();
	}

	void UpdateUI( )
	{
		trMillFeatInfo info = GetMFInfo();
	}

	void ShowItems()
	{
		trMillFeatInfo info = GetMFInfo();
		BOOL bIncCP2 = FALSE, bCP2FromFeat = FALSE, bCP3SameAsCP2 = FALSE, 
			bTopSurfFromFeat = FALSE, bDepthFromAtt = FALSE, bCP3FromFeat = FALSE,
			bTopSurfAuto = FALSE, bCutDAuto = FALSE;

		bIncCP2 = ( info.eCP2Val == eIncValue);
		bCP2FromFeat = ( info.eCP2Val == eAttValue);
		bCP3SameAsCP2 = ( info.eCP3Val == eSameAsApproach);
		bTopSurfFromFeat = ( info.eTopSurfVal == eAttValue2);
		bDepthFromAtt = ( info.eFeatVal == eAttValue2 );
		bCP2FromFeat = ( info.eCP2Val == eAttValue );
		bCP3FromFeat = ( info.eCP3Val == eAttribValue ? TRUE : FALSE) && !bCP3SameAsCP2;
		bTopSurfAuto = ( info.eTopSurfVal == eCalcValue );
		bCutDAuto = ( info.eFeatVal == eCalcValue );

		bool bIncFeatDepthET = true;
		bool bIncToolDepthET = true;
		bool bAbsFeatDepthET = true;
		bool bAbsToolDepthET = true;
		bool bTopSurfZET = true;

		dlog_window->GetDlgItem(millfeat_items.iAbsFeatDepthET)->ShowWindow(info.bDepthFromFeat ? SW_SHOW : SW_HIDE );
		dlog_window->GetDlgItem(millfeat_items.iIncFeatDepthET)->ShowWindow(info.bDepthFromFeat ? SW_SHOW : SW_HIDE );
		//mike		dlog_window->GetDlgItem(millfeat_items.iAbsFeatDepthET)->EnableWindow( !bDepthFromAtt && !bCutDAuto );

		dlog_window->GetDlgItem(millfeat_items.iIncCP2ET)->ShowWindow(bIncCP2 ? SW_SHOW : SW_HIDE );
		dlog_window->GetDlgItem(millfeat_items.iCP3ET)->ShowWindow(bCP3SameAsCP2 ? SW_HIDE : SW_SHOW );
		dlog_window->GetDlgItem(millfeat_items.iCP2ET)->ShowWindow(bIncCP2 ? SW_HIDE : SW_SHOW  );

		dlog_window->GetDlgItem(millfeat_items.iCP3ET)->EnableWindow( !bCP3FromFeat );
		dlog_window->GetDlgItem(millfeat_items.iCP2ET)->EnableWindow( !bCP2FromFeat && !bIncCP2);

		dlog_window->GetDlgItem(millfeat_items.iRedFrameAbsFeat)->ShowWindow(info.bDepthFromFeat ? SW_SHOW : SW_HIDE );
		dlog_window->GetDlgItem(millfeat_items.iRedFrameIncFeat)->ShowWindow(info.bDepthFromFeat ? SW_SHOW : SW_HIDE );

		dlog_window->GetDlgItem(millfeat_items.iIncCP2DownPict)->ShowWindow( bIncCP2 ? SW_SHOW : SW_HIDE );
		dlog_window->GetDlgItem(millfeat_items.iIncCP2UpPict)->ShowWindow(bIncCP2 && bCP3SameAsCP2? SW_SHOW : SW_HIDE );
		dlog_window->GetDlgItem(millfeat_items.iCP3UpPict)->ShowWindow(bCP3SameAsCP2 ? SW_HIDE : SW_SHOW );
		dlog_window->GetDlgItem(millfeat_items.iCP2DownPict)->ShowWindow(!bIncCP2 ? SW_SHOW : SW_HIDE );
		dlog_window->GetDlgItem(millfeat_items.iCP2UpPict)->ShowWindow(!bIncCP2 && bCP3SameAsCP2? SW_SHOW : SW_HIDE );

		if ( bTopSurfFromFeat || bTopSurfAuto) bTopSurfZET = bIncFeatDepthET = false;

		if( millfeat_items.iIncToolDepthET != -1 )
			dlog_window->GetDlgItem(millfeat_items.iIncToolDepthET)->EnableWindow( TRUE );

		if( millfeat_items.iIncToolDepthET != millfeat_items.iAbsToolDepthET )
		{
			dlog_window->GetDlgItem(millfeat_items.iIncToolDepthET)->ShowWindow( info.bDepthFromFeat ? SW_SHOW : SW_HIDE );
			dlog_window->GetDlgItem(millfeat_items.iAbsToolDepthET)->ShowWindow( info.bDepthFromFeat ? SW_HIDE : SW_SHOW );

			if( info.bDepthFromFeat )
				dlog_window->GetDlgItem(millfeat_items.iIncToolDepthET)->EnableWindow( TRUE );
			else
				dlog_window->GetDlgItem(millfeat_items.iIncToolDepthET)->EnableWindow( FALSE );
		}
		else
		{
			if( info.bDepthFromFeat )
				dlog_window->GetDlgItem(millfeat_items.iIncToolDepthET)->EnableWindow( TRUE );
			else
				dlog_window->GetDlgItem(millfeat_items.iIncToolDepthET)->EnableWindow( !bCutDAuto && !bDepthFromAtt );
		}

		if( millfeat_items.iMachCSDropDown != -1 )
		{
			if ( millfeat_items.bRotaryTab && gc_HasRotary() )
				dlog_window->GetDlgItem(millfeat_items.iMachCSDropDown)->ShowWindow(SW_HIDE);
			else
			{
				dlog_window->GetDlgItem(millfeat_items.iMachCSDropDown)->ShowWindow(SW_SHOW);
				dlog_window->GetDlgItem(millfeat_items.iMachCSDropDown)->EnableWindow( (info.eMachCSVal == eAttValue2) ? FALSE : TRUE );
			}
		}

		m_InUpdate = true;
		if( bCutDAuto || bDepthFromAtt )
		{
			if( info.bDepthFromFeat )
			{
				if( bCutDAuto )
				{
					dlog_window->SetDlgItemText(millfeat_items.iAbsFeatDepthET, millfeat_items.automatic );
					dlog_window->SetDlgItemText(millfeat_items.iIncFeatDepthET, millfeat_items.automatic );
				}
				else
				{
					double dCutDAtt = GetAttValue( info.wsFeatDAttName, true, false );
					double dIncFeatD = 0.0;

					if( !bTopSurfAuto )
					{
						double dVal = info.dSurfZ;
						if( bTopSurfFromFeat )
							dVal = GetAttValue( info.wsTopSurfAttName );
						SetDlgItemDouble( millfeat_items.iAbsFeatDepthET, dCutDAtt );
						dIncFeatD = dCutDAtt - dVal;

						SetDlgItemDouble( millfeat_items.iIncFeatDepthET, dIncFeatD );
					}
					else
						dlog_window->SetDlgItemText(millfeat_items.iIncFeatDepthET, millfeat_items.automatic );
				}

				bAbsFeatDepthET = false;
				bIncFeatDepthET = false;
				bAbsToolDepthET = false;
			}
			else
			{
				double dCutDAtt = GetAttValue( info.wsFeatDAttName, true, false );

				if( bCutDAuto )
					dlog_window->SetDlgItemText(millfeat_items.iAbsToolDepthET, millfeat_items.automatic );
				else
					SetDlgItemDouble( millfeat_items.iAbsFeatDepthET, dCutDAtt );
				bAbsToolDepthET = false;
			}
		}

		if( bTopSurfAuto )
		{
			dlog_window->SetDlgItemText(millfeat_items.iTopSurfZET, millfeat_items.automatic );
			if( info.bDepthFromFeat )
				dlog_window->SetDlgItemText(millfeat_items.iIncFeatDepthET, millfeat_items.automatic );
			bTopSurfZET = false;
		}

		dlog_window->GetDlgItem(millfeat_items.iAbsFeatDepthET)->EnableWindow( bAbsFeatDepthET && !bDepthFromAtt );
		dlog_window->GetDlgItem(millfeat_items.iIncFeatDepthET)->EnableWindow( bIncFeatDepthET && ( !bDepthFromAtt && !bTopSurfFromFeat) );
		dlog_window->GetDlgItem(millfeat_items.iAbsToolDepthET)->EnableWindow( bAbsToolDepthET && !bDepthFromAtt);
		dlog_window->GetDlgItem(millfeat_items.iIncToolDepthET)->EnableWindow( bIncToolDepthET );
		dlog_window->GetDlgItem(millfeat_items.iTopSurfZET)->EnableWindow( bTopSurfZET );

		m_InUpdate = false;

		UpdateBGPict();
	}

	double GetAbsToolDepth()
	{
		trMillFeatInfo feat = GetMFInfo();
		return feat.dTipZ;
	}

	void DoDDX( CDataExchange* pDX )
	{
		if( !pDX->m_bSaveAndValidate )
			DataToItems();
	}

	trMillFeatInfo GetMFInfo()
	{
		//should all be procinfo...
		trMillFeatInfo info;
		info.iProc = proc_num;
		gc_GetProcInfoD(info.iProc, gc_efProcMillFeat_IncToolDepth,  &info.dIncToolDepth);
		gc_GetProcInfoD(info.iProc, gc_efProcMillFeat_IncFeatDepth,  &info.dIncFeatDepth);
		gc_GetProcInfoD(info.iProc, gc_efProcMillFeat_AbsFeatDepth,  &info.dAbsFeatDepth);
		gc_GetProcInfoD(info.iProc, gc_efProcMillFeat_IncApproachZ,  &info.dIncCP2);

		gc_GetProcInfoWS(info.iProc, gc_ewsProcMillFeat_ApproachZ, info.wsCP2AttName);
		gc_GetProcInfoWS(info.iProc, gc_ewsProcMillFeat_RetractZ,  info.wsCP3AttName);
		gc_GetProcInfoWS(info.iProc, gc_ewsProcMillFeat_TopSurfZ,  info.wsTopSurfAttName);
		gc_GetProcInfoWS(info.iProc, gc_ewsProcMillFeat_FeatZ,     info.wsFeatDAttName);
		gc_GetProcInfoWS(info.iProc, gc_ewsProcMillFeat_MachCS,    info.wsFeatMachCSAttName);

		gc_GetProcInfoI(info.iProc, gc_eiProcMillFeat_DepthFromFeat,  &info.bDepthFromFeat);
		gc_GetProcInfoI(info.iProc, gc_eiProcMillFeat_ApproachZType3, &info.eCP2Val);
		gc_GetProcInfoI(info.iProc, gc_eiProcMillFeat_RetractZType,   &info.eCP3Val);
		gc_GetProcInfoI(info.iProc, gc_eiProcMillFeat_FeatZType2,     &info.eFeatVal);
		gc_GetProcInfoI(info.iProc, gc_eiProcMillFeat_TopSurfZType2,  &info.eTopSurfVal);
		gc_GetProcInfoI(info.iProc, gc_eiProcMillFeat_MachCSType2,    &info.eMachCSVal);

		gc_GetProcInfoD(info.iProc, efProcEntryClr,    &info.dEntryClearance);
		gc_GetProcInfoD(info.iProc, efProcExitClr,     &info.dExitClearance);
		gc_GetProcInfoD(info.iProc, efProcSurfZ,       &info.dSurfZ);
		gc_GetProcInfoD(info.iProc, efProcTipZ,        &info.dTipZ);
		return info;
	}

	void SetMFInfo(const trMillFeatInfo& info)
	{
		trMillFeatInfo oldInfo = GetMFInfo();
		gc_SetProcInfoD(info.iProc, gc_efProcMillFeat_IncToolDepth,  (double*)&info.dIncToolDepth);
		gc_SetProcInfoD(info.iProc, gc_efProcMillFeat_IncFeatDepth,  (double*)&info.dIncFeatDepth);
		gc_SetProcInfoD(info.iProc, gc_efProcMillFeat_AbsFeatDepth,  (double*)&info.dAbsFeatDepth);
		gc_SetProcInfoD(info.iProc, gc_efProcMillFeat_IncApproachZ,  (double*)&info.dIncCP2);

		gc_SetProcInfoWS(info.iProc, gc_ewsProcMillFeat_ApproachZ, (wchar_t*)info.wsCP2AttName);
		gc_SetProcInfoWS(info.iProc, gc_ewsProcMillFeat_RetractZ,   (wchar_t*)info.wsCP3AttName);
		gc_SetProcInfoWS(info.iProc, gc_ewsProcMillFeat_TopSurfZ,   (wchar_t*)info.wsTopSurfAttName);
		gc_SetProcInfoWS(info.iProc, gc_ewsProcMillFeat_FeatZ,      (wchar_t*)info.wsFeatDAttName);
		gc_SetProcInfoWS(info.iProc, gc_ewsProcMillFeat_MachCS,     (wchar_t*)info.wsFeatMachCSAttName);

		gc_SetProcInfoI(info.iProc, gc_eiProcMillFeat_DepthFromFeat,  (int*)&info.bDepthFromFeat);
		gc_SetProcInfoI(info.iProc, gc_eiProcMillFeat_ApproachZType3, (int*)&info.eCP2Val);
		gc_SetProcInfoI(info.iProc, gc_eiProcMillFeat_RetractZType,   (int*)&info.eCP3Val);
		gc_SetProcInfoI(info.iProc, gc_eiProcMillFeat_FeatZType2,     (int*)&info.eFeatVal);
		gc_SetProcInfoI(info.iProc, gc_eiProcMillFeat_TopSurfZType2,  (int*)&info.eTopSurfVal);
		gc_SetProcInfoI(info.iProc, gc_eiProcMillFeat_MachCSType2,    (int*)&info.eMachCSVal);

		gc_SetProcInfoD(info.iProc, efProcEntryClr,   (double*)&info.dEntryClearance);
		gc_SetProcInfoD(info.iProc, efProcExitClr,    (double*)&info.dExitClearance);
		gc_SetProcInfoD(info.iProc, efProcSurfZ,      (double*)&info.dSurfZ);
		gc_SetProcInfoD(info.iProc, efProcTipZ,       (double*)&info.dTipZ);
	}

	void OnInit()
	{
		((CMFTransparentPictCtrl*)dlog_window->GetDlgItem(millfeat_items.iCP2UpPict))->SetBitmap(millfeat_items.iPict3803);
		((CMFTransparentPictCtrl*)dlog_window->GetDlgItem(millfeat_items.iCP2DownPict))->SetBitmap(millfeat_items.iPict3804);

		((CMFTransparentPictCtrl*)dlog_window->GetDlgItem(millfeat_items.iIncCP2UpPict))->SetBitmap(millfeat_items.iPict3803);
		((CMFTransparentPictCtrl*)dlog_window->GetDlgItem(millfeat_items.iIncCP2DownPict))->SetBitmap(millfeat_items.iPict3804);

		((CMFTransparentPictCtrl*)dlog_window->GetDlgItem(millfeat_items.iCP3UpPict))->SetBitmap(millfeat_items.iPict3803);
	}

	int CalcRedArrowID( int iFocusItem )
	{
		if( dlog_window->IsDlgButtonChecked( millfeat_items.iFromFeatRB ) )
		{
			if( millfeat_items.iRedArrowCtrlID == -1 )
				return -1;

			if( iFocusItem == millfeat_items.iIncFeatDepthET )
				return millfeat_items.iPict3821;

			if( iFocusItem == millfeat_items.iAbsFeatDepthET )
				return millfeat_items.iPict3822;

			if( iFocusItem == millfeat_items.iTopSurfZET && ( dlog_window->IsDlgButtonChecked( millfeat_items.iFromFeatRB ) ) )
				return millfeat_items.iPict3823;
		}

		return -1;

	}

	void UpdateBGPict()
	{
		//determine bgpict id & set it
		int calc_id = 0;

		trMillFeatInfo rMillFeatInfo = GetMFInfo();
		//from tool
		if( !rMillFeatInfo.bDepthFromFeat )
		{
			calc_id += 3800;
			if( rMillFeatInfo.eCP2Val == eIncValue )
				calc_id += 2;
		}
		else
		{
			calc_id += 3820;
			if( rMillFeatInfo.eCP2Val == eIncValue )
				calc_id += 10;
		}

		if(RotaryODCS())
			calc_id += 50;

		switch(calc_id)
		{
			case 3800: calc_id = millfeat_items.iPict3800; break;
			case 3802: calc_id = millfeat_items.iPict3802; break;
			case 3820: calc_id = millfeat_items.iPict3820; break;
			case 3830: calc_id = millfeat_items.iPict3830; break;
			case 3850: calc_id = millfeat_items.iPict3850; break;
			case 3852: calc_id = millfeat_items.iPict3852; break;
			case 3870: calc_id = millfeat_items.iPict3870; break;
			case 3880: calc_id = millfeat_items.iPict3880; break;
		}
		int red_arrow = -1;

		int item = -1;
		if (dlog_window->GetFocus())
			item = dlog_window->GetFocus()->GetDlgCtrlID();

		red_arrow = CalcRedArrowID( item );

		bool bNeedUpdate = ( calc_id != m_iCurPictID ) || ( red_arrow != m_iCurRedPictID );

		if( bNeedUpdate )
		{
			if( millfeat_items.iPictTool != -1 )
				((CMFTransparentPictCtrl*)dlog_window->GetDlgItem(millfeat_items.iPictTool))->SetBitmap(calc_id);
			m_iCurPictID = calc_id;

			if( millfeat_items.iRedArrowCtrlID != -1 )
			{
				if( red_arrow > 0 )
				{
					((CMFTransparentPictCtrl*)dlog_window->GetDlgItem(millfeat_items.iRedArrowCtrlID))->SetBitmap(red_arrow);
					m_iCurRedPictID = red_arrow;
				}
				else
				{
					((CMFTransparentPictCtrl*)dlog_window->GetDlgItem(millfeat_items.iRedArrowCtrlID))->SetBitmap(calc_id);
					m_iCurRedPictID = calc_id;
				}
			}

			dlog_window->Invalidate();
		}
	}
};
