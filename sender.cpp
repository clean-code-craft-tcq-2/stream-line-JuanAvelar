#include "sender.hpp"
#include <fstream>
#include <math.h>
#include <random>
// #include <functional>
#include <chrono>
/*Each instance of a data packet should have all sensor intances in the same line
  separated by a '|' character
*/
#define PI 3.14159265

Sender::Sender(void){
  this->generate_data(2, 50);
}

Sender::Sender(std::vector<SensorParameters> parameters){
  this->generate_data(parameters.size(), 50, parameters);
}

Sender::Sender(std::string input_file){
  std::ifstream in_stream_file;
  in_stream_file.open(input_file, std::ifstream::in);
  if(in_stream_file.is_open()){
    this->parse_input_file(in_stream_file);
    _amount_of_sensors = _data_sensors.size();
  }else{
    std::cerr << "The file to read input could not be open\n";
  }
}

void Sender::parse_input_file(std::ifstream & in){
  std::string number;
  char letter;
  unsigned char sensor_index = 0;
  _data_sensors.push_back(Sensor());//at least 1 sensor in the data
  _amount_of_data_per_sensor = 0;
  bool data_retrieved_is_valid = false;
  while(in.get(letter)){
    // std::cout << letter;
    if(letter == sensor_separator){
      if(_data_sensors.size() < sensor_index + 2){_data_sensors.push_back(Sensor());}
      if(data_retrieved_is_valid){
        // std::cout <<"number:" <<number << std::endl;
        _data_sensors.at(sensor_index)._data_array.push_back(std::stof(number));
        sensor_index++;
      }
      number.clear();
    }
    else if(letter == data_separator){
      if(number == std::string("END")) data_retrieved_is_valid = false;
      if(data_retrieved_is_valid){
        // std::cout <<"number:" <<number << std::endl;
        _data_sensors.at(sensor_index)._data_array.push_back(std::stof(number));
        _amount_of_data_per_sensor++;
      }
      if(number == std::string("START")) data_retrieved_is_valid = true;
      sensor_index = 0;
      number.clear();
    }
    else{
      number.push_back(letter);
    }
  }
}

void Sender::generate_data(size_t HowManySensors, size_t HowManyData, std::vector<SensorParameters> parameters){
  float range = 100.0;
  float mean = 50.0;
  float noise = 5.0;
  if(parameters.empty()){
    _amount_of_sensors = HowManySensors;
  }else{
    _amount_of_sensors = parameters.size();
  }
  _amount_of_data_per_sensor = HowManyData;
  for(int sensors = 0; sensors < _amount_of_sensors; sensors++){
    Sensor mysensorObject;
    if(!parameters.empty()){
      range = parameters.at(sensors).range;
      mean = parameters.at(sensors).offset;
      noise = parameters.at(sensors).noise_STDDEV;
    }
    mysensorObject.generate_new_sine(_amount_of_data_per_sensor, range, mean, noise);
    _data_sensors.push_back(mysensorObject);
  }
  // for(auto&& S : _data_sensors) std::cout << "Size of sensor array : " << S._data_array.size() << std::endl;
}

void Sensor::generate_new_sine(size_t HowMany, float range, float offset, float noise_std_dev){
  const float ratio_to_complete_sine = 360/HowMany;
  const float mean = 0.0;
  //introducing noise to the signal
  std::random_device dev;
  //the next line is to generate true random noise across all sensors
  static size_t seed_offset = 0;//offset applied if the timestamp gets too close with each other between two sensors
  std::mt19937::result_type seed = dev() ^ (
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now().time_since_epoch()
                ).count() +
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()
              ).count() ) + seed_offset++;
  std::mt19937 generator(seed);
  std::normal_distribution<float> dist(mean, noise_std_dev);
  for(int data = 0; data < HowMany; data++){
    float noise = dist(generator);
    _data_array.push_back(((sin(ratio_to_complete_sine*data*PI/180)*range/2) + offset) + noise);
    if(_data_array.back() < (-range/2+offset-noise_std_dev)) _data_array.back() = (-range/2+offset-noise_std_dev);
    if(_data_array.back() > (range/2+offset+noise_std_dev)) _data_array.back() = (range/2+offset+noise_std_dev);
    //std::cout << data+1 << ", data: " << _data_array.back() << ", noise:" << noise << std::endl;
  }
}

void Sender::Send_Data_to_Stream(void){
  std::cout << "Sending data to stream\n";
  std::cout << "START\n";
  for(size_t data_count = 0; data_count < _amount_of_data_per_sensor; data_count++){
    for(size_t sensor_count = 0; sensor_count < _amount_of_sensors; sensor_count++){
      std::cout << _data_sensors.at(sensor_count)._data_array.at(data_count);
      if(sensor_count < _amount_of_sensors-1) std::cout << sensor_separator;
    }
    std::cout << data_separator;
  }
  std::cout << "END\n";
}

std::vector<Sensor> SenderTester::Get_core_data(Sender& sender){
  return sender._data_sensors;
}
