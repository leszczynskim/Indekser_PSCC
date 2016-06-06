#pragma once

#include "Feat.h"

#pragma pack (push, path_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

//--------------------------- Path -----------------------

class Path
{
	private:
		void *path_;
		bool owned_;
		
	public:
		Path()
			: owned_(true)
		{
			API_VERIFY(gc_PathCreate(&path_));
		}
	
		explicit Path(int iOp, int ePathType = gc_eOpMainPath)
			: owned_(true)
		{
			if (gc_GetOpPathEx(iOp, ePathType, &path_) != 0)
				API_VERIFY(gc_PathCreate(&path_));
		}
	
		explicit Path(void *path, bool owned)
			: path_(path), owned_(owned)
		{
		}
	
		Path(const Path &src)
			: path_(src.path_), owned_(true)
		{
			if (path_)
				API_VERIFY(gc_PathCopy(path_, &path_));
		}

		~Path()
		{
			if (path_ && owned_)
				API_VERIFY(gc_PathDelete(path_));
		}

		const void *ptr() const
		{
			return path_;
		}
		
		void *ptr()
		{
			return path_;
		}
		
		void swap(Path &that)
		{
			std::swap(path_, that.path_);
			std::swap(owned_, that.owned_);
		}
		
		void *release()
		{
			void *apath = path_;
			path_ = NULL;
			owned_ = false;
			return apath;
		}
		
		Path & operator = (const Path &rhs)
		{
			Path(rhs).swap(*this);
			return *this;
		}
		
		int size() const
		{
			int count = 0;
			if (path_)
				API_VERIFY(gc_GetPathNumFeat(path_, &count));
			return count;
		}
		
		bool empty() const
		{
			return size() == 0;
		}
		
		void clear()
		{
			if (path_)
				API_VERIFY(gc_PathClear(path_));
		}
		
		Feat read(int ix) const
		{
			void *feat_ptr;
			API_VERIFY(gc_GetPathFeat(path_, ix, &feat_ptr));
			return Feat(feat_ptr);
		}
		
		void write(const Feat &feat)
		{
			API_VERIFY(gc_PathAddFeat(path_, feat.ptr()));
		}
		
		void transform(const Matrix &m)
		{
			if (path_)
				API_VERIFY(gc_PathTransform(path_, m.el[0]));
		}
};

// binary archive functions for Path...
void BinWrite(std::ostream &stream, const Path &path);
void BinRead(std::istream &stream, Path &path);

// text archive functions for Path...
std::ostream & operator << (std::ostream &stream, const Path &path);
std::istream & operator >> (std::istream &stream, Path &path);

void SetOpPath(const Path &path, int iOp, int ePathType = gc_eOpMainPath);

}	// end namespace GCApi

#pragma pack (pop, path_align)						// restore struct alignment
