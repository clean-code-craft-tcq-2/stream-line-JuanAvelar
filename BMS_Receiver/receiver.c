#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "receiver.h"
#include "math.h"

void ReadInputfromConsole(float* Temp,float* Voltage , int SampleCount)
{
  char ReadString[250];
  
  for(int i=0; i<SampleCount ; i++)
    {
	    if(scanf("%50s", ReadString) == EOF) 
       {
            break;
        }
        scanf("%f",&Temp[i]);
        scanf("%20s", ReadString); //deg
        scanf("%20s", ReadString); //C 
        scanf("%20s", ReadString); //,
        scanf("%f",&Voltage[i]);
	  printf("%.3f \t %.3f\n",Temp[i],Voltage[i]);
    }
}

float FindMininimumSample(float* InputData, int SampleCount)
{
  float MinValue = InputData[0];
    for(int i=1; i<TotalSamples; i++)
    {
        if(MinValue > InputData[i])
        {
            MinValue = InputData[i];
        }
    }
    return MinValue;
}



float FindMaximumSample(float* InputData, int SampleCount)
{
  float MaxValue = InputData[0];
    for(int i=1; i<TotalSamples; i++)
    {
        if(MaxValue < InputData[i])
        {
            MaxValue = InputData[i];
        }
    }
    return MaxValue;
}
                        

float FindSampleAverage(float* InputData, int SampleCount)
{
    float Avg = 0;
    float Sum = 0;
    for(int i = 0; i < TotalSamples; i++)
    {
        Sum = Sum + InputData[i];
    }
	    Avg = Sum/TotalSamples;
    return Avg;
}

			
void CalculateSMA(float *InputData, int windowsize, float *MovingAvg)
{
     float Sum = 0;
     for (int i = 0; i < 50; i++) 
     {
         Sum = Sum + InputData[i];
         if (i >= windowsize)
	 {
	     Sum -= InputData[i-windowsize];
	 }
	 if(i >= windowsize - 1)
	 {
            MovingAvg[i-windowsize] = Sum/windowsize;
	 }
     }
}
			
	
void PrintMinMaxValues(float* Temp, float* SOC, int TotalSamples) 
{
  float mintemp, maxtemp, minSOC, maxSOC;
  mintemp = CalculateMinValue(Temp, TotalSamples);
  maxtemp = CalculateMaxValue(Temp, TotalSamples);
  minSOC = CalculateMinValue(SOC, TotalSamples);
  maxSOC = CalculateMaxValue(SOC, TotalSamples);
  printf("min current: %f max current: %f min voltage: %f max voltage: %f\n", mintemp, maxtemp, minSOC, maxSOC);
}
