/*
   dibuat tanggal 30-05-2021
   project otomatis kamar mandi
   IRFAN ARDIANSYAH
   direvisi tanggal 23-04-2022
*/
unsigned long simpan1 = 0;
unsigned long simpan2 = 0;
unsigned long simpan3 = 0;

#define lampu1 12 //indikator sensor 1
#define lampu2 5 //indikator sensor 2
#define lampu3 4 //indikator sensor 3
#define ledPin 13 //relay
#define ledPin1 3 //lamp state
#define button1 A3 //button 
#define TimeBack 122

bool status1 = false;
bool status2 = false;
bool status3 = false;
bool returnValue = LOW;
bool stateTime=false;

#define tunda 1000

uint8_t sensor_1 = 8;
uint8_t sensor_2 = 10;
uint8_t sensor_3 = 11;

//int count1 = 1;
//int count2 = 1;
//int count3 = 1;

int ledState = LOW;
unsigned long tmr = 0;
unsigned long previousMillis = 0;
const long interval = 1000;
int flag;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(lampu1, OUTPUT);
  pinMode(lampu2, OUTPUT);
  pinMode(lampu3, OUTPUT);
  pinMode(button1, INPUT_PULLUP);

}

void button() {
  byte nilaiButton1 = digitalRead(button1);

  if (nilaiButton1 == LOW) {
    status1 = 0;
    status2 = 0;
    status3 = 0;
    tmr=0;
    flag=true;
    ledState=true;
  }

  else if(nilaiButton1 == HIGH && stateTime == LOW){
    flag=false;
    ledState=false;
  }
  
}



void loop() {
  button();
  cekLogic();
  
  if (returnValue == 1) {
    runningTime(0);
    flag = 1;
    tmr=0;
    stateTime=true;
  }
  
  if (returnValue == 0 && stateTime == 1) {
    runningTime(1);
    while (tmr >= TimeBack) {
      ledState = LOW;
      //digitalWrite(ledPin1, ledState);
      flag = 0;
      stateTime=false;
      break;
    }
  }
  digitalWrite(ledPin, flag);
  digitalWrite(ledPin1, ledState);
  //    Serial.println(returnValue);
  //    Serial.println(status1);
  //    Serial.println(status2);
  //    Serial.println(status3);
}


void cekLogic() {
  int nilai_1 = digitalRead(sensor_1);
  int nilai_2 = digitalRead(sensor_2);
  int nilai_3 = digitalRead(sensor_3);

  unsigned long now1 = millis();
  if ((now1 - simpan1) > tunda) {
    simpan1 = now1;

    if (nilai_1 == 1) {
      status1 = true;
    }
    else {
      status1 = false;
    }
   
    digitalWrite(lampu1, status1);
  }

  unsigned long now2 = millis();
  if ((now2 - simpan2) > tunda) {
    simpan2 = now2;

    if (nilai_2 == 1) {
      status2 = true;
    }
    else {
      status2 = false;
    }
    
    digitalWrite(lampu2, status2);
  }

  unsigned long now3 = millis();
  if ((now3 - simpan3) > tunda) {
    simpan3 = now3;

    if (nilai_3 == 1) {
      status3 = true;
    }
    else {
      status3 = false;
    }
    
    digitalWrite(lampu3, status3);
  }
  logic(status1, status2, status3);
}

int logic(int status_1, int status_2, int status_3) {
  int refres;
  if (status_1 == 1 && status_2 == 1 && status_3 == 0) {    //on
    returnValue = 1;
  }
  else if (status_1 == 1 && status_2 == 0 && status_3 == 1) {   //on
    returnValue = 1;
  }
  else if (status_1 == 0 && status_2 == 1 && status_3 == 1) {   //on
    returnValue = 1;
  }
  else if (status_1 == 1 && status_2 == 1 && status_3 == 1) {   //on
    returnValue = 1;
  }
  else if (status_1 == 0 && status_2 == 0 && status_3 == 1) {    //off
    returnValue = 0;
  }
  else if (status_1 == 0 && status_2 == 1 && status_3 == 0) {    //off
    returnValue = 0;
  }
  else if (status_1 == 1 && status_2 == 0 && status_3 == 0) {    //off
    returnValue = 0;
  }
  else if (status_1 == 0 && status_2 == 0 && status_3 == 0) { //off
    returnValue = 0;
  }

}

int runningTime(bool state) {

  if (state == 1) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {

      previousMillis = currentMillis;
      tmr++;
      //Serial.println(previousMillis);
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      digitalWrite(ledPin1, ledState);
    }
  }

  else {
    digitalWrite(ledPin1, LOW);
    previousMillis = 0;
    tmr = 0;
    //Serial.println(tmr);
  }

}
