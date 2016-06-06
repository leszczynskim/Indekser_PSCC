#pragma once

#include "GCTools.h"
#include "ToolDeclarations.h"

#pragma pack (push, mill_options_align, 8)							// 8 byte alignment for following types

namespace GCTools
{
	enum gc_teOptionsType
	{
		gc_BaseMillOptions,	//contains no real data just units definition
		gc_eTaperOpts,
		gc_eNonCuttingOpts,
		gc_eTopCornerRadOpts,
		gc_eLollipopOpts,
		gc_eTCRNDraftOpts,
		gc_eCustomOpts = 99,
		gc_eUndefinedOpts = -1,
	};

	class GCTOOLS_API GC_MillOptions
	{
	public:
		static const gc_teOptionsType type = gc_BaseMillOptions;

	protected:
		struct MillOptions;
		MillOptions* p_options;

		gc_teToolUnits GetUnits() const;

	public:
		GC_MillOptions();
		GC_MillOptions(const GC_MillOptions& other) = delete;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		virtual ~GC_MillOptions();

		virtual void PreserveData( const GC_MillOptions* ptr );

		//no need to call this directly, this will be used by the MillTool class
		void SetUnits( gc_teToolUnits eUnits );

		double ScaleValue( double val, bool bAsPartUnits ) const;

		virtual gc_teOptionsType GetType() const {return type;}

	};

	class GCTOOLS_API GC_LollipopOpts : public GC_MillOptions
	{
	public:
		static const gc_teOptionsType type = gc_eLollipopOpts;

	protected:
		struct LolliOpts;
		LolliOpts* p_lolli;

	public:
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		GC_LollipopOpts();
		GC_LollipopOpts(double top_rad);
		GC_LollipopOpts(const GC_LollipopOpts& other) = delete;

		virtual ~GC_LollipopOpts();
		virtual void PreserveData( const GC_MillOptions* ptr );

		virtual void SetLen( double len );
		virtual double GetLen( bool bAsPartUnits = false ) const;
		virtual gc_teOptionsType GetType() const {return type;}

	};

	class GCTOOLS_API GC_TaperMillOptions : public GC_MillOptions
	{
	public:
		static const gc_teOptionsType type = gc_eTaperOpts;

	protected:
		struct TaperMillOptions;
		TaperMillOptions* ptr_taper;

	public:
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		GC_TaperMillOptions(const GC_TaperMillOptions& other) = delete;
		GC_TaperMillOptions();
		GC_TaperMillOptions( double dTaper );

		virtual ~GC_TaperMillOptions();

		virtual double GetTaperAngle() const;
		virtual void SetTaperAngle( double ang );

		virtual void PreserveData( const GC_MillOptions* ptr );
		virtual gc_teOptionsType GetType() const {return type;}
	};

	class GCTOOLS_API GC_TCRNDraftOptions : public GC_TaperMillOptions
	{
	public:
		static const gc_teOptionsType type = gc_eTCRNDraftOpts;

	protected:
		struct TaperNCornerRadOpts;
		TaperNCornerRadOpts* ptr_tapernrad;

	public:
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		GC_TCRNDraftOptions(const GC_TCRNDraftOptions& other) = delete;
		GC_TCRNDraftOptions();
		GC_TCRNDraftOptions( double taper, double top_rad );

		virtual ~GC_TCRNDraftOptions();

		virtual double GetTaperAngle() const;
		virtual void SetTaperAngle( double ang );
		
		virtual double GetTopCornerRad(bool bAsPartUnits = false) const;
		virtual void SetTopCornerRad(double rad );

		virtual void PreserveData( const GC_MillOptions* ptr );
		virtual gc_teOptionsType GetType() const {return type;}
	};

	class GCTOOLS_API GC_NonCuttionOptions : public GC_TaperMillOptions
	{
	public:
		static const gc_teOptionsType type = gc_eNonCuttingOpts;

	private:
		struct NonCuttingOptions;
		NonCuttingOptions* nc_options;

	public:
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		GC_NonCuttionOptions();
		GC_NonCuttionOptions(const GC_NonCuttionOptions& other);

		virtual double GetNonCuttingRad(bool bAsPartUnits = false) const;
		virtual void SetNonCuttingRad( double rad );

		virtual void PreserveData( const GC_MillOptions* ptr );
		virtual gc_teOptionsType GetType() const {return type;}
	};

	class GCTOOLS_API GC_TopCornerOptions : public GC_NonCuttionOptions
	{
	public:
		static const gc_teOptionsType type = gc_eTopCornerRadOpts;

	private:
		struct TopCornerOptions;
		TopCornerOptions* tcr_options;

	public:
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		GC_TopCornerOptions();

		double GetTopCornerRad(bool bAsPartUnits = false) const;
		void SetTopCornerRad( double rad );

		virtual void PreserveData( const GC_MillOptions* ptr );
		virtual gc_teOptionsType GetType() const {return type;}
	};
}



#pragma pack (pop, mill_options_align)
