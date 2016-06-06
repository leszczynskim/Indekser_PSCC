#pragma once

#pragma pack (push, gibbs_tool_h, 8)							// 8 byte alignment for following types
#include <string>

//#include <boost/serialization/export.hpp>
#include "GCTools.h"
#include "ToolDeclarations.h"

namespace GCTools
{
	class GCTOOLS_API GC_GibbsTool
	{
	private:
		struct GibbsTool;
		GibbsTool* p_gibbsTool;
	public:
		static const char* custom_name;
		static gc_teToolTypes type;
	
	protected:

		GC_GibbsTool();
		GC_GibbsTool(const GC_GibbsTool& other) = delete;

		long GetBaseOffset() const;
	
	public:
		virtual ~GC_GibbsTool();

 		template<class Archive>
 		void serialize(Archive& ar, const unsigned int version);

		int GetCellIndex() const;
		void SetCellIndex(int ix);

		gc_teToolMaterial GetMaterial() const;	//TODO API Tool Material - also need ability to add new tool materials...
		void SetMaterial( gc_teToolMaterial eMaterial );	//TODO API Tool Material - also need ability to add new tool materials...

		long GetTG() const;
		void SetTG( long toolgroup );
		void SetLenOffset( long len_offset );
		long GetLenOffset( ) const;

		bool UseID() const;
		void SetUseID( bool use );

		long GetID() const;
		void SetID( long id );

		long GetTGPos() const;
		void SetTGPos( long tg_pos );

		bool GetUseSubPos() const;
		void SetUseSubPos(bool bUse);

		double GetSubPos() const;
		void SetSubPos( double pos );
		
		long GetAttIndex() const;
		void SetAttIndex(long att_index);

		void *AddAttList();
		void *GetAttList() const;
		bool DeleteAttList();

		void SetCustomHolderType( gc_teToolHolderType eType );
		gc_teToolHolderType GetCustomHolderType() const;

		void SetCustomHolderDim( double* holder_hv_in );
		void GetCustomHolderDims(double* holder_hv_out, bool bAsPartUnits = false) const;

		int GetCustomHolderAutomatic() const;
		void SetCustomHolderAutomatic(int val);

		void SetCustomHolderSolidRef( int iRef );
		int GetCustomHolderSolidRef() const;

		void SetCustomHolderOffset( double offset );
		double GetCustomHolderOffset( bool bAsPartUnits = false ) const;

		void SetCustomHolderComment( const wchar_t* comment );
		const wchar_t* GetCustomHolderComment() const;

		const wchar_t* GetComment() const;
		void SetComment( const wchar_t* tool_comment );

		const wchar_t* GetITCSName() const;
		void SetITCSName( const wchar_t* cs_name );

		void ChangedData() const;

		virtual void SetPresetPt(const double* preset_pt_in);
		virtual void GetPresetPt(double* preset_pt_out) const;

		virtual void SetUsePresetAsFull(bool full_offset);
		virtual bool UsePresetAsFull() const;

		virtual void SetTCShift(const double* turret_shift_in);
		virtual void GetTCShift(double* turret_shift_out, bool bAsPartUnits = false) const;

		virtual gc_teToolUnits GetUnits() const;
		virtual void SetUnits( gc_teToolUnits units );
		
		virtual void PreserveData( const GC_GibbsTool* ptr );
		virtual std::string GetCustomName( void ) const;
		
		virtual void CreateProfile( void* path ) = 0;

		virtual double GetHolderID() const;
		virtual void SetHolderID( double id );

		virtual bool HasIT() const;

		int GetCell() const;	//returns the cell number (aka: tool number) of the tool in the tool tile list

		virtual gc_teToolTypes GetType() const = 0;

		virtual double GetStickOutLen( bool bAsPartUnits = false ) const = 0;
		virtual void SetStickOutLen( double len ) = 0;

		virtual void GetTileString( char* val ) const;	//value to be shown on a tool tile. This will be truncated if too long
		
		virtual const char* GetPostTypeString() const;
		virtual const char* GetTypeString() const;

		double ScaleValue( double val, bool bAsPartUnits ) const;

		long GetRawLenOffset() const;

	};

	GCTOOLS_API bool IsCustomTool( GC_GibbsTool* ptr );
	GCTOOLS_API gc_teToolClass GetToolClass( const GC_GibbsTool* ptr );
	GCTOOLS_API gc_teToolClass GetToolClass( int iCell );
	GCTOOLS_API gc_teToolClass GetToolClass( gc_teToolTypes eType );

	GCTOOLS_API gc_teToolUnits GetPartUnits();
	GCTOOLS_API double ConvertUnits(double val, gc_teToolUnits from_units, gc_teToolUnits to_units);
}

#pragma pack (pop, gibbs_tool_h)
