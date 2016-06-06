#pragma once

#include "FeatData.h"

#pragma pack (push, init_state_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class InitAxisState : public FeatData
{
	public:
		InitAxisState();
		InitAxisState(const InitAxisState &src);
		~InitAxisState();

		// FeatData interface...
		virtual InitAxisState *clone() const					{ return new InitAxisState(*this); }
		virtual void from_feat(const Feat &feat);
		virtual void to_feat(Feat &feat) const;
		virtual void write_bin(std::ostream &stream) const;
		virtual void read_bin(std::istream &stream);
		virtual void write_txt(std::ostream &stream) const;
		virtual void read_txt(std::istream &stream);
		
		void swap(InitAxisState &that)
		{
			std::swap(pimpl, that.pimpl);
		}
		
		InitAxisState & operator = (const InitAxisState &rhs)
		{
			if (this != &rhs)
				swap(InitAxisState(rhs));
			return *this;
		}
		
		void clear()						{ clear_axes(); }
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

#pragma pack (pop, init_state_align)						// restore struct alignment
