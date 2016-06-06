#pragma once

#include "Line.h"

#pragma pack (push, line_ijk_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class LineIJK : public Line
{
	public:
		LineIJK()									{}
		LineIJK(const Pt3d &p0, const Pt3d &p1, const Pt3d &ax0, const Pt3d &ax1)
			: Line(p0, p1), v0(ax0), v1(ax1) {}

		// FeatData interface...
		virtual LineIJK *clone() const				{ return new LineIJK(*this); }
		virtual void from_feat(const Feat &feat);
		virtual void to_feat(Feat &feat) const;
		virtual void write_bin(std::ostream &stream) const;
		virtual void read_bin(std::istream &stream);
		virtual void write_txt(std::ostream &stream) const;
		virtual void read_txt(std::istream &stream);

		// Geom interface...
		virtual bool valid() const;
		virtual void transform(const Matrix &m);
		virtual void reverse();
		virtual bool trim(double t, const Pt3d *p, bool bUpperBound);
		virtual Pt3d tl_norm(double t) const;
		
		const Pt3d &axis() const;
		double angle() const;

		void set_tl_norm_1(const Pt3d &n);
		void set_tl_norm_2(const Pt3d &n);
		
	protected:
		Pt3d v0, v1;

		mutable Pt3d cache_axis;
		mutable double cache_angle;	

		enum
		{
			LINE_IJK_MASK_AXIS		= (1 << 8),
			LINE_IJK_MASK_ANGLE		= (1 << 9)
		};
};

class RapidIJK : public LineIJK
{
	public:
		RapidIJK()									{}
		RapidIJK(const Pt3d &p0, const Pt3d &p1, const Pt3d &ax0, const Pt3d &ax1)
			: LineIJK(p0, p1, ax0, ax1) {}

		virtual void to_feat(Feat &feat) const;
};

}	// end namespace GCApi

#pragma pack (pop, line_ijk_align)						// restore struct alignment
