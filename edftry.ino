//HEIGHT 20 40 60   edf +20  level -30 9-11 29-31 49- 51
// servo 180 2.4
//servo 135 1.9
// servo 90 1.4
// servo 45 1 
// servo 9 .640
// map 200(on servo tester) to 180(controller)
 // servotester 70
 //init 0 wait 5 sec 
 // 18 stage1
 // 23 stage2
 // 1 === GUIDEWAY
 // 2 === ABSOLUTE LENGTH
 // 3 === FORWARD ULTRA
 // EDF DO NOT EXCEED 140
 //guideway 30  ultra2 6.5
#include<Servo.h>
int prev;
int prev_guideway;
#define trigPin1 42
#define echoPin1 43
#define brek 11
#define pwm1 5
#define m11 4
#define m12 6
Servo edf;
#define trigPin2 30
#define echoPin2 31
#define trigPin3 38
#define echoPin3 39

#define kp 4
#define pwm_pin 10
#define slot1 20
#define slot2 40
#define min_distance 25
// 1 logic 1(4) 
//2 pwm (5)
// logic 0 (6)
//last gnd        nisha
void pwm_guideway(int new1)
{
  int i;
  for(i=prev_guideway;i<new1;i++)
  {
    analogWrite(pwm1,i);
  }
  prev_guideway=i;
}
void pwm_guideway1(int new1)
{
  int i;
  for(i=prev_guideway;i>new1;i--)
  {
    analogWrite(pwm1,i);
  }
  prev_guideway=i;
}

long distance1()
{
 long duration, distance_below;
  digitalWrite(trigPin1, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin1, HIGH);

  delayMicroseconds(10); 
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  distance_below = ((duration/2) *10) / 291;
  return distance_below ;
  
}

long distance2()
{
   
  long duration, distance_below;
  digitalWrite(trigPin2, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin2, HIGH);

  delayMicroseconds(10); 
  digitalWrite(trigPin2, LOW);
  duration = pulseIn(echoPin2, HIGH);
  distance_below = ((duration/2) *10) / 291;
  return distance_below;
  
}

long distance3()
{
 long duration, distance_below;
  digitalWrite(trigPin3, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin3, HIGH);

  delayMicroseconds(10); 
  digitalWrite(trigPin3, LOW);
  duration = pulseIn(echoPin3, HIGH);
  distance_below = ((duration/2) *10) / 291;
  return distance_below ;
  
}
void setpwm(int a,int b)
{
  int i;
  int val;
  for(i=a;i<=b;i++)
  {
    edf.write(i);
    
  }
   delay(10);
   
  prev=i;
    
}
void setpwm1(int a,int b)
{
  int i;
  int val;
  for(i=a;i>=b;i--)
  {
    edf.write(i);
    
     
    
  }
  delay(10);
     prev=i;
}
void setup() {
  Serial.begin (9600);
  edf.attach(10);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(pwm1, OUTPUT);
  
  pinMode(pwm_pin, OUTPUT);
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  
}

void loop() 
{
  
  long val;
  long duration, distance_below,temp,distance;
  long duration1, distance_front,d_new;
 
  
 // 0-20 0-255 .7 1.4 1.8
   

setpwm(11,11);
delay(11000);
//29 guideway

 while(1)
{delay(10);
  distance=distance1();
 // Serial.println(distance);
 // Serial.println(d_new);
// CODE FOR GUIDEWAY
  delay(10);
  
  val=30-distance;
  if(val<-2)
  {
    digitalWrite(m12,HIGH);
    digitalWrite(m11,LOW);
    val=val*(-1);  
  }
  else if(val>2) 
  {
    digitalWrite(m11,HIGH);
    digitalWrite(m12,LOW);
  }
  else
  {
    digitalWrite(m11,HIGH);
    digitalWrite(m12,HIGH);
  }
    
  
  val=3*val+160;
  
  val=255-val;
  
    analogWrite(pwm1,val);
    //pwm_guideway(val);
     //pwm_guideway1(val);
  
//CODE FOR EDF 
// 6 
// 22
d_new=distance2();
  
  if((d_new>=25&&d_new<=28)||(d_new>=45&&d_new<=48))
{
  if(prev>80)
  setpwm1(prev,80);
  else
   setpwm(prev,80);
}
else if(d_new>=5&&d_new<=7)
{
    setpwm(prev,140);
}
else if(d_new>=50)
{
  setpwm1(prev,0);
  break;
}
else
{
  setpwm(prev,130);
}  
}
distance=distance2();
while(distance<=57)
{
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  analogWrite(pwm1,90);
  distance=distance2();
  delay(10);
}
  digitalWrite(m11,HIGH);
  digitalWrite(m12,HIGH);

while(1)
{
  
}
}
