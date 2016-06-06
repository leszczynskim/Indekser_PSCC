#pragma once

#include "FeatData.h"

#pragma pack (push, node_pos_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class SetNodeSynchPos : public FeatData
{
	public:
		// FeatData interface...
		virtual SetNodeSynchPos *clone() const					{ return new SetNodeSynchPos(*this); }
		virtual void from_feat(const Feat &feat);
		virtual void to_feat(Feat &feat) const;
		virtual void write_bin(std::ostream &stream) const;
		virtual void read_bin(std::istream &stream);
		virtual void write_txt(std::ostream &stream) const;
		virtual void read_txt(std::istream &stream);
		
		void swap(SetNodeSynchPos &that)
		{
			std::swap(pos, that.pos);
		}
		
		gc_kNodePos pos;
};

}	// end namespace GCApi

#pragma pack (pop, node_pos_align)						// restore struct alignment
