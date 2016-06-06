#ifndef _API_H_
#define _API_H_

#pragma pack (push, gc_api_pack, 8)	// 8 byte alignment for api structures

typedef unsigned __int64 gc_TopoId;

#ifdef INSIDE_VIRTUAL
	#define GC_API extern "C" __declspec( dllexport )
#else
	#define GC_API extern "C" __declspec( dllimport )
#endif

// ************OTHER - Need further work to split these up******************
// ********This section must be at the top of this file because*************
// ********some of these type declarations are used lower down*************** 

typedef int (*gc_tOpEventCallBack)(int, void*);
//For use with entry types ( pocket and surface processes )
enum
{	gc_eAutoPlunge,
	gc_ePlunge,
	gc_eRamp,
	gc_eHelix,
	gc_ePeripheryRamp
};

//type of ramp: for entry type
enum
{	gc_eAutoRamp,
	gc_eXRamp,
	gc_eYRamp,
	gc_eUserRamp
};

//type of helix: for entry type
enum
{	gc_eAutoEndAtSP,
	gc_eAutoCenterAtSP,
	gc_eUserEndAtSP,
	gc_eUserCenterAtSP,
	gc_eUserCenterAtXY
};

enum
{	gc_eFIRO,
	gc_eFIFO,
	gc_eTap,
	gc_eRigidTap,
	gc_ePeckFull,
	gc_ePeckChip,
	gc_eFIStopOffWallRO,
	gc_eFIStopRO,
	gc_eBackBore,
	gc_eFIStopManOut,
	gc_eFIRIFIRO,
	gc_eRIRO,
	gc_eRoughBore,
	gc_eFinishBore,
	gc_eCustomDrillCycle,
	gc_eHelixBore,
};

enum
{
	gc_eEntryExitLine = 1,		// line only
	gc_eEntryExitArc  = 2,		// line and arc
	gc_eEntryExitSame = 3,		// exit same as entry
};

enum
{	gc_eDrillTraverseCP2,
	gc_eDrillTraverseCP1
};

enum	
{	gc_eLContour,
	gc_eLRough,
	gc_eLThread,
	gc_eLDrill,
	gc_eLUtil
};

enum
{	gc_eTurnRough,
	gc_ePlungeRough,
	gc_ePatternShift
};

enum
{	gc_eOD,
	gc_eIDFront,
	gc_eIDRear,
	gc_eFaceFront,
	gc_eFaceRear
};


enum
{	gc_eForward,
	gc_eReverse,
	gc_eRevFor,										/* rough only */
	gc_eForRev										/* rough only */
};

enum
{	gc_eNoPeck,
	gc_eFullOut,
	gc_eRetractBy
};

enum
{	gc_ePTFullOut,
	gc_ePTRetract,
	gc_ePTPlunge
};

enum
{	gc_eDetailsCutType,
	gc_eConstantCutType,
};
enum
{	gc_eUN,
	gc_eUNJ,
	gc_eISO,
	gc_eNPT,
	gc_eAcme,
	gc_eSTACME,
	gc_eAPI,
	gc_ePart60,
	gc_ePart55,
	gc_eWhit55,
	gc_eBSPT,
	gc_eTR,
	gc_eRD,
	gc_eBSUN,
	gc_eAB_PFL,
	gc_eAB_PFT,
	gc_eNTF,
	gc_eNJF,
	gc_eUndStyle
};

enum
{	gc_eZMinus,
	gc_eZPlus,
	gc_eZMinusPlus,
	gc_eZPlusMinus
};

enum
{	gc_eOneTopPass,
	gc_eOneFinishPass,
	gc_eConstCut,
	gc_eConstLoad
};

enum
{
	gc_eOpMainPath,
	gc_eOpCannedPath,
	gc_eOpPatternPath,
	gc_eOpEdgePath,
	gc_eOpCustom1Path,
	gc_eOpCustom2Path,
	gc_eOpCustom3Path,
	gc_eOpCustom4Path,
	gc_eOpCustom5Path,
	gc_eOpCutPath,
	gc_eOpSavedBasePath,	// for thread mill, drill and bore ops; "base instance" of the path that must be expanded for pattern wgs (that path type is different for diff op types)
};

typedef enum 
{
	gc_eStraightWall,
	gc_eSweptWall,
	gc_eTaperWall
} gc_teWallModes;		// Process eiProcWallMode

// utility markers
typedef enum 
{
	gc_eFeedRate_UT,
	gc_eSpindleSpeed_UT,
	gc_eTlOffsetNum_UT,
	gc_eText_UT,
	gc_eCRC_UT,
	gc_eDwell_UT,
	gc_eProgramStop_UT,
	gc_eTlSubPos_UT,
	gc_eAngleMin_UT
};

// feedrate markers
enum
{
	gc_eUserFUT,
	gc_eEntryFUT,
	gc_eContourFUT,
	gc_ePercFUT
};

// Operation Syncs
enum
{	gc_eSystem_Op_Tail,
	gc_eUser_Op_Tail,
	gc_eUser_Retract_Tail,
	gc_eUser_Approach_Head,
	gc_eUser_Op_Head,
	gc_eSystem_Op_Head,
	gc_eLastSyncType,
	gc_eAnyOpHead,		// Accessor enums
	gc_eAnyOpTail,
	gc_eAnyHead,
	gc_eAnyTail
};


// Enum for Tiles 
enum
{
	gc_eTileTool,
	gc_eTileProcess,
	gc_eTileOp,
};

// Enum for Tile status
enum
{
	gc_eTileEmpty,
	gc_eTileIncomplete,
	gc_eTileComplete
};

// Enum for Display States
enum
{
	gc_eDisplayRender,
	gc_eDisplayGeom,
	gc_eDisplayDim,
	gc_eDisplaySolid,
	gc_eDisplayNoWire,
	gc_eDisplayStock,
	gc_eDisplayCS,
	gc_eDisplaySheetSide,
	gc_eDisplayCutOut,
	gc_eDisplayWrapped,
	gc_eDisplayFaceSel,
	gc_eDisplayEdgeSel,
	gc_eDisplayToolList,
	gc_eDisplayProcList,
	gc_eDisplayOpList,	
	gc_eDisplayToolHolders,
	gc_eDisplayFlashCPR,
	gc_eDisplayMachineSim,
	gc_eDisplayToolPathRender,
	gc_eDisplayPreselect,
	gc_eDisplayMulitviewManager,
	gc_eDisplayHelpOnItem,
	gc_eDisplayHoles,
	gc_eDisplayLast,
};

// limts
#define		gc_kMaxOperations		16000
#define		gc_kMaxTools			999
#define		gc_kMaxProcess			99

// pre api 1.7.5 enums


typedef enum {
	gc_esMDDName,
	gc_esMDDFile,
	gc_esMDDKey,
	gc_eiMDDVers,
	gc_eiMMDRev,
	gc_esVMMName,
	gc_esVMMVers,
	gc_esMDDPath
}gc_teMDDInfo;

typedef enum
{
	gc_eAttType3_DialogValue = 1,
	gc_eAttType3_IncValue,
	gc_eAttType3_AttValue,
	gc_eAttType3_HoleFeatValue,
	gc_eAttType3_Last,		// must be last
}gc_teAttType3Val;

typedef enum
{
	gc_eAttType2_UserVal = 1,
	gc_eAttType2_AttValue2,
	gc_eAttType2_CalcValue,
	gc_eAttType2_HoleFeatVal,
	gc_eAttType2_Last,		// must be last
}gc_teAttType2Val;

typedef enum
{
	gc_eAttSameAs_DlgValue = 1,
	gc_eAttSameAs_SameAsApproach,
	gc_eAttSameAs_AttribValue,
	gc_eAttSameAs_Last,		// must be last
}gc_teAttSameAsVal;

enum teToolInfo
{
	eiToolType,
	eiToolMaterial,
	esToolComment,
	eiToolOffset,
	eiToolSpindleDir,
	eiToolID,
	eiUseToolID,
	gc_eiToolTGPos,
	gc_eiToolGroup,
	gc_eiPrimeSpindle,
	gc_esMTlHolderString,
	gc_esToolITCSName,

	eiMToolType = 100,
	eiMToolFlutes,
	efMToolLength,
	efMToolFLength,
	efMToolRadius,
	efMToolShankRad,
	efMToolTopCornRad,
	efMToolCornRad,
	efMToolDraft,
	efMToolNCDiam,
	efMToolTipAngle,
	efMToolPitchTPI,
	efMToolPreset,				// a 2d value, in ZX of tool's "orientation wp"
	efMToolTCShift,				// a 2d value, in ZX of tool's "orientation wp"
	eiMToolCRCOffset,
	eiMToolOrient,
	efMToolLeadTip,
	efMToolTipRad,
	gc_eiMToolLenOffset,
	eiMToolOptions,
	efMToolInnerTopCornRad,
	efMToolBtmRad,
	efMToolTopRad,
	gc_efMToolLengthNShank,		//useful ONLY for RETREIVING full length for Roundover tool. 
								/*Lollipop Tools:  
									efMToolRadius for the Nose Radius
									efMToolFLength for the Nose Length
								*/
	gc_efMToolNeckRad,			//only applies to Lollipop tools for now 7/11/2007
	gc_efMToolShankLen,			//only applies to Lollipop tools for now 7/11/2007
	gc_eiMTlHolderType,
	gc_eiMToolType,

	eiLToolType = 200,
	eiLToolSize,
	efLToolSize,
	efLToolThick,
	efLToolLength,
	efLToolTipRad,
	efLToolInsertAngle,
	efLToolTipOffset,
	efLToolPresetPt,			// a 2d value, in ZX of tool's "orientation wp"
	efLToolTCShift,				// a 2d value, in ZX of tool's "orientation wp"
	eiLToolOrient,
	eiLToolHolder,
	efLToolFaceAngle,
	efLToolSideAngle,
	efLToolTipWidth,
	efLToolTipLength,
	eiLToolThreadStyle,
	eiLToolThreadType,
	eiLToolThreadIDOD,
	eiLToolThreadDir,
	efLToolThreadPitch,
	efLToolThreadFlatLen,
	efLToolThreadInsertWidth,
	efLToolThreadEdgePos,
	efLToolMidAngle,
	efLToolTipCenterToPreset,
	efLToolFaceRelief,
	efLToolDiamRelief,
	gc_eiLToolOffset,
	efLToolHolderThickness,
	gc_eiLCutSide,
	gc_eiLToolFaceUp,
	gc_efLToolBAxis,
	gc_efLToolUtilLength,
	gc_efLToolUtilDiam,
	gc_efLToolUtilAngle,
	gc_eiNegSideTool,
	eiLToolOther,
	eiMToolHolderOpt,
	eiMTOutOfHolderLen,
	efToolPresetPt,				// a 3d value, all tool types, in XYZ of tool's "orientation wp"
	efToolTCShift,				// a 3d value, all tool types, in XYZ of tool's "orientation wp"
	gc_eiUseToolSubPos,
	gc_efToolSubPos,
	gc_efLToolNotchRamp,
	gc_efLTlIncAngle,
	gc_eiLHldrAdaptBlock,
	gc_eiLHldrAttachType,
	gc_efLHldrShank,
	gc_efLHldrFDim,
	gc_efLToolStickout,
	gc_eiToolNonStdAttach,
	gc_efLToolTipCenterDefXY,
	gc_eiLToolHasAltPreset,
	gc_efLToolCenterToAltPresetXY,
	gc_efLToolHolderLength,
	gc_efMToolHolderGageLen,
	gc_efMToolHolderMaxDia,
	gc_efMToolHolderFrontLen,
};

typedef enum {						// teOpInfo
	esOpCommentShort,
	eiOpTool,
	eiOpProcGroup,
	eiOpProcID,
	eiOpProcOp,
	eiOpWG,
	eiOpCS,
	eiOpPathCS,
	eiOpLocks,
	eiOpType,						// mill or lathe operation
	eiMOpType,						// mill operation type (drill, contour, rough, surface, thread mill)
	eiLOpType,						// lathe operation type (drill, contour, rough, threading)
	efOpEntryClr,
	efOpExitClr,
	eiOpRepeats,
	eiOpCrc,
	eiOpCrcOffset,
	eiOpTlOffset,
	eiOpCoolant,
	efOpEntryFeed,
	efOpContourFeed,
	efOpCutWidth,
	efOpStock,
	efOpBossStock,
	efOpRpms,
	efOpTime,
	efOpLength,
	esOpUtilStartShort,
	esOpUtilEndShort,
	eiOpCutType,						// 0 = Climb, 1 = conventionnal, 2 = no cut side
	eiOpCSS,
	efOpCSS,
	efOpSurfStock,
	efOpLatheXZStock,
	efOpLatheCutWidth,
	efOpCutTol,
	efOpStep,
	efOpDepth,
	efOpODIDFace,
	efLOpDepth,
	gc_eiOpCRCSide,
	gc_eiOpDrillType,
	gc_eiOpDrillClrPlane,
	gc_efOpDrillClrPlane,
	gc_eiOpDrillPosApproach,
	gc_efOpDrillDwell,
	gc_efOpDrillTapPercent,
	gc_efOpDrillPeckClearance,			//For "full out" peck: Incremental distance
	gc_efOpDrillPeckAmount,
	gc_efOpDrillPeckRetract,			//For "chip break" peck: Incremental "back off" amount
	gc_efOpDrillBorePullOff,
	gc_efOpDrillCBStartRIZ,
	gc_efOpDrillCBEndRIZ,
	gc_efOpSurfaceD,
	gc_eiOpMatrlOnly,
	gc_efOpMatrlOnlyClrnce,
	gc_eiOpRapidIn,
	gc_efLOpThrdAngle,
	gc_eiLOpThrdBalanced,
	gc_eiLOpThrdAngleAlternate,
	gc_efLOpThrdNominalXd,
	gc_efLOpThrdTPI,
	gc_efLOpThrdPitch,
	gc_efLOpThrdSlope,
	gc_eiLOpThrdStarts,
	gc_efLOpThrdMinorXd,
	gc_efLOpThrdHtXr,
	gc_efLOpThrdRunIn,
	gc_efLOpThrdRunOut,
	gc_efLOpThrdFirstCutD,
	gc_efLOpThrdLastCut,
	gc_eiLOpThrdLastCut,
	gc_eiLOpPrefCanned,
	gc_eiLOpCannedAutoFin,
	gc_eiLOpThrdType,
	gc_eiLOpCutDir,
	gc_eiOpSpringPasses,
	gc_eiLOpRoughType,
	gc_eiLOpPullOffWall,
	gc_eiLOpPlungeCutType,
	gc_eiLOpPlungeCenterOut,
	gc_eiLOpPlungeType,
	gc_efLOpPlungeMaxCut,
	gc_efLOpPlungeAngle,
	gc_efLOpPlungePeckAmt,
	gc_efLOpPlungePeckClearance,
	gc_efLOpPlungePeckRetract,
	gc_efLOpPlungeFeedPrc,
	gc_eiLOpPlungeEntryType,
	gc_efLOpPatShftCut,
	gc_efLOpPatShftSrtPt,
	gc_eiLOpPatShftFixedSrt,
	gc_eiLOpPatShftPasses,
	gc_eiLOpSqrCorners,
	gc_eiLOpNoDrag,
	gc_eiLOpCutOff,
	gc_eiOpODIDFace,
	gc_eiOpWrap,
	gc_efOpWrapStartAngle,
	gc_efOpWrapDupAngle,
	gc_eiOpWrapDups,
	gc_eiOPProgStop,
	gc_eiOpPocketType,
	gc_efLOpMaxRPM,
	gc_eiOpToolGroup = 200, // Changes to 5.5&5.8 should go before this line
	gc_eiOpWorkpiece,
	gc_efLOpSubOnZ,			// obsolete
	gc_efLOpSubOnClearance,	// obsolete
	gc_efLOpSubOffZ,		// obsolete
	gc_eiOpFlow,
	gc_eiOpSpinCtrl,
	gc_eiLOpCutOtherSide,

	//Pocket Entry Info
	gc_eiOpPockEntryRampType,	// 0 = AutoPlunge, 1 = Plunge, 2 = Ramp, 3 = Helix, 4 = Periphery Ramp
	gc_eiOpPockEntryHelixType,
	gc_efOpPockEntryPlungePt,
	gc_efOpPockEntryRampSlope,
	gc_efOpPockEntryRampStartZ,
	gc_efOpPockEntryRampMaxCut,
	gc_efOpPockEntryRampWallClear,
	gc_efOpPockEntryRampAngle,
	gc_efOpPockEntryHelixSlope,
	gc_efOpPockEntryHelixAngle,
	gc_efOpPockEntryHelixStartZ,
	gc_efOpPockEntryHelixMaxCut,
	gc_efOpPockEntryHelixWallClear,
	gc_efOpPockEntryHelixDiameter,
	gc_efOpPockEntryHelixCP,
	gc_efOpPockEntryPeriphStartZ,
	gc_efOpPockEntryPeriphSlope,	
	
	//Surface Entry Info
	gc_eiOpSurfEntryType,	// 1 = Plunge, 2 = Ramp...others will return -1
	gc_eiOpSurfEntryRampType,

	gc_efOpSurfEntryPlungePt,
	gc_eiOpMachEngine,

	gc_efOpRapidClearance,

	// AT 2/5/03
	efOpEntryLine,
	efOpExitLine,
	efOpEntryRad,
	efOpExitRad,

	efOpZStepWanted,
	efOpOverhang,
	efOpOverlap,
	efOpOpenClearance,

	// Thread Milling Op ----------------------
	efOpMThStartThread,
	efOpMThEndThread,
	efOpMThCutDia,
	efOpMThClearDia,
	efOpMThPitch,
	efOpMThFeed,

	// surface Op -----------------------------
	efOpSStepOver,
	efOpSRidgeHeight,
	efOpSCutAngle,
	efOpSZDesired,
	efOpSConstFacesClear,
	efOpSStockTol,
	efOpSFixTol,
	efOpSConstraintTol,
	efOpSSmoothTol,
	efOpSArcFitTol,
	efOpSSplineApproxTol,
	efOpSNormalAngle,
	efOpSStepCutRatio,
	efOpSCornerRad,
	efOpSMaxCutAngle,

	// Pocket/Contour Op ----------------------
	eiOpFeedConnect,
	eiOpCRCOffset,
	eiOpPatternOn,
	eiOpPatternIdx,
	eiOpRoundCorners,
	eiOpEntryPerp,
	eiOpExitPerp,
	eiOpIgnoreTools,
	eiOpDepthFirst,
	eiOpFMUseShape,
	eiOpFMHPlus,
	eiOpFMVPlus,
	eiOpFMMoveH,
	eiOpB4ZigZag,
	eiOpBackNForth,
	eiOpFMType,
	eiOpEntryType,
	eiOpStartOnRight,
	eiOpRetracts,
	eiOpHitParallel,
	eiOpStayClear,
	eiOpCutBack,
	eiOpSameStroke,
	eiOpFullDiameter,
	eiOpStepOverFeedLock,
	eiOpClearFeedLock,
	eiOpScallopFeedLock,
	eiOpClearPeriph,
	eiOpHitFlats,
	efOpCP1,
	efOpCurveTolerance,
	efOpAutoEntryCP,
	efOpAutoEntryClrRad,
	efOpAutoExitCP,
	efOpAutoExitClrRad,
	efOpGeoRad,
	efOpMinRad,
	efOpZStep,
	efOpFMClear,
	efOpFMCutWidth,
	efOpCutAngle,
	efOpStepOverFeed,
	efOpClearFeed,
	efOpScalloFeed,
	efOpMinCut,
	efOpPastStock,

	// Thread Milling process ----------------------
	eiOpMThTraverseCP1,
	eiOpMThIDOD,
	eiOpMThThreadDir,
	// surface op -----------------------------
	eiOpSType,
	eiOpSCutType,
	eiOpSBackNForth,
	eiOpSLaceCutDir,
	eiOpSOutputPref,
	// Lace Cut info. ------------------------------
	eiOpSCutOpt,
	eiOpSOffstSurfs,
	eiOpSOnePass,
	eiOpSCostrain,
	eiOpSRetOpt,
	eiOpSStayInStock,
	eiOpSClearStock,
	eiOpSClearStockType,
	eiOpSCutOverEdges,
	eiOpSSkipFlats,
	// 2 Curve Flow info. --------------------------
	eiOpSCurveCutDir,
	// Surface Flow info. --------------------------
	eiOpSFlowMachDir,
	eiOpSFlowMachZOrder,
	eiOpSTravelAroundMode,
	eiOpSFlowCutType,
	// Intersection info. --------------------------
	eiOpSIntersectType,
	eiOpSCutsType,
	eiOpSPassesType,
	eiOpSCleanUpFrom,
	eiOpSPassesPerSide,

	// Lathe Rough op -------------------------
	eiOpLRghRoundCorners,
	eiOpLRghExitPerp,
	eiOpLRghXPlusAxis,
	eiOpLRghXMinusAxis,
	eiOpLRghZPlusAxis,
	eiOpLRghZMinusAxis,
	eiOpLRghAutoFinish,
	eiOpLRghSpindleDir,
	eiOpLRghConstPath,

	// Lathe Thread op --------------------------
	eiOpLThStyle,
	eiOpLThAlternate,
	eiOpLThNomPitchIndex,
	efOpLThZStart,
	efOpLThZEnd,
	efOpLThMajorDiam,
	efOpLSurfaceZ,

	// Lathe Rough Op ----------------------------
	efOpLRghMinRad,
	efOpLRghEntryLine,
	efOpLRghEntryRad,
	efOpLRghExitRad,
	efOpLRghExitLine,
	efOpLRghRoughStart,
	efOpLRghTurnCutWidth,
	efOpLRghRampAngle,

	// Contour and Pocket Wall -------------------
	gc_eiOpWallStep,
	gc_eiOpWallTop2Bot,
	gc_eiOpWallSameDir,
	gc_eiOpWallDcepSide,
	gc_eiOpWallSweptPoc,
	gc_eiOpWallSweptIslnd,
	gc_eiOpCutSide,
	gc_efOpWallTop,
	gc_efOpWallAng,
	gc_efOpWallBot,
	gc_efOpWalliTop,
	gc_efOpWalliAng,
	gc_efOpWalliBot,
	gc_efOpWalluserStep,
	gc_efOpWallshapeStep,
	gc_efOpWallridgeHght,
	
	gc_efOpDrillClrPlaneLocCS,

	gc_eiOpSUseAdvTol,
	gc_eiOpMUseAdvTol,
	gc_efOpMSurfClear,
	gc_efOpMStockTol,
	gc_efOpMFixtureTol,

	gc_efOpMZShift,
	gc_eiOpWallMode,

	gc_eInterOpOverride,

	gc_eiOpUtilType,
	gc_eiOpMDFromTool,
	gc_eiOpMDVaryWithGeo,
	gc_eiOpMDVaryWithFeat,
	gc_eiOpMDRetractLvl,

	//Contour Entry Info
	gc_eiOpContourEntryRampType,
	gc_eiOpContourEntryHelixType,
	gc_efOpContourEntryRampSlope,
	gc_efOpContourEntryRampStartZ,
	gc_efOpContourEntryRampMaxCut,
	gc_efOpContourEntryRampAngle,
	gc_efOpContourEntryHelixSlope,
	gc_efOpContourEntryHelixStartZ,
	gc_efOpContourEntryHelixMaxCut,
	gc_efOpContourEntryHelixDiameter,
	gc_eiOpPreferSubs,

	// Advanced Entry Exit
	gc_eiOpExitSameAsEntry,
	gc_eiOpAdvancedEntryType,
	gc_eiOpAdvancedExitType,

	gc_eiOpAdvLineEntryIsCRC,
	gc_eiOpAdvLineEntryIsOffPartLine,
	gc_efOpAdvLineEntryOffPartLine,
	gc_efOpAdvLineEntryOffPartAngle,
	gc_efOpAdvLineEntryOffPartDistance,
	gc_eiOpAdvLineEntryIsRamp,
	gc_efOpAdvLineEntryRamp,
	gc_eiOpAdvLineEntryRampIncludeLine,

	gc_eiOpAdvLineExitIsCRC,
	gc_eiOpAdvLineExitIsOffPartLine,
	gc_efOpAdvLineExitOffPartLine,
	gc_efOpAdvLineExitOffPartAngle,
	gc_efOpAdvLineExitOffPartDistance,
	gc_eiOpAdvLineExitIsRamp,
	gc_efOpAdvLineExitRamp,
	gc_eiOpAdvLineExitRampIncludeLine,

	gc_eiOpAdvArcEntryIsCRC,
	gc_eiOpAdvArcEntryIsOffPartLine,
	gc_efOpAdvArcEntryOffPartLine,
	gc_efOpAdvArcEntryOffPartDistance,
	gc_eiOpAdvArcEntryIsRamp,
	gc_efOpAdvArcEntryRamp,
	gc_eiOpAdvArcEntryRampIncludeRadius,

	gc_eiOpAdvArcExitIsCRC,
	gc_eiOpAdvArcExitIsOffPartLine,
	gc_efOpAdvArcExitOffPartLine,
	gc_efOpAdvArcExitOffPartDistance,
	gc_eiOpAdvArcExitIsRamp,
	gc_efOpAdvArcExitRamp,
	gc_eiOpAdvArcExitRampIncludeRadius,

	efOpSFixClear,
	
	// More...Lathe Rough Op ----------------------------
	efOpLRghFeed,
	efOpLRghEntryFeed,
	efOpLRghContourFeed,	// same as efOpLRghFeed

	eiOpDrillReverseOrder,

	// Drill Bore Options
	gc_efOpDrillBoreCutDia,			// mop_d_cutdia
	gc_efOpDrillBoreClearDia,		// mop_d_cleardia
	gc_efOpDrillBoreClearAmount,	// mop_d_appr_clear
	gc_efOpDrillBoreEntryExitRad,	// mop_d_ee_rad
	gc_efOpDrillBoreEntryExitLine,	// mop_d_min_move
	gc_efOpDrillBoreCutWidth,		// mop_d_cutwidth
	gc_efOpDrillBoreStock,			// mop_d_stock
	gc_efOpDrillBoreOverlap,		// mop_d_overlap
	gc_efOpDrillBoreApproachAngle,	// mop_d_appr_ang
	gc_efOpDrillBoreDesStep,		// mop_d_des_step
	gc_eiOpDrillBoreCutType,		// mop_d_cuttype
	
	// Lathe Contour Variable B-Axis
	gc_eiOpVaryBAxisUsed,
	gc_eiOpVaryBAxisMethod,
	gc_eiOpVaryBAxisMultiTrans,
	gc_eiOpVaryBAxisUseMinAngle,
	gc_efOpVaryBAxisMinAngle,
	gc_eiOpVaryBAxisUseMaxAngle,
	gc_efOpVaryBAxisMaxAngle,
	gc_eiOpVaryBAxisSmoothCorners,
	gc_efOpVaryBAxisLeadLagAngle,
	gc_eiOpVaryBAxisVectorType,
	gc_eiOpVaryBAxisCheckCollisions,
	gc_efOpVaryBAxisCollisionClearance,

	gc_eiOpMStayInStock,			// mop_m_useStock

	// For Thread from shape (Contour Threading)
	gc_eiOpLThrdMethod,
	gc_efOpLThrdXrShift,

	//for Mill Feature Depth
	gc_efOpMillFeat_IncToolDepth,
	gc_efOpMillFeat_IncFeatDepth,
	gc_efOpMillFeat_AbsFeatDepth,
	gc_efOpMillFeat_IncApproachZ,

	gc_ewsOpMillFeat_ApproachZ,
	gc_ewsOpMillFeat_RetractZ,
	gc_ewsOpMillFeat_TopSurfZ,
	gc_ewsOpMillFeat_FeatZ,
	gc_ewsOpMillFeat_MachCS,

	gc_eiOpMillFeat_DepthFromFeat,
	gc_eiOpMillFeat_ApproachZType3,
	gc_eiOpMillFeat_RetractZType,
	gc_eiOpMillFeat_FeatZType2,
	gc_eiOpMillFeat_TopSurfZType2,
	gc_eiOpMillFeat_MachCSType2,

	// HelixBore
	gc_eiOpDrillUseCircleDia,
	gc_eiOpDrillRapidIn,
	gc_eiOpDrillSpiralUp,
	gc_efOpDrillSpiralAng,

	// Bore entry/exit
	gc_eiOpDrillEntryType,
	gc_efOpDrillEntryArcLine,
	gc_efOpDrillEntryArcRad,
	gc_efOpDrillEntryLineLine,
	gc_eiOpDrillEntryCenter,
	gc_eiOpDrillExitType,
	gc_efOpDrillExitArcLine,
	gc_efOpDrillExitArcRad,
	gc_efOpDrillExitLineLine,
	gc_eiOpDrillExitCenter,

	// does the op contain an expanded longhand path
	gc_eiOpDrillExpanded,

	// new contouring options
	gc_eiOpRampContouring,		// for ramp down
	gc_eiOpExtraOffset,			// for multiple passes contouring
	gc_efOpExtraStepover,		// for multiple passes contouring

	// pocketing
	gc_eiOpOutermostAsBoss,

	gc_eiOpCommentLength,
	gc_eiOpUtilStartLength,
	gc_eiOpUtilEndLength,
	gc_efLOpThrdPitchMM,

	// Drill Hole Feature Options
	gc_eiOpDrillHoleSurfZ,			// mop_d_start_depthtype
	gc_eiOpDrillHoleDepthZ,			// mop_d_end_depthtype
	gc_eiOpDrillHoleSurfSegment,	// mop_d_start_seg_num
	gc_eiOpDrillHoleDepthSegment,	// mop_d_end_seg_num
	gc_eiOpDrillHoleAdjustToolTip,	// mop_d_adjust_tool_tip
	gc_efOpDrillHoleAdjustTipDelta,	// mop_d_adjust_tip_delta

	gc_eiOpDrillHoleSegmentMatch,	// mop_d_seg_match
	gc_eiOpDrillHoleSegMatchLen,	// mop_d_seg_prop_length
	gc_eiOpDrillHoleSegMatchDia,	// mop_d_seg_prop_dia
	gc_eiOpDrillHoleSegMatchTaper,	// mop_d_seg_prop_taper
	gc_eiOpDrillHoleSegMatchMethod,	// mop_d_seg_prop_method
	esOpComment,						//full length op comment - check the size first and allocate accordingly 
	gc_esOpCoolant,
	esOpUtilStart,
	esOpUtilEnd,

	// does the op use a tool
	gc_eiOpAllowTool,
}
teOpInfo;

typedef enum {						// teProcInfo
	efProcEntryClr,
	efProcExitClr,
	efProcEntryLine,
	efProcExitLine,
	efProcEntryRad,
	efProcExitRad,
	efProcEntryFeed,
	efProcContourFeed,
	efProcSurfZ,
	efProcTipZ,
	efProcZStepWanted,
	efProcCutWidth,
	efProcStock,
	efProcBossStock,
	efProcOverhang,
	efProcOverlap,
	efProcOpenClearance,
	eiProcSpringPasses,
	eiProcCutType,					// 0 = Climb, 1 = conventionnal, 2 = no cut side
	eiProcRepeats,
	eiProcTool,

	// Thread Milling process ----------------------
	eiProcMThTraverseCP1,
	eiProcMThIDOD,
	eiProcMThThreadDir,
	efProcMThStartThread,
	efProcMThEndThread,
	efProcMThCutDia,
	efProcMThClearDia,
	efProcMThPitch,
	efProcMThFeed,
	eiProcMThRapidIn,

	// surface process -----------------------------
	eiProcSType,
	efProcSEFeed,
	efProcSCFeed,
	efProcSStock,
	efProcSFixClear,
	eiProcSCutType, 
	efProcSStepOver,
	efProcSRidgeHeight,
	efProcSCutAngle,
	eiProcSBackNForth,
	efProcSZDesired,
	eiProcSLaceCutDir,
	efProcSConstFacesClear,
	efProcSCuttingTol,
	efProcSStockTol,
	efProcSFixTol,
	efProcSConstraintTol,
	eiProcSOutputPref,
	efProcSSmoothTol,
	efProcSArcFitTol,
	efProcSSplineApproxTol,

	// Lace Cut info. ------------------------------
		eiProcSCutOpt,
		eiProcSOffstSurfs,
		eiProcSOnePass,
		eiProcSCostrain,
		efProcSNormalAngle,
		eiProcSRetOpt,
		efProcSStepCutRatio,
		eiProcSStayInStock,
		eiProcSClearStock,
		eiProcSClearStockType,
		eiProcSCutOverEdges,
		eiProcSSkipFlats,

	// 2 Curve Flow info. --------------------------
		eiProcSCurveCutDir,

	// Surface Flow info. --------------------------
		eiProcSFlowMachDir,
		eiProcSFlowMachZOrder,
		eiProcSTravelAroundMode,
		eiProcSFlowCutType,

	// Intersection info. --------------------------
		eiProcSIntersectType,
		eiProcSCutsType,
		eiProcSPassesType,
		eiProcSCleanUpFrom,
		efProcSCornerRad,
		eiProcSPassesPerSide,
		efProcSMaxCutAngle,

	// Lathe process -------------------------------
	eiProcLPrefCanned,
	eiProcLClearID,

	// Lathe Rough process -------------------------
		eiProcLRghRoundCorners,
		eiProcLRghCutOff,
		eiProcLRghCutDir,
		efProcLRghMinRad,
		efProcLRghStock,
		efProcLRghStockX,
		efProcLRghStockZ,
		eiProcLRghEntryPerp,
		eiProcLRghExitPerp,
		efProcLRghEntryLine,
		efProcLRghEntryRad,
		efProcLRghExitRad,
		efProcLRghExitLine,
		efProcLRghRoughStart,
		eiProcLRghRoughType,
		eiProcLRghCSS,
		efProcLRghMaxRPMs,
		efProcLRghSFPM,
		efProcLRghFeed,
		eiProcLRghRapidStep,
		eiProcLRghMonotonic,
		eiProcLRghAvoidAir,
		efProcLRghClearance,
		eiProcLRghXPlusAxis,
		eiProcLRghXMinusAxis,
		eiProcLRghZPlusAxis,
		eiProcLRghZMinusAxis,
		eiProcLRghAutoFinish,
		eiProcLRghSpindleDir,

			efProcLRghTurnCutWidth,
			efProcLRghRampAngle,
			eiProcLRghFinishLast,

			eiProcLRghCenterOut,
			eiProcLRghConstStep,
			eiProcLRghPeck,
			efProcLRghPlungeAngle,
			efProcLRghPlungeCutWidth,
			efProcLRghFeedPct,
			efProcLRghPeck,
			efProcLRghRetract,
			eiProcLRghPlungeType,

			eiProcLRghConstPath,
			eiProcLRghFixedSP,
			efProcLRghCutX,
			efProcLRghCutZ,
			efProcLRghShiftCutWidth,
			efProcLRghCycleSP,

			eiProcLRghPasses,

	// Lathe Thread process ------------------------
		eiProcLThStyle,
		eiProcLThCutDir,
		eiProcLThCutType,
		eiProcLThCSS,
		eiProcLThBalancedInFeed,
		eiProcLThAlternate,
		eiProcLThLastCut,
		efProcLTh_Unused,
		efProcLThRPM,
		efProcLThZStart,
		efProcLThZEnd,
		eiProcLThNomPitchIndex,
		efProcLThNominal,
		efProcLThPitch,
		efProcLThMajorDiam,
		efProcLThMinorDiam,
		efProcLThThrdHeight,
		eiProcLThTaperIndex,
		efProcLThTaper,
		efProcLThThrdAngle,
		efProcLThCutDepth,
		efProcLThLastCut,
		eiProcLThSpring,
		eiProcLThStarts,
		efProcLThZStartExt,
		efProcLThZEndExt,
		efProcLThXStartExt,
		efProcLThXEndExt,

	// Lathe Drill process -------------------------
		eiProcLDrillEntry,
		efProcLDwell,
		efProcLPeck,
		efProcLClearance,
		efProcLRetract,
		efProcLTapPercent,
		efProcLFeed,
		efProcLTipZ,
		efProcLSurfaceZ,

	// Pocket/Contour process ----------------------
	eiProcFeedConnect,// op_fdcon
	eiProcCRCOffset,// op_crcoffset
	eiProcTLOffset,// op_tloffset
	efProcToolChange, // op_toolchg
	efProcCP1,// op_cp1
	efProcCurveTolerance,// op_curvetol
	efProcAutoEntryCP,// op_autoncp
	efProcAutoEntryClrRad,// op_autonclrrad
	efProcAutoExitCP,// op_autoxcp
	efProcAutoExitClrRad,// op_autoxclrrad
	eiProcCustomCBSet,// op_custom_cb_set

	eiProcPatternOn,// mop_pattOn
	eiProcPatternIdx,// mop_pattWGidx
	efProcAxisInfo,// mop_axisinfo
	efProcGeoRad,// mop_geodepth
	eiProcRoundCorners,// mop_m_rndcorn
	efProcMinRad,// mop_m_minrad
	eiProcEntryPerp,// mop_m_entryperp
	eiProcExitPerp,// mop_m_exitperp
	efProcZStep,// mop_m_zstep
	eiProcIgnoreTools,// mop_m_ignoretools
	eiProcDepthFirst,// mop_m_depfirst
	eiProcFMUseShape,// mop_m_fm_useshape
	eiProcFMHPlus,// mop_m_fm_hplus
	eiProcFMVPlus,// mop_m_fm_vplus
	eiProcFMMoveH,// mop_m_fm_moveh
	eiProcB4ZigZag,// mop_m_beforezigzag
	eiProcBackNForth,// mop_m_backNforth
	eiProcFMType,// mop_m_fm_type
	efProcFMClear,// mop_m_fm_clear
	efProcFMCutWidth,// mop_m_fm_cutwidth
	eiProcEntryType,// mop_m_entrytype
	efProcCutAngle,// mop_m_cutangle

	eiProcStartOnRight,// mop_m_onright
	eiProcRetracts,// mop_m_zigzagretract
	eiProcHitParallel,// mop_m_hitparal
	eiProcStayClear,// mop_m_stayclear
	eiProcCutBack,// mop_m_cutback
	eiProcSameStroke,// mop_m_samestroke
	eiProcFullDiameter,// mop_m_fulldiam
	eiProcStepOverFeedLock,// mop_m_overlock
	eiProcClearFeedLock,// mop_m_clearlock
	eiProcScallopFeedLock,// mop_m_scalloplock
	eiProcClearPeriph,// mop_m_clearperiph
	efProcStepOverFeed,// mop_m_stepoverfeed
	efProcClearFeed,// mop_m_clearfeed
	efProcScalloFeed,// mop_m_scallopfeed
	efProcMinCut,// mop_m_mincut

	eiProcOpCS,		// op coordinate system
	eiProcPathCS,	// path coordinate system

	efProcRpms,		// op speed
	efProcDrillFeed, // feedrate for drilling
	eiProcPocketType, //mop_m_pocType
	eiProcWallMode,   // mop_wall_mode
	eiProcPreferSubs, // mop_m_sub
	efProcPastStock,  // mop_maxair
	eiProcHitFlats,
	eiProcCrc,
	eiProcCoolant,
	
	//Pocket Entry Info
	eiProcPockEntryRampType,	// 0 = AutoPlunge, 1 = Plunge, 2 = Ramp, 3 = Helix, 4 = Periphery Ramp
	eiProcPockEntryHelixType,
	efProcPockEntryPlungePt,
	efProcPockEntryRampSlope,
	efProcPockEntryRampStartZ,
	efProcPockEntryRampMaxCut,
	efProcPockEntryRampWallClear,
	efProcPockEntryRampAngle,
	efProcPockEntryHelixSlope,
	efProcPockEntryHelixAngle,
	efProcPockEntryHelixStartZ,
	efProcPockEntryHelixMaxCut,
	efProcPockEntryHelixWallClear,
	efProcPockEntryHelixDiameter,
	efProcPockEntryHelixCP,
	efProcPockEntryPeriphStartZ,
	efProcPockEntryPeriphSlope,	
	
	//Surface Entry Info
	eiProcSurfEntryType,	// 1 = Plunge, 2 = Ramp...others will return -1
	eiProcSurfEntryRampType,

	efProcSurfEntryPlungePt,
	eiProcType,				//Process Type, Mill, Lathe
	eiMProcType,			//Mill Process Type, Drill, Contour, Rough, Surface, Threading
	eiLProcType,			//Lathe Process Type, Drill, Contour, Rough
	
	efProcRapidClearance,

	gc_eiProcProgStop,
	gc_eiProcRapidIn,
	gc_eiProcMatrlOnly,
	gc_eiProcDrillType,
	gc_eiProcDrillPosApproach,
	gc_eiProcDrillClrPlane,
	efProcSurfStock,
	gc_efProcDrillDwell,
	gc_efProcDrillPeckAmount,
	gc_efProcDrillPeckClearance,
	gc_efProcDrillTapPercent,
	gc_efProcDrillBorePullOff, 
	gc_efProcDrillPeckRetract,

// AT 1/23/03

	gc_eiProcWallStep,        //mop_wall_step
	gc_eiProcWallTop2Bot,
	gc_eiProcWallSameDir,
	gc_eiProcWallDcepSide,
	gc_eiProcWallSweptPoc,
	gc_eiProcWallSweptIslnd,
	gc_efProcWallTop,
	gc_efProcWallAng,
	gc_efProcWallBot,
	gc_efProcWalliTop,
	gc_efProcWalliAng,
	gc_efProcWalliBot,
	gc_efProcWalluserStep,
	gc_efProcWallshapeStep,
	gc_efProcWallridgeHght,
	
	gc_eiProcSUseAdvTol,
	gc_eiProcMUseAdvTol,
	gc_efProcMSurfClear,
	gc_efProcMStockTol,
	gc_efProcMFixtureTol,
	gc_eiProcCutSide,
	gc_efProcMZShift,
	gc_eiProcMDFromTool,
	gc_eiProcMDVaryWithGeo,
	gc_eiProcMDVaryWithFeat,
	gc_eiProcMDRetractLvl,
	gc_eiProcMDPressLoadH1ZFeat,
	
	//Contour Entry Info
	gc_eiProcContourEntryRampType,
	gc_eiProcContourEntryHelixType,
	gc_efProcContourEntryRampSlope,
	gc_efProcContourEntryRampStartZ,
	gc_efProcContourEntryRampMaxCut,
	gc_efProcContourEntryRampAngle,
	gc_efProcContourEntryHelixSlope,
	gc_efProcContourEntryHelixStartZ,
	gc_efProcContourEntryHelixMaxCut,
	gc_efProcContourEntryHelixDiameter,

	gc_eiProcODIDFace,

	// Advanced Entry Exit
	gc_eiProcExitSameAsEntry,
	gc_eiProcAdvancedEntryType,
	gc_eiProcAdvancedExitType,

	gc_eiProcAdvLineEntryIsCRC,
	gc_eiProcAdvLineEntryIsOffPartLine,
	gc_efProcAdvLineEntryOffPartLine,
	gc_efProcAdvLineEntryOffPartAngle,
	gc_efProcAdvLineEntryOffPartDistance,
	gc_eiProcAdvLineEntryIsRamp,
	gc_efProcAdvLineEntryRamp,
	gc_eiProcAdvLineEntryRampIncludeLine,

	gc_eiProcAdvLineExitIsCRC,
	gc_eiProcAdvLineExitIsOffPartLine,
	gc_efProcAdvLineExitOffPartLine,
	gc_efProcAdvLineExitOffPartAngle,
	gc_efProcAdvLineExitOffPartDistance,
	gc_eiProcAdvLineExitIsRamp,
	gc_efProcAdvLineExitRamp,
	gc_eiProcAdvLineExitRampIncludeLine,

	gc_eiProcAdvArcEntryIsCRC,
	gc_eiProcAdvArcEntryIsOffPartLine,
	gc_efProcAdvArcEntryOffPartLine,
	gc_efProcAdvArcEntryOffPartDistance,
	gc_eiProcAdvArcEntryIsRamp,
	gc_efProcAdvArcEntryRamp,
	gc_eiProcAdvArcEntryRampIncludeRadius,

	gc_eiProcAdvArcExitIsCRC,
	gc_eiProcAdvArcExitIsOffPartLine,
	gc_efProcAdvArcExitOffPartLine,
	gc_efProcAdvArcExitOffPartDistance,
	gc_eiProcAdvArcExitIsRamp,
	gc_efProcAdvArcExitRamp,
	gc_eiProcAdvArcExitRampIncludeRadius,

	gc_eiProcWrap,
	gc_efProcWrapStartAngle,
	gc_efProcWrapDupAngle,
	gc_eiProcWrapDups,
	gc_eiProcID,		//read only field
	
	// More Lathe Rough Process
	efProcLRghEntryFeed,
	efProcLRghContourFeed, // same as efProcLRghEntryFeed
	efProcLRghAutoFinishFeed,
	eiProcLRghCleanUpPass,
	eiProcLUsesDeflectComp,
	eiProcLRghDeflectComp,
	eiProcLRghMultiPass,
	
	// More Lathe Process
	eiProcLCutOtherSide,
	eiProcLUseAutoClear,
	
	// More Advanced Entry Exit
	gc_efProcAdvLineEntryCRC,
	gc_efProcAdvLineExitCRC,
	gc_efProcAdvArcEntryCRC,
	gc_efProcAdvArcEntryRadius,
	gc_efProcAdvArcExitCRC,
	gc_efProcAdvArcExitRadius,

	// More Lathe Roughing Process
	gc_efProcLRghEndLimit,
	gc_efProcLRghUseEndLimit,

	eiProcDrillReverseOrder,

	gc_efProcLRghStartSideExt,
	gc_eiProcLRghTurnPullOffWall,
	gc_efProcLRghOffsetCutDepth,
	gc_eiProcLRghShiftSqrCorners,

	// Drill Bore Options
	gc_efProcDrillBoreCutDia,			// mop_d_cutdia
	gc_efProcDrillBoreClearDia,			// mop_d_cleardia
	gc_efProcDrillBoreClearAmount,		// mop_d_appr_clear
	gc_efProcDrillBoreEntryExitRad,		// mop_d_ee_rad
	gc_efProcDrillBoreEntryExitLine,	// mop_d_min_move
	gc_efProcDrillBoreCutWidth,			// mop_d_cutwidth
	gc_efProcDrillBoreStock,			// mop_d_stock
	gc_efProcDrillBoreOverlap,			// mop_d_overlap
	gc_efProcDrillBoreApproachAngle,	// mop_d_appr_ang
	gc_efProcDrillBoreDesStep,			// mop_d_des_step
	gc_eiProcDrillBoreCutType,			// mop_d_cuttype
	
	// Lathe Contour Variable B-Axis
	gc_eiProcVaryBAxisUsed,
	gc_eiProcVaryBAxisMethod,
	gc_eiProcVaryBAxisMultiTrans,
	gc_eiProcVaryBAxisUseMinAngle,
	gc_efProcVaryBAxisMinAngle,
	gc_eiProcVaryBAxisUseMaxAngle,
	gc_efProcVaryBAxisMaxAngle,
	gc_eiProcVaryBAxisSmoothCorners,
	gc_efProcVaryBAxisLeadLagAngle,
	gc_eiProcVaryBAxisVectorType,
	gc_eiProcVaryBAxisCheckCollisions,
	gc_efProcVaryBAxisCollisionClearance,
	gc_eiProcUtilType,

	gc_eiProcMStayInStock,			// mop_m_useStock

	// For Thread from shape (Contour Threading)
	gc_eiProcLThrdMethod,
	gc_efProcLThrdXrShift,

	//for Mill Feature Depth
	gc_efProcMillFeat_IncToolDepth,
	gc_efProcMillFeat_IncFeatDepth,
	gc_efProcMillFeat_AbsFeatDepth,
	gc_efProcMillFeat_IncApproachZ,

	gc_ewsProcMillFeat_ApproachZ,
	gc_ewsProcMillFeat_RetractZ,
	gc_ewsProcMillFeat_TopSurfZ,
	gc_ewsProcMillFeat_FeatZ,
	gc_ewsProcMillFeat_MachCS,

	gc_eiProcMillFeat_DepthFromFeat,
	gc_eiProcMillFeat_ApproachZType3,
	gc_eiProcMillFeat_RetractZType,
	gc_eiProcMillFeat_FeatZType2,
	gc_eiProcMillFeat_TopSurfZType2,
	gc_eiProcMillFeat_MachCSType2,

	// new contouring options
	gc_eiProcRampContouring,	// for ramp down
	gc_eiProcExtraOffset,		// for multiple passes contouring
	gc_efProcExtraStepover,		// for multiple passes contouring
	gc_eiProcState,

	// HelixBore
	gc_eiProcDrillUseCircleDia,
	gc_eiProcDrillRapidIn,
	gc_eiProcDrillSpiralUp,
	gc_efProcDrillSpiralAng,

	// Bore entry/exit
	gc_eiProcDrillEntryType,
	gc_efProcDrillEntryArcLine,
	gc_efProcDrillEntryArcRad,
	gc_efProcDrillEntryLineLine,
	gc_eiProcDrillEntryCenter,
	gc_eiProcDrillExitType,
	gc_efProcDrillExitArcLine,
	gc_efProcDrillExitArcRad,
	gc_efProcDrillExitLineLine,
	gc_eiProcDrillExitCenter,

	// does the op contain an expanded longhand path
	gc_eiProcDrillExpanded,

	// pocketing
	gc_eiProcOutermostAsBoss,

	// Drill Hole Feature Options
	gc_eiProcDrillHoleSurfZ,			// mop_d_start_depthtype
	gc_eiProcDrillHoleDepthZ,			// mop_d_end_depthtype
	gc_eiProcDrillHoleSurfSegment,		// mop_d_start_seg_num
	gc_eiProcDrillHoleDepthSegment,		// mop_d_end_seg_num
	gc_eiProcDrillHoleAdjustToolTip,	// mop_d_adjust_tool_tip
	gc_efProcDrillHoleAdjustTipDelta,	// mop_d_adjust_tip_delta

	gc_eiProcDrillHoleSegmentMatch,		// mop_d_seg_match
	gc_eiProcDrillHoleSegMatchLen,		// mop_d_seg_prop_length
	gc_eiProcDrillHoleSegMatchDia,		// mop_d_seg_prop_dia
	gc_eiProcDrillHoleSegMatchTaper,	// mop_d_seg_prop_taper
	gc_eiProcDrillHoleSegMatchMethod,	// mop_d_seg_prop_method

	// does the process use a tool
	gc_eiProcAllowTool,
}
teProcInfo;

typedef enum {						// teShapeInfo
	gc_eiShapeToolSide,		//0=gc_eLeft, 1=gc_eRight, 2=gc_eCenter
	gc_eiShapeStartRef,
	gc_eiShapeEndRef,
	gc_eiShapeExitRef,
	gc_efStartParam,
	gc_efEndParam,
	gc_efStartPt,
	gc_efEndPt,
	gc_efStartMarkerParam,
	gc_efEndMarkerParam,
	gc_efStartMarkerLoc,
	gc_efEndMarkerLoc,
	gc_eiShapeArw1,		//True or false.  Arrow direction for display and toolpath purposes ( cutside display info )
	gc_eiShapeArcDir,
	gc_eiSingleFeat
} teShapeInfo;

typedef enum
{
	gc_eTravCP2,
	gc_eTravCP1,
	gc_eTravVarCP1,
	gc_eTravHoleClear,
} gc_teTravPlane;

typedef enum
{
	gc_eStartAbs_DDT = 0,
	gc_eStartTop_DDT,
	gc_eStartSegmentStart_DDT,
	gc_eStartSegmentEnd_DDT,
} gc_teStartDepthType;

typedef enum
{
	gc_eEndTop_DDT = 0,
	gc_eEndChamfer_DDT,
	gc_eEndMid_DDT,
	gc_eEndBottom_DDT,
	gc_eEndSegmentStart_DDT,
	gc_eEndSegmentEnd_DDT,
	gc_eEndAbs_DDT,
} gc_teEndDepthType;

typedef enum
{
	gc_eIndex_HFSM = 0,
	gc_eProperties_HFSM,
} gc_teHFSegMatch;

struct gc_trRPMChange				// Extra Data For gc_eLatheRPMCT CTools (deprecated, use gc_trRPMChange2)
{
	int iWP;
	int bCCW;
	double xRPM;
};

struct gc_trRPMChange2				// Extra Data For gc_eLatheRPMCT and gc_eMillRPMCT CTools
{
	int iComponent;					// wp or tg, depending on ctool type
	int bCCW;
	double xRPM;
};

struct gc_CSSChange
{
	enum {cur_vers = 1};

	int version;
	int wp;
	bool css_on;
	double supm;					// surface units (in/meters) per minute, only valid if css_on == true
	double max_rpm;					// only valid if css_on == true

	gc_CSSChange()
		: version(cur_vers), wp(0), css_on(false), supm(-1.0), max_rpm(-1.0) {}
	gc_CSSChange(long the_wp, bool on, double su = - 1.0, double rpm = - 1.0)
		: version(cur_vers), wp(the_wp), css_on(on), supm(su), max_rpm(rpm) {}
};

struct gc_trSpindleMode				// Extra Data For gc_eSpindleModeCT CTools
{
	int iWP;
	int bLathe;
};

struct gc_trTCPMode					// Extra Data For gc_eTCPModeCT CTools
{
	BOOL bOn;
};					

struct gc_trSpindleLink
{
	int buddys[2];
};



#define gc_eUserRPMCT gc_eLatheRPMCT		// old name for lathe rpm ctool



enum		//teGCOptions
{
	gc_eMillOpt,
	gc_eLatheOpt,
	gc_eMillTurnOpt,
	gc_eEDMOpt,
	gc_eExchangeOpt,
	gc_eAdvMillOpt,
	gc_eRotaryMillOpt,
	gc_eCPROpt,
	gc_eAdvLatheOpt,
	gc_e5ARotaryMillOpt,
	gc_eCutDataOpt,
	gc_eSolidsOpt,
	gc_ePostingOpt,
	gc_eSimluationOpt,
	gc_eSolidImportOpt,
	gc_eSATImportOpt,
	gc_eDWGImportOpt,
	gc_eCatiaImportOpt,
	gc_eVDAImportOpt,
	gc_eMachineSimOpt,
	gc_MTM_Flow1Opt,
	gc_MTM_Flow2Opt,
	gc_MTM_Flow3_PlusOpt,
	gc_eAPT_CLOpt,
	gc_eGraniteOpt,
	gc_eCat_V5Opt,
	gc_e2_5D_SolidsOpt,
	gc_eFuture_2Opt,
	gc_eFuture_3Opt,
	gc_eLevel_0Opt,
	gc_eMinCADOpt,
	gc_eMinCADHealStitchOpt,
	gc_eTombstone_Opt,
	gc_e4Axis_Opt,
	gc_eProAXYZ_4Axis = gc_e4Axis_Opt,
	gc_e5Axis_Opt,
	gc_eUGS_NX_Opt,
	gc_eMultiAxisRendering_Opt,
	gc_eUNUSED_4_Opt,
	gc_eUNUSED_5_Opt,
	gc_ePH_MillTurn_Opt,
	gc_ePH_MTM_L1_Opt,
	gc_ePH_MTM_L2_Opt,
	gc_ePH_MTM_L3_Opt,
	gc_eVoluMill2D_Opt,
	gc_eVoluMill3D_Opt,
	gc_e5Axis_Multiblade_Opt,
	gc_e5Axis_Adv_Multiblade_Opt,
	gc_e5Axis_Port_Opt,
	gc_eAPT_CL_Mori_Opt,
	gc_eSTEP_Interop_Opt,
	gc_eCREO_Interop_Opt,
	gc_eAdveon_Opt,
	gc_eCat_V5_Spatial_Opt,
	gc_eSTEP_Spatial_Opt,
	gc_LastOpt
};

enum
{
	gc_English = 0,
	gc_French,
	gc_Spanish,
	gc_Japanese,
	gc_Chinese,	
	gc_Korean,
	gc_Italian,
	gc_German,
	gc_Swedish,
	gc_Polish,
	gc_Portuguese,
	gc_Russian,
	gc_Turkish,
	gc_Czech,
	gc_Dutch,
	gc_Other = 200
};

enum			// body boolean operation types
{
	gc_Body_Union,
	gc_Body_Intersection, 
	gc_Body_Difference
};

enum			// Face parametrization info
{
	gc_eFaceParamBound_Infinite,
	gc_eFaceParamBound_Extendable,
	gc_eFaceParamBound_Bound,
	gc_eFaceParamBound_Closed,
	gc_eFaceParamBound_Degenerate
};

enum
{
	gc_eFaceParamPeriodic_No,
	gc_eFaceParamPeriodic_Yes,
	gc_eFaceParamPeriodic_Seamed
};

enum
{
	gc_eFaceParamForm_Linear,
	gc_eFaceParamForm_Circular,
	gc_eFaceParamForm_Any,
};



#define		gc_fOptInstaled	0x01
#define		gc_fOptKeyed	0x02
#define		gc_fOptAvail	0x04

enum { eUserUT, eEntryUT, eContourUT };

enum { gc_eNoPlane = 0, gc_eXYPlane, gc_eXZPlane, gc_eYZPlane};

enum { gc_eNoTrim, gc_eTrim, gc_eAutoConnect };

typedef struct 
{								//	initalized to
	int		iVersion;			//	1	Do not change
	int		bComParallelCSs;	//	1	Combine Parallel CSs
	int		bSepWGperLevel;		//	1	
	int		bSepWGperCS;		//	0
	int		bForce1CS;			//	0
	int		bPeserveHVD;		//	0
	int		bAllowPoints;		//	0
	int		bAllowLines;		//	1
	int		bAllowCircles;		//	1
	int		bAllowConics;		//	1
	int		bAllowSurfs;		//	1
	int		bAllowCurves;		//	1
	int		bAllowSubordinates;	//	0
	int		bAllowInvisibles;	//	0
	int		bAllowAnnotations;	//	0
	int		bCheckArcs;			//	0
	int		ePreferredPlane;	//	1	gc_eXYPlane
	int		eTrimPrefs;			//	2	gc_eAutoConnect
	int		bSecondPass;		//	0
	double	xConnectRange;		//	0.0
	double	xCurveAccuracy;		//	0.005
	double	xShrinkage;			//	0.0
}gc_ImportFilter;

typedef struct
{
	int	iVersion;			//	1	Do not change
	int	bPoints;
	int	bLines;
	int	bCircles;
	int	bCurves;
	int	bSurfaces;
	int	bOutputInPartUnit;
	int iOutputUnit;       // Used only if bOutputInPartUnit == 0
	int	bSuppressZ;
} gc_ExportFilter;



typedef enum	// Symbols for gc_SetRenderCallBack iMode
{
	gc_eRCB_OpStart,
	gc_eRCB_OpEnd,
	gc_eRCB_PosUpdate,
	gc_eRCB_Play,
	gc_eRCB_Stop,
	gc_eRCB_Reset
} gc_teRenderCallBack;

typedef struct
{
	double	dPosXYZ[3];			// Tool Position
	double	dPosIJK[3];			// Tool Vector
	int		iCallbackStopReq;	// Render Stop Request
} gc_rRenderPosUpdateCBData;

typedef struct
{
	int       iSelType; // 0 - none, 1 - geo, 2 - solid, 3 - face, 4 - edge
	int       iWG;
	int       iRef;
	long      iSolid;
	gc_TopoId topoID;
} gc_rPreselectSelectionData;

typedef enum	// Symbols for gc_SetEventCallBack iMode
{
	gc_eECB_MouseDownInContent,
	gc_eECB_PreMouseDownInContent,
	gc_eECB_PostMouseDownInContent,
	gc_eECB_MouseDragInContent,
	gc_eECB_MouseDragUpInContent,
	gc_eECB_PreDoubleClickInContent,
	gc_eECB_PostDoubleClickInContent,
	gc_eECB_MouseMoveInContent,
	gc_eECB_PreKeyDown,
	gc_eECB_PostKeyDown,
	gc_eECB_PreselectChange				//third callback arg is a pointer to gc_rPreselectSelectionData
} gc_teEventCallBack;

typedef enum	// Symbols for event callback key states
{
	gc_eECB_LeftButton =(1 << 0),
	gc_eECB_RightButton=(1 << 1),
	gc_eECB_AltKey	   =(1 << 2),
	gc_eECB_CtrlKey	   =(1 << 3),
	gc_eECB_ShftKey	   =(1 << 4)
} gc_teEventCallBackKeyState;

typedef enum	// FileIO Callbacks Import Type
{
	gc_eIGES,
	gc_eDXF,
	gc_ePointList,
	gc_ePSolid,
	gc_eSAT,
	gc_eSolidEdge,
	gc_eSolidWorks,
	gc_eVDA,
	gc_encCAD,
	gc_eCatia,
	gc_eUnknownImport
} gct_eImportType;

typedef enum	// FileIO Callbacks
{
	gc_eFileCB_New,			// rFileCBData -New File Name
	gc_eFileCB_Open,		// rFileCBData -Open File Name
	gc_eFileCB_Close,		// NULL -NoData
	gc_eFileCB_Save,		// rFileCBData -Save File Name
	gc_eFileCB_SaveAs,		// rFileCBData -Save As File Name
	gc_eFileCB_ChangeMDD,	// rFileCBData -New MDD Name
	gc_eFileCB_PreImport,	// rFileCBData -Import File Name
	gc_eFileCB_PostImport,	// rFileCBData -Import File Name
	gc_eFileCB_PreClose,  	// NULL -NoData
	gc_eFileCB_PreSave,		// NULL -NoData
	gc_eFileCB_PreChangeMDD,// NULL -NoData
	gc_eFileCB_OpenProc,		// rFileCBData -Open Process File Name
	gc_eFileCB_MatDBSourceChanged	//material database source changed - not applicable for custom implementations as their source doesn't change dynamically
} gc_teFileCallBack;

struct gc_OutputText
{
	const char *sText;
	int bWithLineNum;
};

enum gc_tePostCallBack	// Post Callbacks
{
	gc_ePCB_Start,				// before posting
	gc_ePCB_Display,			// after posting and after "END" callback
	gc_ePCB_Debug,				// each time the "debug" hit command is called
	gc_ePCB_BeforeCommand,		// before each compost command
	gc_ePCB_AfterCommand,		// after each compost command
	gc_ePCB_End,				// after posting but before "Display"
	gc_ePCB_TextOutput,			// when gc_OutputPostLine is called, void* points to gc_OutputText struct
	gc_ePCB_AllowSelOps,		// return 1 to disable "post selected ops" option, 0 to restore - at dialog launch & before posting
	gc_ePCB_AllowMulti,			// return 1 to Force num parts to 1, 0 to restore - at dialog launch & before posting
	gc_ePCB_AllowPosting,		// return 1 to disable the ability to post
	gc_ePCB_PostException,		// called when a post exception is raised
	gc_ePCB_AllowPostDialog,	// return 1 to disable the posting dialog
};

typedef enum	// MDD Event Callbacks
{
	gc_eMDDCB_CreateMDD,			// when we are extracting a MDD
	gc_eMDDCB_PartMDDIsOlder,		// When the part has an older MDD
	gc_eMDDCB_PartMDDIsNewer,		// When the part has an newer MDD
	gc_eMDDCB_DuplicateFound		// when there is a duplicated MDD KEY
}gc_teMDDEventCallBack;

typedef struct
{
	char fName[512];
	gct_eImportType eImportType;
	int iOriginalPVer;
} gc_rFileCBData;


#define gc_ePocConnectMove 4// connection move between the offsets in the spiral pocket
typedef struct 
{
	int		iVersion;
	int		PocketType;	// spiral=1, facinf=2, zigzag=3
	double	FirstOffset;
	double	CutWidth;
	double	EntryClearance;
	double	ExitClearance;
	double	Depth;
	int		EntryPerp;
	int		ExitPerp;
	double	EntryLine;
	double	ExitLine;
	double	EntryRad;
	double	ExitRad;
	double	PocketStock;
	double	BossStock;
	int		CutType;	// Climb=0, Conv=1
	double	ZigZagCutAngle;
}gc_PocketParam;

typedef enum
{
/*DEPRECATED*/	gc_eAppPath = 0,			//	Install_Directory
/*DEPRECATED*/	gc_eVMMPath,				//	Install_Directory\VMM
/*DEPRECATED*/	gc_eMDDPath,				//	Install_Directory\MDD
/*DEPRECATED*/	gc_ePluginPath,				//	Install_Directory\Plugins
/*DEPRECATED*/	gc_ePluginDataPath,			//	C:\Documents and Settings\username\Application Data\Gibbs\GibbsCAM\Version#\Plugins\Data directory inside Local User directory
	gc_ePrefsPath,					//	C:\Documents and Settings\username\Application Data\Gibbs\GibbsCAM\Version#
	gc_eMyDocsPath,					//	C:\Documents and Settings\username\My Documents
	gc_eGlobalPrefsPath,			//	C:\Documents and Settings\username\Application Data\Gibbs\GibbsCAM\Version#
	gc_eTempPrefsPath,				//	C:\Documents and Settings\username\Application Data\Gibbs\GibbsCAM\Version#\current_time
	gc_eTempCommonPrefsPath,		//	C:\Documents and Settings\username\Application Data\Gibbs\GibbsCAM\Version#\current_time
/*DEPRECATED*/	gc_eGlobalMDDPath,			//	C:\Documents and Settings\All Users\Application Data\Gibbs\GibbsCAM\Version#\MDD		
	gc_eUserProcessListPath,		//	User Set Process List
	gc_eUserCutDataPath,			//	User Set Cut Data path 
	gc_eUserFontPath,				//	User Set Font Path
/*DEPRECATED*/	gc_eReporterTemplatePath,	//	Install_Directory\Plugins\Data\Report
/*DEPRECATED*/	gc_ePluginDataSetupPath,	//	Install_Directory\Plugins\Data
	gc_eCommonDocsPath,				//	C:\Documents and Settings\All Users\Documents
/*DEPRECATED */	gc_eGlobalPluginDataPath,	//	C:\Documents and Settings\All Users\Application Data\Gibbs\GibbsCAM\Version#\Plugins\Data - use gc_ePluginData_PD_Path
	gc_eDefaultPartsPath,			//	C:\Documents and Settings\username\Application Data\Gibbs\GibbsCAM\Version#\DefaultParts
	gc_eImportedPartsPath,			//	C:\Documents and Settings\username\Application Data\Gibbs\GibbsCAM\Version#\ImportedParts
	gc_eInstallDir,					//  Install_Directory - this is NOT the folder where the executable is installed, just the top level folder - use instead of gc_eAppDir
	gc_eBinPath,					//  Install_Directory\Bin - where all GibbsCAM binaries are installed
	gc_eResPath,					//	Install_Directory\Res - GibbsCAM Resource Files
	gc_eVMM_PF_Path,				//  Install_Directory\VMM
	gc_eVMM_PD_Path,				//	ProgramData\Gibbs\GibbsCAM\<version#>\VMM
	gc_eMDD_PF_Path,				//	Install_Directory\MDD
	gc_eMDD_PD_Path,				//	ProgramData\Gibbs\GibbsCAM\<version#>\MDD
	gc_ePluginData_PF_Path,			//	Install_Directory\Plugins\Data
	gc_ePluginData_PD_Path,			//	ProgramData\Gibbs\GibbsCAM\<version#>\Plugins\Data
	gc_ePluginData_User_Path,		//	Users/<Username>\AppData\Roaming\GibbsProgramData/Gibbs/GibbsCAM/<version#>\Plugins\Data
	gc_eReporterTemplate_PF_Path,	//	Install_Directory\Plugins\Data\Report
	gc_eReporterTemplate_PD_Path,	//	ProgramData\Gibbs\GibbsCAM\<version#>\Plugins\Data\Report
	gc_eReporterTemplate_User_Path,	 //	Users/<Username>\AppData\Roaming\GibbsProgramData/Gibbs/GibbsCAM/<version#>\Plugins\Data\Report
	gc_eCommonDocsVerNumPath,		//	Win7: X:\Users\Public\Documents\Gibbs\GibbsCAM\<version#>\  Win XP: X:\Documents and Settings\All Users\Documents\Gibbs\GibbsCAM\<version#>
	gc_eHelpDir,					//	Install_Directory\Help
	gc_eMacros_PD_Path,				//	ProgramData\Gibbs\GibbsCAM\<version#>\Macros
	gc_eMachineSim_PF_Path,			//	Install_Directory\MachineSim 
	gc_eMachineSim_PD_Path,			//	ProgramData\Gibbs\GibbsCAM\<version#>\MachineSim 
	gc_eIntermediateTooling_PD_Path,// 	ProgramData\Gibbs\GibbsCAM\<version#>\Intermediate Tooling
	gc_eLastOpenPath,
	gc_eLocalPrefsPath,
	gc_eCommonPluginPath,			//C:\Program Files\Common Files\GibbsCAM Shared\Plugins
	gc_eVGCommonPluginPath,			//C:\Program Files\Common Files\Virtual Gibbs Shared\Plugins
}gc_eFolderPaths;

typedef enum
{
	gc_eZeroEdgeOffset,
	gc_eToolRadEdgeOffset,
	gc_eExactEdgeOffset
}	gc_teEdgeNCenter;

typedef enum
{
	gc_eStatusEmpty,
	gc_eStatusIncomplete,
	gc_eStatusComplete,
	gc_eStatusInvalid
}
gc_eTileStatus;

typedef enum
{
	gc_eTessMatchNone,
	gc_eTessMatchGeom,
	gc_eTessMatchTopo,
	gc_eTessMatchTrim
} gc_eSolTessMatchMode;

enum gc_eRotPref
{
	gc_eMin4thRot,			// try minimum short-axis rotation from current
	gc_eMin5thRot,			// try minimum long-axis rotation from current (default)
	gc_eMinComboRot,		// try minimum sum of rotations from current
	gc_eMinOfMaxRot,		// will use solution with minimum maximum delta from current
	gc_eUseDefaultRotRule	// use the default (from the MDD, or possibly the op)
};

enum gc_eRotHeadOpOverrideType
{
	gc_eNoOverride,
	gc_eShortOverride,
	gc_eLongOverride
};

enum gc_eRotHeadOverrideLevel
{
	gc_eRHOverrideNone,
	gc_eRHOverrideFullRetract,			
	gc_eRHOverridePresetPosition,		
	gc_eRHOverrideGlobalCP1,				
	gc_eRHOverrideNoMove,
	gc_eRHOverrrideIncCP3,
	gc_eRHOverrrideIncCP1		
};

enum gc_eRotHeadTCPOverrideLevel
{
	gc_eRHTCPOverrideNone,
	gc_eRHTCPOverrideNoChange,			
	gc_eRHTCPOverrideLev1,		
	gc_eRHTCPOverrideLev2,				
	gc_eRHTCPOverrideLev3					
};

struct gc_OpRotHeadOpOverride
{
	gc_eRotHeadOpOverrideType		overrideType;
	gc_eRotHeadOverrideLevel		level1Override;
	gc_eRotHeadOverrideLevel		level2Override;
	gc_eRotHeadOverrideLevel		level3Override;
	double							level1OverrideValue;
	double							level2OverrideValue;
	double							level3OverrideValue;
	gc_eRotHeadTCPOverrideLevel		tcpOverride;
};


enum gc_eOpPathAttr
{
	gc_eOp_Has_IJK				= (1 << 0),
	gc_eOp_Has_Splines			= (1 << 1),
	gc_eOp_Has_RChange			= (1 << 2),
	gc_eOp_Has_WrapDChange		= (1 << 3),
	gc_eOp_Has_IntraOpConnect	= (1 << 4),
	gc_eOp_Has_NonAlignedIJK	= (1 << 5)
};

typedef enum
{
	gc_eGibbscam,
	gc_eVirtualGibbs

} gc_teProductType;



// custom op fields
#define gc_kFLD_MOVESTOOL			"MovesTool"				// field's presence and contents tells us that op moves tool
#define gc_kFLD_ATHOME				"AtHome"				// field's presence and contents tells us that op is at home
#define gc_kFLD_STARTOFFPART		"StartOffPart"			// field's presence and contents tells us that tool starts "off part"
#define gc_kFLD_ENDOFFPART			"EndOffPart"			// field's presence and contents tells us that tool end "off part"
#define gc_kFLD_POSTSCRIPT			"PostScript"			// field's contents will be merged into the start op post script at posting time.
#define gc_kFLD_FLOW1				"Flow1"					// flow numbers
#define gc_kFLD_FLOW2				"Flow2"					// flow numbers
#define gc_kFLD_FLOW3				"Flow3"					// flow numbers
#define gc_kFLD_FLOW4				"Flow4"					// flow numbers
#define gc_kFLD_FLOW5				"Flow5"					// flow numbers
#define gc_kFLD_FLOW6				"Flow6"					// flow numbers
#define gc_kFLD_FLOW7				"Flow7"					// flow numbers
#define gc_kFLD_FLOW8				"Flow8"					// flow numbers


typedef void (*tfExpandPathCBfunc)(void *in_path, void *out_path, int iOp);	// call back function for path expansion
typedef bool (*tfWillUseLinearApproxCBfunc)(void *prog_itr, int iFlow, double &ch_tol);// return true if you can't support the flow's current feature, set ch_tol to control segmentation
typedef bool (*tfWillUseLinearApproxCBfunc2)(void *prog_itr, int iFlow, double &ch_tol, double &mach_ch_tol);// return true if you can't support the flow's current feature, set ch_tol to control segmentation
typedef void (*tfPostClearCBfunc)(void *prog_itr);// call back function to modify PI contents after initial reset/clear




// ************VERSION INFO******************

//DECLARATIONS
GC_API int gc_GetAPIVersion(int *iVer);
GC_API int gc_GetVersionString(char *sVer);
GC_API int gc_GetAppProductID( int *iID );





//*************UNDO********************


//ENUMERATIONS
enum teAPIUndoType
{
	eAPINoUndo,
	eAPIToolNewUndo,	// deprecated - use eAPIToolNewDelUndo
	eAPIToolDelUndo,	// deprecated - use eAPIToolNewDelUndo
	eAPIToolMoveUndo,
	eAPIOpNewUndo,		// deprecated - use eAPIOpNewDelUndo
	eAPIOpDelUndo,		// deprecated - use eAPIOpNewDelUndo
	eAPIOpMoveUndo,
	eAPIProcNewUndo,	// deprecated - use eAPIProcNewDelUndo
	eAPIProcDelUndo,	// deprecated - use eAPIProcNewDelUnd
	eAPIProcMoveUndo,
	eAPIWGNewUndo,		// deprecated - use eAPIWGNewDelUndo
	eAPIWGDelUndo,		// deprecated - use eAPIWGNewDelUndo
	eAPIWGModUndo,
	eAPICSNewUndo,		// deprecated - use eAPICSNewDelUndo
	eAPICSDelUndo,		// deprecated - use eAPICSNewDelUndo
	eAPICSModUndo,
	eAPIMoveOriginUndo,
	eAPIStockUndo,
	eAPIGEundo,
	eAPIProcReadUndo,
	eAPIWGModCSNewUndo,
	eAPIUTDelUndo,		// deprecated - use eAPIUTEditUndo
	eAPIUTMoveUndo,		// deprecated - use eAPIUTEditUndo
	eAPIUTNewUndo,		// deprecated - use eAPIUTEditUndo
	eAPIAnnotTextUndo,
	eAPIToolNewDelUndo,
	eAPIOpNewDelUndo,
	eAPIProcNewDelUndo,
	eAPIWGNewDelUndo,
	eAPICSNewDelUndo,
	eAPIUTEditUndo,
	eAPISyncUndo,
	eAPIMillTGUndo,
	eAPILatheTGUndo,
	eAPISelUndo,
	eAPISolSwapUndo,
	eAPISolReplaceUndo,
	eAPIProfileDragUndo,
	eAPIOpModTPUndo,
	eAPICustomPartDataUndo,
	eAPICustomDataUndo,
};

enum gc_eUndoCallBackType
{
	gc_eAfterUndoCallBack
};

enum gc_eUndoEventType
{
	gc_eUndoEvent,
	gc_eRedoEvent
};

typedef enum
{
	gc_eDeleteOp,
	gc_eDeleteTool,
	gc_eDeleteProcess,
	gc_eDeleteMaterial,
	gc_eDeleteWG,
	gc_eDeleteCS,
	gc_eDeleteGeom
} gc_DeleteWithUndoChoiceID;

enum gc_eCustomUndoEventType
{
	gc_eCustomUndoEvent_SetReadContext,
	gc_eCustomUndoEvent_Read,
	gc_eCustomUndoEvent_Write,
	gc_eCustomUndoEvent_Undo,
	gc_eCustomUndoEvent_Redo
};
typedef int (*gc_CustomUndoCallBack)(gc_eCustomUndoEventType eEventType, void* param1, void* param2, void* udata);

//DECLARATIONS

GC_API int gc_CreateCustomUndo(gc_CustomUndoCallBack callback, void* udata);
GC_API int gc_CreateUndo(teAPIUndoType eUndoType);

/** gc_ToggleMultiUndo
*Allows multiple undo types to be grouped into a single undo action.  
*WARNING: The programmer MUST disable this after they have added their undos or risk unpredictable behavior.
*
*@param	bEnable	true = enabled, false = disabled
*@return		0 for success, - 1 if it's a bad ref
*/
GC_API int gc_ToggleMultiUndo( bool bEnable );
GC_API int gc_GetMultiUndo( int *bOn );
GC_API int gc_DeleteWithUndo(int iType);

//CALLBACKS
typedef void (*gc_UndoCallBack)(gc_eUndoCallBackType, teAPIUndoType, gc_eUndoEventType, void*);
GC_API int gc_SetUndoCallBack(gc_eUndoCallBackType cb_type, gc_UndoCallBack callback, void *info = NULL);
GC_API int gc_ClearUndoCallBack(gc_eUndoCallBackType cb_type, gc_UndoCallBack callback, void *info = NULL);



//*****************WORKGROUPS*************************


//ENUMERATIONS
typedef enum
{
	gc_eWGCB_CurrentChanged			// User Changed WG - No Callback Data
} gc_teWGCallBack;


//DECLARATIONS
GC_API int gc_GetWGCount(int *iCount);
GC_API int gc_GetWGName(int id, char *sName);
GC_API int gc_GetWGNumber(int iCellNum, int *iNum);
GC_API int gc_SetWGName(int id, char *sName);
GC_API int gc_UpdateWGWindow();
GC_API int gc_GetCurWG(int *iCur);
GC_API int gc_SetCurWG(int id);
GC_API int gc_NewWG(int *iWg);
GC_API int gc_DeleteWG(int iWg);
GC_API int gc_GetWGVis(int id, int *iVis);
GC_API int gc_GetWGVisible(int id, bool *bVis);
GC_API int gc_SetWGVisible(int id, bool bVis);
GC_API int gc_AutoConnectWG(int iWG, int iPrefPlane, int bSecondPass, double xConnectRange);
//--attributes
GC_API int gc_AddWGAttList(int iWG, void **attlist);
GC_API int gc_GetWGAttList(int iWG, void **attlist);
GC_API int gc_DeleteWGAttList(int iWG);
//CALLBACKS
typedef int (*gc_tWGCallBack)(int, void *pCBData);
GC_API int gc_SetWGCallBack(int iCB, gc_tWGCallBack);
GC_API int gc_ClearWGCallBack(int iCB, gc_tWGCallBack);


//******************* COORDINATE SYSTEM  ************************

//ENUMERATIONS

enum gc_teCSCallBack
{
	gc_eCSCallBack_FreeTemps,
	gc_eCSCallBack_NewCS,
	gc_eCSCallBack_BeforeChangeCS,
	gc_eCSCallBack_AfterChangeCS,
	gc_eCSCallBack_BeforeDeleteCS,
	gc_eCSCallBack_AfterDeleteCS,
	gc_eCSCallBack_AfterModifyCS,		// a user cs was changed
	gc_eCSCallBack_Last
};
//DECLARATIONS
GC_API int gc_GetCSCount(int *iCount);
GC_API int gc_GetCSName(int id, char *sName);
GC_API int gc_GetCSNumber(int iCellNum, int *iNum);
GC_API int gc_SetCSName(int id, char *sName);
GC_API int gc_UpdateCSWindow();

GC_API int gc_GetCurCS(int *iCur);
GC_API int gc_SetCurCS(int iCur);
GC_API int gc_GetCurOpCS(int *cs);
GC_API int gc_SetCurOpCS(int cs);
GC_API int gc_GetCurPathCS(int *cs);
GC_API int gc_SetCurPathCS(int cs);

GC_API int gc_SetCSWFO(int id, int iWFO);
GC_API int gc_GetCSWFO(int id, int *iWFO);
GC_API int gc_NewCS(int *iCs);
GC_API int gc_DeleteCS(int iCs);
GC_API int gc_SetCS(int id, double *dTrans);
GC_API int gc_GetCS(int id, double *dTrans);
GC_API int gc_GetCSEx(int id, bool bUseGraphicDist, double *dTrans);
GC_API int gc_GetCSLocalWP(int id, double *dTrans);
GC_API int gc_SetCSWP(int iCS, int iWP);
GC_API int gc_GetCSWP(int iCS, int *piWP);
GC_API int gc_ModifyCS(int iCS, double *dTrans);
GC_API int gc_CSTransformPos(int iSrcCS, int iDstCS, double *pos);
GC_API int gc_CSTransformPosEx(int iSrcCS, int iDstCS, bool bUseGraphicDist, double *pos);
GC_API int gc_CSTransformVec(int iSrcCS, int iDstCS, double *vec);
GC_API int gc_GetWPXYCS(int iWP, int *piCS);
GC_API int gc_GetWPXZCS(int iWP, int *piCS);
GC_API int gc_GetWPYZCS(int iWP, int *piCS);
GC_API int gc_GetWPZXCS(int iWP, int *piCS);
GC_API int gc_MatchCS(int iCS, int iWP, int *piCS);
GC_API int gc_FindTurningCS(int iWP, int *piCS);
GC_API int gc_IsCSModifiable(int iCS);

GC_API int gc_GetCSAxisStr(char *s, int iCS, int iAxis, bool bCheckWrapped);
GC_API int gc_GetCSAxisStrEx(char *s, int iCS, int iAxis, bool bCheckWrapped, int *piXYZ);

//--attributes
GC_API int gc_AddCSAttList(int iCS, void **attlist);
GC_API int gc_GetCSAttList(int iCS, void **attlist);
GC_API int gc_DeleteCSAttList(int iCS);

GC_API int gc_GetCSRotAngles(int iCS, double *angles, int iWP = 1, int iTG = 1, int iTool = 0);

//CALLBACKS
typedef void (*gc_tfCSCallback)( const void *pData );
GC_API int gc_SetCSCallBack(gc_teCSCallBack eType, gc_tfCSCallback call_back, const void *id);
GC_API int gc_ClearCSCallBack(gc_teCSCallBack eType, gc_tfCSCallback call_back, const void *id);




//******************* MATRIX  MATH************************

//ENUMERATIONS
//DECLARATIONS
GC_API int gc_TransformPos(double *matrix, double *pos);			// transform pos by matrix
GC_API int gc_TransformVec(double *matrix, double *vec);			// transform vec by matrix
GC_API int gc_MultiplyMatrix(double *matrix_a, double *matrix_b);	// matrix_a <- matrix_a * matrix_b
GC_API int gc_InvertMatrix(double *matrix);							// invert matrix
GC_API int gc_NormalizeMatrix(double *matrix);						// make matrix orthogonal
GC_API int gc_IdentityMatrix(double *matrix);						// returns identity matrix
GC_API int gc_TranslationMatrix(double *matrix, double *vec);		// returns matrix that transles by "vec"
GC_API int gc_RotationMatrix(double *matrix, double *axis, double radians);	// returns matrix that rotates "radians" about "axis"
GC_API int gc_ScalingMatrix(double *matrix, double scale);			// returns matrix that scales
GC_API int gc_MatrixFromAxes(double *matrix, const double *d_axis, const double *h_axis, const double *trans);
GC_API int gc_GetMatrixFromCSToCS(int iFromCS, int iToCS, double *dTrans);

//CALLBACKS



//******************* PART DATA  ************************


//ENUMERATIONS

enum
{	gc_eNOCOOLANT,
	gc_eFLOOD,
	gc_eMIST,
	gc_eTHRUSPINDLE,
	gc_eHIPRESSURE,
	gc_ePULSE,
	gc_eFLOODTHRUSPIN,
	gc_eCUSTOMCOOLANT1,
	gc_eCUSTOMCOOLANT2,
	gc_eCUSTOMCOOLANT3,
	gc_eCUSTOMCOOLANT4,
	gc_eCUSTOMCOOLANT5,
	gc_eCUSTOMCOOLANT6,
	gc_eCUSTOMCOOLANT7,
	gc_eCUSTOMCOOLANT8,
	gc_eCUSTOMCOOLANT9,
	gc_eCUSTOMCOOLANT10,
	gc_eCUSTOMCOOLANT11,
	gc_eCUSTOMCOOLANT12,
	gc_eCUSTOMCOOLANT13,
	gc_eCUSTOMCOOLANT14
};
// part type

enum
{	gc_eLathe75Shk,
	gc_e3AVertMill,
	gc_e3AHorMill,
	gc_e4AVertMill,
	gc_e4AHorMill,
	gc_e5AVertMill,
	gc_e5AHorMill,
	gc_eEDM, 
	gc_eMAT,
	gc_eLathe1Shk,
	gc_eLathe15Shk,
	gc_eLathe5Shk,
	gc_eVLathe75Shk,
	gc_eVLathe1Shk,
	gc_eVLathe15Shk,
	gc_eVLathe5Shk,
	gc_eMillTurn1Shk,
	gc_eMillTurn5Shk,
	gc_eMillTurn75Shk,
	gc_eMillTurn15Shk,
	gc_e5AMillTurn1Shk,
	gc_e5AMillTurn5Shk,
	gc_e5AMillTurn75Shk,
	gc_e5AMillTurn15Shk,
};
typedef enum {
	gc_eiPartClassMTM,
	gc_eiPartClassMillTurn,
	gc_eiPartClassLathe,
	gc_eiPartClassMill
}gc_tePartClass;

typedef enum {						// tePartInfo
	esPartName,
	esPartComment,
	esPartAlloy,
	esPartFamily,
	esPartHardness,
	eiPartType,
	eiPartUnit,
	efPartToolChange,
	efPartCP1,
	efPartStock,
	efPartClrRad,
	eiPartRadius,
	eiPartAutoClear,
	efPartAutoClearVal,
	esPostOutFile,
	esPostFile,
	esMddName,
	esMddFile,
	eiMachAxes,
	efMachPos4,
	efMachPos5,
	efMachVec4,
	efMachVec5,
	efMachRange4,
	efMachRange5,
	eiMachLimits,
	gc_eiToolChangeValid,
	eiMachUseRot4,
	eiMachAxis4,
	eiMachAxis5,
	gc_eiPostStartProgNum = 50,
	gc_eiPostSequence,
	gc_eiPostAbsMoves,
	gc_eiPostInsertComments,
	gc_eiPostInsertOpStops,
	gc_eiPostNumParts,
	gc_eiPostWorkFixtures,
	gc_efPostPartSpacing,
	gc_eiPostOnePartAllTools,
	gc_eiPostInterPartFullUp,
	gc_eiPostMinimize,
	gc_eiPostSelectedOps,
	gc_eiPostPrefHeader,
	gc_eiPostPrefSub,
	gc_eiPostPrefOperation,
	gc_eiPostPrefFooter,
	gc_eiMachFlows,
	gc_eiTGCount,
	gc_eiWPCount,
	gc_eiToolEdgeCRC,
	esPartFile,
	gc_eiPartClass,
	gc_eiMachiningPrefOmitSmallChordArcs,
	gc_eiMachiningPrefAllowMillMaterialOnly,
	gc_eiMachiningPrefEntryLineApproach,
	gc_eiMachiningPrefUseSpunOutlineForLatheProfile,
	gc_eiMachiningCRCEntryLineValidation,
	gc_efGraphicPartDist,
	gc_eiGraphicPartDistOpt,
	gc_eiPartReadOnly,								//this is a read only field, it cannot be set through the API
	gc_eiLToolEdgeCRC,
	gc_eiPostOutputIsMetric,
	gc_ewsPartComment,
	gc_ewsProgNotes,
	gc_eiPartCommentLength,							// Read-Only field
	gc_eiProgNotesLength,
	gc_eiPostMinimizeSubs,
	gc_eiSpindleCount,
	gc_eiSpindles
} tePartInfo;


//--workpiece
enum teMachRotAxis
{
	gc_eiMachRot4,					// the "short" rotary axis
	gc_eiMachRot5					// the "long" rotary axis
};
//--cam palette

typedef enum
{
	gc_ePartTypeMaskMill       = 0x01,
	gc_ePartTypeMaskLathe      = 0x02,
	gc_ePartTypeMaskVertical   = 0x04,
	gc_ePartTypeMask4Axis      = 0x08,
	gc_ePartTypeMask5Axis      = 0x10,
	gc_ePartTypeMaskMTM        = 0x20,
	gc_ePartTypeMaskHorizontal = 0x40,
	gc_ePartTypeMask3Axis      = 0x80
} gc_tePartTypeMask;



typedef enum
{
	eCamPalCustomProcMsgType_GetToolTip,
	eCamPalCustomProcMsgType_GetBalloonTip,
	eCamPalCustomProcMsgType_ProcessCreate,
	eCamPalCustomProcMsgType_GetCustomString,
	eCamPalCustomProcMsgType_GetVisibilityOverride,
	eCamPalCustomProcMsgType_GetHelpContextID
} gc_teCamPalCustomProcMsgType;


typedef enum
{
	eCamPalCustomProcType_Mill=1,
	eCamPalCustomProcType_Lathe
} gc_teCamPalCustomProcType;

//--custom CAM selction API
typedef enum
{
	gc_eCutSelect		= 0,
	gc_eConstraintSelect,
	gc_eStockSelect,
	gc_eEdgeSelect,	
	gc_eCustomMode1,
	gc_eUnselected = 100

} gc_teSelectMode;

//--cut part rendering 
typedef struct
{
	int iFlow;
	int iOp;
	int iNextOp;
	int iOpOrder;
	int iRotation;
	int iOrigin;
	int iZPass;
	int eMoveType;
	int iFeature;
	double xParam;
	double xTime;				// elapsed time in minutes; negative if time not calculated
}
gc_ProgState;
//--custom menu item management API
typedef enum
{
	gc_eMenuIdBodyBag,
	gc_eMenuIdWG,
	gc_eMenuIdCS,
	gc_eMenuIdOps,
	gc_eMenuIdHistory,
	gc_eMenuIdMousePos,
	gc_eMenuIdCSHAxis,
	gc_eMenuIdCSVAxis,
	gc_eMenuIdCSSetPlane,
	gc_eMenuIdGeo,
	gc_eMenuIdCSXYPlane,
	gc_eMenuIdCSXZPlane,
	gc_eMenuIdCSYZPlane,
	gc_eMenuIdCSToggleDepth,
	gc_eMenuIdListFind,
	gc_eMenuIdListMoveTo,
	gc_eMenuIdMarker,
	gc_eMenuIdSyncPref,
	gc_eMenuIdVCR,
	gc_eMenuIdAL_ListFind,
	gc_eMenuIdAL_ListMoveTo,
	gc_eMenuIdUnstitchPrefs,
	gc_eMenuIdWinPos,
	gc_eMenuIdProfile,
	gc_eMenuIdWGMI,
	gc_eMenuIdWGInfo,
	gc_eMenuIdWGSpindles,
	gc_eMenuIdSolidSpindles,
	gc_eMenuIdEditToolMatMI,
	gc_eMenuIdSolids,
	gc_eMenuIdSolidPrimitives,
	gc_eMenuIdSolidDialogs,
	gc_eMenuIdSolidTransforms,
	gc_eMenuIdSolidBooleans,
	gc_eMenuIdFilletedBooleans,
	gc_eMenuIdHiddenLines,
	gc_eMenuIdSurfaces,
	gc_eMenuIdBlending,
	gc_eMenuIdTools,
	gc_eMenuIdCDrillSizes,
	gc_eMenuIdHoleType,
	gc_eMenuIdActions,
	gc_eMenuIdSolidAttribute,
	gc_eMenuIdToolListFind,
	gc_eMenuIdToolListMoveTo,
	gc_eMenuIdProcListFind,
	gc_eMenuIdOpListFind,
	gc_eMenuIdMTM_ToolListFind,
	gc_eMenuIdMTM_ToolListMoveTo,
	gc_eMenuIdProcListMoveTo,
	gc_eMenuIdEnd
} gc_menuID;
//--Custom Material Database API
typedef enum
{
	gc_eMatDB_Family,
	gc_eMatDB_Alloy,
	gc_eMatDB_Hardness,
	gc_eMatDB_Comment,
} gc_teMatItem;

typedef enum
{
	gc_eMatUI_ShowUI,
	gc_eMatUI_CalcSpeed,
	gc_eMatUI_CalcEntryFeed,
	gc_eMatUI_CalcContFeed,
	gc_eMatUI_UIActive,
	gc_eMatUI_MaterialChanged,
} gc_teMatUI;
//--Do attribute menu
typedef enum
{
	gc_eOpCheckLoadOpInfoMI=-2,
	gc_eOpCheckLoadUTInfoMI=-1,
	gc_eOperationDataMI=1,
	gc_eUtilityMarkersMI,
	gc_eOpToolMI,
	//divider
	gc_eOpToGeoMI = 5,
	//divider
	gc_eReprocessMI=7,
	gc_eRedoAllMI,
	//divider
	gc_eMoveToMI=10,
	gc_eOpFindMI,
	gc_eSortOpsMI,
	gc_eTPTMI   = 14,
	gc_eReverseToolPathMI = -111, //obsoleted
	gc_eReorderHVLoopsMI  = -111,  //obsoleted
	gc_eScaleToolpathMI   = -111    //obsoleted
} gc_AttributeMenuItemChoiceID;
//STRUCTURE
//--Wal count and work area limits
struct gc_trLimits
{
	BOOL bUsingMin;
	BOOL bUsingMax;
	double dMin;
	double dMax;
};

struct gc_trWAL
{
	char sName[256];
	gc_trLimits rFirstLimits;
	gc_trLimits rSecondLimits;
};

//DECLARATIONS
GC_API int gc_NewPart(char *sFileName);
GC_API int gc_OpenPart(char *sFileName);
GC_API int gc_OpenPartHidden(char *sFileName, bool bSaveCurrentFile = true);
GC_API int gc_OpenPartEx(char *sFileName, bool bReadOnly );
GC_API int gc_ClosePart(int bForceClose, int bSaveFile);
GC_API int gc_SavePart();
GC_API int gc_SavePartEx( int bMin, int bForce );
GC_API int gc_SavePartAs(char *sFileName);
GC_API int gc_SavePartAsHidden(char *sFileName);

typedef enum
{
	gc_eSaveCopyAs_Without_Facets = 1,
	gc_eSaveCopyAs_3_x,
	gc_eSaveCopyAs_4_0,
	gc_eSaveCopyAs_5_0,
	gc_eSaveCopyAs_5_1,
	gc_eSaveCopyAs_5_5,
	gc_eSaveCopyAs_5_57,
	gc_eSaveCopyAs_6_0x,
	gc_eSaveCopyAs_6_10,
	gc_eSaveCopyAs_6_11,
	gc_eSaveCopyAs_7_0,
	gc_eSaveCopyAs_7_3,
	gc_eSaveCopyAs_7_7,
	gc_eSaveCopyAs_8_0,
	gc_eSaveCopyAs_9_0,
	gc_eSaveCopyAs_9_3,
	gc_eSaveCopyAs_9_5,
	gc_eSaveCopyAs_10_0,
	gc_eSaveCopyAs_10_3,
	gc_eSaveCopyAs_10_5,
	gc_eSaveCopyAs_10_7,
} gc_teSaveCopyAs;

GC_API int gc_SaveCopyAs(char *sFileName, gc_teSaveCopyAs iSaveCopyAs);

GC_API int gc_Exit();
GC_API int gc_GetPartPreviewBitmap(void** handle);//Allocates a windows bitmap handle - must destroy using DeleteObject.
GC_API int gc_GetPartInfoD(int id, double *dVal);
GC_API int gc_GetPartInfoI(int id, int *iVal);
GC_API int gc_GetPartInfoS(int id, char *sVal);
GC_API int gc_GetPartComment(char *s, int iSize);
GC_API int gc_GetPartInfoWS(int id, wchar_t *wsVal, int iSize);
GC_API int gc_SetPartInfoD(int id, double *dVal);
GC_API int gc_SetPartInfoI(int id, int *iVal);
GC_API int gc_SetPartInfoS(int id, char *sVal);
GC_API int gc_SetPartInfoWS(int id, wchar_t *wsVal);
GC_API int gc_IsPartOpen();
GC_API int gc_IsLathePart ( void );
GC_API int gc_GetPartNumCoolant(int *iNum);
GC_API int gc_GetPartCoolant(int iIndex, int *iType, char *sName);
GC_API int gc_TriggerClearanceRecalc();
GC_API int gc_OpenVNCDlog( void );
GC_API int gc_SaveAsVNCDlog( void );
GC_API int gc_SaveACopyDlog( void );
GC_API int gc_NewVNCDlog( void );

/** gc_ApplyPrecision
*This routine will round the input double value based on the current part units precision setting.
*
*@param		double dVal to be rounded
*@return	0 in all cases, no error code returned
*/
GC_API int gc_ApplyPrecision(double *pdVal);
GC_API int gc_ApplyPrecisionType(double *pdVal, int eETPrecType); // one of gc_teETPrecType
//--custom part data
GC_API int gc_GetPartCustomDataSize(const char *sName, int *piSize);
GC_API int gc_GetPartCustomData(const char *sName, void *pData);
GC_API int gc_SetPartCustomData(const char *sName, int iSize, void *pData);
GC_API int gc_ClearPartCustomData(const char *sName);
//--CAM palette
GC_API int gc_GetCamPalCustomProcNum();
GC_API int gc_GetCamPalCustomProcName(int iEntry, char *sName);
GC_API int gc_DeleteCamPalCustomProc(int iEntry);
GC_API int gc_GetCamPalCustomProcNumEx(int iType);
GC_API int gc_GetCamPalCustomProcNameEx(int iType, int iEntry, char *sName);
GC_API int gc_DeleteCamPalCustomProcEx(int iType, int iEntry);
GC_API int gc_SetCamPalCustomProcVisibility(int iType, int iEntry, int iVisible);
GC_API int gc_GetCamPalCustomProcVisibility(int iType, int iEntry, int* iVisible);
GC_API int gc_SetCamPalCustomProcVisibilityMask(int iType, int iEntry, int iVisibilityMask);
GC_API int gc_GetCamPalCustomProcVisibilityMask(int iType, int iEntry, int* iVisibilityMask);
//--custom CAM selection API
GC_API int gc_AddCamPalCustomSolidModeMenuItem(int iId, const char* sLabel, float *dRGBA, int bChecked);
GC_API int gc_GetCamPalCustomSolidModeMenuItem(int iId, char* sLabel, float *dRGBA, int* bChecked);
GC_API int gc_DeleteCamPalCustomSolidModeMenuItem(int iId);
GC_API int gc_GetCamPalCustomSolidModeMenuItemCount(int *iVal);
GC_API int gc_GetCustomSolidModeColor(int eMode, float *dRGBA);
GC_API int gc_SetCustomSolidModeColor(int eMode, const float *dRGBA);		// sets mode color without adding it to the menu
GC_API int gc_ClearCustomSolidModeColor(int eMode);
GC_API int gc_GetSolidSelectionMode(int *iMode);
GC_API int gc_SetSolidSelectionMode(int iMode);
GC_API int gc_GetEdgeSelectionMode(int *iMode);
GC_API int gc_SetEdgeSelectionMode(int iMode);
GC_API int gc_GetGeoSelectionMode(int *iMode);
GC_API int gc_SetGeoSelectionMode(int iMode);
GC_API int gc_CloseCAMDlogs();
GC_API int gc_ToggleTaskManager();
//--API String Arrays
GC_API int gc_InitAPIStrs( int iVectorIndex );
GC_API int gc_CountAPIStrs( int iVectorIndex, int *piCount );
GC_API int gc_AddAPIStr( int iVectorIndex, const char *s );
GC_API int gc_GetAPIStr( int iVectorIndex, int iIndex, char *s );
//--workpiece
GC_API int gc_GetWPName(int iWP, char *sName);
GC_API int gc_GetWPPosition(int iWP, double *pxOffset);
GC_API int gc_GetWPPartOffset(int iWP, double *pxOffset);
GC_API int gc_SetWPPartOffset(int iWP, double xOffset);
GC_API int gc_GetWPPartOffsetEx(int iWP, int iAxis, double *pxOffset);
GC_API int gc_SetWPPartOffsetEx(int iWP, int iAxis, double xOffset);
GC_API int gc_GetWPDisplayMatrix(int iWP, double *matrix);
GC_API int gc_GetWPStockBox(int iWP, double *axStockBox);
GC_API int gc_GetWPStockBoxEx(int iWP, int iToCS, double *axStockBox);
GC_API int gc_SetWPStockBox(int iWP, double *axStockBox);
GC_API int gc_GetWPStockType(int iWP, int *iStockType);
GC_API int gc_GetWPStockBody(int iWP, int *iRef);
GC_API int gc_GetWPStockBodyEx(int iWP, int *iRef);
GC_API int gc_GetWPStockBodyEx2(int iWP, int *iRef, bool includeDisplayOnly, bool allowFacetBody);
GC_API int gc_GetWPChuckWidth(int iWP, double *pdChuck);
GC_API int gc_SetWPChuckWidth(int iWP, double dChuck);
GC_API int gc_GetWPGuideBushFaceZ(int iWP, double *z);
GC_API int gc_SetWPGuideBushFaceZ(int iWP, double z);
GC_API int gc_GetWPGuideBushTotalDepth(int iWP, double *val);
GC_API int gc_SetWPGuideBushTotalDepth(int iWP, double val);
GC_API int gc_GetWPGuideBushInnerDepth(int iWP, double *val);
GC_API int gc_SetWPGuideBushInnerDepth(int iWP, double val);
GC_API int gc_GetWPGuideBushOuterDia(int iWP, double *val);
GC_API int gc_SetWPGuideBushOuterDia(int iWP, double val);
GC_API int gc_GetWPCheckSwiss(int iWP, bool &check_swiss);
GC_API int gc_SetWPCheckSwiss(int iWP, bool check_swiss);
GC_API int gc_GetTailstockHomePos(int iWP, double *pos);
GC_API int gc_GetWPHasLinAxis(long iWP, int iAxis, bool *pbHasAxis);
GC_API int gc_GetWPLinAxisLimits(long iWP, int iAxis, bool *pbLimited, double *axLimits);
GC_API int gc_GetWPHasRotAxis(long iWP, int iAxis, bool *pbHasAxis);
GC_API int gc_GetWPRotAxes(long iWP, int *piAxis4th, int *piAxis5th = NULL);
GC_API int gc_GetWPRotAxisInfo(long iWP, teMachRotAxis iAxis4or5, double *pdPos, double *pdRotVec, double *pdZeroVec);
GC_API int gc_GetWPRotAxisLimits(long iWP, teMachRotAxis eAxis4or5, int *pbLimited, double *axLimits);
GC_API int gc_GetWorkpieceClearance ( int iWP, double *paxPos );
GC_API int gc_SetWorkpieceClearance( int iWP, double *paxPos );
GC_API int gc_GetWPFrontFaceAllowance(int iWP, double *dFrontFaceAllowance);
GC_API int gc_SetWPFrontFaceAllowance(int iWP, double dFrontFaceAllowance);
GC_API int gc_GetWPBackFaceAllowance(int iWP, double *dBackFaceAllowance);
GC_API int gc_SetWPBackFaceAllowance(int iWP, double dBackFaceAllowance);
GC_API int gc_GetWPCutOffWidth(int iWP, double *dCutOffWidth);
GC_API int gc_SetWPCutOffWidth(int iWP, double dCutOffWidth);

//--images
GC_API int gc_SaveImage(int iType, int iMode, const char *sName);
GC_API int gc_SaveOpImages(int iType, int iMode, const char *sBaseName, const char *ext);
/**
*Save out the rendered image of the tool as seen in the Mill Tool dialog
*@param	char *sName		Name of image ( Full path and extension )
*@param short iTool		Tool Index of tool
*@param short iHeight	Height of image
*@param short iWidth	Width of image
*
*@return	-1	invalid tool or tool cannot generate an image
*@return	-2	invalid height or width
*@return	0	successful
*/
GC_API int gc_RenderMillTool( char *sName, short iTool, short iHeight, short iWidth );
GC_API int gc_RenderMillToolEx( char *sName, short iTool, short iHeight, short iWidth, int bShowHolder );
GC_API int gc_RenderMillFormTool( char *sName, short iTool, short iHeight, short iWidth );
GC_API int gc_RenderLatheTool( char *sName, short iTool, short iHeight, short iWidth, int bShowHolder );

//--custom menu item management API
GC_API int gc_AddCustomMenuItem(int menuID, int itemPos, const char* label, int itemID, bool bCheck, bool bEnabled, void* uData);
GC_API int gc_DelCustomMenuItem(int menuID, int itemPos, int itemID);
GC_API int gc_GetCustomMenuItemCount(int menuID);
GC_API int gc_GetCustomMenuItem(int menuID, int itemPos, int* itemID, char* label, bool* bEnabled, bool* bCheck, void** uData);
GC_API int gc_SetCustomMenuItem(int menuID, int itemPos, int itemID, const char* label, bool bEnabled, bool bChecked, void* uData);
//--materials
GC_API void gc_DoMaterials(int iOpen);
GC_API bool gc_IsMaterialWUp(void);

//--region container
/** gc_NewRegionContainer
* creates an opaque pointer to a region container - which holds regions to represent material removed for an operation
*@param		void **gc_NewRegionContainer
*@return	0 - success
*/ 
GC_API int gc_NewRegionContainer( void **rgn_container );
/** gc_AddRegionToContainer
* adds a region to the region contain
*( read the API word doc for information on regions and how they work when nested )
*@param		void *region
*@param		void *rgn_container
*@return	0 - success
*@return	-1 - region is null
*@return	-2 - rgn_container is null
*/ 
GC_API int gc_AddRegionToContainer( void *region, void *rgn_container );

/** gc_AddRegionContainerToOp
* takes the constructed ( and populated ) region container and adds it to an operation to represent material that operation removes 
*( read the API word doc for information on regions and how they work when nested )
*@param		void *rgn_container
*@param		int iOp
*@return	0 - success
*@return	-1 - iOp is invalid
*@return	-2 - iOp is not complete
*/ 
GC_API int gc_AddRegionContainerToOp( void *rgn_container, int iOp );

/** gc_ClearOpRegionContainer
* clears the region container used to represent material that an operation removes
*( read the API word doc for information on regions and how they work when nested )
*@param		int iOp
*@return	0 - success
*@return	-1 - iOp is invalid
*@return	-2 - iOp is not complete
*/ 
GC_API int gc_ClearOpRegionContainer( int iOp );

/** gc_GetOpRegionContainer
* get the current region container associated with an operation
* used gc_NewRegionContainer to create *rgn_container before calling this function
*( read the API word doc for information on regions and how they work when nested )
*@param		int iOp
*@param		void *rgn_container
*@return	0 - success
*@return	-1 - iOp is invalid
*@return	-2 - iOp is not complete
*@return	-3 - *rgn_container is invalid
*/ 
GC_API int gc_GetOpRegionContainer(int iOp, void *rgn_container);

/** gc_DeleteRegionContainer
* Deletes a region container that was created using gc_NewRegionContainer
*( read the API word doc for information on regions and how they work when nested )
*@param		void *rgn_container
*@return	0 - success
*/ 
GC_API int gc_DeleteRegionContainer( void *rgn_container );

//--Material Database API
GC_API int gc_GetAlloyString( int iFamily, int iAlloy, char* sAlloy );
GC_API int gc_GetAlloyComment( int iFamily, int iAlloy, char* sComment );
GC_API int gc_GetFamilyString( int iFamily, char* sFamily );
GC_API int gc_GetNumFamily( int* iNumFam );
GC_API int gc_GetNumAlloy( int iFamily, int* iNumAlloy );
GC_API int gc_GetNumMaterial( int iFamily, int iAlloy, int* iNumMaterial );
GC_API int gc_GetMaterial( int iFamily, int iAlloy, int iMaterial, int* iCutType, char* sHardness, char* sCondition,
						  double* dDepth, int *iToolMat, double* dTlSize, double* dSFPM, double* dIPR, int* iComment, 
						  char* sMatComment, char* sAlloyComment  );
GC_API int gc_AddNewMaterial( char* sFamily, char* sAlloy, char* sCutType, char* sHardness, char* sCondition, double dDepth, 
							 char* sToolMat, double dTlSize, double dSFPM, double dIPR, bool bUserNote, char* sMatComment, char* sAlloyComments );
GC_API int gc_GetNumFamily2( int* num_family );
GC_API int gc_GetFamilyString2( int index, char* family );
GC_API int gc_GetNumAlloy2( int* num_alloy );
GC_API int gc_GetAlloyString2( int index, char* alloy );
GC_API int gc_GetNumHardness( int* num_hardness );
GC_API int gc_GetHardnessString( int index, char* hardness );
GC_API int gc_GetAlloyComment2( char* comment );
 //using custom or old?
GC_API int gc_CustomMatDB( void );
/** gc_CheckAllowMaterialItems
*Used to allow controls in the material dialog if it is up
*
*@return		0 for success, - 1 if the material dialog is not up
*/
GC_API int gc_CheckAllowMaterialItems(void);

//--attributes

enum gc_eAttType
{
	gc_eAttEmpty,			// no data, presence used as a flag
	gc_eAttInt,				// four byte int
	gc_eAttDouble,			// eight byte floating point value
	gc_eAttText,			// text string, size is stored with attribute
	gc_eAttBinary,			// blob, size is stored with attribute
	gc_eAttWText,			// Wide text string, size is stored with attribute
	gc_eAttVector,			// Vector Magnitude and Direction; Automatically transformed on geo modify
	gc_eAttPoint			// Vector Coordinate Location; Automatically transformed on geo modify
};

// installed attdefs...
GC_API int gc_GetInstalledAttDefCount(int *piCount);
GC_API int gc_GetInstalledAttDefName(int iIndex, char *sName);
GC_API int gc_InstallAttDef(const char *sName, gc_eAttType eType);
GC_API int gc_UnInstallAttDef(const char *sName);		

// part attdefs...
GC_API int gc_GetPartAttDefCount(int *piCount);
GC_API int gc_GetPartAttDef(const char *sName, int *piIndex);
GC_API int gc_GetPartAttDefName(int iIndex, char *sName);
GC_API int gc_GetPartAttDefType(int iIndex, gc_eAttType *peType);

//--attlists

GC_API int gc_GetAttListCount(void *attlist, int *piCount);
GC_API int gc_GetAttListAtts(void *attlist, void **attrib_list, int *paiAttDefs);

//--attribute creation/deletion/etc.

GC_API int gc_AddAttribute(void *attlist, int iAttDef, void **attrib);
GC_API int gc_GetAttribute(void *attlist, int iAttDef, void **attrib);
GC_API int gc_DeleteAttribute(void *attlist, int iAttDef);

//--attribute values

GC_API int gc_GetAttributeDef(void *attrib, int *piAttDef);
GC_API int gc_GetAttributeName(void *attrib, char *sName);
GC_API int gc_GetAttributeType(void *attrib, gc_eAttType *peType);
GC_API int gc_GetAttributeInt(void *attrib, int *piVal);
GC_API int gc_GetAttributeDouble(void *attrib, double *pxVal);
GC_API int gc_GetAttributePoint(void *attrib, double point[/*3*/]);			// for gc_eAttPoint and gc_eAttVector
GC_API int gc_GetAttributeTextSize(void *attrib, int *piSize);
GC_API int gc_GetAttributeText(void *attrib, char *sText);
GC_API int gc_GetAttributeBinarySize(void *attrib, int *piSize);
GC_API int gc_GetAttributeBinary(void *attrib, void *pData);
GC_API int gc_SetAttributeInt(void *attrib, int iVal);
GC_API int gc_SetAttributeDouble(void *attrib, double xVal);
GC_API int gc_SetAttributePoint(void *attrib, const double point[/*3*/]);	// for gc_eAttPoint and gc_eAttVector
GC_API int gc_SetAttributeText(void *attrib, char *sText);
GC_API int gc_SetAttributeBinary(void *attrib, int iSize, void *pData);

// attribute callbacks...

enum gc_eGeoTransformType
{
	gc_eTranslateGeoTransform,
	gc_eRotateGeoTransform,
	gc_eMirrorGeoTransform,
	gc_eScaleGeoTransform,
	gc_eForceDepthGeoTransform,
	gc_eOtherGeoTransform,
};

typedef void (*gc_AttribTransformCallBack)(int iGeoRef, void *attrib, gc_eGeoTransformType transform_type, const double mx[/*12*/]);

GC_API int gc_GetAttribTransformCallBack(const char *sName, gc_AttribTransformCallBack &call_back);
GC_API int gc_SetAttribTransformCallBack(const char *sName, gc_AttribTransformCallBack call_back);
GC_API int gc_ClearAttribTransformCallBack(const char *sName);

//--Feed And Speeds
GC_API int gc_CalcFeeds( int iProc, double *pdRPM, double *pdEntry, double *pdContour, bool bCalcSpeed = false);
GC_API int gc_GetFeedsAndSpeeds( int iProc, double *dRPM, double *dEntry, double *dContour );
//--Do attribute menu
GC_API int gc_DoAttributeMenu(int wid, int iChoice, int iCell, int iPosX, int iPosY);
//--coolant
GC_API int gc_CoolMen2Fun2(int iMItem);
GC_API int gc_CoolFun2Men2(int iCoolant);
//--Wal count and work area limits
GC_API int gc_GetWALCount(int *iWALs);
GC_API int gc_GetWorkAreaLimits(int iWAL, gc_trWAL *prWAL);
//CALLBACKS

//--CAM palette
typedef int (*gc_tCamPalCustomProcCallBack)(gc_teCamPalCustomProcMsgType, void*, void*);
GC_API int gc_InsertCamPalCustomProc(int iEntry, char *sName, gc_tCamPalCustomProcCallBack userProc, void* userData);
GC_API int gc_InsertCamPalCustomProcEx(int iType, int iEntry, char *sName, gc_tCamPalCustomProcCallBack userProc, void* userData);
GC_API int gc_InsertCamPalCustomProcEx2(int iType, int iEntry, char *sName, gc_tCamPalCustomProcCallBack userProc, void* userData, int iLvlAvail );
GC_API int gc_GetCamPalCustomProcInfo( int iType, int iEntry, char *sName, gc_tCamPalCustomProcCallBack *userProc, void** userData, int* iLvlAvail );
//--custom menu item management API
typedef int (*gc_tMenuEventCallBack)(int, int, void*);
GC_API int gc_SetCustomMenuCallback(gc_tMenuEventCallBack cb, void* uData);
GC_API int gc_RemoveCustomMenuCallback(gc_tMenuEventCallBack cb);
//--custom material db
typedef int (*gc_tGetNumMatItems)( gc_teMatItem, int* );
typedef int (*gc_tGetMatString)( gc_teMatItem, int, char* );
typedef int (*gc_tMatUIAction)( gc_teMatUI, double *, void* );
GC_API int gc_SetMatNumCB( gc_teMatItem eType, gc_tGetNumMatItems call_back );
GC_API int gc_SetMatStringCB( gc_teMatItem eType, gc_tGetMatString call_back );
GC_API int gc_SetMatUICB( gc_teMatUI eType, gc_tMatUIAction call_back );

//******************* GEOMETRY   ************************


//ENUMERATIONS
enum teCurveFitMode
{
	eUniformFit,
	eChordLenFit,
	eFoleyFit,
	eCentripetalFit
};
enum teGeoType
{
	eGeoAll,
	eGeoPoint,
	eGeoLine,
	eGeoCircle,
	eGeoCurve,
	eGeoDimension,
	eGeoText,
	eTpLine_IJK,
	eTpRapid,
	eTpCTool,
	eTpLine_ABC,
	eTpRapid_ABC,
	eTpRapid_IJK,
	eTpThread,
	eTpDwell,
	eTp_TC_Unlock_OBS,			// OBSOLETE - changed to a custom feature: "GIB.PI.InterOp TC Unlock"
	eTp_TC_Index_OBS,			// OBSOLETE - changed to a custom feature: "GIB.PI.InterOp TC Index", or may occur as axis move, if turret is modeled in MDD
	eTp_TC_Lock_OBS,			// OBSOLETE - changed to a custom feature: "GIB.PI.InterOp TC Lock"
	eTp_Custom,					// custom feature type
	eTp_PartMove,				// says part was moved
	eTpArc3D,
	eTpArc_IJK,
	eTpSpline_IJK,
	eTpSpiral,
	eTpSpiral_IJK,
	eTp_AxisMove,
	eTp_AxisSynch,				// synch one axis to another, or un-synch it
	eTp_SetNodeSynchPos,		// sets active node synch pos, and sets interpolation axes
	eTp_InitAxisState,			// sets state of axes at beginning of op
	eTp_InitNodeSynchPos,		// node position at beginning of op, for use with eTp_InitAxisState
	eTpArcThread,				// like a thread feature, but moves the tool along a circular arc
	eFt_Hole,					// feature - hole
};

//--hole feature API
typedef enum
{
	gc_eiHfFeatType,
	gc_eiHfFeatCS,
	gc_eiHfFeatRevCS,
	gc_eiHfThroughType,

	gc_efHfAxis = 10,		//requires array of 3 - hvd
	gc_efHfPos,				//requires array of 3 - hvd
	gc_efHfPosTop,			//requires array of 3 0 hvd

	gc_efHfDiam = 30,
	gc_efHfDiamTop,		// Diam2
	gc_efHfDepth,
	gc_efHfMidDepth,
	gc_efHfFullDepth,

	gc_efHfTopClear,
	gc_efHfBottomClear,	//BottomAdjust
	gc_efHfTopZ,			// CP2
	gc_efHfBottomZ,
	gc_efHfPartTop,
	gc_efHfPartBottom,		// Hole Bottom

	gc_efHfChamferWidth,
	gc_efHfChamferAngle,
	gc_efHfTipAngle,

} gc_hfFeatInfo;
//--picking and interrogation
typedef enum
{
	gc_eColorDefault = 0,
	gc_eColorWhite,
	gc_eColorOrange,
	gc_eColorRed,
	gc_eColorMagenta,
	gc_eColorDkBlue,
	gc_eColorBlue,
	gc_eColorCyan,
	gc_eColorGreen,
	gc_eColorDkGreen,
	gc_eColorDkBrown,
	gc_eColorBrown,
	gc_eColorLtGray,
	gc_eColorGray,
	gc_eColorDkGray,
	gc_eColorYellow,
	gc_eColorBlack
}
gc_eColor;

//--feature api: feature evaluators and accessors...
enum gc_eCToolType
{
	gc_eStartFeatureCT = 0,
	gc_eEndFeatureCT,
	gc_eStartPointCT,
	gc_eEndPointCT,
	gc_eToolRPMCT,				// changes tool spindle speed and direction: extra data is gc_trRPMChange2
	gc_eAngMinPrefCT,			// changes the active angle minimization logic: extra data is gc_eRotPref
	gc_eIntraOpConnectCT,		// signals within an op's path that machine dependent connect moves are needed
	gc_eMoveToEvtLocCT,
	gc_eAutoParkEvtCT,
	gc_eSyncPointCT,			// used in multi-turret lathe stroke synching; prog iterator will turn stroke start and end markers into these: extra data is long sync ID
	gc_eDummyFeatureCT =10,
	gc_eCRCOnCT,				// means that crc is enabled over next feature
	gc_eCRCRevCT,				// means that crc is enabled over next feature (side reversed from op's setting)
	gc_eCRCOffCT,				// means that crc is disabled over next feature
	gc_eEndCutOffCT,
	gc_eStartEntryCT,
	gc_eEndEntryCT,
	gc_eFeedPctCT,
	gc_eXYFeedCT,
	gc_eDCPointCT,
	gc_eStartExitMarkCT =20,
	gc_eEndExitMarkCT,
	gc_eStartEntryMarkCT,
	gc_eEndEntryMarkCT,
	gc_eEndJumpCT,
	gc_eNextLevJmpStartCT,
	gc_eRetractJmpStartCT,
	gc_eNextShapeJmpStartCT,
	gc_eOneSurfsStartCT,		// beginning of the toolpath of single surface
	gc_eNextPassStartCT,		// before the first move of the "between the passes" in lace cut
	gc_eNextPassEndCT =30,		// after the last move of the "between the passes" in lace cut
	gc_eCornerMarkCT,
	gc_eOrigStartEntryCT,
	gc_eOrigXYFeedCT,
	gc_eOrigEndEntryCT,
	gc_eConnectStartCT,
	gc_eConnectEndCT,
	gc_eUserFeedCT,				// changes feed rate: Extra Data double feed rate
	gc_eForceRetractCT,			// retract moves will be created at this mark, used in "LoopsByDepth()" & "AddEntryExitToLoops()"
	gc_eOverLapStartCT,			// overLap moves (pocket only) will start after that mark
	gc_eOverLapEndCT =40,		// marks the end of the overLap moves
	gc_eSpringStartCT,			// spring moves (pocket,contour) will start after that mark
	gc_eSpringEndCT,			// marks the end of the spring moves
	gc_eGeoZDeltaCT,			// contains the difference in geometry depth between the end of last feat and the end of this feat (for wrapping): No Data
	gc_ePeriphRampStartCT,
	gc_ePeriphRampEndCT,
	gc_eClearPeriphStartCT,
	gc_eClearPeriphEndCT,
	gc_eRetractStartCT,			// marks the beginning of a retract sequence (temporary AND final paths): No Data
	gc_eRetractEndCT,			// marks the end of a retract sequence (temporary AND final paths): No Data
	gc_eStrokeEntryCT=50,		// marks the start of the entry to a tp stroke (for lathe stroke synchronization): No Data
	gc_eStrokeStartCT,			// marks the start of a tp stroke (for lathe stroke synchronization): No Data
	gc_eStrokeEndCT,			// marks the end of a tp stroke (for lathe stroke synchronization): No Data
	gc_eLatheRPMCT,				// changes lathe spindle speed and direction: Extra Data gc_trRPMChange2
	gc_eSpindleModeCT,			// so prog iterator can track mill and lathe modes (mill-turn machines): extra data is gc_trSpindleMode
	gc_eRLevelCT,				// Used for multi retract level drilling
	gc_eTCPModeCT,				// so prog iterator can track toolgroup Tip Center Programing (rotary head machines): extra data is gc_trTCPMode
	gc_SpindleLinkOnCT,			// tells prog iterator that 2 spindles are linked together
	gc_SpindleLinkOffCT,		// tells the prog iterator that 2 spindles are now not linked.
	gc_CSSChangeCT,				// changes prog itr css settings
};

//--profiler marker
typedef enum		// Profiler Marker Tools
{
	gc_eSFTool,
	gc_eEFTool,
	gc_eSPTool,
	gc_eEPTool
} gc_teSTool;
//--curve
enum
{
	gc_eCurveLine = 0,
	gc_eCurveCircle,
	gc_eCurveEllipse,
	gc_eCurveBSpline
};

typedef enum		// Spun Outline Algorithms
{
	gc_eSpunAlgCurrent,		// Use Current Spun Outline Algorithm (Default)
	gc_eSpunAlg_PS_24_1,	// Use PS 24.1 Spun Outline Algorithm
	gc_eSpunAlg_PS_24_0,	// Use PS 24.0 Spun Outline Algorithm
	gc_eSpunAlg_PS_23_1,	// Use PS 23.1 Spun Outline Algorithm
	gc_eSpunAlg_PS_23_0,	// Use PS 23.0 Spun Outline Algorithm
	gc_eSpunAlg_PS_22_0		// Use PS 22.0 Spun Outline Algorithm (Oldest)
} gc_teSpunOutlineAlgorithm;

//STRUCTURE
// for moving custom and standard axes...

struct gc_kNodeID
{
	enum Type
	{
		root, mdd_axis, mdd_tg, mdd_wp, mdd_util_comp, mdd_tool_pos,
		vnc_tool, vnc_part_cs, vnc_tool_touch_off, vnc_holder_attach,
		dynamic_node_type, num_node_types
	};
	
	Type type;
	int val1;		// used for all types
	int val2;		// only used if type == mdd_tool_pos
	
	gc_kNodeID()									: type(dynamic_node_type), val1(-1), val2(0) {}
	gc_kNodeID(Type the_type, int v1, int v2 = 0)	: type(the_type), val1(v1), val2(v2) {}
};

struct gc_InterpSet
{
	gc_kNodeID datum;
	gc_kNodeID ref;
	gc_kNodeID axes[5];			// up to 3 linear axes, and up to 2 rotary axes
};

struct gc_AxisCategorySet
{
	enum Axes {none, spindle_rot, all_rot};

	Axes ref_axes;
	Axes datum_axes;

	gc_AxisCategorySet()			: ref_axes(none), datum_axes(none) {}
};

// gc_kNodePos is used to set a "target" node-relative position (and orientation) that a "tool" node will try to achieve.
// At any given time, a node can target at most one other node.
// A prog iterator sets these automatically when processing cutting ops, and when approaching cutting ops.

struct gc_kNodePos
{
	enum Type {none, pos_only, orient_1_axis, full_orient, num_types};
	
	Type type;
	double pos[3];
	double axis1[3];				// valid if (type == orient_1_axis) || (type == full_orient)
	double axis2[3];				// valid if (type == full_orient)
	gc_InterpSet interp_set;		// ids of nodes involved, and axes to be used to achieve pos
	gc_AxisCategorySet zeroed;		// what node rotary axes be zeroed when interpreting pos (& axis1 & axis2)?
	
	gc_kNodePos()					: type(none) {}
};

//--feat combiner api...

struct gc_CombineFeatParams
{
	enum {cur_vers = 1};
	
	enum AttrMergeType
	{
		merge_attrs,
		dont_merge_attrs
	};

	int version;
	AttrMergeType merge_type;
	double lin_tol;				// <= 0 for default (5e-5 inches)
	double ang_tol;				// <= 0 for default (about 1.49e-5 degrees)

	gc_CombineFeatParams(AttrMergeType merge = dont_merge_attrs, double lintol = 0.0, double angtol = 0.0)
		: version(cur_vers), merge_type(merge), lin_tol(lintol), ang_tol(angtol) {}
		
	gc_CombineFeatParams(double lintol, double angtol = 0.0)
		: version(cur_vers), merge_type(dont_merge_attrs), lin_tol(lintol), ang_tol(angtol) {}
};

class gc_FeatCombiner;
//--shape api
struct gc_GeoShape
{
	enum {cur_vers = 1};
	
	enum ParamDir {forward, reverse};
	
	struct Pos
	{
		int ref;
		double param;
		
		Pos()					: ref(-1), param(0.0) {}
		Pos(int geo, double t)	: ref(geo), param(t) {}
	};
	
	int version;
	Pos start;
	Pos end;
	ParamDir start_ref_dir;
	
	gc_GeoShape()	: version(cur_vers), start_ref_dir(forward) {}
};
//--feat api

struct gc_Arc3D
{
	double cp[3];
	double sp_vec[3];
	double axis[3];
	double angle;
	double helix_depth;
};

struct gc_Spiral
{
	double cp[3];
	double axis[3];
	double zero_vec[3];	// spiral angles measured from this vec (radius of spiral is zero_rad at zero degrees)
	double zero_rad;	// radius of the spiral at zero degrees
	double r_delta;		// change in radius for 360 degrees (cannot be zero!)
	double pitch;		// change in depth for 360 degrees
	double shift_0;		// point at angle 0 is shifted by this amount along cross(axis, ang_vec(t))
	double shift_delta;	// change in shift for 360 degrees
	double start_angle;	// defines start point (t == 0); start_angle must be <= end_angle
	double end_angle;	// defines end point (t == 1); end_angle must be >= start_angle
};

// gc_AxisMoveRec DEPRECATED!!  Use gc_AxisMoveRec2 for moving custom and standard axes...

struct gc_AxisMoveRec
{
	enum Type {absolute, incremental};
	
	char name[32];
	Type type;
	double val;
	double max_step;		// largest step of this axis, <=0 for infinite
	double max_feed;		// units per minute, <=0 for infinite
};

struct gc_AxisMoveRec2
{
	enum Type {abs_val, inc_val, short_rot, node_pos, num_types};
	
	char name[32];
	Type type;
	double val;				// used if (type != node_pos)
	gc_kNodeID datum_node;	// used if (type == node_pos)
	double max_step;		// largest step of this axis, <=0 for infinite
	double max_feed;		// units per minute, <=0 for infinite
	
	gc_AxisMoveRec2()		: type(inc_val), val(0.0), max_step(0.0), max_feed(0.0) { name[0] = 0; }
};

// gc_MachAxisBools is a bit field where each bit represents an axis in an "interpolation set" (X, Y, Z, A, B and C)
struct gc_MachAxisBools
{
	int val;
	
	gc_MachAxisBools()		: val(0) {}
};

enum gc_AxisSynchType
{
	gc_ePhysicalAxisSynch,		// axis moves in the same physical direction as the ref_axis, regardless of polarity; e.g. when ref_axis goes left, so does axis
	gc_ePositiveAxisSynch,		// axis goes positive if ref_axis goes positive, negative if ref_axis goes negative
	gc_eNegativeAxisSynch,		// axis goes negative if ref_axis goes positive, positive if ref_axis goes negative
	gc_eAxisSynchOff,
	gc_eNumAxisSynchTypes		// must be last
};

struct gc_SyncID
{
	int main_id;
	int sub_id;

	gc_SyncID()						: main_id(0), sub_id(0) {}
	gc_SyncID(int main, int sub)	: main_id(main), sub_id(sub) {}
};

//DECLARATIONS
//--attributes
GC_API int gc_AddGeoAttList(int iRef, void **attlist);
GC_API int gc_GetGeoAttList(int iRef, void **attlist);
GC_API int gc_DeleteGeoAttList(int iRef);
GC_API int gc_GetGeoAttrColor(int iRef, double *pRGB);
GC_API int gc_SetGeoAttrColor(int iRef, double *pRGB);
GC_API int gc_GetGeoAttrLayer(int iRef, char *pLayer);
GC_API int gc_SetGeoAttrLayer(int iRef, char *pLayer);
//--geometry creation
GC_API int gc_CreatePoint(double *pt, int bRedraw);
GC_API int gc_CreateLine(double *p1, double *p2, int bRedraw);
GC_API int gc_CreateLineEx(double *p1, double *p2, int bExtend, int bRedraw);
GC_API int gc_CreateCircle(double *pt, double rad, int bRedraw);
GC_API int gc_CreateCurve(int degree, int n_knots, int n_ctrls, int *k_mult, double *k_param, double *ctrls, int bRedraw);
GC_API int gc_CreatePolyLine(int iPnts, double *dPts);
GC_API int gc_CreateShape(int iNum, double *dPts);
GC_API int gc_CreateShape3d(int iNum, double *dPts);
GC_API int gc_GetBulgeToCR(double *dP1, double *dP2, double dBulge, double *dCenter, double *dRad);
GC_API int gc_LengthParametrizeCurve(int degree, int n_knots, int n_ctrls, int *k_mult, double *k_param, double *ctrls);
//--shape
GC_API int gc_SetShapesList(int iNumShapes, void **pPath);
GC_API int gc_BuildSelectedShapesList(int iClosedShapes, int iOpenShapes, int *iNumShapes);
GC_API int gc_DeleteSelectedShapesList();
GC_API int gc_GetNumSelShape(int *iNumShape);
GC_API int gc_GetSelShapeNumFeat(int iShape, int *iNum);
GC_API int gc_GetSelShapeFeatType(int iShape, int iFeat, int *iFeatType);
GC_API int gc_GetSelShapePoint(int iShape, int iFeat, double *pt);
GC_API int gc_GetSelShapeLine(int iShape, int iFeat, double *p1, double *p2);
GC_API int gc_GetSelShapeCircle(int iShape, int iFeat, double *dCenter, double *dRad);
GC_API int gc_GetSelShapeArcEnds(int iShape, int iFeat, double *dStart, double *dEnd, int *iDirCCW);
GC_API int gc_GetSelShapeArcAngles(int iShape, int iFeat, double *dStartAng, double *dEndAng);
GC_API int gc_EvalSelShapePoint(int iShape, int iFeat, int iCS, double dParam, double *dPoint);
GC_API int gc_EvalSelShapeTangent(int iShape, int iFeat, int iCS, double dParam, double *dTangent);
GC_API int gc_IsSelShapeCW(int iShape);
GC_API int gc_GetSelShapeFeatLen(int iShape, int iFeat, double *dLen);
GC_API int gc_GetSelShapePath(int iShape, void **ptrPath);
GC_API int gc_ReverseSelShape(int iShape);
GC_API int gc_UpdateSelectedShapes(int iClosedShapes, int iOpenShapes, int *iNumShapes);
GC_API int gc_UpdateSelectedShapesEx(int iClosedShapes, int iOpenShapes, int iEndPoint, int *iNumShapes);
GC_API int gc_SetSelShapeInfoD(int iIndex, int id, double *dVal);
GC_API int gc_SetSelShapeInfoI(int iIndex, int id, int *iVal);
GC_API int gc_GetSelShapeInfoD(int iIndex, int id, double *dVal);
GC_API int gc_GetSelShapeInfoI(int iIndex, int id, int *iVal);
GC_API int gc_SetShapeInfo( int iShape, int iDir, int iToolSide, int bUseLimits, int iStartFeat,
						   double dStartParam, int iEndFeat, double dEndParam, int iSingleFeat );
GC_API int gc_SetShapeInfoEx( int iShape, int iDir, int iToolSide, int bUseLimits, int iStartRef,
							double dStartParam, int iEndRef, double dEndParam, int iSingleFeat );
GC_API int gc_BuildSelShapePath(int iIndex, void **ptrPath);
//--toggle feed status
GC_API int gc_GetGeoLineFeedStatus(int iRef, int *iStatus);
GC_API int gc_SetGeoLineFeedStatus(int iRef, int iStatus);
//--edit geometry
GC_API int gc_EditPoint(int iRef, double *dPt, int iRedraw);
GC_API int gc_EditLine(int iRef, double *dPt1, double *dPt2, int iRedraw);
GC_API int gc_EditCircle(int iRef, double *dPt, double dRad, int iRedraw);
GC_API int gc_EditCurve(int iRef, int iDegree, int iKnots, int iCtrls, int *piMult, double *dParam, double *dCtrls, int iRedraw);
//--geometry selection
GC_API int gc_SelectAllGeometry ( void );
GC_API int gc_GetNumGeoSel(int iType, int *iNum);
GC_API int gc_ResetGeoSel(int iType);
GC_API int gc_ResetGeoSelMode(int iMode);		// iterate through geometry selected with given mode
GC_API int gc_GetNextGeoSel(int *iRef);
GC_API int gc_ClearGeoSel(int iRedraw);
GC_API int gc_ClearGeoSelEx(int iSelMode, int iRedraw);
GC_API int gc_AddGeoSel(int iRef, int iRedraw);
GC_API int gc_AddGeoSelEx(int iRef, int iMode, int iRedraw);
GC_API int gc_RemoveGeoSel(int iRef, int iRedraw);
GC_API int gc_AddGeoConnectListSel(int iRef, int iRedraw);
GC_API int gc_GetGeoRefSelectionMode(int ref, int *mode);
GC_API int gc_GeoSelAll(int iType, int iRedraw);
GC_API int gc_DupSelFeats(int iSrcWG, int iDstWG);
GC_API int gc_UpdateUISel( void );
GC_API int gc_GetNumPoints(int *iNum);
GC_API int gc_GetPointList(int *iList);
GC_API int gc_GetNumLines(int *iNum);
GC_API int gc_GetLineList(int *iList);
GC_API int gc_GetNumCircles(int *iNum);
GC_API int gc_GetCircleList(int *iList);
GC_API int gc_GetNumCurves(int *iNum);
GC_API int gc_GetCurveList(int *iList);
GC_API int gc_GetGeoType(int iRef, int *iType);
GC_API int gc_GetGeoLabel(int iRef, char *label);
GC_API int gc_GetGeoCS(int iRef, int *iCS);
GC_API int gc_SetGeoCS(int iRef, int iCS, int bXYZ);
GC_API int gc_GetGeoPoint(int iRef, int iCS, double *pt);
GC_API int gc_GetGeoLine(int iRef, int iCS, double *p1, double *p2);
GC_API int gc_GetGeoLineConAngle(int iRef, int iCS, double *pdAngle);
GC_API int gc_GetGeoCircle(int iRef, int iCS, double *dCenter, double *dRad);
GC_API int gc_GetGeoCircleDir(int iRef, int iCS, int *iDirCCW);
GC_API int gc_GetGeoArcEnds(int iRef, int iCS, double *dStart, double *dEnd, int *iDirCCW);
GC_API int gc_GetGeoArcAngles(int iRef, int iCS, double *dStartAng, double *dEndAng);
GC_API int gc_ToggleArcDir(int iRef);
GC_API int gc_GetGeoCurve(int iRef, int *degree, int *n_knots, int *n_ctrls);
GC_API int gc_GetGeoCurveParams(int iRef, double *dStartPrm, double *dEndPrm);
GC_API int gc_GetGeoCurveData(int iRef, int iCS, int *k_mult, double *k_param, double *ctrls);
GC_API int gc_GetGeoBaseCurve(int iRef, int *degree, int *n_knots, int *n_ctrls);
GC_API int gc_GetGeoBaseCurveData(int iRef, int iCS, int *k_mult, double *k_param, double *ctrls);
GC_API int gc_DeleteGeo(int iRef);
GC_API int gc_GetGeoCircleNorm(int iRef, int iCS, double *dCenter, double *dPtNorm);
GC_API int gc_EvalGeoPoint(int iRef, int iCS, double dParam, double *dPoint);
GC_API int gc_EvalGeoTangent(int iRef, int iCS, double dParam, double *dTangent);
GC_API int gc_UpdateProcessesFromSelection();
/** gc_GetGeoLength
*Used to get the length of a geometry feature
*
*@param	iRef	API reference of a geometry feature
*@param	len		The length of that feature is returned
*@return		0 for success, - 1 if it's a bad ref
*/
GC_API int gc_GetGeoLength(int iRef, double *len);
GC_API int gc_Redraw();
GC_API int gc_AllowRedraw(int bRedraw);
GC_API int gc_TriggerRedraw();
GC_API int gc_ShrinkWrap(void);
GC_API int gc_ShrinkWrapVisible(void);

GC_API int gc_SegmentSplines( double dAccur, int bLines, int bVisWGs );
//--picking and interrogation
GC_API int gc_PickGeoSol( int bScreenCoords, int iPosX, int iPosY, int *iRef, int *iSolid, gc_TopoId *FeatureRef,
						  bool bMultiSel = false, bool bInterrogate = false);
GC_API int gc_InterrogateGeo(int xyLocal[2]);
GC_API int gc_IsGeoConnected(int iRef);
GC_API int gc_GetGeoConnect(int iRef, int *iRefConnect1, int *iRefConnect2);
GC_API int gc_SetGeoConnect(int iRef, int iRefConnect1, int iRefConnect2);
GC_API int gc_ConnectFeats(int iRef1, int iRef2, int iPtRef);
GC_API int gc_IsGeoFree(int iRef);
GC_API int gc_IsGeoTerminator(int iRef);
GC_API int gc_GetGeoConnectList(int iRef, int *iNum, int *iList);
GC_API int gc_GetGeoList(int iRef, int *iNum, int *iList);
GC_API int gc_GetNumGeoConnect(int iRef, int *iNum);
GC_API int gc_GetGeoHidden(int iRef, int *pbHidden);
GC_API int gc_SetGeoHidden(int iRef, int bHidden);
GC_API int gc_SetGeoAir(int iRef, int bIsAir);
GC_API int gc_GetGeoAir(int iRef, int *bIsAir);
GC_API int gc_GetGeoColor(int iRef, gc_eColor *peColor);
GC_API int gc_SetGeoColor(int iRef, gc_eColor eColor);

//--shape api

GC_API int gc_GeoShapeToPath(const gc_GeoShape &shape, int iCS, void **path);	// if iCS == 0, will use current cs

//--points api

GC_API int gc_FeatPointsCount(void *point_list, int *count);
GC_API int gc_FeatPointsDelete(void *point_list);
GC_API int gc_GetFeatPoint(const void *point_list, int iIndex, double *pt, double *param);	// "pt" and/or "param" may = nullptr
GC_API int gc_GetFeatPoint2(const void *point_list, int iIndex, double *pt, double *param, double *d_axis, double *h_axis);	// any of the outputs may = nullptr

//--feature api

GC_API int gc_CopyFeat(const void *src_feat, void **dst_feat);
GC_API int gc_ClearFeat(void *feat);
GC_API int gc_TransformFeat(void *feat, const double *dMatrix);
GC_API int gc_ReverseFeat(void *feat);
GC_API int gc_TrimFeat(void *feat, double t, bool upper_bound);
GC_API int gc_GetFeatSliceParams(const void *feat, const double *origin, const double *norm, int &n_solns, double *soln_vec, int max_solns);
GC_API int gc_DeleteFeat(void *feat);
GC_API int gc_CreateFeatPoints(const void *feat, double tol, void **point_list);	// tol <= 0 means use default. won't wrap points if wrapped rotary feature
GC_API int gc_CreateFeatPoints2(const void *feat, double tol, void **point_list);	// will wrap points if wrapped rotary feature

//--feature api: feature evaluators and accessors...

GC_API int gc_EvalFeat(const void *feat, double xParam, double *point, double *axis);
GC_API int gc_EvalFeat2(const void *feat, double xParam, double *point, double *axis, double *h_axis);	// h_axis needed for orientation of lathe tools
GC_API int gc_EvalFeatPoint(const void *feat, double xParam, double *point);
GC_API int gc_EvalFeatTlAxis(const void *feat, double xParam, double *axis);
GC_API int gc_EvalFeatTlHAxis(const void *feat, double xParam, double *h_axis);		// h_axis needed for orientation of lathe tools
GC_API int gc_EvalFeatTangent(const void *feat, double xParam, double *tan);		// doesn't work for rotary feature types
GC_API int gc_GetFeatLength(const void *feat, double *dLen);
GC_API int gc_GetFeatType(const void *feat, int *iType);
GC_API int gc_GetFeatName(const void *feat, char *sName);
GC_API int gc_GetFeatAtt(const void *feat, int iAttType, int *iFeatAtt);
GC_API int gc_GetFeatRef(const void *feat, int *iRef, int *iCorn);
GC_API int gc_GetFeatCS(const void *feat, int *piCS);
GC_API int gc_GetFeatWrapped(const void *feat, int *pbWrapped, double *pdStartDepth, double *pdEndDepth);
GC_API int gc_GetFeatPolar(const void *feat, int *pbPolar, int *pbNegSide = NULL);
GC_API int gc_GetFeatEnds(const void *feat, double *p1, double *p2);
GC_API int gc_GetFeatSP(const void *feat, double *pt);
GC_API int gc_GetFeatEP(const void *feat, double *pt);
GC_API int gc_GetFeatCircle(const void *feat, double *cp, double *rad, int *bDirCCW);
GC_API int gc_GetFeatArcAngles(const void *feat, double *dStartAng, double *dEndAng);
GC_API int gc_GetFeatArc3D(const void *feat, gc_Arc3D *arc_def);
GC_API int gc_GetFeatSpiral(const void *feat, gc_Spiral *spiral_def);
GC_API int gc_GetFeatCurve(const void *feat, int *degree, int *n_knots, int *n_ctrls);
GC_API int gc_GetFeatCurveData(const void *feat, int *k_mult, double *k_param, double *ctrls);
GC_API int gc_GetFeatCurveIJK(const void *feat, void **loc_feat = NULL, void **guide_feat = NULL);
GC_API int gc_GetFeatABCEnds(const void *feat, double *abc1, double *abc2);
GC_API int gc_GetFeatABCContext(const void *feat, int *tool, int *wp, int *tcp_on);
GC_API int gc_GetFeatABCStartUnknownAxes(const void *feat, gc_MachAxisBools &unknown);
GC_API int gc_GetFeatABCEndUnknownAxes(const void *feat, gc_MachAxisBools &unknown);
GC_API int gc_GetFeatABCLinAxisStartUnknown(const void *feat, int axis, int *pbUnknown);
GC_API int gc_GetFeatABCRotAxisStartUnknown(const void *feat, int axis, int *pbUnknown);
GC_API int gc_GetFeatABCLinAxisEndUnknown(const void *feat, int axis, int *pbUnknown);
GC_API int gc_GetFeatABCRotAxisEndUnknown(const void *feat, int axis, int *pbUnknown);
GC_API int gc_GetFeatCTool(const void *feat, gc_eCToolType *peType, double *dLoc=NULL, void *data=NULL);
GC_API int gc_GetFeatSync(const void *feat, gc_SyncID *id, bool *postable);
GC_API int gc_GetFeatDwell(const void *feat, int *pbRevs, double *pxDwell);
GC_API int gc_GetFeatPartMove(const void *feat, int *piFromWP, int *piToWP, double *pos, double *d_axis, double *h_axis);
GC_API int gc_GetFeatCustom(const void *feat, char *sName, double *axParams, double *pxTime, double *pxLength, int *piDataSize);
GC_API int gc_GetFeatCustomData(const void *feat, char *pData);
GC_API int gc_GetFeatCustomFieldInfo(const void *feat, char *sFieldName, int *piSize, int *piOffset, int *piEnabled);
GC_API int gc_GetFeatCustomFieldData(const void *feat, char *sFieldName, void *pData);
GC_API int gc_GetFeatAxisMove(const void *feat, double *pxTime, int *piAxes);
GC_API int gc_GetFeatAxisMoveData2(const void *feat, gc_AxisMoveRec2 *axes);
GC_API int gc_GetFeatAxisSynch(const void *feat, gc_AxisSynchType *type, char *axis, char *ref_axis);
GC_API int gc_GetFeatSetNodePos(const void *feat, gc_kNodePos &pos);
GC_API int gc_GetFeatParam(const void *feat, const double *pt, double &param);

//--feature api: feature creation...

GC_API int gc_CreateEmptyFeat(void **feat);
GC_API int gc_SetFeatAtt(void *feat, int iAttType, int iFeatAtt);
GC_API int gc_SetFeatRef(void *feat, int iRef, int iCorn);
GC_API int gc_SetRawFeatRef(void *feat, int iRef, int iCorn);
GC_API int gc_SetFeatPoint(void *feat, const double pt[3]);
GC_API int gc_SetFeatLine(void *feat, const double p1[3], const double p2[3], int iType = 1);
GC_API int gc_SetFeatCircle(void *feat, const double p1[3], const double p2[3], const double cp[3], double rad, int bDirCCW);
GC_API int gc_SetFeatArcThread(void *feat, const double p1[3], const double p2[3], const double cp[3], double rad, int bDirCCW);
GC_API int gc_SetFeatArc3D(void *feat, const gc_Arc3D *arc_def);
GC_API int gc_SetFeatSpiral(void *feat, const gc_Spiral *spiral_def);
GC_API int gc_SetFeatCurve(void *feat, int degree, int n_knots, int n_ctrls, const int *k_mult, const double *k_param, const double *ctrls);
GC_API int gc_SetFeatLineIJK(void *feat, const double p1[3], const double ijk1[3], const double p2[3], const double ijk2[3], int iType = 1);
GC_API int gc_SetFeatArcIJK(void *feat, const gc_Arc3D *arc_def, const double ijk1[3], const double ijk2[3]);
GC_API int gc_SetFeatSpiralIJK(void *feat, const gc_Spiral *spiral_def, const double ijk1[3], const double ijk2[3]);
GC_API int gc_SetFeatCurveIJK(void *feat, const void *loc_feat, const void *guide_feat);
GC_API int gc_SetFeatLineABC(void *feat, const double p1[3], const double abc1[3], const double p2[3], const double abc2[3], int tool, int wp, int tcp_on, int iType);
GC_API int gc_SetFeatABCEnds(void *feat, const double *abc1, const double *abc2);
GC_API int gc_SetFeatABCStartUnknownAxes(void *feat, gc_MachAxisBools unknown);
GC_API int gc_SetFeatABCEndUnknownAxes(void *feat, gc_MachAxisBools unknown);
GC_API int gc_SetFeatABCLinAxisStartUnknown(void *feat, int axis, int bUnknown);
GC_API int gc_SetFeatABCRotAxisStartUnknown(void *feat, int axis, int bUnknown);
GC_API int gc_SetFeatABCLinAxisEndUnknown(void *feat, int axis, int bUnknown);
GC_API int gc_SetFeatABCRotAxisEndUnknown(void *feat, int axis, int bUnknown);
GC_API int gc_SetFeatCTool(void *feat, gc_eCToolType eType, const double *dLoc = NULL, const void *data = NULL);
GC_API int gc_SetFeatSync(void *feat, gc_SyncID id, bool postable);
GC_API int gc_SetFeatDwell(void *feat, int bRevs, double xDwell);
GC_API int gc_SetFeatPartMove(void *feat, int iFromWP, int iToWP,
				const double pos[3], const double d_axis[3], const double h_axis[3]);
GC_API int gc_SetFeatCustom(void *feat, const char *sName, const double axParams[2],
				double xTime, double xLength, int iDataSize = 0, const char *pData = NULL);
GC_API int gc_SetFeatAxisMove2(void *feat, double xTime, int iAxes, const gc_AxisMoveRec2 *axes);	// if time > 0, used as feature's time (in minutes)
GC_API int gc_SetFeatAxisSynch(void *feat, gc_AxisSynchType type, const char *axis, const char *ref_axis);		// type == gc_eAxisSynchOff, ref_axis can be NULL
GC_API int gc_SetFeatSetNodePos(void *feat, const gc_kNodePos &pos);
GC_API int gc_SetFeatInitAxisState(void *feat, int iAxes, const gc_AxisMoveRec2 *axes);
GC_API int gc_SetFeatInitNodePos(void *feat, const gc_kNodePos &pos);
GC_API int gc_ConvertFeatToCurve(void *feat);
/* DEPRECATED */ GC_API int gc_SetFeatAxisMove(void *feat, double xTime, int iAxes, const gc_AxisMoveRec *axes);	// if time > 0, used as feature's time (in minutes)

//--hole feature API
/** gc_HFLoadGroupInfo
*This function will find the Hole Feature associated with a given workgroup
*
*@param		int iWG: workgroup to load data for
*@param		void **pGroupData: pointer to memory to hold data, this will be allocated from within GibbsCAM and must be released calling gc_HFFreeGroupInfo
*@return	0= success, -1= no Hole Feature data for the workgroup, -2= data failed to load - have the user reload the data through the interface, -3= size mismatch  - have the user reload the data through the interface, -22 = Hole Feature module is not available
*/
GC_API int gc_HFLoadGroupInfo(const int iWg, void **pGroupData);

/** gc_HFFreeGroupInfo
*This function frees memory that was allocated in gc_HFLoadGroupInfo
*
*@param		void **pGroupData: pointer to memory to free
*@return	0= success, -22 = Hole Feature module is not available
*/
GC_API int gc_HFFreeGroupInfo(void *pGroupData);

/** gc_HFGetNumGroup
*This function retrieves the number of groups in this particular Hole Feature set
*
*@param		void **pGroupData: data retrieved by gc_HFLoadGroupInfo
*@param		int *iNum: pointer to hold the number of groups
*@return	0= success, -1= iNum is NULL, -22 = Hole Feature module is not available
*/
GC_API int gc_HFGetNumGroup(void *pGroupData, int *iNum);

/** gc_HFGetGroupNumFeat
*This function retrieves the number of features in a given group
*
*@param		void **pGroupData: data retrieved by gc_HFLoadGroupInfo
*@param		int iGroup: group to get number of features ( number of groups retrieved by gc_HFGetNumGroup )
*@param		int *iNum: pointer to hold the number of features
*@return	0= success, -1= pGroupData is NULL, -2= iGroup is not in the data set, -3 = iNum is NULL, -22 = Hole Feature module is not available
*/
GC_API int gc_HFGetGroupNumFeat(void *pGroupData, const int iGroup, int *iNum);

/** gc_HFGetGroupFeatList
*This function retrieves the number of features in a given group
*
*@param		void **pGroupData: data retrieved by gc_HFLoadGroupInfo
*@param		int iGroup: group to get number of features ( number of groups retrieved by gc_HFGetNumGroup )
*@param		int *iList: pointer to hold the list of features in the group
*@return	0= success, -1= pGroupData is NULL, -2= iGroup is not in the data set, -3 = iList is NULL, -22 = Hole Feature module is not available
*/
GC_API int gc_HFGetGroupFeatList(void *pGroupData, const int iGroup, int *iList);

/** gc_HFGetFeatInfoI
*This function retrieves an integer value from the feature
*
*@param		int iFeatRef: GeoRef of a point or circle, use the Features retrieved from gc_HFGetGroupFeatList or any point / circle, an error will be returned if no data exists
*@param		int iId: see gc_hfFeatInfo
*@param		int *piData: pointer to hold integer data
*@return	0= success, -10 through -14= cannot load data for feature, -1= invalid iId value, -2 piData is NULL, -22 = Hole Feature module is not available
*/
//GC_API int gc_HFGetFeatInfoI(const int iFeatRef, const int iId, int *piData);

/** gc_HFGetFeatInfoD
*This function retrieves an double value from the feature
*
*@param		int iFeatRef: GeoRef of a point or circle, use the Features retrieved from gc_HFGetGroupFeatList or any point / circle, an error will be returned if no data exists
*@param		int iId: see gc_hfFeatInfo
*@param		double *pdData: pointer to hold integer data
*@return	0= success, -10 through -14= cannot load data for feature, -1= invalid iId value, -2 pdData is NULL, -22 = Hole Feature module is not available
*/
//GC_API int gc_HFGetFeatInfoD(const int iFeatRef, const int iId, double *pdData);

/** gc_HFGetFeatInfoS
*This function retrieves a character ( string ) value from the feature
*
*@param		int iFeatRef: GeoRef of a point or circle, use the Features retrieved from gc_HFGetGroupFeatList or any point / circle, an error will be returned if no data exists
*@param		int iId: see gc_hfFeatInfo
*@param		char *psData: pointer to hold character data
*@return	0= success, -10 through -14= cannot load data for feature, -1= invalid iId value, -2 piData is NULL, -22 = Hole Feature module is not available
*/
//GC_API int gc_HFGetFeatInfoS(const int iFeatRef, const int iId, char *psData);

/** gc_HFGetHfrSol
*This function, for a given workgroup, will find the solid ( if any ) with Hole Features
*
*@param		int *iSol: pointer to hold Solid ID
*@param		int *iState: pointer to hold the bagged/unbagged status ( 1 = bagged, 0 = unbagged )
*@return	0= success, -1= no Hole Feature data for the workgroup, -2= No Solid found ( deleted? ), -3= No Match, -22 = Hole Feature module is not available 
*/
GC_API int gc_HFGetHfrSol(const int iWg, int *iSol, int *iState); 

/** gc_HFReverseHole
*This function reverses the given hole's direction
*A redraw will be needed; it is not performed automatically (use gc_Redraw)
*
*@param		int iFeatRef: GeoRef of a point, use the Features retrieved from gc_HFGetGroupFeatList or any point / circle, an error will be returned if no data exists
*@return	0=success, -1=reversal failed (perhaps blind hole?), -2=feature save failed, -10 through -14=cannot load data for feature, -22 = Hole Feature module is not available 
*/
GC_API int gc_HFReverseHole(const int iFeatRef);

/** gc_HFSetHoleWG
*This function sets the Geo Ref and WG (if WG > 0) for the given hole
*
*@param		int iFromRef: GeoRef of a point, use the Features retrieved from gc_HFGetGroupFeatList or any point / circle, an error will be returned if no data exists
*@return	0=success, -1=failed, -2=feature save failed, -10 through -14=cannot load data for feature, -22 = Hole Feature module is not available 
*/
GC_API int gc_HFChangeHoleWG(const int iFromRef, const int iFromWG, const int iToRef, const int iToWG);

/** gc_HFCopyPaste
*This function must be called at the start and end of any copy/paste operation
*so that the hole manager can keep track of hole features being copied
*
*@param		int iAction, 11=start of copy, 12=end of copy, 21=start of paste, 22=end of paste
*@return	0=success, -1=failed
*/
GC_API int gc_HFCopyPaste(const int iAction);

/** gc_HFGetNumFeat
*This function will return the number of features on the main dialog
*
*@param		int *iNumFeat = number of features (holes)
*@return	0=success, -1=failed
*/
GC_API int gc_HFGetNumFeat(int *iNumFeats);

/** gc_HFGetFeatSelected
*This function will check if a hole feature is selected
*
*@param		int iFeat = feature number
*@param		int *iSelected, 1=selected, 0=deselected
*@return	0=success, -1=failed
*/
GC_API int gc_HFGetFeatSelected(const int iFeat, int *iSelected);

/** gc_HFSetFeatSelected
*This function will select or deselect a hole feature
*
*@param		int iFeat = feature number
*@param		int iSelected, 1=selected, 0=deselected
*@return	0=success, -1=failed
*/
GC_API int gc_HFSetFeatSelected(const int iGroup, const int iSelected);

/** gc_HFGetNumGroups
*This function will return the number of groups on the main dialog
*
*@param		int *iNumGroups = number of groups
*@return	0=success, -1=failed
*/
GC_API int gc_HFGetNumGroups(int *iNumGroups);

/** gc_HFGetGroupSelected
*This function will check if a group is selected
*
*@param		int iGroup = group number
*@param		int *iSelected, 1=selected, 0=deselected
*@return	0=success, -1=failed
*/
GC_API int gc_HFGetGroupSelected(const int iGroup, int *iSelected);

/** gc_HFSetGroupSelected
*This function will select or deselect a group
*
*@param		int iGroup = group number
*@param		int iSelected, 1=selected, 0=deselected
*@return	0=success, -1=failed
*/
GC_API int gc_HFSetGroupSelected(const int iGroup, const int iSelected);

/** gc_HFCreateGroup
*This function will create a new group from the selected hole features
*
*@param		char *sName = group name
*@param		int *iGroup = number of new group
*@return	0=success, -1=failed
*/
GC_API int gc_HFCreateGroup(const char *sName, int *iGroup);

/** gc_HFCheckPart
*This function is used to check the validity of a part by comparing the face attributes with
*hole feature point attributes. any faces that have attributes relating to hole features that
*do not exist will have those face attributes removed
*
*@param		int iSolids 0=check all solids, 1=check selected solids, 2=check given solid ref
*           int iSolRef=solid to check (if iSolids=2)
*           int *iNumHoleFeats=number of hole features (points) found
*           int *iNumErrors=number of faces with attribute errors\
*           int *iNumFixed=number of faces with errors that were fixed
*           char *sMessage=message to show number of errors and number fixed
*@return	0=success, other=failed
*/
GC_API int gc_HFCheckPart(int iSolids, int iSolRef, int *iNumHoleFeats, int *iNumErrors, int *iNumFixed, char *sMessage);
GC_API int gc_HFReloadHoleData(int iHoleNum);

GC_API int gc_HFGeoRefToFeatureID(int iGeoRef);
GC_API int gc_HFFeatureIDToGeoRef(int iFeatureID);

GC_API int gc_HFGetFirstSelDrillFeature(int *iFeatureID);
GC_API int gc_HFOpenFileCallback();

//--feat combiner api...
GC_API int gc_CombinerCreate(void *path, const gc_CombineFeatParams &params, gc_FeatCombiner **combiner);
GC_API int gc_CombinerAddFeat(gc_FeatCombiner *combiner, const void *feat);
GC_API int gc_CombinerEmpty(const gc_FeatCombiner *combiner, int *empty);
GC_API int gc_CombinerEP(const gc_FeatCombiner *combiner, double *ep);
GC_API int gc_CombinerFlush(gc_FeatCombiner *combiner);
GC_API int gc_CombinerDelete(gc_FeatCombiner *combiner);
//--combine combinable features...
GC_API int gc_CombinePath(const void *src_path, void *dst_path, const gc_CombineFeatParams &params = gc_CombineFeatParams());
//--regions...
GC_API int gc_CreateEmptyRegion(void **region, int ccw);
GC_API int gc_AddRegionLoop(void *region, void *loop_path, int outer);
GC_API int gc_GetRegionNumLoops(void *region, int *nloops);
GC_API int gc_GetRegionLoop(void *region, int loop, void **loop_path);
GC_API int gc_GetRegionDirection(void *region, int *ccw);
GC_API int gc_GetRegionBBox(void *region, double bbox[2][2]);
GC_API int gc_GetRegionLoopBBox(void *region, int loop, double bbox[2][2]);
GC_API int gc_GetRegionLoopOuter(void *region, int loop, int *outer);
GC_API int gc_PointInRegion(void *region, double point[3], int *inside);
GC_API int gc_UnionRegions(void *region1, void *region2, void **union_region);
GC_API int gc_DiffRegions(void *region1, void *region2, void **diff_region);
GC_API int gc_IntersectRegions(void *region1, void *region2, void **intersect_region);
GC_API int gc_CopyRegion(void *region, void **copy_region);
GC_API int gc_OffsetRegion(void *region, double offset);
GC_API int gc_TransformRegion(void *region, double *matrix);
GC_API int gc_ReverseRegion(void *region);
GC_API int gc_RegionHasSplines(void *region, int *pbHasSplines);
GC_API int gc_SegmentRegionSplines(void *region, double xTol);
GC_API int gc_DeleteRegion(void *region);
GC_API int gc_RegionSliceSolidWithCS( int iSolid, int iCS, void *region );
GC_API int gc_SplitRegion( void *region, int axis, void **path );
GC_API int gc_ClearRgn2Geom(double xTol);
GC_API int gc_GetUseOutlineDepthMax();
GC_API void gc_SetUseOutlineDepthMax(int bUseIt);
GC_API int gc_GetUseOutlineDepthMin();
GC_API void gc_SetUseOutlineDepthMin(int bUseIt);
GC_API double gc_GetOutlineDepthMax();
GC_API void gc_SetOutlineDepthMax(double xVal);
GC_API double gc_GetOutlineDepthMin();
GC_API void gc_SetOutlineDepthMin(double xVal);

/** gc_CreateEmptyRegionEx
* Create an empty region, setting the direction of its outter loops and its depth
*( read the API word doc for information on regions and how they work when nested )
*@param		void **region
*@param		int ccw
*@param		double double
*@return	0 - success
*@return	-1 - no region
*/ 
GC_API int gc_CreateEmptyRegionEx( void **region, int ccw, double depth );
/** gc_SetRegionDepth
* Set the depth of an existing region, or one created by gc_CreateEmptyRegion
*( read the API word doc for information on regions and how they work when nested )
*@param		void *region
*@param		double double
*@return	0 - success
*@return	-1 - no region
*/ 
GC_API int gc_SetRegionDepth( void *region, double depth );
/** gc_GetRegionDepth
* Get the depth of an existing region, or one created by gc_CreateEmptyRegion
*( read the API word doc for information on regions and how they work when nested )
*@param		void *region
*@param		double *double
*@return	0 - success
*@return	-1 - no region
*@return	-2 - null pointer to hold returned value
*/ 
GC_API int gc_GetRegionDepth( void *region, double *depth );
/** gc_AddRegionLoopEx
* Add a loop to a region with the ability to specify if it is an open or closed loop
* Open loops must not self intersect, nor be fully closed.  Make sure the loop does not have the same start and end point
*( read the API word doc for information on regions and how they work when nested )
*@param		void *region
*@param		double *double
*@return	0 - success
*@return	-1 - no region
*@return	-2 - null pointer to hold returned value
*/ 
GC_API int gc_AddRegionLoopEx(void *region, void *loop_path, int outer, int closed);
//--curve fitting
GC_API int gc_FitCurve(int iNumPoints, double *dPoints, double dTol, int iClosed, int eParamMode);
GC_API int gc_CalcParams(int iNumPoints, const double *dPoints, teCurveFitMode eParamMode, double *params);
GC_API int gc_FitCurve2(int iNumPoints, const double *dPoints, const double *params, double dTol, int iClosed);
GC_API int gc_InterpolateCurve(int iNumPoints, double *dPoints, int iClosed, int eParamMode);
GC_API int gc_InterpolateCurve2(int iNumPoints, double *dPoints, int iClosed, const double *params);

//--profiler and profiler marker

enum
{
	gc_eSliceMode_Off=0,
	gc_eSliceMode_Plane=1,
	gc_eSliceMode_Rotary=2,
	gc_eSliceMode_Silhouette=3,
	gc_eSliceMode_Cylinder=4
};

GC_API int gc_GetProfilerMode(int *piMode);
GC_API int gc_SetProfilerMode(int iMode);
GC_API int gc_GetProfilerDepth(double *pdDepth);
GC_API int gc_SetProfilerDepth(double dDepth);
GC_API int gc_GetProfilerPathCount(int *piCount);
GC_API int gc_GetProfilerPathSelected(int iPath, int *piSelected);
GC_API int gc_SetProfilerPathSelected(int iPath, int iSelected);
GC_API int gc_GetProfilerPathOuter(int iPath, int *piOuter);
GC_API int gc_GetProfilerPath(int iPath, void **ppPath);
GC_API int gc_GetProfilerHole(int iPath, double *dCenter, double *dRad);
GC_API int gc_GetProfilerCircle(int iPath, double *dCenter, double *dRad);
GC_API int gc_GetSpunOutlineAlgorithm(int *pnSpunAlg);
GC_API int gc_SetSpunOutlineAlgorithm(int nSpunAlg);
GC_API int gc_GetProfilerMarkerMode(int *piMode);
GC_API int gc_GetProfilerMarkerSetCount(int *piSetCount);
GC_API int gc_GetProfilerMarker(int iSet, int iTool, int*piPath, int *piFeat, double *pxParam);
GC_API int gc_SetProfilerMarker(int iSet, int iTool, int iFeat, double xParam);
GC_API int gc_GetProfilerMarkerSide(int iSet, int *piSide);
GC_API int gc_SetProfilerMarkerSide(int iSet, int iSide);
GC_API int gc_GetProfilerMarkerSingleFeature(int iSet, int *piSingle);
GC_API int gc_SetProfilerMarkerSingleFeature(int iSet, int iSingle);
//--curve
GC_API int gc_GetCurveType(void *curve, int *type);
GC_API int gc_GetCurveLine(void *curve, double origin[3], double axis[3]);
GC_API int gc_GetCurveCircle(void *curve, double *radius, double origin[3], double xvec[3], double yvec[3]);
GC_API int gc_GetCurveEllipse(void *curve, double *radius1, double *radius2, double origin[3], double xvec[3], double yvec[3]);
GC_API int gc_GetCurveBSpline(void *curve, int *degree, int *n_knots, int *n_ctrls);
GC_API int gc_GetCurveBSplineData(void *curve, int *k_mult, double *k_param, double *ctrls);
//--curve creation
GC_API int gc_CreateCurveLine(double origin[3], double axis[3], void **curve);
GC_API int gc_CreateCurveCircle(double radius, double origin[3], double xvec[3], double yvec[3], void **curve);
GC_API int gc_CreateCurveEllipse(double radius1, double radius2, double origin[3], double xvec[3], double yvec[3], void **curve);
GC_API int gc_CreateCurveBSpline(int degree, int n_knots, int n_ctrls, int *k_mult, double *k_param, double *ctrls, void **curve);
GC_API int gc_ExtractEdgeCurve(int iSolRef, int iEdgeRef, void **curve, double *params);
GC_API int gc_ExtractEdgeCurveLM(int iSolRef, gc_TopoId EdgeRef, void **curve, double *params);
GC_API int gc_DeleteCurve(void *curve);
GC_API int gc_CopyCurve(void *curve, void **new_curve);
GC_API int gc_TransformCurve(void *curve, double *matrix);
//CALLBACKS


GC_API int gc_SetGeomCallBack(int iMode, void (*call_back)(void*));
GC_API int gc_ClearGeomCallBack(int iMode, void (*call_back)(void*));

//******************* PROGRAM ITERATOR  ************************


//ENUMERATIONS

enum gc_InterOpEvent
{
	gc_eGoToOnPartOpEvent,
	gc_eGoToOffPartOpkEvent,
	gc_eTGChangeEvent,
	gc_eToolPosChangeEvent,
	gc_eToolIDChangeEvent,
	gc_eToolOffsetChangeEvent,
	gc_eToolSubPosChangeEvent,
	gc_eProgStopEvent,
	gc_eNonToolUtilOpEvent,
	gc_eDiff1stAngleEvent,
	gc_eDiff2ndAngleEvent,
	gc_eDiffRotSideEvent,		// new value for the 2nd rotary axis is on the other side of the 'singularity'
	gc_eBeforeWPJumpEvent,
	gc_eAfterWPJumpEvent,
	gc_eFlowEndEvent,
	gc_eDiffSpinThingEvent,		// for lathe drill to mill drill switch, or vice versa
	gc_eEveryInterOpEvent,		// this event occurs between every pair of ops, used to ALWAYS go off parta
	gc_eProgEndEvent,
	gc_eNumInterOpEvents		// must be last
};

//--program states...
enum teProgItrState
{
	eProgOpPath = 0,
	eProgOpExit,
	eProgInterOp,
	eProgOpEntry,
	eProgRotExit,
	eProgInterRot,
	eProgRotEntry,
	eProgOriginExit,
	eProgInterOrigin,
	eProgOriginEntry,
	eProgZPassExit,
	eProgInterZPass,
	eProgZPassEntry
};

//--prog itr error types...
enum gc_ProgItrErr
{
	gc_eSpindleRPMErr,		// spindle off when turning, or on when milling
	gc_eSpindleDirErr,		// turning ops machining simultaneously have different spindle directions
	gc_eDeadLockErr,		// synchs are crossed
	gc_eWrongToolErr,		// the correct tool isn't loaded into the active position
	gc_eBadPositionErr,		// couldn't achieve position required by path feature or component synch
	gc_eBadOrientationErr,	// couldn't achieve orientation required by path feature
	gc_eLimitsExceededErr,	// one or more axes went out of limits
	gc_eAxisConflictErr,	// two flows simultaneously driving the same axis to different values
	gc_eUtilOpErr,			// VMM reported something wrong with utility op
	gc_eBadFeedRateErr,		// feed rate not set properly in an op (often due to using non-tapping tools in tapping ops)
	gc_eSyncConflictErr,	// VMM has defined syncs in different flows with conflicting info
	gc_eRotAxisNeededErr,	// no rotary axis was available for use in a rotary face mill op ('polar')
	gc_eNoAxisSetErr,		// neither the MDD nor the VMM specified an axis set for a flow
	gc_eBadUtilOpErr,		// VMM created an invalid path for a utility op
	gc_eBadTurningPlaneErr,	// An invalid turning plane was defined by the tool block assigned to a tool
	gc_eSwissCollisionErr,	// sliding head-stock hit back of guide bushing
	gc_eUnsupportedStockErr,// bar stock did not have minimum support by guide bushing
};

//--prog itr rotation errors...
enum teProgItrRotErr
{
	eProgRotNoErr,
	eProgRotNeed1Err,		// obsolete (now returns eProgRotNoSolnErr)
	eProgRotNeed2Err,		// obsolete (now returns eProgRotNoSolnErr)
	eProgRotLim1Err,		// this orientation requires 1st rotation outside limits
	eProgRotLim2Err,		// this orientation requires 2nd rotation outside limits
	eProgRotNoSolnErr,		// this orientation can't be reached given axis set up
	eProgRotInternErr		// obsolete
};

//--prog itr custom axis types...
enum gc_CustomAxisType
{
	gc_eLinearCustomAxis,
	gc_eRotaryCustomAxis,
	gc_eOtherCustomAxis
};

struct gc_CustomAxisParams
{
	enum {cur_vers = 1};

	int version;					// param block data structure version, don't change from default constructed value!
	gc_CustomAxisType type;
	int visible;
	double max_step;
	double max_feed;

	gc_CustomAxisParams()
		: version(cur_vers), type(gc_eOtherCustomAxis), visible(false), max_step(0.0), max_feed(0.0) {}
	gc_CustomAxisParams(gc_CustomAxisType typ, bool vis, double mx_step = 0.0, double mx_feed = 0.0)
		: version(cur_vers), type(typ), visible(vis), max_step(mx_step), max_feed(mx_feed) {}
};

//STRUCTURE

struct gc_kNode;

struct gc_NextProgItrOpInfo
{
	int iOp;				// the next op; <= 0 at end
	int iOpInst;			// instance of op (must increase for two instances of same op)
	int bMoveOp;			// should iOp be moved?  not relevant at end
	double move_matrix[12];	// if bMoveOp is true, this matrix moves iOp from its "op cs" to new position & orientation
	int bUseTravPlane;		// should the traversal plane to iOp be overridden (at end, it's the traversal plane from last op)
	double trav_plane;		// if bUseTravPlane is true, the value should be in the last op's "op cs"
	
	gc_NextProgItrOpInfo()			: iOp(0), iOpInst(1), bMoveOp(false), bUseTravPlane(false) {}
	gc_NextProgItrOpInfo(int op)	: iOp(op), iOpInst(1), bMoveOp(false), bUseTravPlane(false) {}
};

typedef void (*tfNextProgItrOp)(void *prog_itr, int iFlow, int bBegin, gc_NextProgItrOpInfo *pInfo);// call back function to override op order

//--program iterator parameter block...
struct gc_ProgItrParams
{
	int iVersion;							// structure version, fields may be added and version incremented
	int bAllOps;							// non-zero to iterate through all ops
	int iOpToDo;							// if !bAllOps, 0 means selected ops, non-zero is op number to iterate through
	int bExpandDrillOps;					// if true, mill drilling cycles are expanded into feeds and rapids, else, points are returned
	int bPreferCannedPath;					// if true, lathe roughing paths are returned in their "short hand" form. Check "gc_GetProgItrFeatCanned"
	int bPreferEdgePath;					// if true, where possible, paths are to the tool edge. Check "gc_GetProgItrFeatToEdge"
	tfExpandPathCBfunc fDrillCB;			// if set, and bExpandDrillOps is true, will be called for drill expansion
	int bCalcTime;							// calc elapsed time?
	double xMaxFeedLength;					// > 0 to break feed moves by length (in part-space)
	double xMaxRapidLength;					// > 0 to break rapid moves by length (in part-space); applies to ALL rapids
	double xMaxThreadRevs;					// > 0 to break thread moves by revolutions
	int iMinTCIndexFrames;					// > 0 to break tool change index moves
	int iNumItrFlows;						// number of flows to iterate through; 0 means do all
	int *aiItrFlows;						// if (iNumItrFlows > 0), array [0..iNumItrFlows-1] of flows to iterate through
	int bKeepInterFlags;					// if true, interop moves with different flags will not be combined
	double xMaxFeedPartAngle;				// > 0 to break feed moves by part-space angle, in degrees)
	double xMaxRapidPartAngle;				// > 0 to break rapid moves by part-space angle, in degrees); applies to ALL rapids
	double xMaxFeedMachAngle;				// > 0 to break feed moves by machine angle, in degrees)
	double xMaxRapidMachAngle;				// > 0 to break rapid moves by machine angle, in degrees); applies to ALL rapids
	tfNextProgItrOp fNextOpCB;				// used to override normal op ordering; bAllOps & iOpToDo are ignored if this is set
	int iReserved1;							// for internal use
	gc_tOpEventCallBack fDrillCycleCB;		// will be called per hole; void* points to a gc_DrillCycleCBParams struct
	void *internal_use_1;					// not used
	void *internal_use_2;					// not used
	int internal_use_3;						// not used
	tfWillUseLinearApproxCBfunc fWillUseLinearApprox;	// called after each new feature is read, can control "part-space" chord height segmentation
	double xMaxCustomLength;				// > 0 to break custom linear moves (part units)
	double xMaxCustomAngle;					// > 0 to break custom rotary moves (degrees)
	int bReportErrors;						// keep list of errors?
	double xSingularityLinkTol;				// part-space chord height tol used when linking angle discontinuities at 5-axis singularites; 0 for default tol, < 0 for no links
	int bTrackAxesInsideOp;					// turning this off can be much faster, if tg/wp axis tracking isn't needed
	int bMakePathCopy;						// turning this off can be faster, but might not copy path, so it's only safe if you use the PI immediately and delete it
	int bAllowOpSkip;						// turn this off if op skipping won't be used, as it will be faster over 5-axis ops
	int bUseGraphicDist;					// if false, move between spindles will ignore graphic part face distance
	int bReportParkEvents;					// keep list of auto-park events? (per flow)
	int iReserved2;							// for internal use
	tfWillUseLinearApproxCBfunc2 fWillUseLinearApprox2;	// called after each new feature is read, can control "part-space" and/or "machine-space" chord height segmentation
	tfPostClearCBfunc fPostClear;	        // called after PI reset/clear - allows the modification of the PI-specific Machine Definition
	int bVerboseFeats;						// by default, sync points appear as "dead syncs", and many custom feats appear as state changes, not as features; set to true to see as features also
	int bUseOpInstanceScheme;				// set to true to use installed global op instance callback to get op order
	double xMaxOnPartRapidLength;			// > 0 to break rapid moves by length (in part-space); applies to ONLY ON-PART rapids
	double xMaxOnPartRapidPartAngle;		// > 0 to break rapid moves by part-space angle, in degrees); applies ONLY ON-PART rapids
	double xMaxOnPartRapidMachAngle;		// > 0 to break rapid moves by machine angle, in degrees); applies ONLY ON-PART rapids
	double xSpiralToArcTol;					// part-space chord height tol used used to approximate spirals with circular arcs; 0 for default tol, < 0 for no approximation
};

// call "gc_InitProgItrParams" to initialize param block fields to defaults...
#define gc_InitProgItrParams(params)		\
	(										\
		(params).iVersion = 22,				\
		(params).bAllOps = 1,				\
		(params).iOpToDo = 0,				\
		(params).bExpandDrillOps = 0,		\
		(params).bPreferCannedPath = 0,		\
		(params).bPreferEdgePath = 0,		\
		(params).fDrillCB = 0,				\
		(params).bCalcTime = 0,				\
		(params).xMaxFeedLength = - 1.0,		\
		(params).xMaxRapidLength = - 1.0,	\
		(params).xMaxThreadRevs = - 1.0,		\
		(params).iMinTCIndexFrames = 0,		\
		(params).iNumItrFlows = 0,			\
		(params).aiItrFlows = 0,			\
		(params).bKeepInterFlags = 0,		\
		(params).xMaxFeedPartAngle = - 1.0,	\
		(params).xMaxRapidPartAngle = - 1.0,\
		(params).xMaxFeedMachAngle = - 1.0,	\
		(params).xMaxRapidMachAngle = - 1.0,\
		(params).fNextOpCB = 0,				\
		(params).iReserved1 = 0,			\
		(params).fDrillCycleCB = 0,			\
		(params).internal_use_1 = 0,		\
		(params).internal_use_2 = 0,		\
		(params).internal_use_3 = 1,		\
		(params).fWillUseLinearApprox = 0,	\
		(params).fWillUseLinearApprox2 = 0,	\
		(params).fPostClear = 0,	        \
		(params).xMaxCustomLength = - 1.0,	\
		(params).xMaxCustomAngle = - 1.0,	\
		(params).bReportErrors = false,		\
		(params).bReportParkEvents = false,	\
		(params).xSingularityLinkTol = 0.0,	\
		(params).bTrackAxesInsideOp = true,	\
		(params).bMakePathCopy = true,		\
		(params).bAllowOpSkip = false,		\
		(params).bUseGraphicDist = false,	\
		(params).iReserved2 = 0,			\
		(params).bVerboseFeats = false,		\
		(params).bUseOpInstanceScheme = false,\
		(params).xMaxOnPartRapidLength = - 1.0,	\
		(params).xMaxOnPartRapidPartAngle = - 1.0,\
		(params).xMaxOnPartRapidMachAngle = - 1.0,\
		(params).xSpiralToArcTol = - 1.0	\
	)

struct gc_NextProgItrOpInfo2
{
	int iOp;				// the next op; <= 0 at end
	int iOpInst;			// instance of op (must increase for two instances of same op)
	int bMoveOp;			// should iOp be moved?  not relevant at end
	double move_matrix[12];	// if bMoveOp is true, this matrix moves iOp from its "op cs" to new position & orientation
	int bUseTravPlane;		// should the traversal plane to iOp be overridden (at end, it's the traversal plane from last op)
	double trav_plane;		// if bUseTravPlane is true, the value should be in the last op's "op cs"
	int iWFO;				// wfo to be used, 0 for default
	
	gc_NextProgItrOpInfo2()			: iOp(0), iOpInst(1), bMoveOp(false), bUseTravPlane(false), iWFO(0) {}
	gc_NextProgItrOpInfo2(int op)	: iOp(op), iOpInst(1), bMoveOp(false), bUseTravPlane(false), iWFO(0) {}
};

typedef void (*tfNextProgItrOp2)(int iFlow, int bBegin, gc_NextProgItrOpInfo2 *pInfo);				// call back function to override op order

//--to install a multi-part solution that will be used by any interested ProgItr client...
GC_API int gc_InstallOpInstanceScheme(const char *identity, tfNextProgItrOp2 new_op_callback);	// returns 0 if successful, -1 for invalid name, -2 if another is already installed
GC_API bool gc_OpInstanceSchemeInstalled();										// returns true if a scheme is already installed
GC_API const char *gc_OpInstanceSchemeIdentity();								// returns the installed scheme's name
GC_API void gc_ClearOpInstanceScheme();											// to clear a previously installed scheme

class CMachDef;

//DECLARATIONS
GC_API int gc_GetProgIterator(void **itr);
GC_API int gc_ProgIteratorDelete(void *itr);
GC_API int gc_ProgIteratorCopy(const void *itr, void **copy_itr);
GC_API int gc_ProgIteratorReset(void *itr, const gc_ProgItrParams *params);
GC_API int gc_ProgIteratorDone(const void *itr, bool &done);
GC_API int gc_ProgIteratorNext(void *itr);
GC_API int gc_ProgIteratorTime(const void *itr, double *xTime);					// returns elapsed time in minutes
GC_API int gc_ProgIteratorStateChange(const void *itr, bool *pbChange);
GC_API int gc_GetProgItrNumLoadedTools(const void *itr, int *piNum);
GC_API int gc_GetProgItrLoadedTools(const void *itr, int aiTools[]);
GC_API int gc_GetProgItrMachDef(const void *itr, const CMachDef *&mach_def);
GC_API int gc_GetProgItrMutableMachDef(void *itr, CMachDef *&mach_def);
GC_API int gc_GetProgItrWPAngles(const void *itr, int iWP, double *angles);		// in degrees
GC_API int gc_GetProgItrWPAngle(const void *itr, int iWP, int iAxis, double *angle);	// in degrees
GC_API int gc_SetProgItrWPAngle(void *itr, int iWP, int iAxis, double angle);	// in degrees
GC_API int gc_GetProgItrWPRPMFixed(const void *itr, int iWP, int *bFixed);		// wp spindle css state
GC_API int gc_GetProgItrWPRPM(const void *itr, int iWP, double *dRPM);			// wp spindle rpm
GC_API int gc_GetProgItrWPSUPM(const void *itr, int iWP, double *dSFPM );		// wp spindle supm/sfpm
GC_API int gc_GetProgItrWPDir(const void *itr, int iWP, int *iDirCCW);			// wp spindle dir
GC_API int gc_GetProgItrWPPos(const void *itr, int iWP, double *pos);
GC_API int gc_GetProgItrWPLinked(const void *itr, int iWP, int *iLinkedWP);

//--iterator parameters...
GC_API int gc_GetProgItrReportErrors(const void *itr, int *bReport);
GC_API int gc_SetProgItrReportErrors(void *itr, int bReport);
GC_API int gc_GetProgItrExpandDrillOps(const void *itr, int *bExpand);
GC_API int gc_SetProgItrExpandDrillOps(void *itr, int bExpand);
GC_API int gc_GetProgItrPreferCannedPath(const void *itr, int *bPreferCanned);
GC_API int gc_SetProgItrPreferCannedPath(void *itr, int bPreferCanned);
GC_API int gc_GetProgItrPreferEdgePath(const void *itr, int *bPreferEdge);
GC_API int gc_SetProgItrPreferEdgePath(void *itr, int bPreferEdge);
GC_API int gc_GetProgItrMaxFeedLength(const void *itr, double *xLength);
GC_API int gc_SetProgItrMaxFeedLength(void *itr, double xLength);
GC_API int gc_GetProgItrMaxRapidLength(const void *itr, double *xLength);
GC_API int gc_SetProgItrMaxRapidLength(void *itr, double xLength);
GC_API int gc_GetProgItrMaxOnPartRapidLength(const void *itr, double *xLength);
GC_API int gc_SetProgItrMaxOnPartRapidLength(void *itr, double xLength);
GC_API int gc_GetProgItrMaxFeedPartAngle(const void *itr, double *xAngle);	// in degrees
GC_API int gc_SetProgItrMaxFeedPartAngle(void *itr, double xAngle);			// in degrees
GC_API int gc_GetProgItrMaxRapidPartAngle(const void *itr, double *xAngle);	// in degrees
GC_API int gc_SetProgItrMaxRapidPartAngle(void *itr, double xAngle);		// in degrees
GC_API int gc_GetProgItrMaxOnPartRapidPartAngle(const void *itr, double *xAngle);	// in degrees
GC_API int gc_SetProgItrMaxOnPartRapidPartAngle(void *itr, double xAngle);		// in degrees
GC_API int gc_GetProgItrMaxFeedMachAngle(const void *itr, double *xAngle);	// in degrees
GC_API int gc_SetProgItrMaxFeedMachAngle(void *itr, double xAngle);			// in degrees
GC_API int gc_GetProgItrMaxRapidMachAngle(const void *itr, double *xAngle);	// in degrees
GC_API int gc_SetProgItrMaxRapidMachAngle(void *itr, double xAngle);		// in degrees
GC_API int gc_GetProgItrMaxOnPartRapidMachAngle(const void *itr, double *xAngle);	// in degrees
GC_API int gc_SetProgItrMaxOnPartRapidMachAngle(void *itr, double xAngle);		// in degrees
GC_API int gc_GetProgItrMaxCustomLength(const void *itr, double *xLength);
GC_API int gc_SetProgItrMaxCustomLength(void *itr, double xLength);
GC_API int gc_GetProgItrMaxCustomAngle(const void *itr, double *xAngle);	// in degrees
GC_API int gc_SetProgItrMaxCustomAngle(void *itr, double xAngle);			// in degrees
GC_API int gc_GetProgItrMaxThreadRevs(const void *itr, double *xRevs);
GC_API int gc_SetProgItrMaxThreadRevs(void *itr, double xRevs);
GC_API int gc_GetProgItrMinTCIndexFrames(const void *itr, int *iFrames);
GC_API int gc_SetProgItrMinTCIndexFrames(void *itr, int iFrames);
GC_API int gc_GetProgItrSingularityLinkTol(const void *itr, double *tol);
GC_API int gc_SetProgItrSingularityLinkTol(void *itr, double tol);
GC_API int gc_SetProgItrAliasTGs(void *itr, int n_tgs, const int *tg_list);
GC_API int gc_SynchProgItrAxes(void *itr, int n_axes, const char *axis_names[], gc_AxisSynchType type);
GC_API int gc_UnSynchProgItrAxes(void *itr, int n_axes, const char *axis_names[]);

//--feature geometry retrieval...
GC_API int gc_GetProgItrFeatType(const void *itr, int iFlow, int *iType);
GC_API int gc_GetProgItrFeatName(const void *itr, int iFlow, char *sName);
GC_API int gc_GetProgItrFeatAtt(const void *itr, int iFlow, int iAttType, int *iFeatAtt);
GC_API int gc_GetProgItrFeatPoint(const void *itr, int iFlow, double *pt);
GC_API int gc_GetProgItrFeatLine(const void *itr, int iFlow, double *p1, double *p2);
GC_API int gc_GetProgItrFeatCircle(const void *itr, int iFlow, double *dCenter, double *dRad);
GC_API int gc_GetProgItrFeatArcEnds(const void *itr, int iFlow, double *dStart, double *dEnd, int *iDirCCW);
GC_API int gc_GetProgItrFeatArcAngles(const void *itr, int iFlow, double *dStartAng, double *dEndAng);
GC_API int gc_GetProgItrFeatCurve(const void *itr, int iFlow, int *degree, int *n_knots, int *n_ctrls);
GC_API int gc_GetProgItrFeatCurveData(const void *itr, int iFlow, int *k_mult, double *k_param, double *ctrls);
GC_API int gc_GetProgItrFeatLineIJK(const void *itr, int iFlow, double *p1, double *ijk1, double *p2, double *ijk2);
GC_API int gc_GetProgItrFeatLineABC(const void *itr, int iFlow, double *p1, double *abc1, double *p2, double *abc2);
GC_API int gc_GetProgItrFeatDwell(const void *itr, int iFlow, int *pbRevs, double *pxDwell);
GC_API int gc_GetProgItrFeatPartMove(const void *itr, int iFlow, int *piFromWP, int *piToWP, double *pos, double *d_axis, double *h_axis);
GC_API int gc_GetProgItrFeatCustom(const void *itr, int iFlow, char *sName, double *axParams, double *pxTime, double *pxLength, int *piDataSize);
GC_API int gc_GetProgItrFeatCustomData(const void *itr, int iFlow, char *pData);
GC_API int gc_GetProgItrFeatCustomFieldInfo(const void *itr, int iFlow, char *sFieldName, int *piSize, int *piOffset, int *piEnabled);
GC_API int gc_GetProgItrFeatCustomFieldData(const void *itr, int iFlow, char *sFieldName, void *pData);
GC_API int gc_CreateProgItrFeatPoints(const void *itr, int iFlow, double tol, void **point_list);		// tol <= 0 means use default. won't wrap points if wrapped rotary feature
GC_API int gc_CreateProgItrFeatPoints2(const void *itr, int iFlow, double tol, void **point_list);	// will wrap points if wrapped rotary feature
GC_API int gc_EvalProgItrFeat(const void *itr, int iFlow, double xParam, double *point, double *axis);
GC_API int gc_EvalProgItrPoint(const void *itr, int iFlow, double xParam, double *point);
GC_API int gc_EvalProgItrTlAxis(const void *itr, int iFlow, double xParam, double *axis);
GC_API int gc_GetProgItrFeat(const void *itr, int iFlow, void **feat);
GC_API int gc_GetProgItrUntrimmedFeat(const void *itr, int iFlow, void **feat);		// entire feature, untrimmed by other flows or segmentation, max angles, etc.
GC_API int gc_ProgItrPeekNextFeature(const void *itr, int iFlow, void **feat);		// returns next feature, if it's EASY and CHEAP, otherwise it will return non-zero error code
GC_API int gc_GetProgItrFeatWasRapid(const void *itr, int iFlow, bool &was_rapid);

//--other state info...

GC_API int gc_GetProgItrFlowDone(const void *itr, int iFlow, int *pbDone);
GC_API int gc_GetProgItrFlowBlocked(const void *itr, int iFlow, int *pbBlocked);
GC_API int gc_GetProgItrState(const void *itr, int iFlow, gc_ProgState*);
GC_API int gc_GetProgItrOpNum(const void *itr, int iFlow, int *iOp);
GC_API int gc_GetProgItrOpInstance(const void *itr, int iFlow, int *iInstance);
GC_API bool gc_GetProgItrOpWFO(const void *itr, int iFlow, int *wfo);
GC_API int gc_GetProgItrNextOpNum(const void *itr, int iFlow, int *iOp);
GC_API int gc_GetProgItrNextOpInstance(const void *itr, int iFlow, int *iInstance);
GC_API bool gc_GetProgItrNextOpWFO(const void *itr, int iFlow, int *wfo);
GC_API int gc_GetProgItrToolNum(const void *itr, int iFlow, int *iTool);
GC_API int gc_GetProgItrNextToolNum(const void *itr, int iFlow, int *iTool);
GC_API int gc_GetProgItrTGNum(const void *itr, int iFlow, int *iTG);
GC_API int gc_GetProgItrNextTGNum(const void *itr, int iFlow, int *iTG);
GC_API int gc_GetProgItrWPNum(const void *itr, int iFlow, int *iWP);
GC_API int gc_GetProgItrNextWPNum(const void *itr, int iFlow, int *iWP);
GC_API int gc_GetProgItrFeatState(const void *itr, int iFlow, int *iState);		// returns current state; see above "prog state" enumeration
GC_API int gc_GetProgItrFeatCount(const void *itr, int iFlow, int *iCount);
GC_API int gc_GetProgItrFeatIndex(const void *itr, int iFlow, int *iIndex);
GC_API int gc_GetProgItrFeatParams(const void *itr, int iFlow, double *dStart, double *dEnd);
GC_API int gc_GetProgItrAtSegEnd(const void *itr, int iFlow, bool *pbAtSegEnd);
GC_API int gc_GetProgItrToolCS(const void *itr, int iFlow, int *iCS);
GC_API int gc_GetProgItrFeatCS(const void *itr, int iFlow, int *iCS);
GC_API int gc_GetProgItrFeatWrapped(const void *itr, int iFlow, int *bWrapped);
GC_API int gc_GetProgItrFeatPolar(const void *itr, int iFlow, int *pbPolar, int *pbNegSide = NULL);
GC_API int gc_GetProgItrFeatToEdge(const void *itr, int iFlow, int *bToEdge);
GC_API int gc_GetProgItrFeatCanned(const void *itr, int iFlow, int *bCanned);
GC_API int gc_GetProgItrFeatStartWrapDepth(const void *itr, int iFlow, double *dDepth);
GC_API int gc_GetProgItrFeatEndWrapDepth(const void *itr, int iFlow, double *dDepth);
GC_API int gc_GetProgItrFeedRate(const void *itr, int iFlow, double *dFeed);			// mill ops: units/min; lathe ops: units/rev
GC_API int gc_GetProgItrFeedRateEx(const void *itr, int iFlow, double *dFeed);			// check gc_GetProgItrFeedPerRev to determine units
GC_API int gc_GetProgItrFeedPerRev(const void *itr, int iFlow, bool &is_per_rev);
GC_API int gc_GetProgItrZPassIndex(const void *itr, int iFlow, int *iZPass);
GC_API int gc_GetProgItrZPasses(const void *itr, int iFlow, int *iZPasses);
GC_API int gc_GetProgItrOriginIndex(const void *itr, int iFlow, int *iOrigin);
GC_API int gc_GetProgItrOrigins(const void *itr, int iFlow, int *iOrigins);
GC_API int gc_GetProgItrRotationIndex(const void *itr, int iFlow, int *iRotation);
GC_API int gc_GetProgItrRotations(const void *itr, int iFlow, int *iRotations);
GC_API int gc_GetProgItrRotAngles(const void *itr, int iFlow, double xParam, double axAngles[3]);
GC_API int gc_GetProgItrRotMatrix(const void *itr, int iFlow, double xParam, double *matrix);			// feat cs to "workplane axes" (uses part AND tool rotations)
GC_API int gc_GetProgItrMachMatrix(const void *itr, int iFlow, double xParam, double *matrix);		// feat cs to "machine axes" (uses part rotations ONLY)
GC_API int gc_GetProgItrRotError(const void *itr, int iFlow, double xParam, teProgItrRotErr *peErr);
GC_API int gc_GetProgItrHasReparent(const void *itr, int iFlow, bool *reparent);
GC_API int gc_GetProgItrNumReleasedSyncs(const void *itr, int *piCount);
GC_API int gc_GetProgItrReleasedSyncID(const void *itr, int iSyncIndex, gc_SyncID *sync_id);
GC_API int gc_GetProgItrCRCState(const void *itr, int iFlow, int *on);
GC_API int gc_GetProgItrCRCSide(const void *itr, int iFlow, int *right_side);
GC_API int gc_GetProgItrInterOpEventCount(const void *itr, int iFlow, int *num_evts);
GC_API int gc_GetProgItrInterOpEvent(const void *itr, int iFlow, int iIndex, gc_InterOpEvent *evt);
GC_API int gc_ClearProgItrInterOpEvents(void *itr, int iFlow);
GC_API int gc_GetProgItrAxisSet(const void *itr, int iFlow, char *axis_set);
GC_API int gc_GetProgItrNextAxisSet(const void *itr, int iFlow, char *axis_set);
GC_API int gc_GetProgItrInterpSet(const void *itr, int iFlow, gc_InterpSet &interp_set);
GC_API int gc_GetProgItrNextInterpSet(const void *itr, int iFlow, gc_InterpSet &interp_set);
GC_API bool gc_GetProgItrFlowControlsAxis(const void *itr, int iFlow, const char *axis_name);

// In gc_GetProgItrTGPos below, iTool == 0 means give the position of the currently loaded tool,
// while iTool < 0 means give the position of the toolgroup with no tool offset...
GC_API int gc_GetProgItrTGToolNum(const void *itr, int iTG, int *iTool);
GC_API int gc_GetProgItrTGCurWP(const void *itr, int iTG, int *iWP);
GC_API int gc_GetProgItrTGPos(const void *itr, int iTG, int iTool, int iWP, double *pos);
GC_API int gc_GetProgItrTGAngles(const void *itr, int iTG, double *angles);	// in degrees
GC_API int gc_GetProgItrTGAngle(const void *itr, int iTG, int iAxis, double *angle);	// in degrees
GC_API int gc_SetProgItrTGAngle(void *itr, int iTG, int iAxis, double angle);	// in degrees
GC_API int gc_GetProgItrTGRPM(const void *itr, int iTG, double *dRPM);			// tg spindle rpm
GC_API int gc_GetProgItrTGDir(const void *itr, int iTG, int *iDirCCW);			// tg spindle dir
GC_API int gc_GetProgItrTGTCPState(const void *itr, int iTG, int *on);
GC_API int gc_GetProgItrCustomAxisCount(const void *itr, int *count);
GC_API int gc_GetProgItrCustomAxes(const void *itr, char asAxisNames[][16], double vals[], gc_CustomAxisType types[], double max_steps[], double max_feeds[]);
// 'max_step' and 'max_feed' ignored in gc_AddProgItrCustomAxis (use gc_AddProgItrCustomAxis2)
GC_API int gc_AddProgItrCustomAxis(void *itr, const char *sAxisName, double val, gc_CustomAxisType type = gc_eOtherCustomAxis, double max_step = 0.0, double max_feed = 0.0);
GC_API int gc_AddProgItrCustomAxis2(void *itr, const char *sAxisName, double val, const gc_CustomAxisParams &params);
GC_API int gc_SetProgItrCustomAxisVal(void *itr, const char *sAxisName, double val);
GC_API int gc_GetProgItrCustomAxisVal(const void *itr, const char *sAxisName, double *val);
GC_API int gc_GetProgItrCustomAxisType(const void *itr, const char *sAxisName, gc_CustomAxisType *type);
GC_API int gc_SetProgItrCustomAxisMaxStep(void *itr, const char *sAxisName, double max_step);
GC_API int gc_GetProgItrCustomAxisMaxStep(const void *itr, const char *sAxisName, double *max_step);
GC_API int gc_SetProgItrCustomAxisMaxFeed(void *itr, const char *sAxisName, double max_feed);
GC_API int gc_GetProgItrCustomAxisMaxFeed(const void *itr, const char *sAxisName, double *max_feed);
GC_API int gc_GetProgItrAxisCount(const void *itr, int *count);
GC_API int gc_GetProgItrAxes(const void *itr, char asAxisNames[][16], double vals[], gc_CustomAxisType types[], double max_steps[], double max_feeds[]);
GC_API int gc_GetProgItrAxes2(const void *itr, char asAxisNames[][16], double vals[], gc_CustomAxisType types[], int visible[], int is_tc_axis[], double max_steps[], double max_feeds[]);
GC_API int gc_SetProgItrAxisVal(void *itr, const char *sAxisName, double val);
GC_API int gc_GetProgItrAxisVal(const void *itr, const char *sAxisName, double *val);
GC_API int gc_GetProgItrAxisType(const void *itr, const char *sAxisName, gc_CustomAxisType *type);
GC_API int gc_SetProgItrAxisMaxStep(void *itr, const char *sAxisName, double max_step);
GC_API int gc_GetProgItrAxisMaxStep(const void *itr, const char *sAxisName, double *max_step);
GC_API int gc_SetProgItrAxisMaxFeed(void *itr, const char *sAxisName, double max_feed);
GC_API int gc_GetProgItrAxisMaxFeed(const void *itr, const char *sAxisName, double *max_feed);
GC_API int gc_GetProgItrAxisLimits(const void *itr, const char *sAxisName, bool *pbLimited, double *axLimits);
GC_API int gc_GetProgItrTree(const void *itr, gc_kNode **tree);			// share ownership of the prog itr's tree; must be deleted
GC_API int gc_GetProgItrPrevTree(const void *itr, gc_kNode **tree);		// returns copy of prog itr's tree, with prev axis vals; must be deleted
GC_API int gc_GetProgItrNodeTransform(const void *itr, const char *sFromNode, const char *sToNode, double *matrix);
GC_API int gc_ClearProgItrErrors(void *itr);
GC_API int gc_GetProgItrErrorCount(const void *itr, int *count);
GC_API int gc_GetProgItrErrorType(const void *itr, int index, gc_ProgItrErr *type);
GC_API int gc_GetProgItrErrorOp(const void *itr, int index, int &op);					// valid if (type != gc_eDeadLockErr) && (type != gc_eLimitsExceededErr)
GC_API int gc_GetProgItrLimitErrorAxisCount(const void *itr, int err_ix, int &n_axes);	// valid if (type == gc_eLimitsExceededErr)
GC_API int gc_GetProgItrLimitErrorAxisName(const void *itr, int err_ix, int axis_ix, char axis_name[]);	// valid if (type == gc_eLimitsExceededErr)
GC_API int gc_GetProgItrConflictErrorAxisCount(const void *itr, int err_ix, int &n_axes);	// valid if (type == gc_eAxisConflictErr)
GC_API int gc_GetProgItrConflictErrorAxisName(const void *itr, int err_ix, int axis_ix, char axis_name[]);	// valid if (type == gc_eAxisConflictErr)
GC_API int gc_GetProgItrUtilOpErrorMsg(const void *itr, int err_ix, char *msg);

// incidental cutting rules (managed by VMM)...
GC_API int gc_ClearProgItrIncidentalCuttingRules(void *itr);
GC_API int gc_AddProgItrIncidentalCuttingRule(void *itr, int tool, int part);
GC_API int gc_AddProgItrIncidentalCuttingRule2(void *itr, int tg, int tool_pos, int part);
GC_API int gc_RemoveProgItrIncidentalCuttingRule(void *itr, int tool, int part);
GC_API int gc_RemoveProgItrIncidentalCuttingRule2(void *itr, int tg, int tool_pos, int part);

// incidental cutting instance changes from last step (read by MachineSim)...
GC_API int gc_GetProgItrNumRemovedIncidentalCuttingInstances(const void *itr, int *piNum);
GC_API int gc_GetProgItrRemovedIncidentalCuttingInstances(const void *itr, int aiTools[], int aiParts[]);
GC_API int gc_GetProgItrNumNewIncidentalCuttingInstances(const void *itr, int *piNum);
GC_API int gc_GetProgItrNewIncidentalCuttingInstances(const void *itr, int aiTools[], int aiParts[]);

// old style prog iterator functions follow
// they only support 1 flow and 1 workpiece
// don't use these for new code, as they will eventually be obsolete

/* DEPRECATED */ GC_API int gc_GetProgFeatType(void *itr, int *iType);
/* DEPRECATED */ GC_API int gc_GetProgFeatPoint(void *itr, double *pt);
/* DEPRECATED */ GC_API int gc_GetProgFeatLine(void *itr, double *p1, double *p2);
/* DEPRECATED */ GC_API int gc_GetProgFeatCircle(void *itr, double *dCenter, double *dRad);
/* DEPRECATED */ GC_API int gc_GetProgFeatArcEnds(void *itr, double *dStart, double *dEnd, int *iDirCCW);
/* DEPRECATED */ GC_API int gc_GetProgFeatArcAngles(void *itr, double *dStartAng, double *dEndAng);
/* DEPRECATED */ GC_API int gc_GetProgFeatCurve(void *itr, int *degree, int *n_knots, int *n_ctrls);
/* DEPRECATED */ GC_API int gc_GetProgFeatCurveData(void *itr, int *k_mult, double *k_param, double *ctrls);
/* DEPRECATED */ GC_API int gc_GetProgFeatLineIJK(void *itr, double *p1, double *ijk1, double *p2, double *ijk2);
/* DEPRECATED */ GC_API int gc_GetProgFeatLineABC(void *itr, double *p1, double *abc1, double *p2, double *abc2);
/* DEPRECATED */ GC_API int gc_GetProgTGFeatDwell(void *itr, int iTG, int *pbRevs, double *pxDwell);
/* DEPRECATED */ GC_API int gc_GetProgTGFeatPartMove(void *itr, int iTG, int *piFromWP, int *piToWP, double *pos, double *d_axis, double *h_axis);
/* DEPRECATED */ GC_API int gc_GetProgTGFeatCustom(void *itr, int iTG, char *sName, double *axParams, double *pxTime, double *pxLength, int *piDataSize);
/* DEPRECATED */ GC_API int gc_GetProgTGFeatCustomData(void *itr, int iTG, char *pData);
/* DEPRECATED */ GC_API int gc_CreateProgFeatPoints(void *itr, double tol, void **point_list);
/* DEPRECATED */ GC_API int gc_GetProgOpNum(void *itr, int *iOp);
/* DEPRECATED */ GC_API int gc_GetProgNextOpNum(void *itr, int *iOp);
/* DEPRECATED */ GC_API int gc_GetProgState(void *itr, int *iState);
/* DEPRECATED */ GC_API int gc_GetProgFeatCount(void *itr, int *iCount);
/* DEPRECATED */ GC_API int gc_GetProgFeatIndex(void *itr, int *iIndex);
/* DEPRECATED */ GC_API int gc_GetProgFeatParams(void *itr, double *dStart, double *dEnd);
/* DEPRECATED */ GC_API int gc_GetProgSpindleRPMFixed(void *itr, int *bFixed);
/* DEPRECATED */ GC_API int gc_GetProgSpindleRPM(void *itr, double *dRPM);
/* DEPRECATED */ GC_API int gc_GetProgToolCS(void *itr, int *iCS);
/* DEPRECATED */ GC_API int gc_GetProgFeatCS(void *itr, int *iCS);
/* DEPRECATED */ GC_API int gc_GetProgFeatWrapped(void *itr, int *bWrapped);
/* DEPRECATED */ GC_API int gc_GetProgFeatToEdge(void *itr, int *bToEdge);
/* DEPRECATED */ GC_API int gc_GetProgFeatCanned(void *itr, int *bCanned);
/* DEPRECATED */ GC_API int gc_GetProgFeatStartWrapDepth(void *itr, double *dDepth);
/* DEPRECATED */ GC_API int gc_GetProgFeatEndWrapDepth(void *itr, double *dDepth);
/* DEPRECATED */ GC_API int gc_GetProgFeedRate(void *itr, double *dFeed);
/* DEPRECATED */ GC_API int gc_GetProgZPassIndex(void *itr, int *iZPass);
/* DEPRECATED */ GC_API int gc_GetProgZPasses(void *itr, int *iZPasses);
/* DEPRECATED */ GC_API int gc_GetProgOriginIndex(void *itr, int *iOrigin);
/* DEPRECATED */ GC_API int gc_GetProgOrigins(void *itr, int *iOrigins);
/* DEPRECATED */ GC_API int gc_GetProgRotationIndex(void *itr, int *iRotation);
/* DEPRECATED */ GC_API int gc_GetProgRotations(void *itr, int *iRotations);
/* DEPRECATED */ GC_API int gc_GetProgWorkpieceAngles(void *itr, double xParam, double axAngles[3]);
/* DEPRECATED */ GC_API int gc_GetProgWorkpieceRotMatrix(void *itr, double xParam, double *matrix);

// CMachDef functions...

enum gc_eParkLocAxisType
{
	gc_park_axis_abs,
	gc_park_axis_inc,
	gc_park_axis_user,						// node_pos tg datum in part cs
	gc_park_axis_preset,					// tg datum in part station cs
	gc_park_axis_tool_mach_pos,				// cur tool in root cs
	gc_park_axis_short_rot,
	gc_park_axis_tool_clear_can_pos,		// cur tool relative to happy can
	gc_park_axis_num_types,					// must be last
};

GC_API int gc_GetMachDefParkLocName(const CMachDef &mach_def, const char axis_set_name[], int flow, gc_InterOpEvent evt, char park_loc_name[]);
GC_API int gc_GetMachDefParkLocAxisType(const CMachDef &mach_def, const char axis_set_name[], int flow, const char park_loc_name[], const char *axis_name, gc_eParkLocAxisType &type);
GC_API int gc_GetMachDefParkLocAxisVal(const CMachDef &mach_def, const char axis_set_name[], int flow, const char park_loc_name[], const char *axis_name, double &val);
GC_API int gc_SetMachDefParkLocAxisType(CMachDef &mach_def, const char axis_set_name[], int flow, const char park_loc_name[], const char *axis_name, gc_eParkLocAxisType type);
GC_API int gc_SetMachDefParkLocAxisVal(CMachDef &mach_def, const char axis_set_name[], int flow, const char park_loc_name[], const char *axis_name, double val);

//--Tool control

enum gc_teTCType
{
	gc_eTC_FullRetract,					// full up
	gc_eTC_UserPosition,				// ask user
	gc_eTC_PresetPosition,				// use stored position
	gc_eTC_NoMove,						// no move
	gc_eTC_Zero							// zero is used for Axes A, B & C only
};

GC_API int gc_GetLinTCVal(long iWP, long iTG, int iAxis, double *dval);
GC_API int gc_SetLinTCVal(long iWP, long iTG, int iAxis, double dVal );
GC_API int gc_GetTCLinAxisType(long iWP, long iTG, int iAxis, gc_teTCType *peType);
GC_API int gc_SetTCLinAxisType(long iWP, long iTG, int iAxis, gc_teTCType peType);

//******************* TOOL  ************************


//ENUMERATIONS
// tool info
enum
{	gc_eMillTool,
	gc_eLatheTool,
	gc_eNoTool
};

enum
{	gc_eHSS = 1,
	gc_eHSS_TiN_Coated,
	gc_eCarbide_Insert,
	gc_eCarbide_Insert_Coated,
	gc_eCarbide_Solid,
	gc_eDiamond,
	gc_eCeramic,
	gc_eOther
};

enum
{	gc_rEM,
	gc_fEM,
	gc_bEM,
	gc_shell,
	gc_face,
	gc_key_cutter,
	gc_drill,
	gc_center_drill,
	gc_spot_drill,
	gc_bore,
	gc_tap,
	gc_csink,
	gc_reamer,
	gc_spot_face,
	gc_fly_cut,
	gc_thd_mill,
	gc_bbore,
	gc_rigid_tap,
	gc_roundover,
	gc_form,
	gc_combo,
	gc_custom,
	gc_lollipop,
	gc_eNumMTools
};

enum
{	gc_eDiam80,
	gc_eDiam55,
	gc_eDiam35,
	gc_eRound,
	gc_eSquare,
	gc_eTriangle,
	gc_eTrigon,
	gc_ePentagon,
	gc_ePara55,					// parallelogram
	gc_eRectangle,
	gc_eGroove,					// two cutting radii
	gc_eCutOff,					// two cutting radii
	gc_eThread1,				// groove style
	gc_eThread2,				// Kennemetal LT style
	gc_eVProfiler35,			// Kennemetal VN style
	gc_eForm,
	gc_eUtilTool,
};

enum
{	gc_eVQ1,					/* vertical tool holder, tool in quadrant 1 */
	gc_eVQ2,					/* vertical tool holder, tool in quadrant 2 */
	gc_eVQ3,					/* vertical tool holder, tool in quadrant 3 */
	gc_eVQ4,					/* vertical tool holder, tool in quadrant 4 */
	gc_eHQ1,					/* horizontal tool holder, tool in quadrant 1 */
	gc_eHQ2,					/* horizontal tool holder, tool in quadrant 2 */
	gc_eHQ3,					/* horizontal tool holder, tool in quadrant 3 */
	gc_eHQ4						/* horizontal tool holder, tool in quadrant 4 */
};

enum
{
	gc_eTlHolder,
	gc_eBoringBar,
	gc_eNoHolder,	//this is actually other
	gc_eCustomHolder,
	gc_eNoneNoBHolder,
};

enum
{	gc_eMTWest,
	gc_eMTNorth,
	gc_eMTEast,
	gc_eMTSouth					/* Direction the Mill Tool is pointing */
};	
enum
{
	gc_eBT_Flange_30,
	gc_eBT_Flange_35,
	gc_eBT_Flange_40,
	gc_eBT_Flange_45,
	gc_eBT_Flange_50,
	gc_eBT_Flange_60,
	gc_eCAT_30,
	gc_eCAT_35,
	gc_eCAT_40,
	gc_eCAT_45,
	gc_eCAT_50,
	gc_eCAT_60,
	gc_eDIN698_Taper_30,
	gc_eDIN698_Taper_40,
	gc_eDIN698_Taper_45,
	gc_eDIN698_Taper_50,
	gc_eHSK_40a,
	gc_eHSK_50a,
	gc_eHSK_63a,
	gc_eHSK_80a,
	gc_eHSK_100a,
	gc_eNMTB_30,
	gc_eNMTB_40,
	gc_eNMTB_45,
	gc_eNMTB_50,
	gc_eNone_Hldr,
	gc_eHSK_32a,
	gc_eHSK_25a,
	gc_eCapto_C3,
	gc_eCapto_C4,
	gc_eCapto_C5,
	gc_eCapto_C6,
	gc_eCapto_C8,
	gc_eNumofBackside
};

/**
*Frontend holder type enumeration
*valid for mill tools ONLY
*/
//--tool callbacktypedef enum
typedef enum
{
	gc_eToolCB_BeforeLoad,			// Before User double clicked on tool - No Callback Data
	gc_eToolCB_AfterLoad,			// After User double clicked on tool - No Callback Data
	gc_eToolCB_BitMap,				// to set tile graphics on per tool basis; if return value != 0, Callback Data is a BITMAP*, set with bitmap to use
	gc_eToolCB_HolderBtn,			// called when holder button is pressed
	gc_eToolCB_ToolWinClosed,		// called when the tool window ( mill or lathe ) is closed
	gc_eToolCB_BeforeDelete,
	gc_eToolCB_AfterDelete,
	gc_eToolCB_ToolChanged,			// Tool data has changed
	gc_eToolCB_OffsetBtn,
	gc_eToolCB_ITChanged,			// intermediate tooling data has changed
} gc_teToolCallBack;


typedef enum
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
} gc_teMHolderDesc;

/**
*Mill Holder Values
*/

typedef enum
{
	gc_eMToolHolder,	//Database
	gc_eMCustom,		//Plugin	
	gc_eMNone
}gc_eMHolderOpt;
//--Tool Holder 
typedef enum
{
	gc_eNoToolHolder,
	gc_eAutomaticToolHolder,
	gc_eExtrudedPathToolHolder,
	gc_eRevolvedPathToolHolder,
	gc_eSolidToolHolder,
	gc_eExternalToolHolder
} gc_teToolHolderType;
typedef enum 
{
	gc_eToolErrNoErr = 0,
	gc_eToolErrNum,
	gc_eToolErrType,
	gc_eToolErrTG,
} gc_teToolErr;
//STRUCTURE

//DECLARATIONS
GC_API int gc_GetTGName(int iTG, char *sName);
GC_API int gc_GetStandardToolChange ( int iWP, int iTG, double *dVal );
GC_API int gc_SetStandardToolChange( int iWP, int iTG, double *dVal );
GC_API int gc_GetTGToPartMatrix(int iTG, int iWP, double *matrix);
GC_API int gc_GetPartToTGMatrix(int iWP, int iTG, double *matrix);
GC_API int gc_GetToolAxisVec(int iTool, int iWP, double xTGAngle, double *vec);
GC_API int gc_GetToolOrientMatrix(int iTool, int iWP, const double *axTGAngles, double *mx);
GC_API int gc_GetToolToTGVec(int iTool, int iWP, double xTGAngle, double *vec);
GC_API int gc_GetToolToTGVecEx(int iTool, int iWP, const double *tg_angles, double *vec);
GC_API int gc_GetToolToTGVec(int iTool, int iWP, double xTGAngle, double *vec);
GC_API int gc_GetToolTipCenterToPresetVec(int iTool, int iWP, double *vec);
GC_API int gc_GetToolTipCenterToPresetVecEx(int iTool, int iWP, double xTGAngle, double *vec);
GC_API int gc_GetNumTools(int *iNum);
GC_API int gc_GetNumToolsEx(int *iNum, int include_incomplete);
GC_API int gc_GetFreeTool(int *iIndex);
GC_API int gc_GetLastTool(int *iIndex);
GC_API int gc_GetToolIndexList(int *iList);
GC_API int gc_GetToolIndexListEx(int *iList, int include_incomplete);
GC_API int gc_SortTools();
GC_API int gc_ReorderTools(int iNumTools, int* iNewToolList);
GC_API int gc_GetToolInfoI(int iIndex, int id, int *iVal);
GC_API int gc_GetToolInfoD(int iIndex, int id, double *dVal);
GC_API int gc_GetToolInfoS(int iIndex, int id, char *sVal);
GC_API int gc_SetToolInfoI(int iIndex, int id, int *iVal);
GC_API int gc_SetToolInfoD(int iIndex, int id, double *dVal);
GC_API int gc_SetToolInfoS(int iIndex, int id, char *sVal);
GC_API int gc_GetNumSelTools(int *iNum);
GC_API int gc_GetSelToolIndexList(int *iList);
GC_API int gc_DeleteTool(int iIndex);
GC_API int gc_OpenTool(int iCell);
GC_API int gc_GetToolError(int iTool, int *iToolError);
GC_API int gc_CreateDrillTool(int iIndex, double dRad, double dTipAngle);
GC_API int gc_CreateMillTool(int iIndex, double dRad, double dCorn, double dLength);
GC_API int gc_CreateLatheTool(int iIndex, int iType, double dTipRad, double dInsertAngle, double dSize, int iOrient);
GC_API int gc_GetLTlTrailingEdgeAngle(int tool, double* angle);
GC_API int gc_GetToolSectionPath(int iTool, void **ptrPath);
GC_API int gc_SetToolSectionPath(int iTool, void *ptrPath);
GC_API int gc_GetToolShape(int iTool, double dTol, int iMode, int *nb, double *dShape);
GC_API int gc_GetToolSectionPathEx( int iTool, int iHalf, void **ptrToolPath, void** ptrShankPath );
GC_API int gc_GetCurToolTile(int *piTile);
GC_API int gc_GetCurProcTile(int *piTile);
GC_API int gc_GetCurOpTile(int *piTile);
// The following API calls ONLY work on feedrate markers. These routines are obsolete.
// Use the cooresponding Ex calls instead.
GC_API int gc_AddUtilTool( int iOp, int iUTType, int iFeature, double dParam, double dVal, int *piIndex );
GC_API int gc_GetUtilTool( int iOp, int *piUTType, int *piFeature, double *dParam, double *dVal, int iIndex );
GC_API int gc_GetNumUtilTool( int iOp, int *iCount );
GC_API int gc_DeleteUtilTool( int iOp, int iIndex );
GC_API int gc_SetUtilTool(int iOp, int iIndex, int iUTType, double dVal);
GC_API int gc_DeleteUtilToolList(int iOp);
GC_API int gc_GetUtilToolList( int iOp, int *piUTType, int *piFeature, double *pdParam, double *pdVal );
GC_API int gc_SetUtilToolList( int iOp, int iNum, int *piUTType, int *piFeature, double *pdParam, double *pdVal);
// End of obsolete block
GC_API int gc_IsUtilMarkerDlogOpen();
GC_API int gc_CloseUtilMarkerDlog();
GC_API int gc_OpenUtilMarkerDlog(int iOp);
GC_API int gc_GetUtilMarkerDlogOp();
GC_API int gc_AddUtilToolEx(int iOp, int iUTType, int iUTSubType, int lFeature, double dParam, double dVal, int iVal, const char *sText, int *plIndex);
GC_API int gc_GetUtilToolEx(int iOp, int *pUTType, int *pUTSubType, int *pFeature, double *dParam, double *dVal, int *iVal, char *sText, int lIndex);
GC_API int gc_SetUtilToolEx(int iOp, int iIndex, int iUTType, int iUTSubType, double dVal, int iVal, const char *sText);
GC_API int gc_GetUtilToolListEx( int iOp, int *piUTType, int *piUTSubType, int *piFeature, double *pdParam, double *pdVal, int *piVal, char psText[][256] );
GC_API int gc_SetUtilToolListEx(int iOp, int iNum, const int *piUTType, const int *piUTSubType, const int *piFeature, const double *pdParam, const double *pdVal, const int *piVal, const char psText[][256]);
GC_API int gc_GetNumUtilToolEx( int iOp, int *iCount );
GC_API int gc_DeleteUtilToolEx( int iOp, int iIndex );
GC_API int gc_DeleteUtilToolListEx(int iOp);
GC_API int gc_GetNormRotAngles(const double *norm, double *angles, int iWP = 1, int iTG = 1, int iTool = 0);
//--attributes
GC_API int gc_AddToolAttList(int iTool, void **attlist);
GC_API int gc_GetToolAttList(int iTool, void **attlist);
GC_API int gc_DeleteToolAttList(int iTool);
//--Tool Holder 
GC_API int gc_GetToolHolderType(int iTool, int *pnToolHolderType);
GC_API int gc_SetToolHolderType(int iTool, int nToolHolderType);
GC_API int gc_GetToolHolderAutomatic(int iTool, int *pnAutomatic);
GC_API int gc_SetToolHolderAutomatic(int iTool, int nAutomatic);
GC_API int gc_GetToolHolderDimensions(int iTool, double* dDimensions);
GC_API int gc_SetToolHolderDimensions(int iTool, double* dDimensions);
GC_API int gc_GetToolHolderSolidRef(int iTool, int *pnSolidRef);
GC_API int gc_SetToolHolderSolidRef(int iTool, int nSolidRef);
GC_API int gc_GetToolHolderExternalRef(int iTool, char* sExtRef);
GC_API int gc_SetToolHolderExternalRef(int iTool, char* sExtRef);
GC_API int gc_GetToolHolderComment(int iTool, char* sComment);
GC_API int gc_SetToolHolderComment(int iTool, char* sComment);
GC_API int gc_GetToolHolderMatrix(int iTool, double* dMatrix);
GC_API int gc_SetToolHolderMatrix(int iTool, double* dMatrix);
GC_API int gc_GetToolHolderPath(int iTool, void **ptrPath);
GC_API int gc_SetToolHolderPath(int iTool, void *ptrPath);
GC_API int gc_GetToolHolderPos(int iTool, double* dPos);
GC_API int gc_SetToolHolderPos(int iTool, double* dPos);
GC_API int gc_GetMTlHldrBacksideDnH(int iTool, double *dDia, double *dHeight );
/**
*Used to Get the path of the front portion of the Tool Holder for a specified MILL tool
*
*@param	iTool	Tool Index
*@param **pPath	pointer to a Path object to hold the returned path
*@return		-1 pPath is invalid, 
*@return		-2 invalid Tool, 
*@return		0 for success
*@see			gc_PathCreate
*/
GC_API int gc_GetMTlHldrFrontPath( short iTool, void **pPath );
/**
*Used to set the type of Front Holder for a specified Mill Tool
*
*@param	iTool	Tool Index
*@param iType	Value to set for the holder front end.  Valid values between the range gc_eBore_Hldr and gc_eNoMHolder
*@return		-1 for invalid tool, 
*@return		-2 & -3 for invalid iType, 
*@return		0 for success
*/
GC_API int gc_SetMTlFrontHolderType( int iTool, int iType );
/**
*Used to get the type of Front Holder for a specified Mill Tool
*
*@param	iTool	Tool Index
*@param *iType	Pointer to return the front tool holder type
*@return		-1 for invalid tool, 
*@return		-2 NULL iType
*@return		0 for success
*/
GC_API int gc_GetMTlFrontHolderType( int iTool, int *iType );
//--toolgroup
GC_API int gc_GetTGHasLinAxis(long iTG, int iAxis, bool *pbHasAxis);
GC_API int gc_GetTGLinAxisLimits(long iTG, int iAxis, bool *pbLimited, double *axLimits);
GC_API int gc_GetTGHasRotAxis(long iTG, int iAxis, bool *pbHasAxis);
GC_API int gc_GetTGPosition(int iTG, double *paxPos);
GC_API int gc_GetTGRotAxes(long iTG, int *piAxis4th, int *piAxis5th);
GC_API int gc_GetTGRotAxisInfo(long iTG, teMachRotAxis eAxis4or5, double *pdPos, double *pdRotVec, double *pdZeroVec);
GC_API int gc_GetTGRotAxisLimits(long iTG, teMachRotAxis eAxis4or5, int *pbLimited, double *axLimits);
GC_API int gc_GetTGCalcTlOffsets(long iTG, bool *pbCalc);
GC_API int gc_GetTGHolderAttachPos(long iTG, double *pos);
GC_API int gc_GetTGReverseB(long iTG, int *pbReversB);
GC_API int gc_GetTGBOffset(long iTG, double *xBOffset);
GC_API int gc_HasExtToolChange(void);
GC_API int gc_IsGeneric(void);
GC_API int gc_RotaryAxisLimitsEnabled( void);
GC_API int gc_SmartInteropClearance(void);
GC_API int gc_GetDefMachSimModelFilename( char *sFilename );
GC_API int gc_GetDefPostFilename( char *sFilename );
GC_API int gc_GetCSS_RPM(double radius, double supm, double max_rpm, double *rpm);		// calc rpm from radius and css params ('supm' is surface units (in/meters) per min)

/**
*Set the back end holder type ( as seen in the Document Control Dialog ) for the supplied Toolgroup 
*@param	iTG	Toolgroup to set back end type 
*@param iBackHolder	Type of back end - valid values range between gc_eBT_Flange_30 and gc_eNone_Hldr
*
*@return	-1	invalid Toolgroup
*@return	-2	invalid Back end
*@return	0	successful
*/
GC_API int gc_SetTGBackHolder( long iTG, int iBackHolder );
/**
*Get the back end holder type ( as seen in the Document Control Dialog ) for the supplied Toolgroup 
*@param	iTG	Toolgroup to set back end type 
*@param iBackHolder	Pointer to holder the returned value
*
*@return	-1	invalid Toolgroup
*@return	-2	*iBackHolder is NULL or otherwise invalid
*@return	0	successful
*/
GC_API int gc_GetTGBackHolder( long iTG, int *iBackHolder );

//CALLBACKS
typedef int (*gc_tToolCallBack)(int, void *pCBData);
GC_API int gc_SetToolCallBack(int iCB, gc_tToolCallBack);
GC_API int gc_ClearToolCallBack(int iCB, gc_tToolCallBack);

//******************* IMPORT/EXPORT  ************************

//ENUMERATIONS
enum
{
	gc_eParasolidFile = 0,
	gc_eParasolidBinaryFile = 1,
	gc_eParasolidPartition = 2
};
//DECLARATIONS
GC_API int gc_AskSolidFileOpenOptions();
GC_API int gc_AskSolidFileImportOptions();
GC_API int gc_MapImportAttributes();
GC_API int gc_ImportIgesFile(char *sFileName, gc_ImportFilter *pFilter, char *szLogFile, int(*pCommentProc)(int,int,int,char*,char*));
GC_API int gc_ImportDXFFile(char *sFileName, gc_ImportFilter *pFilter, char *szLogFile, int(*pCommentProc)(int,int,int,char*,char*));
GC_API int gc_ImportParasolidFile(char *sFileName);
GC_API int gc_ImportParasolidFileEx(char *sFileName, int iMode, int iCS);
GC_API int gc_ImportRhinoFile(char *sFileName);
GC_API int gc_ImportInventorFile( char *sFileName );
/** gc_GenericImportFile
*This import will attempt to import the based on the file extension.  This must be the full path to the file
*
*@param	sFileName	full path and file name
*@return			0 for success; negative return values indicate the import failed.
*/
GC_API int gc_GenericImportFile( char *sFileName );
GC_API int gc_GenericOpenFile( char *sFileName );

GC_API int gc_ExportParasolidFile(char *sFileName, int iVersion);
GC_API int gc_ExportParasolidFileEx(char *sFileName, int iVersion, int iFileType, int iDeleteAttributes);
GC_API int gc_InitImportFilter(gc_ImportFilter *pFilter);
GC_API int gc_ExportDXFFile(char *sFileName, gc_ExportFilter *pFilter);
GC_API int gc_STLExportTol(char *sFileName, int iSolid, double dFacetAccy);
GC_API int gc_STLExportBinaryTol(char *sFileName, int iSolid, double dFacetAccy);
GC_API int gc_ImportSolidEdgeFile(char *sFileName); // DEPRECATED (Maybe)
GC_API int gc_ImportSolidEdgePart(char *sFileName);
GC_API int gc_ImportSolidEdgeAssembly(char *sFileName);
GC_API int gc_ImportSolidWorksFile(char *sFileName);
GC_API int gc_ImportAcisFile(char *sFileName, double dScale, bool bUnstitch, bool bShowDialog );
GC_API int gc_ImportSolidWorksFileEX( char *sFileName, int iAssembly, int iEnableUI );
GC_API int gc_AddImportFilter(char *sTitle, char *sFilter, int (*cb_import)(char *sFileName));
GC_API int gc_AddImportFilterEx(char *sTitle, char *sFilter, int (*cb_import)(char *sFileName), int iType);
GC_API int gc_AddImportFilterEx2(char *sTitle, char *sFilter, int (*cb_import)(char *sFileName), int iType, int (*cb_can_open)(char *sFileName));
GC_API int gc_AddImportFilterEx3(char *sTitle, char *sFilter, int (*cb_import)(char *sFileName), int iType, int (*cb_can_open)(char *sFileName), int iCreateVNC );
GC_API int gc_GetImportFilterCount(int *piNum);
GC_API int gc_GetImportFilter(int nFilter, char *sTitle, char *sFilter, int (**cb_import)(char *sFileName));
GC_API int gc_AddExportFilter(char *sTitle, char *sFilter, int (*cb_export)(char *sFileName));
#ifndef EDU_NO_POST
GC_API int gc_AddPostFilter(char *sTitle, char *sFilter, int (*cb_post)(char *sPostName, char *sNCFName));
#endif 
//--solid import
GC_API int gc_GetSolidImportPreserveFileUnits( int *bPreserveFileUnits);
GC_API int gc_GetSolidImportScaleType( int *nScaleType );		// 0 => Uniform Shrinkage, 1 => Scale Factor
GC_API int gc_GetSolidImportShrinkage( double *lfShrinkage );
GC_API int gc_GetSolidImportScaleFactor( double *lfScaoutleFactor );
GC_API int gc_GetSolidImportSolidify( int *bSolidify );
GC_API int gc_GetSolidImportRemoveUnTopology( int *bRemoveUnTopology );
GC_API int gc_GetSolidImportSimplify( int *bSimplify );

GC_API int gc_SetSolidImportPreserveFileUnits( int bPreserveFileUnits);
GC_API int gc_SetSolidImportScaleType( int nScaleType );
GC_API int gc_SetSolidImportShrinkage( double lfShrinkage );
GC_API int gc_SetSolidImportScaleFactor( double lfScaleFactor );
GC_API int gc_SetSolidImportSolidify( int bSolidify );
GC_API int gc_SetSolidImportRemoveUnTopology( int bRemoveUnTopology );
GC_API int gc_SetSolidImportSimplify( int bSimplify );

//--solid export
/** gc_SolidToSTL
* Export solid to STL.  Selected faces and unselected faces will go to separate files as defined in the parameters explained below
*@param		int cs_for_xform: CS to transform solid orientation to
*@param		char* selface_file_name: file name for selected solids STL output
*@param		char* selface_header: header for selected solids STL output
*@param		char* unselface_file_name: file name for unselected solids STL output
*@param		char* unselface_header: header for unselected solids STL output
*@return	0= success, 
*/
GC_API int gc_SolidToSTL( int coord_sys, char* selface_file_name, char* selface_header, char* unselface_file_name=NULL, char* unselface_header=NULL );

/** gc_SolidToSTLEx
* Export solid to STL.  Selected faces and unselected faces will go to separate files as defined in the parameters explained below
*@param		int cs_for_xform: CS to transform solid orientation to
*@param		char* selface_file_name: file name for selected solids STL output
*@param		char* selface_header: header for selected solids STL output
*@param		char* unselface_file_name: file name for unselected solids STL output
*@param		char* unselface_header: header for unselected solids STL output
*@param		double dTol: Tolerance for facet calculation
*@return	0= success, 
*/

GC_API int gc_SolidToSTLEx( int coord_sys, char* selface_file_name, char* selface_header, char* unselface_file_name, char* unselface_header, double dTol );

/** gc_SolidToSTLEx2
* Export the solid to STL using the given selection type ( only faces of the selection type will be exported )
*@param		int solid_id: solid to export faces of
*@param		gc_teSelectMode sel_type: selection type to export
*@param		int coord_sys: CS to transform the solid into
*@param		char* file_name: file name for facet body's STL output
*@param		char* header: header for facet body STL output
*@param		double dTol: tolerance for export faceting 
*@return	0=success,
*@return	-1=invalid solid 
*@return	-2=no filename given
*@return	-3=could not open file
*@return	-4=invalid seleciton state
*@return	-5=no faces to output
*/
GC_API int gc_SolidToSTLEx2( int solid_id, gc_teSelectMode sel_type, int coord_sys, char* file_name, char* header, double dTol );

/** gc_FacetBodyToSTL
* Export facet body to STL.
*@param		int cs_for_xform: CS to transform facet body orientation to
*@param		int solid_ref: solid ID for the facet body to output
*@param		const char* file_name: file name for facet body's STL output
*@param		const char* header: header for facet body STL output
*@return	0=success,
*@return	-1=bad solid reference,
*@return	-2=solid is not a facet body
*/
GC_API int gc_FacetBodyToSTL(int coord_sys, int solid_ref, const char* file_name, const char* header);

/** gc_DefaultStockToSTL
* Export the default stock ( cube or cylinder) to STL.
*@param		int iWP: Workpiece to general the default stock condition for
*@param		int coord_sys: CS to transform the solid into
*@param		char* file_name: file name for facet body's STL output
*@param		char* header: header for facet body STL output
*@return	0=success,
*@return	-1=part not open, 
*@return	-2=no filename given
*@return	-3=could not open file
*@return	-4=no faces
*@return	-5=invalid workpiece
*/

GC_API int gc_BufferSolidFacesOfType(int solid_id, gc_teSelectMode sel_type, int coord_sys, void **pFacesBuffer);
GC_API int gc_BufferedFacesToSTL(void *pFacesBuffer, char* file_name, char* header, double dTol );
GC_API int gc_DeleteBufferedFaces( void * pFacesBuffer );

GC_API int gc_DefaultStockToSTL( int iWP, int coord_sys, char* file_name, char* header );

struct gc_tFacetRep;

GC_API int gc_FiletoFacetRep(const char* filename, gc_tFacetRep* facetRep);
enum
{
	gc_eFileToFacetRep_Auto = 0,
	gc_eFileToFacetRep_STL  = 1,
	gc_eFileToFacetRep_FB   = 2
};

GC_API int gc_FiletoFacetRep2(const char* filename, gc_tFacetRep* facetRep, int flags);
GC_API int gc_FreeFacetRep(gc_tFacetRep* facetRep);

struct gc_tFacetRep
{
	gc_tFacetRep() : nverts(0), verts(nullptr), nindices(0), indices(nullptr), norms(nullptr), nfacets(0), facetcolors(nullptr)
	{}
	~gc_tFacetRep()
	{
		gc_FreeFacetRep(this);
	}
	int Read(const char* filename, int flags = gc_eFileToFacetRep_Auto)
	{
		return gc_FiletoFacetRep2(filename, this, flags);
	}
	int     nfacets;		//number of facets(triangles) in body
	int     nverts;			//number of vertices in body (typically 3 x the number of facets)
	float*  verts;			//the XYZ coordinate values for each vertex (3 x the number of vertices) 
	int     nindices;		//number of indices for facets (3 x the number of facets)
	int*    indices;		//index of each vertex in each facet.
	float*  norms;			//the normalized XYZ values for vertices for each facet (3 x 3 x the number of facets)
	int*    facetcolors;	//the COLORREF (4 byte RGB value - 0x00rrggbb) for  each facet (the number of facets) 
};

//CALLBACKS
GC_API int gc_SetFileIOCallBack(int iCB, void (*call_back)(gc_rFileCBData*));
GC_API int gc_ClearFileIOCallBack(int iCB, void (*call_back)(gc_rFileCBData*));

//******************* MDD  ************************

//STRUCTURE

enum gc_AxisNodeType
{
	gc_LinearAxis,
	gc_RotaryAxis,
	gc_UnspecifiedAxisType
};

// the following inline functions create node ids that are valid regardless of tree instance...

inline gc_kNodeID gc_MakeRootNode()
{
	return gc_kNodeID(gc_kNodeID::root, 0);
}

inline gc_kNodeID gc_MakeTGNode(int iTG)
{
	return gc_kNodeID(gc_kNodeID::mdd_tg, iTG);
}

inline gc_kNodeID gc_MakeWPNode(int iWP)
{
	return gc_kNodeID(gc_kNodeID::mdd_wp, iWP);
}

inline gc_kNodeID gc_MakeUtilNode(int iUtil)
{
	return gc_kNodeID(gc_kNodeID::mdd_util_comp, iUtil);
}

inline gc_kNodeID gc_MakeToolNode(int iTool)
{
	return gc_kNodeID(gc_kNodeID::vnc_tool, iTool);
}

inline gc_kNodeID gc_MakeToolTouchOffNode(int iTool)
{
	return gc_kNodeID(gc_kNodeID::vnc_tool_touch_off, iTool);
}

inline gc_kNodeID gc_MakeHolderAttachNode(int iTool)
{
	return gc_kNodeID(gc_kNodeID::vnc_holder_attach, iTool);
}

inline gc_kNodeID gc_MakePartCSNode(int iWP)
{
	return gc_kNodeID(gc_kNodeID::vnc_part_cs, iWP);
}

// gc_kNodeID identifies a node in the kinematic tree


inline bool operator == (const gc_kNodeID &lhs, const gc_kNodeID &rhs)
{
	return (lhs.type == rhs.type) && (lhs.val1 == rhs.val1) && (lhs.val2 == rhs.val2);
}

inline bool operator != (const gc_kNodeID &lhs, const gc_kNodeID &rhs)
{
	return !(lhs == rhs);
}

//DECLARATIONS
GC_API int gc_GetMDDCount ( void );
GC_API int gc_GetCurrentMDD ( void );
GC_API int gc_GetMDDInfoI ( int iMDD, gc_teMDDInfo eType, int *iVal );
GC_API int gc_GetMDDInfoS ( int iMDD, gc_teMDDInfo eType, char *sVal );
GC_API int gc_SetCurrentMDD ( int iMDD );
GC_API int gc_SetCurrentMDDFromFilename ( char *sMDDFilename );
GC_API int gc_ClearMDDCache(int iMDD);		// force cached mdd to be reloaded from file
GC_API int gc_GetMDDNumCoolant(int *iNum);
GC_API int gc_GetMDDCoolant(int iIndex, int *iType, char *sName);
GC_API int gc_GetMDDNumCustomDrill( int *iNum );
GC_API int gc_GetMDDCustomDrill( int iIndex, int *iType, char *sName );
GC_API int gc_GetMDDCustomDrillMacroID(int iIndex, char *sID);
GC_API int gc_SaveCurrentMDD(char *sFileName);
GC_API int gc_GetPartMDDFileName(char *sFileName);
GC_API int gc_SavePartMDD(char *sFileName);

//--kinematic trees, nodes, and related

struct gc_kNodeVisitor
{
	virtual void visit(const gc_kNode *node)	= 0;
	virtual bool done() const					{ return false; }
	virtual ~gc_kNodeVisitor()					{}
};

GC_API int gc_MakeMDDTree(gc_kNode **tree);							// returns complete tree, minus tool nodes; solely owned; must be deleted
GC_API int gc_CreateEmptyNode(gc_kNode **node);						// returns a node pointer to nothing
GC_API int gc_CopyTree(const gc_kNode *tree, gc_kNode **new_tree);	// returns deep copy of 'tree'; solely owned; must be deleted
GC_API int gc_CopyNode(const gc_kNode *node, gc_kNode **new_node);	// returns shallow copy of 'node'; shared ownership; must be deleted
GC_API int gc_DeleteNode(gc_kNode *node);							// give up ownership of 'node' (which may be solely owned or shared).  Used for both trees and nodes

// node finding...
GC_API int gc_FindNodeFromName(const gc_kNode *tree, const char *name, gc_kNode **node);// returns whether node was found; if so, returned 'node' shares ownership with tree
GC_API int gc_FindNodeFromID(const gc_kNode *tree, gc_kNodeID node_id, gc_kNode **node);	// returns whether node was found; if so, returned 'node' shares ownership with tree
GC_API int gc_VisitNodes(const gc_kNode *tree, gc_kNodeVisitor &visitor);					// general purpose way to traverse the tree

// node query functions...
GC_API int gc_IsNodeEmpty(const gc_kNode *node, bool &empty);
GC_API int gc_GetNodeID(const gc_kNode *node, gc_kNodeID &node_id);
GC_API int gc_GetNodeName(const gc_kNode *node, char name[/*at least 32*/]);
GC_API int gc_GetNodeUserName(const gc_kNode *node, char user_name[/*at least 32*/]);
GC_API int gc_GetNodeParent(const gc_kNode *node, gc_kNode **parent_node);
GC_API int gc_GetNodeChildCount(const gc_kNode *node, int &n_children);
GC_API int gc_GetNodeChild(const gc_kNode *node, int child_ix, gc_kNode **child_node);
GC_API int gc_GetNodeTransform(const gc_kNode *datum_node, const gc_kNode *ref_node, gc_AxisCategorySet zeroed, double *matrix);
GC_API int gc_GetNodeRotaryAxisData(const gc_kNode *node, double *vec, double *pos);
GC_API int gc_GetNodeLinearAxisData(const gc_kNode *node, double *vec);
GC_API int gc_GetAxisNodeInfo(const gc_kNode *node, gc_AxisNodeType *type, int *axis_ix);	// 'axis_ix' => X, Y, Z (or A, B, C)
GC_API int gc_GetAxisNodeLimits(const gc_kNode *node, bool *pbLimited, double *axLimits);
GC_API int gc_GetAxisNodeVal(const gc_kNode *node, double *val);

GC_API int gc_SetNodePos(gc_kNode *tree, gc_InterpSet &interp_set, gc_AxisCategorySet zeroed, const double *pos);
GC_API int gc_SetAxisNodeVal(gc_kNode *node, double val);

GC_API int gc_GetNodeId(int *iType, unsigned int *iID);
GC_API int gc_LoadToolNode(const gc_kNode *tree, int tool);
GC_API int gc_OptionAvail(int iOption, int *iAvail);
GC_API int gc_GetLanguage(int *iLang);
GC_API int gc_GetCultureName ( char* buffer, int inLen );

// Check if current MDD has rotary (used in GUI display in pluggin)
GC_API bool gc_HasRotary(void);
GC_API bool gc_HasRotaryWrap(void);
GC_API void gc_RotaryAxisName(char *strName);
//CALLBACKS
//--MDD event
typedef void (*gc_tMDDEventCallBack)(char*,char*);
GC_API int gc_SetMDDEventCallBack ( gc_teMDDEventCallBack	eEvent, gc_tMDDEventCallBack);
GC_API int gc_ClearMDDEventCallBack ( gc_teMDDEventCallBack	eEvent, gc_tMDDEventCallBack);


//******************* SOLID  ************************

//ENUMERATIONS
//--surface
enum
{
	gc_eSurfPlane = 0,
	gc_eSurfSphere,
	gc_eSurfCyl,
	gc_eSurfCone,
	gc_eSurfTorus,
	gc_eSurfSpun,
	gc_eSurfExtruded,
	gc_eSurfOffset,
	gc_eSurfBSpline,
	gc_eSurfBlend
};

//STRUCTURE
struct gc_TempBody;

//DECLARATIONS

//--solid creation

GC_API int gc_ImportParaBody(int iBody);
GC_API int gc_DeleteSol(int iSolId, int bRedraw);
GC_API int gc_CreateSolExtrude(double *dVec, double dStart, double dEnd, int iMakeSolid, int *iSolRef);
GC_API int gc_CreateSolExtrudeEx(double *dVec, double dStart, double dEnd, int iTaper, double dAngle, int iMakeSolid, int *iSolRef);
GC_API int gc_CreateSolRevolve(int iHaxis, double dAxisVal, double dAngle, int *iSolRef);
GC_API int gc_CreateSolLoft(int iAlignment, int iClosed, int *iSolRef);
GC_API int gc_TrimSheet(int iSheetId, void *ptrPath, int iPathCS, int bDestroy, int *iTrimmedSheetId);
GC_API int gc_UntrimSheet(int iSheetId, int bDestroy, int *iUntrimmedSheetId);
GC_API int gc_ExtendSheetPoint(int iSheetId, int bDestroy, double *pPoint, int *iExtSheetId);
GC_API int gc_ExtendSheetBox(int iSheetId, int bDestroy, double *pMinPt, double *pMaxPt, int *iExtSheetId);
GC_API int gc_ProjPathOnBody(int iBody, void *ptrPath, int iPathCS, double *dVec);
GC_API int gc_BodyBoolean(int eBoolType, int iBody1, int iBody2, int *iBody3);

//--solid selection

GC_API int gc_ClearSolSel(int iRedraw);
GC_API int gc_ClearSolSelEx(int iSelMode, int iRedraw);
GC_API int gc_AddSolSel(int iRef, int iRedraw);
GC_API int gc_AddSolFaceSelLM(int iSolRef, gc_TopoId FaceRef, int iRedraw);
GC_API int gc_AddSolEdgeSelLM(int iSolRef, gc_TopoId EdgeRef, int iRedraw);
GC_API int gc_AddSolFaceSelLM2(int iSolRef, gc_TopoId FaceRef, int mode, int iRedraw);
GC_API int gc_AddSolEdgeSelLM2(int iSolRef, gc_TopoId EdgeRef, int mode, int iRedraw);
GC_API int gc_RemoveSolTopoSel(int iSolRef, gc_TopoId topo_id, int iRedraw);
GC_API int gc_GetHandleFacetBodies(int *pbHandle);
GC_API int gc_SetHandleFacetBodies(int bHandle);
GC_API int gc_GetNumSolSel(int iType, int *iNum);
GC_API int gc_ResetSolSel(int iType);
GC_API int gc_GetNextSolSel(int *iRef);
GC_API int gc_GetSolName(int iRef, char *sName);
GC_API int gc_GetFullSolName(int iRef, bool bShowID, bool bShowCreation, char *sName);
GC_API int gc_GetSolComment(int iRef, char *sComment);
GC_API int gc_GetSolFacetTol(int iRef, double *dTol);
GC_API int gc_SetSolName(int iRef, char *sName);
GC_API int gc_SetSolComment(int iRef, char *sComment);
GC_API int gc_GetSolHidden(int iRef, int *pbHidden);
GC_API int gc_SetSolHidden(int iRef, int bHidden);
GC_API int gc_GetSolHistory(int iRef, int *pParentRef1, int *pParentRef2);
GC_API int gc_ClearSolHistory(int iRef);
GC_API int gc_GetSolBodyType(int iRef, int *pBodyType);
GC_API int gc_SetSolDormant(int iRef);
GC_API int gc_SetSolActive(int iRef);
GC_API int gc_GetSolBBox(int iRef, double *dBox);
GC_API int gc_GetFaceBBoxLM(int iSolRef, gc_TopoId FaceRef, double *dBox);
GC_API int gc_GetEdgeBBoxLM(int iSolRef, gc_TopoId EdgeRef, double *dBox);
GC_API int gc_GetFaceBBoxInCS(int iSolRef, gc_TopoId FaceRef, double *dBox);
GC_API int gc_GetEdgeBBoxInCS(int iSolRef, gc_TopoId EdgeRef, double *dBox);
GC_API int gc_GetSolTess(int iRef, int iCS, double dTol, void **result);
GC_API int gc_GetFaceTessLM(int iSolRef, gc_TopoId FaceRef, int iCS, double dTol, void **result);
GC_API int gc_GetFaceTessLMEx(int iSolRef, gc_TopoId FaceRef, int iCS, double dTol, int iMapCS, void **result);
GC_API int gc_GetFaceFacetsLM(int iSolRef, gc_TopoId FaceRef, int *nstrips, void **ppstrips);
GC_API int gc_GetTessFacetCount(void *pTess, int *iNum);
GC_API int gc_GetTessFacets(void *pTess, double *dPts, double *dNorm);
GC_API int gc_GetTessFacetInfo(void *pTess, int *nFacFin, int **piFacFin, int *nFin, int **piFinFin, int **piFinVtx, int **piFinVtx0, int *nVtx, double **dPos, double **dNorm);
GC_API int gc_FreeTess(void *result);
GC_API int gc_GetSolCS(int iRef, int *iCS);
GC_API int gc_SetSolCS(int iRef, int iCS, int iOption, int *iNewSolRef);
GC_API int gc_GetSolId(int iSolRef, int *iId);
GC_API int gc_GetFaceIdLM(int iSolRef, gc_TopoId FaceRef, int *iId);		// parasolid id
GC_API int gc_GetEdgeIdLM(int iSolRef, gc_TopoId EdgeRef, int *iId);		// parasolid id
GC_API int gc_GetTopoGeoIDLM(int iSolRef, gc_TopoId topo_ref, unsigned long *geo_id);	// geometry-only portion of id, for faces and edges
GC_API int gc_UpdateSolidPropertiesDialog(int iSolRef);

//--Custom CAM Selection API
GC_API int gc_GetFaceSelectionMode(int iSolRef, gc_TopoId topo_ref, int *iMode);
GC_API int gc_GetSolNumSelFaces(int iRef, int *iNum);
GC_API int gc_GetSolSelFaceListLM(int iRef, gc_TopoId *List);
GC_API int gc_GetSolSelFaceOrder(int iRef, int *iOrderList);
GC_API int gc_GetSolSelFaceMode(int iRef, int *iModeList);
GC_API int gc_GetSolNumSelEdges(int iRef, int *iNum);
GC_API int gc_GetSolSelEdgeListLM(int iRef, gc_TopoId *List);
GC_API int gc_GetSolSelEdgeOrder(int iRef, int *iOrderList);
GC_API int gc_GetSolSelEdgeMode(int iRef, int *iModeList);
/* DEPRECATED */ GC_API int gc_GetSolSelFaceType(int iRef, int *iModeList);	// use gc_GetSolSelFaceMode instead
GC_API int gc_GetFaceSurfClassLM(int iSolRef, gc_TopoId FaceRef, int *pClass);
GC_API int gc_GetFaceUVBoxLM(int iSolRef, gc_TopoId FaceRef, double *dBox);
GC_API int gc_GetFaceParamInfoLM(int iSolRef, gc_TopoId FaceRef, int *iIsUVBox, double dRange[4], int iBound[4], int iPeriod[2], int iForm[2], int iCont[2]);
GC_API int gc_EvalFacePointLM(int iSolRef, gc_TopoId FaceRef, double u, double v, double *dPoint);
GC_API int gc_EvalFaceNormalLM(int iSolRef, gc_TopoId FaceRef, double u, double v, double *dNormal);
GC_API int gc_EvalFaceDervsLM(int iSolRef, gc_TopoId piFaceRef, double u, double v, int nDervs, double *dDervs);
GC_API int gc_EvalFaceCurvatureLM(int iSolRef, gc_TopoId FaceRef, double u, double v, double *dCurv1, double *dCurv2, double *dN, double *dDir1, double *dDir2);
GC_API int gc_EvalFaceMinRadiusLM(int iSolRef, gc_TopoId FaceRef, double *dMinRadius);
GC_API int gc_EvalFaceGridLM(int iSolRef, gc_TopoId FaceRef, int iNumU, double *dU, int iNumV, double *dV, int nDervs, double *dDervs);
GC_API int gc_EvalFaceParamLM(int iSolRef, gc_TopoId FaceRef, double *dPoint, double *u, double *v);
GC_API int gc_ProjFaceVectorLM(int iSolRef, gc_TopoId FaceRef, double *dPoint, double *dVec, double *dProj);
GC_API int gc_IsPointInFaceLM(int iSolRef, gc_TopoId FaceRef, double *dPoint);
GC_API int gc_GetFaceEdgeBoundsLM(int iSolRef, gc_TopoId FaceRef, gc_TopoId EdgeRef, double *dBox);
GC_API int gc_EvalFaceEdgePointLM(int iSolRef, gc_TopoId FaceRef, gc_TopoId EdgeRef, double t, double *dPoint);
GC_API int gc_EvalFaceEdgeDervsLM(int iSolRef, gc_TopoId FaceRef, gc_TopoId EdgeRef, int iNumDervs, double t, double *dDervs);
GC_API int gc_EvalFaceEdgeParamLM(int iSolRef, gc_TopoId FaceRef, gc_TopoId EdgeRef, double *dPoint, double *t);
GC_API int gc_GetEdgeFacesLM(int iSolRef, gc_TopoId EdgeRef, int *iNumFaces, gc_TopoId *Face1, gc_TopoId *Face2);
GC_API int gc_GetEdgeVertsLM(int iSolRef, gc_TopoId edge_ref, int *iNumVerts, gc_TopoId *vert1, gc_TopoId *vert2);
GC_API int gc_GetVertNumEdgesLM(int iSolRef, gc_TopoId vert_ref, int *iNumEdges);
GC_API int gc_GetVertEdgeListLM(int iSolRef, gc_TopoId vert_ref, gc_TopoId *edge_list);
GC_API int gc_ExtractEdgeAsFeatureLM(int iSolRef, gc_TopoId edge_ref, int iCS, void **feat);
GC_API int gc_GetSolNumFaces(int iRef, int *iNumFaces);
GC_API int gc_GetSolFaceListLM(int iRef, gc_TopoId *FaceList);
GC_API int gc_GetSolFaceListIdLM(int iRef, int *IdList, gc_TopoId *FaceList);
GC_API int gc_GetSolNumEdges(int iRef, int *iNumEdges);
GC_API int gc_GetSolEdgeListLM(int iRef, gc_TopoId *iEdgeList);
GC_API int gc_GetSolFaceNumEdgesLM(int iSolRef, gc_TopoId FaceRef, int *iNumEdges);
GC_API int gc_GetSolFaceEdgeListLM(int iSolRef, gc_TopoId FaceRef, gc_TopoId *EdgeList, int *iEdgeDir);
GC_API int gc_GetSolFaceNumLoopsLM(int iSolRef, gc_TopoId FaceRef, int *iNumLoops);
GC_API int gc_GetSolFaceLoopNumEdgesLM(int iSolRef, gc_TopoId FaceRef, int iLoop, int *iNumEdges);
GC_API int gc_GetSolFaceLoopEdgeListLM(int iSolRef, gc_TopoId FaceRef, int iLoop, gc_TopoId *EdgeList, int *iEdgeDir);
GC_API int gc_PickSolVectorLM(int iSolRef, double *dPoint, double *dVec, int iMax, int *iNum, double *dProj, gc_TopoId *FaceRef);
GC_API int gc_GetNumSol(int *iNum);
GC_API int gc_GetSolList(int *iList);
GC_API int gc_IsSolInBag(int iRef);
GC_API int gc_BagSolid(int iRef);
GC_API int gc_BagSolidEx(int iRef, int open_body_bag);
GC_API int gc_UnBagSolid(int iRef);
enum
{
	gc_eBodyBagMsg_SetTransactionMode = 0,			
	gc_eBodyBagMsg_GetNumPages,			
	gc_eBodyBagMsg_GetActivePage,
	gc_eBodyBagMsg_SetActivePage,
	gc_eBodyBagMsg_GetPageNameLen,
	gc_eBodyBagMsg_GetPageName,
	gc_eBodyBagMsg_SetPageName,
	gc_eBodyBagMsg_InsertPage,
	gc_eBodyBagMsg_DeletePage,
	gc_eBodyBagMsg_MovePage,
	gc_eBodyBagMsg_GetNumPageSolids,
	gc_eBodyBagMsg_GetPageSolids,
	gc_eBodyBagMsg_MovePageSolids,
	gc_eBodyBagMsg_GetSolidPage,
	gc_eBodyBagMsg_SetSolidPage,
	gc_eBodyBagMsg_SetChangeCallback
};
/** gc_BodyBagSendMessage
* Send message to bodybag dialog to modify/query contents.
*@param		int iCmd: message to send to the bodybag dialog can be one of the following:
	gc_eBodyBagMsg_GetNumPages			returns the current number of pages through data1 (int*)		
	gc_eBodyBagMsg_GetActivePage		returns the current active page through data1 (int*)
	gc_eBodyBagMsg_SetActivePage		sets the current active page through data1 (int)
	gc_eBodyBagMsg_GetPageNameLen		returns the size of name of page number specified as 
										data1 (int) through data2 (int*)
	gc_eBodyBagMsg_GetPageName			returns the name of page number specified as data1 (int) 
										through data2 (char*)
	gc_eBodyBagMsg_SetPageName			sets the name of page number specified as data1 (int) 
										through data2 (const char*)
	gc_eBodyBagMsg_InsertPage			inserts a new page at index as data1 (int) which name as data2 
										(const char*) data2
	gc_eBodyBagMsg_DeletePage			deletes page at index as data1 (int)
	gc_eBodyBagMsg_MovePage				moves page from index as data1 (int) to data2 (int)
	gc_eBodyBagMsg_GetNumPageSolids		returns the number of solids in page index as data1 (int)
										through data2 (int*)
	gc_eBodyBagMsg_GetPageSolids		returns the the solids in page index as data1 (int)
										through data2 (int*)
	gc_eBodyBagMsg_MovePageSolids		moves all solids in page from index as data1 (int) to page
										from index as data2 (int)
	gc_eBodyBagMsg_GetSolidPage			returns the page from solid as data1 (int)
										through data2 (int*)
	gc_eBodyBagMsg_SetSolidPage			set the page from solid as data1 (int)
										through data2 (int)
	gc_eBodyBagMsg_SetChangeCallback    set a host-provided callback function data1 (int (int, void*, void*))
										using data2 (int) to register (1) and unregister (0) the callback.
*@param		void* data1: abstract data pointer
*@param		void* data2: abstract data pointer
*@return	0=success,
*@return	-1=input parameters out of range 
*@return	-2=no filename given
*@return	-3=could not open file
*/
GC_API int gc_BodyBagSendMessage(int iCmd, void* data1, void* data2);
GC_API int gc_IsBodyBagOpen();
GC_API int gc_DoBodyBag(int iOpen);

GC_API int gc_GetSolType(int iRef, int *iType);
GC_API int gc_SetSolType(int iRef, int iType);
GC_API int gc_GetNumSolGeo(int *iNum);
GC_API int gc_GetSolListGeo(int *iList);
GC_API int gc_GetNumSolStock(int *iNum);
GC_API int gc_GetSolListStock(int *iList);
GC_API int gc_GetNumSolFixtures(int *iNum);
GC_API int gc_GetSolListFixtures(int *iList);
GC_API int gc_ConvEdgesToGeom(double dTol, int iMax, int *iNum, int *iRefList);
GC_API int gc_UnstitchSolSel();
GC_API int gc_StitchSolSel(int iOnePass, double dTol);
GC_API int gc_StitchSolSelEx(int iOnePass, double dTol, int iReselect);
GC_API int gc_SimplifySolSel();
GC_API int gc_RemoveUnTopologySolSel();
GC_API int gc_TranslateSolSel(double *dVec, int iCS);
GC_API int gc_TranslateSolSelEx(double *dVec, int iCS, int *iNewSolRef);
GC_API int gc_TransformSolid(int iSolRef, double *matrix);
GC_API int gc_TransformSolidEx(int iSolRef, double *matrix, int *iNewSolRef);
GC_API int gc_TransformSolidEx2(int iSolRef, double *matrix, int bUseCurCS, int *iNewSolRef);
GC_API int gc_CopySolid(int iSolRef, int *iNewSolRef);
GC_API int gc_CheckSolValid(int iRef, int *iNumErr);
GC_API int gc_CheckFaceValidLM(int iSolRef, gc_TopoId FaceRef, int *iNumErr);
GC_API int gc_GetSolError(int iErrIndex, char *str);
GC_API int gc_TesselateSolids(void);
//--multi lump solid
GC_API int gc_GetSolNumLumps(int iRef, int *iNumLumps);
GC_API int gc_GetSolLumpId(int iRef, int iLump, int *iId);
GC_API int gc_GetSolLumpBBox(int iRef, int iLump, double *dBox);
GC_API int gc_GetSolLumpNumFaces(int iRef, int iLump, int *iNumFaces);
GC_API int gc_GetSolLumpFaceListLM(int iRef, int iLump, gc_TopoId *FaceList);
GC_API int gc_GetSolLumpNumEdges(int iRef, int iLump, int *iNumEdges);
GC_API int gc_GetSolLumpEdgeListLM(int iRef, int iLump, gc_TopoId *EdgeList);
GC_API int gc_GetSolLumpTess(int iRef, int iLump, int iCS, double dTol, void **result);
GC_API int gc_ExplodeSolid(int iSolRef, int *iNum, int *iSolList);
GC_API int gc_GetFaceLumpLM(int iSolRef, gc_TopoId FaceRef, int *iLump);
GC_API int gc_GetEdgeLumpLM(int iSolRef, gc_TopoId EdgeRef, int *iLump);
//--Solid NURB extraction API
GC_API int gc_GetFaceOrientation(int iSolRef, gc_TopoId FaceRef, int* iOrientation);
GC_API int gc_GetFaceSpline(int iSolRef, gc_TopoId FaceRef, void **result);
GC_API int gc_GetFaceSplineSurfInfo
(
	void*    pSplineInfo, 
	int*     iRational,
	int*     iDegU,
	int*     iDegV,
	int*     iKnotU,
	int*     iKnotV,
	int*     iCtrlU,
	int*     iCtrlV,
	double** dKnotU,
	double** dKnotV,
	double** dCtrl,
	int*     iTrimCount
);
GC_API int gc_GetFaceSplineTrimSurfInfo
(
	void*    pSplineInfo, 
	int      iTrimSurf,
	int*     iLoopCount
);
GC_API int gc_GetFaceSplineTrimSurfLoopInfo
(
	void*    pSplineInfo, 
	int      iTrimSurf,
	int      iLoop,
	int*     iCurveCount
);
GC_API int gc_GetFaceSplineTrimSurfLoopCurvePoints
(
	void*    pSplineInfo, 
	int      iTrimSurf,
	int      iLoop,
	int      iCurve,
	int*     iCurvePts,
	double** dCurvePts
);
GC_API int gc_GetFaceSplineTrimSurfLoopCurveInfo
(
	void*    pSplineInfo, 
	int      iTrimSurf,
	int      iLoop,
	int      iCurve,
	int*     iDegree,
	int*     iRational,
	int*     iClosed,
	int*     iPeriodic,
	int*     iControls,
	double** dControls,
	int*     iKnots,
	double** dKnots
);
GC_API int gc_FreeFaceSpline( void* pSplineInfo);
GC_API int gc_GetEdgeCurve(int iSolRef, gc_TopoId EdgeRef, int *degree, int *n_knots, int *n_ctrls);
GC_API int gc_GetEdgeCurveData(int iSolRef, gc_TopoId EdgeRef, int iCS, int *k_mult, double *k_param, double *ctrls);
//--Solid Tessellation with Matching Options
GC_API int gc_GetSolTess2(int iRef, int iCS, double dTol, gc_eSolTessMatchMode eMode, void **result);
GC_API int gc_GetSolLumpTess2(int iRef, int iLump, int iCS, double dTol, gc_eSolTessMatchMode eMode, void **result);
GC_API int gc_GetFaceTess2LM(int iSolRef, gc_TopoId FaceRef, int iCS, double dTol, gc_eSolTessMatchMode eMode, void **result);
//--Temp Bodies
// these bodies are meant to be used and immediately deleted,
// specifically before a Save can happen...
GC_API int gc_MakeDefaultStockBody(int iWP, gc_TempBody **body);
GC_API int gc_GetTempBodyID(const gc_TempBody *body, int *body_id);
GC_API int gc_DeleteTempBody(gc_TempBody *body);
/***** FUNCTIONS BELOW WILL BE MADE OBSOLETE--USE "LM" VERSIONS *************/
/* DEPRECATED */ GC_API int gc_AddSolFaceSel(int iSolRef, int iFaceRef, int iRedraw);
/* DEPRECATED */ GC_API int gc_AddSolEdgeSel(int iSolRef, int iEdgeRef, int iRedraw);
/* DEPRECATED */ GC_API int gc_GetFaceBBox(int iSolRef, int iFaceRef, double *dBox);
/* DEPRECATED */ GC_API int gc_GetEdgeBBox(int iSolRef, int iEdgeRef, double *dBox);
/* DEPRECATED */ GC_API int gc_GetFaceTess(int iSolRef, int iFaceRef, int iCS, double dTol, void **result);
/* DEPRECATED */ GC_API int gc_GetFaceId(int iSolRef, int iFaceRef, int *iId);
/* DEPRECATED */ GC_API int gc_GetEdgeId(int iSolRef, int iEdgeRef, int *iId);
/* DEPRECATED */ GC_API int gc_GetSolSelFaceList(int iRef, int *iList);
/* DEPRECATED */ GC_API int gc_GetSolSelEdgeList(int iRef, int *iList);
/* DEPRECATED */ GC_API int gc_GetFaceUVBox(int iSolRef, int iFaceRef, double *dBox);
/* DEPRECATED */ GC_API int gc_GetFaceParamInfo(int iSolRef, int iFaceRef, int *iIsUVBox, double dRange[4], int iBound[4], int iPeriod[2], int iForm[2], int iCont[2]);
/* DEPRECATED */ GC_API int gc_EvalFacePoint(int iSolRef, int iFaceRef, double u, double v, double *dPoint);
/* DEPRECATED */ GC_API int gc_EvalFaceNormal(int iSolRef, int iFaceRef, double u, double v, double *dNormal);
/* DEPRECATED */ GC_API int gc_EvalFaceDervs(int iSolRef, int iFaceRef, double u, double v, int nDervs, double *dDervs);
/* DEPRECATED */ GC_API int gc_EvalFaceCurvature(int iSolRef, int iFaceRef, double u, double v, double *dCurv1, double *dCurv2, double *dN, double *dDir1, double *dDir2);
/* DEPRECATED */ GC_API int gc_EvalFaceGrid(int iSolRef, int iFaceRef, int iNumU, double *dU, int iNumV, double *dV, int nDervs, double *dDervs);
/* DEPRECATED */ GC_API int gc_EvalFaceParam(int iSolRef, int iFaceRef, double *dPoint, double *u, double *v);
/* DEPRECATED */ GC_API int gc_ProjFaceVector(int iSolRef, int iFaceRef, double *dPoint, double *dVec, double *dProj);
/* DEPRECATED */ GC_API int gc_IsPointInFace(int iSolRef, int iFaceRef, double *dPoint);
/* DEPRECATED */ GC_API int gc_GetFaceEdgeBounds(int iSolRef, int iFaceRef, int iEdgeRef, double *dBox);
/* DEPRECATED */ GC_API int gc_EvalFaceEdgePoint(int iSolRef, int iFaceRef, int iEdgeRef, double t, double *dPoint);
/* DEPRECATED */ GC_API int gc_EvalFaceEdgeDervs(int iSolRef, int iFaceRef, int iEdgeRef, int iNumDervs, double t, double *dDervs);
/* DEPRECATED */ GC_API int gc_EvalFaceEdgeParam(int iSolRef, int iFaceRef, int iEdgeRef, double *dPoint, double *t);
/* DEPRECATED */ GC_API int gc_GetEdgeFaces(int iSolRef, int iEdgeRef, int *iNumFaces, int *iFace1, int *iFace2);
/* DEPRECATED */ GC_API int gc_GetSolFaceList(int iRef, int *iFaceList);
/* DEPRECATED */ GC_API int gc_GetSolEdgeList(int iRef, int *iEdgeList);
/* DEPRECATED */ GC_API int gc_GetSolFaceNumEdges(int iSolRef, int iFaceRef, int *iNumEdges);
/* DEPRECATED */ GC_API int gc_GetSolFaceEdgeList(int iSolRef, int iFaceRef, int *iEdgeList, int *iEdgeDir);
/* DEPRECATED */ GC_API int gc_GetSolFaceNumLoops(int iSolRef, int iFaceRef, int *iNumLoops);
/* DEPRECATED */ GC_API int gc_GetSolFaceLoopNumEdges(int iSolRef, int iFaceRef, int iLoop, int *iNumEdges);
/* DEPRECATED */ GC_API int gc_GetSolFaceLoopEdgeList(int iSolRef, int iFaceRef, int iLoop, int *iEdgeList, int *iEdgeDir);
/* DEPRECATED */ GC_API int gc_PickSolVector(int iSolRef, double *dPoint, double *dVec, int iMax, int *iNum, double *dProj, int *iFaceRef);
/* DEPRECATED */ GC_API int gc_CheckFaceValid(int iSolRef, int iFaceRef, int *iNumErr);
/***** FUNCTIONS ABOVE WILL BE MADE OBSOLETE--USE "LM" VERSIONS *************/

/***** FUNCTIONS BELOW WILL BE MADE OBSOLETE--USE VERSIONS THAT REQUIRE FACE REF *************/
/* DEPRECATED */ GC_API int gc_GetEdgeBounds(int iSolRef, int iEdgeRef, double *dBox);
/* DEPRECATED */ GC_API int gc_EvalEdgePoint(int iSolRef, int iEdgeRef, double t, double *dPoint);
/* DEPRECATED */ GC_API int gc_EvalEdgeDervs(int iSolRef, int iEdgeRef, int iNumDervs, double t, double *dDervs);
/* DEPRECATED */ GC_API int gc_EvalEdgeParam(int iSolRef, int iEdgeRef, double *dPoint, double *t);
/***** FUNCTIONS ABOVE WILL BE MADE OBSOLETE--USE VERSIONS THAT REQUIRE FACE REF *************/
//--surface query 
GC_API int gc_GetSurfType(void *surf, int *type);
GC_API int gc_GetSurfPlane(void *surf, double origin[3], double xvec[3], double yvec[3]);
GC_API int gc_GetSurfSphere(void *surf, double *radius, double origin[3], double xvec[3], double yvec[3]);
GC_API int gc_GetSurfCyl(void *surf, double *radius, double origin[3], double xvec[3], double yvec[3]);
GC_API int gc_GetSurfCone(void *surf, double *radius, double *angle, double origin[3], double xvec[3], double yvec[3]);
GC_API int gc_GetSurfTorus(void *surf, double *major, double *minor, double origin[3], double xvec[3], double yvec[3]);
GC_API int gc_GetSurfSpun(void *surf, void **curve, double origin[3], double axis[3]);
GC_API int gc_GetSurfExtruded(void *surf, void **curve, double direction[3]);
GC_API int gc_GetSurfOffset(void *surf, void **base_surf, double *distance);
GC_API int gc_GetSurfBSpline(void *surf, int *degu, int *degv, int *n_knots_u, int *n_knots_v, int *n_ctrls_u, int *n_ctrls_v);
GC_API int gc_GetSurfBSplineData(void *surf, int *k_mult_u, double *k_param_u, int *k_mult_v, double *k_param_v, double *ctrls);
//--surface creation functions...
GC_API int gc_CreateSurfPlane(double origin[3], double xvec[3], double yvec[3], void **surf);
GC_API int gc_CreateSurfSphere(double radius, double origin[3], double xvec[3], double yvec[3], void **surf);
GC_API int gc_CreateSurfCyl(double radius, double origin[3], double xvec[3], double yvec[3], void **surf);
GC_API int gc_CreateSurfCone(double radius, double angle, double origin[3], double xvec[3], double yvec[3], void **surf);
GC_API int gc_CreateSurfTorus(double major, double minor, double origin[3], double xvec[3], double yvec[3], void **surf);
GC_API int gc_CreateSurfSpun(void *curve, double origin[3], double axis[3], void **surf);
GC_API int gc_CreateSurfExtruded(void *curve, double direction[3], void **surf);
GC_API int gc_CreateSurfOffset(void *base_surf, double distance, void **surf);
GC_API int gc_CreateSurfBSpline(int degu, int degv, int n_knots_u, int n_knots_v, int n_ctrls_u, int n_ctrls_v,
					int *k_mult_u, double *k_param_u, int *k_mult_v, double *k_param_v, double *ctrls, void **surf);
GC_API int gc_ExtractFaceSurf(int iSolRef, int iFaceRef, void **surf, void **region);
GC_API int gc_ExtractFaceSurfLM(int iSolRef, gc_TopoId FaceRef, void **surf, void **region);
GC_API int gc_DeleteSurf(void *surf);
GC_API int gc_CopySurf(void *surf, void **new_surf);
GC_API int gc_TransformSurf(void *surf, double *matrix);
GC_API int gc_CreateSheetBody(void *surf, void *region, int *body);	// create single face sheet body from surface and uv loops
GC_API int gc_CreateSheetBodyXYZ(void *surf, void *region, int looptype, int *body);	// xyz loops 0 - eXYZDirLoops 1- eXYZEncLoops 2- eXYZHoleLoops
//--attributes
GC_API int gc_AddSolidAttList(int iSolRef, void **attlist);
GC_API int gc_GetSolidAttList(int iSolRef, void **attlist);
GC_API int gc_DeleteSolidAttList(int iSolRef);
GC_API int gc_AddFaceAttList(int iSolRef, gc_TopoId FaceRef, void **attlist);
GC_API int gc_GetFaceAttList(int iSolRef, gc_TopoId FaceRef, void **attlist);
GC_API int gc_DeleteFaceAttList(int iSolRef, gc_TopoId FaceRef);
GC_API int gc_AddEdgeAttList(int iSolRef, gc_TopoId EdgeRef, void **attlist);
GC_API int gc_GetEdgeAttList(int iSolRef, gc_TopoId EdgeRef, void **attlist);
GC_API int gc_DeleteEdgeAttList(int iSolRef, gc_TopoId EdgeRef);
//--solids attribute definitions
GC_API int gc_SolidAttributeDefCount(int *piCount);
GC_API int gc_SolidAttributeDefList(int *piSolAttDefs);
GC_API int gc_SolidAttributeDefInfo(int iSolAttDef, char *name, int *n_fields);
GC_API int gc_SolidAttributeDefFields(int iSolAttDef, int *field_types);
GC_API int gc_SolidAttributeDefFind(char *name, int *piSolAttDef);
GC_API int gc_SolidAttributeDefCreate(char *name, int n_fields, int *field_types, int *piSolAttDef);
GC_API int gc_SolidAttributeDefDelete(char *name);
//--solids attribute creation/deletion/etc.
GC_API int gc_SolidBodyAttributeFind(int iSolRef, char *name, int *piSolAtt);
GC_API int gc_SolidFaceAttributeFind(int iSolRef, gc_TopoId FaceRef, char *name, int *piSolAtt);
GC_API int gc_SolidEdgeAttributeFind(int iSolRef, gc_TopoId EdgeRef, char *name, int *piSolAtt);
GC_API int gc_SolidBodyAttributeCreate(int iSolRef, char *name, int field_items[], void *field_data[], int *piSolAtt);
GC_API int gc_SolidFaceAttributeCreate(int iSolRef, gc_TopoId FaceRef, char *name, int field_items[], void *field_data[], int *piSolAtt);
GC_API int gc_SolidEdgeAttributeCreate(int iSolRef, gc_TopoId EdgeRef, char *name, int field_items[], void *field_data[], int *piSolAtt);
GC_API int gc_SolidBodyAttributeDelete(int iSolRef, char *name);
GC_API int gc_SolidFaceAttributeDelete(int iSolRef, gc_TopoId FaceRef, char *name);
GC_API int gc_SolidEdgeAttributeDelete(int iSolRef, gc_TopoId EdgeRef, char *name);
GC_API int gc_SolidBodyAttributeCount(int iSolRef, int *piCount);
GC_API int gc_SolidFaceAttributeCount(int iSolRef, gc_TopoId FaceRef, int *piCount);
GC_API int gc_SolidEdgeAttributeCount(int iSolRef, gc_TopoId EdgeRef, int *piCount);
GC_API int gc_SolidBodyAttributeList(int iSolRef, int *piSolAtts);
GC_API int gc_SolidFaceAttributeList(int iSolRef, gc_TopoId FaceRef, int *piSolAtts);
GC_API int gc_SolidEdgeAttributeList(int iSolRef, gc_TopoId EdgeRef, int *piSolAtts);
//--solids attribute values
GC_API int gc_SolidAttributeGetDef(int iSolAtt, int *piSolAttDef);
GC_API int gc_SolidAttributeGetItemCount(int iSolAtt, int nField, int *piCount);
GC_API int gc_SolidAttributeGetInt(int iSolAtt, int nField, int nItem, int *pn_value);
GC_API int gc_SolidAttributeSetInt(int iSolAtt, int nField, int nItem, int n_value);
GC_API int gc_SolidAttributeGetDouble(int iSolAtt, int nField, int nItem, double *plf_value);
GC_API int gc_SolidAttributeSetDouble(int iSolAtt, int nField, int nItem, double lf_value);
GC_API int gc_SolidAttributeGetString(int iSolAtt, int nField, char **pps_value);
GC_API int gc_SolidAttributeSetString(int iSolAtt, int nField, char *ps_value);
GC_API int gc_SolidAttributeGetPointer(int iSolAtt, int nField, int nItem, void **ppv_value);
GC_API int gc_SolidAttributeSetPointer(int iSolAtt, int nField, int nItem, void *pv_value);
GC_API int gc_SolidAttributeGetWString(int iSolAtt, int nField, wchar_t **pps_value);
GC_API int gc_SolidAttributeSetWString(int iSolAtt, int nField, wchar_t *ps_value);
GC_API int gc_SolidAttributeGetVector(int iSolAtt, int nField, int nItem, double *plf_value);
GC_API int gc_SolidAttributeSetVector(int iSolAtt, int nField, int nItem, double *plf_value);
GC_API int gc_SolidAttributeGetPoint(int iSolAtt, int nField, int nItem, double *plf_value);
GC_API int gc_SolidAttributeSetPoint(int iSolAtt, int nField, int nItem, double *plf_value);
//--solid standard attributes
GC_API int gc_GetSolidBodyColorAttr(int iSolRef, double *pRGB);
GC_API int gc_SetSolidBodyColorAttr(int iSolRef, double *pRGB);
GC_API int gc_GetSolidFaceColorAttr(int iSolRef, gc_TopoId FaceRef, double *pRGB);
GC_API int gc_SetSolidFaceColorAttr(int iSolRef, gc_TopoId FaceRef, double *pRGB);
GC_API int gc_GetSolidEdgeColorAttr(int iSolRef, gc_TopoId EdgeRef, double *pRGB);
GC_API int gc_SetSolidEdgeColorAttr(int iSolRef, gc_TopoId EdgeRef, double *pRGB);
GC_API int gc_GetSolidBodyNameAttr(int iSolRef, char **pName);
GC_API int gc_SetSolidBodyNameAttr(int iSolRef, char *pName);
GC_API int gc_GetSolidFaceNameAttr(int iSolRef, gc_TopoId FaceRef, char **pName);
GC_API int gc_SetSolidFaceNameAttr(int iSolRef, gc_TopoId FaceRef, char *pName);
GC_API int gc_GetSolidEdgeNameAttr(int iSolRef, gc_TopoId EdgeRef, char **pName);
GC_API int gc_SetSolidEdgeNameAttr(int iSolRef, gc_TopoId EdgeRef, char *pName);
GC_API int gc_GetSolidBodyLayerAttr(int iSolRef, char **pName);
GC_API int gc_SetSolidBodyLayerAttr(int iSolRef, char *pName);
GC_API int gc_GetSolidFaceLayerAttr(int iSolRef, gc_TopoId FaceRef, char **pName);
GC_API int gc_SetSolidFaceLayerAttr(int iSolRef, gc_TopoId FaceRef, char *pName);
GC_API int gc_GetSolidEdgeLayerAttr(int iSolRef, gc_TopoId EdgeRef, char **pName);
GC_API int gc_SetSolidEdgeLayerAttr(int iSolRef, gc_TopoId EdgeRef, char *pName);
GC_API int gc_GetSolidBodyImportIDAttr(int iSolRef, int *pID);
GC_API int gc_SetSolidBodyImportIDAttr(int iSolRef, int nID);
GC_API int gc_GetSolidFaceImportIDAttr(int iSolRef, gc_TopoId FaceRef, int *pID);
GC_API int gc_SetSolidFaceImportIDAttr(int iSolRef, gc_TopoId FaceRef, int nID);
GC_API int gc_GetSolidEdgeImportIDAttr(int iSolRef, gc_TopoId EdgeRef, int *pID);
GC_API int gc_SetSolidEdgeImportIDAttr(int iSolRef, gc_TopoId EdgeRef, int nID);
//--Facet Body solid support
GC_API int gc_IsFacetBodySolid(int iSolid, int *iIsFacetBody);
//CALLBACKS
GC_API int gc_SetSolidCallBack(int iMode, void (*call_back)(void*));
GC_API int gc_ClearSolidCallBack(int iMode, void (*call_back)(void*));


//******************* OPERATION  ************************


//ENUMERATIONS

//Operation Type enums

enum
{	gc_eMillOp,
	gc_eLatheOp,	
};

enum
{	gc_eMDrill,
	gc_eMContour,
	gc_eMPocket,
	gc_eMThrdMill,
	gc_eMSurface,
};

enum
{	gc_eLeft,
	gc_eRight,
	gc_eCenter
};

enum
{	gc_eClimb,
	gc_eConventional,
	gc_eNoCutSide
};

enum
{	gc_eCW, 
	gc_eCCW,
	gc_eUNDEFINED_DIR
};

enum
{   gc_eSpiralPocket = 1,
	gc_eFacingPocket,
	gc_eZigZagPocket,
	gc_eOffsetCleanup,
};
typedef enum 
{
	gc_eOpEventOpBeforeLoad,			// user double clicked on operation; return non-zero to bypass load of all processes
	gc_eOpEventAutoRedo,				// operation must be re-processed
	gc_eOpEventExpandOnTheFly,			// prog iterator toolpath expansion; for use by utility ops
	gc_eOpEventOpLoadDefault,			// for loading default custom data into an operation
	gc_eOpEventProcessLoadDefault,		// for loading default custom data into a process
	gc_eOpEventOpDataChanged,			// for saving default custom op data
	gc_eOpEventProcessDataChanged,		// for saving default custom process data
	gc_eOpEventProcessDblClick,			// user double clicked on process; return value != 0 means don't display standard dialog
	gc_eOpEventProcessBeforeDoIt,		// user hit DoIt; return 0 for std op and tp, 1 for std op w/no tp, 2 for no op & no tp
	gc_eOpEventAfterDoIt,				// a new op was created
	gc_eOpEventPosting,					// callBack for Compost CallCustomProc (c562)
	gc_eOpEventProcessAllowDoIt,		// check selection to enable Do It button, all must return 0 to allow
	gc_eOpEventOpAfterLoad,				// user double clicked on operation and processes have been loaded
	gc_eOpEventProcessBeforeLoad,		// return non-zero to bypass load of this process (process number will not be set)
	gc_eOpEventProcessAfterLoad,		// process has been loaded
	gc_eOpEventOpBitMap,				// to set tile graphics on per op basis; if return value != 0, void* is a BITMAP*, set with bitmap to use
	gc_eOpEventProcessBitMap,			// to set tile graphics on per proc basis; if return value != 0, void* is a BITMAP*, set with bitmap to use
	gc_eOpEventOpDataBeforeChange,		// custom op data field will change, void* is const char*, c-string name of field
	gc_eOpEventOpDataAfterChange,		// custom op data field did change, void* is const char*, c-string name of field
	gc_eOpEventProcessDataBeforeChange,	// custom op data field will change, void* is const char*, c-string name of field
	gc_eOpEventProcessDataAfterChange,	// custom op data field did change, void* is const char*, c-string name of field
	gc_eOpEventOpRightClick,			// user right clicked on custom op
	gc_eOpEventMDrillPlanes,			// prog iterator mill drill planes, void* points to a gc_DrillPlanesCBParams struct
	gc_eOpEventMDrillCycle,				// prog iterator mill drill cycle expansion, void* points to a gc_DrillCycleCBParams struct
	gc_eOpEventProcessCreate,			// process tile added from CAM palette 
	gc_eOpEventProcessDelete,			// process tile deleted
	gc_eOpEventProcessMove,             // process tile moved
	gc_eOpEventProcessClose,			// process tile needs it's dialog closed, another process was activated, the cam pallet was closed, or the part was closed.
	gc_eOpEventOpData,					// Op Data item picked from RMM
	gc_eOpEventOpMove,					// op moved
	gc_eOpEventOpClose,					// op tile closed		
	gc_eOpEventProcessAllowMarkers,		// check to enable markers, return 0 to continue default checking, 1 to allow, 2 to disallow
	gc_eOpEventBeforeDelete,			// called before deletion of an op
	gc_eOpEventProcessSpeedCalc,		// calculated speed from material dialog. Can display in custom process dialog
	gc_eOpEventProcessFeedCalc,			// calculated feed from material dialog. Can display in custom process dialog
	gc_eOpEventAllowMaterial,			// allows interaction with material dialog
	gc_eOpEventPostOpTypeComment,		// fills out a string for the post engine to use for the operation type in it's comments ( ASCII only )
	gc_eOpEventCacheProcessData,		// called after the "BeforeDoIt" but before the "AfterDoIt" callback. If custom processes want to take advantage of "features" they need to use this 
	gc_eOpEventCreateOps,				// called before and after Redo All Ops, Redo Selected Ops, DoIt or Redo a Process Group
	gc_eOpEventProcessSaveData,			// Tells a custom process that data may be requested after this point, so make sure all the data is saved in the process
	gc_eOpEventProcSupportMFD,			// callback to determine if the cust mill process supports machining features from attribute data ( as per contouring, roughing, & surfacing )
	gc_eOpEventLast						// must be last
}
gc_teOpEventType;

typedef enum
{
	gc_eCreateOpsRedoAllStart = 100,	// start of Redo All Ops
	gc_eCreateOpsRedoSelStart,			// start of Redo Selected Ops
	gc_eCreateOpsCreateStart,			// start of DoIt or Redo a process group
	gc_eCreateOpsDoItStart,				// start of DoIt
	gc_eCreateOpsRedoStart,				// start of Redo
	gc_eCreateOpsRedoAllEnd = 200,		// end of Redo All Ops
	gc_eCreateOpsRedoSelEnd,			// end of Redo Selected Ops
	gc_eCreateOpsCreateEnd,				// end of DoIt or Redo a process group
	gc_eCreateOpsStopped = 900,			// user pressed stop
};

typedef enum
{
	gc_eProcGroupCompleted = 1,
	gc_eProcGroupFailed,
	gc_eProcGroupCanceled,
};

//-path
enum gc_SegType
{
	gc_eSegSpl,		// segment only spline features
	gc_eSegAll		// segment all non-linear features
};
//--Dirty Operation Callbacks
typedef enum
{
	gc_eDirtyOpCB_New,				// rDirtyOpCBData
	gc_eDirtyOpCB_Deleted,			// rDirtyOpCBData
	gc_eDirtyOpCB_Moved,			// rDirtyOpCBData
	gc_eDirtyOpCB_Replaced,			// rDirtyOpCBData
	gc_eDirtyOpCB_DataChanged,		// rDirtyOpCBData
	gc_eDirtyOpCB_Sorted		// rDirtyOpCBData
} gc_teDirtyOperationCallBack;
//STRUCTURE
// input/output params for gc_eOpEventMDrillPlanes callback...
typedef struct
{
	int iHoleRef;			// input; hole index, zero-based
	double xStartPlane;		// input; we traversed at this plane from last hole, and cycle should start here
	double xRetractPlane;	// output; the R-value
	double xEndPlane;		// output; cycle should end here, and we will traverse at this plane to next hole
}
gc_DrillPlanesCBParams;

// input/output params for gc_eOpEventMDrillCycle callback...

typedef struct
{
	int iHoleRef;			// input; hole index, zero-based
	double xStartPlane;		// input; we traversed at this plane from last hole, and cycle should start here
	double xRetractPlane;	// input; the R-value
	double xEndPlane;		// input; cycle should end here, and we will traverse at this plane to next hole
	double pos[3];			// input; position of bottom of hole
	int bAttribs;			// input; put attributes on features (for Compost long-hand output)
	void *path;				// output; write to this path (already allocated)
}
gc_DrillCycleCBParams;

//DECLARATIONS
GC_API int gc_CreateDrillOp(int iIndex, int iTool, double dClear, int iNbPts, double *dPts);
GC_API int gc_CreateMillOp(int iIndex, int iTool, double dClear, int iNbPts, double *dPts, int *iMotionType);
GC_API int gc_CreateLUtilOp(int iIndex, int iTool, int iFlow );
GC_API int gc_CreateShapeMillOp(int iIndex, int iTool, double dClear, int iNbPts, double *dPts, double dDepth);
GC_API int gc_CreateShapeLatheOp(int iIndex, int iTool, double dClear, int iNbPts, double *dPts);
GC_API int gc_SelectOp(int iIndex);
//--custom op data description
GC_API int gc_SetCustomDataDesc(const char *sCustomName, int iNumFields, char *asNames[/*iNumFields*/], int aiSizes[/*iNumFields*/], int aiOffsets[/*iNumFields*/], int aiEnabled[/*iNumFields*/]);
GC_API int gc_GetCustomDataDescFieldCount(const char *sCustomName, int *piCount);
GC_API int gc_GetCustomDataDescField(const char *sCustomName, int iIndex, char *sName, int *piSize, int *piOffset, int *piEnabled);
GC_API int gc_ClearCustomDataDesc(const char *sCustomName);
//--operation info
GC_API int gc_HandleOnlyCompleteOps(int iSafeOps);
GC_API int gc_GetHandleOnlyCompleteOps(int *iSafeOps);
GC_API int gc_GetNumOps(int *iNum);
GC_API int gc_GetFreeOp(int *iIndex);
GC_API int gc_GetLastOp(int *iIndex);
GC_API int gc_GetOpIndexList(int *iList);
GC_API int gc_GetNumSelOps(int *iNum);
GC_API int gc_GetSelOpIndexList(int *iList);
GC_API int gc_CopyOp(int iIndexSource, int iIndexDest);
GC_API int gc_GetOpStatus(int iIndex, gc_eTileStatus *peStatus);
GC_API int gc_SetOpStatus(int iIndex, gc_eTileStatus eStatus);
GC_API int gc_GetSelOpStatus(int iIndex, int *piSelect);
GC_API int gc_GetOpInfoI(int iIndex, int id, int *iVal);
GC_API int gc_GetOpInfoS(int iIndex, int id, char *sVal);
GC_API int gc_GetOpInfoWS( int iOp, int id, wchar_t *sVal );
GC_API int gc_GetOpInfoD(int iIndex, int id, double *dVal);
GC_API int gc_SetOpInfoI(int iIndex, int id, int *iVal);
GC_API int gc_SetOpInfoS(int iIndex, int id, const char *sVal);
GC_API int gc_SetOpInfoWS(int iOp, int id, const wchar_t *sVal );
GC_API int gc_SetOpInfoD(int iIndex, int id, double *dVal);
GC_API int gc_SetOpPath(int iIndex, const void *pPath);
GC_API int gc_CloneOpInfo(int iIndexSource, int iIndexDest);
GC_API int gc_IsOpAdv3D(int iIndex);
GC_API int gc_IsOp5Axis(int iIndex);
GC_API int gc_IsOp5AxisDrill(int iIndex);
GC_API int gc_GetOp5AxisDrillInfoI(int iIndex, int id, int *iVal);
GC_API int gc_GetOp5AxisDrillInfoD(int iIndex, int id, double *dVal);
GC_API int gc_GetOpCustomName(int iIndex, char *sName);
GC_API int gc_SetOpCustomName(int iIndex, const char *sName);		// set to "" for non-custom op
GC_API int gc_GetOpCustomString(int iIndex, const char* sID, char* sValue);
GC_API int gc_GetOpToolTipString(int iIndex, char* sValue);
GC_API int gc_GetOpCustomDataSize(int iIndex, int *piSize);
GC_API int gc_GetOpCustomData(int iIndex, void *pData);
GC_API int gc_SetOpCustomData(int iIndex, int iSize, void *pData);
GC_API int gc_GetOpCustomDataSizeEx(int iIndex, const char* sDataName, int *piSize);
GC_API int gc_GetOpCustomDataEx(int iIndex, const char* sDataName, void *pData);
GC_API int gc_SetOpCustomDataEx(int iIndex, const char* sDataName, int iSize, void *pData);
GC_API int gc_GetOpCustomDataFieldSize(int iIndex, const char *sFieldName, int *piSize);
GC_API int gc_GetOpCustomDataField(int iIndex, const char *sFieldName, void *pData);
GC_API int gc_SetOpCustomDataField(int iIndex, const char *sFieldName, void *pData);
GC_API int gc_GetOpCustomStreamDataFieldSize(const char *sStreamName, const char *sFieldName, int *piSize);
GC_API int gc_GetOpCustomStreamDataField(int iIndex, const char *sStreamName, const char *sFieldName, void *pData);
GC_API int gc_SetOpCustomStreamDataField(int iIndex, const char *sStreamName, const char *sFieldName, void *pData);
GC_API int gc_GetNewOpSynchID(int *piSynchId);		// returns a new, unused sync id
GC_API int gc_GetOpSynch(int iIndex, int iSyncType, int *piSynchId);
GC_API int gc_GetOpStartSynch(int iIndex, int *piSynchId);
GC_API int gc_SetOpStartSynch(int iIndex, int iSynchId);
GC_API int gc_GetOpEndSynch(int iIndex, int *piSynchId);
GC_API int gc_SetOpEndSynch(int iIndex, int iSynchId);
GC_API int gc_GetOpStrokeSynch(int iIndex, int *pbStrokeSynch);
GC_API int gc_SetOpStrokeSynch(int iIndex, int bStrokeSynch);
GC_API int gc_GetOpRotPref(int iIndex, gc_eRotPref *peRotPref);
GC_API int gc_SetOpRotPref(int iIndex, gc_eRotPref eRotPref);
GC_API int gc_GetOpRotLimits(int iIndex, teMachRotAxis eAxis, int *pbLimited, double *pxMin = NULL, double *pxMax = NULL);
GC_API int gc_SetOpRotLimits(int iIndex, teMachRotAxis eAxis, int bLimited, const double *pxMin = NULL, const double *pxMax = NULL);
GC_API int gc_SetRotHeadInterOpOverrides(int iIndex, gc_OpRotHeadOpOverride rOpOverrides );
GC_API int gc_GetRotHeadInterOpOverrides(int iIndex, gc_OpRotHeadOpOverride *rOpOverrides );
GC_API int gc_SetRotHeadIntraOpOverrides(int iIndex, gc_OpRotHeadOpOverride rOpOverrides );
GC_API int gc_GetRotHeadIntraOpOverrides(int iIndex, gc_OpRotHeadOpOverride *rOpOverrides );
GC_API int gc_DeleteOp(int iIndex);
GC_API int gc_ReorderOps(int iNumOps, int* iNewOpList, int iCheck);
GC_API bool gc_AllOpsFinished();
GC_API bool gc_AllProcGroupOpsFinished(const short iProcGroup);
GC_API int gc_SortOps();

//--operation path

GC_API int gc_CreateOpPatternPath(int iIndex);
GC_API int gc_GetOpNumFeat(int iIndex, int *iNumFeat);
GC_API int gc_GetOpFeatType(int iIndex, int iFeatIndex, int *iFeatType);
GC_API int gc_GetOpPoint(int iIndex, int iFeatIndex, double *pt);
GC_API int gc_GetOpLine(int iIndex, int iFeatIndex, double *p1, double *p2);
GC_API int gc_GetOpCTool(int iIndex, int iFeatIndex, int *iType, double *dPos);
GC_API int gc_GetOpCircle(int iIndex, int iFeatIndex, double *dCenter, double *dRad);
GC_API int gc_GetOpArcEnds(int iIndex, int iFeatIndex, double *dStart, double *dEnd, int *iDirCCW);
GC_API int gc_GetOpArcAngles(int iIndex, int iFeatIndex, double *dStartAng, double *dEndAng);
GC_API int gc_GetOpCurve(int iIndex, int iFeatIndex, int *degree, int *n_knots, int *n_ctrls);
GC_API int gc_GetOpCurveData(int iIndex, int iFeatIndex, int *k_mult, double *k_param, double *ctrls);
GC_API int gc_GetOpLineIJK(int iIndex, int iFeatIndex, double *p1, double *p2, double *ijk1, double *ijk2);
GC_API int gc_CreateOpFeatPoints(int iIndex, int iFeatIndex, double tol, void **point_list);		// tol <= 0 means use default
GC_API int gc_GetOpPath(int iIndex, void **pPath);
GC_API int gc_GetPathEndPts(const void *pPath, double *dPt1, double *dPt2);
GC_API int gc_GetOpPathEndPts(int iIndex, double *dPt1, double *dPt2);
GC_API int gc_GetOpNumSolSel(int iOpIndex, int *iNum);
GC_API int gc_GetOpSolSelList(int iOpIndex, int *iList);
GC_API int gc_GetOpPathEx(int iIndex,int iType, void **pPath);
GC_API int gc_SetOpPathEx(int iIndex,int iType, const void *pPath);
GC_API int gc_GetPostOutputPath(int iOp, bool bAddCTools, void **pPath);
GC_API int gc_GetPostOutputPathEx(int iOp, bool bAddCTools, bool bAllowEdgePath, void **pPath);
GC_API int gc_GetOpPathMatrix(int iIndex, double *dMatrix);
GC_API int gc_GetOpPathAttr(int iOp, gc_eOpPathAttr eAttr, int &bHasAttr);
GC_API int gc_ClearOpPathAttrs(int iOp);

//--lathe op cut rgn parameter block...
struct gc_LOpCutRgnCalcParams
{
	int version;					// param block data structure version, don't change from default constructed value!
	// looks stupid now, but wait until I add stuff here, then we'll see who's stupid!

	gc_LOpCutRgnCalcParams() : version(1) {}
};

GC_API int gc_SetLOpCutRgnFromPath(int iOp, const void *path, const gc_LOpCutRgnCalcParams &params);	// for cutting util ops to set cut rgn

//--paths

struct gc_BBox
{
	enum {min_x, min_y, min_z, max_x, max_y, max_z};

	double val[6];

	operator double * ()
	{
		return val;
	}
	
	operator const double * () const
	{
		return val;
	}
};

GC_API int gc_PathCreate(void **ptr);
GC_API int gc_PathDelete(void *ptr);
GC_API int gc_PathClear(void *ptr);
GC_API int gc_PathSwap(void *ptr, void* ptr2);
GC_API int gc_PathCopy(void *ptr, void **copy_ptr);
GC_API int gc_PathReverse(void *ptr);
GC_API int gc_PathAddFeat(void *ptr, const void *feat);
GC_API int gc_PathAddPoint(void *ptr, double *pt);
GC_API int gc_PathAddLine(void *ptr, double *p1, double *p2, int iType = 1);
GC_API int gc_PathAddArc(void *ptr, double *p1, double *p2, double *center, double rad, int iDirCCW);
GC_API int gc_PathAddCurve(void *ptr, int degree, int n_knots, int n_ctrls, int *k_mult, double *k_param, double *ctrls);
GC_API int gc_PathAddShape(void *ptr, int iNum, double *dPts, double dDepth);
GC_API int gc_PathAddLineIJK(void *ptr, double *p1, double *ijk1, double *p2, double *ijk2,  int iType = 1);
GC_API int gc_PathAddCTool(void *ptr, gc_eCToolType eType, double *dLoc=NULL, void *data=NULL);
GC_API int gc_PathAddDwell(void *ptrPath, int bRevs, double xDwell);
GC_API int gc_PathAddPartMove(void *ptr, int iFromWP, int iToWP, double *pos, double *d_axis, double *h_axis);
GC_API int gc_PathAddCustom(void *ptrPath, char *sName, double *axParams, double xTime, double xLength, int iDataSize, char *pData);
GC_API int gc_PathAddPathPortion(void *ptr1, void *ptr2,  double dPrm1, double dPrm2);
GC_API int gc_PathTranslate(void *ptrPath, double *dVec);
GC_API int gc_PathTransform(void *path, const double *mx);
GC_API int gc_PathRotate(void *ptrPath, double *dOrg, double *dRotVec, double dAngle);
GC_API int gc_PathLengthParameterize(void *ptr);
GC_API int gc_PathSegment(void *path_ptr, gc_SegType seg_type, double tol);
GC_API int gc_PathSimplify(void *path_ptr, double tol);
GC_API int gc_CreatePathMillOp(int iIndex, int iTool, double dClear, void *ptr, double dDepth);
GC_API int gc_GetPathNumFeat(void *ptrPath, int *iNum);
GC_API int gc_GetPathFeat(const void *ppath, int iFeat, void **feat);
GC_API int gc_GetPathFeatType(void *ptrPath, int iFeat, int *iFeatType);
GC_API int gc_GetPathFeatRef(void *ptrPath, int iFeat, int *iRef, int *iCorn);
GC_API int gc_GetPathFeatLen(void *ptrPath, int iFeat, double *dLen);
GC_API int gc_GetPathFeatName(void *ptrPath, int iFeat, char *sName);
GC_API int gc_GetPathBBox(const void *ptrPath, gc_BBox &bbox);
GC_API int gc_GetPathPoint(void *ptrPath, int iFeat, double *pt);
GC_API int gc_GetPathLine(void *ptrPath, int iFeat, double *p1, double *p2);
GC_API int gc_GetPathCircle(void *ptrPath, int iFeat, double *dCenter, double *dRad);
GC_API int gc_GetPathArcEnds(void *ptrPath, int iFeat, double *dStart, double *dEnd, int *iDirCCW);
GC_API int gc_GetPathArcAngles(void *ptrPath, int iFeat, double *dStartAng, double *dEndAng);
GC_API int gc_GetPathCurve(void *ptrPath, int iFeat, int *degree, int *n_knots, int *n_ctrls);
GC_API int gc_GetPathCurveData(void *ptrPath, int iFeat, int *k_mult, double *k_param, double *ctrls);
GC_API int gc_GetPathFeatDwell(void *ptrPath, int iFeat, int *pbRevs, double *pxDwell);
GC_API int gc_GetPathFeatPartMove(void *ptrPath, int iFeat, int *piFromWP, int *piToWP, double *pos, double *d_axis, double *h_axis);
GC_API int gc_GetPathFeatCustom(void *ptrPath, int iFeat, char *sName, double *axParams, double *pxTime, double *pxLength, int *piDataSize);
GC_API int gc_GetPathFeatCustomData(void *ptrPath, int iFeat, char *pData);
GC_API int gc_GetPathFeatCustomFieldInfo(void *ptrPath, int iFeat, char *sFieldName, int *piSize, int *piOffset, int *piEnabled);
GC_API int gc_GetPathFeatCustomFieldData(void *ptrPath, int iFeat, char *sFieldName, void *pData);
GC_API int gc_GetPathFeatAtt(void *ptrPath, int iFeat, int iAttType, int *iFeatAtt);
GC_API int gc_SetPathFeatAtt(void *ptrPath, int iFeat, int iAttType, int iFeatAtt);
GC_API int gc_SetPathFeatRef(void *ptrPath, int iFeat, int iRef, int iCorn);
GC_API int gc_GetPathCTool(void *ptrPath, int iFeat, gc_eCToolType *peType, double *dLoc=NULL, void *data=NULL);
GC_API int gc_GetPathLineIJK(void *ptrPath, int iFeat, double *p1, double *ijk1, double *p2, double *ijk2);
GC_API int gc_GetPathDirection(void *ptrPath, int *iDirCCW);
GC_API int gc_CreatePathFeatPoints(void *ptrPath, int iFeat, double tol, void **point_list);		// tol <= 0 means use default
GC_API int gc_ProjPointOnPath(void *ptrPath, double *dPt, double *dPtProj, double *dParamProj, double *dDistProj);
GC_API int gc_IsPathClosed(void *ptrPath);
GC_API int gc_PointInPath(void *ptrPath, double dPoint[3], int *bInside, int *bOn);
GC_API int gc_ConvCurve2C1BSpline(int degree, int *n_knots, int *n_ctrls, int *k_mult, double *k_param, double *ctrls);
GC_API int gc_ConvPath2Geom(void *ptrPath, int bRedraw);
GC_API int gc_EvalPathPoint(void *ptrPath, int iFeat, double dParam, double *dPoint);
GC_API int gc_EvalPathTangent(void *ptrPath, int iFeat, double dParam, double *dTangent);
GC_API int gc_PathHasSplines(void *ptrPath, int *pbHasSplines);
GC_API int gc_SegmentPathSplines(void *ptrPath);
GC_API int gc_OffsetPath(void *ptrInPath, void *ptrOutPath, double dOffset, int nSide, int nCornerType, int nEndType, int nUndefCornerType, double dMinCR, double dCornerAccy);
GC_API int gc_OffsetPath2(void *ptrInPath, void *ptrOutPath, double dOffset, int nSide, int nCornerType, int nEndType, int nUndefCornerType, double dMinCR, double dCornerAccy);
GC_API int gc_MakePathMonotonic( void *path_ptr );
GC_API int gc_PathRestartClosed( void* ptr_path, long feat_index, double xParam = 0.0 );

GC_API int gc_ExpandMDrillPos(int iOp, gc_DrillCycleCBParams *params);
GC_API int gc_ExpandMDrillPath(void *in_path, void *out_path, int bKeepFlags, int iOp);
GC_API int gc_GetMachinePath( char* sPath );
GC_API int gc_SetMachinePath( const char* sPath );
GC_API int gc_GetCurrentOpWP(long *plWP);
GC_API int gc_SetCurrentOpWP(long lWP);
GC_API	int gc_GetFolderPath ( gc_eFolderPaths	eFolderPath, char* szPath, int iSize = -1 );
//--attributes
GC_API int gc_AddOpAttList(int iOp, void **attlist);
GC_API int gc_GetOpAttList(int iOp, void **attlist);
GC_API int gc_DeleteOpAttList(int iOp);
//--Material Only Support for custom operations

/** gc_CreateMatRemovedVec
* holds the pointer to a vector that stores material removed per op and the tool associated with the cut
*@param		void **removed_mat_vec
*@return	0 = success, 
*/
GC_API int gc_CreateMatRemovedVec( void **removed_mat_vec );

/** gc_PopulateMatRemovedVec
* Call this function ( if necessary ) from a gc_eOpEventAfterDoIt callback
* This will populate an already created vector ( from gc_CreateMatRemovedVec ) and populate it with 
* Regions that represent the material removed by "compatible" operations.
* Compatible operations have axially aligned depth axes and are MILL operations. 
*@param		int iOp: already existing operation to use to use to search for all compatible operations
*@param		char* selface_file_name: file name for selected solids STL output
*@return	0 = success, 
*@return	-1 = region pointer is null
*@return	-2 = not a valid op type
*@return	-3 = no compatible operations found
*/
GC_API int gc_PopulateMatRemovedVec( int iOp, void *removed_mat_vec );

/** gc_GetMatRemovedVecSize
* Get the number of elements within the vector
*@param		void **removed_mat_vec
*@return	0 = success, 
*@return	-1 = *removed_mat_vec is invalid
*/
GC_API int gc_GetMatRemovedVecSize( void * removed_mat_vec );

/** gc_GetMatRemovedTool
* Get the number of elements within the vector
*@param		int index - index of vector to get data from
*@param		void **removed_mat_vec - vector
*@param		int *tool - pointer to assign tool number to
*@return	0 = success
*@return	-1 = *removed_mat_vec is invalid
*@return	-2 = invalid index
*/
GC_API int gc_GetMatRemovedTool( int index, void * removed_mat_vec, int *tool );

/** gc_GetMatRemovedRgn
* Get the region of material removed
*@param		int index - index of vector to get data from
*@param		void **removed_mat_vec - vector
*@param		void **region - place to hold a copy of the region.  Make sure to call gc_DeleteRegion when done with the region
*@return	0 = success
*@return	-1 = *removed_mat_vec is invalid
*@return	-2 = invalid index
*/
GC_API int gc_GetMatRemovedRgn( int index, void * removed_mat_vec, void **region );

/** gc_DeleteMatRemovedVec
* delete the pointer to the vector
*@param		void **removed_mat_vec
*@return	-1 = *removed_mat_vec is invalid
*@return	-1 = success
*/
GC_API int gc_DeleteMatRemovedVec( void * removed_mat_vec );

GC_API int gc_CreateMatRemovedOpVec( void **removed_mat_op_vec );
GC_API int gc_DeleteMatRemovedOpVec( void * removed_mat_op_vec );
GC_API int gc_GetMatRemovedOp( int index, void * removed_mat_op_vec, short *op );
GC_API int gc_GetMatRemovedOpVecSize( void * removed_mat_op_vec );
GC_API int gc_PopulateMatRemovedOpVec( int iOp, void *removed_mat_op_vec );

// for pre-drill
GC_API int gc_CreatePredrillOpVec( void **predrill_op_vec );
GC_API int gc_DeletePredrillOpVec( void * predrill_op_vec );
GC_API int gc_GetPredrillOp( int index, void * predrill_op_vec, short *op );
GC_API int gc_GetPredrillOpVecSize( void * predrill_op_vec );
GC_API int gc_PopulatePredrillOpVec( int iOp, void *predrill_op_vec );
GC_API int gc_AdjustPredrillDepth(int iMainOp, int iPredrillOp, double *dHoleDepth);

//--op event
GC_API int gc_CheckAllowDoit(void); // force a check of the allow do it callback. 
GC_API int gc_GetRedoAllOpStatus(int *iVal);
GC_API int gc_GetRedoAllOpSyncStatus(int *iVal);

#define gc_eOpEventOpDblClick		gc_eOpEventOpBeforeLoad		// OBSOLETE enum name
//CALLBACKS
//--custom op callbacks for unique named ops

//I cannot put here the callback structure declaration because it's used by a list before (prog itr params), so it will be at the top of the document
GC_API int gc_SetCustomOpEventCallBack(const char *sCustomName, gc_teOpEventType iMode, gc_tOpEventCallBack);
GC_API int gc_ClearCustomOpEventCallBack(const char *sCustomName, gc_teOpEventType iMode);
GC_API int gc_GetCustomOpEventCallBack(const char *sCustomName, gc_teOpEventType iMode, gc_tOpEventCallBack&);
GC_API int gc_SetIdleCallBack(void (*call_back)(void*));
GC_API int gc_ClearIdleCallBack(void (*call_back)(void*));
//--op callbacks
GC_API int gc_SetOpEventCallBack(gc_teOpEventType iMode, gc_tOpEventCallBack);
GC_API int gc_ClearOpEventCallBack(gc_teOpEventType iMode, gc_tOpEventCallBack);
//--Dirty Operation Callbacks
typedef struct _gc_rDirtyOpCBData
{
	int iOp1;			// First Op Dirtied
	int iOp2;			// Second Op Dirtied, If Applicable
} gc_rDirtyOpCBData, *gc_rDirtyOpCBDataPtr;

typedef void (*gc_tDirtyOperationCallBack)(gc_rDirtyOpCBDataPtr pCBData);
GC_API int gc_SetDirtyOperationCallBack(int iCB, gc_tDirtyOperationCallBack);
GC_API int gc_ClearDirtyOperationCallBack(int iCB, gc_tDirtyOperationCallBack);


//******************* PROCESS  ************************

//ENUMERATIONS
//STRUCTURE
// call "gc_InitPocParams" to initialize param block fields to defaults...
// working units:   iUnit=0 metric,    iUnit=1 inch
#define gc_InitPocketParams(params, iUnit)				\
	(													\
		(params).iVersion		= 1,					\
		(params).PocketType		= gc_eSpiralPocket,		\
		(params).FirstOffset	= (iUnit) ? 0.1 : 2.0,	\
		(params).CutWidth		= (iUnit) ? 0.05 : 1.0,	\
		(params).EntryClearance	= (iUnit) ? 1.0 : 25.0,	\
		(params).ExitClearance	= (iUnit) ? 1.0 : 25.0,	\
		(params).Depth			= 0.0,					\
		(params).EntryPerp		= 0,					\
		(params).ExitPerp		= 0,					\
		(params).EntryLine		= 0.0,					\
		(params).ExitLine		= 0.0,					\
		(params).EntryRad		= 0.0,					\
		(params).ExitRad		= 0.0,					\
		(params).PocketStock	= 0.0,					\
		(params).BossStock		= 0.0,					\
		(params).CutType		= 0,					\
		(params).ZigZagCutAngle = 0.0					\
	)

#define gc_InitImportFilter_M(params)					\
	(													\
	(params).iVersion			= 1,					\
	(params).bComParallelCSs	= 1,					\
	(params).bSepWGperLevel		= 1,					\
	(params).bSepWGperCS		= 0,					\
	(params).bForce1CS			= 0,					\
	(params).bPeserveHVD		= 0,					\
	(params).bAllowPoints		= 0,					\
	(params).bAllowLines		= 1,					\
	(params).bAllowCircles		= 1,					\
	(params).bAllowConics		= 1,					\
	(params).bAllowCurves		= 1,					\
	(params).bAllowSurfs		= 1,					\
	(params).bAllowSubordinates	= 0,					\
	(params).bAllowInvisibles	= 0,					\
	(params).bAllowAnnotations	= 0,					\
	(params).bCheckArcs			= 0,					\
	(params).ePreferredPlane	= 1,					\
	(params).eTrimPrefs			= gc_eAutoConnect,		\
	(params).bSecondPass		= 0,					\
	(params).xConnectRange		= 0.0,					\
	(params).xCurveAccuracy		= 0.005,				\
	(params).xShrinkage			= 0.0					\
	)

#define gc_InitExportFilter_M(params)			\
	(											\
	(params).iVersion	= 1,					\
	(params).bPoints	= 1,					\
	(params).bLines		= 1,					\
	(params).bCircles	= 1,					\
	(params).bCurves	= 1,					\
	(params).bSurfaces	= 0,					\
	(params).bOutputInPartUnit= 1,				\
	(params).iOutputUnit= 0,					\
	(params).bSuppressZ = 0						\
	)


//DECLARATIONS
GC_API int gc_ClearProcessList();
GC_API int gc_LoadOpProcess(int iOp);

enum
{
	gc_eLoadOpProcessFlags_None = 0,
	gc_eLoadOpProcessFlags_TryOpenProcessDlg = 1
};

GC_API int gc_LoadOpProcessEx(int iOp, int iFlags);

GC_API int gc_RedoAllOps();
GC_API int gc_RedoAllOpsAsync();
GC_API int gc_OpenProcess(int iCell);
GC_API int gc_CloseProcessDialogs(int iCell);
//--Milling processes 
GC_API int gc_CreateDrillProcess(int iCell, int iTool);
GC_API int gc_CreateMContourProcess(int iCell, int iTool);
GC_API int gc_CreatePocketProcess(int iCell, int iTool);
GC_API int gc_CreateMSurfaceProcess(int iCell, int iTool);
GC_API int gc_CreateMThreadProcess(int iCell, int iTool);
//--Silent Milling processes/ops 
GC_API int gc_CreatePocketPath(gc_PocketParam *pParam, void *pInRegion, void **pOutPath);
GC_API int gc_CreatePocketPathEx(gc_PocketParam *pParam, void *pInRegion, void **pOutPath, void (*cb_SetProcessInfo)(int, void *), void *pData);
//--Lathe processes 
GC_API int gc_CreateLContourProcess(int iCell, int iTool);
GC_API int gc_CreateLRoughProcess(int iCell, int iTool);
GC_API int gc_CreateLThreadProcess(int iCell, int iTool);
GC_API int gc_CreateLDrillProcess(int iCell, int iTool);
GC_API int gc_CreateLUtilityProcess(int iCell, int iTool);
//--process information
GC_API int gc_SetProcInfoI(int iCell, int id, int *iVal);
GC_API int gc_SetProcInfoS(int iCell, int id, const char *sVal);
GC_API int gc_SetProcInfoD(int iCell, int id, double *dVal);
GC_API int gc_GetProcInfoI(int iCell, int id, int *iVal);
GC_API int gc_GetProcInfoS(int iCell, int id, char *sVal);
GC_API int gc_GetProcInfoD(int iCell, int id, double *dVal);
GC_API int gc_SetOpProcInfoI(int iOpNum, bool bFromPGroup, int id, int *iVal);
GC_API int gc_SetOpProcInfoS(int iOpNum, bool bFromPGroup, int id, const char *sVal);
GC_API int gc_SetOpProcInfoD(int iOpNum, bool bFromPGroup, int id, double *dVal);
GC_API int gc_GetOpProcInfoI(int iOpNum, bool bFromPGroup, int id, int *iVal);
GC_API int gc_GetOpProcInfoS(int iOpNum, bool bFromPGroup, int id, char *sVal);
GC_API int gc_GetOpProcInfoD(int iOpNum, bool bFromPGroup, int id, double *dVal);
GC_API int gc_SetOpProcCustomName(int iOpNum, const char *sVal);
GC_API int gc_GetOpProcInfoWS(int iOpNum, bool bFromPGroup, int id, wchar_t *sVal);
GC_API int gc_SetOpProcInfoWS(int iOpNum, bool bFromPGroup, int id, wchar_t *sVal);
GC_API int gc_SetProcInfoWS( int iCell, int id, wchar_t* sVal );
GC_API int gc_GetProcInfoWS( int iCell, int id, wchar_t* sVal );

GC_API int gc_GetProcessCustomName(int iIndex, char *sName);
GC_API int gc_SetProcessCustomName(int iIndex, const char *sName);		// set to "" for non-custom process
GC_API int gc_GetProcessCustomDataSize(int iIndex, int *piSize);
GC_API int gc_GetProcessCustomData(int iIndex, void *pData);
GC_API int gc_SetProcessCustomData(int iIndex, int iSize, void *pData);
GC_API int gc_GetProcessCustomDataSizeEx(int iIndex, const char* sDataName, int *piSize);
GC_API int gc_GetProcessCustomDataEx(int iIndex, const char* sDataName, void *pData);
GC_API int gc_SetProcessCustomDataEx(int iIndex, const char* sDataName, int iSize, void *pData);
GC_API int gc_GetProcessCustomDataFieldSize(int iIndex, const char *sFieldName, int *piSize);
GC_API int gc_GetProcessCustomDataField(int iIndex, const char *sFieldName, void *pData);
GC_API int gc_SetProcessCustomDataField(int iIndex, const char *sFieldName, void *pData);
GC_API int gc_GetProcessCustomStreamDataFieldSize(const char *sStreamName, const char *sFieldName, int *piSize);
GC_API int gc_GetProcessCustomStreamDataField(int iIndex, const char *sStreamName, const char *sFieldName, void *pData);
GC_API int gc_SetProcessCustomStreamDataField(int iIndex, const char *sStreamName, const char *sFieldName, void *pData);
GC_API int gc_IsProcAdv3D(int iCell);
GC_API int gc_IsProc5Axis(int iCell);
GC_API int gc_CalcProcess();
GC_API int gc_CalcProcessAsync();
GC_API int gc_DeleteProcess(int iCell);
GC_API int gc_DoPosting(int bSkipCallBacks);
GC_API int gc_CopyProcess(int iSrcIndex, int iDestCell );			//iSrcIndex = Process Cell to Copy..iDestCell = cell to copy to
GC_API int gc_GetFreeProcess( int *iNum );
GC_API int gc_GetLastProcess( int *iNum );
GC_API int gc_GetNumProcesses(int *iNum, bool bAllowIncomplete = false);
GC_API int gc_GetNumSelProcesses(int *iNum, bool bAllowIncomplete = false);
GC_API int gc_GetProcessIndexList(int *iList, bool bAllowIncomplete = false);
GC_API int gc_GetSelProcesseIndexList(int *iList, bool bAllowIncomplete = false);
GC_API int gc_ReadProcessFile(char *sFileName);
GC_API int gc_ReadProcessFileEx(char *sFileName, int iFirstProcess);
GC_API int gc_ReadProcess2File( char* full_file_name, int iNonExactMatches );
GC_API int gc_WriteProcessFile(char *sFileName);
//--process groups
GC_API int gc_GetNumPGroups(int *piNum);
GC_API int gc_GetIndexedPGroupID(int iIndex, int *piPGroupID);
GC_API int gc_GetPGroupNumProcesses(int iPGroupID, int *piNum);
GC_API int gc_GetPGroupTool(int iPGroupID, int iIndex, int *piTool);
GC_API int gc_GetPGroupCustomName(int iPGroupID, int iIndex, char *sName);
GC_API int gc_SetPGroupCustomName(int iPGroupID, int iIndex, const char *sName);
GC_API int gc_GetPGroupCustomDataSize(int iPGroupID, int iIndex, int *piSize);
GC_API int gc_GetPGroupCustomData(int iPGroupID, int iIndex, void *pData);
GC_API int gc_SetPGroupCustomData(int iPGroupID, int iIndex, int iSize, void *pData);
GC_API int gc_GetPGroupNumSolSel(int iPGroupID, int *piNum);
GC_API int gc_GetPGroupSolSelList(int iPGroupID, int *iList);
GC_API int gc_ReplacePGroupSol(int iPGroupID, int iOldSol, int iNewSol, int iEnableFullSel);
GC_API int gc_GetPGroupNumProfileSolSel(int iPGroupID, int *piNum);
GC_API int gc_GetPGroupSolProfileSelList(int iPGroupID, int *iList);
GC_API int gc_GetPGroupUsesProfiler(int iPGroupID, int *piUses);
//CALLBACKS



//******************* POSTING  ************************
//ENUMERATIONS
//STRUCTURE

//DECLARATIONS
// Compost Specific
GC_API int gc_OutputPostLine(const char *sText, int bWithLineNum);
GC_API int gc_GetPostSeqNo(int *piSeqNo);
GC_API int gc_GetPostVarD( char *sName, double *pdVal );
GC_API int gc_GetPostVarB( char *sName, int *piVal );
GC_API int gc_SetPostVarD( char *sName, double dVal );
GC_API int gc_SetPostVarB( char *sName, int iVal );
GC_API int gc_SetPostOp( int iPreviousOp, int iThisOp );
GC_API int gc_SetPostCSOffsets( double *linear, double *rotary );
GC_API int gc_GetCurrentPostPointInPathCS( bool startPoint, double values[3] );
//--Multiple NCF files (one for each flow)
GC_API int gc_TotalFlowFiles( int *iCount );
GC_API int gc_GetFlowFileName( int iIndex, char *sName );
//CALLBACKS
typedef int (*gc_tPostCallBack)(void*);
GC_API int gc_SetPostCallBack(int iMode, gc_tPostCallBack);
GC_API int gc_ClearPostCallBack(int iMode, gc_tPostCallBack);
GC_API int gc_SetPostInitiateFunction( void (*cb_SetInitPosting)(void) );	//for external posting implementations
GC_API int gc_CheckAllowedToInitiatePosting( void );	//this should be called by external posting solutions prior to the start of posting. This will trigger the function set by gc_SetPostInitiateFunction
GC_API int gc_AllowedToInitiatePosting( void );	//to only be called by whatever functionality interrupted posting via ePCB_AllowPostDialog non-zero return value
GC_API int gc_AddPostDisplayText(const char*);	//adds a line of text to the posting status pane

//--custom post command call backs
typedef void (*gc_tPostCmdCallBack)(char*);
typedef int (*gc_tPostBoolCallBack)(char*);
typedef double (*gc_tPostNumCallBack)(char*);
typedef int (*gc_tPostStrCallBack)(char*, char*);
GC_API int gc_SetPostCommandCallBack(char *sName, gc_tPostCmdCallBack);
GC_API int gc_ClearPostCommandCallBack(char *sName);
GC_API int gc_SetPostBooleanCallBack(char *sName, gc_tPostBoolCallBack);
GC_API int gc_ClearPostBooleanCallBack(char *sName);
GC_API int gc_SetPostNumberCallBack(char *sName, gc_tPostNumCallBack);
GC_API int gc_ClearPostNumberCallBack(char *sName);
GC_API int gc_SetPostStringCallBack(char *sName, gc_tPostStrCallBack);
GC_API int gc_ClearPostStringCallBack(char *sName);


//******************* RENDER ************************

//ENUMERATIONS
//--draw
typedef enum
{
	gc_eDCB_Before,
	gc_eDCB_After,
	gc_eDCB_CustomBBox,	// callback outputs in arg the bounding box of all custom entities to be rendered, return non-zero if none
	gc_eDCB_CustomDraw,	// the arg is a pointer to a gc_CustomRenderInfo; do all rendering of custom entities to the display buffer
	gc_eDCB_CustomPick,	// the arg is a pointer to a gc_CustomPickMsg; the callback is either requested to render to pick buffer, or notified that its entity was picked
	gc_eDCB_AfterBlit,	// the arg is a pointer to an array of 4 ints (the blit rect): top, left, bottom, right
	gc_eDCB_CustomPickClear, // not any custom entity is picked
	gc_eDCB_AfterRender,// called after simulation and CPR rendering. The arg is a pointer to an array of 4 ints (the blit rect): top, left, bottom, right
	gc_eDCB_AfterOSDraw,	// the arg is a pointer to an array of 4 ints (the blit rect): top, left, bottom, right
	gc_eDCB_BeforeWire, //used for non-projected, potentially z-buffered rendering
	gc_eDCB_Last		// must be last
}
gc_eDrawCallBack;
typedef enum
{
	gc_eCustomPickNotify,	// the callback is notified that one of its entities was picked
	gc_eCustomPickRender	// the callback should do all rendering of custom entities to the pick buffer
}
gc_eCustomPickMsg;
//--display
typedef enum
{
	gc_eUndef_LT,
	gc_eHpos_LT,
	gc_eVpos_LT,
	gc_eDpos_LT,
	gc_eTopHpos_LT,
	gc_eTopVpos_LT,
	gc_eTopDpos_LT,
	gc_eRad_LT,
	gc_eDia_LT,
	gc_eAngle_LT,
	gc_eDiaVpos_LT,
	gc_eOpCSHpos_LT,
	gc_eOpCSVpos_LT,
	gc_eOpCSDpos_LT,
	gc_eOpCSTopDpos_LT,
	gc_eCustom_LT
} gc_teETLoadType;
typedef enum
{
	gc_eLinear_PT,
	gc_eAngular_PT,
	gc_eTime_PT,
	gc_ePercent_PT,
	gc_eFeed_PT,
	gc_eTolerance_PT,
	gc_eScale_PT,
	gc_eCustom4_PT,
	gc_eCustom5_PT,
	gc_eCustom6_PT,
	gc_eCustom7_PT,
	gc_eFullFloat_PT,
	gc_eCustom8_PT,
	gc_eCustom9_PT,
	gc_eCustom10_PT,
	gc_eCustom11_PT,
	gc_eCustom12_PT,
	gc_eCustom13_PT,
	gc_eCustom14_PT,
	gc_eFullDouble_PT
} gc_teETPrecType;
enum teDisplayInfo
{
	eiDisplayTechnology,		// 1 means OpenGL, 0 means non-OpenGL
	eiDisplayTransitionFrame,	// return 1 if we are currently redrawing the workspace window as part of a transition between views 
	eiDisplayExplodedMode,	// return 1 if we are currently in exploded view mode
};
//--view
typedef enum		// Orientations for gc_SetViewOrientation, iOrientation
{
	gc_eViewTop,
	gc_eViewFront,
	gc_eViewLeft,
	gc_eViewRight,
	gc_eViewBack,
	gc_eViewBottom,
	gc_eViewIso,
	gc_eViewHome
} gc_eViewOrientation;
//--draw
typedef enum			// Types for gc_DrawDimension, iType
{
	gc_eDIM_NONE,
	gc_eAllign,
	gc_eHoriz,
	gc_eVert,
	gc_eHorizFromZero,
	gc_eVertFromZero,
	gc_e2LinesAngle,
	gc_e3PntsAngle,
	gc_eDiameter,
	gc_eRadius,
	gc_eDimPoint
} gc_eDimensionType;
//--poly
typedef enum
{
	gc_eGrayBase,
	gc_eBlueBase,
	gc_eRedBase,
	gc_eYellowBase,
	gc_eLtBlueBase
}
gc_eBaseColor;

//--Machine Sim callback
typedef enum
{
	gc_eMachineSimCallbackTypeNextOp,
	gc_eMachineSimCallbackTypeLast
}
gc_teMachineSimCallbackType;

typedef enum
{
	gc_eGeomWindowMode,
	gc_eLegacyCPRMode,
	gc_eFlashCPRMode,
	gc_eMachineSimMode
}gc_teCurrentRenderMode;
//--Window Management functions
typedef enum
{
	eBalloonMsgType_GetText,
	eBalloonMsgType_GetID,
	eBalloonMsgType_GetContextID
} gc_teBalloonMsgType;
//STRUCTURE
//--draw
typedef struct
{
	int rect[4];	// this is the 2d window of the display/pick buffer (top, left, bottom, right)
	void *caller_id;// use this id with calls to gc_DisplayRender or gc_PickRender
}
gc_CustomRenderInfo;



typedef struct
{
	gc_eCustomPickMsg msg;
	union
	{
		int entity;							// (msg == eCustomPickNofify), this is the id of the entity picked
		gc_CustomRenderInfo render_info;	// (msg == eCustomPickRender)
	}
	info;
}
gc_CustomPickMsg;

//DECLARATIONS
GC_API int gc_SetGlobalDrawSync(bool bInit);
GC_API int gc_GetCurrentRenderMode(int *iMode);
//--display
GC_API int gc_GetDisplayState(int iMode, int *iState);
GC_API int gc_SetDisplayState(int iMode, int iState);
GC_API int gc_SetCustomDisplayMode(int iMode);
GC_API int gc_GetCustomDisplayMode(int *iMode);
GC_API int gc_GetDisplayInfoI(teDisplayInfo id, int *val);
//--view
GC_API int gc_ZoomView(double dScale);
GC_API int gc_PanView(int iPanDir, double dValue);
GC_API int gc_RotView(int iCS, const double *dOrg, const double *dAxis, double dAngle);
GC_API int gc_SetViewMatrix(const double *matrix);
GC_API int gc_GetViewOrientMatrix(double *matrix);
GC_API int gc_SetViewOrientMatrix(const double *matrix);
GC_API int gc_SetViewOrientation(int iOrientation);
GC_API int gc_MapMV(int iCS, const double *dModelPt, double *dScrenPt);
GC_API int gc_MapVM(int iCS, const double *dScreenPt, double depth, double *dModelPt);
//--draw
GC_API int gc_DrawLine2d(double *p1, double *p2, int rgb, int width);
GC_API int gc_DrawLine3d(int iCS, double *p1, double *p2, int rgb, int width);
GC_API int gc_DrawPolyLine3d(int iCS, int iNumPts, double *dPts, int rgb, int width);
GC_API int gc_DrawText2d(char *sText, double *dPos, int iFont, int iRgbColor, int iHeight, int iAlign);
GC_API int gc_DrawText3d(char *sText, int iCS, double *dPos, int iFont, int iRgbColor, int iHeight, int iAlign);
GC_API int gc_DrawSymbol2d(int iSymbol, double *dPos, int iRgbColor, int iSize);
GC_API int gc_DrawSymbol3d(int iSymbol, int iCS, double *dPos, int iRgbColor, int iSize);
GC_API int gc_DrawCircle2d(double *pt, double rad, int iRgbColor, int iWidth);
GC_API int gc_DrawCircle3d(int iCS, double *pt, double rad, int iRgbColor, int iWidth);
GC_API int gc_DrawArc2d(int iDir, double *pt, double dStartAngle, double dEndAngle, double rad, int iRgbColor, int iWidth);
GC_API int gc_DrawArc3d(int iCS, int iDir, double *pt, double *pt1, double *pt2, double rad, int iRgbColor, int iWidth);
GC_API int gc_DrawCurve2d(int degree, int n_knots, int n_ctrls, int *k_mult, double *k_param, double *ctrls, int iRgbColor, int iWidth);
GC_API int gc_DrawCurve3d(int iCS, int degree, int n_knots, int n_ctrls, int *k_mult, double *k_param, double *ctrls, int iRgbColor, int iWidth);
GC_API int gc_DrawPath2d(const void *ptr, int iRgbColor, int iWidth);
GC_API int gc_DrawPath3d(int iCS, const void *ptr, int iRgbColor, int iWidth);
GC_API int gc_DrawRegion2d(const void *region, int iRgbColor, int iWidth);
GC_API int gc_DrawRegion3d(int iCS, const void *region, int iRgbColor, int iWidth);
GC_API int gc_MakeDirArrows(double *aPtLoc, double *aDirVector, bool bOnArrow, bool bOffArrow);
GC_API int gc_DrawDirArrow(bool bOnArrow, bool bOffArrow);
GC_API int gc_DrawDimension(int iType, int iCS, double *dSide1, double *dSide2, double *dApex, double *dLine, double dTextPos, char *sHText, char *sVText, char *sDText);
GC_API int gc_DrawDimArrow(double *dPt1, double *dPt2, double dTextPos, int iH, int iV);
GC_API int gc_DrawVecArrow(double *pos, double *dir);

//--poly
GC_API int gc_DisplayRenderPoly(void *caller_id, int iEntityID, int iVerts, double pVerts[][3], double pNorms[][3], gc_eBaseColor iColor, int bClosed, int bConvex, int bEnclosed);
GC_API int gc_PickRenderPoly(void *caller_id, int iEntityID, int iVerts, double pVerts[][3], double pNorms[][3], int bClosed, int bConvex);
GC_API int gc_IsPolyConvex(int iVerts, double pVerts[][3]);
GC_API int gc_MakeConvexPolys(int iVerts, double pVerts[][3], double pNorms[][3], void **poly_list);
GC_API int gc_GetPolyListCount(void *poly_list, int *piCount);
GC_API int gc_GetPolyNumVerts(void *poly_list, int iIndex, int *piVerts);
GC_API int gc_GetPolyVerts(void *poly_list, int iIndex, double pVerts[][3], double pNorms[][3]);
GC_API int gc_DeletePolyList(void *poly_list);
//--cut part rendering
GC_API int gc_GetCurRenderPos(gc_ProgState *prog_flow_state);
GC_API int gc_SetCurRenderPos(gc_ProgState *prog_flow_state);
GC_API int gc_GetRenderWallThickness(int iCS, int iPosX, int iPosY, double *dStart, double *dEnd, double* dThickness);
GC_API int gc_GetRenderPos(int iCS, int iPosX, int iPosY, int iMax, int *iNumGot, int *iNumAvail, double *dPos);
GC_API int gc_GetRenderVolume(int iWP, double *pdVolume);
GC_API int gc_GetRenderProgIterator(void **itr);				// returns a pointer to the current CPR iterator; please don't advance, reset, or delete
GC_API int gc_GetRenderState(int iFlow, gc_ProgState*);			// returns rendering state for given flow
GC_API int gc_GetRenderFeatType(int iFlow, int *piFeatType);	// returns current rendering feature type for given flow
GC_API int gc_GetRenderFlowPos(int iFlow, double xyz[3], double ijk[3]);// returns current rendering position (xyz) for given flow
GC_API int gc_GetRenderFeatParam(int iFlow, double*);			// returns current rendering feature parameter for given flow (for "meta-features")
GC_API int gc_PushDisplayState();
GC_API int gc_PopDisplayState();
GC_API int gc_InitRenderEx(int iRenderStyle);
GC_API int gc_InitRender();
GC_API int gc_SetRenderSpeed(int iSpeed);
GC_API int gc_GetRenderSpeed(int *iSpeed);
GC_API int gc_StartRender(int iToolMode, int iCheckInterrupt);

typedef enum
{
	gc_eFBRenderMode_ExportToSTL,		//target - const char* filepath
	gc_eFBRenderMode_ExportToSTLByOp,	//target - const char* filepath
	gc_eFBRenderMode_ExportToFBSolid,
	gc_eFBRenderMode_ExportToFBFile,	//target - const char* filepath, data1 - int Workpiece number
	gc_eFBRenderMode_OutputBitmap,		//target - const char* filepath, data1 - int* height/width dimensions
	gc_eFBRenderMode_OutputOpBitmaps,	//target - const char* filepath, data1 - int* height/width dimensions
}gc_teFBRenderMode;

GC_API int gc_FBRender(int iMode, void* target, void* data1, void* data2);

GC_API int gc_GetWPInitialStock(int iWP, int *piInitial);
GC_API int gc_SetWPInitialStock(int iWP, int iInitial );
GC_API int gc_GetWPPreloadStock(int iWP, int *piPreload);
GC_API int gc_SetWPPreloadStock( int iWP, int iPreload );
GC_API int gc_StockIsExtruded(int iWP, int *piExtruded);
GC_API int gc_GetStockPath(int iOp, int iWP, int bBefore, void **ptrPath);	// return path representing stock condition at specified op (lathe only)
GC_API int gc_GetLExtStockPath(int iOp, int iWP, int bBefore, void **ptrPath, double *matrix);
GC_API int gc_GetViewScale(double *dScale);
GC_API int gc_GetViewMatrix(double *dMat);
GC_API int gc_GetViewMatrixEx(double *dMat);
GC_API int gc_SetRenderCS(int iCS);
GC_API int gc_GetRenderMatrix(double *matrix);
//--Window Management functions
GC_API int gc_ManageWindow(HWND hwnd, const char* windowName, int bModal, int* handle);
GC_API int gc_UnmanageWindow(int handle);
GC_API HWND gc_GetAppWindowHandle();
GC_API int gc_GetGeoWindowHandle(int* hwnd, int iData);
GC_API int gc_ShowManagedWindow(int handle, int nShow);
GC_API int gc_GetBalloonHelp( int *iBalloonHelp);
GC_API int gc_SetBalloonHelp(int iBalloonHelp);
GC_API int gc_GetToolTipIDMode();
GC_API int gc_HandleBalloonHelp(int msg, void* lParam, gc_teBalloonMsgType *type, int** iId, int** iSubId, int** iPos, char** ppszHelpString);
enum gc_teManageWindowHandleMap
{
	gc_eManageWindowHandleMap_Add,
	gc_eManageWindowHandleMap_Remove,
	gc_eManageWindowHandleMap_Get
};
GC_API int gc_ManageWindowHandleMap(void* windowHandle, void** pdata, gc_teManageWindowHandleMap action);

/** gc_SetInterrogGroup
*This function sets the interrogation group for a text edit box in a managed window.
*This function must be called once for each text edit box that your plugin wishes Shift-Alt-Click group interrogation to work for.
*
*@param		int handle: managed window handle (returned by gc_ManageWindow).
*@param		int group: arbitrary group id.  text edit boxes registered with the same group ID will be group-interrogated together.
*@param		HWND hwnd: Windows window handle of the text edit box to add to the given group.
*@return	0=success, -1/-3=handle is invalid/unregistered, -2=hwnd already in this group.
*/
GC_API int gc_SetInterrogGroup(int handle, int group, HWND hwnd);
//Trackball/Viewing Management functions
typedef enum
{
	gc_eTrackballControlFunction_TopView = 0,
	gc_eTrackballControlFunction_FrontView,
	gc_eTrackballControlFunction_RightView,
	gc_eTrackballControlFunction_IsoView,
	gc_eTrackballControlFunction_RedrawView,
	gc_eTrackballControlFunction_PreviousView,
	gc_eTrackballControlFunction_UnZoom,
	gc_eTrackballControlFunction_HomeView,
	gc_eTrackballControlFunction_ScreenCenter,
	gc_eTrackballControlFunction_MouseCenter,
	gc_eTrackballControlFunction_StockCenter,
	gc_eTrackballControlFunction_PartCenter,
	gc_eTrackballControlFunction_SelGeoCenter,
	gc_eTrackballControlFunction_UnZoomOnSel,
	gc_eTrackballControlFunction_Zoom = 101,
	gc_eTrackballControlFunction_XAxisRotation,
	gc_eTrackballControlFunction_YAxisRotation,
	gc_eTrackballControlFunction_ZAxisRotation,
	gc_eTrackballControlFunction_XPan,
	gc_eTrackballControlFunction_YPan,
	gc_eTrackballControlFunction_3DControllerXform,
	gc_eTrackballControlFunction_GetCurrentView,
	gc_eTrackballControlFunction_SetCurrentView,
	gc_eTrackballControlFunction_GetCurrentCamera,
	gc_eTrackballControlFunction_SetCurrentCamera,
	gc_eTrackballControlFunction_GetOpenGLViewMatrices,
	gc_eTrackballControlFunction_GetCurrentGeoWindow,
	gc_eTrackballControlFunction_SetCurrentGeoWindow,
	gc_eTrackballControlFunction_MatrixView,
}gc_teTrackballControlCmd;
GC_API int gc_TrackballControl(int iFunctionNum, int bReverse, int bForceDraw, void* data);
//CALLBACKS
typedef void (*gc_tRenderCallBack)(void*);
GC_API int gc_SetRenderCallBack(int iMode, gc_tRenderCallBack);
GC_API int gc_ClearRenderCallBack(int iMode, gc_tRenderCallBack);
GC_API int gc_CallRenderCallBacks(int iMode, void *p);
//--Machine Sim callback
typedef int (*gc_tMachineSimCallBack)(void*);
GC_API int gc_SetMachineSimCallBack(gc_teMachineSimCallbackType eEvent, gc_tMachineSimCallBack);
GC_API int gc_ClearMachineSimCallBack(gc_teMachineSimCallbackType eEvent, gc_tMachineSimCallBack);
GC_API int gc_GetMachineSimCallBack(gc_teMachineSimCallbackType eEvent, gc_tMachineSimCallBack *cb);
//--draw
typedef int (*gc_tDrawCallBack)(void*);
GC_API int gc_SetDrawCallBack(gc_eDrawCallBack iMode, gc_tDrawCallBack);
GC_API int gc_ClearDrawCallBack(gc_eDrawCallBack iMode, gc_tDrawCallBack);

//******************* OTHER  ************************
//ENUMERATIONS

//--plugin
typedef enum
{
	gc_eGetInfoPluginRegistrationData = 1
} gc_teGetInfoPlugin;

typedef enum
{
	gc_ePluginStringPMName = 1,
} gc_tePluginString;

//--tile list management
typedef enum
{
	gc_eTool,
	gc_eProcess,
	gc_eOperation
} gc_TileListID;

typedef enum
{
	gc_eHighlight,
	gc_eRedraw,
	gc_eDoubleClick,
	gc_eClick,
	gc_eMoveToTop,
	gc_eDelete,
	gc_eGetTileColor, //pointer to COLORREF
	gc_eGetTabColor,   //pointer to COLORREF
	gc_eTileMove,//int new cell
	gc_eTileNew
} gc_TileEventID;

typedef struct
{
	gc_TileListID  tileListId;
	gc_TileEventID eventId;
	int		       iCell;
	int            iValue;
} gc_rTileEventCBData;

typedef struct
{
	gc_TileListID  tileListId;
	gc_TileEventID eventId;
	int		       iCell;
	void*          pValue;
} gc_rTileEventExCBData;

typedef enum
{
	gc_ePostExtension,
	gc_eIGESExtension,
	gc_eDXFExtension,
	gc_ePointListExtension,
	gc_eParasolidExtension,
	gc_eSATExtension,
	gc_eSTLExtension,
	gc_eMacroExtension,
	gc_eVDAExtension,
	gc_eSolidEdgeExtension,
	gc_eSolidWorksExtension,
	gc_eCatiaExtension
} gc_eUserFileExtension;
//--Wizard
typedef enum
{
	gc_eHole_Wizard,
	gc_eStock_Wizard,
	gc_eLast_Wizard
} gc_teWizard;
//--DoIt Button Callbacks
typedef enum
{
	gc_eDoItButtonCB_Before,		// rDoItButtonCBData
	gc_eDoItButtonCB_After			// rDoItButtonCBData
} gc_teDoItButtonCallBack;

//--Task manager
enum gc_PROCMGR_EVENTTYPE
{
	gc_ePROCMGR_GETPROCNAME,
	gc_ePROCMGR_CALC,
	gc_ePROCMGR_OUTPUT_TOOLPATH,
	gc_PROCMGR_BUFFER_COMPATIBLE_OPS,
};
//STRUCTURE

#define GC_TILE_SCROLL_TOP		0x00000001 //scrolls the tile to the top of the list
#define GC_TILE_SCROLL_VIEWABLE	0x00000002 //scrolls the tile to the top of the list only if it is not currently visible 

//--RUNTIME API
struct gc_RunTimeInfo;



//DECLARATIONS
//--tile list
GC_API int gc_DeselectTileList(int iTileList);
GC_API int gc_SetTileSelect(int iTileList, int iIndex, int iSelected);
GC_API int gc_GetTileSelect(int iTileList, int iIndex, int *iSelected);
GC_API int gc_SelectOpInsertion(int iIndex, int iSelected);
GC_API int gc_InsertTile(int iTileList, int iIndex);
GC_API int gc_GetTileStatus(int iTileList, int iIndex, int *iStatus);
GC_API int gc_RedrawTiles(int iTileList);
GC_API int gc_RedrawTile(int iTileList, int iIndex);
GC_API int gc_UpdateSyncDlog();
GC_API int gc_ScrollTileList(int iTileList, int iFirstTile);
/** gc_ScrollTileListEx
* Scroll the given tile list 
*@param		int iTileList
*@param		int iFirstTile
*@param		DWORD flags - combination of flags from above
*/
GC_API int gc_ScrollTileListEx(int iTileList, int iFirstTile, DWORD flags );
//--tile list management
GC_API int gc_TileListShown(int iTileID, int* iShown);
GC_API int gc_ShowTileList(int iTileID);
GC_API int gc_HideTileList(int iTileID);
GC_API int gc_GetTileListSize(int iTileID, int* iSize);
GC_API int gc_GetTileListValue(int iTileID, int iIndex, int* iVal);
GC_API int gc_SetTileListStart(int iTileID, int iVal);
GC_API int gc_MoveTile( int iTileList, int iSrcTile, int iDestTile, bool bInsert );
//--custom bitmaps
GC_API int gc_SetCustomTileBitmap(const char *sCustomName, void *bitmap);
GC_API int gc_GetCustomTileBitmap(const char *sCustomName, void **bitmap);
GC_API int gc_ClearCustomTileBitmap(const char *sCustomName);
//--plugin
GC_API int gc_AddPlugInMenuEntry(int iId, char *sLabel);
GC_API int gc_SetPlugInMenuStyle(int iStyle);
GC_API int gc_GetNumPlugInEntry(int *iNumEntry);
GC_API int gc_GetPlugInEntry(int iEntry, char *sDll, char *sTitle, int *iDispatchId, int *iMenuId, int *iMenuItem);
GC_API int gc_RemovePlugInMenuEntry( int iId, int iMenuID, int iMenuItem  );
GC_API int gc_AddPlugInMenu( char *sLabel );
GC_API int gc_AddPlugInMenuItem( int iDispatchID, int iMenuID, char *sLabel, int iStyle, void* pDispatch, void* pUnload );
GC_API int gc_RemovePlugInMenu( int iMenuID );
GC_API int gc_FindPlugInEntry(char *sDllName, char *sTitle, int *iDispatchId, int *iEntry);
GC_API int gc_CallPlugInEntry(int iEntry);
GC_API int gc_CallPlugInGetInfoEntry(int iEntry, int iCmd, void* data1, void* data2);
GC_API int gc_GetCurPlugInEntry(int *iEntry);
GC_API int gc_GetMenuEntryName(int iEntry, char *sName);
GC_API int gc_SetMenuEntryName(int iEntry, char *sName);
GC_API int gc_GetMenuEntryCheck(int iEntry, int *bCheckState);
GC_API int gc_SetMenuEntryCheck(int iEntry, int bCheckState);
//--Command Table Interface
GC_API int gc_GetCMDTable(void** aCmdList);
GC_API int gc_GetCMDTableNumEntries(void* aCmdList, int *iNumEntries);
GC_API int gc_GetCMDTableEntryData(void* aCmdList, int iEntry, char* sFamily, char* sTitle, int* iCommand, int* iModifier, int* iMask);
GC_API int gc_RunCMDTableEntry(void* aCmdList, int iEntry);
GC_API int gc_FreeCMDTable(void* aCmdLis);

//--RUNTIME API
GC_API int gc_GetRunTimeInfo(gc_RunTimeInfo **rt_info);
GC_API int gc_GetRunTimeInfoEx(gc_RunTimeInfo **rt_info, bool bUseOpInstanceScheme);	// set bUseOpInstanceScheme to true to use installed global op instance scheme (e.g. TMS)
GC_API int gc_DeleteRunTimeInfo(gc_RunTimeInfo *rt_info);
GC_API int gc_GetOpRunTimeInfo(const gc_RunTimeInfo *rt_info, int iOp, double *start_secs, double *end_secs, double *feed_len, double *rapid_len);
GC_API int gc_GetOpStartTime(const gc_RunTimeInfo *rt_info, int iOp, double &secs);
GC_API int gc_GetOpEndTime(const gc_RunTimeInfo *rt_info, int iOp, double &secs);
GC_API int gc_GetOpFeedLength(const gc_RunTimeInfo *rt_info, int iOp, double &len);
GC_API int gc_GetOpRapidLength(const gc_RunTimeInfo *rt_info, int iOp, double &len);
GC_API int gc_GetProgEndTime(const gc_RunTimeInfo *rt_info, double &secs);

//--Alert API
GC_API int gc_Ok_Cancel_Alert(char *s1, char *s2, char *s3);
GC_API void gc_Ok_Alert(char *s1, char *s2, char *s3);
//--Quality Assurance API Routines
GC_API int gc_Log_InitStats(void);
GC_API int gc_Log_FilePath(const char *sPath);
GC_API int gc_Log_FileName(const char *sName);
GC_API int gc_Log_ClearFile(void);
GC_API int gc_Log_WriteHeader(const char *sHeader);
GC_API int gc_Log_WriteError(const char *sMessage);
GC_API int gc_Log_Write(const char *sMessage);
GC_API int gc_Log_DumpGeomCounts(void);
GC_API int gc_Log_WriteStats(void);
//--progress bar
GC_API int gc_StartProgress(char *sTitle);
GC_API int gc_SetProgress(double dVal);
GC_API int gc_StopProgress();
GC_API int gc_SetProgressTitle(const char *sTitle);
GC_API int gc_SetTBMessage(const char *sMsg);
GC_API int gc_CheckUserBreak();
GC_API int gc_SetProgressSilent(int iSilent);
//--Config file management functions
GC_API int     gc_GetAppSystemFilePath(const char* sSubDir, const char* sFilename, char* sBuffer);
GC_API int     gc_OpenConfigFile(const char* sFilename, INT_PTR *iFileHandle);
GC_API int     gc_CloseConfigFile(INT_PTR iFileHandle, int iUpdateFlag);
GC_API int     gc_PutConfigFileRecord(INT_PTR iFileHandle, const char* sKey, int iDataSize, const void* pvData);
GC_API int     gc_GetConfigFileRecord(INT_PTR iFileHandle, const char* sKey, int* iDataSize, void* pvData);
GC_API int     gc_GetConfigFileRecordNum(INT_PTR iFileHandle);
GC_API int     gc_GetConfigFileRecordKey(INT_PTR iFileHandle, int iIndex, int* iKey, char* sKey, int iKeyLen );

//--Automated Security Testing
GC_API int gc_SaveFilePath( char *s );
GC_API int gc_GetFilePath( char *s );
//--file extension
GC_API int gc_GetUserFileExtension( gc_eUserFileExtension eFileType, char *sExt);
GC_API int gc_SetUserFileExtension( gc_eUserFileExtension eFileType, char *sExt);

GC_API int gc_GetDefaultFileImportCount( int *iCount );
GC_API int gc_GetDefaultFileFilter( int iIndex, char* sLabel, char* sExt );

//--Wizard
GC_API int gc_IsWizardOpen(gc_teWizard eType, int *iOpen);
GC_API int gc_OpenWizard(gc_teWizard eType);
GC_API int gc_CloseWizard(gc_teWizard eType);

//--Task manager
GC_API bool gc_TaskManagerUpdateProgress(const short iOp, const short nPercent, const char *strMsg);
GC_API void gc_ErrorReport(const short iOp);
GC_API void gc_ErrorMessage(const short iOp, const char *strMsg);
GC_API int gc_UpdateUtilTools(const short iOp, bool bClear);
//CALLBACKS
GC_API int gc_AddNamedCallback( char* sName, void* func_ptr );
GC_API int gc_RemoveNamedCallback( char* sName );
GC_API int gc_GetNamedCallback( char* sName, void * func_ptr );

GC_API void gc_InvalidateEntireToolCSCache();
GC_API void gc_InvalidateToolCSCache(int tool);

typedef int (*gc_tEventCallBack)(int, int, void*);
typedef int (*gc_tWinEventCallBack)(void*, unsigned int, WPARAM, LPARAM);
typedef int (*gc_tSelCallBack)(void*);
GC_API int gc_SetEventCallBack(int iMode, gc_tEventCallBack);
GC_API int gc_ClearEventCallBack(int iMode, gc_tEventCallBack);
GC_API int gc_SetSelectionCallBack(int iMode, gc_tSelCallBack);
GC_API int gc_ClearSelectionCallBack(int iMode, gc_tSelCallBack);
GC_API int gc_SetWinEventCallBack(int iMode, unsigned int iMessage, gc_tWinEventCallBack);
GC_API int gc_ClearWinEventCallBack(int iMode, unsigned int iMessage, gc_tWinEventCallBack);
GC_API int gc_SetInWinMsgLoop(int iIn);
//--tile list management
typedef int (*gc_tTileEventCallBack)(gc_rTileEventCBData* data, void*);
typedef int (*gc_tTileEventExCallBack)(gc_rTileEventExCBData* data, void*);

GC_API int gc_SetTileEventCallback(gc_tTileEventCallBack cb, void* uData);
GC_API int gc_SetTileEventExCallback(gc_tTileEventExCallBack cb, void* uData);
GC_API int gc_RemoveTileEventCallback(gc_tTileEventCallBack cb);
//--DoIt Button Callbacks
typedef struct _gc_rDoitButtonCBData
{
	int iOpSelected;			// First Op Selected, if any (Implies Do/Redo)
} gc_rDoitButtonCBData, *gc_rDoitButtonCBDataPtr;

typedef void (*gc_tDoItButtonCallBack)(gc_rDoitButtonCBDataPtr pCBData);
GC_API int gc_SetDoItButtonCallBack(int iCB, gc_tDoItButtonCallBack call_back);
GC_API int gc_ClearDoItButtonCallBack(int iCB, gc_tDoItButtonCallBack call_back);
//--Task manager
#define PROCMGR_API __cdecl

struct gc_TaskMgrEventData
{
	short	nOp;
	char	pszProcName[MAX_PATH];
};

typedef bool (PROCMGR_API *gc_PFNPROCMGRCALLBACK) (enum gc_PROCMGR_EVENTTYPE EventType, void* EventData, void* UserData);
GC_API void gc_AddTaskManager(const short iOp, const char *strOpType, const bool bConcurrentRunable, gc_PFNPROCMGRCALLBACK pfnProcMgr_Callback, void *pProcMgrCallbackUserdata);
GC_API void gc_AddTaskManagerEx(const short iOp, const short iCompOp, const short *pCompOps, const char *strOpType, const bool bConcurrentRunable, gc_PFNPROCMGRCALLBACK pfnProcMgr_Callback, void *pProcMgrCallbackUserdata);
GC_API int gc_TaskManagerUpdateOp(const short iOp);

// ************ADDED AFTER SILVIA REORDERED THE API******************

//--Op Modifier Manager
GC_API int gc_IsOpModifierDlogOpen();

enum gc_teWGType
{
	gc_ePartGeo,
	gc_ePartStock,
};

/**
*enumeration for setting retrieving Workgroup information using gc_GetWGInfoI & gc_SetWGInfoI
*/
enum gc_teWGInfo
{
	gc_eWGType,
	gc_eWGAxis,		//used with the enumeration
	gc_eWGWrapped,
	gc_eWGRevOrExtruded,
	gc_eWGSpindle
};

/**
*enumeration that relates to the value set and retrieved when using gc_eWGAxis from [[gc_SetWGInfoI]]
*/
enum gc_teWGAxisInfo
{
	gc_eX,
	gc_eY,
	gc_eZ
};

GC_API int gc_WGStockNum( int *wg_id );		// deprecated
GC_API int gc_GetWGStockNum( int *wg_id );	// same as above, function name matches 10.5 for compatibility
GC_API int gc_GetWGInfoI( int wg_id, int option, int *val );
GC_API int gc_SetWGInfoI( int wg_id, int option, int val );

GC_API int gc_FlushPendingUpdates();

enum gc_teDCDDataCB
{
	gc_eDCDDataChangedCB,
	gc_eDCDPartUnitsChangedCB,
	gc_eDCDUpdateStockCB,
	gc_eDCDWindowAddCustomTabCB,
	gc_eDCDWindowRemoveCustomTabCB,
	gc_eDCDWindowEvaluateCustomTabCB,
	gc_eDCDUpdateTitleCB,
	gc_eDCDDataCBLast
};

typedef void(*gc_tDCDCB)(void);
GC_API int gc_AddDCDDataCB( gc_teDCDDataCB eType, gc_tDCDCB cb );
GC_API int gc_ClearDCDDataCB( gc_teDCDDataCB eType, gc_tDCDCB cb );
GC_API int gc_CallDCDDataCallbacks( gc_teDCDDataCB eType );

typedef enum
{
	gc_PostPrefAbsOrInc,
	gc_PostPrefbDateNTime,
	gc_PostPrefbExtendedChars,
	gc_PostPrefbFormatCode,
	gc_PostPrefbFormatName,
	gc_PostPrefbLenInChars,
	gc_PostPrefbLenInFeet,
	gc_PostPrefbLenInMeters,
	gc_PostPrefbNumOfParts,
	gc_PostPrefbOpComm,
	gc_PostPrefbOpNUmNType,
	gc_PostPrefbProgComm,
	gc_PostPrefbProgName,
	gc_PostPrefbStartToolState,
	gc_PostPrefbSubNumber,
	gc_PostPrefbToolComm,
	gc_PostPrefbToolNumNType,
	gc_PostPrefbUtilityData,
	gc_PostPrefbWGComm

}gc_tePostPref;

GC_API int gc_GetPostPrefs( gc_tePostPref ePref, int *iVal );
GC_API int gc_SetPostPrefs( gc_tePostPref ePref, int iVal );

GC_API int gc_GetSessionID( DWORD* session );

GC_API int gc_GetLatheOpToolBBox(int iOp, bool at_start, gc_BBox &bbox);

//-- Sort Features (Modify menu)

typedef enum
{
	gc_eSortTypeSPattern,
	gc_eSortTypeNextClosest,
	gc_eSortTypeReversePattern,
};

GC_API int gc_SortFeats(int iSortType, bool bMainAxisX, double dScanHeight, double dMaxGap, bool bStartCornerPlusX, bool bStartCornerPlusY);
GC_API int gc_CheckAllowSortProcess(void); // force a check of the allow do it callback for the sort process. 

GC_API int gc_CurveElevateDegree(int iRef, int newDegree);
GC_API int gc_GetCurveConnectors(int curveRef, int *r1, int *r2, double *param1, double *param2);
GC_API int gc_CurveElevateDegree(int iRef, int newDegree);
GC_API int gc_CurveInsertKnot(int iRef, double u, double accuracy);
GC_API int gc_CurveParam(int iRef, const double *pt, double *param, int pixelTol);
GC_API int gc_CurveReInterpolate(int iRef, int iNumPoints, double *dPoints, int iClosed, int eParamMode);
GC_API int gc_GetCurveConnectors(int curveRef, int *r1, int *r2, double *param1, double *param2);
GC_API int gc_GetNETPrecision(int eETPrecType); // eETPrecType one of gc_teETPrecType
GC_API int gc_PrecisionString(char *s, double dVal, bool bUseCStr, int iPrec = - 1);
GC_API int gc_GetStringPrecision(bool bUseTool, int* piPrec);
GC_API int gc_ImportToolIntermediateFile(char* file_name);

GC_API int gc_GetTGMinToolPos(long tg, int *val);
GC_API int gc_GetTGMaxToolPos(long tg, int *val);
GC_API int gc_TGHasAnyLiveTooling(long tg, int* spins);
GC_API int gc_GetTGPosLiveTooling(long tg, int pos, int* spins);
GC_API int gc_AnyPartStationSpins(int *spins);
GC_API int gc_GetPartStationSpins(long iWP, int *spins);

// engraving

typedef enum
{
	gc_eTextJustificationLeft = 1,
	gc_eTextJustificationCenter,
	gc_eTextJustificationRight,
};

typedef enum
{
	gc_eTextPositionTopLeft = 1,
	gc_eTextPositionTopCenter,
	gc_eTextPositionTopRight,
	gc_eTextPositionCenterLeft,
	gc_eTextPositionCenterCenter,
	gc_eTextPositionCenterRight,
	gc_eTextPositionBottomLeft,
	gc_eTextPositionBottomCenter,
	gc_eTextPositionBottomRight,
};

typedef enum
{
	gc_eTextFlowLeftToRight = 1,
	gc_eTextFlowRightToLeft,
	gc_eTextFlowBottomUp,
	gc_eTextFlowTopDown,
};

typedef enum
{
	gc_eTextShapeStraight = 1,
	gc_eTextShapeArcLeft,
	gc_eTextShapeArcRight,
};

typedef enum
{
	gc_eTextLinesFlowLeft = 1,
	gc_eTextLinesFlowRight,
};

typedef struct
{
	char	szFont[256];
	double	dCharHeight;

	double	dPt[3];
	int		iJustification;
	int		iPosition;

	double	dAngle;
	double	dRadius;

	double	dBetweenChars;
	double	dBetweenWords;
	double	dBetweenLines;

	int		iTextShape;
	int		iTextFlow;
	int		iLinesFlow;
}gc_trEngraving;

GC_API int gc_GetEngraveData(gc_trEngraving *pData);
GC_API int gc_SetEngraveData(gc_trEngraving pData);
GC_API int gc_EngraveText(char *szText);


// boolean shapes

enum
{
	gc_eCombineShapes_Union = 1,
	gc_eCombineShapes_Difference,
	gc_eCombineShapes_Intersection,
	gc_eCombineShapes_TrimToInside,
	gc_eCombineShapes_TrimToOutside,
	gc_eCombineShapes_Slice,
};

GC_API int gc_CombineSelShapes(int iOption, bool bDeleteShapes = true);

GC_API void gc_GetCurInterfaceLevel(int *level);

enum gc_teOpLock
{
	gc_Lock_MachCS,
	gc_Lock_RotAngle,
	gc_Lock_Coolant,
	gc_Lock_ProgStop,
	gc_Lock_ToolOffset,
	gc_Lock_RotPos,
	gc_Lock_RotTimes,
	gc_Lock_EntryClear,
	gc_Lock_ExitClear,
	gc_Lock_RPM,
	gc_Lock_CRC,
	gc_Lock_CRCOffset,
	gc_Lock_EntryFeed,
	gc_Lock_ContourFeed,
	gc_Lock_RotDupAngle,
	gc_Lock_DrillDwell,
	gc_Lock_Pattern,
	gc_Lock_TapPercent = 19,
	gc_Lock_DrillPosApproach,
	gc_Lock_PrefCanned = 22,
	gc_Lock_CSS = 24,
	gc_Lock_MaxRPM,
	gc_Lock_SpindleDir = 27,
	gc_Lock_LRoughAutoFinish,
	gc_eLastLock = 30
};

GC_API int GC_SetLockVal(gc_teOpLock eLock, int op, int* op_locks, bool val);
GC_API int GC_GetLockVal(gc_teOpLock eLock, int op, int *op_locks, bool *val);

#pragma pack (pop, gc_api_pack)	// restore struct alignment

#endif //_API_H_
