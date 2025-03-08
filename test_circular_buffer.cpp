#include <gtest/gtest.h>
extern "C" 
{
#include "circular_buffer.h"
}

// Test Initialization: buffer should be created empty.
TEST(CircularBufferTest, Initialization) 
{
    size_t capacity = 5;
    CircularBuffer *cb = cb_init(capacity);
    ASSERT_NE(cb, nullptr);
    EXPECT_EQ(cb_size(cb), 0u);
    EXPECT_TRUE(cb_is_empty(cb));
    cb_free(cb);
}

// Test basic add and remove operations.
TEST(CircularBufferTest, AddRemoveElements) 
{
    size_t capacity = 3;
    CircularBuffer *cb = cb_init(capacity);
    ASSERT_NE(cb, nullptr);
    
    // Add single element.
    cb_add(cb, 75);
    EXPECT_EQ(cb_size(cb), 1u);
    EXPECT_FALSE(cb_is_empty(cb));
    EXPECT_FALSE(cb_is_full(cb));
    
    // Remove and check the element.
    int value;
    EXPECT_EQ(cb_remove(cb, &value), 0);
    EXPECT_EQ(value, 75);
    EXPECT_EQ(cb_size(cb), 0u);
    EXPECT_TRUE(cb_is_empty(cb));
    
    cb_free(cb);
}

// Test buffer overwriting when full.
TEST(CircularBufferTest, OverwriteWhenFull) 
{
    size_t capacity = 3;
    CircularBuffer *cb = cb_init(capacity);
    ASSERT_NE(cb, nullptr);
    
    cb_add(cb, 100);
    cb_add(cb, 110);
    cb_add(cb, 120);
    
    EXPECT_EQ(cb_size(cb), capacity);
    EXPECT_TRUE(cb_is_full(cb));
    
    // Add one more element to force overwriting.
    cb_add(cb, 130);
    EXPECT_EQ(cb_size(cb), capacity);
    
    // The oldest element (100) should be overwritten.
    int value;
    EXPECT_EQ(cb_remove(cb, &value), 0);
    EXPECT_EQ(value, 110); // Expected order: 110, 120, 130.
    
    cb_free(cb);
}

// Test compute EMA with known values.
// Using alpha = 0.5 we can easily check the calculation.
// For input values: 80, 90, 100:
// EMA calculations:
//   ema0 = 80
//   ema1 = 0.5*90 + 0.5*80 = 85
//   ema2 = 0.5*100 + 0.5*85 = 92.5
TEST(CircularBufferTest, ComputeEMA) 
{
    size_t capacity = 5;
    CircularBuffer *cb = cb_init(capacity);
    ASSERT_NE(cb, nullptr);
    
    cb_add(cb, 80);
    cb_add(cb, 90);
    cb_add(cb, 100);
    
    double ema = compute_ema(cb, 0.5);
    EXPECT_NEAR(ema, 92.5, 0.01);
    
    cb_free(cb);
}

// Test removal when the buffer is empty.
TEST(CircularBufferTest, RemoveFromEmptyBuffer) 
{
    size_t capacity = 3;
    CircularBuffer *cb = cb_init(capacity);
    ASSERT_NE(cb, nullptr);
    
    int dummy;
    EXPECT_EQ(cb_remove(cb, &dummy), -1);
    
    cb_free(cb);
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
