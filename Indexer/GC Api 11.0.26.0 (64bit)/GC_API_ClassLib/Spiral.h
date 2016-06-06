#pragma once

#include "Geom.h"

#pragma pack (push, spiral_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

struct Spiral_POD
{
	Pt3d cp;
	Pt3d axis;
	Pt3d zero_vec;		// spiral angles measured from this vec (radius of spiral is zero_rad at zero degrees)
	double zero_rad;	// radius of the spiral at zero degrees
	double r_delta;		// change in radius for 360 degrees (cannot be zero!)
	double pitch;		// change in depth for 360 degrees
	double shift_0;		// point at angle 0 is shifted by this amount along cross(axis, ang_vec(t))
	double shift_delta;	// change in shift for 360 degrees
	double start_angle;	// defines start point (t == 0); start_angle must be <= end_angle
	double end_angle;	// defines end point (t == 1); end_angle must be >= start_angle

	Spiral_POD()			{}
	Spiral_POD(const gc_Spiral &spiral)
		: cp(spiral.cp), axis(spiral.axis), zero_vec(spiral.zero_vec), zero_rad(spiral.zero_rad), r_delta(spiral.r_delta), pitch(spiral.pitch),
		shift_0(spiral.shift_0), shift_delta(spiral.shift_delta), start_angle(spiral.start_angle), end_angle(spiral.end_angle) {}
		
	operator gc_Spiral () const
	{
		gc_Spiral spiral;
		
		pt_ref(spiral.cp) = cp;
		pt_ref(spiral.axis) = axis;
		pt_ref(spiral.zero_vec) = zero_vec;
		spiral.zero_rad = zero_rad;
		spiral.r_delta = r_delta;
		spiral.pitch = pitch;
		spiral.shift_0 = shift_0;
		spiral.shift_delta = shift_delta;
		spiral.start_angle = start_angle;
		spiral.end_angle = end_angle;
		
		return spiral;
	}
};

class Spiral : public virtual Geom
{
	public:
		Spiral();
		Spiral(const Spiral_POD &spiral)			{ set_def(spiral); }
		Spiral(const gc_Spiral &spiral)				{ set_def(spiral); }

		operator const Spiral_POD& () const			{ return _def; }

		// FeatData interface...
		virtual Spiral *clone() const				{ return new Spiral(*this); }
		virtual void from_feat(const Feat &feat);
		virtual void to_feat(Feat &feat) const;
		virtual void write_bin(std::ostream &stream) const;
		virtual void read_bin(std::istream &stream);
		virtual void write_txt(std::ostream &stream) const;
		virtual void read_txt(std::istream &stream);

		// Geom interface...
		virtual bool valid() const;
		virtual Pt3d sp() const;
		virtual Pt3d ep() const;
		virtual double length() const;
		virtual Pt3d eval(double t) const;
		virtual Pt3d tangent(double t) const;
		virtual double param(const Pt3d &p) const;
		virtual void transform(const Matrix &m);
		virtual void reverse();
		virtual bool trim(double t, const Pt3d *p, bool bUpperBound);
		virtual void set_sp(const Pt3d &p);
		virtual void set_ep(const Pt3d &p);

		// Spiral interface...
		void set_def(const Spiral_POD &spiral);
		const Spiral_POD &def() const				{ return _def; }
		double angle() const						{ return _def.end_angle - _def.start_angle; }
		double radius(double t) const				{ return ang_to_rad(param_to_ang(t)); }
		
	protected:
		Spiral_POD _def;

		mutable Pt3d cache_sp;
		mutable Pt3d cache_ep;
		mutable Pt3d cache_vvec;		// vec to position at 90 degrees
		mutable double cache_len;
		
		enum
		{
			SPIRAL_MASK_SP			= (1 << 0),
			SPIRAL_MASK_EP			= (1 << 1),
			SPIRAL_MASK_VVEC		= (1 << 2),
			SPIRAL_MASK_LEN			= (1 << 3),
		};
		
		double param_to_ang(double ang) const;
		Pt3d ang_vec(double ang) const;					// with axis, defines coordinate frame
		Pt3d eval_prim(double ang) const;
		const Pt3d &hvec() const						{ return _def.zero_vec; }
		const Pt3d &vvec() const;
		double calc_len() const;
		inline double ang_to_rad(double ang) const		{ return _def.zero_rad + _def.r_delta * ang / 360.0; }
		inline double ang_to_shift(double ang) const	{ return _def.shift_0 + _def.shift_delta * ang / 360.0; }
};

}	// end namespace GCApi

#pragma pack (pop, spiral_align)						// restore struct alignment
