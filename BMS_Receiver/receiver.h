void ReadInputfromConsole(float* Temp,float* Voltage , int SampleCount);
float FindMininimumSample(float* InputData , int SampleCount);
float FindMaximumSample(float* InputData , int SampleCount);                       
float FindSampleAverage(float* InputData, int TotalSamples);                       
void CalculateSMA(float *InputData, int windowsize, float *movingAvg);                   
void PrintMinMaxValues(float* Temp, float* SOC, int TotalSamples) ;
