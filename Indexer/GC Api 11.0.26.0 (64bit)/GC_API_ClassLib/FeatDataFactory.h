#pragma once

#include "FeatData.h"
#include <boost/utility.hpp>
#include <boost/function.hpp>

#pragma pack (push, factory_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class FeatDataFactory : boost::noncopyable
{
	public:
		typedef boost::function <FeatDataPtr ()> CreateFunctor;

		struct FeatType
		{
			teGeoType type;
			int sub_type;			// for CTool sub-types

			FeatType()											: type(eGeoAll), sub_type(0) {}
			FeatType(teGeoType the_type, int the_sub_type = 0)	: type(the_type), sub_type(the_sub_type) {}
		};
		
		static FeatDataFactory &instance();
		
		bool register_feat(FeatType type, const char *name, const CreateFunctor &callback);
		const char *find_name(FeatType type) const;
		const CreateFunctor *find_callback(FeatType type) const;
		
		FeatDataPtr create(FeatType type) const;
		FeatDataPtr create(const char *name) const;
		FeatDataPtr create(const Feat &feat) const;
		
		void clear();		// for eliminating pesky "leak" reports
		
	protected:
		FeatDataFactory();
		
	private:
		struct impl;
		impl *pimpl;
};

}	// end namespace GCApi

#pragma pack (pop, factory_align)						// restore struct alignment
