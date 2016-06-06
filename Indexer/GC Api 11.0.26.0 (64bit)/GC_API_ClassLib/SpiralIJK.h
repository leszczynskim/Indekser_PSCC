#pragma once

#include "Spiral.h"
#include "FrameIJKGeom.h"

#pragma pack (push, spiralijk_align, 8)							// 8 byte alignment for following types

// shut compiler up about bogus virtual inheritance warning
#pragma warning (push)
#pragma warning (disable : 4250)

namespace GCApi
{
class SpiralIJK : public Spiral, public FrameIJKGeom
{
	public:	
		SpiralIJK()									{}
		SpiralIJK(const Spiral &spiral, const Pt3d &V1, const Pt3d &V2)
			: Spiral(spiral), FrameIJKGeom(V1, V2)	{}
			
		// FeatData interface...
		virtual SpiralIJK *clone() const			{ return new SpiralIJK(*this); }
		virtual void from_feat(const Feat &feat);
		virtual void to_feat(Feat &feat) const;
		virtual void write_bin(std::ostream &stream) const;
		virtual void read_bin(std::istream &stream);
		virtual void write_txt(std::ostream &stream) const;
		virtual void read_txt(std::istream &stream);
		
		// GeomBase interface...
		virtual bool valid() const;
		virtual void transform(const Matrix &matrix);
		virtual void reverse();
		virtual bool trim(double t, const Pt3d *p, bool bUpperBound);
		
		SpiralIJK &set(const Spiral &spiral, const Pt3d &V1 = Pt3d(0.0, 0.0, 1.0), const Pt3d &V2 = Pt3d(0.0, 0.0, 1.0))
		{
			set_def(spiral);
			set_vecs(V1, V2);
			return *this;
		}

	protected:
		Matrix &get_frame_matrix(double t, Matrix &matrix) const;		// virtual
};

}	// end namespace GCApi

#pragma warning (pop)
#pragma pack (pop, spiralijk_align)						// restore struct alignment
