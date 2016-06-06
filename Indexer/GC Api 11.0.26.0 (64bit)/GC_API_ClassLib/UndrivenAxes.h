#pragma once

#include "Asserts.h"

#pragma pack (push, axes_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

//--------------------------- UnDrivenAxes -----------------------

struct UnDrivenAxes
{
	bool lin[3];
	bool rot[3];
	
	UnDrivenAxes()
	{
		std::fill_n(lin, 3, false);
		std::fill_n(rot, 3, false);
	}
};

inline bool Any(const UnDrivenAxes &axes)
{
	for (int i=0; i<3; ++i)
		if (axes.lin[i] || axes.rot[i])
			return true;
	return false;
}

//-----------------------------------------------------
// text archive functions for UnDrivenAxes...
std::ostream & operator << (std::ostream &stream, const UnDrivenAxes &axes);
std::istream & operator >> (std::istream &stream, UnDrivenAxes &axes);

}	// end namespace GCApi

#pragma pack (pop, axes_align)						// restore struct alignment
