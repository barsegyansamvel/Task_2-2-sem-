#include "ClassDeque.h"

#include <gtest/gtest.h>

#include <limits>
#include <stdexcept>
#include <utility>

TEST(DequeTests, DefaultConstructorCreatesEmptyDeque)
{
    const Deque deque;
    EXPECT_TRUE(deque.empty());
    EXPECT_EQ(deque.toString(), "{}");
}

TEST(DequeTests, InitializerListPreservesElementOrder)
{
    const Deque deque{1, 2, 3};
    EXPECT_FALSE(deque.empty());
    EXPECT_EQ(deque.front(), 1);
    EXPECT_EQ(deque.back(), 3);
    EXPECT_EQ(deque.toString(), "{1, 2, 3}");
}

TEST(DequeTests, PushBackAppendsElement)
{
    Deque deque{1, 2};
    deque.push_back(3);
    EXPECT_EQ(deque.toString(), "{1, 2, 3}");
    EXPECT_EQ(deque.back(), 3);
}

TEST(DequeTests, PushFrontPrependsElement)
{
    Deque deque{2, 3};
    deque.push_front(1);
    EXPECT_EQ(deque.toString(), "{1, 2, 3}");
    EXPECT_EQ(deque.front(), 1);
}

TEST(DequeTests, BothPushOperationsWorkOnEmptyDeque)
{
    Deque first;
    first.push_front(7);
    EXPECT_EQ(first.front(), 7);
    EXPECT_EQ(first.back(), 7);

    Deque second;
    second.push_back(9);
    EXPECT_EQ(second.front(), 9);
    EXPECT_EQ(second.back(), 9);
}

TEST(DequeTests, PopBackReturnsAndRemovesLastElement)
{
    Deque deque{1, 2, 3};
    EXPECT_EQ(deque.pop_back(), 3);
    EXPECT_EQ(deque.toString(), "{1, 2}");
    EXPECT_EQ(deque.back(), 2);
}

TEST(DequeTests, PopFrontReturnsAndRemovesFirstElement)
{
    Deque deque{1, 2, 3};
    EXPECT_EQ(deque.pop_front(), 1);
    EXPECT_EQ(deque.toString(), "{2, 3}");
    EXPECT_EQ(deque.front(), 2);
}

TEST(DequeTests, RemovingOnlyElementLeavesReusableEmptyDeque)
{
    Deque deque{5};
    EXPECT_EQ(deque.pop_front(), 5);
    EXPECT_TRUE(deque.empty());
    deque.push_back(8);
    EXPECT_EQ(deque.pop_back(), 8);
    EXPECT_TRUE(deque.empty());
    deque.push_front(9);
    EXPECT_EQ(deque.toString(), "{9}");
}

TEST(DequeTests, FrontAndBackDoNotRemoveElements)
{
    const Deque deque{4, 5, 6};
    EXPECT_EQ(deque.front(), 4);
    EXPECT_EQ(deque.back(), 6);
    EXPECT_EQ(deque.toString(), "{4, 5, 6}");
}

TEST(DequeTests, EmptyDequeRejectsReadingAndRemoving)
{
    Deque deque;
    EXPECT_THROW(deque.front(), std::out_of_range);
    EXPECT_THROW(deque.back(), std::out_of_range);
    EXPECT_THROW(deque.pop_front(), std::out_of_range);
    EXPECT_THROW(deque.pop_back(), std::out_of_range);
    EXPECT_TRUE(deque.empty());
}

TEST(DequeTests, CopyConstructorCreatesIndependentCopy)
{
    Deque original{1, 2, 3};
    Deque copy(original);
    original.pop_front();
    copy.push_back(4);
    EXPECT_EQ(original.toString(), "{2, 3}");
    EXPECT_EQ(copy.toString(), "{1, 2, 3, 4}");
}

TEST(DequeTests, CopyAssignmentReplacesContentAndCreatesIndependentCopy)
{
    Deque original{1, 2};
    Deque copy{9, 8, 7};
    copy = original;
    original.pop_back();
    EXPECT_EQ(original.toString(), "{1}");
    EXPECT_EQ(copy.toString(), "{1, 2}");
}

TEST(DequeTests, SelfCopyAssignmentPreservesContent)
{
    Deque deque{1, 2, 3};
    deque = deque;
    EXPECT_EQ(deque.toString(), "{1, 2, 3}");
}

TEST(DequeTests, MoveConstructorTransfersContentAndLeavesSourceReusable)
{
    Deque original{1, 2, 3};
    const Deque moved(std::move(original));
    EXPECT_EQ(moved.toString(), "{1, 2, 3}");
    EXPECT_TRUE(original.empty());
    original.push_front(5);
    EXPECT_EQ(original.toString(), "{5}");
}

TEST(DequeTests, MoveAssignmentReplacesContentAndEmptiesSource)
{
    Deque original{1, 2};
    Deque moved{9, 8, 7};
    moved = std::move(original);
    EXPECT_EQ(moved.toString(), "{1, 2}");
    EXPECT_TRUE(original.empty());
    original.push_back(5);
    EXPECT_EQ(original.back(), 5);
}

TEST(DequeTests, SelfMoveAssignmentPreservesContent)
{
    Deque deque{1, 2, 3};
    Deque& same = deque;
    deque = std::move(same);
    EXPECT_EQ(deque.toString(), "{1, 2, 3}");
}

TEST(DequeTests, CopyingAndMovingEmptyDequeWorks)
{
    const Deque empty;
    Deque copy(empty);
    Deque moved(std::move(copy));
    EXPECT_TRUE(copy.empty());
    EXPECT_TRUE(moved.empty());

    Deque target{1, 2};
    target = empty;
    EXPECT_TRUE(target.empty());
    target.push_back(5);
    target = std::move(moved);
    EXPECT_TRUE(target.empty());
    EXPECT_TRUE(moved.empty());
}

TEST(DequeTests, ToStringSupportsNegativeZeroAndExtremeIntegers)
{
    const Deque deque{std::numeric_limits<int>::min(), 0,
                      std::numeric_limits<int>::max()};
    EXPECT_EQ(deque.toString(),
              "{" + std::to_string(std::numeric_limits<int>::min())
              + ", 0, " + std::to_string(std::numeric_limits<int>::max()) + "}");
}

TEST(DequeTests, LeftShiftAddsToEnd)
{
    Deque deque{1};
    deque << 2 << 3;
    EXPECT_EQ(deque.toString(), "{1, 2, 3}");
}

TEST(DequeTests, RightShiftExtractsFromBeginning)
{
    Deque deque{1, 2};
    int first = 0;
    int second = 0;
    deque >> first >> second;
    EXPECT_EQ(first, 1);
    EXPECT_EQ(second, 2);
    EXPECT_TRUE(deque.empty());
    EXPECT_THROW(deque >> first, std::out_of_range);
}
