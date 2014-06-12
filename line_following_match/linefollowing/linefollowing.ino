//  PID controller
#include <PID_v1.h>
double Setpoint, Input, Output;
PID myPID(&Input, &Output, &Setpoint,30,0,15, DIRECT);

int ledArray[] = {2,3,19};
float colourArray[] = {0,0,0};
float whiteArray[] = {0,0,0};
float blackArray[] = {0,0,0};
int avgRead;

//Arduino PWM Speed Control：
const int E1 = 5;  
const int M1 = 4; 
const int E2 = 6;                      
const int M2 = 7;                        
// variables:
int sensorValue[5] = {0, 0, 0, 0, 0};         // the sensor value
int sensorMin[5] = {1023, 1023, 1023, 1023, 1023};        // minimum sensor value
int sensorMax[5] = {0, 0, 0, 0, 0};           // maximum sensor value
int error = 0, Last_error = 0;
//-------------------------------------------------------------------------------------------------

void setup() 
{ 
	Serial.begin(9600);  
	pinMode(M1, OUTPUT);   
	pinMode(M2, OUTPUT); 
	pinMode(ledArray[0],OUTPUT);
	pinMode(ledArray[1],OUTPUT);
	pinMode(ledArray[2],OUTPUT);
	Setpoint = 0;
	Input = 0;
	calibration();
	// myPID.SetOutputLimits(-510, 510);
	// myPID.SetMode(AUTOMATIC);
}   
//-------------------------------------------------------------------------------------------------
void loop() 
{ 
	//  Read the sensor as sensorMap
	Map = 0;
	for(int i=0; i<3; i++){
		sensorValue[i] =  analogRead(14+i); 
	}
	Map = map(sensorValue[0], sensorMin[0], sensorMax[0], 0, 100)- map(sensorValue[1], sensorMin[1], sensorMax[1], 0, 100);


	Serial.println(Map);

	

	// Last_error = error;

	// // control the motor speed


	// Input = error;
	// myPID.Compute();
	// if (Output<0)
	// {
	// 	if (Output >= -255)
	// 	{
	// 		digitalWrite(M2, HIGH);
	// 		analogWrite(E2, 255+int(Output));
	// 		//Serial.print("R");
	// 		// Serial.println(255+int(Output));
	// 	}
	// 	else
	// 	{
	// 		digitalWrite(M2, LOW);
	// 		analogWrite(E2, -255-int(Output));
	// 		//Serial.print("R-");
	// 		//Serial.println(-255-int(Output));
	// 	}
	// 	digitalWrite(M1, HIGH);
	// 	analogWrite(E1, 255);
	// }
	// else
	// {
	// 	if (Output <= 255)
	// 	{
	// 		digitalWrite(M1, HIGH);
	// 		analogWrite(E1, 255-int(Output));
	// 		//Serial.print("L");
	// 		//Serial.println(255-int(Output));
	// 	}
	// 	else
	// 	{
	// 		digitalWrite(M1, LOW);
	// 		analogWrite(E1, int(Output)-255);
	// 		//Serial.print("L-");
	// 		//Serial.println(int(Output)-255);
	// 	}
	// 	digitalWrite(M2, HIGH);
	// 	analogWrite(E2, 255);
	// }
}

//-------------------------------------------------------------------------------------------------
void calibration()
{
	while(millis() < 10000)
	{	
		for (int i = 0; i <= 3; i++){ 
			sensorValue[i] = analogRead(i);
			if (sensorValue[i] > sensorMax[i])
			sensorMax[i] = sensorValue[i];
			if (sensorValue[i] < sensorMin[i])
			sensorMin[i] = sensorValue[i];
		}
	}
	for(int i=0; i<=2; i++){
		digitalWrite(ledArray[i], HIGH);
	}
	delay(1000);
	for(int i=0; i<=2; i++){
		digitalWrite(ledArray[i], LOW);
	}
	delay(4000);

	for(int i = 0;i<=2;i++){
		digitalWrite(ledArray[i],HIGH);
		delay(100);
		getReading(5);   
		whiteArray[i] = avgRead;
		digitalWrite(ledArray[i],LOW);
		delay(100);
	}
	delay(5000);   
	for(int i = 0;i<=2;i++){
		digitalWrite(ledArray[i],HIGH);
		delay(100);
		getReading(5);
		blackArray[i] = avgRead;
		digitalWrite(ledArray[i],LOW);
		delay(100);
	}
	delay(3000);
}
//----------------------------------------------------------------------------------------------
void checkColour(){
	for(int i = 0;i<=2;i++){
		digitalWrite(ledArray[i],HIGH);  
		delay(100);                      
		getReading(5);                  
		colourArray[i] = avgRead;       
		float greyDiff = whiteArray[i] - blackArray[i];                   
		colourArray[i] = (colourArray[i] - blackArray[i])/(greyDiff)*255; 
		digitalWrite(ledArray[i],LOW);   
		delay(100);
	}
}

void getReading(int times){
	int reading;
	int tally=0;
	//take the reading however many times was requested and add them up
	for(int i = 0;i < times;i++){
		reading = analogRead(0);
		tally = reading + tally;
		delay(10);
	}
	//calculate the average and set it
	avgRead = (tally)/times;
}