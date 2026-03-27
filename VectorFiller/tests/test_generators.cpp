#include "gtest/gtest.h"
#include "atlas/generator/impl/generic/GenericGeneratorImpl.h"
#include "atlas/generator/impl/random/MersenneTwisterNumberGenerator.h"
#include "atlas/generator/impl/random/MersenneTwisterNumberGeneratorFactory.h"

using namespace atlas::generator;

// ============================================================
// GenericGeneratorImpl
// Each test uses a different seed/transform — no shared fixture.
// ============================================================

TEST(GenericGeneratorImplTest, ReturnsInitialSeed) {
    GenericGeneratorImpl gen{42, [](int v) { return v; }};
    EXPECT_EQ(gen.next(), 42);
}

TEST(GenericGeneratorImplTest, ConstantFunctionAlwaysReturnsSameValue) {
    GenericGeneratorImpl gen{7, [](int v) { return v; }};
    for (int i = 0; i < 10; ++i)
        EXPECT_EQ(gen.next(), 7);
}

TEST(GenericGeneratorImplTest, AppliesTransformFunction) {
    GenericGeneratorImpl gen{1, [](int v) { return v * 2; }};
    EXPECT_EQ(gen.next(), 1);
    EXPECT_EQ(gen.next(), 2);
    EXPECT_EQ(gen.next(), 4);
    EXPECT_EQ(gen.next(), 8);
}

TEST(GenericGeneratorImplTest, CounterProducesSequence) {
    GenericGeneratorImpl gen{0, [](int v) { return v + 1; }};
    for (int i = 0; i < 5; ++i)
        EXPECT_EQ(gen.next(), i);
}

// ============================================================
// MersenneTwisterNumberGenerator
// ============================================================

class MersenneTwisterNumberGeneratorTest : public ::testing::Test {
protected:
    MersenneTwisterNumberGenerator gen;
};

TEST_F(MersenneTwisterNumberGeneratorTest, ReturnsValidInt) {
    int value = gen.next();
    EXPECT_GE(value, INT_MIN);
    EXPECT_LE(value, INT_MAX);
}

TEST_F(MersenneTwisterNumberGeneratorTest, ProducesNonConstantSequence) {
    int first = gen.next();
    bool allSame = true;
    for (int i = 0; i < 20; ++i) {
        if (gen.next() != first) {
            allSame = false;
            break;
        }
    }
    EXPECT_FALSE(allSame);
}

TEST_F(MersenneTwisterNumberGeneratorTest, TwoInstancesProduceDifferentSequences) {
    MersenneTwisterNumberGenerator other;
    bool anyDifference = false;
    for (int i = 0; i < 20; ++i) {
        if (gen.next() != other.next()) {
            anyDifference = true;
            break;
        }
    }
    EXPECT_TRUE(anyDifference);
}

// ============================================================
// MersenneTwisterNumberGeneratorFactory
// ============================================================

class MersenneTwisterNumberGeneratorFactoryTest : public ::testing::Test {
protected:
    MersenneTwisterNumberGeneratorFactory factory;
};

TEST_F(MersenneTwisterNumberGeneratorFactoryTest, CreateReturnsNonNull) {
    EXPECT_NE(factory.create(), nullptr);
}

TEST_F(MersenneTwisterNumberGeneratorFactoryTest, CreateReturnsFunctionalGenerator) {
    auto gen = factory.create();
    int value = gen->next();
    EXPECT_GE(value, INT_MIN);
    EXPECT_LE(value, INT_MAX);
}

TEST_F(MersenneTwisterNumberGeneratorFactoryTest, MultipleCreateCallsReturnIndependentGenerators) {
    auto gen1 = factory.create();
    auto gen2 = factory.create();
    EXPECT_NE(gen1.get(), gen2.get());
}
