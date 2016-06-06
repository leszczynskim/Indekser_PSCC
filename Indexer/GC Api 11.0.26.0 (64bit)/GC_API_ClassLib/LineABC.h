#pragma once

#include "Line.h"
#include "Angles.h"
#include "UndrivenAxes.h"

#pragma pack (push, line_abc_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

class LineABC : public Line
{
	public:
		Angles abc0, abc1;
		int tool, wp;
		bool tcp_on;
		UnDrivenAxes undriven;

		LineABC()						: tool(1), wp(1), tcp_on(false) {}

		virtual LineABC *clone() const	{ return new LineABC(*this); }

		virtual void from_feat(const Feat &feat)
		{
			Line::from_feat(feat);
			API_VERIFY(gc_GetFeatABCEnds(feat.ptr(), abc0.coord, abc1.coord));
			
			int tcp;
			API_VERIFY(gc_GetFeatABCContext(feat.ptr(), &tool, &wp, &tcp));
			tcp_on = (tcp != 0);
			
			driven_from_feat(feat);
		}

		virtual void to_feat(Feat &feat) const
		{
			API_VERIFY(gc_SetFeatLineABC(feat.ptr(), p0.coord, abc0.coord, p1.coord, abc1.coord, tool, wp, tcp_on, 1));
			driven_to_feat(feat);
		}

		virtual void write_bin(std::ostream &stream) const
		{
			Line::write_bin(stream);
			BinWrite(stream, abc0);
			BinWrite(stream, abc1);
			BinWrite(stream, tool);
			BinWrite(stream, wp);
			BinWrite(stream, tcp_on);
			BinWrite(stream, undriven);
		}
		
		virtual void read_bin(std::istream &stream)
		{
			Line::read_bin(stream);
			BinRead(stream, abc0);
			BinRead(stream, abc1);
			BinRead(stream, tool);
			BinRead(stream, wp);
			BinRead(stream, tcp_on);
			BinRead(stream, undriven);
		}
		
		virtual void write_txt(std::ostream &stream) const
		{
			Line::write_txt(stream);
			stream << abc0_label << abc0 << std::endl;
			stream << abc1_label << abc1 << std::endl;
			stream << tool_label << tool << wp_label << wp;
			stream << " " << (tcp_on ? tcp_on_label : tcp_off_label) << std::endl;
			if (Any(undriven))
				stream << undriven_label << undriven << std::endl;
		}
		
		virtual void read_txt(std::istream &stream)
		{
			Line::read_txt(stream);
			Eat(stream, abc0_label);
			stream >> abc0;
			Eat(stream, abc1_label);
			stream >> abc1;
			Eat(stream, tool_label);
			stream >> tool;
			Eat(stream, wp_label);
			stream >> wp;
			if (Match(stream, tcp_on_label))
				tcp_on = true;
			else
			{
				Eat(stream, tcp_off_label);
				tcp_on = false;
			}
			if (Match(stream, undriven_label))
				stream >> undriven;
			else
				undriven = UnDrivenAxes();
		}
		
	protected:
		void driven_from_feat(const Feat &feat)
		{
			for (int i=0; i<3; ++i)
			{
				int unknown;
				API_VERIFY(gc_GetFeatABCLinAxisEndUnknown(feat.ptr(), i, &unknown));
				undriven.lin[i] = (unknown != false);
				API_VERIFY(gc_GetFeatABCRotAxisEndUnknown(feat.ptr(), i, &unknown));
				undriven.rot[i] = (unknown != false);
			}
		}

		void driven_to_feat(Feat &feat) const
		{
			for (int i=0; i<3; ++i)
			{
				if (undriven.lin[i])
					API_VERIFY(gc_SetFeatABCLinAxisEndUnknown(feat.ptr(), i, true));
				if (undriven.rot[i])
					API_VERIFY(gc_SetFeatABCRotAxisEndUnknown(feat.ptr(), i, true));
			}
		}
};

class RapidABC : public LineABC
{
	public:
		virtual void to_feat(Feat &feat) const
		{
			API_VERIFY(gc_SetFeatLineABC(feat.ptr(), p0.coord, abc0.coord, p1.coord, abc1.coord, tool, wp, tcp_on, 0));
			driven_to_feat(feat);
		}
};

}	// end namespace GCApi

#pragma pack (pop, line_abc_align)						// restore struct alignment
