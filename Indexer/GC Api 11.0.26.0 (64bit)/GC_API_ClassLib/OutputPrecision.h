#pragma once

#pragma pack (push, prec_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

struct OutputPrecision
{
	int time;			// for outputting time in minutes
	int position;		// for outputting coordinates in part coordinates
	int angle;			// for outputting angles in degrees
	int normalized;		// for outputting normalized values
};

}	// end namespace GCApi

#pragma pack (pop, prec_align)						// restore struct alignment
