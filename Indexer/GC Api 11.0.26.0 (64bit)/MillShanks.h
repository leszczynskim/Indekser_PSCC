#pragma once

#include "GCTools.h"
#include "ToolDeclarations.h"

#pragma pack (push, mill_shank_align, 8)							// 8 byte alignment for following types


namespace GCTools
{
	enum gc_teShankType
	{
		gc_eStraightShank,
		gc_eTaperShank,
		gc_eStepShank,
		gc_UndefinedShank = -99
	};

	class GC_MillShank
	{
	private:
		struct MillShank;
		MillShank* p_mill_shank;
	protected:
		double ScaleValue( double val, bool bAsPartUnits ) const;

		gc_teToolUnits GetUnits() const;
		void ChangedData();

	public:
		GC_MillShank();
		GC_MillShank( double rad );
		GC_MillShank( double rad, gc_teToolUnits units );
		
		GC_MillShank(const GC_MillShank& other) = delete;

		virtual ~GC_MillShank();

		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version);

		//no need to call this directly, this will be used by the MillTool class
		void SetUnits( gc_teToolUnits eUnits );

		virtual double GetRad(bool bAsPartUnits = false) const;
		virtual void SetRad( double rad );
		virtual void CreateProfile( void* path, double overall_length ) const;

		virtual gc_teShankType GetType() const { return gc_eStraightShank; }

		virtual void PreserveData( const GC_MillShank* ptr );


	};

	class GC_MillAdvShank : public GC_MillShank
	{
	protected:
		struct AdvMillShank;
		AdvMillShank* p_advshank;

		GC_MillAdvShank();
		GC_MillAdvShank( double top_rad, double btm_rad, double neck_len );

	public:

		virtual ~GC_MillAdvShank();

 		template<typename Archive>
 		void serialize(Archive& ar, const unsigned int version);

		virtual void PreserveData( const GC_MillShank* ptr );

		virtual double GetTopRad(bool bAsPartUnits = false) const;
		virtual void SetTopRad(double rad);

		virtual double GetNeckLen(bool bAsPartUnits = false) const;		//only neck length portion of entire shank length
		virtual void SetNeckLen( double len );	//only neck length portion of entire shank length

		virtual double GetNeckRad(bool bAsPartUnits = false) const;
		virtual void SetNeckRad( double rad );

	};

	class GC_StraightShank : public GC_MillShank
	{
	public:
		static const gc_teShankType type = gc_eStraightShank;

	public:
		GC_StraightShank();
		GC_StraightShank( double rad );
		virtual ~GC_StraightShank();
		
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual gc_teShankType GetType() const { return type; }
		virtual void PreserveData( const GC_MillShank* ptr );
	};

	class GC_TaperedShank : public GC_MillAdvShank
	{
	public:
		static const gc_teShankType type = gc_eTaperShank;

	protected:
		struct TaperedShank;
		TaperedShank* p_taper;

	public:
		GC_TaperedShank( double taper, double neck_rad, double neck_len, double top_rad );
		GC_TaperedShank();
		virtual ~GC_TaperedShank();

		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual gc_teShankType GetType() const { return type; }
		virtual void PreserveData( const GC_MillShank* ptr );
		
		virtual double GetTaperAngle() const;
		virtual void SetTaperAngle(double taper);

		virtual void SetTaperLen(double len);
		virtual double GetTaperLen(bool bAsPartUnits = false) const;

		virtual void CreateProfile( void* path, double overall_length ) const;
	};

	class GC_SteppedShank : public GC_MillAdvShank
	{
	public:
		static const gc_teShankType type = gc_eStepShank;

	public:
		GC_SteppedShank();
		GC_SteppedShank( double neck_rad, double neck_len, double shank_rad );
		virtual ~GC_SteppedShank();

		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual gc_teShankType GetType() const { return type; }

		virtual void PreserveData( const GC_MillShank* ptr );

		virtual void CreateProfile( void* path, double overall_length ) const;
	};
}


#pragma pack (pop, mill_shank_align)
