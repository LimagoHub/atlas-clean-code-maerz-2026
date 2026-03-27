#include "gtest/gtest.h"
#include "atlas/container/impl/builder/VectorFactoryBuilder.h"
#include "atlas/generator/impl/random/MersenneTwisterNumberGeneratorFactory.h"
#include "atlas/time/impl/StopwatchImpl.h"

using namespace atlas;

auto makeMTFactory() {
    return std::make_unique<generator::MersenneTwisterNumberGeneratorFactory>();
}

class VectorFactoryBuilderTest : public ::testing::Test {
protected:
    container::VectorFactoryBuilder<int> builder;
};

// ============================================================
// Strategy selection
// ============================================================

TEST_F(VectorFactoryBuilderTest, SequentialStrategyBuildsNonNullFactory) {
    auto factory = builder.withStrategy(container::Strategy::Sequential).build(makeMTFactory());
    EXPECT_NE(factory, nullptr);
}

TEST_F(VectorFactoryBuilderTest, AutoStrategyBuildsNonNullFactory) {
    auto factory = builder.withStrategy(container::Strategy::Auto).build(makeMTFactory());
    EXPECT_NE(factory, nullptr);
}

TEST_F(VectorFactoryBuilderTest, ParallelStrategyBuildsNonNullFactory) {
    auto factory = builder.withStrategy(container::Strategy::Parallel).withThreadCount(2).build(makeMTFactory());
    EXPECT_NE(factory, nullptr);
}

TEST_F(VectorFactoryBuilderTest, ThreadpoolStrategyBuildsNonNullFactory) {
    auto factory = builder.withStrategy(container::Strategy::Threadpool).withThreadCount(2).build(makeMTFactory());
    EXPECT_NE(factory, nullptr);
}

TEST_F(VectorFactoryBuilderTest, ThreadpoolLoopStrategyBuildsNonNullFactory) {
    auto factory = builder.withStrategy(container::Strategy::ThreadpoolLoop).withThreadCount(2).build(makeMTFactory());
    EXPECT_NE(factory, nullptr);
}

// ============================================================
// Output correctness
// ============================================================

TEST_F(VectorFactoryBuilderTest, BuiltFactoryFillsVectorWithCorrectSize) {
    auto factory = builder.withStrategy(container::Strategy::Sequential).build(makeMTFactory());
    auto result = factory->createAndFillVector(100);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->size(), 100u);
}

TEST_F(VectorFactoryBuilderTest, DefaultStrategyIsSequential) {
    auto factory = builder.build(makeMTFactory());
    auto result = factory->createAndFillVector(10);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->size(), 10u);
}

// ============================================================
// Decorators
// ============================================================

TEST_F(VectorFactoryBuilderTest, LoggingDecoratorPreservesCorrectSize) {
    auto factory = builder
        .withStrategy(container::Strategy::Sequential)
        .enableLogging()
        .build(makeMTFactory());
    EXPECT_EQ(factory->createAndFillVector(10)->size(), 10u);
}

TEST_F(VectorFactoryBuilderTest, SecurityDecoratorPreservesCorrectSize) {
    auto factory = builder
        .withStrategy(container::Strategy::Sequential)
        .enableSecurity()
        .build(makeMTFactory());
    EXPECT_EQ(factory->createAndFillVector(10)->size(), 10u);
}

TEST_F(VectorFactoryBuilderTest, BenchmarkDecoratorPreservesCorrectSize) {
    auto factory = builder
        .withStrategy(container::Strategy::Sequential)
        .withBenchmark(std::make_unique<time::StopwatchImpl>())
        .build(makeMTFactory());
    EXPECT_EQ(factory->createAndFillVector(10)->size(), 10u);
}

TEST_F(VectorFactoryBuilderTest, AllDecoratorsStackCorrectly) {
    auto factory = builder
        .withStrategy(container::Strategy::Sequential)
        .enableLogging()
        .enableSecurity()
        .withBenchmark(std::make_unique<time::StopwatchImpl>())
        .build(makeMTFactory());
    EXPECT_EQ(factory->createAndFillVector(10)->size(), 10u);
}

// ============================================================
// Builder reuse
// ============================================================

TEST_F(VectorFactoryBuilderTest, BuilderCanBuildMultipleTimes) {
    builder.withStrategy(container::Strategy::Sequential);

    auto f1 = builder.build(makeMTFactory());
    auto f2 = builder.build(makeMTFactory());

    EXPECT_EQ(f1->createAndFillVector(10)->size(), 10u);
    EXPECT_EQ(f2->createAndFillVector(20)->size(), 20u);
}
