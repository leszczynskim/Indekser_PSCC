#pragma once

#include "Geom.h"

#pragma pack (push, line_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class Line : public Geom
{
	public:
		Line()										{}
		Line(const Pt3d &P0, const Pt3d &P1)		: p0(P0), p1(P1) {}
		
		// FeatData interface...
		virtual Line *clone() const					{ return new Line(*this); }
		virtual void from_feat(const Feat &feat);
		virtual void to_feat(Feat &feat) const;
		virtual void write_bin(std::ostream &stream) const;
		virtual void read_bin(std::istream &stream);
		virtual void write_txt(std::ostream &stream) const;
		virtual void read_txt(std::istream &stream);

		// Geom interface...
		virtual Pt3d sp() const						{ return p0; }
		virtual Pt3d ep() const						{ return p1; }
		virtual double length() const;
		virtual Pt3d eval(double t) const;
		virtual Pt3d tangent(double t) const;
		virtual double param(const Pt3d &p) const;
		virtual void transform(const Matrix &m);
		virtual void reverse();
		virtual bool trim(double t, const Pt3d *p, bool bUpperBound);
		virtual void set_sp(const Pt3d &p);
		virtual void set_ep(const Pt3d &p);

	protected:
		Pt3d p0, p1;

		mutable Pt3d cache_tan;

		enum
		{
			LINE_MASK_TAN		= (1 << 0)
		};
};

class Rapid : public Line
{
	public:
		Rapid()										{}
		Rapid(const Pt3d &P0, const Pt3d &P1)		: Line(P0, P1) {}

		virtual void to_feat(Feat &feat) const;
};

class Thread : public Line
{
	public:
		Thread()									{}
		Thread(const Pt3d &P0, const Pt3d &P1)		: Line(P0, P1) {}

		virtual void to_feat(Feat &feat) const;
};

}	// end namespace GCApi

#pragma pack (pop, line_align)						// restore struct alignment
