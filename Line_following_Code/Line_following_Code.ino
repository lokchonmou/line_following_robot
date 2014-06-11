//  PID controller
#include <PID_v1.h>
double Setpoint, Input, Output;
PID myPID(&Input, &Output, &Setpoint,30,0,15, DIRECT);

//Arduino PWM Speed Control：
const int E1 = 5;  
const int M1 = 4; 
const int E2 = 6;                      
const int M2 = 7;                        
// variables:
int sensorValue[5] = {0, 0, 0, 0, 0};         // the sensor value
int sensorMin[5] = {1023, 1023, 1023, 1023, 1023};        // minimum sensor value
int sensorMax[5] = {0, 0, 0, 0, 0};           // maximum sensor value
boolean sensor_state[5] = {0, 0, 0, 0, 0};
byte Map = 0;
int error = 0, Last_error = 0;
//-------------------------------------------------------------------------------------------------

void setup() 
{ 
	Serial.begin(9600);  
	pinMode(M1, OUTPUT);   
	pinMode(M2, OUTPUT); 
	Setpoint = 0;
	Input = 0;
	calibration();
	myPID.SetOutputLimits(-510, 510);
	myPID.SetMode(AUTOMATIC);
}   
//-------------------------------------------------------------------------------------------------
void loop() 
{ 
	//  Read the sensor as sensorMap
	Map = 0;
	for (int i = 0; i <= 4; i++)
	{
		if (analogRead(i) < sensorMin[i])
		{
			sensor_state[i] = 0;
		}
		if (analogRead(i) > sensorMax[i])
		{
			sensor_state[i] = 1;
		}
		Map = Map | sensor_state[i];
		Map = Map << 1; 
	}

	Serial.println(Map, BIN);

	//  changle the sensorMap to error
	switch (Map)
	{
	case B1000000:
		error = -5;
		break;
	case B1100000:
		error = -4;
		break;
	case B0100000:
		error = -3;
		break;
	case B0110000:
		error = -2;
		break;
	case B0010000:
		error = -1;
		break;
		// case B0011000:
		// error = 0;
		// break;
	case B0001000:
		error = 1;
		break;
	case B0001100:
		error = 2;
		break;
	case B0000100:
		error = 3;
		break;
	case B0000110:
		error = 4;
		break;
	case B0000010:
		error = 5;
		break;
		/* case 0:
	if (Last_error < 0)
	{
	error = -10;
	}
	else
	{
	error = 10;
	}
	break;  */
		//  special case
	case B1111000:
		error = -6;
		break;
	case B1110000:
		error = -7;
		break;
	case B0001110:
		error = 7;
		break;
	case B0011110:
		error = 6;
		break; 
	}

	Last_error = error;

	// control the motor speed


	Input = error;
	myPID.Compute();
	if (Output<0)
	{
		if (Output >= -255)
		{
			digitalWrite(M2, HIGH);
			analogWrite(E2, 255+int(Output));
			//Serial.print("R");
			// Serial.println(255+int(Output));
		}
		else
		{
			digitalWrite(M2, LOW);
			analogWrite(E2, -255-int(Output));
			//Serial.print("R-");
			//Serial.println(-255-int(Output));
		}
		digitalWrite(M1, HIGH);
		analogWrite(E1, 255);
	}
	else
	{
		if (Output <= 255)
		{
			digitalWrite(M1, HIGH);
			analogWrite(E1, 255-int(Output));
			//Serial.print("L");
			//Serial.println(255-int(Output));
		}
		else
		{
			digitalWrite(M1, LOW);
			analogWrite(E1, int(Output)-255);
			//Serial.print("L-");
			//Serial.println(int(Output)-255);
		}
		digitalWrite(M2, HIGH);
		analogWrite(E2, 255);
	}
}

//-------------------------------------------------------------------------------------------------
void calibration()
{
	while(millis() < 10000)
	{
		for (int i = 0; i <= 4; i++)
		{ 
			sensorValue[i] = analogRead(i);
			if (sensorValue[i] > sensorMax[i])
			sensorMax[i] = sensorValue[i];
			if (sensorValue[i] < sensorMin[i])
			sensorMin[i] = sensorValue[i];
		}
	}
	for (int i = 0; i <= 4; i++)
	{ 
		sensorMin[i] = (sensorMin[i] + (sensorMax[i]-sensorMin[i])/3);
		sensorMax[i] = (sensorMin[i] + (sensorMax[i]-sensorMin[i])*2/3);
	}
}
//----------------------------------------------------------------------------------------------