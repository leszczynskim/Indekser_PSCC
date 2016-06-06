#pragma once

#include "FeatData.h"

#pragma pack (push, axis_synch_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class AxisSynch : public FeatData
{
	public:
		AxisSynch();
		AxisSynch(gc_AxisSynchType typ, const char *ax, const char *ref = nullptr);
		AxisSynch(const AxisSynch &src);
		~AxisSynch();

		// FeatData interface...
		virtual AxisSynch *clone() const					{ return new AxisSynch(*this); }
		virtual void from_feat(const Feat &feat);
		virtual void to_feat(Feat &feat) const;
		virtual void write_bin(std::ostream &stream) const;
		virtual void read_bin(std::istream &stream);
		virtual void write_txt(std::ostream &stream) const;
		virtual void read_txt(std::istream &stream);
		
		void swap(AxisSynch &that)
		{
			std::swap(pimpl, that.pimpl);
		}
		
		AxisSynch & operator = (const AxisSynch &rhs)
		{
			if (this != &rhs)
				swap(AxisSynch(rhs));
			return *this;
		}
		
		gc_AxisSynchType type() const;
		void set_type(gc_AxisSynchType the_type);
		const char *axis() const;
		void set_axis(const char *axis_name);
		const char *ref_axis() const;
		void set_ref_axis(const char *axis_name);

	private:
		struct impl;
		impl *pimpl;
};

}	// end namespace GCApi

#pragma pack (pop, axis_synch_align)						// restore struct alignment
