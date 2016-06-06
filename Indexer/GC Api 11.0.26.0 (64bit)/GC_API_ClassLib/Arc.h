#pragma once

#include "Geom.h"
#include "MathUtils.h"

#pragma pack (push, arc_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class Arc : public virtual  Geom
{
	public:
		virtual Arc *clone() const			= 0;
		virtual double length() const;

		virtual Pt3d cp() const				= 0;
		virtual Pt3d axis() const			= 0;
		virtual double radius() const		= 0;
		virtual double angle() const		= 0;
		virtual double dstep() const		= 0;

		bool helix(double tol = part_accy) const
		{
			return fabs(dstep()) > tol;
		}
};

}	// end namespace GCApi

#pragma pack (pop, arc_align)						// restore struct alignment
