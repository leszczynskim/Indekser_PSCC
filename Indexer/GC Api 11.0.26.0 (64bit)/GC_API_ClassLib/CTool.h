#pragma once

#include "FeatData.h"

#pragma pack (push, ctool_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

// for now, only handles data from feed-rate ctools

class CTool : public FeatData
{
	public:
		gc_eCToolType type;
		double feed;			// specific to feed-rate ctools
		
		CTool()							: feed(0.0) {}
		CTool(gc_eCToolType the_type)	: type(the_type), feed(0.0) {}
		
		CTool *clone() const		{ return new CTool(*this); }
		
		void from_feat(const Feat &feat)
		{
			API_VERIFY(gc_GetFeatCTool(feat.ptr(), &type));
			
			if (type == gc_eUserFeedCT)
				API_VERIFY(gc_GetFeatCTool(feat.ptr(), &type, NULL, &feed));
		}

		void to_feat(Feat &feat) const
		{
			API_VERIFY(gc_SetFeatCTool(feat.ptr(), type, NULL, &feed));
		}

		void write_bin(std::ostream &stream) const
		{
			BinWriteEnum(stream, type);
			if (type == gc_eUserFeedCT)
				BinWrite(stream, feed);
		}
		
		void read_bin(std::istream &stream)
		{
			type = BinReadEnum<gc_eCToolType>(stream);
			if (type == gc_eUserFeedCT)
				BinRead(stream, feed);
		}
		
		void write_txt(std::ostream &stream) const;
		void read_txt(std::istream &stream);
};

class Sync : public FeatData
{
	public:
		gc_SyncID id;
		bool postable;
		
		Sync()										: postable(true) {}
		Sync(gc_SyncID the_id, bool for_output)		: id(the_id), postable(for_output) {}
		
		Sync *clone() const		{ return new Sync(*this); }
		
		void from_feat(const Feat &feat)
		{
			API_VERIFY(gc_GetFeatSync(feat.ptr(), &id, &postable));
		}

		void to_feat(Feat &feat) const
		{
			API_VERIFY(gc_SetFeatSync(feat.ptr(), id, postable));
		}

		void write_bin(std::ostream &stream) const
		{
			BinWrite(stream, id.main_id);
			BinWrite(stream, id.sub_id);
			BinWrite(stream, postable);
		}
		
		void read_bin(std::istream &stream)
		{
			BinRead(stream, id.main_id);
			BinRead(stream, id.sub_id);
			BinRead(stream, postable);
		}
		
		void write_txt(std::ostream &stream) const;
		void read_txt(std::istream &stream);
};

}	// end namespace GCApi

#pragma pack (pop, ctool_align)						// restore struct alignment
