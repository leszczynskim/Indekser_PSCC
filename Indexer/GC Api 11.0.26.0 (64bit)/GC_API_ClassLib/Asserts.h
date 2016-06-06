#pragma once

#include <cassert>

namespace GCApi
{

#define MY_ASSERT(exp)			assert(exp)

#ifdef NDEBUG
#define MY_VERIFY(exp)			(exp)
#else
#define MY_VERIFY(exp)			MY_ASSERT(exp)
#endif

#define API_VERIFY(gc_call)		MY_VERIFY((gc_call) == 0)

}	// end namespace GCApi
