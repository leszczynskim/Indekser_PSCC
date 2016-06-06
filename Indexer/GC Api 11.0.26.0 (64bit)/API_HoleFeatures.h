#pragma once

#include "API_HoleStructures.h"

GC_API bool gc_GetImportingHolesState();
GC_API void gc_SetImportingHolesState(bool bState);

GC_API int  gc_StartHoleImport(int iSource);				// call before importing any holes
GC_API int  gc_FinishHoleImport();							// call after importing holes
GC_API int  gc_InitImportedHole(gcHF_sFeature *pFeature, int *iNewHoleNum);		// call to get clean data for next hole to import
GC_API int	gc_ValidateHoleFeature(int iHoleNum);			// validate hole data, calculate hole type if not already set
GC_API int  gc_AddImportedHole(int *iNewHoleNum);			// call to add/update hole
GC_API int  gc_ClearHoleContents(int iHoleNum);

GC_API int	gc_DeleteAllHoleFeatures();
GC_API int	gc_GetHoleFeaturesFromCustomData();
GC_API int	gc_SaveHoleFeaturesToCustomData();

GC_API int	gc_CreateHoleFeature(int *iHoleNum, gcHF_sFeature *pFeature);
GC_API int	gc_DeleteHoleFeature(int iHoleNum);
GC_API int  gc_DeleteHoleFeatureBySolid(int iSolid, bool bReloadHoleData = true);  // returns number of holes deleted

GC_API int	gc_CreateHoleSegment(int iHoleNum, int *iSegment, gcHF_sSegment *pSegment);
GC_API int	gc_AddHoleSegment(int iHoleNum, gcHF_sSegment pSegment, int *iSegment = NULL);
GC_API int	gc_RemoveHoleSegment(int iHoleNum, int iSegment, int *iNumSegments = NULL);
GC_API int	gc_InsertHoleSegment(int iHoleNum, int iInsertSegmentNum, gcHF_sSegment pSegment, int *iNumSegments = NULL); //Set iInsertSegmentNum = total num of segments +1 to insert to the end

//GC_API int	gc_UpdateHoleFeaturesSolidRef();

GC_API int	gc_NumHoleFeatures();
GC_API int	gc_GetListHoleFeatures(int *iList, int iSize);
GC_API int	gc_FirstHoleFeature();
GC_API int	gc_LastHoleFeature();
GC_API bool	gc_DoesHoleFeatureExist(int iHoleNum);

GC_API int	gc_NumVisibleHoleFeatures();
GC_API int	gc_GetListVisibleHoleFeatures(int *iList, int iSize);
GC_API bool gc_IsHoleFeatureVisible(int iHoleNum);

GC_API int	gc_NumSelectedHoleFeatures();
GC_API int	gc_GetListSelectedHoleFeatures(int *iList, int iSize);
GC_API int	gc_FirstSelectedHoleFeature();
GC_API int	gc_SetHoleFeatureSelected(int iHoleNum, bool bSelected);
GC_API int	gc_SelectAllHoleFeatures();
GC_API int	gc_DeselectAllHoleFeatures();
GC_API int	gc_ToggleAllHoleFeatures();

GC_API int	gc_SelectHoleFeature(int iHoleNum, int iRedraw);
GC_API int	gc_DeselectHoleFeature(int iHoleNum, int iRedraw);

GC_API bool gc_HoleFeatureIsInch(int iHoleNum);
GC_API int	gc_GetHoleFeatureCS(int iHoleNum);
GC_API int	gc_GetHoleFeatureWPCS(int iHoleNum);
GC_API int	gc_GetHoleFeatureNumSegments(int iHoleNum, int *iNumSegments);
GC_API int	gc_GetHoleFeatureSegmentData(int iHoleNum, int iSegment, int *iType, double *dData, bool *bThreaded);
GC_API int	gc_GetHoleFeatureSol(int iHoleNum, int *iSolRef);

GC_API int	gc_CreateHFSegmentPopUpItem(int iHoleNum, int iSegment, bool bInch, char *szItem);

GC_API int	gc_CreateHoleFeatureCS(int iHoleNum, int *iCS);

GC_API int	gc_DrawAllHoleFeatures();
GC_API int	gc_DrawOneHoleFeature(int iHoleNum);

GC_API int	gc_GetHoleFeatureInfoI(int iHoleNum, int id, int *iVal);
GC_API int	gc_GetHoleFeatureInfoD(int iHoleNum, int id, double *dVal);
GC_API int	gc_GetHoleFeatureInfoX(int iHoleNum, gcHF_sFeature *pFeature);

GC_API int	gc_GetHoleFeatureGroups(int iHoleNum, int *iGroups);
GC_API int	gc_GetHoleFeatureFaces(int iHoleNum, gc_TopoId *iFaces);

GC_API int	gc_SetHoleFeatureInfoI(int iHoleNum, int id, int iVal);
GC_API int	gc_SetHoleFeatureInfoD(int iHoleNum, int id, double *dVal);
GC_API int	gc_SetHoleFeatureInfoX(int iHoleNum, gcHF_sFeature pFeature);

GC_API int	gc_ClearHoleFeatureFaces(int iHoleNum);
GC_API int	gc_AddHoleFeatureFace(int iHoleNum, gc_TopoId iFace);
GC_API int	gc_SetHoleFeatureListFaces(int iHoleNum, gc_TopoId *iListFaces, int iNumFaces);

GC_API int	gc_GetHoleSegmentInfoI(int iHoleNum, int iSegment, int id, int *iVal);
GC_API int	gc_GetHoleSegmentInfoD(int iHoleNum, int iSegment, int id, double *dVal);
GC_API int	gc_GetHoleSegmentInfoX(int iHoleNum, int iSegment, gcHF_sSegment *pSegment);

GC_API int	gc_SetHoleSegmentInfoI(int iHoleNum, int iSegment, int id, int iVal);
GC_API int	gc_SetHoleSegmentInfoD(int iHoleNum, int iSegment, int id, double *dVal);
GC_API int	gc_SetHoleSegmentInfoX(int iHoleNum, int iSegment, gcHF_sSegment pSegment);

GC_API int  gc_CalculateHoleType(int iHoleNum);

GC_API int	gc_ClearHoleFeatureSegments(int iHoleNum);

GC_API int	gc_GetHoleNumberFromGeoRef(int iWG, int iRef);
GC_API int	gc_GetHoleNumberFromFaceRef(int iSol, gc_TopoId iFace);

GC_API int	gc_GetNumHoleGroups();
GC_API int	gc_GetListHoleGroups(int *iListGroups);
GC_API int	gc_GetGroupNumHoles(int iGroupNum, int *iNumHoles);
GC_API int	gc_GetGroupHoleList(int iGroupNum, int *iList);
GC_API int	gc_CreateHoleGroup(int *iGroupNum, char *szName);
GC_API int  gc_SetHoleGroupName(int iGroupNum, char *szName);
GC_API int  gc_GetHoleGroupName(int iGroupNum, char *szName);
GC_API int	gc_GetHoleGroupShown(int iGroupNum, bool *bShow);
GC_API int	gc_SetHoleGroupShown(int iGroupNum, bool bShow);
GC_API int	gc_GetHoleGroupEye(int iGroupNum, bool *bSelected);
GC_API int	gc_SetHoleGroupEye(int iGroupNum, bool bSelected);
GC_API int	gc_AddHoleToGroup(int iGroupNum, int iHoleNum);
GC_API int	gc_AddHolesToGroup(int iGroupNum, int *iListHoles, int iNumHoles);
GC_API int	gc_RemoveHoleFromGroup(int iHoleNum, int iGroupNum);
GC_API int	gc_RemoveHolesFromGroup(int iGroupNum, int *iListHoles, int iNumHoles);
GC_API int	gc_RemoveAllHolesFromGroup(int iGroupNum);
GC_API int	gc_DeleteHoleGroup(int iGroupNum, bool bDeleteHoles = false);

GC_API int  gc_GetHoleNumGroups(int iHoleNum, int *iNumGroups, bool bRecalculate);
GC_API int  gc_RecalcAllHoleNumGroups();

GC_API void	gc_SetHFDepthFirstHole(int iHoleNum, int iSegment, bool bMatchProperties,
	bool bMatchLength, bool bMatchDia, bool bMatchTaper, bool bMatchMethod,
	gcHF_sDepthHoleFeature *trDepthFirstHoleFeature);

GC_API int	gc_GetHFRStartLevels(int iHoleNum, int iCS, double *dStart, double *dStartPlusClear);
GC_API int	gc_GetHFStartDepth(bool bAbsolute, gcHF_sDepthHoleFeature trStartFirstHoleFeature, int iHoleNum,  gc_teStartDepthType eHolePos, int iCS, double *dStart);
GC_API int	gc_GetHFEndDepth(int iToolNum, bool bAbsolute, gcHF_sDepthHoleFeature trDepthFirstHoleFeature, int iHoleNum, gc_teEndDepthType eHolePos, int iCS, double *dDepth, double *dStartDia, double *dEndDia);

GC_API bool gc_GetHoleToolTipRadiusAngle(int iToolNum, double *dToolTipRadius, double *dToolTipAngle);
GC_API double gc_GetHoleToolTipLen(int iToolNum);

// functions to replace code that used old hole features, only use if necessary
// convert code to use new hole data where possible

GC_API int	gc_GetHolePartTop(int iHoleNum, double *dVal);	// lp_gchf_GetFeatInfoD(iRef, efHfPartTop, dPartTop)
GC_API int	gc_GetHoleTopZ(int iHoleNum, double *dVal);		// lp_gchf_GetFeatInfoD(iRef, efHfTopZ, dTopZ)
GC_API int  gc_SwapHoleFeatures(int iHoleNumOne, int iHoleNumTwo);
GC_API int  gc_ReverseHoleFeature(int iHoleNum);
GC_API int  gc_ReplaceHoleSolidReferences(int iOriginalHoleSolidRef, int iNewHoleSolidRef);

GC_API double gc_GetHoleDiaTolerance();

GC_API int gc_SetHoleImportOptions(bool bImportDataAsNew);

enum
{
	gc_eGroupSameHoleDataMethods = 1,
	gc_eGroupSameHoleDataAllDiameters,
	gc_eGroupSameHoleDataIntDepths,
	gc_eGroupSameHoleDataFinalDepth,
};

GC_API int gc_GroupSameHoleData(int iHoleNum1, int iHoleNum2, int iData, double dTol);

GC_API int gc_OpenCompoundHoleEditor(int iHoleNum);
GC_API int gc_UpdateCompoundHoleEditor(int iHoleNum);
GC_API int gc_ActivateHoleAlignedCS(int iHoleNum, int *iNewCS, bool *bNewCS);
GC_API int gc_UpdateHoleGroupEyes();
