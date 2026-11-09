#include "Point.h"
#include "PiecewiseLinearApproximation.h"
#include "Segment.h"

#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <vector>

TEST(SegmentTests, CopiesLeftPointAndUsesItsYForRightPoint)
{
    const Segment segment(Point(1, 5), Point(4, 99));
    EXPECT_EQ(segment.getLeftPoint(), Point(1, 5));
    EXPECT_EQ(segment.getRightPoint(), Point(4, 5));
}

TEST(SegmentTests, SignalIsConstantAcrossTheSegment)
{
    const Segment segment(Point(1, 5), Point(4, 0));
    EXPECT_DOUBLE_EQ(segment.getY(1), 5);
    EXPECT_DOUBLE_EQ(segment.getY(2.5), 5);
    EXPECT_DOUBLE_EQ(segment.getY(4), 5);
}

TEST(SegmentTests, RejectsAbscissaOutsideSegment)
{
    const Segment segment(Point(1, 5), Point(4, 0));
    EXPECT_THROW(segment.getY(0.99), std::out_of_range);
    EXPECT_THROW(segment.getY(4.01), std::out_of_range);
}

TEST(SegmentTests, RejectsRightPointBeforeLeftPoint)
{
    EXPECT_THROW((Segment(Point(4, 5), Point(1, 9))), std::invalid_argument);
}

TEST(SegmentTests, StaticReadReadsBothPointsUsingPointExtraction)
{
    std::istringstream input("1 5 4 99");
    const Segment segment = Segment::Read(input);
    EXPECT_EQ(segment.getLeftPoint(), Point(1, 5));
    EXPECT_EQ(segment.getRightPoint(), Point(4, 5));
}

TEST(SegmentTests, LeftShiftOperatorWritesSegmentToStream)
{
    const Segment segment(Point(1, 5), Point(4, 0));
    std::ostringstream output;
    output << segment;
    EXPECT_EQ(output.str(), "[1 5; 4 5]");
}

TEST(PointTests, StreamOperatorsRoundTripCoordinates)
{
    Point point;
    std::istringstream input("2.5 -3");
    input >> point;
    EXPECT_EQ(point, Point(2.5, -3));

    std::ostringstream output;
    output << point;
    EXPECT_EQ(output.str(), "2.5 -3");
}

TEST(PiecewiseApproximationTests, CanBeConstructedFromVector)
{
    const std::vector<Point> points{Point(0, 2), Point(3, 4)};
    const PiecewiseLinearApproximation approximation(points);
    EXPECT_EQ(approximation.GetPoints().size(), 2U);
}

TEST(PiecewiseApproximationTests, CanBeConstructedFromInitializerList)
{
    const PiecewiseLinearApproximation approximation{
        Point(0, 2), Point(3, 4)
    };
    EXPECT_EQ(approximation.GetPoints().front(), Point(0, 2));
}

TEST(PiecewiseApproximationTests, AddPointAppendsAnIncreasingAbscissa)
{
    PiecewiseLinearApproximation approximation{
        Point(0, 2), Point(3, 4)
    };
    approximation.AddPoint(Point(5, 6));
    EXPECT_EQ(approximation.GetPoints().size(), 3U);
    EXPECT_THROW(approximation.AddPoint(Point(4, 7)), std::invalid_argument);
}

TEST(PiecewiseApproximationTests, ReadPointsReadsRequestedNumberOfPoints)
{
    std::istringstream input("0 2 3 4");
    const std::vector<Point> points =
        PiecewiseLinearApproximation::ReadPoints(input, 2);
    EXPECT_EQ(points[0], Point(0, 2));
    EXPECT_EQ(points[1], Point(3, 4));
}

TEST(SegmentTests, UsesCompositionInsteadOfInheritingTheBase)
{
    EXPECT_FALSE((std::is_base_of_v<PiecewiseLinearApproximation, Segment>));
}

TEST(PiecewiseApproximationTests, HoldsPreviousPointValueUntilNextKnot)
{
    const PiecewiseLinearApproximation approximation{
        Point(1, 5), Point(4, 5), Point(6, 9)
    };

    EXPECT_DOUBLE_EQ(approximation.getY(1), 5);
    EXPECT_DOUBLE_EQ(approximation.getY(5), 5);
    EXPECT_DOUBLE_EQ(approximation.getY(6), 9);
}
