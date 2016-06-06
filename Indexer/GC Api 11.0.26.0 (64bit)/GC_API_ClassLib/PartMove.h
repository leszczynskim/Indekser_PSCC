#pragma once

#include "FeatData.h"

#pragma pack (push, part_move_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class PartMove : public FeatData
{
	public:
		int from_wp;
		int to_wp;
		Pt3d pos;							// old part's origin, in to_wp's coordinate frame (from chuck face)
		Pt3d daxis;							// old part's z-axis, in to_wp's coordinate frame
		Pt3d haxis;							// old part's x-axis, in to_wp's coordinate frame
		
		PartMove()							: from_wp(0), to_wp(0), pos(0.0, 0.0, 0.0), daxis(0.0, 0.0, 1.0), haxis(1.0, 0.0, 0.0) {}
		PartMove(int from, int to)			: from_wp(from), to_wp(to), pos(0.0, 0.0, 0.0), daxis(0.0, 0.0, 1.0), haxis(1.0, 0.0, 0.0) {}

		virtual PartMove *clone() const		{ return new PartMove(*this); }
		
		virtual void from_feat(const Feat &feat)
		{
			API_VERIFY(gc_GetFeatPartMove(feat.ptr(), &from_wp, &to_wp, pos.coord, daxis.coord, haxis.coord));
		}

		virtual void to_feat(Feat &feat) const
		{
			API_VERIFY(gc_SetFeatPartMove(feat.ptr(), from_wp, to_wp, pos.coord, daxis.coord, haxis.coord));
		}

		virtual void write_bin(std::ostream &stream) const
		{
			BinWrite(stream, from_wp);
			BinWrite(stream, to_wp);
			if ((from_wp > 0) && (to_wp > 0))
			{
				BinWrite(stream, pos);
				BinWrite(stream, daxis);
				BinWrite(stream, haxis);
			}
		}
		
		virtual void read_bin(std::istream &stream)
		{
			BinRead(stream, from_wp);
			BinRead(stream, to_wp);
			if ((from_wp > 0) && (to_wp > 0))
			{
				BinRead(stream, pos);
				BinRead(stream, daxis);
				BinRead(stream, haxis);
			}
		}
		
		virtual void write_txt(std::ostream &stream) const
		{
			stream << from_wp_label << from_wp << std::endl;
			stream << to_wp_label << to_wp << std::endl;
			if ((from_wp > 0) && (to_wp > 0))
			{
				stream << pos_label << pos << std::endl;
				stream << daxis_label << daxis << std::endl;
				stream << haxis_label << haxis << std::endl;
			}
		}
		
		virtual void read_txt(std::istream &stream)
		{
			Eat(stream, from_wp_label);
			stream >> from_wp;
			Eat(stream, to_wp_label);
			stream >> to_wp;
			if ((from_wp > 0) && (to_wp > 0))
			{
				Eat(stream, pos_label);
				stream >> pos;
				Eat(stream, daxis_label);
				stream >> daxis;
				Eat(stream, haxis_label);
				stream >> haxis;
			}
		}
};

}	// end namespace GCApi

#pragma pack (pop, part_move_align)						// restore struct alignment
