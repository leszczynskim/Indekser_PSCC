#pragma once

#pragma pack (push, gc_api_pack_10, 8)	// 8 byte alignment for api structures

enum	// hole type
{
	gcHF_eHoleType_Unknown = 0,
	gcHF_eHoleType_Simple,
	gcHF_eHoleType_Tap,
	gcHF_eHoleType_Ream,
	gcHF_eHoleType_BoltHole,
	gcHF_eHoleType_SpotFace,
	gcHF_eHoleType_Bore,
	gcHF_eHoleType_BoreThru,
	gcHF_eHoleType_BackBore,
	gcHF_eHoleType_Compound,
};

enum	// hole state
{
	gcHF_eHoleState_Unknown = 0,
	gcHF_eHoleState_Visible,
	gcHF_eHoleState_Hidden,
	gcHF_eHoleState_Bagged,
	gcHF_eHoleState_Deleted,
	gcHF_eHoleState_Dormant,
};

enum	// import state
{
	gcHF_eImportState_Unknown = 0,
	gcHF_eImportState_Original,
	gcHF_eImportState_Updated,
	gcHF_eImportState_Added,
};

enum	// hole reference type (read only)
{
	gcHF_eHoleRefType_Unknown = 0,
	gcHF_eHoleRefType_Geo,
	gcHF_eHoleRefType_Solid,
};

enum	// hole feature source
{
	gcHF_eHoleSource_Unknown = 0,
	gcHF_eHoleSource_Geo,
	gcHF_eHoleSource_Afr,
	gcHF_eHoleSource_Solidworks,
	gcHF_eHoleSource_SolidEdge,
	gcHF_eHoleSource_Catia,
	gcHF_eHoleSource_Inventor,
};

enum	// hole end condition
{
	gcHF_eHoleEndCondition_Unknown = 0,
	gcHF_eHoleEndCondition_Blind,
	gcHF_eHoleEndCondition_Through,
	gcHF_eHoleEndCondition_ThruBlind,
	gcHF_eHoleEndCondition_Obstructed,
	gcHF_eHoleEndCondition_Spherical,
};

enum	// hole segment type
{
	gcHF_eSegmentType_Unknown = 0,
	gcHF_eSegmentType_Simple,
	gcHF_eSegmentType_Threaded,
};

enum	// hole segment method
{
	gcHF_eSegmentMethod_Unknown = 0,
	gcHF_eSegmentMethod_Drill,
	gcHF_eSegmentMethod_Bore,
	gcHF_eSegmentMethod_Ream,
};

enum	// hole segment data
{
	gcHF_eiSegmentType,			// segment type
	gcHF_eiSegmentiMethod,		// segment method
	gcHF_efSegmentPitch,		// thread pitch (if threaded)
	gcHF_efSegmentTPI,			// TPI (if threaded)
	gcHF_efSegmentDiaTop,		// diameter of segment at the top 
	gcHF_efSegmentDiaBottom,	// diameter of segment at the bottom
	gcHF_efSegmentDistTop,		// distance from the top position of the hole to the start of segment
	gcHF_efSegmentDistBottom,	// distance from the top position of the hole to the end of segment
	gcHF_efSegmentLength,		// segment length
	gcHF_efSegmentTaper,		// segment taper angle
	gcHF_eiSegmentThreaded,		// is segment threaded, calculated from segment type (1=threaded)
};

enum	// hole data
{
	gcHF_eiState,			// hole state (visible, hidden, bagged...)
	gcHF_eiSelected,		// 1=selected, 0=not selected

	gcHF_eiSource,			// hole source
	gcHF_eiHoleType,		// hole type

	gcHF_eiRefType,			// hole reference type

	gcHF_eiSolRef,			// solid associated with hole (if created from solid)
	gcHF_eiNumFaces,		// number of faces associated with hole (if created from solid)
	gcHF_eiListFaces,		// list of solid faces

	gcHF_eiGeoRef,			// geometry ref associated with hole (if created from geometry)
	gcHF_eiGeoWG,			// WG of geometry

	gcHF_eiWP,				// workpiece

	gcHF_eiUnits,			// units, inch(1) or metric(0)

	gcHF_efTopClearance,	// top clearance
	gcHF_efBottomClearance,	// bottom clearance
	gcHF_efTipAngle,		// tip angle
	gcHF_efAxis,			// direction of the hole
	gcHF_efPosTop,			// top position of the hole
	gcHF_efPosBottom,		// bottom position of the hole
	
	gcHF_eiEndCondition,	// end condition

	gcHF_eiNumSegments,		// number of hole segments

	gcHF_eiCS,				// hole reference CS

	gcHF_eiImportState,		// hole import state
};

typedef struct
{
	int		iSource;			// eHF_HoleSource
	int		iHoleType;			// eHF_HoleType

	int		iRefType;			// eHF_RefType
	int		iSolRef;			// Solid associated with hole

	int		iGeoRef;			// Point or Circle
	int		iGeoWG;				// WG of geometry

	int		iWP;				// Workpiece

	int		iUnits;				// inch (1) or metric (0)

	double	dTopClearance;		// Top Clearance
	double	dBottomClearance;	// Bottom Clearance
	double	dTipAngle;			// Tip Angle
	double	dAxis[3];			// Direction of the hole
	double	dPosTop[3];			// Top position of the hole
	double	dBottom[3];			// Bottom position of the hole (read only)
	int		iEndCondition;		// eHF_HoleEndCondition
}gcHF_sFeature;		// only used to pass via the api

typedef struct
{
	int		iType;				// eHF_SegmentType
	int		iMethod;			// eHF_SegmentMethod
	double	dPitch;				// Thread Pitch (if Threaded)
	double	dDiaTop;			// Diameter of segment at the top 
	double	dDiaBottom;			// Diameter of segment at the bottom
	double	dDistTop;			// Distance from the top position of the hole to the start of segment
	double	dDistBottom;		// Distance from the top position of the hole to the end of segment
}gcHF_sSegment;		// only used to pass via the api

typedef struct 
{
	int		iHoleNum;
	int		iSegment;

	bool	bInch;

	bool	bMatchProperties;

	bool	bMatchLength;
	bool	bMatchDia;
	bool	bMatchTaper;
	bool	bMatchMethod;
	
	double	dMatchLength;
	double	dMatchDia;
	double	dMatchTaper;
	int		iMatchMethod;

	bool	bThreaded;
	double	dPitch;
}gcHF_sDepthHoleFeature;	// only used by gc_SetHFDepthFirstHole and g_GetHFDepthHole

#pragma pack (pop, gc_api_pack_10)	// restore struct alignment
