#define BOOST_TEST_MODULE Code Buffer Test
#include "HooConfig.hh"
#include "CodeBuffer.hh"

#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <stdlib.h>
#include <unistd.h>

#ifdef HOO_WIN64
#include <windows.h>
#endif

#ifdef HOO_LINUX64
#include <sys/mman.h>
#endif

using namespace hoo::jit;

size_t CodeBufferTest_GetPageSize();

BOOST_AUTO_TEST_CASE(Test001_CodeBufferTest) {
    CodeBuffer buffer;
    BOOST_CHECK(nullptr == buffer.GetBuffer());
    BOOST_CHECK(0 == buffer.GetSize());
    BOOST_CHECK(0 == buffer.GetPageCount());
    BOOST_CHECK(-1 == buffer.GetPosition());
    BOOST_CHECK(false == buffer.IsLocked());

    const auto page_size = CodeBufferTest_GetPageSize();
    const auto sample_data_size = page_size / 2;
    auto sample_data = std::vector<uint8_t >();
    for(auto index = 0; index < sample_data_size; index++) {
        sample_data.push_back((uint8_t) (rand() % 255));
    }

    auto location = buffer.Write(sample_data);
    auto data1 = buffer.GetBuffer();
    BOOST_CHECK(0 == location.GetStart());
    BOOST_CHECK(sample_data.size() == location.GetCount());
    BOOST_CHECK(&data1[location.GetStart()] == location.GetAddress());
    BOOST_CHECK(nullptr != data1);
    BOOST_CHECK(1 == buffer.GetPageCount());
    BOOST_CHECK(page_size == buffer.GetSize());
    BOOST_CHECK((sample_data_size - 1) == buffer.GetPosition());
    BOOST_CHECK(false == buffer.IsLocked());

    for(auto index = 0; index < sample_data_size; index++) {
        BOOST_CHECK(data1[index] == sample_data[index]);
    }

    const auto more_data_size = page_size / 4;
    auto more_data = std::vector<uint8_t>();
    for(auto index = 0; index < more_data_size; index++) {
        more_data.push_back((uint8_t)(rand() % 255));
    }

    buffer.Write(more_data);
    auto data2 = buffer.GetBuffer();
    BOOST_CHECK(data1 == data2);
    BOOST_CHECK(1 == buffer.GetPageCount());
    BOOST_CHECK(page_size == buffer.GetSize());
    BOOST_CHECK((sample_data_size + more_data_size - 1) == buffer.GetPosition());
    BOOST_CHECK(false == buffer.IsLocked());

    for(auto index = 0; index < (sample_data_size + more_data_size); index++) {
        if(index < sample_data_size) {
            BOOST_CHECK(data1[index] == sample_data[index]);
        } else {
            BOOST_CHECK(data1[index] == more_data[index - sample_data_size]);
        }
    }

    const auto extra_data_size = page_size + (page_size / 2);
    auto extra_data = std::vector<uint8_t>();
    for(auto index = 0; index < extra_data_size; index++) {
        extra_data.push_back((uint8_t)(rand() % 255));
    }

    buffer.Write(extra_data);
    auto data3 = buffer.GetBuffer();
    BOOST_CHECK(data2 != data3);
    BOOST_CHECK(3 == buffer.GetPageCount());
    BOOST_CHECK((3 * page_size) == buffer.GetSize());
    BOOST_CHECK((sample_data_size + more_data_size + extra_data_size - 1) == buffer.GetPosition());
    BOOST_CHECK(false == buffer.IsLocked());

    std::vector<uint8_t> all_data;
    all_data.insert(all_data.end(), sample_data.begin(), sample_data.end());
    all_data.insert(all_data.end(), more_data.begin(), more_data.end());
    all_data.insert(all_data.end(), extra_data.begin(), extra_data.end());

    BOOST_CHECK((sample_data_size + more_data_size + extra_data_size) == all_data.size());
    for(auto index = 0; index < all_data.size(); index++) {
        BOOST_CHECK(data3[index] == all_data[index]);
    }
}

BOOST_AUTO_TEST_CASE(Test002_CodeBufferTest) {
    CodeBuffer buffer;
    std::vector<uint8_t> sample_data;
    const auto page_size = CodeBufferTest_GetPageSize();
    for(auto index = 0; index < page_size; index++) {
        sample_data.push_back((uint8_t)(rand() % 255));
    }
    buffer.Write(sample_data);
}


size_t CodeBufferTest_GetPageSize() {
#ifdef HOO_WIN64
    SYSTEM_INFO info;
            GetSystemInfo(&info);
            return (size_t) info.dwPageSize;
#endif
#ifdef HOO_LINUX64
    return (size_t) sysconf(_SC_PAGE_SIZE);
#endif
}
