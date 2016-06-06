#pragma once

#include "Asserts.h"
#include <cmath>
#include "TolConsts.h"
#include "IOUtils.h"

#pragma pack (push, angles_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

template <class T>
inline bool EqualAngle(const T &ang1, const T &ang2)
{
	return EQUAL_X(ang1, ang2, ANG_TOL * deg_con);
}

template <class T>
inline bool EqualAngles(const T *abc1, const T *abc2)
{
	for (int iAxis=a_axis; iAxis<=c_axis; iAxis++)
		if (!EqualAngle(abc1[iAxis], abc2[iAxis]))
			return false;
	return true;
}

//--------------------------- Angles -----------------------

struct Angles
{
	double coord[3];
	
	Angles()
	{
		coord[0] = coord[1] = coord[2] = 0.0;
	}
	
	Angles(double abc[])
	{
		coord[0] = abc[0];
		coord[1] = abc[1];
		coord[2] = abc[2];
	}
	
	Angles(double a, double b, double c)
	{
		coord[0] = a;
		coord[1] = b;
		coord[2] = c;
	}
	
	double & operator [] (int axis)
	{
		return coord[axis];
	}
	
	const double & operator [] (int axis) const
	{
		return coord[axis];
	}
	
	Angles & operator () (double a, double b, double c)
	{
		coord[0] = a;
		coord[1] = b;
		coord[2] = c;
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

inline const Angles &ang_ref(const double *abc)
{
	MY_ASSERT(abc);
	return *reinterpret_cast<const Angles*>(abc);
}

inline Angles &ang_ref(double *abc)
{
	MY_ASSERT(abc);
	return *reinterpret_cast<Angles*>(abc);
}

//-----------------------------------------------------
// text archive functions for Angles...

inline std::ostream & operator << (std::ostream &stream, const Angles &abc)
{
	TxtWriteSeq(stream, abc.coord, abc.coord + 3);
	return stream;
}

inline std::istream & operator >> (std::istream &stream, Angles &abc)
{
	if (!TxtReadSeq(stream, abc.coord, abc.coord + 3))
		throw;
	return stream;
}

//------------------------- Angles operators --------------------

inline Angles operator - (const Angles &abc)
{
	return Angles(-abc[0], -abc[1], -abc[2]);
}

inline Angles operator + (const Angles &abc0, const Angles &abc1)
{
	return Angles(abc0[0] + abc1[0], abc0[1] + abc1[1], abc0[2] + abc1[2]);
}

inline Angles operator - (const Angles &abc0, const Angles &abc1)
{
	return Angles(abc0[0] - abc1[0], abc0[1] - abc1[1], abc0[2] - abc1[2]);
}

inline Angles operator * (const Angles &abc, double scalar)
{
	return Angles(abc[0] * scalar, abc[1] * scalar, abc[2] * scalar);
}

inline Angles operator / (const Angles &abc, double scalar)
{
	return abc * (1.0 / scalar);
}

inline Angles operator * (double scalar, const Angles &abc)
{
	return abc * scalar;
}

inline Angles & operator += (Angles &abc0, const Angles &abc1)
{
	abc0[0] += abc1[0];
	abc0[1] += abc1[1];
	abc0[2] += abc1[2];
	return abc0;
}

inline Angles & operator -= (Angles &abc0, const Angles &abc1)
{
	abc0[0] -= abc1[0];
	abc0[1] -= abc1[1];
	abc0[2] -= abc1[2];
	return abc0;
}

inline Angles & operator *= (Angles &abc, double scalar)
{
	abc[0] *= scalar;
	abc[1] *= scalar;
	abc[2] *= scalar;
	return abc;
}

inline Angles & operator /= (Angles &abc, double scalar)
{
	abc *= 1.0 / scalar;
	return abc;
}

inline bool EqualAngles(const Angles &abc1, const Angles &abc2)
{
	return EqualAngles(abc1.coord, abc2.coord);
}

}	// end namespace GCApi

#pragma pack (pop, angles_align)						// restore struct alignment
