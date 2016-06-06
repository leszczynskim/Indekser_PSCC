#pragma once

#include "GCTools.h" 
#include "GibbsTool.h"

#pragma pack (push, boost_align, 8)

namespace GCTools
{
	class GCTOOLS_API GC_LatheTool : public GC_GibbsTool
	{
	public:
		static const gc_teToolTypes type = gc_eUnsupportedTool;

	protected:
		struct LatheTool;
		LatheTool* p_lt;

		GC_LatheTool();
		GC_LatheTool(const GC_LatheTool& other) = delete;
		GC_LatheTool( double angle );

		void SetSizeEnum( gc_teLTlSize eSize );
		void UpdateInsertAngle();
	public:

		bool IsDBHolder() const;
		bool CanBeObtuse() const;

		virtual ~GC_LatheTool();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		gc_teLTlOrient GetOrientation() const;
		void SetOrientation( gc_teLTlOrient orient );

		virtual void PreserveData( const GC_GibbsTool* ptr );

		virtual bool GetITNonStdAttachment() const;
		virtual void SetITNonStdAttachment(bool bNonStd );

		virtual double GetTipRad(bool bAsPartUnits = false) const;
		virtual void SetTipRad( double tip_rad );

		virtual double GetInsertAngle() const;
		virtual bool SetInsertAngle(double angle);

		virtual gc_teLTlSize GetSizeEnum() const;
		virtual double GetSize( bool bAsPartUnits = false ) const = 0;
		virtual void SetSize( double size ) = 0;

		double GetLegacyStickout(bool bAsPartUnits) const;
		virtual double GetStickOutLen( bool bAsPartUnits = false ) const;
		virtual void SetStickOutLen( double len );
		
		virtual double GetTipHalfAngle() const;

		virtual gc_LTlHolderType GetHolderType() const;
		virtual void SetHolderType(gc_LTlHolderType type);

		virtual GCTools::gc_teToolHolderType GetCustomHolderType() const;

		virtual int GetIndex() const;

		virtual int SetValuesFromIndex(int index);	//returns 0 if successful otherwise returns -1

		virtual double GetTipOffset( bool bAsPartUnits = false ) const;
		virtual void SetTipOffset( double tip_offset );

		virtual double GetLen( bool bAsPartUnits = false ) const;
		virtual void SetLen( double length );

		virtual void GetTileString( char* val ) const;

		virtual bool UsesNotchRamp() const { return true; }

		virtual double GetNotchRamp(bool bAsPartUnits = false) const;
		virtual void SetNotchRamp(double notch);

		virtual void SetCutXPlus( bool b_cut_xplus );
		virtual bool GetCutXPlus() const;

		virtual double GetBAngle() const;
		virtual void SetBAngle( double angle );

		virtual void SetThickness( double thickness ) {}
		virtual double GetThickness(bool bAsPartUnits = false) const {return 0.0;}

		virtual bool SupportsOther() const {return true;}

		virtual void InitValuesFromDB();

		virtual const char* GetPostTypeString() const;
		virtual const char* GetTypeString() const;

		virtual bool GetFaceUp() const;
		virtual void SetFaceUp( bool face_up );
		virtual void MatchFromDB();

		virtual double GetMaxPlungeAngle() const;
		virtual void SetMaxPlungeAngle( double ang );

		virtual void SetRenderedHolderLen( double len );
		virtual double GetRenderedHolderLen(bool bAsPartUnits = false) const;

		virtual void SetSetupAngle( double angle );
		virtual double GetSetupAngle() const;

		virtual double GetOrientedPlungeAngle() const;

		//actually stores the relief from the trailing edge
		virtual double GetHolderDataMaxPlungeAngle() const;
		virtual bool SetHolderDataMaxPlungeAngle(double angle);

		virtual bool GetHolderDataAllowToolBlock(void) const;
		virtual bool SetHolderDataAllowToolBlock(bool allow);

		virtual bool GetHolderDataModifyMaxPlunge(void) const;
		virtual bool SetHolderDataModifyMaxPlunge(bool modify);

		virtual bool SetHolderDataFDim(double fdim);
		virtual double GetHolderDataFDim(bool bAsPartUnits = false) const;

		virtual bool SetHolderDataShankSize(double shank_size);
		virtual double GetHolderDataShankSize(bool bAsPartUnits = false) const;

		virtual bool SetHolderDataGageTipRad(double rad);
		virtual double GetHolderDataGageTipRad(bool bAsPartUnits = false) const;

		virtual bool SetHolderDataLeadAngle(double rad);
		virtual double GetHolderDataLeadAngle(void) const;

		virtual bool SetHolderDataCutDir(gc_tePrimaryCuttingDir dir);
		virtual gc_tePrimaryCuttingDir GetHolderDataCutDir(void) const;

		virtual bool SetHolderDataDimType(gc_teHolderDimType dim_type);
		virtual gc_teHolderDimType GetHolderDataDimType(void) const;


		virtual bool SetCustomHolderAttachment(gc_teLHolderDef attachment);
		virtual gc_teLHolderDef GetCustomHolderAttachment() const;

		virtual void SetUseStandardTouchOff(bool use_std);
		virtual bool UseStandardTouchOff(void) const;

		virtual bool GetHolderDataUseObtuse() const;
		virtual bool SetHolderDataUseObtuse(bool obtuse);

		virtual void SetHolderID(double id);
	};

	class GCTOOLS_API GC_ISOLathe : public GC_LatheTool
	{
	public:
		static const gc_teToolTypes type = gc_eUnsupportedTool;

	protected:
		struct IsoTool;
		IsoTool* p_iso;

		GC_ISOLathe();
		GC_ISOLathe(const GC_ISOLathe& other) = delete;
		GC_ISOLathe( double tip_rad, double inscr_circle, double thickness, double notch_ramp, double insert_angle );

	public:

		virtual ~GC_ISOLathe();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );

		virtual void SetTipRad(double rad);
		virtual double GetTipRad(bool bAsPartUnits = false) const;

		virtual void SetInscribedCircle(double rad);
		virtual double GetInscribedCircle(bool bAsPartUnits = false) const;
		virtual gc_teLTlSize GetSizeEnum() const;

		virtual void SetThickness(double thickness);
		virtual double GetThickness(bool bAsPartUnits = false) const;

		virtual void SetNotchRamp(double notch);
		virtual double GetNotchRamp(bool bAsPartUnits = false) const;

		virtual double GetSize( bool bAsPartUnits = false ) const;
		virtual void SetSize( double size );

	};

	class GCTOOLS_API GC_Diamond : public GC_ISOLathe
	{
	protected:
		GC_Diamond();
		GC_Diamond(const GC_Diamond& other) = delete;
		GC_Diamond( double tip_rad, double inscr_circle, double thickness, double notch_ramp, double insert_angle );

	public:
		virtual ~GC_Diamond();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void CreateProfile( void* path );
	};

	class GCTOOLS_API GC_80DiamondCLT : public GC_Diamond
	{
	public:
		static const gc_teToolTypes type = gc_e80DiaCLT;

	public:
		GC_80DiamondCLT();
		GC_80DiamondCLT( double tip_rad, double inscr_circle, double thickness, double notch_ramp, double insert_angle );

		virtual ~GC_80DiamondCLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual gc_teToolTypes GetType() const { return type; }

		virtual double GetTipHalfAngle() const;
	};

	class GCTOOLS_API GC_55DiamondDLT : public GC_Diamond
	{
	public:
		static const gc_teToolTypes type = gc_e55DiaDLT;

	public:
		GC_55DiamondDLT();
		GC_55DiamondDLT( double tip_rad, double inscr_circle, double thickness, double notch_ramp, double insert_angle );

		virtual ~GC_55DiamondDLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual gc_teToolTypes GetType() const { return type; }

		virtual double GetTipHalfAngle() const;

	};

	class GCTOOLS_API GC_35DiamondVLT : public GC_Diamond
	{
	public:
		static const gc_teToolTypes type = gc_e35DiaVLT;

	public:
		GC_35DiamondVLT();
		GC_35DiamondVLT( double tip_rad, double inscr_circle, double thickness, double notch_ramp, double insert_angle );

		virtual ~GC_35DiamondVLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual gc_teToolTypes GetType() const { return type; }

		virtual double GetTipHalfAngle() const;

	};

	class GCTOOLS_API GC_SquareSLT : public GC_Diamond
	{
	public:
		static const gc_teToolTypes type = gc_eSquareSLT;

	public:
		GC_SquareSLT();
		GC_SquareSLT( double tip_rad, double inscr_circle, double thickness, double notch_ramp, double insert_angle );

		virtual ~GC_SquareSLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual gc_teToolTypes GetType() const { return type; }

		virtual double GetTipHalfAngle() const;

	};

	class GCTOOLS_API GC_RoundRLT : public GC_ISOLathe
	{
	public:
		static const gc_teToolTypes type = gc_eRoundRLT;

	protected:
		struct Round;
		Round* p_rnd;

	public:
		GC_RoundRLT();
		GC_RoundRLT(const GC_RoundRLT& other) = delete;
		GC_RoundRLT(double angle);
		GC_RoundRLT(double angle, double tip_rad, double inscr_circle, double thickness, double notch_ramp, double insert_angle );
		virtual ~GC_RoundRLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual bool SetIncludedAngle( double angle );
		virtual double GetIncludeAngle() const;

		virtual void SetTipRad( double rad );
		virtual void SetInscribedCircle( double rad );

		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual gc_teToolTypes GetType() const { return type; }

		virtual double GetTipHalfAngle() const;

		virtual void CreateProfile( void* path );

	};

	class GCTOOLS_API GC_TriangleTLT : public GC_ISOLathe
	{
	public:
		static const gc_teToolTypes type = gc_eTriangleTLT;

	protected:

	public:
		GC_TriangleTLT();
		GC_TriangleTLT(double tip_rad, double inscr_circle, double thickness, double notch_ramp, double insert_angle );
		GC_TriangleTLT(const GC_TriangleTLT& other) = delete;
		virtual ~GC_TriangleTLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual gc_teToolTypes GetType() const { return type; }

		virtual double GetTipHalfAngle() const;
		virtual void CreateProfile( void* path );
	};

	class GCTOOLS_API GC_TrigonWLT : public GC_ISOLathe
	{
	public:
		static const gc_teToolTypes type = gc_eTrigonWLT;

	protected:

	public:
		GC_TrigonWLT();
		GC_TrigonWLT(double tip_rad, double inscr_circle, double thickness, double notch_ramp, double insert_angle );
		GC_TrigonWLT(const GC_TrigonWLT& other) = delete;
		virtual ~GC_TrigonWLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual gc_teToolTypes GetType() const { return type; }

		virtual double GetTipHalfAngle() const;
		virtual void CreateProfile( void* path );
	};

	class GCTOOLS_API GC_PentagonPLT : public GC_ISOLathe
	{
	public:
		static const gc_teToolTypes type = gc_ePentagonPLT;

	protected:

	public:
		GC_PentagonPLT();
		GC_PentagonPLT(double tip_rad, double inscr_circle, double thickness, double notch_ramp, double insert_angle );
		GC_PentagonPLT(const GC_PentagonPLT& other) = delete;
		virtual ~GC_PentagonPLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual gc_teToolTypes GetType() const { return type; }

		virtual double GetTipHalfAngle() const;
		virtual void CreateProfile( void* path );
	};

	class GCTOOLS_API GC_RectangleLLT : public GC_ISOLathe
	{
	public:
		static const gc_teToolTypes type = gc_eRectangleLLT;

	protected:
		struct Rectangle;
		Rectangle *p_rect;
	public:
		GC_RectangleLLT();
		GC_RectangleLLT( double length );
		GC_RectangleLLT(double length, double tip_rad, double inscr_circle, double thickness, double notch_ramp, double insert_angle );
		GC_RectangleLLT(const GC_RectangleLLT& other) = delete;
		virtual ~GC_RectangleLLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual gc_teToolTypes GetType() const { return type; }

		virtual double GetTipHalfAngle() const;
		virtual void CreateProfile( void* path );

		virtual double GetLen( bool bAsPartUnits = false )  const;
		virtual void SetLen( double len );

		virtual double GetWidth( bool bAsPartUnits = false ) const;
		virtual void SetWidth( double width );
	};

	class GCTOOLS_API GC_ParallelKLT : public GC_RectangleLLT
	{
	public:
		static const gc_teToolTypes type = gc_eParallel55KLT;

	protected:

	public:
		GC_ParallelKLT();
		GC_ParallelKLT( double length );
		GC_ParallelKLT(double length, double tip_rad, double inscr_circle, double thickness, double notch_ramp, double insert_angle );
		GC_ParallelKLT(const GC_ParallelKLT& other) = delete;
		virtual ~GC_ParallelKLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual gc_teToolTypes GetType() const { return type; }

		virtual double GetTipHalfAngle() const;
	};

	class GCTOOLS_API GC_ProfileVNLT : public GC_ISOLathe
	{
	public:
		static const gc_teToolTypes type = gc_eProfileVNLT;

	protected:
		struct ProfVN;
		ProfVN *p_vn;

	public:
		GC_ProfileVNLT();
		GC_ProfileVNLT( double len, double tip_rad, double inscr_circle, double thickness, double notch_ramp, double insert_angle );
		GC_ProfileVNLT(const GC_ProfileVNLT& other) = delete;
		~GC_ProfileVNLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual double GetTipHalfAngle() const;
		virtual void CreateProfile( void* path );

		virtual double GetLen( bool bAsPartUnits = false ) const;
		virtual void SetLen( double length );

		virtual gc_teToolTypes GetType() const {return type;}

		virtual void PreserveData(const GC_GibbsTool* ptr);
	};

	class GCTOOLS_API GC_CutOffLT : public GC_LatheTool
	{
	public:
		static const gc_teToolTypes type = gc_eCutOffLT;
	protected:
		struct CutOff;
		CutOff* p_cut;

	public:
		GC_CutOffLT();
		GC_CutOffLT( double insert_angle, double tip_rad, double size, double thickness, double tip_width, double face_ang, double side_ang, double length );
		GC_CutOffLT(const GC_CutOffLT& other) = delete;
		virtual ~GC_CutOffLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual double GetTipRad( bool bAsPartUnits = false ) const;
		virtual void SetTipRad(double rad);

		virtual double GetSize(bool bAsPartUnits = false) const;
		virtual void SetSize(double size);

		virtual double GetThickness(bool bAsPartUnits = false) const;
		virtual void SetThickness(double thickness);

		virtual double GetTipWidth(bool bAsPartUnits = false) const;
		virtual void SetTipWidth(double width);

		virtual double GetFaceAngle() const;
		virtual void SetFaceAngle(double angle);

		virtual double GetSideAngle() const;
		virtual void SetSideAngle(double angle);

		virtual double GetLen(bool bAsPartUnits = false) const;
		virtual void SetLen(double len);

		virtual void CreateProfile( void* path );

		virtual gc_teToolTypes GetType() const {return type;}

		virtual void GetTileString( char* val ) const;

		virtual bool UsesNotchRamp() const { return false; }

		virtual void PreserveData( const GC_GibbsTool* ptr );

		virtual double GetTipHalfAngle() const;

	};

	class GCTOOLS_API GC_GrooveLT : public GC_CutOffLT
	{
	public:
		static const gc_teToolTypes type = gc_eGrooveLT;
	protected:
		struct Groove;
		Groove* p_grv;

	public:
		GC_GrooveLT();
		GC_GrooveLT( double insert_angle, double tip_rad, double size, double thickness, double tip_width, double tip_len, double tip_offset, double face_ang,
			double side_ang, double length, bool use_deflect_comp, int deflect_comp, bool full_rad );
		GC_GrooveLT(const GC_GrooveLT& other) = delete;

		virtual ~GC_GrooveLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);


		virtual void CreateProfile( void* path );
		
		virtual double GetTipLen(bool bAsPartUnits = false) const;
		virtual void SetTipLen(double len);

		virtual double GetTipOffset(bool bAsPartUnits = false) const;
		virtual void SetTipOffset(double offset);

		virtual bool GetUseDeflectionComp() const;
		virtual void SetUseDeflectionComp( bool use_deflect_comp );

		virtual int GetDeflectionComp() const;
		virtual void SetDeflectionComp( int comp );

		virtual gc_teToolTypes GetType() const {return type;}

		virtual void SetUseFullRad( bool use_full_rad );
		virtual bool GetUseFullRad() const;

		virtual void GetTileString( char* val ) const;

		virtual void PreserveData(const GC_GibbsTool* ptr);

	};

	class GCTOOLS_API GC_ThreadLT : public GC_LatheTool
	{
	protected:
		GC_ThreadLT();
		GC_ThreadLT(const GC_ThreadLT& other) = delete;
	public:
		virtual ~GC_ThreadLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		//ThreadN only has TPI - no pitch values
		virtual double GetTPI() const = 0;
		virtual void SetTPI(double tpi) = 0;

		virtual void SetPitch( double pitch ) = 0;
		virtual double GetPitch() const = 0;

		virtual bool IsTPIStyle() const = 0;

		virtual double GetThickness( bool bAsPartUnits = false ) const = 0;
		virtual void SetThickness(double thickness) = 0;
		virtual void GetThreadStyleString( char* type ) const = 0;

		virtual double GetHalfTipAngle() const;

	};

	class GCTOOLS_API GC_ThreadNLT : public GC_ThreadLT
	{
	public:
		enum gc_eThreadNStyle
		{
			gc_eUN = 0,
			gc_eUNJ,
			gc_eAcme,
			gc_eStub_Acme,
			gc_eAPI,
			gc_eAB_PF_Leading,
			gc_eAB_PF_Trailing,
			gc_eNTF,
			gc_eNJF,
			gc_eISO
		};

		enum gc_eThreadNType
		{
			gc_eNone = 0,
			gc_eCresting,
			gc_eFull,
			gc_eMultiForm,
			gc_ePartial,
			gc_ePositive,
			gc_eUtility,
		};

		static const gc_teToolTypes type = gc_eThreadNLT;
	protected:
		struct ThreadN;
		ThreadN* p_thdn;

	public:
		GC_ThreadNLT();
		GC_ThreadNLT(const GC_ThreadNLT& other) = delete;
		virtual ~GC_ThreadNLT();
		
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);
		
		virtual double GetTipHalfAngle() const;
		
		virtual GC_ThreadNLT::gc_eThreadNStyle GetThreadStyle() const;
		virtual void SetThreadStyle(GC_ThreadNLT::gc_eThreadNStyle style);
		
		virtual GC_ThreadNLT::gc_eThreadNType GetThreadType() const;
		virtual void SetThreadType(GC_ThreadNLT::gc_eThreadNType);

		//insert width
		virtual double GetWidth( bool bAsPartUnits = false ) const;
		virtual void SetWidth( double width );

		virtual double GetFlatLen( bool bAsPartUnits = false ) const;
		virtual void SetFlatLen( double flat_len );

		virtual double GetTipOffset( bool bAsPartUnits = false) const;
		virtual void SetTipOffset( double tip_offset );

		virtual void GC_ThreadNLT::SetLen( double len );
		virtual double GetLen(bool bAsPartUnits = false) const;

		virtual void CreateProfile( void* path );

		virtual void SetTipRad( double tip_rad );
		virtual double GetTipRad(bool bAsPartUnits = false) const;

		virtual void SetThickness( double thickness );
		virtual double GetThickness(bool bAsPartUnits = false) const;

		virtual double GetSize( bool bAsPartUnits = false ) const;
		virtual void SetSize(double size);

		virtual gc_teToolTypes GetType() const {return type;}

		virtual void GetTileString( char* val ) const;

		virtual bool UsesNotchRamp() const { return false; }

		virtual double GetTPI() const;
		virtual void SetTPI(double tpi);

		virtual void SetPitch( double pitch );
		virtual double GetPitch() const;

		virtual bool IsTPIStyle() const;

		virtual int GetIndex() const;

		virtual void GetThreadStyleString( char* type ) const;

		virtual void PreserveData(const GC_GibbsTool* ptr);
 	};

	class GCTOOLS_API GC_ThreadLLT : public GC_ThreadLT
	{
	public:
		static const gc_teToolTypes type = gc_eThreadLLT;

		enum gc_eThreadLStyle
		{
			gc_eUN = 0,
			gc_eUNJ,
			gc_eISO,
			gc_eNPT,
			gc_eAcme,
			gc_eStub_Acme,
			gc_ePart60,
			gc_ePart55,
			gc_eWhit55,
			gc_eBSPT,
			gc_eTrapez,
			gc_eRound,
		};

	protected:
		struct ThreadL;
		ThreadL* p_thdl;

	public:
		GC_ThreadLLT();
		GC_ThreadLLT(const GC_ThreadLLT& other) = delete;
		virtual ~GC_ThreadLLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void PreserveData( const GC_GibbsTool* ptr );

		virtual void CreateProfile( void* path );

		virtual void GetTileString( char* val ) const;
		virtual bool UsesNotchRamp() const { return false; }

		virtual GC_ThreadLLT::gc_eThreadLStyle GetThreadStyle() const;
		virtual void SetThreadStyle(GC_ThreadLLT::gc_eThreadLStyle style);

		virtual void GetThreadEdge( double* edge_out, bool bAsPartUnits = false ) const;
		virtual void SetThreadEdge( double* edge_in );

		virtual double GetSize( bool bAsPartUnits = false ) const;
		virtual void SetSize(double size);

		virtual bool IsTPIStyle() const;

		virtual double GetTPI() const;
		virtual void SetTPI( double tpi );

		virtual double GetPitch() const;
		virtual void SetPitch( double pitch );

		void SetRootRad(double rad);
		double GetRootRad(bool bAsPartUnits = false) const;
		
		void SetCrestRad(double rad);
		double GetCrestRad(bool bAsPartUnits = false) const;

		double GetHalfInsertTipAngle() const;
		virtual double GetTipHalfAngle() const;

		virtual double GetBaseAngle() const;
		virtual void SetBaseAngle( double angle );

		virtual double GetThickness( bool bAsPartUnits = false ) const;
		virtual void SetThickness( double thickenss );

		virtual gc_teToolTypes GetType() const {return type;}

		virtual void GetThreadStyleString( char* type ) const;
	};

	class GCTOOLS_API GC_UtilLT : public GC_LatheTool
	{
	public: 
		static const gc_teToolTypes type = gc_eUtilLT;
	protected:
		struct UtilLT;
		UtilLT* p_util;

	public:
		GC_UtilLT();
		GC_UtilLT( double rad, double len );
		GC_UtilLT(const GC_UtilLT& other) = delete;
		virtual ~GC_UtilLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);


		virtual double GetRad( bool bAsPartUnits = false ) const;
		virtual void SetRad( double rad );

		virtual double GetLen( bool bAsPartUnits = false ) const;
		virtual void SetLen( double len );

		virtual void CreateProfile( void* path );
		virtual bool SupportsOther() const {return false;}

		virtual void GetTileString( char* val ) const;

		virtual double GetSize( bool bAsPartUnits = false ) const {return GetRad(bAsPartUnits) * 2.0;}
		virtual void SetSize( double size ) { SetRad(size/2.0); }

		gc_teToolTypes GetType() const { return type; }
		bool UsesNotchRamp() const {return false;}

		virtual void SetThickness( double thickness );
		virtual double GetThickness(bool bAsPartUnits = false) const;

		virtual void PreserveData( const GC_GibbsTool* ptr );

		virtual int SetValuesFromIndex(int index) { return -1;  }	//not in the database

	};

	class GCTOOLS_API GC_2DFormLT : public GC_LatheTool
	{
	public: 
		static const gc_teToolTypes type = gc_e2DFormLT;
	protected:
		struct Form2DLT;
		Form2DLT* p_2dForm;

	public:
		GC_2DFormLT();
		GC_2DFormLT( double insert_angle );
		GC_2DFormLT( double insert_angle, double thickness );
		GC_2DFormLT(const GC_2DFormLT& other) = delete;
		virtual ~GC_2DFormLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void CreateProfile( void* path );
		virtual bool SupportsOther() const {return false;}

		virtual void GetTileString( char* val ) const;

		virtual bool UsesNotchRamp() const { return true; }
		virtual void SetNotchRamp(double notch);
		virtual double GetNotchRamp(bool bAsPartUnits = false) const;

		gc_teToolTypes GetType() const { return type; }

		virtual double GetSize( bool bAsPartUnits = false ) const {return 0.0;}
		virtual void SetSize( double size ) {};

		virtual double GetThickness( bool bAsPartUnits = false ) const;
		virtual void SetThickness( double thickness );

		virtual void PreserveData( const GC_GibbsTool* ptr );

		virtual int SetValuesFromIndex(int index) { return -1; }	//not in the database
	};

	class GCTOOLS_API GC_3DFormLT : public GC_2DFormLT
	{
	public:
		static const gc_teToolTypes type = gc_e3DFormLT;
	protected:
		struct Form3DLT;
		Form3DLT* p_3Dform;

	public:
		GC_3DFormLT();
		GC_3DFormLT( double insert_angle );
		GC_3DFormLT( double insert_angle, double thickness );
		GC_3DFormLT(const GC_3DFormLT& other) = delete;
		virtual ~GC_3DFormLT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void CreateProfile( void* path );
		virtual bool SupportsOther() const {return false;}

		int GetSolidRef() const;

		virtual void GetTileString( char* val ) const;
		virtual bool UsesNotchRamp() const { return false; }

		gc_teToolTypes GetType() const { return type; }

		virtual double GetSize( bool bAsPartUnits = false ) const {return 0.0;}
		virtual void SetSize( double size ) {};

		virtual void SetThickness( double thickness );
		virtual double GetThickness(  bool bAsPartUnits = false ) const;

		virtual int SetValuesFromIndex(int index) { return -1; }	//not in the database

	};

	
	class GCTOOLS_API GC_75DiamondELT : public GC_Diamond
	{
	public:
		static const gc_teToolTypes type = gc_e75DiaELT;

	public:
		GC_75DiamondELT();
		GC_75DiamondELT( double tip_rad, double inscr_circle, double thickness, double notch_ramp, double insert_angle );

		virtual ~GC_75DiamondELT();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual gc_teToolTypes GetType() const { return type; }

		virtual double GetTipHalfAngle() const;

	};
}

#pragma pack (pop, boost_align)
