void drawRobot() {
  // draw the body of robot////////////////////////////////
  pushMatrix();
  rectMode(CENTER);
  stroke(3);
  translate(x, y);
  rotate(radians(theta));
  fill(255,0);
  rect(0, 0, d.getValueF()/2, d.getValueF());
 
  fill(#FF00FF);
  text(round(vr/max_speed.getValueF() *100)+"%",-d.getValueF()/2,d.getValueF()+20);
  text(round(vl/max_speed.getValueF() *100)+"%",-d.getValueF()/2,-d.getValueF());
  popMatrix();

  // draw the sensor////////////////////////////////
  noStroke();
  fill(#FF0000);
  for (int i=0; i<=4; i++) {
    
    float sensor_position_x = x+sensor_distance.getValueF()*cos(abs(i-2)*sensor_width.getValueF()/sensor_distance.getValueF())*cos(radians(theta))-(i-2)*sensor_width.getValueF()*sin(radians(theta));
    float sensor_position_y = y+sensor_distance.getValueF()*cos(abs(i-2)*sensor_width.getValueF()/sensor_distance.getValueF())*sin(radians(theta))+(i-2)*sensor_width.getValueF()*cos(radians(theta));
    color c = get(int(sensor_position_x), +int(sensor_position_y));
    //print(c, '\t');
    if (c==-16777216) state[i] = true;
    else state[i] = false;
    print(state[i], '\t');
    ellipse(sensor_position_x, sensor_position_y, 6, 6);
    
  }println();

  if (millis() - timer >=150) {

    // define the input by the state of sensor ////////////////////////////////
    if (state[0]==true && state[1]==true && state[2]==true && state[3]==false && state[4]==false) input = 4.0;
    if (state[0]==true && state[1]==false && state[2]==false && state[3]==false && state[4]==false) input = 4.0;
    if (state[0]==true && state[1]==true && state[2]==false && state[3]==false && state[4]==false) input = 3.0;
    if (state[0]==false && state[1]==true && state[2]==false && state[3]==false && state[4]==false) input = 2.0;
    if (state[0]==false && state[1]==true && state[2]==true && state[3]==false && state[4]==false) input = 1.0;
    if (state[0]==false && state[1]==false && state[2]==true && state[3]==false && state[4]==false) input = 0.0;
    if (state[0]==false && state[1]==false && state[2]==true && state[3]==true && state[4]==false) input = -1.0;
    if (state[0]==false && state[1]==false && state[2]==false && state[3]==true && state[4]==false) input = -2.0;
    if (state[0]==false && state[1]==false && state[2]==false && state[3]==true && state[4]==true) input = -3.0;
    if (state[0]==false && state[1]==false && state[2]==false && state[3]==false && state[4]==true) input = -4.0;
    if (state[0]==false && state[1]==false && state[2]==true && state[3]==true && state[4]==true) input = -5.0;
    

    // PID controller////////////////////////////////
    output = Kp.getValueF() * input+ Kd.getValueF() *(input - last_input);
    // output = Kp.getValueF() * input;
    output = constrain(output, -2*max_speed.getValueF(), 2* max_speed.getValueF());
    if (output >0) {
      vl = max_speed.getValueF() -output;
      vr = max_speed.getValueF();
    } else {
      vl = max_speed.getValueF();
      vr=max_speed.getValueF() - abs(output);
    }
    println(input,'\t',output,'\t', vl,'\t',vr);
    timer = millis();
  }

  dtheta=(vl-vr)/2;
  dx=(vr+vl)/2 * cos(radians(theta));
  dy=(vr+vl)/2 * sin(radians(theta));

  theta += dtheta;
  x += dx;
  y += dy;
}