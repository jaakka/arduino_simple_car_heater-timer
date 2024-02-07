#include <TFT.h>  
#include <SPI.h>

#define cs   10
#define dc   9
#define rst  8

TFT TFTscreen = TFT(cs, dc, rst);

char sensorPrintout[6];
char sensorPrintoutm[6];
char sensorPrintouth[6];
int s=0;
int m=1;
int h=0;
int mita=0;
int pause=false;
void setup() 
{
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(3,HIGH);
  digitalWrite(2,HIGH);
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.setTextSize(2);
  TFTscreen.text("Koska :\n ", 0, 0);
  TFTscreen.setTextSize(3);
}

void loop() 
{
  int sensorValue = analogRead(A2);
  Serial.println(sensorValue);
if(sensorValue>100)
{
  if(mita<4)
  {
    mita+=1;
  }
    else
  {
    mita=0;
  }
}
  else
{
  if(mita==1)
  {
    if(s<60){
    s+=1;
    }
    if(s+9<60){
    s+=9;
    }
    mita=0;
  }
  if(mita==2)
  {
    if(m<60){
    m+=1;
    }
    if(m+4<60){
    m+=4;
    }
    mita=0;
  }
  if(mita==3)
  {
    h+=1;
    mita=0;
  }
  if(mita==4)
  {
    if(pause==true){pause=false;}else{pause=true;}
    mita=0;
  }
}


  String sensorVal = String(String(s)+String("s"));
  String sensorValm = String(String(m)+String("m"));
  String sensorValh = String(String(h)+String("h"));

  sensorVal.toCharArray(sensorPrintout, 6);
  sensorValm.toCharArray(sensorPrintoutm, 6);
  sensorValh.toCharArray(sensorPrintouth, 6);

  TFTscreen.stroke(255, 255, 255);
  TFTscreen.text(sensorPrintouth, 0, 20);
  TFTscreen.text(sensorPrintoutm, 0, 45);
  TFTscreen.text(sensorPrintout, 0, 70);
  // wait for a moment
  if(mita==1)
  {
    TFTscreen.text("+10s/1s", 10, 95);
  }
  if(mita==2)
  {
    TFTscreen.text("+5m/1m", 10, 95);
  }
  if(mita==3)
  {
    TFTscreen.text("+1h", 10, 95);
  }
  if(mita==4)
  {
    TFTscreen.text("Pys/Jat", 10, 95);
  }
  delay(1000);
TFTscreen.stroke(0, 0, 0);
  if(mita==1)
  {
    TFTscreen.text("+10s/1s", 10, 95);
  }
  if(mita==2)
  {
    TFTscreen.text("+5m/1m", 10, 95);
  }
  if(mita==3)
  {
    TFTscreen.text("+1h", 10, 95);
  }
  if(mita==4)
  {
    TFTscreen.text("Pys/Jat", 10, 95);
  }

  if(pause==false){
  if(s>0)
  {
    s-=1;
  }
    else
  {
    if(m>0)
    {
      m-=1; s=60;
    }
      else
     {
      if(h>0)
      {
        h-=1; m=60;
      }
        else
      {
        digitalWrite(3,LOW);
        digitalWrite(2,LOW);
      } 
     }
  }
  }

  TFTscreen.stroke(0, 0, 0);
  TFTscreen.text(sensorPrintouth, 0, 20);
  TFTscreen.text(sensorPrintoutm, 0, 45);
  TFTscreen.text(sensorPrintout, 0, 70);
}
