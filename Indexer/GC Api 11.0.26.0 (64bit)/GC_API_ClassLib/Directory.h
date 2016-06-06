#pragma once

#pragma pack (push, dir_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class CDirectory
{
	private:
		bool bError;
		char sSaveDir[MAX_PATH];

	public:
		CDirectory();
		CDirectory(const char *sNewDir);

		bool success() const				{ return !bError; }
		bool operator () (const char *sNewDir);

		~CDirectory();
};

inline CDirectory::CDirectory()
{
	GetCurrentDirectory(MAX_PATH - 1, sSaveDir);
	bError = false;
}

inline CDirectory::CDirectory(const char *sNewDir)
{
	GetCurrentDirectory(MAX_PATH - 1, sSaveDir);
	bError = !SetCurrentDirectory(sNewDir);
}

inline bool CDirectory::operator () (const char *sNewDir)
{
	bError = !SetCurrentDirectory(sNewDir);
	return !bError;
}

inline CDirectory::~CDirectory()
{
	SetCurrentDirectory(sSaveDir);
}

}	// end namespace GCApi

#pragma pack (pop, dir_align)						// restore struct alignment
