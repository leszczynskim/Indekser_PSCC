#pragma once

#include "Geom.h"

#pragma pack (push, frameijk_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

// FrameIJKGeom is a base class for ijk feature types whose tl_norm sweeps uniformly in the coordinate frame from v1 to v2.
// FrameIJKGeom stores v1 and v2, and provides the implementation for 'tl_norm' method.
// The derived class must provide coordinate frame via 'get_frame_matrix' method

class FrameIJKGeom : public virtual Geom
{
	public:
		FrameIJKGeom()								: v1(0.0, 0.0, 1.0), v2(0.0, 0.0, 1.0) {}
		FrameIJKGeom(const Pt3d &V1, const Pt3d &V2);
			
		// GeomBase interface...
		void transform(const Matrix &matrix);		// virtual
		void reverse();								// virtual
		bool trim(double t, const Pt3d *p, bool bUpperBound);	// virtual
		Pt3d tl_norm(double t) const;				// virtual
		
		void set_tl_norm_1(const Pt3d &n);
		void set_tl_norm_2(const Pt3d &n);
		void set_vecs(const Pt3d &V1 = Pt3d(0.0, 0.0, 1.0), const Pt3d &V2 = Pt3d(0.0, 0.0, 1.0));
		bool valid_vecs() const;
		
	protected:
		Pt3d v1;
		Pt3d v2;
		
		struct frame_info
		{
			Pt3d v1;		// v1 in local coordinate frame
			Pt3d nv1;		// normal to both v1 and the rot axis from v1 to v2 in local coordinate frame
			double angle;	// angle of rotation from v1 to v2 in local coordinate frame
			
			Pt3d eval(double t)
			{
				double theta = t * angle * rad_con;
				return cos(theta) * v1 + sin(theta) * nv1;
			}
		};
		
		mutable frame_info cache_frame_info;

		enum
		{
			IJK_MASK_FRAME_INFO			= (1 << 8)
		};
		
		void calc_frame_info() const;

		virtual Matrix &get_frame_matrix(double t, Matrix &matrix = Matrix()) const = 0; // derived class provides frame info
};

} // end namespace Geom

#pragma pack (pop, frameijk_align)						// restore struct alignment
