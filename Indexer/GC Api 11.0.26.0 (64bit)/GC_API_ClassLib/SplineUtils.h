#pragma once

#include "Spline.h"

namespace GCApi
{

void Bez_DegreeElevate(Spline &spl, int newDegree);
void Append(Spline a_spl, Spline &b_spl);

}	// end namespace GCApi
