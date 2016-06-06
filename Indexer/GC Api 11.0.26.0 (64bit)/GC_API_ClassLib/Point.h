#pragma once

#include "Geom.h"

#pragma pack (push, point_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class Point : public Geom
{
	public:
		Point()										{}
		Point(const Pt3d &p)						: _p(p) {}
		
		// FeatData interface...
		virtual Point *clone() const				{ return new Point(*this); }
		virtual void from_feat(const Feat &feat);
		virtual void to_feat(Feat &feat) const;
		virtual void write_bin(std::ostream &stream) const;
		virtual void read_bin(std::istream &stream);
		virtual void write_txt(std::ostream &stream) const;
		virtual void read_txt(std::istream &stream);

		// Geom interface...
		virtual Pt3d sp() const						{ return _p; }
		virtual Pt3d ep() const						{ return _p; }
		virtual double length() const				{ return 0.0; }
		virtual Pt3d eval(double t) const			{ return _p; }
		virtual Pt3d tangent(double t) const		{ return Pt3d(); }
		virtual double param(const Pt3d &p) const	{ return 0.0; }
		virtual void transform(const Matrix &m)		{ TransformPos(_p, m); }
		virtual void reverse()						{}
		virtual bool trim(double t, const Pt3d *p, bool bUpperBound);
		virtual void set_sp(const Pt3d &p)			{ _p = p; }
		virtual void set_ep(const Pt3d &p)			{ _p = p; }
		
	private:
		Pt3d _p;
};

}	// end namespace GCApi

#pragma pack (pop, point_align)						// restore struct alignment
