#pragma once

#include "Asserts.h"
#include "IOUtils.h"
#include <cmath>

#pragma pack (push, pt2d_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

#define DFLT_TOO_SMALL_	1.0e-15

//--------------------------- Pt2d -----------------------

struct Pt2d
{
	double coord[2];
	
	Pt2d()
	{
		coord[0] = coord[1] = 0.0;
	}
	
	Pt2d(const double p[])
	{
		coord[0] = p[0];
		coord[1] = p[1];
	}
	
	Pt2d(double x, double y)
	{
		coord[0] = x;
		coord[1] = y;
	}
	
	Pt2d & operator () (double x, double y)
	{
		coord[0] = x;
		coord[1] = y;
		return *this;
	}
	
	operator double * ()
	{
		return coord;
	}
	
	operator const double * () const
	{
		return coord;
	}
};

inline const Pt2d &pt2_ref(const double *p)
{
	MY_ASSERT(p);
	return *reinterpret_cast<const Pt2d*>(p);
}

inline Pt2d &pt2_ref(double *p)
{
	MY_ASSERT(p);
	return *reinterpret_cast<Pt2d*>(p);
}

//-----------------------------------------------------
// text archive functions for Pt2d...

inline std::ostream & operator << (std::ostream &stream, const Pt2d &p)
{
	TxtWriteSeq(stream, p.coord, p.coord + 2);
	return stream;
}

inline std::istream & operator >> (std::istream &stream, Pt2d &p)
{
	if (!TxtReadSeq(stream, p.coord, p.coord + 2))
		throw;
	return stream;
}
//------------------------- Pt2d operators --------------------

inline Pt2d operator - (const Pt2d &p)
{
	return Pt2d(-p[0], -p[1]);
}

inline Pt2d operator + (const Pt2d &p0, const Pt2d &p1)
{
	return Pt2d(p0[0] + p1[0], p0[1] + p1[1]);
}

inline Pt2d operator - (const Pt2d &p0, const Pt2d &p1)
{
	return Pt2d(p0[0] - p1[0], p0[1] - p1[1]);
}

inline Pt2d operator * (const Pt2d &p, double scalar)
{
	return Pt2d(p[0] * scalar, p[1] * scalar);
}

inline Pt2d operator / (const Pt2d &p, double scalar)
{
	return p * (1.0 / scalar);
}

inline Pt2d operator * (double scalar, const Pt2d &p)
{
	return p * scalar;
}

inline Pt2d & operator += (Pt2d &p0, const Pt2d &p1)
{
	p0[0] += p1[0];
	p0[1] += p1[1];
	return p0;
}

inline Pt2d & operator -= (Pt2d &p0, const Pt2d &p1)
{
	p0[0] -= p1[0];
	p0[1] -= p1[1];
	return p0;
}

inline Pt2d & operator *= (Pt2d &p0, const Pt2d &p1)
{
	p0[0] *= p1[0];
	p0[1] *= p1[1];
	return p0;
}

inline Pt2d & operator /= (Pt2d &p0, const Pt2d &p1)
{
	p0[0] /= p1[0];
	p0[1] /= p1[1];
	return p0;
}

inline Pt2d & operator *= (Pt2d &p, double scalar)
{
	p[0] *= scalar;
	p[1] *= scalar;
	return p;
}

inline Pt2d & operator /= (Pt2d &p, double scalar)
{
	p *= 1.0 / scalar;
	return p;
}

inline double dot(const Pt2d &lhs, const Pt2d &rhs)
{
	return lhs[0] * rhs[0] + lhs[1] * rhs[1];
}

inline double det(const Pt2d &lhs, const Pt2d &rhs)
{
	return lhs[0] * rhs[1] - lhs[1] * rhs[0];
}

inline double get_mag_sqr(const Pt2d &v)
{
	return dot(v, v);
}

inline double get_mag(const Pt2d &vec)
{
	return sqrt(get_mag_sqr(vec));
}

inline bool set_mag(Pt2d &vec, double mag, double too_small = DFLT_TOO_SMALL_)
{
	double old_mag = get_mag(vec);
	if (old_mag <= too_small)
	{
		vec(mag, 0.0);
		return false;
	}
	vec *= mag / old_mag;
	return true;
}

inline bool make_unit(Pt2d &vec, double too_small = DFLT_TOO_SMALL_)
{
	return set_mag(vec, 1.0, too_small);
}

inline Pt2d &normalize(Pt2d &vec, double too_small = DFLT_TOO_SMALL_)
{
	make_unit(vec, too_small);
	return vec;
}

}	// end namespace GCApi

#pragma pack (pop, pt2d_align)						// restore struct alignment
