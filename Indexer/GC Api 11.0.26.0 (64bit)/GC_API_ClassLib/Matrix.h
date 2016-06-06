#pragma once

#include "Asserts.h"
#include "IOUtils.h"
#include "MathUtils.h"

#pragma pack (push, matrix_align, 1)							// 1 byte alignment so Matrix is binary compatible with trMatrix

namespace GCApi
{

//--------------------------- Matrix -----------------------

struct Matrix
{
	enum
	{
		trans_flag = 1,
		scale_flag = 2,
		rot_flag = 4,
		any_flag = trans_flag + scale_flag + rot_flag
	};

	int flags;
	double el[3][4];
	
	Matrix();
	Matrix(const double *p);
	
	double * operator [] (int row)
	{
		return el[row];
	}
	
	const double * operator [] (int row) const
	{
		return el[row];
	}
};

//--------------------------- Functions -----------------------

Matrix &Classify(Matrix &m);
Matrix &Concat(Matrix &m1, const Matrix &m2);
Pt3d &TransformPos(Pt3d &p, const Matrix &m);
Pt3d &TransformVec(Pt3d &vec, const Matrix &m);
Matrix &Invert(Matrix &m);
Matrix &Normalize(Matrix &m);
bool Planar(const Matrix &m, bool *pbReverse = NULL);
Pt3d GetScale(const Matrix &m);
Matrix &Scale(Matrix &m, const Pt3d &scale);
Matrix &MakeScale(const Pt3d &scale, Matrix &m = Matrix());
Matrix &Translate(Matrix &m, const Pt3d &trans);
Matrix &MakeTranslation(const Pt3d &trans, Matrix &m = Matrix());
Matrix &MakeRotation(const Pt3d &axis, double sine, double cosine, Matrix &m = Matrix());
Matrix &MakeRotation(double sine, double cosine, Matrix &m = Matrix());
Matrix &FromAxes(const Pt3d &d, const Pt3d *h, const Pt3d *pos, Matrix &m = Matrix());

inline Matrix &Identity(Matrix &m)
{
	m.flags = 0;
	m[0][0] = 1.0; m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] = 0.0;
	m[1][0] = 0.0; m[1][1] = 1.0; m[1][2] = 0.0; m[1][3] = 0.0;
	m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = 1.0; m[2][3] = 0.0;
	return m;
}

inline Pt3d GetRow(const Matrix &m, int iRow)
{
	return Pt3d(m[iRow]);
}

inline Matrix &SetRow(Matrix &m, int iRow, const Pt3d &vec)
{
	pt_ref(m[iRow]) = vec;
	return m;
}

inline Pt3d GetColumn(const Matrix &m, int iCol)
{
	return Pt3d(m[0][iCol], m[1][iCol], m[2][iCol]);
}

inline Matrix &SetColumn(Matrix &m, int iCol, const Pt3d &vec)
{
	m[0][iCol] = vec[0];
	m[1][iCol] = vec[1];
	m[2][iCol] = vec[2];
	return m;
}

inline bool ScalingMatrix(const Matrix &m)
{
	return (m.flags & Matrix::scale_flag) && !EQUAL_X3(GetScale(m), Pt3d(1.0, 1.0, 1.0), LIN_TOL * 0.01);
}

inline Matrix &MakeScale(double scale, Matrix &m = Matrix())
{
	return MakeScale(Pt3d(scale, scale, scale), m);
}

inline Pt3d GetTranslation(const Matrix &m)
{
	return GetColumn(m, 3);
}

inline Matrix &SetTranslation(Matrix &m, const Pt3d &pos)
{
	return SetColumn(m, 3, pos);
}

inline Matrix &ClearTranslation(Matrix &m)
{
	m.flags &= ~Matrix::trans_flag;
	m.el[0][3] = m.el[1][3] = m.el[2][3] = 0.0;
	return m;
}

inline Matrix &MakeRotation(const Pt3d &axis, double angle, Matrix &m = Matrix())
{
	angle *= rad_con;
	return MakeRotation(axis, sin(angle), cos(angle), m);
}

inline Matrix &MakeRotation(double angle, Matrix &m = Matrix())
{
	angle *= rad_con;
	return MakeRotation(sin(angle), cos(angle), m);
}

inline Matrix &MakeRotation(const Pt3d &axis, double angle, const Pt3d &origin, Matrix &m = Matrix())
{
	return Translate(Concat(MakeRotation(axis, angle, m), MakeTranslation(-origin)), origin);
}

inline Matrix &MakeRotation(double angle, const Pt3d &origin, Matrix &m = Matrix())
{
	return Translate(Concat(MakeRotation(angle, m), MakeTranslation(-origin)), origin);
}

inline Matrix &FromAxes(const Pt3d &d, const Pt3d &h, const Pt3d &pos, Matrix &m = Matrix())
{
	return FromAxes(d, &h, &pos, m);
}

inline Matrix &FromAxes(const Pt3d &d, const Pt3d &h, Matrix &m = Matrix())
{
	return FromAxes(d, &h, NULL, m);
}

inline Matrix &FromAxes(const Pt3d &d, Matrix &m = Matrix())
{
	return FromAxes(d, NULL, NULL, m);
}

inline double Determinant(const Matrix &m)
{
	return m.el[0][0] * (m.el[1][1] * m.el[2][2] - m.el[2][1] * m.el[1][2])
		- m.el[0][1] * (m.el[1][0] * m.el[2][2] - m.el[2][0] * m.el[1][2])
		+ m.el[0][2] * (m.el[1][0] * m.el[2][1] - m.el[2][0] * m.el[1][1]);
}

inline Matrix &Transpose(Matrix &m)
{
	// does 3 x 3 only
	std::swap(m.el[0][1], m.el[1][0]);
	std::swap(m.el[0][2], m.el[2][0]);
	std::swap(m.el[1][2], m.el[2][1]);
	return m;
}

inline Matrix &ChangeMatrixBasis(Matrix &mx, const Matrix &to_new_basis_mx)
{
	mx = Concat(Concat(Matrix(to_new_basis_mx), mx), Invert(Matrix(to_new_basis_mx)));
	return mx;
}

inline Matrix &ChangeMatrixBasis2(Matrix &mx, const Matrix &to_old_basis_mx)
{
	mx = Concat(Concat(Invert(Matrix(to_old_basis_mx)), mx), to_old_basis_mx);
	return mx;
}

inline bool ReverseDir(const Matrix &mx)
{
	return mx[2][2] < - 1.0 + ANG_TOL;
}

//--------------------------- Matrix implementation -----------------------

inline Matrix::Matrix()
{
	Identity(*this);
}

inline Matrix::Matrix(const double *p)
{
	for (int row=0; row<3; ++row)
		for (int col=0; col<4; ++col, ++p)
			el[row][col] = *p;
	flags = any_flag;
}

//--------------------------------------------------------
// text archive functions for Matrix...

inline std::ostream & operator << (std::ostream &stream, const Matrix &m)
{
	TxtWriteSeq(stream, m.el[0], m.el[0] + 12, '[', ']');
	return stream;
}

inline std::istream & operator >> (std::istream &stream, Matrix &m)
{
	if (!TxtReadSeq(stream, m.el[0], m.el[0] + 12, '[', ']'))
		throw;

	Classify(m);
	return stream;
}

}	// end namespace GCApi

#pragma pack (pop, matrix_align)						// restore struct alignment
