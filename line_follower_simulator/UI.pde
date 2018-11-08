void drawUI() {
  //rectMode(CORNER);
  //stroke(2);
  //fill(255);
  //rect(width-220, 30, 200,30);
  // rect(width-220, 70, 200,30);
  //fill(#FF0000);
  ////rect(width-220,30,map(Kp,0,1.2,0,200),30);
  //fill(#00FF00);
  //// rect(width-220,70,map(Kd,0,0.12,0,200),30);
  //fill(0);
  //textSize(12);
  //text("Kp="+Kp*100/100.0, width-240,50);
  //text("Kd="+round(Kd*1000)/1000.0, width-240,90);
  textSize(36);
  fill(#FF00FF);
  stroke(2);
  text("Robot sensor", width/2-20, height/2+100);
  for (int i=0; i<=4; i++) {
    if (state[i]) fill(#FF0000);
    else noFill();
    ellipse((width/2+60)+i*30, height/2+130, 30, 30);
  }
}

void keyPressed() {
  //if (key == 'Q' || key =='q') Kp+=.05; 
  //if (key == 'A' || key =='a') Kp-=0.05;
  // if (key == 'W' || key =='w') Kd+=.005; 
  //if (key == 'S' || key =='s') Kd-=0.005;
  //Kp = constrain(Kp,0,1.2);
  //Kd = constrain(Kd,0,.12);
  if (key == 'R' || key =='r') {
    x=655;
    y = 390;
    theta=90;

    input = 0.;
    last_input =0;
    output =0.;
  }
}