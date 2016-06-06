#pragma once

#include "FeatData.h"

#pragma pack (push, geom_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class Geom : public FeatData
{
	public:
		virtual bool valid() const						{ return true; }
		virtual Pt3d sp() const							= 0;
		virtual Pt3d ep() const							= 0;
		virtual double length() const					= 0;
		virtual Pt3d eval(double t) const				= 0;
		virtual Pt3d tangent(double t) const			= 0;
		virtual double param(const Pt3d &p) const		= 0;
		virtual void transform(const Matrix &m)			= 0;
		virtual void reverse()							= 0;
		virtual bool trim(double t, const Pt3d *p, bool bUpperBound) = 0;
		virtual void set_sp(const Pt3d &p)				= 0; // for fine adjustment of sp
		virtual void set_ep(const Pt3d &p)				= 0; // for fine adjustment of ep
		virtual Pt3d tl_norm(double t) const			{ return Pt3d(0.0, 0.0, 1.0); }
		
	protected:
		mutable int whats_cached;
		
		inline bool test_cache(int mask) const
		{
			if ((whats_cached & mask) != 0)
				return true;
			whats_cached |= mask;
			return false;
		}
		
		inline void clear_cache(int mask = - 1) const
		{
			whats_cached &= ~mask;
		}
};

}	// end namespace GCApi

#pragma pack (pop, geom_align)						// restore struct alignment
