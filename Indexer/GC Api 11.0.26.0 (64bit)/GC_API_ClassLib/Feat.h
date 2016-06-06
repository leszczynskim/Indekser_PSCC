#pragma once

#include "api.h"
#include "Pt3d.h"
#include "Matrix.h"
#include <algorithm>

#pragma pack (push, feat_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

//--------------------------- Feat -----------------------

class Feat
{
	private:
		void *ft_;
		
	public:
		Feat()
		{
			API_VERIFY(gc_CreateEmptyFeat(&ft_));
		}
		
		Feat(const Feat &src)
		{
			ft_ = NULL;
			if (src.ft_)
				API_VERIFY(gc_CopyFeat(src.ft_, &ft_));
		}
		
		explicit Feat(void *feat)
			:ft_(feat)
		{
		}
		
		~Feat()
		{
			if (ft_)
				API_VERIFY(gc_DeleteFeat(ft_));
		}
		
		const void *ptr() const
		{
			return ft_;
		}
		
		void *ptr()
		{
			return ft_;
		}
		
		void swap(Feat &that)
		{
			std::swap(ft_, that.ft_);
		}
		
		Feat & operator = (const Feat &rhs)
		{
			Feat(rhs).swap(*this);
			return *this;
		}
		
		void clear()
		{
			if (ft_)
				API_VERIFY(gc_ClearFeat(ft_));
		}
		
		teGeoType type() const
		{
			int t = - 1;
			if (ft_)
				gc_GetFeatType(ft_, &t);
			return static_cast<teGeoType>(t);
		}
		
		char *name(char *sName) const
		{
			API_VERIFY(gc_GetFeatName(ft_, sName));
			return sName;
		}
		
		int feat_cs() const
		{
			int cs = - 1;
			API_VERIFY(gc_GetFeatCS(ft_, &cs));
			return cs;
		}
		
		int attrib(int type) const
		{
			int att = - 1;
			gc_GetFeatAtt(ft_, type, &att);
			return att;
		}
		
		Pt3d eval(double t) const
		{
			Pt3d p;
			API_VERIFY(gc_EvalFeatPoint(ft_, t, p.coord));
			return p;
		}
		
		Pt3d sp() const
		{
			return eval(0.0);
		}
		
		Pt3d ep() const
		{
			return eval(1.0);
		}
		
		Pt3d tl_axis(double t) const
		{
			Pt3d v;
			API_VERIFY(gc_EvalFeatTlAxis(ft_, t, v.coord));
			return v;
		}
		
		void transform(const Matrix &m)
		{
			if (ft_)
				API_VERIFY(gc_TransformFeat(ft_, m.el[0]));
		}
		
		void reverse()
		{
			if (ft_)
				API_VERIFY(gc_ReverseFeat(ft_));
		}

		bool trim(double t, bool upper_bound)
		{
			return gc_TrimFeat(ft_, t, upper_bound) == 0;
		}

		bool wrapped() const
		{
			int bWrapped = false;
			if (ft_)
				gc_GetFeatWrapped(ft_, &bWrapped, NULL, NULL);
			return bWrapped != false;
		}
	
		bool polar() const
		{
			int bPolar = false;
			if (ft_)
				gc_GetFeatPolar(ft_, &bPolar, NULL);
			return bPolar != false;
		}
};

// binary archive functions for Feat...
void BinWrite(std::ostream &stream, const Feat &feat);
void BinRead(std::istream &stream, Feat &feat);

// text archive functions for Feat...
std::ostream & operator << (std::ostream &stream, const Feat &feat);
std::istream & operator >> (std::istream &stream, Feat &feat);

}	// end namespace GCApi

#pragma pack (pop, feat_align)						// restore struct alignment
