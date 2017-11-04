int regress;

void setup() {  
  Serial.begin(9600);
  
  pinMode(18, OUTPUT);
  digitalWrite (18, LOW); 
  pinMode(19, OUTPUT);
  digitalWrite (19, LOW);
  pinMode(0, INPUT_PULLUP);
  pinMode(17, INPUT);  
}

void loop() {
  bool startCheck = digitalRead(0);
  
  if (!startCheck) {    
    digitalWrite (18, LOW);         //turn off LEDs
    digitalWrite (19, LOW);
    regress = 0;
    bool testCheck = (check00() || check02() || check04() || check08() || check10() || check20() || check27() || check86()); 
    
    if(!testCheck && regress != 0){ //passed at least one test and failed at least one test
      digitalWrite (18, HIGH);      
      digitalWrite (19, HIGH);
    }
    else if (regress == 10) {       //regress will only reach 10 if it passed all regression checks
      digitalWrite (19, HIGH);
    } 
    else if(!testCheck){            //regress stays at zero if no IC checks passed
      digitalWrite (18, HIGH);
    }
  }    
}

bool check00() { //Run to check for a 74HC00
  Serial.println("----------------Checking 74HC00----------------");
  int Input00[] = {7, 2, 4, 5, 9, 10, 12, 13}; //Input and output pin # arrays (for the IC)
  int Output00[] = {3, 6, 8, 11};

  for (int i = 0; i < 8; i++) { //Pinmode for ardunio board
    pinMode(Input00[i], OUTPUT);
  }

  for (int j = 0; j < 4; j++) {
    pinMode(Output00[j], INPUT);
  }

  for(regress; regress < 10; regress++){
    int count = 0;
    for (int k = 0; k < 4; k++) { //k loop is ALWAYS for each gate
      Serial.print("----GATE");
      Serial.print(k + 1);
      Serial.print("----");
      Serial.println();
      
      for (int i = 0; i < 2; i++) { //i, j, n, m loops are for inputs to each gate
        for (int j = 0; j < 2; j++) {
          digitalWrite(Input00[count], i);
          digitalWrite(Input00[count + 1], j);
          int x = digitalRead(Output00[k]);
          if ((i&&j) != !x){
            Serial.println("CHECK FAILED");
            Serial.println();
            return false;
          }
          Serial.print(i); 
          Serial.print(j);
          Serial.print("|");
          Serial.println(x);
        }
      }
    count += 2;  
    }
  }

  Serial.println("CHECK PASSED");
  return true;
}

bool check02() { //Run to check for a 74HC02
  Serial.println("----------------Checking 74HC02----------------");
  int Input02[] = {2, 3, 5, 6, 8, 9, 11, 12}; //Input and output pin # arrays (for the IC)
  int Output02[] = {7, 4, 10, 13};

  for (int i = 0; i < 8; i++) { //Pinmode for ardunio board
    pinMode(Input02[i], OUTPUT);
  }

  for (int j = 0; j < 4; j++) {
    pinMode(Output02[j], INPUT);
  }


  for(regress; regress < 10; regress++){
    int count = 0;
    for (int k = 0; k < 4; k++) {
      Serial.print("----GATE");
      Serial.print(k + 1);
      Serial.print("----");
      Serial.println();
      
      for (int i = 0; i < 2; i++) {
        for (int j  = 0; j < 2; j++) {
          digitalWrite(Input02[count], i);
          digitalWrite(Input02[count + 1], j);
          int x = digitalRead(Output02[k]);
          if ((i||j)!= !x){
            Serial.println("CHECK FAILED");
            Serial.println();
            return false;
          }
          Serial.print(i); 
          Serial.print(j);
          Serial.print("|");
          Serial.println(x);
        }
      }
    count += 2;  
    }
  }
  
  Serial.println("CHECK PASSED");
  return true;
}

bool check04() { //Run to check for a 74HC04
  Serial.println("----------------Checking 74HC04----------------");
  int Input04[] = {7, 3, 5, 9, 11, 13}; //Input and output pin # arrays
  int Output04[] = {2, 4, 6, 8, 10, 12};

  for (int i = 0; i < 6; i++) { //Pinmode for ardunio board
    pinMode(Input04[i], OUTPUT);
  }

  for (int j = 0; j < 6; j++) {
    pinMode(Output04[j], INPUT);
  }
  
  for(regress; regress < 10; regress++){
    for (int k = 0; k < 6; k++) {
      Serial.print("----GATE");
      Serial.print(k + 1);
      Serial.print("----");
      Serial.println();
      
      for (int i = 0; i < 2; i++) {
        digitalWrite(Input04[k], i);
        delay(50);
        int x = digitalRead(Output04[k]);
        Serial.print(i);
        Serial.print("|");
        Serial.println(x);
        if (x == i) {
          Serial.println("CHECK FAILED");
          Serial.println();
          return false;
        }
        delay(50);      
      }
    }
  }

  Serial.println("CHECK PASSED");
  return true;
}

bool check08() { //Run to check for a 74HC08
  Serial.println("----------------Checking 74HC08----------------");
  int Input08[] = {7, 2, 4, 5, 9, 10, 12, 13}; //Input and output pin # arrays
  int Output08[] = {3, 6, 8, 11};

  for (int i = 0; i < 8; i++) { //Pinmode for ardunio board
    pinMode(Input08[i], OUTPUT);
  }

  for (int j = 0; j < 4; j++) {
    pinMode(Output08[j], INPUT);
  }

  for(regress; regress < 10; regress++){
    int count = 0;  
    for (int k = 0; k < 4; k++) {
      Serial.print("----GATE");
      Serial.print(k + 1);
      Serial.print("----");
      Serial.println();
      
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          digitalWrite(Input08[count], i);
          digitalWrite(Input08[count + 1], j);
          int x = digitalRead(Output08[k]);
          if ((i&&j)!= x){
            Serial.println("CHECK FAILED");
            Serial.println();
            return false;
          }
          Serial.print(i);
          Serial.print(j);
          Serial.print("|");
          Serial.println(x);
        }
      }    
      count += 2;
    }
  }

  Serial.println("CHECK PASSED");
  return true;
}

bool check10() { //Run to check for a 74HC10
  Serial.println("----------------Checking 74HC10----------------");
  int Input10[] = {7, 2, 13, 3, 4, 5, 9, 10, 11}; //Input and output pin # arrays
  int Output10[] = {12, 6, 8};

  for (int i = 0; i < 9; i++) { //Pinmode for ardunio board
    pinMode(Input10[i], OUTPUT);
  }

  for (int j = 0; j < 3; j++) {
    pinMode(Output10[j], INPUT);
  }

  for(regress; regress < 10; regress++){
    int count = 0;  
    for (int k = 0; k < 3; k++) {
      Serial.print("----GATE");
      Serial.print(k + 1);
      Serial.print("----");
      Serial.println();
      
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          for (int n = 0; n < 2; n++) {
            digitalWrite(Input10[count], i);
            digitalWrite(Input10[count + 1], j);
            digitalWrite(Input10[count + 2], n);
            int x = digitalRead(Output10[k]);
            if ((i&&j&&n)!= !x){
              Serial.println("CHECK FAILED");
              Serial.println();
              return false;
            }
            Serial.print(i);
            Serial.print(j);
            Serial.print(n);
            Serial.print("|");
            Serial.println(x);
          }
        }
      }      
      count += 3;
    }
  }

  Serial.println("CHECK PASSED");
  return true;
}
  
bool check20() { //Run to check for a 74HC20
  Serial.println("----------------Checking 74HC20----------------");
  int Input20[] = {7, 2, 4, 5, 9, 10, 12, 13}; //Input and output pin # arrays
  int Output20[] = {6, 8};
  
  for (int i = 0; i < 8; i++) { //Pinmode for ardunio board
    pinMode(Input20[i], OUTPUT);
  }

  for (int j = 0; j < 2; j++) {
    pinMode(Output20[j], INPUT);
  }

  for(regress; regress < 10; regress++){
    int count = 0;  
    for (int k = 0; k < 2; k++) {
      Serial.print("----GATE");
      Serial.print(k + 1);
      Serial.print("----");
      Serial.println();
      
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          for (int n = 0; n < 2; n++) {
            for (int m = 0; m < 2; m++) {
              digitalWrite(Input20[count], i);
              digitalWrite(Input20[count + 1], j);
              digitalWrite(Input20[count + 2], n);            
              digitalWrite(Input20[count + 3], m);
              int x = digitalRead(Output20[k]);
              if ((i&&j&&n&&m)!= !x){
                Serial.println("CHECK FAILED");
                Serial.println();
                return false;
              }
              Serial.print(i);
              Serial.print(j);
              Serial.print(n);            
              Serial.print(m);
              Serial.print("|");
              Serial.println(x);
            }
          }
        }
      }    
      count += 4;
    }
  }

  Serial.println("CHECK PASSED");
  return true;
}

bool check27() { //Run to check for a 74HC27
  Serial.println("----------------Checking 74HC27----------------");
  int Input27[] = {7, 2, 13, 3, 4, 5, 9, 10, 11}; //Input and output pin # arrays
  int Output27[] = {12, 6, 8};

  for (int i = 0; i < 9; i++) { //Pinmode for ardunio board
    pinMode(Input27[i], OUTPUT);
  }

  for (int j = 0; j < 3; j++) {
    pinMode(Output27[j], INPUT);
  }

  for(regress; regress < 10; regress++){
    int count = 0;
    for (int k = 0; k < 3; k++) {
      Serial.print("----GATE");
      Serial.print(k + 1);
      Serial.print("----");
      Serial.println();
      
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          for (int n = 0; n < 2; n++) {
            digitalWrite(Input27[count], i);
            digitalWrite(Input27[count + 1], j);
            digitalWrite(Input27[count + 2], n);
            int x = digitalRead(Output27[k]);
            if ((i||j||n)!= !x){
              Serial.println("CHECK FAILED");
              Serial.println();
              return false;
            }
            Serial.print(i);
            Serial.print(j);
            Serial.print(n);
            Serial.print("|");
            Serial.println(x);
          }
        }
      }      
      count += 3;
    }
  }

  Serial.println("CHECK PASSED");
  return true;
}

bool check86() { //Run to check for a 74HC86
  Serial.println("----------------Checking 74HC86----------------");
  int Input86[] = {7, 2, 4, 5, 9, 10, 12, 13}; //Input and output pin # arrays
  int Output86[] = {3, 6, 8, 11};

  for (int i = 0; i < 8; i++) { //Pinmode for ardunio board
    pinMode(Input86[i], OUTPUT);
  }

  for (int j = 0; j < 4; j++) {
    pinMode(Output86[j], INPUT);
  }

  for(regress; regress < 10; regress++){
    int count = 0;  
    for (int k = 0; k < 4; k++) {
      Serial.print("----GATE");
      Serial.print(k + 1);
      Serial.print("----");
      Serial.println();
      
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          digitalWrite(Input86[count], i);
          digitalWrite(Input86[count + 1], j);
          int x = digitalRead(Output86[k]);
          if ((i^j)!= x){
            Serial.println("CHECK FAILED");
            Serial.println();
            return false;
          }
          Serial.print(i);
          Serial.print(j);
          Serial.print("|");
          Serial.println(x);
        }
      }      
      count += 2;
    }
  }
  
  Serial.println("CHECK PASSED");
  return true;
}


