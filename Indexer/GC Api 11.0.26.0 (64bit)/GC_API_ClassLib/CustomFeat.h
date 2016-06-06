#pragma once

#include "FeatData.h"
#include "ContainerUtils.h"

#pragma pack (push, custom_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class CustomFeat : public FeatData
{
	public:
		char name[256];
		double time;
		std::vector <char> data;
		
		CustomFeat()												: time(0.0) { strcpy(name, ""); }
		CustomFeat(const char *the_name, double the_time = 0.0)		: time(the_time) { strcpy(name, the_name); }
		
		virtual CustomFeat *clone() const		{ return new CustomFeat(*this); }
		
		virtual void from_feat(const Feat &feat)
		{
			int size;
			API_VERIFY(gc_GetFeatCustom(feat.ptr(), name, NULL, &time, NULL, &size));

			data.resize(size);
			if (size)
				API_VERIFY(gc_GetFeatCustomData(feat.ptr(), &data[0]));
		}

		virtual void to_feat(Feat &feat) const
		{
			API_VERIFY(gc_SetFeatCustom(feat.ptr(), name, NULL, time, 0.0, Siz(data), data.empty() ? NULL : &data[0]));
		}

		virtual void write_bin(std::ostream &stream) const
		{
			BinWriteStr(stream, name);
			BinWrite(stream, time);
			BinWrite(stream, data.size());
			BinWriteVec(stream, data);
		}
		
		virtual void read_bin(std::istream &stream)
		{
			BinReadStr(stream, name);
			BinRead(stream, time);
			data.resize(BinRead<int>(stream));
			BinReadVec(stream, data);
		}
		
		virtual void write_txt(std::ostream &stream) const
		{
			stream << name << std::endl;
			if (txt_output_pref == with_data)
				stream << data << std::endl;
		}
		
		virtual void read_txt(std::istream &stream)
		{
			stream >> name;
			stream >> data;
		}
		
		// set CustomFeat::output_pref to 'without_data' to suppress output of data blob
		enum OutputPref {with_data, without_data};
		static OutputPref txt_output_pref;
};

}	// end namespace GCApi

#pragma pack (pop, custom_align)						// restore struct alignment
