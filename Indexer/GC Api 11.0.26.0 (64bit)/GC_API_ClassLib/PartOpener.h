#pragma once

#pragma pack (push, opener_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class CPartOpener
{
	private:
		bool bError;

	public:
		CPartOpener()						: bError(false) {}
		CPartOpener(const char *sPartName)	{ open(sPartName); }

		bool open(const char *sPartName)
		{
			bError = (gc_OpenPart(const_cast<char*>(sPartName)) < 0);
			return !bError;
		}
		
		bool success() const				{ return !bError; }

		~CPartOpener()						{ gc_ClosePart(TRUE, FALSE); }
};

}	// end namespace GCApi

#pragma pack (pop, opener_align)						// restore struct alignment
