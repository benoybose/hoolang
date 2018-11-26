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
std::vector<uint8_t> CodeBufferTest_GenerateRandomData(size_t size);
void CodeBufferTest_VerifyData(size_t size, const uint8_t *buffer, std::vector<uint8_t> data);

BOOST_AUTO_TEST_CASE(Test001_CodeBufferTest) {
    CodeBuffer buffer;
    BOOST_CHECK(nullptr == buffer.GetBuffer());
    BOOST_CHECK(0 == buffer.GetSize());
    BOOST_CHECK(0 == buffer.GetPageCount());
    BOOST_CHECK(-1 == buffer.GetPosition());
    BOOST_CHECK(false == buffer.IsLocked());

    const auto page_size = CodeBufferTest_GetPageSize();
    const auto sample_data_size = page_size / 2;
    auto sample_data = CodeBufferTest_GenerateRandomData(sample_data_size);

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
    CodeBufferTest_VerifyData(sample_data_size, data1, sample_data);

    const auto more_data_size = page_size / 4;
    auto more_data = CodeBufferTest_GenerateRandomData(more_data_size);

    location = buffer.Write(more_data);
    auto data2 = buffer.GetBuffer();
    BOOST_CHECK(sample_data_size == location.GetStart());
    BOOST_CHECK(more_data_size == location.GetCount());
    BOOST_CHECK(&data2[location.GetStart()] == location.GetAddress());

    BOOST_CHECK(data1 == data2);
    BOOST_CHECK(1 == buffer.GetPageCount());
    BOOST_CHECK(page_size == buffer.GetSize());
    BOOST_CHECK((sample_data_size + more_data_size - 1) == buffer.GetPosition());
    BOOST_CHECK(false == buffer.IsLocked());

    std::vector<uint8_t> all_data;
    all_data.insert(all_data.end(), sample_data.begin(), sample_data.end());
    all_data.insert(all_data.end(), more_data.begin(), more_data.end());
    CodeBufferTest_VerifyData(sample_data_size + more_data_size, data1, all_data);

    const auto extra_data_size = page_size + (page_size / 2);
    auto extra_data = CodeBufferTest_GenerateRandomData(extra_data_size);

    location = buffer.Write(extra_data);
    auto data3 = buffer.GetBuffer();
    BOOST_CHECK(all_data.size() == location.GetStart());
    BOOST_CHECK(extra_data_size == location.GetCount());
    BOOST_CHECK(&data3[location.GetStart()] == location.GetAddress());

    BOOST_CHECK(data2 != data3);
    BOOST_CHECK(3 == buffer.GetPageCount());
    BOOST_CHECK((3 * page_size) == buffer.GetSize());
    BOOST_CHECK((sample_data_size + more_data_size + extra_data_size - 1) == buffer.GetPosition());
    BOOST_CHECK(false == buffer.IsLocked());

    all_data.insert(all_data.end(), extra_data.begin(), extra_data.end());
    CodeBufferTest_VerifyData(sample_data_size + more_data_size + extra_data_size,
                              data3, all_data);

}

BOOST_AUTO_TEST_CASE(Test002_CodeBufferTest) {
    CodeBuffer buffer;
    const auto page_size = CodeBufferTest_GetPageSize();
    auto sample_data = CodeBufferTest_GenerateRandomData(page_size);
    auto location = buffer.Write(sample_data);
    auto data1 = buffer.GetBuffer();

    BOOST_CHECK(0 == location.GetStart());
    BOOST_CHECK(page_size == location.GetCount());
    BOOST_CHECK(&data1[location.GetStart()] == location.GetAddress());

    BOOST_CHECK(1 == buffer.GetPageCount());
    BOOST_CHECK(page_size == buffer.GetSize());
    CodeBufferTest_VerifyData(page_size, data1, sample_data);

    auto more_data = CodeBufferTest_GenerateRandomData(page_size);
    location = buffer.Write(more_data);
    auto data2 = buffer.GetBuffer();

    BOOST_CHECK(page_size == location.GetStart());
    BOOST_CHECK(page_size == location.GetCount());
    BOOST_CHECK(&data2[page_size] == location.GetAddress());

    BOOST_CHECK(data1 != data2);
    BOOST_CHECK(2 == buffer.GetPageCount());
    BOOST_CHECK((2 * page_size) == buffer.GetSize());
}

void CodeBufferTest_VerifyData(size_t size, const uint8_t *buffer, std::vector<uint8_t> data) {
    for(auto index = 0; index < size; index++) {
        BOOST_CHECK(data[index] == buffer[index]);
    }
}

std::vector<uint8_t> CodeBufferTest_GenerateRandomData(size_t size) {
    std::vector<uint8_t> data;
    for(auto index = 0; index < size; index++) {
        data.push_back((uint8_t)(rand() % 255));
    }
    return data;
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
