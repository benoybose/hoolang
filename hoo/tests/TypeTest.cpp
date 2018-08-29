#define BOOST_TEST_MODULE Type Test
#include "HooTypes.hh"

#include <boost/test/included/unit_test.hpp>
#include <cstdio>

BOOST_AUTO_TEST_CASE(Test001_BasicTypes) {
    BOOST_CHECK((sizeof(void*) == 8));
    BOOST_CHECK((sizeof(hoo::Integer) == 8));
    BOOST_CHECK((sizeof(hoo::Character) == sizeof(void*)));
    BOOST_CHECK((sizeof(hoo::String) == sizeof(void*)));
    BOOST_CHECK((sizeof(hoo::Boolean) == 1));
    BOOST_CHECK((sizeof(hoo::Double) == 16));
}
