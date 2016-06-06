#pragma once

#include "GibbsTool.h"
#include "MillShanks.h"
#include "MillOptions.h"

namespace GCTools
{
	
	class GCTOOLS_API GC_MillTool : public GC_GibbsTool
	{
	private:
		struct MillTool;
		MillTool* p_mt;

	protected:
		GC_MillShank* p_shank;
		GC_MillOptions* p_options;


	public:
		GC_MillTool();
		GC_MillTool(const GC_MillTool& other) = delete;
		GC_MillTool( double rad, double len );
		GC_MillTool(  double flute_rad, double flute_len, double len );

		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version);

		const GC_MillOptions* GetOptionsPtr() const;
		GC_MillOptions* GetOptionsPtr();

		//accessors
		gc_teDirection GetSpindleDir() const;
		void SetSpindleDir( gc_teDirection dir );
		gc_teMTlOrient GetOrientation() const;
		void SetOrientation( gc_teMTlOrient orient );
		const GC_MillShank* GetShank() const;
		GC_MillShank* GetShank();

		void SetHolderType( gc_teMHolderOpt type );
		gc_teMHolderOpt GetHolderType( ) const;

		gc_teMHolderDesc GetFrontHolderType( ) const;
		void SetFrontHolderType( GCTools::gc_teMHolderDesc type );
		GCTools::gc_teShankType GetShankType() const;
		virtual void SetShankType( gc_teShankType type );

		//quick shank accessors when you just need the general top rad & overall length
		virtual double GetShankRad(bool bAsPartUnits = false) const;
		void SetShankRad( double val );
		double GetShankLen(bool bAsPartUnits = false) const;
		void SetShankLen(double length);

		double GetTopShankLen( bool bAsPartUnits ) const;

		void SetLeadTip( double lead_tip );
		double GetLeadTip( bool bAsPartUnits = false ) const;


		virtual void SetUnits( gc_teToolUnits units );
		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual double GetTopCornerRad(bool bAsPartUnits = false) const;
		virtual void SetTopCornerRad( double rad );
		
		//bottom corner radius
		virtual double GetCornerRad(bool bAsPartUnits = false) const;
		virtual void SetCornerRad( double rad );

		virtual double GetRad(bool bAsPartUnits = false) const;
		virtual void SetRad( double rad );

		virtual void SetNumFlutes( int flutes );
		virtual int GetNumFlutes() const;

		virtual double GetLen(bool bAsPartUnits = false) const;
		virtual void SetLen( double len );
		virtual double GetFluteLen(bool bAsPartUnits = false) const;
		virtual void SetFluteLen( double len );
		virtual double GetFluteRad(bool bAsPartUnits = false) const;
		virtual void SetFluteRad( double rad );
		virtual bool SupportOptions() const {return false;};
		virtual bool GetOptions() const;
		virtual void SetOptions( bool bEnabled );

		virtual double GetTipRad(bool bAsPartUnits = false) const;
		virtual void SetTipRad(double rad);
		
		virtual double GetDraftAngle() const;
		virtual void SetDraftAngle( double angle );
		virtual double GetHolderID() const;

		virtual void CreateShankProfile( void*path );

		virtual ~GC_MillTool();

		virtual bool SyncShankNFluteRad() const { return true; }
		virtual double GetStickOutLen( bool bAsPartUnits = false ) const;
		virtual void SetStickOutLen( double len );

		virtual long GetCRCOffset() const;
		virtual void SetCRCOffset( long offset );

		virtual long GetRawCRCOffset() const;

		virtual double GetPitch() const;
		virtual void SetPitch( double pitch );

		virtual double GetTPI() const;
		virtual void SetTPI( double tpi );

		//returns the radius at the tool at a given "depth" from the tip of the tool. 0.0 is the tip of the tool, positive values move towards the top of the tool
		virtual double GetRadAtVal( double depth ) const;	//always in part units

		virtual void GetTileString( char* val ) const;

		virtual const char* GetPostTypeString() const;
		virtual const char* GetTypeString() const;

		virtual GCTools::gc_teToolHolderType GetCustomHolderType() const;

	};

	class GCTOOLS_API GC_EndMill : public GC_MillTool
	{
	protected:
		struct EndMill;

		GC_EndMill();
		GC_EndMill( double btm_rad, double rad, double len, double shank_rad, double tool_len );
		GC_EndMill(const GC_EndMill& other) = delete;

		EndMill* p_em;

	public:
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version);

		//virtual int GetProfile( void* path ) const;
		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual double GetLen(bool bAsPartUnits = false) const;
		virtual void SetLen( double length );
		virtual bool SupportOptions() const {return true;}
		
		//corner rad is BOTTOM corner rad
		virtual double GetCornerRad(bool bAsPartUnits = false) const;
		virtual void SetCornerRad(double btm_corner_rad);

		virtual void CreateProfile( void* path );

		virtual bool SyncShankNFluteRad() const;

		virtual ~GC_EndMill();
	};

	class GCTOOLS_API GC_FinishEndMill : public GC_EndMill
	{
	public:
		static const gc_teToolTypes type = gc_eFEMT;

		GC_FinishEndMill();

		virtual ~GC_FinishEndMill() {}

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);


		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );

		virtual gc_teToolTypes GetType() const { return type; }

	};

	class GCTOOLS_API GC_RoughEndMill : public GC_EndMill 
	{
	public:
		static const gc_teToolTypes type = gc_eREMT;
		//static gc_teToolTypes type = gc_eREMT;

	public:
		GC_RoughEndMill();

		//default destructor 

		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );

		virtual gc_teToolTypes GetType() const { return type; }

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);
	};

	class GCTOOLS_API GC_BallEndMill : public GC_EndMill 
	{
	public:
		static const gc_teToolTypes type = gc_eBEMT;

	public:
		GC_BallEndMill();
		GC_BallEndMill( const GC_BallEndMill& other );

		virtual ~GC_BallEndMill() {}

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual void SetCornerRad( double rad );
		virtual double GetCornerRad(bool bAsPartUnits = false) const;
		virtual void SetRad(double rad);

		virtual gc_teToolTypes GetType() const { return type; }
	};

	class GCTOOLS_API GC_SpotFaceTool : public GC_EndMill
	{
	public:
		static const gc_teToolTypes type = gc_eSpotFaceMT;

	public:

		GC_SpotFaceTool();

		virtual ~GC_SpotFaceTool();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);


		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );

		virtual gc_teToolTypes GetType() const { return type; }
	};

	class GCTOOLS_API GC_ThrdMillHalf : public GC_MillTool
	{
	public:
		static const gc_teToolTypes type = gc_eThrdMillHalfProfMT;

	protected:
		struct HalfThrdMill;
		HalfThrdMill* p_thrdmill;

	public:
		GC_ThrdMillHalf();
		GC_ThrdMillHalf(const GC_ThrdMillHalf& other) = delete;
		GC_ThrdMillHalf(double thrd_angle, double rad, double flute_len, double shank_len, double shank_rad);

		virtual ~GC_ThrdMillHalf();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual double GetTipAngle() const;
		virtual void SetTipAngle(double angle);
		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );

		virtual double GetRadAtVal( double depth ) const;

		virtual gc_teToolTypes GetType() const { return type; }
		virtual bool SyncShankNFluteRad() const {return false;}
	};

	class GCTOOLS_API GC_Bore : public GC_MillTool
	{
	public:
		static const gc_teToolTypes type = gc_eBoreMT;

	protected:
		struct Bore;
		Bore* p_bore;

	public:
		GC_Bore();
		GC_Bore(const GC_Bore& other) = delete;

		virtual ~GC_Bore();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual bool SupportOptions() const { return false; }
		virtual void SetRad( double rad );

		virtual double GetNonCuttingLen(bool bAsPartUnits = false) const;
		virtual void SetNonCuttingLen( double len );

		virtual gc_teToolTypes GetType() const { return type; }
		virtual bool SyncShankNFluteRad() const {return false;}
	};

	class GCTOOLS_API GC_BackBore : public GC_Bore
	{
	public:
		static const gc_teToolTypes type = gc_eBackBoreMT;

	protected:
		struct BBore;
		BBore* p_bbore;

	public:
		GC_BackBore();
		GC_BackBore(const GC_BackBore& other) = delete;

		virtual ~GC_BackBore();

 		template<class Archive>
 		void serialize(Archive& ar, const unsigned int version);

		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual bool SupportOptions() const { return false; }

		virtual double GetCuttingLen(bool bAsPartUnits = false) const;
		virtual void SetCuttingLen( double len );
		virtual double GetFluteLen(bool bAsPartUnits = false) const;
		virtual void SetFluteLen( double len );

		virtual gc_teToolTypes GetType() const { return type; }

		virtual void CreateShankProfile( void*path );
	};

	class GCTOOLS_API GC_Drill : public GC_MillTool
	{
	public:
		static const gc_teToolTypes type = gc_eDrillMT;
	protected:
		struct Drill;
		Drill* p_drill;

	public:
		GC_Drill();
		GC_Drill(const GC_Drill& other) = delete;
		GC_Drill( double tip_angle );
		GC_Drill( double tip_angle, double rad, double len );

		virtual ~GC_Drill();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual double GetTipAngle() const;
		virtual void SetTipAngle(double angle);

		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual bool SupportOptions() const { return false; }

		virtual double GetRadAtVal( double depth ) const;

		virtual gc_teToolTypes GetType() const { return type; }
	};

	class GCTOOLS_API GC_SpotDrill : public GC_Drill
	{
	public:
		static const gc_teToolTypes type = gc_eSpotDrillMT;

		GC_SpotDrill();
		GC_SpotDrill( const GC_SpotDrill& other );

		virtual ~GC_SpotDrill();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual bool SupportOptions() const { return false; }

		virtual gc_teToolTypes GetType() const { return type; }
	};

	//Center drill taper is PART of the tool
	//part of the CUTTING part of the tool, even though it is
	//not shown like that in the 10.5 and prior dialogs
	//Dimensions are as follows
	//pilot length: tip to where tool begins to taper ( or would if one exists )
	//pilot rad: 
	//shoulder taper: taper angle of the shoulder
	//shoulder rad:
	//flute length: calculated value as it will include the length to the top of the taper
	//flute rad: pilot radius
	//tool rad: shoulder radius
	class GCTOOLS_API GC_CenterDrill : public GC_Drill
	{
	protected:
		struct CDrill;
		CDrill* p_cdrill;

		double GetTipLen( bool bAsPartUnits = false ) const;

	public:
		static const gc_teToolTypes type = gc_eCenterDrillMT;

		GC_CenterDrill();
		GC_CenterDrill(const GC_CenterDrill& other) = delete;

		virtual ~GC_CenterDrill();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual double GetPilotRad(bool bAsPartUnits = false) const;
		virtual void SetPilotRad(double rad);
		
		virtual double GetPilotLen(bool bAsPartUnits = false) const;
		virtual void SetPilotLen(double len);
		
		virtual double GetShoulderRad(bool bAsPartUnits = false) const;
		virtual void SetShoulderRad(double rad);

		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );
		
		virtual double GetFluteLen(bool bAsPartUnits = false) const; //this is calculated: defined to be from tip of the tool to top of the taper
		virtual void SetFluteLen( double len );	//this will change the pilot length
		
		virtual void ChangeShankType( gc_teShankType eNewType )	{} //not allowed
		
		virtual double GetRad(bool bAsPartUnits = false) const;
		virtual void SetRad( double rad );
		
		virtual double GetDraftAngle() const;
		virtual void SetDraftAngle( double angle );

		virtual double GetRadAtVal( double depth ) const;
		
		virtual bool SupportOptions() const { return false; }

		virtual gc_teToolTypes GetType() const { return type; }

		virtual void GetTileString( char* val ) const;

		virtual bool SyncShankNFluteRad() const { return false; }
	};

	class GCTOOLS_API GC_Tap : public GC_Drill
	{
	public:
		static const gc_teToolTypes type = gc_eTapMT;

	protected:
		struct Tap;
		Tap* p_tap;

	public:
		GC_Tap();
		GC_Tap(const GC_Tap& other) = delete;

		virtual ~GC_Tap();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );

		virtual void SetPitch( double pitch );
		virtual double GetPitch() const;

		virtual void SetTPI( double tpi );
		virtual double GetTPI() const;

		virtual double GetNonCuttingLen(bool bAsPartUnits = false) const;
		virtual void SetNonCuttingLen( double len );

		virtual gc_teToolTypes GetType() const { return type; }

	};

	class GCTOOLS_API GC_RigidTap : public GC_Tap
	{
	public:
		static const gc_teToolTypes type = gc_eRigidTapMT;

	public:
		GC_RigidTap();
		virtual ~GC_RigidTap();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void PreserveData( const GC_GibbsTool* ptr );

		virtual gc_teToolTypes GetType() const { return type; }

	};

	class GCTOOLS_API GC_RoundOver : public GC_MillTool
	{
	public:
		static const gc_teToolTypes type = gc_eRoundOverMT;

	protected:
		struct RoundOver;
		RoundOver* p_ro;

	public:
		GC_RoundOver();
		GC_RoundOver(const GC_RoundOver& other) = delete;
		virtual ~GC_RoundOver();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual bool SupportOptions() const { return false; }

		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );
		
		virtual double GetFluteRad(bool bAsPartUnits = false) const;
		virtual double GetFluteLen(bool bAsPartUnits = false) const;

		//calculated value - effectively does nothing
		virtual void SetFluteRad(double rad);
		
		//this calls SetTipToCornerRadLen
		virtual void SetFluteLen( double len);
		
		virtual double GetInnerCornerRad(bool bAsPartUnits = false) const;
		virtual void SetInnerCornerRad(double rad);
		
		virtual double GetLen(bool bAsPartUnits = false) const;
		virtual void SetLen( double len);

		virtual double GetTipToCornerRadLen(bool bAsPartUnits = false) const;
		virtual void SetTipToCornerRadLen( double len );

		virtual double GetPilotRad(bool bAsPartUnits = false) const;
		virtual void SetPilotRad( double rad );
		
		virtual void SetBodyLen( double len );
		virtual double GetBodyLen(bool bAsPartUnits = false) const;

		virtual void SetBodyRad(double rad);
		virtual double GetBodyRad(bool bAsPartUnits = false) const;

		virtual double GetTopCornerRad(bool bAsPartUnits = false ) const;

		virtual gc_teToolTypes GetType() const { return type; }
		virtual bool SyncShankNFluteRad() const { return false; }
		virtual void CreateShankProfile( void*path );

		virtual void GetTileString( char* val ) const;
	};

	//for newly defined lollipop tools assume that the flute length IS the diameter. No mushroom tools
	class GCTOOLS_API GC_Lollipop : public GC_MillTool
	{
	public:
		static const gc_teToolTypes type = gc_eLolliMT;

	protected:

	public:
		GC_Lollipop();
		GC_Lollipop( double rad, double neck_len, double nec_rad, double shank_rad, double tool_len );
		virtual ~GC_Lollipop();
		GC_Lollipop(const GC_Lollipop& other) = delete;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual bool SupportOptions() const { return true; }
		
		virtual double GetFluteLen(bool bAsPartUnits = false) const;
		virtual void SetFluteLen( double len );
		
		virtual void SetRad(double rad);
		virtual double GetRad(bool bAsPartUnits = false) const;
		virtual void SetFluteRad(double rad);
		virtual void SetOptions( bool bEnabled );
		virtual double GetCornerRad(bool bAsPartUnits = false) const;

		virtual bool SyncShankNFluteRad() const { return false; }
		virtual gc_teToolTypes GetType() const { return type; }
	};

	class GCTOOLS_API GC_ShellMill :  public GC_EndMill
	{
	public:
		static const gc_teToolTypes type = gc_eShellMT;

	public:
		GC_ShellMill();
		GC_ShellMill(double rad, double len, double shank_rad, double tool_len, double btm_crn_rad );
		virtual ~GC_ShellMill();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void CreateProfile( void* path );
		virtual bool SupportOptions() const { return true; }

		virtual gc_teToolTypes GetType() const { return type; }

		virtual bool SyncShankNFluteRad() const {return false;}
	};


	class GCTOOLS_API GC_FaceMill :  public GC_EndMill
	{
	protected:
		struct FaceMill;
		FaceMill* p_facemill;
	public:
		static const gc_teToolTypes type = gc_eFaceMT;

	public:
		GC_FaceMill();
		GC_FaceMill(const GC_FaceMill& other) = delete;
		GC_FaceMill(double rad, double len, double shank_rad, double tool_len, double btm_crn_rad );
		virtual ~GC_FaceMill();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void CreateProfile( void* path );
		virtual bool SupportOptions() const { return true; }

		virtual void SetLeadAngle( double angle );
		virtual double GetLeadAngle() const;

		virtual double GetNoseRad( bool bAsPartUnits = false ) const;
		virtual void SetNoseRad( double rad );

		virtual void SetHeadRad( double rad );							//head rad
		virtual double GetHeadRad( bool bAsPartUnits = false ) const;	//head rad

		virtual void SetRad( double rad );							//head rad
		virtual double GetRad( bool bAsPartUnits = false ) const;	//head rad

		virtual void SetFluteLen( double len );
		virtual void SetCornerRad(double btm_corner_rad);

		virtual double GetTipRad(bool bAsPartUnits = false) const;	//nose rad
		virtual void SetTipRad( double rad );						//nose rad

		virtual void SetHeadLen( double len ) const;
		virtual double GetHeadLen( bool bAsPartUnits = false ) const;
		
		virtual gc_teToolTypes GetType() const { return type; }
		virtual bool SyncShankNFluteRad() const {return false;}

		virtual void PreserveData( const GC_GibbsTool* ptr );

		virtual double GetRadAtVal( double depth ) const;
	};

	class GCTOOLS_API GC_FlyCutter :  public GC_EndMill
	{
	public:
		static const gc_teToolTypes type = gc_eFlyCutMT;

	public:
		GC_FlyCutter();
		GC_FlyCutter(double rad, double len, double shank_rad, double tool_len, double btm_crn_rad );
		virtual ~GC_FlyCutter();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void CreateProfile( void* path );
		virtual bool SupportOptions() const { return true; }

		virtual gc_teToolTypes GetType() const { return type; }
		virtual bool SyncShankNFluteRad() const {return false;}
	};

	class GCTOOLS_API GC_KeyCutter :  public GC_EndMill
	{
	public:
		static const gc_teToolTypes type = gc_eKeyCutMT;

	protected:
		struct KeyCutter;
		KeyCutter* p_kc;

	public:
		GC_KeyCutter();
		GC_KeyCutter(double rad, double len, double shank_rad, double tool_len, double btm_crn_rad, double top_corner_rad );
		GC_KeyCutter(const GC_KeyCutter& other) = delete;
		virtual ~GC_KeyCutter();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void CreateProfile( void* path );
		virtual bool SupportOptions() const { return true; }
		virtual double GetTopCornerRad(bool bAsPartUnits = false) const;
		virtual void SetTopCornerRad(double rad);

		virtual gc_teToolTypes GetType() const { return type; }
		virtual bool SyncShankNFluteRad() const {return false;}
	};

	class GCTOOLS_API GC_Mill2DForm : public GC_MillTool
	{
	protected:
		struct Mill2DForm;
		Mill2DForm* p_form;
	public:
		static const gc_teToolTypes type = gc_e2DFormMT;
	public:
		GC_Mill2DForm( double nominal_radius );
		GC_Mill2DForm();
		GC_Mill2DForm(const GC_Mill2DForm& other) = delete;
		virtual ~GC_Mill2DForm();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual bool SupportOptions() const {return false;}

		virtual double GetRad(bool bAsPartUnits = false) const;		//nominal rad - this is now used for machining 
		virtual void SetRad( double rad );	//nominal rad - this is now used for machining 

		virtual double GetMaxRad(bool bAsPartUnits = false) const;	//calculated boundary
		virtual void SetMaxRad(double rad);						//calculated boundary

		virtual gc_teToolTypes GetType() const { return type; }
		virtual double GetShankRad(bool bAsPartUnits = false) const;

		virtual void SetShankType(gc_teShankType type);
	};

	class GCTOOLS_API GC_Reamer : public GC_MillTool
	{
	public:
		static const gc_teToolTypes type = gc_eReamerMT;

	protected:
		struct Reamer;
		Reamer* p_reamer;

	public:
		GC_Reamer();
		GC_Reamer(const GC_Reamer& other) = delete;
		GC_Reamer( double rad, double len, double non_cutting_len, double non_cutting_rad, double shank_rad, double tool_len );
		virtual ~GC_Reamer();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual double GetNonCuttingLen(bool bAsPartUnits = false) const;
		virtual void SetNonCuttingLen(double len);

		virtual double GetNonCuttingRad(bool bAsPartUnits = false) const;
		virtual void SetNonCuttingRad(double rad);
	
		virtual bool SupportOptions() const { return true; }
		virtual void CreateProfile( void* path );

		virtual gc_teToolTypes GetType() const { return type; }
	};

	class GCTOOLS_API GC_CounterSink : public GC_Drill
	{
	public:
		static const gc_teToolTypes type = gc_eCounterSinkMT;

	protected:
		struct CounterSink;
		CounterSink* p_cs;

	public:
		GC_CounterSink();
		GC_CounterSink(const GC_CounterSink& other) = delete;
		GC_CounterSink( double flute_rad, double taper_len, double taper_angle, double flute_len, double tool_len, double shank_rad );
		virtual ~GC_CounterSink();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void PreserveData( const GC_GibbsTool* ptr );

		virtual void SetTipAngle( double angle );
		virtual double GetTipAngle() const;

		virtual void SetTipRad( double rad );
		virtual double GetTipRad(bool bAsPartUnits = false) const;

		virtual void SetTaperLen( double len );
		virtual double GetTaperLen(bool bAsPartUnits = false) const;

		virtual bool SupportOptions() const { return false; }
		virtual void CreateProfile( void* path );

		virtual gc_teToolTypes GetType() const { return type; }
		virtual bool SyncShankNFluteRad() const {return false;}

		virtual void SetRad(double rad);
	};

	class GCTOOLS_API GC_ConvexTipMill : public GC_EndMill
	{
	public:
		static const gc_teToolTypes type = gc_eConvexTipMT;

	protected:
		struct ConvexTip;
		ConvexTip* p_ct;

	public:
		GC_ConvexTipMill();
		GC_ConvexTipMill(const GC_ConvexTipMill& other) = delete;
		virtual ~GC_ConvexTipMill();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual double GetFlatRad(bool bAsPartUnits = false) const;
		virtual void SetFlatRad( double rad );

		virtual double GetCornerRad(bool bAsPartUnits = false) const;
		virtual void SetCornerRad(double rad);

		virtual double GetConvexRad(bool bAsPartUnits = false) const;
		virtual void SetConvexRad( double rad);

		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );

		virtual bool SupportOptions() const {return true;}
		virtual gc_teToolTypes GetType() const {return type;}
	};

	class GCTOOLS_API GC_BarrelMill : public GC_MillTool
	{
	public:
		static const gc_teToolTypes type = gc_eBarrelMT;

	protected:
		struct Barrel;
		Barrel* p_barrel;

	public:
		GC_BarrelMill();
		GC_BarrelMill(const GC_BarrelMill& other) = delete;
		virtual ~GC_BarrelMill();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual double GetProfileRad(bool bAsPartUnits = false) const;
		virtual void SetProfileRad( double rad );
		
		//these are the exact same fields - setting one sets both
		virtual double GetCornerRad(bool bAsPartUnits = false) const;
		virtual void SetCornerRad( double rad );
		virtual double GetTopCornerRad(bool bAsPartUnits = false) const;
		virtual void SetTopCornerRad( double rad );

		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );

		virtual bool SupportOptions() const {return false;}
		virtual bool SyncShankNFluteRad() const {return false;}

		virtual gc_teToolTypes GetType() const { return type;}

	};

	class GCTOOLS_API GC_DoveTailMill : public GC_MillTool
	{
	public:
		static const gc_teToolTypes type = gc_eDoveTailMT;

	protected:
		struct DoveTail;
		DoveTail* p_dt;

	public:
		GC_DoveTailMill();
		GC_DoveTailMill(const GC_DoveTailMill& other) = delete;
		virtual ~GC_DoveTailMill();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual double GetCornerRad(bool bAsPartUnits = false) const;
		virtual void SetCornerRad(double rad);
		virtual double GetTopCornerRad(bool bAsPartUnits = false) const;

		virtual double GetDraftAngle() const;
		virtual void SetDraftAngle( double angle );

		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual gc_teToolTypes GetType() const { return type; }

		virtual bool SupportOptions() const {return false;}
		virtual bool SyncShankNFluteRad() const {return false;}
	};

	class GCTOOLS_API GC_Mill3DForm : public GC_MillTool
	{
	public:
		static const gc_teToolTypes type = gc_e3DFormMT;
	protected:
		struct Mill3DForm;
		Mill3DForm* p_form;
	public:
		GC_Mill3DForm();
		GC_Mill3DForm(long sol_ref);
		GC_Mill3DForm(const GC_Mill3DForm& other) = delete;
		virtual ~GC_Mill3DForm();

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual void CreateProfile( void* path );
		virtual void PreserveData( const GC_GibbsTool* ptr );

		virtual gc_teToolTypes GetType() const { return type; }

		virtual void SetRad(double rad);				//nominal rad
		virtual double GetRad(bool bAsPartUnits = false) const;	//nominal rad

		virtual void SetMaxRad(double rad);				//calculated boundary
		virtual double GetMaxRad(bool bAsPartUnits = false) const;	//calculated boundary

		virtual long GetSolidRef() const;

		virtual void SetShankType(gc_teShankType type);

	};
}
