#pragma once

#include <cmath>

namespace GCApi
{

enum
{
	x_axis = 0, y_axis = 1, z_axis = 2,
	h_axis = 0, v_axis = 1, d_axis = 2,
	a_axis = 0, b_axis = 1, c_axis = 2
};

const double root2			= 1.4142135623730950488;
const double pi				= 3.141592653589793238;
const double two_pi			= pi * 2.0;
const double rad_con		= pi / 180.0;		// conversion from degrees to radians
const double deg_con		= 180.0 / pi;		// conversion from radians to degrees
const double LIN_TOL		= 5.0e-5;			// linear tolerance, in inches (50 millionths of an inch)
const double ANG_TOL		= 2.6e-7;			// angular tolerance, 50 millionths of an inch, on a 16 foot radius, in radians

inline bool EQUAL_X(double v0, double v1, double z)
{
	return fabs(v0 - v1) <= z;
}

template <class T, class U>
inline bool EQUAL_X2(const T &v0, const U &v1, double z)
{
	return EQUAL_X(v0[0], v1[0], z) && EQUAL_X(v0[1], v1[1], z);
}

template <class T, class U>
inline bool EQUAL_X3(const T &v0, const U &v1, double z)
{
	return EQUAL_X2(v0, v1, z) && EQUAL_X(v0[2], v1[2], z);
}

}	// end namespace GCApi
