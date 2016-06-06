#pragma once
#pragma pack (push, boost_align, 8)	
#ifdef INSIDE_VIRTUAL

#define GCTOOLS_API __declspec(dllexport)
#else

#define GCTOOLS_API __declspec(dllimport)
#endif
#pragma pack(pop, boost_align)