#pragma once

namespace GCApi
{

template <typename Container>
inline int Siz(const Container &cont)
{
	return static_cast<int>(cont.size());
}

}	// end namespace GCApi
