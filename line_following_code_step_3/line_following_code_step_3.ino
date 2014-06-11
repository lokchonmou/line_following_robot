int sensorValue[5] = {
  0, 0, 0, 0, 0};         // the sensor value
int sensorMin[5] = {
  1023, 1023, 1023, 1023, 1023};        // minimum sensor value
int sensorMax[5] = {
  0, 0, 0, 0, 0};           // maximum sensor value
boolean sensor_state[5] = {
  0, 0, 0, 0, 0};
byte Map = 0;
float input, output, P, D, lastinput;
unsigned long lastTime, SampleTime;
int inByte = 0;
int E1 = 5;  
int M1 = 4; 
int E2 = 6;                      
int M2 = 7; 
int MaxSpeed = 255;


void setup()
{
  P = 64.0;
  D = 5.1;
  SampleTime = 30;

  Serial.begin(9600);
  pinMode(M1, OUTPUT);   
  pinMode(M2, OUTPUT); 

  while (millis() < 5000)
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
      sensor_state[i] = 1;
    if (analogRead(i) > (sensorMin[i] + (sensorMax[i]-sensorMin[i])*2/3))
      sensor_state[i] = 0;
    Map = Map | sensor_state[i];
    Map = Map << 1; 
  }


  //  changle the sensorMap to input
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
  case B111000:
    input  = -2;
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
  case B001110:
    input = 2;
    break;
  case B000110:
    input = 3;
    break;
  case B000010:
    input = 4;
    break;
  }
  unsigned long now = millis();
  unsigned long timeChange = (now - lastTime);
  if (timeChange >= SampleTime)
  {
    output = -P*input- D*(input - lastinput)/(SampleTime*1e-3);
    output = constrain(output, -2*MaxSpeed, 2*MaxSpeed);
   
    Serial.print(MaxSpeed);
    Serial.print(",");
    Serial.print(P);
    Serial.print(",");
    Serial.println(D);
   

    if (output > -MaxSpeed && output <0)
    {
      digitalWrite(M1,HIGH);   
      digitalWrite(M2, HIGH);       
      analogWrite(E1, MaxSpeed);   
      analogWrite(E2, MaxSpeed - abs(output));   
    }
    else if(output >= 0 && output < MaxSpeed)
    {
      digitalWrite(M1,HIGH);   
      digitalWrite(M2, HIGH);       
      analogWrite(E1, MaxSpeed - abs(output));   
      analogWrite(E2, MaxSpeed);   
    }
    else if(output >= MaxSpeed && output <= 2*MaxSpeed)
    {
      digitalWrite(M1,LOW);   //反轉
      digitalWrite(M2, HIGH);       
      analogWrite(E1, abs(output) - MaxSpeed);   
      analogWrite(E2, MaxSpeed);   
    }
    else if(output >= -2*MaxSpeed && output <= -MaxSpeed)
    {
      digitalWrite(M1,HIGH);   
      digitalWrite(M2, LOW);     //反轉  
      analogWrite(E1, MaxSpeed);   
      analogWrite(E2, abs(output) - MaxSpeed);   
    }
    lastTime = now;
    lastinput = input;
  }
  if (Serial.available()>0)
  {
    int inByte = Serial.read();
    if  (inByte == 'w')  P++;
    if  (inByte == 's')  P--;
    if  (inByte == 'd')  D+=.1;
    if  (inByte == 'a')  D-=.1;
    if  (inByte == ',')  MaxSpeed -=2;
    if (inByte =='.')   MaxSpeed +=2;
  }
}





