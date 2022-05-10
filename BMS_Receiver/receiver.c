#include <stdio.h>
#include "receiver.h"
#include "math.h"
#include <stdlib.h>
#include <string.h>

void ReadBMSParametersfromConsole(float* Temp,float* SOC , int TotalSamples)
{
  char ReadString[250];
  
  for(int i=0; i<TotalSamples ; i++)
    {
	    if(scanf("%50s", ReadString) == EOF) 
       {
            break;
        }
        scanf("%f",&Temp[i]);
        scanf("%20s", ReadString); //deg
        scanf("%20s", ReadString); //C 
        scanf("%20s", ReadString); //,
        scanf("%f",&SOC[i]);
	  printf("%.3f \t %.3f\n",Temp[i],SOC[i]);
    }
}
