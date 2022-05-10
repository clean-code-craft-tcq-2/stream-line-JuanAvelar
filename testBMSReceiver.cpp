#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "test/catch.hpp"
#include "receiver/receiver.h"
#include <string.h>
#include <stdio.h>

TEST_CASE("Test for finding Max , Min and Avg value for temp") 
{
  float temp[5]= {2, 5, 10, 15, 20};
  float Max = FindMaximumSample(temp, 5);
  float Min = FindMininimumSample(temp, 5);
  float Avg = CalculateAvg(temp , 5);
  REQUIRE(Max == 20);
  REQUIRE(Min == 2);
  REQUIRE( abs(Avg - 10.4f ) <=0.001);
}

TEST_CASE("Test for finding Max , Min and Avg value for SOC") 
{
  float Voltage[5]= {5, 5, 10, 5, 10};
  float Max = CalculateMaxValue(Voltage, 5);
  float Min = CalculateMinValue(Voltage, 5);
  float Avg = CalculateAvg(Voltage , 5);
  REQUIRE(Max == 10);
  REQUIRE(Min == 5);
  REQUIRE(Avg==7);
}
