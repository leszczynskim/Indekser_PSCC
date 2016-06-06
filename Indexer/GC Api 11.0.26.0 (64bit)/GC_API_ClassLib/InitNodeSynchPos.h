#pragma once

#include "SetNodeSynchPos.h"

#pragma pack (push, init_pos_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class InitNodeSynchPos : public SetNodeSynchPos
{
	public:
		// FeatData interface...
		virtual InitNodeSynchPos *clone() const					{ return new InitNodeSynchPos(*this); }
		virtual void to_feat(Feat &feat) const;
		
		void swap(InitNodeSynchPos &that)
		{
			SetNodeSynchPos::swap(that);
		}
};

}	// end namespace GCApi

#pragma pack (pop, init_pos_align)						// restore struct alignment
