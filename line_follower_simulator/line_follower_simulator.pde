import g4p_controls.*;
float vr=0, vl=0;
float dx, dy, dtheta;
float x, y, theta;
boolean state[]={false, false, false, false, false};
PShape bg;
byte map;
float input, last_input,  output;

long timer;

void setup() {
  size(800, 800);
   createGUI();
  customGUI();
  //pixelDensity(displayDensity());
  x=655;
  y = 390;
  theta=90;
  
  input = 0.;
  last_input =0;
  output =0.;
  
  bg = loadShape("line guide.svg");
}

void draw() {
  // draw the background ////////////////////////////////
  background(255, 70);
  shape(bg, 0, 0, width, height);

  drawRobot();

  drawUI();
}

public void customGUI(){

}