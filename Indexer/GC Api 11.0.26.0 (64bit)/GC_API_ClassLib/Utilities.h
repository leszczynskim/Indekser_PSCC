#pragma once

#include "Asserts.h"

namespace GCApi
{

template <typename T>
inline T GetPartInfo(int id)
{
	assert(!"GetPartInfo<> for type not supported");
	return T(0);
}

template <>
inline int GetPartInfo<int>(int id)
{
	int val = 0;
	API_VERIFY(gc_GetPartInfoI(id, &val));
	return val;
}

template <>
inline double GetPartInfo<double>(int id)
{
	double val = 0.0;
	API_VERIFY(gc_GetPartInfoD(id, &val));
	return val;
}

template <typename T>
inline void SetPartInfo(int id, T val)
{
	assert(!"SetPartInfo<> for type not supported");
}

template <>
inline void SetPartInfo<int>(int id, int val)
{
	API_VERIFY(gc_SetPartInfoI(id, &val));
}

template <>
inline void SetPartInfo<double>(int id, double val)
{
	API_VERIFY(gc_SetPartInfoD(id, &val));
}

template <typename T>
inline T GetOpInfo(int op, int id)
{
	assert(!"GetOpInfo<> for type not supported");
	return T(0);
}

template <>
inline int GetOpInfo<int>(int op, int id)
{
	int val = 0;
	API_VERIFY(gc_GetOpInfoI(op, id, &val));
	return val;
}

template <>
inline double GetOpInfo<double>(int op, int id)
{
	double val = 0.0;
	API_VERIFY(gc_GetOpInfoD(op, id, &val));
	return val;
}

template <typename T>
inline void SetOpInfo(int op, int id, T val)
{
	assert(!"SetOpInfo<> for type not supported");
}

template <>
inline void SetOpInfo<int>(int op, int id, int val)
{
	API_VERIFY(gc_SetOpInfoI(op, id, &val));
}

template <>
inline void SetOpInfo<double>(int op, int id, double val)
{
	API_VERIFY(gc_SetOpInfoD(op, id, &val));
}

template <typename T>
inline T GetProcessInfo(int process, int id)
{
	assert(!"GetProcessInfo<> for type not supported");
	return T(0);
}

template <>
inline int GetProcessInfo<int>(int process, int id)
{
	int val = 0;
	API_VERIFY(gc_GetProcInfoI(process, id, &val));
	return val;
}

template <>
inline double GetProcessInfo<double>(int process, int id)
{
	double val = 0.0;
	API_VERIFY(gc_GetProcInfoD(process, id, &val));
	return val;
}

template <typename T>
inline void SetProcessInfo(int process, int id, T val)
{
	assert(!"SetProcessInfo<> for type not supported");
}

template <>
inline void SetProcessInfo<int>(int process, int id, int val)
{
	API_VERIFY(gc_SetProcInfoI(process, id, &val));
}

template <>
inline void SetProcessInfo<double>(int process, int id, double val)
{
	API_VERIFY(gc_SetProcInfoD(process, id, &val));
}

template <typename T>
inline T GetToolInfo(int tool, int id)
{
	assert(!"GetToolInfo<> for type not supported");
	return T(0);
}

template <>
inline int GetToolInfo<int>(int tool, int id)
{
	int val = 0;
	API_VERIFY(gc_GetToolInfoI(tool, id, &val));
	return val;
}

template <>
inline double GetToolInfo<double>(int tool, int id)
{
	double val = 0.0;
	API_VERIFY(gc_GetToolInfoD(tool, id, &val));
	return val;
}

template <typename T>
inline void SetToolInfo(int tool, int id, T val)
{
	assert(!"SetToolInfo<> for type not supported");
}

template <>
inline void SetToolInfo<int>(int tool, int id, int val)
{
	API_VERIFY(gc_SetToolInfoI(tool, id, &val));
}

template <>
inline void SetToolInfo<double>(int tool, int id, double val)
{
	API_VERIFY(gc_SetToolInfoD(tool, id, &val));
}

typedef std::vector <std::string> FILE_LIST;

bool GetEnvVar(const char *sVarName, char *sVar);
bool TestDirName(char *sDirectory);
void StripExtension(char *sFileName, const char *sExt);
void StripDirectory(const char *sFullName, char *sRelativeName);
void GetFileList(FILE_LIST &files, const char *reg_exp);
void ClearDirectory(const char *sDirectory, const char *reg_exp);

}	// end namespace GCApi
