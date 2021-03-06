int TX=1;
int RX=0;
char OPEN[12]={0x55,0xAA,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x01};
char LEDON[12]={0x55,0xAA,0x01,0x00,0x01,0x00,0x00,0x00,0x12,0x00,0x13,0x01};
char OPENBuffer[12];
char LEDBuffer[12];
int j=0;
void setup() {
 Serial.begin(9600);
 delay(100);
 Serial.write(OPEN,sizeof(OPEN));
 delay(1000);
 if(Serial.available()>0){
    while(j<12){
      OPENBuffer[j]=Serial.read();
      Serial.print(OPENBuffer[j],HEX);
      j++;
      delay(5);
    } 
  }
  j=0;
 delay(100);
 Serial.write(LEDON,sizeof(LEDON));
 delay(1000);
 if(Serial.available()>0){
    while(j<12){
      LEDBuffer[j]=Serial.read();
      Serial.print(LEDBuffer[j],HEX);
      j++;
      delay(5);
    } 
   }
 delay(100);

bool useid=true;
  int id =0;
  delay(100);
  while(useid==true){
    useid=CheckEnrolled(id);
    if(useid==true)
    {
     id++;
    }
  }
  EnrollStart(id);
  
  Serial.print("Press finger to Enroll #");
  Serial.println(id);
 
}

bool CheckEnrolled(int id)
{ 
  char CheckEnrolled[12]={0x55,0xAA,0x01,0x00,0x00+id,0x00,0x00,0x00,0x21,0x00,0x21+id,0x01};
  char CheckBuffer[12];
  int i=0;
  
  Serial.write(CheckEnrolled,sizeof(CheckEnrolled)); 
  delay(1000);
  if(Serial.available()>0){
    while(i<12){
      CheckBuffer[i]=Serial.read();
      Serial.print(CheckBuffer[i],HEX);
      i++;
      delay(5);
    } 
   }
  i=0;
  delay(100);
  if(CheckBuffer[8]==0x31){
    return false;
  }
  if(CheckBuffer[8]==0x30){
    return true;
  }
}

int EnrollStart(int id)
{
  char EnrollStart[12]={0x55,0xAA,0x01,0x00,0x00+id,0x00,0x00,0x00,0x22,0x00,0x22+id,0x01};
  char EnrollStartBuffer[12];
  int i=0;
  Serial.write(EnrollStart,sizeof(EnrollStart));
  delay(1000);
  if(Serial.available()>0){
    while(i<12){
      EnrollStartBuffer[i]=Serial.read();
      Serial.print(EnrollStartBuffer[i],HEX);
      i++;
      delay(5);
    } 
   }
  i=0;
  delay(100);
}

void loop() {
  delay(1000);
}
