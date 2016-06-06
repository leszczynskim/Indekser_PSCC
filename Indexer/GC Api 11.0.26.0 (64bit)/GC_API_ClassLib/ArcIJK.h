#pragma once

#include "Arc3D.h"
#include "FrameIJKGeom.h"

#pragma pack (push, arcijk_align, 8)							// 8 byte alignment for following types

// shut compiler up about bogus virtual inheritance warning
#pragma warning (push)
#pragma warning (disable : 4250)

namespace GCApi
{

class ArcIJK : public Arc3d, public FrameIJKGeom
{
	public:
		ArcIJK()									{}
		ArcIJK(const Arc3d &arc, const Pt3d &ax0, const Pt3d &ax1)
			: Arc3d(arc), FrameIJKGeom(ax0, ax1)	{}
		ArcIJK(const gc_Arc3D &arc, const Pt3d &ax0, const Pt3d &ax1)
			: Arc3d(arc), FrameIJKGeom(ax0, ax1)	{}
		ArcIJK(const Circle &arc, const Pt3d &ax0, const Pt3d &ax1)
			: Arc3d(arc), FrameIJKGeom(ax0, ax1)	{}

		// FeatData interface...
		virtual ArcIJK *clone() const				{ return new ArcIJK(*this); }
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
		
		bool closed() const;
		void restart_closed(double t);

	protected:
		virtual Matrix &get_frame_matrix(double t, Matrix &m = Matrix()) const;
};

}	// end namespace GCApi

#pragma warning (pop)
#pragma pack (pop, arcijk_align)						// restore struct alignment
