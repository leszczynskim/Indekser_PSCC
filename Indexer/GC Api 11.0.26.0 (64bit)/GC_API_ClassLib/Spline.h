#pragma once

#include "Geom.h"
#include "ContainerUtils.h"
#include "boost/logic/tribool.hpp"

#pragma pack (push, spline_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

//--------------------------- Spline -----------------------

class Spline : public Geom
{
	public:
		Spline()									{}
		Spline(int deg, int kct, int cct)			{ init(deg, kct, cct); }

		// FeatData interface...
		virtual Spline *clone() const				{ return new Spline(*this); }
		virtual void from_feat(const Feat &feat);
		virtual void to_feat(Feat &feat) const;
		virtual void write_bin(std::ostream &stream) const;
		virtual void read_bin(std::istream &stream);
		virtual void write_txt(std::ostream &stream) const;
		virtual void read_txt(std::istream &stream);

		// Geom interface...
		virtual bool valid() const;
		virtual Pt3d sp() const						{ MY_ASSERT(!ctrls.empty()); return ctrls.front().pt; }
		virtual Pt3d ep() const						{ MY_ASSERT(!ctrls.empty()); return ctrls.back().pt; }
		virtual double length() const				{ warn(); return 0.0; }
		virtual Pt3d eval(double t) const			{ warn(); return Pt3d(); }
		virtual Pt3d tangent(double t) const		{ warn(); return Pt3d(); }
		virtual double param(const Pt3d &p) const	{ warn(); return 0.0; }
		virtual void transform(const Matrix &m)		{ warn(); }
		virtual void reverse()						{ warn(); }
		virtual bool trim(double t, const Pt3d *p, bool bUpperBound)	{ warn(); return false; }
		virtual void set_sp(const Pt3d &p)			{ warn(); }
		virtual void set_ep(const Pt3d &p)			{ warn(); }

		int k_count() const							{ return Siz(knots); }
		int c_count() const							{ return Siz(ctrls); }
		void set_k_count(int kct)					{ knots.resize(kct); }
		void set_c_count(int cct)					{ ctrls.resize(cct); }
		bool empty() const							{ return knots.empty() || ctrls.empty(); }
		void init(int deg, int kct, int cct);
		void swap(Spline &that);
		Spline & operator += (const Spline &rhs);	// append rhs to this
		bool rational() const;
		void set_dirty()							{ is_rat = boost::indeterminate; }
	
		struct Knot
		{
			double param;
			int mult;
		};
		
		struct Ctrl
		{
			Pt3d pt;
			double wt;
		};
		
		typedef std::vector <Knot> KnotVec;
		typedef std::vector <Ctrl> CtrlVec;
	
		int degree;
		KnotVec knots;
		CtrlVec ctrls;
		mutable boost::tribool is_rat;
		
	private:
		void warn() const							{ MY_ASSERT(false); }	// Spline geometry operators not available yet
};

inline void Spline::init(int deg, int kct, int cct)
{
	degree = deg;
	set_k_count(kct);
	set_c_count(cct);
}

inline void Spline::swap(Spline &that)
{
	std::swap(degree, that.degree);
	knots.swap(that.knots);
	ctrls.swap(that.ctrls);
	std::swap(is_rat, that.is_rat);
}


}	// end namespace GCApi

#pragma pack (pop, spline_align)						// restore struct alignment
