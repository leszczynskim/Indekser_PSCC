#pragma once

#include "Arc.h"
#include "Feat.h"

#pragma pack (push, circle_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

enum dir_type
{
	cw, ccw
};

inline dir_type ToggleDir(dir_type dir)
{
	return (dir == ccw) ? cw : ccw;
}

inline bool CW(dir_type dir)
{
	return dir == cw;
}

inline bool CCW(dir_type dir)
{
	return dir == ccw;
}

struct Circle_POD
{
	Pt3d sp, ep;
	Pt3d cp;
	double rad;
	dir_type dir;
};

class Circle : public Arc
{
	public:
		Circle()						{}
		Circle(const Circle_POD &arc);

		// FeatData interface...
		virtual Circle *clone() const				{ return new Circle(*this); }
		virtual void from_feat(const Feat &feat);
		virtual void to_feat(Feat &feat) const;
		virtual void write_bin(std::ostream &stream) const;
		virtual void read_bin(std::istream &stream);
		virtual void write_txt(std::ostream &stream) const;
		virtual void read_txt(std::istream &stream);
		
		// Geom interface...
		virtual bool valid() const;
		virtual Pt3d sp() const						{ return _def.sp; }
		virtual Pt3d ep() const						{ return _def.ep; }
		virtual Pt3d eval(double t) const;
		virtual Pt3d tangent(double t) const;
		virtual double param(const Pt3d &p) const;
		virtual void transform(const Matrix &m);
		virtual void reverse();
		virtual bool trim(double t, const Pt3d *p, bool bUpperBound);
		virtual void set_sp(const Pt3d &p);
		virtual void set_ep(const Pt3d &p);

		// Arc interface...
		virtual Pt3d cp() const						{ return _def.cp; }
		virtual Pt3d axis() const;
		virtual double radius() const				{ return _def.rad; }
		virtual double angle() const;
		virtual double dstep() const				{ return _def.ep[d_axis] - _def.sp[d_axis]; }

	protected:
		Circle_POD _def;
		
		mutable Pt3d cache_axis;
		mutable double cache_angle;

		enum
		{
			ARC2D_MASK_AXIS		= (1 << 0),
			ARC2D_MASK_ANGLE	= (1 << 1)
		};
};

class ArcThread : public Circle
{
	public:
		ArcThread()									{}
		ArcThread(const Circle_POD &arc)			: Circle(arc) {}

		virtual void to_feat(Feat &feat) const;
};

} // end namespace GCApi

#pragma pack (pop, circle_align)						// restore struct alignment
