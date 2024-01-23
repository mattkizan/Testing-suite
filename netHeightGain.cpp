#include <boost/test/unit_test.hpp>

#include "types.h"
#include "waypoints.h"
#include "analysis-route.h"
#include <math.h>
using namespace GPS;
BOOST_AUTO_TEST_SUITE(netHeightGain)


const Position pos1 = Position(10,1,1.25);
const Position pos2 = Position(20,2,1.99);
const Position pos3 = Position(30,3,3.30);
const Position pos4 = Position(40,4,2.00);
const Position pos5 = Position(50,5,-5.80);
const Position pos6 = Position(50,5,0);

const RoutePoint rtpt1 = { pos1, "P1" };
const RoutePoint rtpt2 = { pos2, "P2" };
const RoutePoint rtpt3 = { pos3, "P3" };
const RoutePoint rtpt4 = { pos4, "P2" };
const RoutePoint rtpt5= { pos5, "P3" };
const RoutePoint rtpt6= { pos6, "P3" };

// this test suite tests the net height gain function. the net height gain function reutrns the difference by subtracting the route point value of the start point
// from the routpoint value of the last point. if the difference is negative, it will return zero, if the difference is postive it will return the difference.
// the function should throw a domain error if vector contains no route points/is empty

 //Typical case: checks if the function returns evelation if the net height is above zero
BOOST_AUTO_TEST_CASE( typicalInput_Net_Positive )
{
    const std::vector<RoutePoint> routePoints = { rtpt1, rtpt2,rtpt4,rtpt6, rtpt3 };
    const Analysis::Route route {routePoints};
    const double expectedElevation = 2.05;

   double actualNumPoints = route.netHeightGain();


    BOOST_REQUIRE_CLOSE( actualNumPoints , expectedElevation, 0.0001 );

}

//Typical case: checks if the function rerturns zero if the net height is negative
BOOST_AUTO_TEST_CASE( typicalInput_Net_Negative )
{
    const std::vector<RoutePoint> routePoints = { rtpt1, rtpt2, rtpt5 };
    const Analysis::Route route {routePoints};

    const double expectedElevation = 0.00;

    double actualNumPoints = route.netHeightGain();

    BOOST_REQUIRE_CLOSE( actualNumPoints , expectedElevation, 0.0001 );
}

//Error case : tests if the the function will throw a domain error if there are no route points in the vector
BOOST_AUTO_TEST_CASE( errorCase )
{
    const std::vector<RoutePoint> routePoints = { };
    const Analysis::Route route {routePoints};

    BOOST_CHECK_THROW( route.netHeightGain(), std::domain_error);

}

// edge case: checks if the functions correct output, if there is only one route point in the list.
BOOST_AUTO_TEST_CASE( edgeCase )
{
    const std::vector<RoutePoint> routePoints = { rtpt3};
    const Analysis::Route route {routePoints};
     const double expectedElevation = 0.00;

     double actualNumPoints = route.netHeightGain();

     BOOST_REQUIRE_CLOSE( actualNumPoints , expectedElevation, 0.0001 );


}

//corner case: checks if the function returns correct output if there is only one element with the value of zero in the vector
BOOST_AUTO_TEST_CASE( CornerCase )
{
    const std::vector<RoutePoint> routePoints = { rtpt6};
    const Analysis::Route route {routePoints};
     const double expectedElevation = 0;

     double actualNumPoints = route.netHeightGain();

       BOOST_REQUIRE_CLOSE( actualNumPoints , expectedElevation, 0.0001 );

}

// corner case : checks if the function returns correct output if the vector only contins zero values
BOOST_AUTO_TEST_CASE( CornerCase_withRepeatedZeroValues )
{
    const std::vector<RoutePoint> routePoints = { rtpt6, rtpt6, rtpt6, rtpt6,rtpt6};
    const Analysis::Route route {routePoints};
     const double expectedElevation = 0;

     double actualNumPoints = route.netHeightGain();

    BOOST_REQUIRE_CLOSE( actualNumPoints , expectedElevation, 0.0001 );

}

// corner case: when the start and last route points are the same

BOOST_AUTO_TEST_CASE( cornerCase )
{
    const std::vector<RoutePoint> routePoints = { rtpt3, rtpt2,rtpt6,rtpt5, rtpt3 };
    const Analysis::Route route {routePoints};
    const double expectedElevation = 0;

   double actualNumPoints = route.netHeightGain();


    BOOST_REQUIRE_CLOSE( actualNumPoints , expectedElevation, 0.0001 );

}

//boundary case: checks if the output is -0.01, the program returns zero as it is  still a negative
BOOST_AUTO_TEST_CASE( boundaryCase )
{
    const std::vector<RoutePoint> routePoints = { rtpt4,rtpt2};
    const Analysis::Route route {routePoints};


   double actualNumPoints = route.netHeightGain();

   BOOST_CHECK_SMALL(actualNumPoints,0.01);


}

// boundary case: chceks the boundary( zero) to see if the program returnms zero
BOOST_AUTO_TEST_CASE( boundaryCase2 )
{
    const std::vector<RoutePoint> routePoints = { rtpt4};
    const Analysis::Route route {routePoints};


   double actualNumPoints = route.netHeightGain();

   BOOST_CHECK_SMALL(actualNumPoints,0.01);



}


BOOST_AUTO_TEST_SUITE_END()
