#pragma once
#include "GCTools.h"

#pragma pack(push, boost_align, 8)
namespace GCTools
{
	enum gc_teToolClass
	{
		gc_eMillTool = 0,
		gc_eLatheTool,
		gc_eUndefinedTool = 99
	};

	enum gc_teToolMaterial
	{
		gc_eHSS = 1,
		gc_eHSS_TiN_Coated,
		gc_eCarbide_Insert,
		gc_eCarbide_Insert_Coated,
		gc_eCarbide_Solid,
		gc_eDiamond,
		gc_eCeramic,
		gc_eOtherMaterial,
	};

	enum gc_teToolTypes
	{
		gc_eREMT = 0,
		gc_eFEMT,
		gc_eBEMT,
		gc_eShellMT,
		gc_eFaceMT,
		gc_eKeyCutMT,
		gc_eDrillMT,
		gc_eCenterDrillMT,

		gc_eSpotDrillMT,
		gc_eBoreMT,
		gc_eTapMT,
		gc_eCounterSinkMT,
		gc_eReamerMT,
		gc_eSpotFaceMT,
		gc_eFlyCutMT,

		gc_eThrdMillHalfProfMT,
		gc_eBackBoreMT,
		gc_eRigidTapMT,
		
		gc_eRoundOverMT,
		gc_e2DFormMT,
		gc_e3DFormMT,
		gc_eThrdMillFullProfMT,
		gc_eLolliMT,

		gc_eConvexTipMT,
		gc_eBarrelMT,
		gc_eDoveTailMT,
	
		gc_eInsertedMT,
		//gap for other tools??
		gc_eCustomMT = 100,

		//lathe here with large gap
		gc_e80DiaCLT = 200,
		gc_e55DiaDLT,
		gc_e35DiaVLT,
		gc_eRoundRLT,
		gc_eSquareSLT,
		gc_eTriangleTLT,
		gc_eTrigonWLT,
		gc_ePentagonPLT,
		gc_eParallel55KLT,
		gc_eRectangleLLT,
		gc_eGrooveLT,
		gc_eCutOffLT,
		gc_eThreadNLT,
		gc_eThreadLLT,
		gc_eProfileVNLT,
		gc_e2DFormLT,
		gc_e3DFormLT,
		gc_eUtilLT,
		gc_e75DiaELT,
		gc_eCustomLT = 500,
		gc_eUnsupportedTool = 999,

	};

	enum gc_teToolHolderType
	{
		gc_eNoToolHolder,
		gc_eAutomaticToolHolder,
		gc_eExtrudedPathToolHolder,
		gc_eRevolvedPathToolHolder,
		gc_eSolidToolHolder,
	};

	enum gc_teToolUnits
	{
		gc_eMetric = 0,
		gc_eInch,
		gc_eUnknownUnit
	};

	enum gc_teLHolderDef
	{
		gc_eHeadRotZero,
		gc_eToolBRot,
		gc_UndefRot,
	};

	enum gc_teDirection
	{
		gc_eCW,
		gc_eCCW,
	};

	enum gc_teMTlOrient
	{
		gc_eWest,
		gc_eNorth,
		gc_eEast,
		gc_eSouth	

	};

	enum gc_teLTlOrient
	{
		gc_eVQ1,					/* vertical tool holder, tool in quadrant 1 */
		gc_eVQ2,					/* vertical tool holder, tool in quadrant 2 */
		gc_eVQ3,					/* vertical tool holder, tool in quadrant 3 */
		gc_eVQ4,					/* vertical tool holder, tool in quadrant 4 */
		gc_eHQ1,					/* horizontal tool holder, tool in quadrant 1 */
		gc_eHQ2,					/* horizontal tool holder, tool in quadrant 2 */
		gc_eHQ3,					/* horizontal tool holder, tool in quadrant 3 */
		gc_eHQ4					/* horizontal tool holder, tool in quadrant 4 */
	};

	typedef enum
	{
		gc_eMToolHolder,	//Database
		gc_eMCustom,		//Plugin	
		gc_eMNone
	}gc_teMHolderOpt;

	enum gc_teMHolderDesc
	{
		gc_eBore_Hldr,
		gc_eCollet_Hldr,
		gc_eTGCollet_Hldr,
		gc_eDrill_Hldr,
		gc_eMill_Hldr,
		gc_eRotClamp_Hldr,		//5
		gc_eShell_Hldr,
		gc_eShrinkFit_Hldr,
		gc_eTap_Hldr,	
		gc_eNoMHolder,			//9
	};

	enum gc_LTlHolderType
	{
		gc_eTlHolder,
		gc_eBoringBar,
		gc_eNoHolder,	//this is actually other
		gc_eCustomHolder,
		gc_eNoneNoBHolder,
	};

	enum gc_teHolderDimType
	{
		gc_eDimAsHolder,
		gc_eDimAsBoringBar,
	};

	enum gc_tePrimaryCuttingDir
	{
		gc_eEastCutDir,
		gc_eSouthCutDir,
		gc_eWestCutDir,
	};

	enum gc_teLTlSize
	{
		/* no. of 1/32's is < .25, se for small english */
		gc_se1, gc_se2, gc_se3, gc_se4, gc_se5, gc_se6, gc_se7,

		/* no. of 1/8's is >= .25, le for large english */
		gc_le2, gc_le2_5, gc_le3, gc_le3_5, gc_le4, gc_le4_5, gc_le5, gc_le5_5, gc_le6, gc_le6_5, gc_le7, gc_le7_5,
		gc_le8, gc_le9, gc_le10, gc_le11, gc_le12, gc_le13, gc_le14, gc_le15, gc_le16,

		/* no. of mm */
		gc_m1, gc_m2, gc_m3, gc_m4, gc_m5, gc_m6, gc_m7, gc_m8, gc_m9, gc_m10,
		gc_m11, gc_m12, gc_m13, gc_m14, gc_m15, gc_m16, gc_m17, gc_m18, gc_m19, gc_m20,
		gc_m21, gc_m22, gc_m23, gc_m24, gc_m25, gc_m26, gc_m27, gc_m28, gc_m29, gc_m30,
		gc_m31, gc_m32, gc_m33, gc_m34, gc_m35, gc_m36, gc_m37, gc_m38, gc_m39, gc_m40,

		/* misc. size values */
		gc_misc1, gc_misc2, gc_misc3, gc_misc4, gc_misc5, gc_misc6, gc_misc7, gc_misc8, gc_misc9, gc_misc10,

		gc_undef_size = 999,
	};

}
#pragma pack(pop, boost_align)
