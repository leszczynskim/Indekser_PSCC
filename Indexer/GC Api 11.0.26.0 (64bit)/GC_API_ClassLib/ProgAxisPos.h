#pragma once

#include "Pt3d.h"
#include "Angles.h"

#pragma pack (push, pos_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

struct ProgAxisPos
{
	Pt3d xyz;											// tool pivot pt coords
	Angles abc;
	
	ProgAxisPos()										: xyz(0.0, 0.0, 0.0) {}
	ProgAxisPos(const Pt3d &XYZ, const Angles &ABC)		: xyz(XYZ), abc(ABC) {}
	explicit ProgAxisPos(const Pt3d &XYZ)				: xyz(XYZ) {}
	explicit ProgAxisPos(const Angles &ABC)				: xyz(0.0, 0.0, 0.0), abc(ABC) {}
	
	ProgAxisPos & operator () (const Pt3d &XYZ, const Angles &ABC)
	{
		xyz = XYZ; abc = ABC;
		return *this;
	}
};

//-----------------------------------------------------
// text archive functions for ProgAxisPos...

inline std::ostream & operator << (std::ostream &stream, const ProgAxisPos &pos)
{
	stream << '{' << pos.xyz << ", " << pos.abc << '}';
	return stream;
}

inline std::istream & operator >> (std::istream &stream, ProgAxisPos &pos)
{
	Eat(stream, "{");
	stream >> pos.xyz;
	Eat(stream, ",");
	stream >> pos.abc;
	Eat(stream, "}");
}

//----------------------------------- ProgAxisPos operators ---------------------------------------

inline ProgAxisPos operator - (const ProgAxisPos &p)
{
	return ProgAxisPos(-p.xyz, -p.abc);
}

inline ProgAxisPos operator + (const ProgAxisPos &p0, const ProgAxisPos &p1)
{
	return ProgAxisPos(p0.xyz + p1.xyz, p0.abc + p1.abc);
}

inline ProgAxisPos operator - (const ProgAxisPos &p0, const ProgAxisPos &p1)
{
	return ProgAxisPos(p0.xyz - p1.xyz, p0.abc - p1.abc);
}

inline ProgAxisPos operator * (const ProgAxisPos &p, double scalar)
{
	return ProgAxisPos(p.xyz * scalar, p.abc * scalar);
}

inline ProgAxisPos operator / (const ProgAxisPos &p, double scalar)
{
	return p * (1.0 / scalar);
}

inline ProgAxisPos operator * (double scalar, const ProgAxisPos &p)
{
	return p * scalar;
}

inline ProgAxisPos & operator += (ProgAxisPos &p0, const ProgAxisPos &p1)
{
	p0.xyz += p1.xyz;
	p0.abc += p1.abc;
	return p0;
}

inline ProgAxisPos & operator -= (ProgAxisPos &p0, const ProgAxisPos &p1)
{
	p0.xyz -= p1.xyz;
	p0.abc -= p1.abc;
	return p0;
}

inline ProgAxisPos & operator *= (ProgAxisPos &p, double scalar)
{
	p.xyz *= scalar;
	p.abc *= scalar;
	return p;
}

inline ProgAxisPos & operator /= (ProgAxisPos &p, double scalar)
{
	p *= 1.0 / scalar;
	return p;
}

inline bool EqualAxes(const ProgAxisPos &p0, const ProgAxisPos &p1, double tol)
{
	return EqualAngles(p0.abc, p1.abc) && EQUAL_X3(p0.xyz, p1.xyz, tol);
}

}	// end namespace GCApi

#pragma pack (pop, pos_align)						// restore struct alignment
