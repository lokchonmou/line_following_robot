int sensorValue[5] = {0, 0, 0, 0, 0};         // the sensor value
int sensorMin[5] = {1023, 1023, 1023, 1023, 1023};        // minimum sensor value
int sensorMax[5] = {0, 0, 0, 0, 0};           // maximum sensor value
boolean sensor_state[5] = {0, 0, 0, 0, 0};
byte Map = 0;
double input, output, P;
int E1 = 5;  
int M1 = 4; 
int E2 = 6;                      
int M2 = 7; 


void setup()
{
	P = 120.0;
	Serial.begin(9600);
	pinMode(M1, OUTPUT);   
	pinMode(M2, OUTPUT); 
	while (millis() < 10000)
	{
		for (int i = 0; i<=4; i++)
		{
			sensorValue[i] = analogRead(i);
			if (sensorValue[i] > sensorMax[i])		sensorMax[i] = sensorValue[i];
			if (sensorValue[i] < sensorMin[i])		sensorMin[i] = sensorValue[i];
		}
	}
}
	void loop()
	{
		Map = 0;
		for (int i = 0; i <= 4; i++)
		{
			if (analogRead(i) < (sensorMin[i] + (sensorMax[i]-sensorMin[i])/3))
			sensor_state[i] = 0;
			if (analogRead(i) > (sensorMin[i] + (sensorMax[i]-sensorMin[i])*2/3))
			sensor_state[i] = 1;
			Map = Map | sensor_state[i];
			Map = Map << 1; 
		}
		
		
		//  change the sensorMap to input
		switch (Map)
		{
		case B100000:
			input = -4;
			break;
		case B110000:
			input = -3;
			break;
		case B010000:
			input = -2;
			break;
		case B011000:
			input = -1;
			break;
		case B001000:
			input = 0;
			break;
		case B001100:
			input = 1;
			break;
		case B000100:
			input = 2;
			break;
		case B000110:
			input = 3;
			break;
		case B000010:
			input = 4;
			break;
		}
		
		output = -P*input;
		output = constrain(output, -510, 510);
		Serial.println(output);
		
		if (output > -255 && output <0)
		{
			digitalWrite(M1,HIGH);   
			digitalWrite(M2, HIGH);       
			analogWrite(E1, 255);   
			analogWrite(E2, 255 - abs(output));   
		}
		else if(output >= 0 && output < 255)
		{
			digitalWrite(M1,HIGH);   
			digitalWrite(M2, HIGH);       
			analogWrite(E1, 255 - abs(output));   
			analogWrite(E2, 255);   
		}
		else if(output >= 255 && output <= 510)
		{
			digitalWrite(M1,LOW);   //反轉
			digitalWrite(M2, HIGH);       
			analogWrite(E1, abs(output) - 255);   
			analogWrite(E2, 255);   
		}
		else if(output >= -510 && output <= -255)
		{
			digitalWrite(M1,HIGH);   
			digitalWrite(M2, LOW);     //反轉  
			analogWrite(E1, 255);   
			analogWrite(E2, abs(output) - 255);   
		}
		
	}
