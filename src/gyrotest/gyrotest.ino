#include<Wire.h>
#include <U8glib.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);

const int MPU=0x68;//MPU6050 I2C주소
int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
void get6050();


void setup()

{
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);//MPU6050 을 동작 대기 모드로 변경
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop()

{
  get6050();//센서값 갱신
  //받아온 센서값을 출력합니다.

  
  Serial.print(AcX);
  Serial.print(" ");
  Serial.print(AcY);
  Serial.print(" ");
  Serial.print(AcZ);
  Serial.println();
  

/*
  Serial.print(GyX);
  Serial.print(" ");
  Serial.print(GyY);
  Serial.print(" ");
  Serial.print(GyZ);
  Serial.println();
  */

  AcX = map(AcX,-16000,16000,64,0);
  AcY = map(AcY,-16000,16000,128,0);

  u8g.firstPage();
  do{
    u8g.drawBox(AcY,AcX,5,5);
   }while(u8g.nextPage());
  
  delay(10);
}

void get6050(){
  
  Wire.beginTransmission(MPU);//MPU6050 호출
  Wire.write(0x3B);//AcX 레지스터 위치 요청
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);//14byte의 데이터를 요청

  AcX=Wire.read()<<8|Wire.read();//두개의 나뉘어진 바이트를 하나로 이어붙입니다.
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  Tmp=Wire.read()<<8|Wire.read();
  GyX=Wire.read()<<8|Wire.read();
  GyY=Wire.read()<<8|Wire.read();
  GyZ=Wire.read()<<8|Wire.read();

}
