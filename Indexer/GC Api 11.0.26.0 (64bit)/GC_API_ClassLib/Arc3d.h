#pragma once

#include "Arc.h"

#pragma pack (push, arc3d_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class Circle;

struct Arc3d_POD
{
	Pt3d cp;
	Pt3d sp_vec;
	Pt3d axis;
	double angle;
	double helix_depth;
	
	Arc3d_POD()			{}
	Arc3d_POD(const gc_Arc3D &arc)
		: cp(arc.cp), sp_vec(arc.sp_vec), axis(arc.axis), angle(arc.angle), helix_depth(arc.helix_depth) {}
		
	operator gc_Arc3D () const
	{
		gc_Arc3D arc;
		
		pt_ref(arc.cp) = cp;
		pt_ref(arc.sp_vec) = sp_vec;
		pt_ref(arc.axis) = axis;
		arc.angle = angle;
		arc.helix_depth = helix_depth;
		
		return arc;
	}
};

class Arc3d : public Arc
{
	public:
		Arc3d();
		Arc3d(const Arc3d_POD &arc)	: _def(arc) {}
		Arc3d(const gc_Arc3D &arc)	: _def(arc) {}
		Arc3d(const Circle &arc);

		operator const Arc3d_POD& () const	{ return _def; }

		// FeatData interface...
		virtual Arc3d *clone() const				{ return new Arc3d(*this); }
		virtual void from_feat(const Feat &feat);
		virtual void to_feat(Feat &feat) const;
		virtual void write_bin(std::ostream &stream) const;
		virtual void read_bin(std::istream &stream);
		virtual void write_txt(std::ostream &stream) const;
		virtual void read_txt(std::istream &stream);

		// Geom interface...
		virtual Pt3d sp() const;
		virtual Pt3d ep() const;
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
		virtual Pt3d axis() const					{ return _def.axis; }
		virtual double radius() const;
		virtual double angle() const				{ return _def.angle; }
		virtual double dstep() const				{ return _def.helix_depth; }
		
		Pt3d norm(double t) const;
		bool closed() const;
		void restart_closed(double t);

	protected:
		Arc3d_POD _def;

		mutable Pt3d cache_sp;
		mutable Pt3d cache_ep;
		mutable Pt3d cache_norm1;
		mutable Pt3d cache_tan1;
		mutable double cache_rad;
		
		enum
		{
			ARC3D_MASK_SP			= (1 << 0),
			ARC3D_MASK_EP			= (1 << 1),
			ARC3D_MASK_NORM1		= (1 << 2),
			ARC3D_MASK_TAN1			= (1 << 3),
			ARC3D_MASK_RAD			= (1 << 4),
			ARC3D_MASK_BOX			= (1 << 5),
		};
		
		const Pt3d &norm1() const;
		const Pt3d &tan1() const;
		
	private:
		void set_eps(const Pt3d &start, const Pt3d &end);
};

}	// end namespace GCApi

#pragma pack (pop, arc3d_align)						// restore struct alignment
