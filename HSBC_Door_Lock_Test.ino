 #define servoMotor 11
 #define sevenVolt 6
 #define lock -75
 #define unlock 65
 #define GSMLock 2 
 #define LDR1 A0
 #define LDR2 A1
 #define ambientLightThresh 250

  bool GSMSig;
  bool lightDetected;
  int LDRVal1;
  int LDRVal2;
  int LDRavg;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sevenVolt, OUTPUT);   // D6 = 7V trigger
  pinMode(servoMotor, OUTPUT);  // D11 = PWM output
  pinMode(GSMLock, INPUT_PULLUP);      // D2 = GSM input signal to lock/unlock

  LDRVal1 = 0;
  LDRVal2 = 0;
  LDRavg = 0;
  lightDetected = false;

  digitalWrite(sevenVolt, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  GSMSig = digitalRead(GSMLock);
  Serial.println (LDRavg);
  if(GSMSig == false) {
    doorUnlock();
  }
  
  else {
    doorLock();
  }
  lightDetection();
}

void doorUnlock() {
  analogWri
  te(servoMotor , unlock);
}

void doorLock() {
  analogWrite(servoMotor, lock);
}

void lightDetection() {
  LDRVal1 = analogRead(LDR1);
  LDRVal2 = analogRead(LDR2);
  LDRavg =  (LDRVal1 + LDRVal2)/2 ;
  if(LDRavg >= ambientLightThresh ) {
    lightDetected = true;
    Serial.println("LIGHT DETECTED!!!");
  }
  else {
    lightDetected = false;
  }

}
