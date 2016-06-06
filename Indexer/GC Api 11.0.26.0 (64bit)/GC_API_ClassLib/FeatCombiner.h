#pragma once

#include "Path.h"
#include "boost/utility.hpp"

#pragma pack (push, combiner_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

//--------------------------- FeatCombiner -----------------------

class FeatCombiner : boost::noncopyable
{
	private:
		gc_FeatCombiner *comb_;
		
	public:
		FeatCombiner(Path &path, const gc_CombineFeatParams &params = gc_CombineFeatParams())
		{
			API_VERIFY(gc_CombinerCreate(path.ptr(), params, &comb_));
		}
	
		~FeatCombiner()
		{
			API_VERIFY(gc_CombinerDelete(comb_));
		}

		void write(const Feat &feat)
		{
			API_VERIFY(gc_CombinerAddFeat(comb_, feat.ptr()));
		}
		
		bool empty() const
		{
			int bEmpty = true;
			API_VERIFY(gc_CombinerEmpty(comb_, &bEmpty));
			return (bEmpty != false);
		}
		
		void flush()
		{
			API_VERIFY(gc_CombinerFlush(comb_));
		}
};

}	// end namespace GCApi

#pragma pack (pop, combiner_align)						// restore struct alignment
