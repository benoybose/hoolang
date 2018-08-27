#include "CodeBufferTest.hh"
#include "HooConfig.hh"

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <vector>
#include <cstdlib>

#ifdef HOO_WIN64
#include <windows.h>
#endif

#ifdef HOO_LINUX64
#include <sys/mman.h>
#include <unistd.h>
#endif

using namespace hoo::jit;
using namespace CppUnit;

void CodeBufferTest::Test001_CodeBufferTest() {
    CodeBuffer buffer;
    CPPUNIT_ASSERT(nullptr == buffer.GetBuffer());
    CPPUNIT_ASSERT(0 == buffer.GetSize());
    CPPUNIT_ASSERT(0 == buffer.GetPageCount());
    CPPUNIT_ASSERT(-1 == buffer.GetPosition());
    CPPUNIT_ASSERT(false == buffer.IsLocked());

    const auto page_size = this->GetPageSize();
    const auto sample_data_size = page_size / 2;
    auto sample_data = std::vector<uint8_t >();
    for(auto index = 0; index < sample_data_size; index++) {
        sample_data.push_back((uint8_t) (rand() % 255));
    }


    buffer.Write(sample_data);
    auto data1 = buffer.GetBuffer();

    CPPUNIT_ASSERT(nullptr != data1);
    CPPUNIT_ASSERT(1 == buffer.GetPageCount());
    CPPUNIT_ASSERT(page_size == buffer.GetSize());
    CPPUNIT_ASSERT((sample_data_size - 1) == buffer.GetPosition());
    CPPUNIT_ASSERT(false == buffer.IsLocked());


    for(auto index = 0; index < sample_data_size; index++) {
        CPPUNIT_ASSERT(data1[index] == sample_data[index]);
    }

    const auto more_data_size = page_size / 4;
    auto more_data = std::vector<uint8_t>();
    for(auto index = 0; index < more_data_size; index++) {
        more_data.push_back((uint8_t)(rand() % 255));
    }

    buffer.Write(more_data);
    auto data2 = buffer.GetBuffer();
    CPPUNIT_ASSERT(data1 == data2);
    CPPUNIT_ASSERT(1 == buffer.GetPageCount());
    CPPUNIT_ASSERT(page_size == buffer.GetSize());
    CPPUNIT_ASSERT((sample_data_size + more_data_size - 1) == buffer.GetPosition());
    CPPUNIT_ASSERT(false == buffer.IsLocked());

    for(auto index = 0; index < (sample_data_size + more_data_size); index++) {
        if(index < sample_data_size) {
            CPPUNIT_ASSERT(data1[index] == sample_data[index]);
        } else {
            CPPUNIT_ASSERT(data1[index] == more_data[index - sample_data_size]);
        }
    }

    const auto extra_data_size = page_size + (page_size / 2);
    auto extra_data = std::vector<uint8_t>();
    for(auto index = 0; index < extra_data_size; index++) {
        extra_data.push_back((uint8_t)(rand() % 255));
    }

    buffer.Write(extra_data);
    auto data3 = buffer.GetBuffer();
    CPPUNIT_ASSERT(data2 != data3);
    CPPUNIT_ASSERT(3 == buffer.GetPageCount());
    CPPUNIT_ASSERT((3 * page_size) == buffer.GetSize());
    CPPUNIT_ASSERT((sample_data_size + more_data_size + extra_data_size - 1) == buffer.GetPosition());
    CPPUNIT_ASSERT(false == buffer.IsLocked());

    std::vector<uint8_t> all_data;
    all_data.insert(all_data.end(), sample_data.begin(), sample_data.end());
    all_data.insert(all_data.end(), more_data.begin(), more_data.end());
    all_data.insert(all_data.end(), extra_data.begin(), extra_data.end());

    CPPUNIT_ASSERT((sample_data_size + more_data_size + extra_data_size) == all_data.size());
    for(auto index = 0; index < all_data.size(); index++) {
        CPPUNIT_ASSERT(data3[index] == all_data[index]);
    }
}

void CodeBufferTest::Test002_CodeBufferTest() {
    CodeBuffer buffer;
    std::vector<uint8_t> sample_data;
    const auto page_size = this->GetPageSize();
    for(auto index = 0; index < page_size; index++) {
        sample_data.push_back((uint8_t)(rand() % 255));
    }
    buffer.Write(sample_data);
}



TestSuite *CodeBufferTest::suite() {
    TestSuite *testSuite = new TestSuite();
    testSuite->addTest(new TestCaller<CodeBufferTest>("Test001_CodeBufferTest",
                                                      &CodeBufferTest::Test001_CodeBufferTest));
    testSuite->addTest(new TestCaller<CodeBufferTest>("Test002_CodeBufferTest",
                                                      & CodeBufferTest::Test002_CodeBufferTest));
    return testSuite;
}

size_t CodeBufferTest::GetPageSize() {
#ifdef HOO_WIN64
    SYSTEM_INFO info;
            GetSystemInfo(&info);
            return (size_t) info.dwPageSize;
#endif
#ifdef HOO_LINUX64
    return (size_t) sysconf(_SC_PAGE_SIZE);
#endif
}
