   #include <webots/DistanceSensor.hpp>
  #include <webots/Motor.hpp>
  #include <webots/Robot.hpp>
  #include <webots/Camera.hpp>
  #define TIME_STEP 64
  #include <iostream>     

  using namespace webots;
  using namespace std;
  float ms=6.28,rs,ls;
  float dsO,ds_l,ds_ll,ds_lll,r,r_l,r_ll,g=0,b=0,u=0,ss=20;
  int lf,rh,fw,t;
  void cube() 
  {
  if(ds_l!=1000&&ds_ll!=1000&&r_l!=0&&r_ll!=0)
  {
  if(fw<=500)
  {
  b=1;
  ls=6.28;
  rs=-6.28;
  }
  else if(lf<=100)
  {
  ls=7;
  rs=6.28/5;
  }
  else if(rh<=500)
  {
  b=0;
  ls=6.28;
  rs=6.28;
  }
  else 
  {
  ls=6.28/5;
  rs=7;
  }
  }
  else
  g=0;
  }
      int main(int argc, char **argv) {
      Robot *robot = new Robot();
      int timeStep = (int)robot->getBasicTimeStep();
      Camera *camera= robot->getCamera("camera");
      camera->enable(TIME_STEP);
      Motor *wheels[2];
      DistanceSensor *ds1 = robot->getDistanceSensor("ds1");
      ds1->enable(TIME_STEP);
      DistanceSensor *ds2 = robot->getDistanceSensor("ds2");
      ds2->enable(TIME_STEP);
      DistanceSensor *ds3 = robot->getDistanceSensor("ds3");
      ds3->enable(TIME_STEP);
      DistanceSensor *ds4 = robot->getDistanceSensor("ds4");
      ds4->enable(TIME_STEP);
      DistanceSensor *ds5 = robot->getDistanceSensor("ds5");
      ds5->enable(TIME_STEP);  
      char wheels_names[2][48] = {"left wheel motor","right wheel motor"};
      for (int i = 0; i < 2; i++)
  {
        wheels[i] = robot->getMotor(wheels_names[i]);
        wheels[i]->setPosition(INFINITY);
        wheels[i]->setVelocity(0);
  } 
  while (robot->step(timeStep) != -1)
  {
  const unsigned char *image = camera->getImage();
   
  if(robot->getTime()>1)
  {  
  r = camera->imageGetRed(image, 64, 32, 63);
  r_l = camera->imageGetRed(image, 64, 5, 63);
  r_ll = camera->imageGetRed(image, 64, 58, 63);

  lf=ds3->getValue();
  rh=ds4->getValue();
  fw=ds5->getValue();
  ds_l=ds1->getValue();
  ds_ll=ds2->getValue();

  if(fw<300)
  g=1; 
  if(g==0)
  {
  
  if(((ds_l<500&&ds_ll<500)||(ds_l==1000&&ds_ll==1000&&r_l!=0&&r_ll!=0))&&r==0)
  {  
  ls=ms;
  rs=ms;
  
  }
  else if(ds_l==1000&&ds_ll<500)
  {
  ls=ms;
  rs=ms/ss;
  }
  else if(ds_l<500&&ds_ll==1000)
  {
  ls=ms/ss;
  rs=ms;
  }
  else if(((ds_l==1000&&ds_ll==1000))&&r==0&&r_l!=0&&r_ll==0)
  {
  ls=ms;
  rs=ms/ss;
  }
  else if(((ds_l==1000&&ds_ll==1000))&&r==0&&r_l==0&&r_ll!=0)
  {
  ls=ms/ss;
  rs=ms;
  }
  else if(((ds_l==1000&&ds_ll==1000))&&r!=0&&r_l!=0&&r_ll!=0)
  {
  ls=ms;
  rs=ms/ss;
  }

  else 
  { 
  ls=ms/ss;
  rs=ms;
  }
  }
  else
  cube();

  wheels[0]->setVelocity(ls);
  wheels[1]->setVelocity(rs);
  }
  };
    delete robot;
    return 0;
  }