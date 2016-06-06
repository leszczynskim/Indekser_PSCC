#pragma once

#include <fstream>
#include <ostream>
#include <iostream>
#include <string>

#pragma pack (push, ioutils_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

struct StreamRollback
{
	std::istream &stream;
	std::istream::pos_type old_pos;
	bool dismissed;
	
	StreamRollback(std::istream &the_stream)
		: stream(the_stream)
	{
		old_pos = stream.tellg();		// save position
		dismissed = false;
	}
	
	void dismiss()
	{
		dismissed = true;
	}
	
	~StreamRollback()
	{
		if (!dismissed)
			stream.seekg(old_pos);
	}
};

bool EatStreamChar(std::istream &stream, char target_c);
bool GetStreamString(std::istream &stream, char *s, int nmax);
bool GetStreamString(std::istream &stream, std::string &s);
bool Match(std::istream &stream, const char *to_match);

inline std::istream &Eat(std::istream &stream, const char *to_match)
{
	if (!Match(stream, to_match))
		throw;
	return stream;
}

// safe text input for doubles...
std::istream & operator > (std::istream &stream, double &val);

// io to binary streams...

template <typename T>
inline void BinRead(std::istream &stream, T &val)
{
	// reads "plain old data" from a binary file
	stream.read(reinterpret_cast<char*>(&val), sizeof(T));
}

template <typename T>
inline T BinRead(std::istream &stream)
{
	T val;
	BinRead(stream, val);
	return val;
}

template <typename T>
inline void BinWrite(std::ostream &stream, const T &val)
{
	// writes "plain old data" to a binary file
	stream.write(reinterpret_cast<const char*>(&val), sizeof(T));
}

template <typename FwdItr>
inline void BinReadSeq(std::istream &stream, FwdItr begin, FwdItr end)
{
	for (; begin!=end; ++begin)
		BinRead(stream, *begin);
}

template <typename FwdItr>
inline void BinWriteSeq(std::ostream &stream, FwdItr begin, FwdItr end)
{
	for (; begin!=end; ++begin)
		BinWrite(stream, *begin);
}

template <typename T>
inline void BinReadVec(std::istream &stream, std::vector <T> &vec)
{
	BinReadSeq(stream, vec.begin(), vec.end());
}

template <typename T>
inline void BinWriteVec(std::ostream &stream, const std::vector <T> &vec)
{
	BinWriteSeq(stream, vec.begin(), vec.end());
}

// to ensure enums are written and read as ints...

template <typename EnumType>
inline EnumType BinReadEnum(std::istream &stream)
{
	return static_cast<EnumType>(BinRead<int>(stream));
}

template <typename EnumType>
inline void BinWriteEnum(std::ostream &stream, EnumType val)
{
	BinWrite(stream, static_cast<int>(val));
}

inline void BinReadStr(std::istream &stream, char *s)
{
	int len = BinRead<int>(stream);
	stream.read(s, len);
	s[len] = 0;
}

inline void BinWriteStr(std::ostream &stream, const char *s)
{
	int len = static_cast<int>(strlen(s));
	BinWrite(stream, len);
	stream.write(s, len);
}

// io to text streams...

template <typename T>
inline T TxtRead(std::istream &stream)
{
	T val;
	stream >> val;
	return val;
}

template <typename FwdItr>
bool TxtReadSeq(std::istream &stream, FwdItr begin, FwdItr end, char cstart = '(', char cend = ')', char ctween = ',')
{
	StreamRollback roll_back(stream);
	
	char delim = cstart;
	for (FwdItr itr=begin; itr!=end; ++itr)
	{
		if (!EatStreamChar(stream, delim))
			return false;
		stream >> *itr;
		delim = ctween;
	}

	if (!EatStreamChar(stream, cend))
		return false;
	
	roll_back.dismiss();
	return true;
}

template <typename FwdItr>
void TxtWriteSeq(std::ostream &stream, FwdItr begin, FwdItr end, char cstart = '(', char cend = ')', char ctween = ',')
{
	stream << cstart;
	if (begin != end)
	{
		FwdItr itr = begin;
		stream << *itr;
		for (++itr; itr!=end; ++itr)
			stream << ctween << " " << *itr;
	}
	stream << cend;
}

template <typename T>
std::istream & operator >> (std::istream &stream, std::vector <T> &vec)
{
	if (!TxtReadSeq(stream, vec.begin(), vec.end()))
		throw;
	return stream;
}

template <typename T>
std::ostream & operator << (std::ostream &stream, const std::vector <T> &vec)
{
	TxtWriteSeq(stream, vec.begin(), vec.end());
	return stream;
}

inline std::string &ReadStr(std::istream &stream, std::string &s = std::string())
{
	stream >> s;
	return s;
}

struct QuotedStr
{
	explicit QuotedStr(const char *s)			: p(s) {}
	explicit QuotedStr(const std::string &s)	: p(s.c_str()) {}
	
	const char *p;
};

inline std::ostream & operator << (std::ostream &stream, const QuotedStr &s)
{
	stream << '"' << s.p << '"';
	return stream;
}

inline std::string &ReadQuotedStr(std::istream &stream, std::string &s = std::string())
{
	if (!GetStreamString(stream, s))
		throw;
	return s;
}

template <typename EnumType, typename KeyType, typename EntryType>
static EnumType ToEnum(const KeyType &key, const EntryType table[], EnumType enum_size)
{
	const EntryType *found = std::find(table, table + enum_size, key);
	if (found == table + enum_size)
		throw;
	return static_cast<EnumType>(found - table);
}

int ToInt(const std::string &s);
double ToReal(const std::string &s);

// text archive functions for gc_kNodeID...
std::ostream & operator << (std::ostream &stream, gc_kNodeID id);
std::istream & operator >> (std::istream &stream, gc_kNodeID &id);

// text archive functions for gc_AxisMoveRec2...
std::ostream & operator << (std::ostream &stream, const gc_AxisMoveRec2 &move_rec);
std::istream & operator >> (std::istream &stream, gc_AxisMoveRec2 &move_rec);

// text archive functions for gc_InterpSet...
std::ostream & operator << (std::ostream &stream, const gc_InterpSet &interp_set);
std::istream & operator >> (std::istream &stream, gc_InterpSet &interp_set);

// text archive functions for gc_kNodePos...
std::ostream & operator << (std::ostream &stream, const gc_kNodePos &node_pos);
std::istream & operator >> (std::istream &stream, gc_kNodePos &node_pos);

std::ostream & operator << (std::ostream &stream, gc_SyncID id);
std::istream & operator >> (std::istream &stream, gc_SyncID &id);

}	// end namespace GCApi

#pragma pack (pop, ioutils_align)						// restore struct alignment
