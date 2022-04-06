#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "sender.hpp"

std::vector<SensorParameters> test_parameters = {{100.0,55.0,5.0},{25.0,30.0,3.0}};

TEST_CASE("Check that the data generated is within range"){
  Sender sender(test_parameters);
  SenderTester tester;
  std::vector<Sensor> all_data = tester.Get_core_data(sender);
  REQUIRE(all_data.size() == test_parameters.size());
  for(int i = 0; i < all_data.size(); i++){
    for(int j = 0; j < all_data.at(i)._data_array.size();j++){
      //Check lower limit
      REQUIRE(all_data.at(i)._data_array.at(j) >= (-test_parameters.at(i).range/2+test_parameters.at(i).offset-test_parameters.at(i).noise_STDDEV));
      //Check upper limit
      REQUIRE(all_data.at(i)._data_array.at(j) <= (test_parameters.at(i).range/2+test_parameters.at(i).offset+test_parameters.at(i).noise_STDDEV));
    }
  }
}

TEST_CASE("Check that the correct interface(2 Battery/Charging parameters) is used in the output stream"){
  std::ostringstream streambuffer;
  std::streambuf* Original_COUT = std::cout.rdbuf(streambuffer.rdbuf());
  Sender sender;
  sender.Send_Data_to_Stream();
  std::string streamoutput = streambuffer.str();
  size_t findstart = streamoutput.find("START");
  size_t findend = streamoutput.find("END");
  REQUIRE(findstart != std::string::npos);
  REQUIRE(findend != std::string::npos);
  int countsensorseparations = 0;
  int countdataseparations = -1;//because the'\n' at the end of word "START" doesnt count
  for(size_t index = findstart+1; index < findend; index++){
    if(streamoutput.at(index) == '\n') countdataseparations++;
    if(streamoutput.at(index) == '|') countsensorseparations++;
  }
  REQUIRE(countdataseparations == 50);
  REQUIRE(countsensorseparations == 50);
  std::cout.rdbuf(Original_COUT);
}

TEST_CASE("Check that it sends extactly 50 pairs of parameters(for this exercise)"){
  Sender sender(test_parameters);
  SenderTester tester;
  std::vector<Sensor> all_data = tester.Get_core_data(sender);
  for(auto&& SENSOR : all_data){
    REQUIRE(SENSOR._data_array.size()==50);
  }
}

TEST_CASE("Check that it can use a read from file option"){
  Sender sender("Input_example.txt");
  SenderTester tester;
  std::vector<Sensor> all_data = tester.Get_core_data(sender);
  REQUIRE(all_data.size() == 2);
  for(auto&& SENSOR : all_data){
    //check that inner data is correctly populated
    REQUIRE(SENSOR._data_array.size()==50);
  }
}
