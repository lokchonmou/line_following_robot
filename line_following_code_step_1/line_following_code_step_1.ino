int sensorValue[5] = {0, 0, 0, 0, 0};
int sensorMin[5] = {1023, 1023, 1023, 1023, 1023};        
int sensorMax[5] = {0, 0, 0, 0, 0};           
boolean sensor_state[5] = {LOW, LOW, LOW, LOW, LOW};
byte Map = 0;
double input;



void setup()
{      
	Serial.begin(9600); 
      
	while (millis() < 10000)
	{
		for (int i = 0; i<=4; i++)
		{
			sensorValue[i] = analogRead(i);
			if (sensorValue[i] > sensorMax[i])		
			sensorMax[i] = sensorValue[i];
			if (sensorValue[i] < sensorMin[i])		
			sensorMin[i] = sensorValue[i];
		}
	}
}

void loop()
{
	Map = 0;
	for (int i = 0; i <= 4; i++)
	{
		sensorValue[i] = analogRead(i);
		if (sensorValue[i] < (sensorMin[i] + sensorMax[i])/2)		
				sensor_state[i] = LOW;
		else	sensor_state[i] = HIGH;
		Map = Map | sensor_state[i];
		Map = Map << 1; 
	}
        Serial.println(Map, BIN);
      
}
