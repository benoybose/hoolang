#include <cstdint>

#include "Utility.hh"
#include "TestUnit.hh"

class UtilityTest : public hoo::test::TestUnit
{
public:
    UtilityTest()
    {
        RegisterTestCase<UtilityTest> ("GetBytes", &UtilityTest::TestGetBytes);
    }

    void TestGetBytes()
    {
        auto bytes = hoo::common::Utility::GetBytes(0xA1B2F078);
        Count<uint8_t>(bytes, 4);
        At<uint8_t>(bytes, 0, 0x78, "First byte must be 0x78");
        At<uint8_t>(bytes, 1, 0xF0, "Second byte must be 0xF0");
        At<uint8_t>(bytes, 2, 0xB2, "Third byte must be 0xB2");
        At<uint8_t>(bytes, 3, 0xA1, "Fourth byte must be 0xA1");

        bytes = hoo::common::Utility::GetBytes(0xA1);
        Count<uint8_t>(bytes, 1, "Only one byte is expected.");
        At<uint8_t>(bytes, 0, 0xA1, "The single byte should be 0xA1");
        
        bytes = hoo::common::Utility::GetBytes(0xA1B2F07800012A4E);
        Count<uint8_t>(bytes, 8, "8 bytes are expected.");
        At<uint8_t>(bytes, 0, 0x4E);
        At<uint8_t>(bytes, 1, 0x2A);
        At<uint8_t>(bytes, 2, 0x01);
        At<uint8_t>(bytes, 3, 0x00);
        At<uint8_t>(bytes, 4, 0x78);
        At<uint8_t>(bytes, 5, 0xF0);
        At<uint8_t>(bytes, 6, 0xB2);
        At<uint8_t>(bytes, 7, 0xA1);
    }
};

int main()
{
    UtilityTest test;
    auto results = test.Run();
    for (auto result: results) {
        if (!result.IsSuccess()) {
            return -1;
        }
    }
    return 0;
}