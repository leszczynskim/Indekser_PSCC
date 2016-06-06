/* API_IntTooling.h
 *
 * 13 May 2015 : Mike O
 *
 */ 

#pragma once

#ifdef INSIDE_VIRTUAL
	#define GC_API_IT extern "C" __declspec( dllexport )
#else
	#define GC_API_IT extern "C" __declspec( dllimport )
#endif

#pragma pack (push, gc_api_it_pack, 8)	// 8 byte alignment for api structures

enum gcit_teMachineInfo
{
	gcit_eMachine_bUsesBlocks = 1,			// does this machine use blocks (read only)
	gcit_eMachine_iNumToolGroups,			// number of toolgroups (read only)
	gcit_eMachine_iNumBlockMakes = 101,		// number of block makes supported
	gcit_eMachine_sBlockMake,				// block make (read only)
	gcit_eMachine_bUsesFixtures = 201,		// does this machine use fixtures (read only)
	gcit_eMachine_iNumFixtureMakes,			// number of fixture makes supported
	gcit_eMachine_sFixtureMake,				// fixture make (read only)
	gcit_eMachine_iNumAttachNodes = 221,	// number of nodes that are suitable for attaching fixtures (read only)
	gcit_eMachine_sAttachNode,				// attachment node name (read only)
	gcit_eMachine_iNumFixtureNodes = 241,	// number of nodes that are configured for attaching fixtures (read only)
	gcit_eMachine_sFixtureNode,				// fixture node name (read only)
	gcit_eMachine_iNumFixtures = 261,		// number of fixtures in current part (read only)
	gcit_eMachine_iNumBlockTypes = 301,		// total number of block types supported (read only)
	gcit_eMachine_iBlockType,				// block type value (read only)
	gcit_eMachine_sBlockType,				// block type name (read only)
	gcit_eMachine_iListBlockTypes,			// list of block types (read only)
	gcit_eMachine_iNumShankSizes = 401,		// total number of shank sizes supported (read only)
	gcit_eMachine_iShankSize,				// shank size value (read only)
	gcit_eMachine_sShankSize,				// shank size as text (read only)
	gcit_eMachine_iListShankSizes,			// list of shank sizes (read only)
};

enum gcit_teToolGroupInfo
{
	gcit_eToolGroup_iType = 1,			// toolgroup type (read only)
	gcit_eToolGroup_bATC,				// is this toolgroup an atc (read only)
	gcit_eToolGroup_iUseBlocks,			// does this toolgroup use blocks (0=no, 1=yes, 2=from another tg (use enum eToolGroupUseBlocks...)
	gcit_eToolGroup_iMasterTg,			// master toolgroup number, if this is a slave toolgroup
	gcit_eToolGroup_iNumStations,		// number of stations (read only)
	gcit_eToolGroup_iFirstStation,		// number of first station (read only)
	gcit_eToolGroup_bMultiPosBlocks,	// does this toolgroup support multi position blocks
};

enum gcit_teStationInfo
{
	gcit_eStation_bATC = 1,				// is this station an atc (read only)
	gcit_eStation_bBlockTypeAny,		// does this station support any block type
	gcit_eStation_iNumBlockTypes,		// number of blocks types supported (read only)
	gcit_eStation_iBlockType,			// block type value
	gcit_eStation_sBlockType,			// block type as text (read only)
	gcit_eStation_iListBlockTypes,		// list of block types
	gcit_eStation_bShankSizeAny,		// does this station support any shank size
	gcit_eStation_iNumShankSizes,		// number of shank sizes supported
	gcit_eStation_iShankSize,			// shank size value
	gcit_eStation_sShankSize,			// shank size as text (read only)
	gcit_eStation_iListShankSizes,		// list of shank sizes
	gcit_eStation_bOffsetX,				// can a block in this station be positioned in X
	gcit_eStation_bOffsetY,				// can a block in this station be positioned in Y
	gcit_eStation_bOffsetZ,				// can a block in this station be positioned in Z
	gcit_eStation_iOrientType,			// block orientation type (0=fixed, 1=front/back turret, 2=rotary)
	gcit_eStation_dOrientX,				// position adjustment in X, if attached to opposite face of turret
	gcit_eStation_dOrientY,				// position adjustment in Y, if attached to opposite face of turret
	gcit_eStation_dOrientZ,				// position adjustment in Z, if attached to opposite face of turret
	gcit_eStation_bCustomSubPos,		// does this station have a list of sub position
	gcit_eStation_iNumCustomSubPos,		// number of sub positions
	gcit_eStation_iCustomSubPos,		// sub position number
	gcit_eStation_iListCustomSubPos,	// list of sub positions
	gcit_eStation_iOtherBlockNum,		// station number of block used for tools in this position (0 if none)
	gcit_eStation_iOtherBlockPos,		// sub position number, if a block from another station is used
	gcit_eStation_dOtherBlockTrans,		// transformation matrix when a block from another station is used (read only)
};

enum gcit_teBlockInfo
{
	gcit_eBlock_sName = 1,				// block name
	gcit_eBlock_sFile,					// filename (without .vnc) also used for image file and sim file (read only)
	gcit_eBlock_bMetric,				// true, if metric
	gcit_eBlock_bOffsetX,				// true, if user can adjust block along X direction
	gcit_eBlock_bOffsetY,				// true, if user can adjust block along Y direction
	gcit_eBlock_bOffsetZ,				// true, if user can adjust block along Z direction
	gcit_eBlock_iNumOrient,				// number of orientations (equally spaced around 360 degrees)
	gcit_eBlock_iDefaultOrient,			// default orientation
	gcit_eBlock_iNumSimFiles,			// number of fb files used for simulation (read only)
	gcit_eBlock_iNumToolPos,			// number of tool positions (read only)
	gcit_eBlock_iToolPos,				// one tool position (CS number) (read only)
	gcit_eBlock_sToolPos,				// one tool position (CS name) (read only)
	gcit_eBlock_iListToolPos,			// list of tool positions (CS numbers)
	gcit_eBlock_sDefaultCS,				// default CS name
	gcit_eBlock_iNumBlockTypes,			// number of block types (read only)
	gcit_eBlock_iBlockType,				// one block type (int value) (read only)
	gcit_eBlock_sBlockType,				// one block type (text displayed) (read only)
	gcit_eBlock_iListBlockTypes,		// list of types (drill/turn/boring bar etc)
	gcit_eBlock_iNumShankSizes,			// number of shank sizes (read only)
	gcit_eBlock_iShankSize,				// one shank size (int value) (read only)
	gcit_eBlock_sShankSize,				// one shank size (text displayed) (read only)
	gcit_eBlock_iListShankSizes,		// list of shank sizes in either 64th inch or 100th mm
	gcit_eBlock_iNumAllTypes,			// number of block types available (read only)
	gcit_eBlock_iListAllTypes,			// list of all types available (read only)
	gcit_eBlock_iNumAllShanks,			// number of shank sizes available (read only)
	gcit_eBlock_iListAllShanks,			// list of all shank sizes available (read only)
};

enum gcit_teToolGroupUseBlocks
{
	gcit_eToolGroupUseBlocksNo = 0,		// toolgroup does not used blocks
	gcit_eToolGroupUseBlocksYes = 1,	// toolgroup uses blocks
	gcit_eToolGroupUseBlocksTg = 2,		// toolgroup uses blocks from another toolgroup (this is a slave toolgroup)
};

enum gcit_teToolGroupType
{
	gcit_eToolGroupType_Turret = 1,
	gcit_eToolGroupType_Slide,
	gcit_eToolGroupType_Gang,
	gcit_eToolGroupType_LegacyTurret,
	gcit_eToolGroupType_LegacyNonTurret,
	gcit_eToolGroupType_Other,
};

enum gcit_teBlockType
{
	gcit_eBlockType_Turn = 1,
	gcit_eBlockType_Drill,
	gcit_eBlockType_BoreBar,
	gcit_eBlockType_Cutoff,
	gcit_eBlockType_RtAngle,
	gcit_eBlockType_Live,
};

enum gcit_teStationOrientType
{
	gcit_eStationOrient_Fixed = 0,
	gcit_eStationOrient_Turret = 1,
	gcit_eStationOrient_Rotary = 2,
};

enum gcit_teFixtureType
{
	gcit_eFixtureTypeAny = 0,
	gcit_eFixtureTypeChuck = 1,
	gcit_eFixtureTypeTailstock,
	gcit_eFixtureTypeSteady,
	gcit_eFixtureTypeGuideBushing,
	gcit_eFixtureTypeOther = 999,
};

enum gcit_teAttachNodeInfo
{
	gcit_eAttachNode_iNodeType = 1,	// wp, util, tool pos (read only)
	gcit_eAttachNode_sNodeType,		// text displayed for node type (read only)
	gcit_eAttachNode_iId,			// node id (read only)
	gcit_eAttachNode_sName,			// internal node name (read only)
	gcit_eAttachNode_sUser,			// user node name (read only)
	gcit_eAttachNode_iFixtureType,	// type of fixture that can be attached, 0=any
	gcit_eAttachNode_sFixtureType,	// text displayed for fixture type (read only)
	gcit_eAttachNode_sFixtureUser,	// user defined fixture name, use when fixture type = other
	gcit_eAttachNode_iWP,			// if this is a wp node, the wp number (read only)
};

enum gcit_teFixtureNodeInfo
{
	gcit_eFixtureNode_iNodeType = 1,// wp, util, tool pos (read only)
	gcit_eFixtureNode_sNodeType,	// text displayed for node type (read only)
	gcit_eFixtureNode_iId,			// node id (read only)
	gcit_eFixtureNode_sName,		// user node name (read only)
	gcit_eFixtureNode_sUser,		// user node name (read only)
	gcit_eFixtureNode_iFixtureType,	// type of fixture that can be attached, 0=any
	gcit_eFixtureNode_sFixtureType,	// text displayed for fixture type (read only)
	gcit_eFixtureNode_sFixtureUser,	// user defined fixture name, use when fixture type = other
	gcit_eFixtureNode_iWP,			// if this is a wp node, the wp number (read only)
};

GC_API_IT int gcit_Blocks_GetNumMakes(int *iNumMakes, bool bReloadBlockMakes = false);
GC_API_IT int gcit_Blocks_GetMakeName(int iIndex, char *szMake);
GC_API_IT int gcit_Blocks_GetNumBlocks(char *szMake, int *iNumBlocks);
GC_API_IT int gcit_Blocks_GetName(char *szMake, int iIndex, char *szBlock);

GC_API_IT int gcit_Blocks_GetInfo (char *szMake, char *szBlock, gcit_teBlockInfo id, int iVal, int *iData, bool *bData, double *dData, char *szData);
GC_API_IT int gcit_Blocks_GetInfoI(char *szMake, char *szBlock, gcit_teBlockInfo id, int *iData);
GC_API_IT int gcit_Blocks_GetInfoB(char *szMake, char *szBlock, gcit_teBlockInfo id, bool *bData);
GC_API_IT int gcit_Blocks_GetInfoD(char *szMake, char *szBlock, gcit_teBlockInfo id, double *dData);
GC_API_IT int gcit_Blocks_GetInfoS(char *szMake, char *szBlock, gcit_teBlockInfo id, char *szData);

GC_API_IT int gcit_Blocks_GetListTypes(char *szMake, char *szBlock, int *iList, int iMax);
GC_API_IT int gcit_Blocks_GetListShankSizes(char *szMake, char *szBlock, int *iList, int iMax);

GC_API_IT int gcit_Blocks_AddNewMake(char *szMake);
GC_API_IT int gcit_Blocks_DeleteMake(char *szMake);
GC_API_IT int gcit_Blocks_RenameMake(char *szOld, char *szNew);

GC_API_IT int gcit_Blocks_AddNewBlock(char *szMake, char *szBlock);
GC_API_IT int gcit_Blocks_DeleteBlock(char *szMake, char *szBlock);

GC_API_IT int gcit_Blocks_SetInfo(char *szMake, char *szBlock, gcit_teBlockInfo id, int iVal, int *iData, bool *bData, double *dData, char *szData);
GC_API_IT int gcit_Blocks_SetInfoI(char *szMake, char *szBlock, gcit_teBlockInfo id, int iData);
GC_API_IT int gcit_Blocks_SetInfoB(char *szMake, char *szBlock, gcit_teBlockInfo id, bool bData);
GC_API_IT int gcit_Blocks_SetInfoD(char *szMake, char *szBlock, gcit_teBlockInfo id, double dData);
GC_API_IT int gcit_Blocks_SetInfoS(char *szMake, char *szBlock, gcit_teBlockInfo id, char *szData);

GC_API_IT int gcit_Blocks_AddNewType(char *szMake, char *szBlock, int iType);
GC_API_IT int gcit_Blocks_DeleteType(char *szMake, char *szBlock, int iType);

GC_API_IT int gcit_Blocks_AddNewShankSize(char *szMake, char *szBlock, int iSize);
GC_API_IT int gcit_Blocks_DeleteShankSize(char *szMake, char *szBlock, int iSize);

GC_API_IT int gcit_GetBlockTypeText(int iType, char *sz);
GC_API_IT int gcit_GetListAllBlockTypes(int *iList, int iSize, int *iNum);

GC_API_IT int gcit_IsShankSizeValid(int iSize, bool *bValid);
GC_API_IT int gcit_GetShankSizeText(int iSize, char *sz);
GC_API_IT int gcit_GetListAllShankSizes(int *iList, int iSize, int *iNum);

GC_API_IT int gcit_GetFixtureTypeText(int iType, char *sz);

GC_API_IT int gcit_Machine_GetInfo (gcit_teMachineInfo id, int iVal, int *iData, bool *bData, double *dData, char *szData);
GC_API_IT int gcit_Machine_GetInfoI(gcit_teMachineInfo id, int *iData);
GC_API_IT int gcit_Machine_GetInfoB(gcit_teMachineInfo id, bool *bData);
GC_API_IT int gcit_Machine_GetInfoD(gcit_teMachineInfo id, double *dData);
GC_API_IT int gcit_Machine_GetInfoS(gcit_teMachineInfo id, char *szData);

GC_API_IT int gcit_Machine_GetToolGroupInfo (int iToolGroupNum, gcit_teToolGroupInfo id, int iVal, int *iData, bool *bData, double *dData, char *szData);
GC_API_IT int gcit_Machine_GetToolGroupInfoI(int iToolGroupNum, gcit_teToolGroupInfo id, int *iData);
GC_API_IT int gcit_Machine_GetToolGroupInfoB(int iToolGroupNum, gcit_teToolGroupInfo id, bool *bData);
GC_API_IT int gcit_Machine_GetToolGroupInfoD(int iToolGroupNum, gcit_teToolGroupInfo id, double *dData);
GC_API_IT int gcit_Machine_GetToolGroupInfoS(int iToolGroupNum, gcit_teToolGroupInfo id, char *szData);

GC_API_IT int gcit_Machine_GetStationInfo (int iToolGroupNum, int iStationNum, gcit_teStationInfo id, int iVal, int *iData, bool *bData, double *dData, char *szData);
GC_API_IT int gcit_Machine_GetStationInfoI(int iToolGroupNum, int iStationNum, gcit_teStationInfo id, int *iData);
GC_API_IT int gcit_Machine_GetStationInfoB(int iToolGroupNum, int iStationNum, gcit_teStationInfo id, bool *bData);
GC_API_IT int gcit_Machine_GetStationInfoD(int iToolGroupNum, int iStationNum, gcit_teStationInfo id, double *dData);
GC_API_IT int gcit_Machine_GetStationInfoS(int iToolGroupNum, int iStationNum, gcit_teStationInfo id, char *szData);

GC_API_IT int gcit_Machine_GetStationListTypes(int iToolGroupNum, int iStationNum, int *iList, int iMax);
GC_API_IT int gcit_Machine_GetStationListShanks(int iToolGroupNum, int iStationNum, int *iList, int iMax);
GC_API_IT int gcit_Machine_GetStationListCustomSubPos(int iToolGroupNum, int iStationNum, int *iList, int iMax);

GC_API_IT int gcit_Machine_SetInfo (gcit_teMachineInfo id, int iVal, int *iData, bool *bData, double *dData, char *szData);
GC_API_IT int gcit_Machine_SetInfoI(gcit_teMachineInfo id, int iData);
GC_API_IT int gcit_Machine_SetInfoB(gcit_teMachineInfo id, bool bData);
GC_API_IT int gcit_Machine_SetInfoD(gcit_teMachineInfo id, double dData);
GC_API_IT int gcit_Machine_SetInfoS(gcit_teMachineInfo id, char *szData);

GC_API_IT int gcit_Machine_SetToolGroupInfo (int iToolGroupNum, gcit_teToolGroupInfo id, int iVal, int *iData, bool *bData, double *dData, char *szData);
GC_API_IT int gcit_Machine_SetToolGroupInfoI(int iToolGroupNum, gcit_teToolGroupInfo id, int iData);
GC_API_IT int gcit_Machine_SetToolGroupInfoB(int iToolGroupNum, gcit_teToolGroupInfo id, bool bData);
GC_API_IT int gcit_Machine_SetToolGroupInfoD(int iToolGroupNum, gcit_teToolGroupInfo id, double dData);
GC_API_IT int gcit_Machine_SetToolGroupInfoS(int iToolGroupNum, gcit_teToolGroupInfo id, char *szData);

GC_API_IT int gcit_Machine_SetStationInfo (int iToolGroupNum, int iStationNum, gcit_teStationInfo id, int iVal, int *iData, bool *bData, double *dData, char *szData);
GC_API_IT int gcit_Machine_SetStationInfoI(int iToolGroupNum, int iStationNum, gcit_teStationInfo id, int iData);
GC_API_IT int gcit_Machine_SetStationInfoB(int iToolGroupNum, int iStationNum, gcit_teStationInfo id, bool bData);
GC_API_IT int gcit_Machine_SetStationInfoD(int iToolGroupNum, int iStationNum, gcit_teStationInfo id, double dData);
GC_API_IT int gcit_Machine_SetStationInfoS(int iToolGroupNum, int iStationNum, gcit_teStationInfo id, char *szData);

GC_API_IT int gcit_Machine_GetAttachNodeInfo (int iNodeIndex, gcit_teAttachNodeInfo id, int *iData, bool *bData, double *dData, char *szData);
GC_API_IT int gcit_Machine_GetAttachNodeInfoI(int iNodeIndex, gcit_teAttachNodeInfo id, int *iData);
GC_API_IT int gcit_Machine_GetAttachNodeInfoB(int iNodeIndex, gcit_teAttachNodeInfo id, bool *bData);
GC_API_IT int gcit_Machine_GetAttachNodeInfoD(int iNodeIndex, gcit_teAttachNodeInfo id, double *dData);
GC_API_IT int gcit_Machine_GetAttachNodeInfoS(int iNodeIndex, gcit_teAttachNodeInfo id, char *szData);

GC_API_IT int gcit_Machine_SetAttachNodeInfo (int iNodeIndex, gcit_teAttachNodeInfo id, int *iData, bool *bData, double *dData, char *szData);
GC_API_IT int gcit_Machine_SetAttachNodeInfoI(int iNodeIndex, gcit_teAttachNodeInfo id, int iData);
GC_API_IT int gcit_Machine_SetAttachNodeInfoB(int iNodeIndex, gcit_teAttachNodeInfo id, bool bData);
GC_API_IT int gcit_Machine_SetAttachNodeInfoD(int iNodeIndex, gcit_teAttachNodeInfo id, double dData);
GC_API_IT int gcit_Machine_SetAttachNodeInfoS(int iNodeIndex, gcit_teAttachNodeInfo id, char *szData);

GC_API_IT int gcit_Machine_GetFixtureNodeInfo (int iNodeIndex, gcit_teFixtureNodeInfo id, int *iData, bool *bData, double *dData, char *szData);
GC_API_IT int gcit_Machine_GetFixtureNodeInfoI(int iNodeIndex, gcit_teFixtureNodeInfo id, int *iData);
GC_API_IT int gcit_Machine_GetFixtureNodeInfoB(int iNodeIndex, gcit_teFixtureNodeInfo id, bool *bData);
GC_API_IT int gcit_Machine_GetFixtureNodeInfoD(int iNodeIndex, gcit_teFixtureNodeInfo id, double *dData);
GC_API_IT int gcit_Machine_GetFixtureNodeInfoS(int iNodeIndex, gcit_teFixtureNodeInfo id, char *szData);

GC_API_IT int gcit_Machine_SetFixtureNodeInfo (int iNodeIndex, gcit_teFixtureNodeInfo id, int *iData, bool *bData, double *dData, char *szData);
GC_API_IT int gcit_Machine_SetFixtureNodeInfoI(int iNodeIndex, gcit_teFixtureNodeInfo id, int iData);
GC_API_IT int gcit_Machine_SetFixtureNodeInfoB(int iNodeIndex, gcit_teFixtureNodeInfo id, bool bData);
GC_API_IT int gcit_Machine_SetFixtureNodeInfoD(int iNodeIndex, gcit_teFixtureNodeInfo id, double dData);
GC_API_IT int gcit_Machine_SetFixtureNodeInfoS(int iNodeIndex, gcit_teFixtureNodeInfo id, char *szData);

struct gcit_teSetupBlock
{
	char szMake[256];
	char szName[64];
};

struct gcit_teSetupFixture
{
	char szMake[256];
	char szName[64];
};

enum gcit_teSetupBlockInfo
{
	gcit_eSetup_Block_sMake = 1,	// block make (read only)
	gcit_eSetup_Block_sName,		// block name (read only)
	gcit_eSetup_Block_sDefaultCS,	// default attachment CS name
	gcit_eSetup_Block_iOrientation,	// default orientation, used if it a multi-orientation block
	gcit_eSetup_Block_bOffsetX,		// can this block position be adjusted in X (read only)
	gcit_eSetup_Block_bOffsetY,		// can this block position be adjusted in Y (read only)
	gcit_eSetup_Block_bOffsetZ,		// can this block position be adjusted in Z (read only)
	gcit_eSetup_Block_dOffsetX,		// position adjustment in X direction (read only)
	gcit_eSetup_Block_dOffsetY,		// position adjustment in Y direction (read only)
	gcit_eSetup_Block_dOffsetZ,		// position adjustment in Z direction (read only)
};

enum gcit_teSetupFixtureInfo
{
	gcit_eSetup_Node_iNodeId = 1,	// node id
	gcit_eSetup_Node_iNodeType,		// node type
	gcit_eSetup_Node_sNodeType,		// text displayed for node type
	gcit_eSetup_Node_sNodeName,		// node name
	gcit_eSetup_Node_sUserName,		// user node name
	gcit_eSetup_Node_iFixtureType,	// type of fixture that can be attached, 0=any
	gcit_eSetup_Node_sFixtureType,	// text displayed for fixture type
	gcit_eSetup_Node_sFixtureUser,	// user defined fixture name, use when fixture type = other
	gcit_eSetup_Node_iNumFixtures,	// number of fixtures attached to node
	gcit_eSetup_Node_sFixtureMake,	// make of fixture attached to node
	gcit_eSetup_Node_sFixtureName,	// name of fixture attached to node
};

// blocks assigned to stations
GC_API_IT int gcit_Setup_Station_GetListMatchingBlocks(int iToolGroupNum, int iStationNum, gcit_teSetupBlock *rSetupBlock, int iSize, int *iNum);
GC_API_IT int gcit_Setup_Station_GetMatchingBlock(int iToolGroupNum, int iStationNum, int iIndex, gcit_teSetupBlock *rSetupBlock);

GC_API_IT int gcit_Setup_Station_GetBlock(int iToolGroupNum, int iStationNum, char *szMake, char *szName);
GC_API_IT int gcit_Setup_Station_SetBlock(int iToolGroupNum, int iStationNum, int iIndex);
GC_API_IT int gcit_Setup_Station_RemoveBlock(int iToolGroupNum, int iStationNum);

GC_API_IT int gcit_Setup_Station_GetInfo (int iToolGroupNum, int iStationNum, gcit_teBlockInfo id, int iVal, int *iData, bool *bData, double *dData, char *szData);
GC_API_IT int gcit_Setup_Station_GetInfoI(int iToolGroupNum, int iStationNum, gcit_teBlockInfo id, int *iData);
GC_API_IT int gcit_Setup_Station_GetInfoB(int iToolGroupNum, int iStationNum, gcit_teBlockInfo id, bool *bData);
GC_API_IT int gcit_Setup_Station_GetInfoD(int iToolGroupNum, int iStationNum, gcit_teBlockInfo id, double *dData);
GC_API_IT int gcit_Setup_Station_GetInfoS(int iToolGroupNum, int iStationNum, gcit_teBlockInfo id, char *szData);

GC_API_IT int gcit_Setup_Station_SetInfo (int iToolGroupNum, int iStationNum, gcit_teBlockInfo id, int iVal, int *iData, bool *bData, double *dData, char *szData);
GC_API_IT int gcit_Setup_Station_SetInfoI(int iToolGroupNum, int iStationNum, gcit_teBlockInfo id, int iData);
GC_API_IT int gcit_Setup_Station_SetInfoB(int iToolGroupNum, int iStationNum, gcit_teBlockInfo id, bool bData);
GC_API_IT int gcit_Setup_Station_SetInfoD(int iToolGroupNum, int iStationNum, gcit_teBlockInfo id, double dData);
GC_API_IT int gcit_Setup_Station_SetInfoS(int iToolGroupNum, int iStationNum, gcit_teBlockInfo id, char *szData);

// blocks assigned to tools
GC_API_IT int gcit_Setup_Tool_GetListMatchingBlocks(int iToolNum, gcit_teSetupBlock *rSetupBlock, int iSize, int *iNum);
GC_API_IT int gcit_Setup_Tool_GetMatchingBlock(int iToolNum, int iIndex, gcit_teSetupBlock *rSetupBlock);

GC_API_IT int gcit_Setup_Tool_GetBlock(int iToolNum, char *szMake, char *szName);
GC_API_IT int gcit_Setup_Tool_SetBlock(int iToolNum, int iIndex);
GC_API_IT int gcit_Setup_Tool_RemoveBlock(int iToolNum);

GC_API_IT int gcit_Setup_Tool_GetInfo (int iToolNum, gcit_teBlockInfo id, int iVal, int *iData, bool *bData, double *dData, char *szData);
GC_API_IT int gcit_Setup_Tool_GetInfoI(int iToolNum, gcit_teBlockInfo id, int *iData);
GC_API_IT int gcit_Setup_Tool_GetInfoB(int iToolNum, gcit_teBlockInfo id, bool *bData);
GC_API_IT int gcit_Setup_Tool_GetInfoD(int iToolNum, gcit_teBlockInfo id, double *dData);
GC_API_IT int gcit_Setup_Tool_GetInfoS(int iToolNum, gcit_teBlockInfo id, char *szData);

GC_API_IT int gcit_Setup_Tool_SetInfo (int iToolNum, gcit_teBlockInfo id, int iVal, int *iData, bool *bData, double *dData, char *szData);
GC_API_IT int gcit_Setup_Tool_SetInfoI(int iToolNum, gcit_teBlockInfo id, int iData);
GC_API_IT int gcit_Setup_Tool_SetInfoB(int iToolNum, gcit_teBlockInfo id, bool bData);
GC_API_IT int gcit_Setup_Tool_SetInfoD(int iToolNum, gcit_teBlockInfo id, double dData);
GC_API_IT int gcit_Setup_Tool_SetInfoS(int iToolNum, gcit_teBlockInfo id, char *szData);

// fixtures added to the part
GC_API_IT int gcit_Setup_Part_GetNumFixtures(int *iNumFixtures);
GC_API_IT int gcit_Setup_Part_GetFixture(int iListIndex, int *iNodeIndex, char *szMake, char *szName);
GC_API_IT int gcit_Setup_Part_RemoveFixture(int iListIndex);
GC_API_IT int gcit_Setup_Part_RemoveAllFixtures();

// fixtures assigned to nodes
GC_API_IT int gcit_Setup_Node_GetListMatchingFixtures(int iNodeIndex, gcit_teSetupFixture *rSetupFixture, int iSize, int *iNum);
GC_API_IT int gcit_Setup_Node_GetMatchingFixture(int iNodeIndex, int iMatchIndex, gcit_teSetupFixture *rSetupFixture);

GC_API_IT int gcit_Setup_Node_GetNumFixtures(int iNodeIndex, int *iNumFixtures);
GC_API_IT int gcit_Setup_Node_GetFixture(int iNodeIndex, int iFixtureIndex, char *szMake, char *szName);
GC_API_IT int gcit_Setup_Node_AddFixture(int iNodeIndex, int iMatchIndex);
GC_API_IT int gcit_Setup_Node_RemoveFixture(int iNodeIndex, int iFixtureIndex);
GC_API_IT int gcit_Setup_Node_RemoveAllFixtures(int iNodeIndex);

#pragma pack (pop, gc_api_it_pack)	// restore struct alignment