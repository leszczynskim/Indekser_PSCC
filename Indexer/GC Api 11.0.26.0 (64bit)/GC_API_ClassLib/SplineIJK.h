#pragma once

#include "Spline.h"

#pragma pack (push, spline_ijk_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class SplineIJK : public Spline
{
	public:
		SplineIJK()							{}
		
		// FeatData interface...
		virtual SplineIJK *clone() const			{ return new SplineIJK(*this); }
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
		
		void swap(SplineIJK &that);
		
	private:
		Spline guide;
};

}	// end namespace GCApi

#pragma pack (pop, spline_ijk_align)						// restore struct alignment
