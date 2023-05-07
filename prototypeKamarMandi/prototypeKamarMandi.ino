#define relay D5
#define ledPir_1 D7
#define ledPir_2 D0
#define led_war D4
#define pir_1 D1
#define pir_2 D6
unsigned long simpan1 = 0;
unsigned long simpan2 = 0;
//unsigned long simpan3 = 0;

#define TimeBack 122

bool status1 = false;
bool status2 = false;
//bool status3 = false;
bool returnValue = LOW;
bool stateTime=false;

#define tunda 100


uint8_t ledState = HIGH;
unsigned long tmr = 0;
unsigned long previousMillis = 0;
const long interval = 500;
uint8_t flag;




void setup() {
  pinMode(relay,OUTPUT);
  pinMode(ledPir_1,OUTPUT);
  pinMode(ledPir_2,OUTPUT);
  pinMode(led_war,OUTPUT);
}


void loop() {
  
  cekLogic();
  
  if (returnValue == 1) {
    runningTime(0);
    //digitalWrite(led_war, HIGH);
    flag = 1;
    tmr=0;
    stateTime=true;
  }
  
  if (returnValue == 0 && stateTime == 1) {
    runningTime(1);
    while (tmr >= TimeBack) {
      ledState = HIGH;
      //digitalWrite(ledPin1, ledState);
      flag = 0;
      stateTime=false;
      break;
    }
  }
  digitalWrite(relay, flag);
  digitalWrite(led_war, ledState);
  //    Serial.println(returnValue);
  //    Serial.println(status1);
  //    Serial.println(status2);
  //    Serial.println(status3);
}


void cekLogic() {
  int nilai_1 = digitalRead(pir_1);
  int nilai_2 = digitalRead(pir_2);
 // int nilai_3 = digitalRead(sensor_3);

  unsigned long now1 = millis();
  if ((now1 - simpan1) > tunda) {
    simpan1 = now1;

    if (nilai_1 == 1) {
      status1 = true;
    }
    else {
      status1 = false;
    }
   
    digitalWrite(ledPir_1, status1);
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
    
    digitalWrite(ledPir_2, status2);
  }

  logic(status1, status2);
}

void logic(int status_1, int status_2) {
  
  if (status_1 == 1 && status_2 == 1) {    //on
    returnValue = 1;
  }
  else if (status_1 == 0 && status_2 == 1) {
    returnValue = 1;
  }

  else if( status_1 == 1 && status_2 == 0) {
    returnValue = 1;
  }
  else{ returnValue = 0; }           //off
  

}

void runningTime(bool state) {

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
     // digitalWrite(led_war, ledState);
    }
  }

  else if(state == 0){
   // digitalWrite(led_war, HIGH);
    previousMillis = 0;
    tmr = 0;
    ledState = HIGH;
    //Serial.println(tmr);
  }

}
