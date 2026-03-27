#include "gtest/gtest.h"
#include "atlas/generator/IGeneratorFactory.h"
#include "atlas/generator/IGenerator.h"
#include "atlas/generator/impl/generic/GenericGeneratorImpl.h"
#include "atlas/container/impl/sequential/VectorFactorySequentialImpl.h"
#include "atlas/container/impl/parallel/VectorFactoryAutoImpl.h"
#include "atlas/container/impl/parallel/VectorFactoryParallelImpl.h"
#include "atlas/container/impl/parallel/VectorFactoryThreadpoolImpl.h"
#include "atlas/container/impl/parallel/VectorFactoryThreadpoolLoopImpl.h"

using namespace atlas;

// ============================================================
// Test helper: generator factory that always returns a fixed value
// ============================================================

class ConstantGeneratorFactory : public generator::IGeneratorFactory<int> {
    int value_;
public:
    explicit ConstantGeneratorFactory(int value) : value_{value} {}

    [[nodiscard]] auto create() const -> std::unique_ptr<generator::IGenerator<int>> override {
        return std::make_unique<generator::GenericGeneratorImpl>(value_, [](int v) { return v; });
    }
};

auto makeConstantFactory(int value = 42) {
    return std::make_unique<ConstantGeneratorFactory>(value);
}

// ============================================================
// VectorFactorySequentialImpl
// ============================================================

class VectorFactorySequentialImplTest : public ::testing::Test {
protected:
    container::VectorFactorySequentialImpl<int> factory{makeConstantFactory(42)->create()};
};

TEST_F(VectorFactorySequentialImplTest, ReturnsNonNull) {
    EXPECT_NE(factory.createAndFillVector(10), nullptr);
}

TEST_F(VectorFactorySequentialImplTest, ReturnsCorrectSize) {
    EXPECT_EQ(factory.createAndFillVector(100)->size(), 100u);
}

TEST_F(VectorFactorySequentialImplTest, FillsAllElementsWithGeneratedValue) {
    auto result = factory.createAndFillVector(10);
    for (int v : *result) EXPECT_EQ(v, 42);
}

TEST_F(VectorFactorySequentialImplTest, EmptySizeReturnsEmptyVector) {
    EXPECT_TRUE(factory.createAndFillVector(0)->empty());
}

// ============================================================
// VectorFactoryAutoImpl
// ============================================================

class VectorFactoryAutoImplTest : public ::testing::Test {
protected:
    container::VectorFactoryAutoImpl<int> factory{makeConstantFactory(7)};
};

TEST_F(VectorFactoryAutoImplTest, ReturnsNonNull) {
    EXPECT_NE(factory.createAndFillVector(10), nullptr);
}

TEST_F(VectorFactoryAutoImplTest, ReturnsCorrectSize) {
    EXPECT_EQ(factory.createAndFillVector(100)->size(), 100u);
}

TEST_F(VectorFactoryAutoImplTest, FillsAllElementsWithGeneratedValue) {
    auto result = factory.createAndFillVector(50);
    for (int v : *result) EXPECT_EQ(v, 7);
}

// ============================================================
// VectorFactoryParallelImpl
// ============================================================

class VectorFactoryParallelImplTest : public ::testing::Test {
protected:
    container::VectorFactoryParallelImpl<int> factory{makeConstantFactory(99), 4};
};

TEST_F(VectorFactoryParallelImplTest, ReturnsNonNull) {
    EXPECT_NE(factory.createAndFillVector(10), nullptr);
}

TEST_F(VectorFactoryParallelImplTest, ReturnsCorrectSize) {
    EXPECT_EQ(factory.createAndFillVector(100)->size(), 100u);
}

TEST_F(VectorFactoryParallelImplTest, FillsAllElementsWithGeneratedValue) {
    auto result = factory.createAndFillVector(100);
    for (int v : *result) EXPECT_EQ(v, 99);
}

TEST_F(VectorFactoryParallelImplTest, SingleThreadFallback) {
    container::VectorFactoryParallelImpl<int> singleThread{makeConstantFactory(1), 0};
    EXPECT_EQ(singleThread.createAndFillVector(10)->size(), 10u);
}

// ============================================================
// VectorFactoryThreadpoolImpl
// ============================================================

class VectorFactoryThreadpoolImplTest : public ::testing::Test {
protected:
    container::VectorFactoryThreadpoolImpl<int> factory{makeConstantFactory(55), 4};
};

TEST_F(VectorFactoryThreadpoolImplTest, ReturnsNonNull) {
    EXPECT_NE(factory.createAndFillVector(10), nullptr);
}

TEST_F(VectorFactoryThreadpoolImplTest, ReturnsCorrectSize) {
    EXPECT_EQ(factory.createAndFillVector(100)->size(), 100u);
}

TEST_F(VectorFactoryThreadpoolImplTest, FillsAllElementsWithGeneratedValue) {
    auto result = factory.createAndFillVector(100);
    for (int v : *result) EXPECT_EQ(v, 55);
}

TEST_F(VectorFactoryThreadpoolImplTest, EmptySizeReturnsEmptyVector) {
    EXPECT_TRUE(factory.createAndFillVector(0)->empty());
}

// ============================================================
// VectorFactoryThreadpoolLoopImpl
// ============================================================

class VectorFactoryThreadpoolLoopImplTest : public ::testing::Test {
protected:
    container::VectorFactoryThreadpoolLoopImpl<int> factory{makeConstantFactory(33), 4};
};

TEST_F(VectorFactoryThreadpoolLoopImplTest, ReturnsNonNull) {
    EXPECT_NE(factory.createAndFillVector(10), nullptr);
}

TEST_F(VectorFactoryThreadpoolLoopImplTest, ReturnsCorrectSize) {
    EXPECT_EQ(factory.createAndFillVector(100)->size(), 100u);
}

TEST_F(VectorFactoryThreadpoolLoopImplTest, FillsAllElementsWithGeneratedValue) {
    auto result = factory.createAndFillVector(100);
    for (int v : *result) EXPECT_EQ(v, 33);
}

TEST_F(VectorFactoryThreadpoolLoopImplTest, EmptySizeReturnsEmptyVector) {
    EXPECT_TRUE(factory.createAndFillVector(0)->empty());
}
