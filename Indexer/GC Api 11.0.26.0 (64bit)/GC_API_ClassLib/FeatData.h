#pragma once

#include <memory>		// for std::unique_ptr
#include "IOUtils.h"
#include "Feat.h"
#include "FeatLabels.h"

#pragma pack (push, feat_data_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class FeatData
{
	public:
		virtual FeatData *clone() const						= 0;
		
		virtual void from_feat(const Feat &feat)			= 0;
		virtual void to_feat(Feat &feat) const				= 0;
		
		virtual void write_bin(std::ostream &stream) const	= 0;
		virtual void read_bin(std::istream &stream)			= 0;
		virtual void write_txt(std::ostream &stream) const	= 0;
		virtual void read_txt(std::istream &stream)			= 0;
		virtual ~FeatData()									{}
};

typedef std::unique_ptr <FeatData> FeatDataPtr;

inline Feat &ToFeat(const FeatData &ft_data, Feat &feat = Feat())
{
	ft_data.to_feat(feat);
	return feat;
}

template <typename FeatDataType>
inline FeatDataType &FromFeat(const Feat &feat, FeatDataType &ft_data = FeatDataType())
{
	ft_data.from_feat(feat);
	return ft_data;
}

}	// end namespace GCApi

#pragma pack (pop, feat_data_align)						// restore struct alignment
