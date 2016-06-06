#pragma once

#include "boost/static_assert.hpp"

// ensure correct number of names are defined in array...

#define ARRAY_SIZE(the_array)				(sizeof(the_array) / sizeof(*the_array))
#define NAME_TABLE_ASSERT(names, size)		BOOST_STATIC_ASSERT(ARRAY_SIZE(names) == size)

