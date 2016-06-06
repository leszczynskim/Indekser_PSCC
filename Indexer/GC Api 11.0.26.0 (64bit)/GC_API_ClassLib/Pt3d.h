#pragma once

#include "Asserts.h"
#include "IOUtils.h"
#include <cmath>

#pragma pack (push, pt3d_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

#define DFLT_TOO_SMALL_	1.0e-15

//--------------------------- Pt3d -----------------------

struct Pt3d
{
	double coord[3];
	
	Pt3d()
	{
		coord[0] = coord[1] = coord[2] = 0.0;
	}
	
	Pt3d(const double p[])
	{
		coord[0] = p[0];
		coord[1] = p[1];
		coord[2] = p[2];
	}
	
	Pt3d(double x, double y, double z = 0.0)
	{
		coord[0] = x;
		coord[1] = y;
		coord[2] = z;
	}

	Pt3d & operator () (double x, double y, double z = 0.0)
	{
		coord[0] = x;
		coord[1] = y;
		coord[2] = z;
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

inline const Pt3d &pt_ref(const double *p)
{
	MY_ASSERT(p);
	return *reinterpret_cast<const Pt3d*>(p);
}

inline Pt3d &pt_ref(double *p)
{
	MY_ASSERT(p);
	return *reinterpret_cast<Pt3d*>(p);
}

//-----------------------------------------------------
// text archive functions for Pt3d...

inline std::ostream & operator << (std::ostream &stream, const Pt3d &p)
{
	TxtWriteSeq(stream, p.coord, p.coord + 3);
	return stream;
}

inline std::istream & operator >> (std::istream &stream, Pt3d &p)
{
	if (!TxtReadSeq(stream, p.coord, p.coord + 3))
		throw;
	return stream;
}
//------------------------- Pt3d operators --------------------

inline Pt3d operator - (const Pt3d &p)
{
	return Pt3d(-p[0], -p[1], -p[2]);
}

inline Pt3d operator + (const Pt3d &p0, const Pt3d &p1)
{
	return Pt3d(p0[0] + p1[0], p0[1] + p1[1], p0[2] + p1[2]);
}

inline Pt3d operator - (const Pt3d &p0, const Pt3d &p1)
{
	return Pt3d(p0[0] - p1[0], p0[1] - p1[1], p0[2] - p1[2]);
}

inline Pt3d operator * (const Pt3d &p, double scalar)
{
	return Pt3d(p[0] * scalar, p[1] * scalar, p[2] * scalar);
}

inline Pt3d operator / (const Pt3d &p, double scalar)
{
	return p * (1.0 / scalar);
}

inline Pt3d operator * (double scalar, const Pt3d &p)
{
	return p * scalar;
}

inline Pt3d & operator += (Pt3d &p0, const Pt3d &p1)
{
	p0[0] += p1[0];
	p0[1] += p1[1];
	p0[2] += p1[2];
	return p0;
}

inline Pt3d & operator -= (Pt3d &p0, const Pt3d &p1)
{
	p0[0] -= p1[0];
	p0[1] -= p1[1];
	p0[2] -= p1[2];
	return p0;
}

inline Pt3d & operator *= (Pt3d &p0, const Pt3d &p1)
{
	p0[0] *= p1[0];
	p0[1] *= p1[1];
	p0[2] *= p1[2];
	return p0;
}

inline Pt3d & operator /= (Pt3d &p0, const Pt3d &p1)
{
	p0[0] /= p1[0];
	p0[1] /= p1[1];
	p0[2] /= p1[2];
	return p0;
}

inline Pt3d & operator *= (Pt3d &p, double scalar)
{
	p[0] *= scalar;
	p[1] *= scalar;
	p[2] *= scalar;
	return p;
}

inline Pt3d & operator /= (Pt3d &p, double scalar)
{
	p *= 1.0 / scalar;
	return p;
}

inline double dot(const Pt3d &lhs, const Pt3d &rhs)
{
	return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
}

inline double dot_2d(const Pt3d &lhs, const Pt3d &rhs)
{
	return lhs[0] * rhs[0] + lhs[1] * rhs[1];
}

inline Pt3d cross(const Pt3d &lhs, const Pt3d &rhs)
{
	return Pt3d(lhs[1] * rhs[2] - lhs[2] * rhs[1],
				lhs[2] * rhs[0] - lhs[0] * rhs[2],
				lhs[0] * rhs[1] - lhs[1] * rhs[0]);
}

inline double cross_2d(const Pt3d &lhs, const Pt3d &rhs)
{
	return lhs[0] * rhs[1] - lhs[1] * rhs[0];
}

inline double get_mag_sqr(const Pt3d &v)
{
	return dot(v, v);
}

inline double get_mag_sqr_2d(const Pt3d &v)
{
	return dot_2d(v, v);
}

inline double get_mag(const Pt3d &vec)
{
	return sqrt(get_mag_sqr(vec));
}

inline double get_mag_2d(const Pt3d &vec)
{
	return sqrt(get_mag_sqr_2d(vec));
}

inline bool set_mag(Pt3d &vec, double mag, double too_small = DFLT_TOO_SMALL_)
{
	double old_mag = get_mag(vec);
	if (old_mag <= too_small)
	{
		vec(mag, 0.0, 0.0);
		return false;
	}
	vec *= mag / old_mag;
	return true;
}

inline bool set_mag_2d(Pt3d &vec, double mag, double too_small = DFLT_TOO_SMALL_)
{
	double old_mag = get_mag_2d(vec);
	if (old_mag <= too_small)
	{
		vec(mag, 0.0, 0.0);
		return false;
	}
	mag /= old_mag;
	vec[0] *= mag;
	vec[1] *= mag;
	return true;
}

inline bool make_unit(Pt3d &vec, double too_small = DFLT_TOO_SMALL_)
{
	return set_mag(vec, 1.0, too_small);
}

inline Pt3d &normalize(Pt3d &vec, double too_small = DFLT_TOO_SMALL_)
{
	make_unit(vec, too_small);
	return vec;
}

inline bool make_unit_2d(Pt3d &vec, double too_small = DFLT_TOO_SMALL_)
{
	return set_mag_2d(vec, 1.0, too_small);
}

inline Pt3d &normalize_2d(Pt3d &vec, double too_small = DFLT_TOO_SMALL_)
{
	make_unit_2d(vec, too_small);
	return vec;
}

}	// end namespace GCApi

#pragma pack (pop, pt3d_align)						// restore struct alignment
