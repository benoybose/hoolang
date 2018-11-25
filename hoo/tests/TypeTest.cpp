#define BOOST_TEST_MODULE Type Test
#include "HooTypes.hh"
#include "String.hh"
#include "Character.hh"

#include <boost/test/included/unit_test.hpp>
#include <cstdio>

BOOST_AUTO_TEST_CASE(Test001_BasicTypes) {
    BOOST_CHECK((sizeof(void*) == 8));
    BOOST_CHECK((sizeof(hoo::Integer) == 8));
    BOOST_CHECK((sizeof(hoo::Character) == sizeof(hoo::Character)));
    BOOST_CHECK((sizeof(hoo::String) == sizeof(hoo::String)));
    BOOST_CHECK((sizeof(hoo::Boolean) == 1));
    BOOST_CHECK((sizeof(hoo::Double) == 16));
}
