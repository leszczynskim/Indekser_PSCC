#pragma once

#include "FeatData.h"

#pragma pack (push, dwell_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class Dwell : public FeatData
{
	public:
		enum Type {revs, secs};
		
		Type type;
		double amount;
		
		Dwell(Type typ = revs, double amt = 0.0)		: type(typ), amount(amt) {}

		virtual Dwell *clone() const	{ return new Dwell(*this); }
		
		virtual void from_feat(const Feat &feat)
		{
			int is_revs;
			API_VERIFY(gc_GetFeatDwell(feat.ptr(), &is_revs, &amount));
			type = is_revs ? revs : secs;
		}

		virtual void to_feat(Feat &feat) const
		{
			API_VERIFY(gc_SetFeatDwell(feat.ptr(), type == revs, amount));
		}

		virtual void write_bin(std::ostream &stream) const
		{
			BinWriteEnum(stream, type);
			BinWrite(stream, amount);
		}
		
		virtual void read_bin(std::istream &stream)
		{
			type = BinReadEnum<Type>(stream);
			BinRead(stream, amount);
		}
		
		virtual void write_txt(std::ostream &stream) const
		{
			stream << ((type == revs) ? revs_label : secs_label) << amount << std::endl;
		}
		
		virtual void read_txt(std::istream &stream)
		{
			if (Match(stream, revs_label))
				type = revs;
			else
			{
				Eat(stream, secs_label);
				type = secs;
			}
			stream >> amount;
		}
};

}	// end namespace GCApi

#pragma pack (pop, dwell_align)						// restore struct alignment
