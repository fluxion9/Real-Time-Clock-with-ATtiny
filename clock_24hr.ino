int Days;
int Hrs;
int Min;
int Sec;
unsigned long lastTime = 0;
unsigned long convertedValue;
const long interval = 1000;
unsigned long currentTime;
String TimeWithoutSec, TimeWithSec;
String readString, receivedData;
int setPin = 9;
void setup() {
  Days = 0;
  Hrs = 0;
  Min = 0;
  Sec = 0;
  Serial.begin(9600);
  pinMode(setPin, INPUT_PULLUP);
}

void loop() {
  while(digitalRead(setPin))
  {
    s();
    m();
    h();
    t();
    Serial.println(TimeWithSec);
    //Serial.println(TimeWithoutSec);
  }
  checkForUpdate();
}
  
void s()
  {
currentTime = millis();
if (currentTime - lastTime > interval) 
{ 
  Sec += 1;
  lastTime = currentTime;
} 
if (Sec >= 60)
{
  Sec = 0;
  Min += 1;
}
  }

void m() {
    if(Min >= 60)
    {
      Min = 0;
      Hrs += 1;
      }
}

void h() {
  if(Hrs >= 24)
  {
    Hrs = 0;
    Days += 1;
  }
 }
 
void t() {
     if (Min < 10 && Sec < 10)
    {
      TimeWithoutSec = String(Hrs) + ":0" + String(Min);
      TimeWithSec = String(Hrs) + ":0" + String(Min) + ":0" + String(Sec);
    }
        else if (Min >= 10 && Sec < 10) {
      TimeWithoutSec = String(Hrs) + ":" + String(Min);
      TimeWithSec = String(Hrs) + ":" + String(Min) + ":0" + String(Sec);
    }
     else if (Min >= 10 && Sec >= 10) {
      TimeWithoutSec = String(Hrs) + ":" + String(Min);
      TimeWithSec = String(Hrs) + ":" + String(Min) + ":" + String(Sec);
    }
        else if (Min < 10 && Sec >= 10) {
      TimeWithoutSec = String(Hrs) + ":" + String(Min);
      TimeWithSec = String(Hrs) + ":0" + String(Min) + ":" + String(Sec);
      }
}


void checkForUpdate() {
  while(Serial.available()) {
  delay(3);
  char data = Serial.read();
  readString += data;
}
  if (readString.length() > 0)
{
  receivedData = readString;
  convertedValue = receivedData.toInt();
  splitInt(convertedValue, 4);
  readString = "";
}
}

void splitInt(unsigned long num, int Length)
{
  long first, second, third, fourth, fifth, sixth;
  first = long(num / long(pow(10, Length - 1)));
  second = long(num / long(pow(10, Length - 2)));
  second = second - (long(second / 10) * 10);
  third = long(num / long(pow(10, Length - 3)));
  third = third - (long(third / 10) * 10);
  fourth = num - (long(num / 10) * 10);
  Hrs = (first * 10) + second;
  Min = (third * 10) + fourth;
  Sec = 0;
}
