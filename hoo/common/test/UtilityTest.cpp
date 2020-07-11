#include <hoo/common/Utility.hh>
#include <hoo/test/TestUnit.hh>

#include <cstdint>
#include <vector>

class UtilityTest : public hoo::test::TestUnit
{
public:
    UtilityTest()
    {
        RegisterTestCase<UtilityTest>("GetBytes", &UtilityTest::TestGetBytes);
        RegisterTestCase<UtilityTest>("AppendTo", &UtilityTest::TestAppendTo);
        RegisterTestCase<UtilityTest>("ToHex", &UtilityTest::TestToHex);
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

        bytes = hoo::common::Utility::GetBytes(0xF1F2F3F4F5);
        Count<uint8_t>(bytes, 5, "8 bytes are expected.");
        At<uint8_t>(bytes, 0, 0xF5);
        At<uint8_t>(bytes, 1, 0xF4);
        At<uint8_t>(bytes, 2, 0xF3);
        At<uint8_t>(bytes, 3, 0xF2);
        At<uint8_t>(bytes, 4, 0xF1);
    }

    void TestAppendTo()
    {
        std::vector<char> v1;
        std::vector<char> v2 = { 'a', 'b', 'c' };
        hoo::common::Utility::AppendTo<char>(v1, v2);
        Count<char>(v1, 3);
        At<char>(v1, 0, 'a');
        At<char>(v1, 1, 'b');
        At<char>(v1, 2, 'c');
        hoo::common::Utility::AppendTo<char>(v1, { '0', '1', '2' });
        Count<char>(v1, 6);
        At<char>(v1, 3, '0');
        At<char>(v1, 4, '1');
        At<char>(v1, 5, '2');
    }

    void TestToHex()
    {
        auto r1 = hoo::common::Utility::ToHex(0);
        StringEqual(r1, "0x00");
        auto r2 = hoo::common::Utility::ToHex(0xFF);
        StringEqual(r2, "0xFF");
        auto r3 = hoo::common::Utility::ToHex(0x7F);
        StringEqual(r3, "0x7F");
        auto r4 = hoo::common::Utility::ToHex(1);
        StringEqual(r4, "0x01");
    }
};

int main()
{
    UtilityTest test;
    auto results = test.Run();
    for (auto result : results)
    {
        if (!result.IsSuccess())
        {
            return -1;
        }
    }
    return 0;
}