#pragma once

#include "FeatData.h"

#pragma pack (push, axis_move_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class AxisMove : public FeatData
{
	public:
		AxisMove();
		AxisMove(const AxisMove &src);
		~AxisMove();

		// FeatData interface...
		virtual AxisMove *clone() const					{ return new AxisMove(*this); }
		virtual void from_feat(const Feat &feat);
		virtual void to_feat(Feat &feat) const;
		virtual void write_bin(std::ostream &stream) const;
		virtual void read_bin(std::istream &stream);
		virtual void write_txt(std::ostream &stream) const;
		virtual void read_txt(std::istream &stream);
		
		void swap(AxisMove &that)
		{
			std::swap(pimpl, that.pimpl);
		}
		
		AxisMove & operator = (const AxisMove &rhs)
		{
			if (this != &rhs)
				swap(AxisMove(rhs));
			return *this;
		}
		
		void clear()						{ set_time(0.0); clear_axes(); }
		double get_time() const;			// in minutes, <=0 means calc from axes
		void set_time(double time);
		int axis_count() const;
		void add_axis(const gc_AxisMoveRec2 &src);
		void remove_axis(int ix);
		void clear_axes();
		const gc_AxisMoveRec2 & operator [] (int ix) const;
		gc_AxisMoveRec2 & operator [] (int ix);

	private:
		struct impl;
		impl *pimpl;
};

}	// end namespace GCApi

#pragma pack (pop, axis_move_align)						// restore struct alignment
