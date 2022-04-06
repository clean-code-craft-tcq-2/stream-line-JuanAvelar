#ifndef SENDER_HPP
#define SENDER_HPP
#include <iostream>
#include <vector>
#include <string>

struct Sensor{
  std::vector<float> _data_array;
  void generate_new_sine(size_t HowMany, float range, float offset, float noise_size = 0.0);
};

struct SensorParameters{
  float range;
  float offset;
  float noise_STDDEV;
};

class Sender{
private:
  std::vector<Sensor> _data_sensors;
  void generate_data(size_t HowManySensors, size_t HowManyData, std::vector<SensorParameters> parameters = std::vector<SensorParameters>());
  void parse_input_file(std::ifstream & in);
  const char sensor_separator = '|';
  const char data_separator = '\n';
  size_t _amount_of_sensors;
  size_t _amount_of_data_per_sensor;
public:
  Sender(std::string input_file);
  Sender(void/*No input file*/);
  Sender(std::vector<SensorParameters> parameters);
  void Send_Data_to_Stream(void);
  friend class SenderTester;
};

class SenderTester{
public:
  std::vector<Sensor> Get_core_data(Sender& sender);
};

#endif
