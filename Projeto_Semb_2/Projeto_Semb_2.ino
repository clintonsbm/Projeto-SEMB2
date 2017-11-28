//Setup portas
int pinLamp = 2;
int pinWater = 4;

//Temp sensor setup
int pinTempSensor = A1; // select the input pin for the potentiometer
int tempSensorValue = 0; // variable to store the value coming from the sensor

float i = 0;
float fixtemp = 0.0;
int fixInput = 560;
float fixedDegreeValue = 4.48;

//Luminosity sensor setup
int ldrPin = 2; 
int ldrValor = 0; 

//Umid sensor setup
int pinUmidSensor = A0;
int umidSensorValue = 0;

//Time control
long previousMillis = 0;

//Time interval to next check
long delayTimeWatering = 1000;
long lampCheckInterval = 10000;
long umidCheckInterval = 10000 + delayTimeWatering;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinLamp, OUTPUT);
  pinMode(pinWater, OUTPUT);
  pinMode(pinUmidSensor, INPUT);

  Serial.begin (9600);
}

void loop() {
  delay(500);
  measureTemp();
  measureLum();
  measureUmid();
}

void measureTemp() {
  tempSensorValue = analogRead(pinTempSensor);  

  int conta = (tempSensorValue*34)/400;
  int contaDois = conta - 34;
  int contaTres = 34 - contaDois;
  
  
//  Serial.println(tempSensorValue);
  Serial.print("Temperatura: ");
  Serial.println(contaTres);
//  if (tempSensorValue > fixInput ) { 
//        i = tempSensorValue - fixInput;
//        i = i /fixedDegreeValue; 
//        Serial.print("Temperature = ");
//        fixtemp = fixtemp - i;
//        Serial.print(fixtemp);
//        Serial.println(" C");
//  } else if(tempSensorValue < fixInput) {
//        i =  fixInput - tempSensorValue;
//        i = i /fixedDegreeValue; 
//        Serial.print("Temperature = ");
//        fixtemp = fixtemp + i;
//        Serial.print(fixtemp);
//        Serial.println(" C");
//  } else if(tempSensorValue == fixInput ) {  
//        Serial.println(" temperature  = 20 C");
//    
//  }

  //Add resistor to control temperature
  /*
  if (fixtemp < 23) {
    digitalWrite(pinLamp, HIGH);
  } else {
    digitalWrite(pinLamp, LOW);
  }*/
  
    
  fixtemp = 0.0;
}

void measureLum() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis > lampCheckInterval) { 
    previousMillis = currentMillis;    // Salva o tempo atual
//    Serial.println(ldrValor);
    digitalWrite(pinLamp, LOW);
    delay(500);
    ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
  
    //imprime o valor lido do LDR no monitor serial
    if(ldrValor > 1000) {
      Serial.println("Liga a luz");
      digitalWrite(pinLamp, HIGH);
    } else {
      Serial.println("Desliga a luz");
      digitalWrite(pinLamp, LOW);
    }
  }
}

void measureUmid() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis > umidCheckInterval) { 
    previousMillis = currentMillis;    // Salva o tempo atual
    
    umidSensorValue = analogRead(pinUmidSensor);

    while(umidSensorValue > 800) {
      digitalWrite(pinWater, HIGH);
      delay(delayTimeWatering);
      digitalWrite(pinWater, LOW);

      umidSensorValue = analogRead(pinUmidSensor);
      Serial.print("Valor do sensor de umidade: ");
      Serial.println(umidSensorValue);
    };
    Serial.println("Desliga o motor");
//    if (umidSensorValue > 800) {
//      digitalWrite(pinWater, HIGH);
//      delay(delayTimeWatering);
//      digitalWrite(pinWater, LOW);
//    } else {
//      delay(delayTimeWatering);
//    }
  }
}

