#pragma once

#include "Pt3d.h"
#include "Pt2d.h"
#include "TolConsts.h"

#pragma pack (push, math_utils_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

struct Circle_POD;

enum teAngleRetType
{
	eNormAngle,			// 0 to 360
	eUnNormAngle		// -180 to 180
};

extern double part_accy;

double DefaultPartAccy();

//------------------------------------ InitPartAccy ---------------------------------------

inline void InitPartAccy()
{
	part_accy = DefaultPartAccy();
}

//------------------------ CTempAccy -------------------------------------------

class CTempAccy
{
	public:
		CTempAccy()				: save(part_accy) {}
		CTempAccy(double acc)	: save(part_accy) { set(acc); }
		
		void set(double acc)	{ part_accy = acc; }
		void reset()			{ part_accy = save; }
		double get() const		{ return part_accy; }
		
		~CTempAccy()			{ reset(); }
	
	private:
		double save;
};

//------------------------ equal_coord -------------------------------------------

inline bool equal_coord(double val1, double val2)
{
	return EQUAL_X(val1, val2, part_accy);
}

//------------------------ equal_pt_2d -------------------------------------------

inline bool equal_pt_2d(const Pt3d &p1, const Pt3d &p2)
{
	return EQUAL_X2(p1, p2, part_accy);
}

//------------------------ equal_pt_3d -------------------------------------------

inline bool equal_pt_3d(const Pt3d &p1, const Pt3d &p2)
{
	return EQUAL_X3(p1, p2, part_accy);
}

//------------------------ round -------------------------------------------

inline double round(double x)
{
	return floor(x + 0.5);
}

//------------------------ round_to -------------------------------------------

inline double round_to(double x, double y)
{
	return round(x / y) * y;
}

//------------------------ GetShortAngle -------------------------------------------

inline double GetShortAngle(double last_ang, double this_ang)
{
	double delta = this_ang - last_ang;
	if (fabs(delta) > 180.0)
		this_ang -= round_to(delta, 360.0);
	return this_ang;
}

//------------------------ ValidUnitVec ---------------------------------

inline bool ValidUnitVec(const Pt3d &vec)
{
	return EQUAL_X(get_mag(vec), 1.0, ANG_TOL);
}

//------------------------ ParallelUnitVecs ---------------------------------------

inline bool ParallelUnitVecs(const Pt3d &vec1, const Pt3d &vec2, double ang_tol = ANG_TOL)
{
	return (get_mag_sqr(cross(vec1, vec2)) <= ang_tol * ang_tol);
}

//------------------------ ParallelUnitVecs2D ---------------------------------------

inline bool ParallelUnitVecs2D(const Pt3d &vec1, const Pt3d &vec2, double ang_tol = ANG_TOL)
{
	return (fabs(cross_2d(vec1, vec2)) <= ang_tol);
}

//------------------------ TangentUnitVecs ---------------------------------------

inline bool TangentUnitVecs(const Pt3d &vec1, const Pt3d &vec2, double ang_tol = ANG_TOL)
{
	return ParallelUnitVecs(vec1, vec2, ang_tol) && (dot(vec1, vec2) > 0.0);
}

//------------------------ TangentUnitVecs2D ---------------------------------------

inline bool TangentUnitVecs2D(const Pt3d &vec1, const Pt3d &vec2, double ang_tol = ANG_TOL)
{
	return ParallelUnitVecs2D(vec1, vec2) && (dot_2d(vec1, vec2) > 0.0);
}

//------------------------ Rotate90 -------------------------------------------

inline Pt3d Rotate90(const Pt3d &vec)
{
	return Pt3d(- vec[1], vec[0]);
}

//------------------------ Dist2D -------------------------------------------

template <class T1, class T2>
inline double Dist2D(const T1 &p1, const T2 &p2)
{
	return get_mag(Pt2d(p2[0] - p1[0], p2[1] - p1[1]));
}

//------------------------ Dist2DSqr -------------------------------------------

template <class T1, class T2>
inline double Dist2DSqr(const T1 &p1, const T2 &p2)
{
	return get_mag_sqr(Pt2d(p2[0] - p1[0], p2[1] - p1[1]));
}

//------------------------ Dist3D -------------------------------------------

inline double Dist3D(const Pt3d &p1, const Pt3d &p2)
{
	return get_mag(p2 - p1);
}

//------------------------ Dist3DSqr -------------------------------------------

inline double Dist3DSqr(const Pt3d &p1, const Pt3d &p2)
{
	return get_mag_sqr(p2 - p1);
}

//------------------------ CalcLinParam -------------------------------------------

inline double CalcLinParam(double val_lim_0, double val_lim_1, double val)
{
	// calculate a parametric value for 'val' that can be used in linear interpolation.
	// val == val_lim_0 will return 0, val == val_lim_1 will return 1
	double denom = val_lim_1 - val_lim_0;
	return (fabs(denom) > 0.0) ? (val - val_lim_0) / denom : 0.0;
}

//------------------------ LinInterp -------------------------------------------

template <typename T>
inline T LinInterp(const T &val0, const T &val1, double u)
{
	// linear interpolate between val0 and val1...
	return static_cast<T>(val0 + u * (val1 - val0));
}

//------------------------ VecParam -------------------------------------------

inline double VecParam(const Pt3d &test_vec, const Pt3d &base_vec)
{
	double d = dot(base_vec, base_vec);
	return (d > 1.0e-15) ? dot(test_vec, base_vec) / d : 0.0;
}

//------------------------ VecParam2D -------------------------------------------

inline double VecParam2D(const Pt3d &test_vec, const Pt3d &base_vec)
{
	double d = dot_2d(base_vec, base_vec);
	return (d > 1.0e-15) ? dot_2d(test_vec, base_vec) / d : 0.0;
}

//------------------------ GetAngleFromVecs -------------------------------------------

inline double GetAngleFromVecs(const Pt3d &v1, const Pt3d &v2)
{
	// result between 0 and 180 degrees
	return atan2(get_mag(cross(v1, v2)), dot(v1, v2)) * deg_con;
}

//------------------------ GetAngleFromVecs2D -------------------------------------------

inline double GetAngleFromVecs2D(const Pt3d &v1, const Pt3d &v2)
{
	// result between -180 and 180 degrees
	return atan2(cross_2d(v1, v2), dot_2d(v1, v2)) * deg_con;
}

//------------------------ NormAngle -------------------------------------------

inline double NormAngle(double angle)
{
	return angle - floor(angle / 360.0) * 360.0;
}

//------------------------ VecAngle -------------------------------------------

inline double VecAngle(const Pt3d &vec, teAngleRetType ret_type = eNormAngle)
{
	double ang = atan2(vec[1], vec[0]) * deg_con;
	if (ret_type == eNormAngle)
		ang = NormAngle(ang);
	return ang;
}

int CirCir3D(const Pt3d &cp1, double r1, const Pt3d &cp2, double r2, const Pt3d &axis, Pt3d solns[2]);
int CirCir2D(const Pt3d &cp1, double r1, const Pt3d &cp2, double r2, Pt3d solns[]);
void RecalcCP(Circle_POD &circ);

}	// end namespace GCApi

#pragma pack (pop, math_utils_align)						// restore struct alignment
