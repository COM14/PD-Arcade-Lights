#define arraySize 3
#define Sync 0xff

#define led1 2  // BUTTON LED TRIANGLE
#define led2 3  // BUTTON LED SQUARE
#define led3 4  // BUTTON LED CROSS
#define led4 5  // BUTTON LED CIRCLE

#define led_R1 6  // LEFT PARTITION LED PED
#define led_G1 7  // LEFT PARTITION LED GREEN
#define led_B1 8  // LEFT PARTITION LED BLUE

#define led_R2 9  // RIGHT PARTITION LED PED
#define led_G2 10 // RIGHT PARTITION LED GREEN
#define led_B2 11 // RIGHT PARTITION LED BLUE

uint8_t iteration = 0;
uint8_t inData[arraySize];


void setup() {
     Serial.begin(38400);
     pinMode(led1, OUTPUT);
     pinMode(led2, OUTPUT);
     pinMode(led3, OUTPUT);
     pinMode(led4, OUTPUT);
     pinMode(led_R1, OUTPUT);
     pinMode(led_G1, OUTPUT);
     pinMode(led_B1, OUTPUT);
     pinMode(led_R2, OUTPUT);
     pinMode(led_G2, OUTPUT);
     pinMode(led_B2, OUTPUT);
}

void loop(){while(1){
  if(Serial.available()){
      inData[iteration] = Serial.read();
      iteration++;
      if(iteration>2) {Update();}
      if(inData[0] != Sync) {Clear();}
  }
}}

void Update() {
//BUTTONS 

      if(bitRead(inData[1],0)){digitalWrite(led1, HIGH);}
      else {digitalWrite(led1, LOW);}
      
      if(bitRead(inData[1],1)){digitalWrite(led2, HIGH);}
      else {digitalWrite(led2, LOW);}
      
      if(bitRead(inData[1],2)){digitalWrite(led3, HIGH);}
      else {digitalWrite(led3, LOW);}
      
      if(bitRead(inData[1],3)){digitalWrite(led4, HIGH);}
      else {digitalWrite(led4, LOW);}

//SIDES
    
      if(bitRead(inData[2],0)){digitalWrite(led_R1, HIGH);}
      else {digitalWrite(led_R1, LOW);}
      
      if(bitRead(inData[2],1)){digitalWrite(led_G1, HIGH);}
      else {digitalWrite(led_G1, LOW);}
      
      if(bitRead(inData[2],2)){digitalWrite(led_B1, HIGH);}
      else {digitalWrite(led_B1, LOW);}
      
      if(bitRead(inData[2],3)){digitalWrite(led_R2, HIGH);}
      else {digitalWrite(led_R2, LOW);}
      
      if(bitRead(inData[2],4)){digitalWrite(led_G2, HIGH);}
      else {digitalWrite(led_G2, LOW);}
    
      if(bitRead(inData[2],5)){digitalWrite(led_B2, HIGH);}
      else {digitalWrite(led_B2, LOW);}
      
      Clear();
}
    
void Clear() {
      iteration = 0;
      inData[0] = 0;
      inData[1] = 0;
      inData[2] = 0;
}
