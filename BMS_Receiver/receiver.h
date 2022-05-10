void ReadInputfromConsole(float* Temp,float* Voltage , int SampleCount);
float FindMininimumSample(float* BMSParameterInput , int SampleCount);
float FindMaximumSample(float* BMSParameterInput , int SampleCount);                       
float FindSampleAverage(float* BMSParameterInput, int TotalSamples);                       
void CalculateSMA(float *InputData, int windowsize, float *movingAvg);                   
void PrintMinMaxValues(float* Temp, float* SOC, int TotalSamples) ;
