// Copyright 2024 Accenture.

#include "async/util/Call.h"

#include <gmock/gmock.h>

namespace
{
using namespace ::async;
using namespace ::testing;

class AsyncCallTest : public Test
{
public:
    MOCK_METHOD0(functionCall, void());
    MOCK_METHOD2(closureCall, void(uint16_t, uint32_t));
};

TEST_F(AsyncCallTest, testFunction)
{
    {
        Function cut;
        cut.execute();
    }
    {
        Function cut(
            Function::CallType::create<AsyncCallTest, &AsyncCallTest::functionCall>(*this));
        EXPECT_CALL(*this, functionCall());
        cut.execute();
    }
}

TEST_F(AsyncCallTest, testClosure)
{
    using TestClosure = ::estd::closure<void(uint16_t, uint32_t)>;
    Call<TestClosure> cut(TestClosure(
        TestClosure::fct::create<AsyncCallTest, &AsyncCallTest::closureCall>(*this),
        1234U,
        3247834U));
    EXPECT_CALL(*this, closureCall(1234U, 3247834U));
    cut.execute();
}
} // namespace