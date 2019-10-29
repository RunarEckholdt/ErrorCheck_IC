
//pin på IC:    1  2  3  4  5  6  8  9  10  11  12  13
const int pins[] = {30, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13}; //Pins på arduino


enum state {NOT, OR, AND, XOR, NAND, NOR, NONE};

state mode;
String brokenPins = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < sizeof(pins); i++) {
    digitalWrite(pins[i], LOW);
  }


}

void loop() {
  
  readInput();


}

void manageMode(String input) {
  if (input == "NOT") {
    mode = NOT;
  }
  else if (input == "OR") {
    mode = OR;
  }
  else if (input == "AND") {
    mode = AND;
  }
  else if (input == "XOR") {
    mode = XOR;
  }
  else if (input == "NAND") {
    mode = NAND;
  }
  else if (input == "NOR") {
    mode = NOR;
  }else{
    mode = NONE;
    }
}

void readInput() {
  //leser av input og sender til riktig funksjon
  Serial.println("NB! Feil type kan føre til brenning av IC så velg riktig");
  Serial.println("Velg logisk type: (not,or,and,xor,nand,nor)");

  while (!Serial.available());
  String input = Serial.readString();
  input.toUpperCase();

  manageMode(input);

  switch (mode) {
    case NOT:
      testNot();
      break;
    case AND:
      testAnd();
      break;
    case OR:
      testOr();
      break;
    case XOR:
      testXor();
      break;
    case NOR:
      testNor();
      break;
    case NAND:
      testNand();
      break;
    default:
      Serial.println("Det er ikke et gyldig input. Prøv igjen");
  }
}









void runTestNot(int in, int out) {
  bool x;
  bool pinsBroke = false;
  Serial.print("Tester pin ");
  if (in == pins[0]) {
    Serial.print("1");
  }
  else {
    Serial.print(in);
  }
  Serial.println("...");
  digitalWrite(in, LOW);
  x = digitalRead(out);
  if (x == LOW) {
    Serial.print("Feil ved test av pin ");
    if (in == pins[0]) {
      Serial.print("1");
    }
    else {
      Serial.print(in);
    }
    Serial.println("...");

    Serial.println("Prøver igjen..");
    delay(500);
    digitalWrite(in, LOW);
    x = digitalRead(out);
    if (x == LOW) {
      Serial.print("Feil ved invertering av pin ");
      if (in == pins[0]) {
        Serial.print("1");
      }
      else {
        Serial.print(in);
      }
      Serial.println("...");
      pinsBroke = true;
    }
  }



  delay(500);
  digitalWrite(in, HIGH);
  x = digitalRead(out);
  if (x == HIGH) {
    Serial.print("Feil ved test av pin ");
    if (in == pins[0]) {
      Serial.print("1");
    }
    else {
      Serial.print(in);
    }
    Serial.println("...");
    Serial.println("Prøver igjen..");
    delay(500);
    digitalWrite(in, HIGH);
    x = digitalRead(out);
    if (x == HIGH) {
      Serial.print("Feil ved invertering av pin ");
      if (in == pins[0]) {
        Serial.print("1");
      }
      else {
        Serial.print(in);
      }
      Serial.println("...");
      pinsBroke = true;
    }
  }
  if (pinsBroke == true) {
    if (in == pins[0]) {
      brokenPins.concat("1");
    }
    else {
      brokenPins.concat((String)in);
    }
    brokenPins.concat(",");
    brokenPins.concat((String)out);
    brokenPins.concat(",");
  }


}

void testNot() {
  brokenPins = "";
  pinMode(pins[0], OUTPUT);
  pinMode(pins[1], INPUT);
  pinMode(pins[2], OUTPUT);
  pinMode(pins[3], INPUT);
  pinMode(pins[4], OUTPUT);
  pinMode(pins[5], INPUT);
  pinMode(pins[11], OUTPUT);
  pinMode(pins[10], INPUT);
  pinMode(pins[9], OUTPUT);
  pinMode(pins[8], INPUT);
  pinMode(pins[7], OUTPUT);
  pinMode(pins[6], INPUT);

  int in;
  int out;
  Serial.println("Starter test av NOT chip");
  //tester pin 1
  in = pins[0];
  out = pins[1];
  delay(500);
  runTestNot(in, out);



  //tester pin 3
  in = pins[2];
  out = pins[3];
  delay(500);
  runTestNot(in, out);



  //tester pin 5
  in = pins[4];
  out = pins[5];
  delay(500);
  runTestNot(in, out);



  //tester pin 13
  in = pins[11];
  out = pins[10];
  delay(500);
  runTestNot(in, out);


  //tester pin 11
  in = pins[9];
  out = pins[8];
  delay(500);
  runTestNot(in, out);

  //tester pin 9
  in = pins[7];
  out = pins[6];
  delay(500);
  runTestNot(in, out);






  if (brokenPins != "") {
    Serial.print("Ødelagte pinns: ");
    Serial.println(brokenPins);

  } else {
    Serial.println("Alt gikk vell");
  }

  Serial.println("Restart program for å teste på nytt");
  while (1);

}



















void runTestAnd(int pin1, int pin2, int pin3) {

  bool pinsBroke = false;
  Serial.print("Tester pin ");
  if (pin1 == pins[0]) {
    Serial.print("1");
  }
  else {
    Serial.print(pin1);
  }
  Serial.print(" og ");
  Serial.print(pin2);
  Serial.println("...");
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  bool x = digitalRead(pin3);
  if (x == HIGH) {
    Serial.print("Feil ved test av pin ");
    if (pin1 == pins[0]) {
      Serial.print("1");
    }
    else {
      Serial.print(pin1);
    }
    Serial.print(" og ");
    Serial.print(pin2);
    Serial.println("...");
    Serial.println("Prøver igjen..");
    delay(500);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    x = digitalRead(pin3);
    if (x == HIGH) {
      Serial.println("Output ");
      Serial.print(pin3);
      Serial.println("gir HIGH selv om inputs er low...");
      pinsBroke = true;
    }
  }



  delay(500);
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  x = digitalRead(pin3);
  if (x == LOW) {
    Serial.print("Feil ved test av pin ");
    if (pin1 == pins[0]) {
      Serial.print("1");
    }
    else {
      Serial.print(pin1);
    }
    Serial.print(" og ");
    Serial.print(pin2);
    Serial.println("...");
    Serial.println("Prøver igjen..");
    delay(500);
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    x = digitalRead(pin3);
    if (x == LOW) {
      Serial.print("Output ");
      Serial.print(pin3);
      Serial.println(" gir LOW selv om inputs er HIGH...");
      pinsBroke = true;
    }
  }

  if (pinsBroke == true) {
    if (pin1 == pins[0]) {
      brokenPins.concat("1");
    }
    else {
      brokenPins.concat((String)pin1);
    }
    brokenPins.concat(",");
    brokenPins.concat((String)pin2);
    brokenPins.concat(",");
    brokenPins.concat((String)pin3);
    brokenPins.concat(",");
  }
}


void testAnd() {
  pinMode(pins[0], OUTPUT);
  pinMode(pins[1], OUTPUT);
  pinMode(pins[2], INPUT);
  pinMode(pins[3], OUTPUT);
  pinMode(pins[4], OUTPUT);
  pinMode(pins[5], INPUT);
  pinMode(pins[11], OUTPUT);
  pinMode(pins[10], OUTPUT);
  pinMode(pins[9], INPUT);
  pinMode(pins[8], OUTPUT);
  pinMode(pins[7], OUTPUT);
  pinMode(pins[6], INPUT);

  byte in1;
  byte in2;
  byte out;
  Serial.println("Starter test av AND chip");
  brokenPins = "";



  //tester pin 1 og 2
  in1 = pins[0];
  in2 = pins[1];
  out = pins[2];
  delay(500);
  runTestAnd(in1, in2, out);

  //tester pin 4 og 5
  in1 = pins[3];
  in2 = pins[4];
  out = pins[5];
  delay(500);
  runTestAnd(in1, in2, out);



  //tester pin 13 og 12
  in1 = pins[11];
  in2 = pins[10];
  out = pins[9];
  delay(500);
  runTestAnd(in1, in2, out);



  //tester pin 10 og 9
  in1 = pins[8];
  in2 = pins[7];
  out = pins[6];
  delay(500);
  runTestAnd(in1, in2, out);





  if (brokenPins != "") {
    Serial.print("Ødelagte pinns: ");
    Serial.println(brokenPins);

  } else {
    Serial.println("Alt gikk vell");
  }

  Serial.println("Restart program for å teste på nytt");
  while (1);














}

void runTestOr(int pin1, int pin2, int pin3) {
  bool pin1Broke = false;
  bool pin2Broke = false;
  bool pin3Broke = false;


  Serial.print("Tester pin ");
  if (pin1 == pins[0]) {
    Serial.print("1");
  }
  else {
    Serial.print(pin1);
  }
  Serial.print(" og ");
  Serial.print(pin2);
  Serial.println("...");
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  bool x = digitalRead(pin3);
  if (x == HIGH) {
    Serial.print("Feil ved test av pin ");
    if (pin1 == pins[0]) {
      Serial.print("1");
    }
    else {
      Serial.print(pin1);
    }
    Serial.print(" og ");
    Serial.print(pin2);
    Serial.println("...");
    Serial.println("Prøver igjen..");
    delay(500);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    x = digitalRead(pin3);
    if (x == HIGH) {
      Serial.println("Output ");
      Serial.print(pin3);
      Serial.println("gir HIGH selv om inputs er low...");
      pin3Broke = true;
    }
  }



  delay(500);
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  x = digitalRead(pin3);
  if (x == LOW) {
    Serial.print("Feil ved test av pin ");
    if (pin1 == pins[0]) {
      Serial.print("1");
    }
    else {
      Serial.print(pin1);
    }
    Serial.println("...");
    Serial.println("Prøver igjen..");
    delay(500);
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    x = digitalRead(pin3);
    if (x == LOW) {
      Serial.print("Output ");
      Serial.print(pin3);
      Serial.print(" gir LOW selv om input ");
      if (pin1 == pins[0]) {
        Serial.print("1");
      }
      else {
        Serial.print(pin1);
      }
      Serial.println(" er HIGH...");
      pin1Broke = true;
    }
  }

  delay(500);
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  x = digitalRead(pin3);
  if (x == LOW) {
    Serial.print("Feil ved test av pin ");
    Serial.print(pin2);
    Serial.println("...");
    Serial.println("Prøver igjen..");
    delay(500);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    x = digitalRead(pin3);
    if (x == LOW) {
      Serial.print("Output ");
      Serial.print(pin3);
      Serial.print(" gir LOW selv om input ");
      Serial.print(pin2);
      Serial.println(" er HIGH...");
      pin2Broke = true;

    }


  }
  if (pin3Broke == true) {
    if (pin1 == pins[0]) {
      brokenPins.concat("1");
    }
    else {
      brokenPins.concat((String)pin1);
    }
    brokenPins.concat(",");
    brokenPins.concat((String)pin2);
    brokenPins.concat(",");
    brokenPins.concat((String)pin3);
    brokenPins.concat(",");
  } else if (pin1Broke == true && pin2Broke == false) {
    if (pin1 == pins[0]) {
      brokenPins.concat("1");
    }
    else {
      brokenPins.concat((String)pin1);
    }
    brokenPins.concat(",");
  } else if (pin2Broke == true && pin1Broke == false) {
    brokenPins.concat((String)pin2);
    brokenPins.concat(",");
  } else if (pin1Broke == true && pin2Broke == true) {
    if (pin1 == pins[0]) {
      brokenPins.concat("1");
    }
    else {
      brokenPins.concat((String)pin1);
    }
    brokenPins.concat(",");
    brokenPins.concat((String)pin2);
    brokenPins.concat(",");
    brokenPins.concat((String)pin3);
    brokenPins.concat(",");
  }

}

void testOr() {
  pinMode(pins[0], OUTPUT);
  pinMode(pins[1], OUTPUT);
  pinMode(pins[2], INPUT);
  pinMode(pins[3], OUTPUT);
  pinMode(pins[4], OUTPUT);
  pinMode(pins[5], INPUT);
  pinMode(pins[11], OUTPUT);
  pinMode(pins[10], OUTPUT);
  pinMode(pins[9], INPUT);
  pinMode(pins[8], OUTPUT);
  pinMode(pins[7], OUTPUT);
  pinMode(pins[6], INPUT);

  brokenPins = "";
  int in1;
  int in2;
  int out;

  Serial.println("Starter test av OR chip");

  //tester pin 1 og 2
  in1 = pins[0];
  in2 = pins[1];
  out = pins[2];
  delay(500);
  runTestOr(in1, in2, out);

  //tester pin 4 og 5
  in1 = pins[3];
  in2 = pins[4];
  out = pins[5];
  delay(500);
  runTestOr(in1, in2, out);


  //tester pin 13 og 12
  in1 = pins[11];
  in2 = pins[10];
  out = pins[9];
  delay(500);
  runTestOr(in1, in2, out);

  //tester pin 10 og 9
  in1 = pins[8];
  in2 = pins[7];
  out = pins[6];
  delay(500);
  runTestOr(in1, in2, out);


  if (brokenPins != "") {
    Serial.print("Ødelagte pinns: ");
    Serial.println(brokenPins);

  } else {
    Serial.println("Alt gikk vell");
  }

  Serial.println("Restart program for å teste på nytt");
  while (1);






}

void runTestXor(int pin1, int pin2, int pin3) {
  bool pin1Broke = false;
  bool pin2Broke = false;
  bool pin3Broke = false;
  Serial.print("Tester pin ");
  if (pin1 == pins[0]) {
    Serial.print("1");
  }
  else {
    Serial.print(pin1);
  }
  Serial.print(" og ");
  Serial.print(pin2);
  Serial.println("...");




  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  delay(30);
  bool x = digitalRead(pin3);
  if (x == HIGH) {
    Serial.print("Feil ved test av pin ");
    if (pin1 == pins[0]) {
      Serial.print("1");
    }
    else {
      Serial.print(pin1);
    }
    Serial.print(" og ");
    Serial.print(pin2);
    Serial.println("...");
    Serial.println("Prøver igjen..");
    delay(500);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    x = digitalRead(pin3);
    if (x == HIGH) {
      Serial.print("Output ");
      Serial.print(pin3);
      Serial.println(" gir HIGH selv om inputs er low...");
      pin3Broke = true;

    }
  }



  delay(500);
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  delay(30);
  x = digitalRead(pin3);
  if (x == LOW) {
    Serial.print("Feil ved test av pin ");
    if (pin1 == pins[0]) {
      Serial.print("1");
    }
    else {
      Serial.print(pin1);
    }
    Serial.println("...");
    Serial.println("Prøver igjen..");
    delay(500);
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    x = digitalRead(pin3);
    if (x == LOW) {
      Serial.print("Output ");
      Serial.print(pin3);
      Serial.print(" gir LOW selv om input ");
      if (pin1 == pins[0]) {
        Serial.print("1");
      }
      else {
        Serial.print(pin1);
      }
      Serial.println(" er HIGH...");
      pin1Broke = true;
    }
  }

  delay(500);
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  delay(30);
  x = digitalRead(pin3);
  if (x == LOW) {
    Serial.print("Feil ved test av pin ");
    Serial.print(pin2);
    Serial.println("...");
    Serial.println("Prøver igjen..");
    delay(500);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    x = digitalRead(pin3);
    if (x == LOW) {
      Serial.print("Output ");
      Serial.print(pin3);
      Serial.print(" gir LOW selv om input ");
      Serial.print(pin2);
      Serial.println(" er HIGH...");
      pin2Broke = true;

    }


  }


  if (pin1Broke == false && pin2Broke == false) {
    delay(500);
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    x = digitalRead(pin3);
    if (x == HIGH) {
      Serial.print("Feil ved test av pin ");
      Serial.print(pin2);
      Serial.println("...");
      Serial.println("Prøver igjen..");
      delay(500);
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);
      x = digitalRead(pin3);
      if (x == HIGH) {
        Serial.print("Output ");
        Serial.print(pin3);
        Serial.println(" gir HIGH selv om begge inputs er HIGH");
        pin3Broke = true;


      }


    }
  }

  if (pin3Broke == true) {
    if (pin1 == pins[0]) {
      brokenPins.concat("1");
    }
    else {
      brokenPins.concat((String)pin1);
    }
    brokenPins.concat(",");
    brokenPins.concat((String)pin2);
    brokenPins.concat(",");
    brokenPins.concat((String)pin3);
    brokenPins.concat(",");
  } else if (pin1Broke == true && pin2Broke == false) {
    if (pin1 == pins[0]) {
      brokenPins.concat("1");
    }
    else {
      brokenPins.concat((String)pin1);
    }
    brokenPins.concat(",");
  } else if (pin2Broke == true && pin1Broke == false) {
    brokenPins.concat((String)pin2);
    brokenPins.concat(",");
  } else if (pin1Broke == true && pin2Broke == true) {
    if (pin1 == pins[0]) {
      brokenPins.concat("1");
    }
    else {
      brokenPins.concat((String)pin1);
    }
    brokenPins.concat(",");
    brokenPins.concat((String)pin2);
    brokenPins.concat(",");
    brokenPins.concat((String)pin3);
    brokenPins.concat(",");
  }

}

void testXor() {
  pinMode(pins[0], OUTPUT);
  pinMode(pins[1], OUTPUT);
  pinMode(pins[2], INPUT);
  pinMode(pins[3], OUTPUT);
  pinMode(pins[4], OUTPUT);
  pinMode(pins[5], INPUT);
  pinMode(pins[11], OUTPUT);
  pinMode(pins[10], OUTPUT);
  pinMode(pins[9], INPUT);
  pinMode(pins[8], OUTPUT);
  pinMode(pins[7], OUTPUT);
  pinMode(pins[6], INPUT);


  brokenPins = "";
  int in1;
  int in2;
  int out;

  Serial.println("Starter test av XOR chip");

  //tester pin 1 og 2
  in1 = pins[0];
  in2 = pins[1];
  out = pins[2];
  delay(500);
  runTestXor(in1, in2, out);

  //tester pin 4 og 5
  in1 = pins[3];
  in2 = pins[4];
  out = pins[5];
  delay(500);
  runTestXor(in1, in2, out);

  //tester pin 13 og 12
  in1 = pins[11];
  in2 = pins[10];
  out = pins[9];
  delay(500);
  runTestXor(in1, in2, out);

  //tester pin 10 og 9
  in1 = pins[8];
  in2 = pins[7];
  out = pins[6];
  delay(500);
  runTestXor(in1, in2, out);



  if (brokenPins != "") {
    Serial.print("Ødelagte pinns: ");
    Serial.println(brokenPins);

  } else {
    Serial.println("Alt gikk vell");
  }

  Serial.println("Restart program for å teste på nytt");
  while (1);

}

void runTestNor(int pin1, int pin2, int pin3) {
  bool pin1Broke = false;
  bool pin2Broke = false;
  bool pin3Broke = false;
  Serial.print("Tester pin ");
  Serial.print(pin1);
  Serial.print(" og ");
  Serial.print(pin2);
  Serial.println("...");


  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  delay(30);
  bool x = digitalRead(pin3);
  if (x == LOW) {
    Serial.print("Feil ved test av pin ");
    Serial.print(pin1);
    Serial.print(" og ");
    Serial.print(pin2);
    Serial.println("...");
    Serial.println("Prøver igjen..");

    
    delay(500);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    x = digitalRead(pin3);
    if (x == LOW) {
      Serial.print("Output ");
      if (pin3 == pins[0]) {
      Serial.print("1");
    }
    else {
      Serial.print(pin3);
    }
      Serial.println("gir LOW selv om inputs er low...");
      pin3Broke = true;
    }
  }

  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  delay(30);
  x = digitalRead(pin3);
  if (x == HIGH) {
    Serial.print("Feil ved test av pin ");
    Serial.print(pin1);
    Serial.print(" og ");
    Serial.print(pin2);
    Serial.println("...");
    Serial.println("Prøver igjen..");
    delay(500);
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    x = digitalRead(pin3);
    if (x == HIGH) {
      Serial.print("Output ");
      if (pin3 == pins[0]) {
      Serial.print("1");
    }
    else {
      Serial.print(pin3);
    }
      Serial.print(" gir HIGH selv om input ");
        Serial.print(pin1);
      Serial.println(" er HIGH...");
      pin1Broke = true;
    }
  }

  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  delay(30);
  x = digitalRead(pin3);
  if (x == HIGH) {
    Serial.print("Feil ved test av pin ");
    Serial.print(pin1);
    Serial.print(" og ");
    Serial.print(pin2);
    Serial.println("...");
    Serial.println("Prøver igjen..");
    delay(500);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    x = digitalRead(pin3);
    if (x == HIGH) {
      Serial.print("Output ");
      if (pin3 == pins[0]) {
      Serial.print("1");
    }
    else {
      Serial.print(pin3);
    }
      Serial.print(" gir HIGH selv om input ");
      Serial.print(pin2);
      Serial.println(" er HIGH...");
      pin2Broke = true;
    }
  }


  if (pin3Broke == true) {
    if (pin1 == pins[0]) {
      brokenPins.concat("1");
    }
    else {
      brokenPins.concat((String)pin1);
    }
    brokenPins.concat(",");
    brokenPins.concat((String)pin2);
    brokenPins.concat(",");
    brokenPins.concat((String)pin3);
    brokenPins.concat(",");
  } else if (pin1Broke == true && pin2Broke == false) {
    if (pin1 == pins[0]) {
      brokenPins.concat("1");
    }
    else {
      brokenPins.concat((String)pin1);
    }
    brokenPins.concat(",");
  } else if (pin2Broke == true && pin1Broke == false) {
    brokenPins.concat((String)pin2);
    brokenPins.concat(",");
  } else if (pin1Broke == true && pin2Broke == true) {
    if (pin1 == pins[0]) {
      brokenPins.concat("1");
    }
    else {
      brokenPins.concat((String)pin1);
    }
    brokenPins.concat(",");
    brokenPins.concat((String)pin2);
    brokenPins.concat(",");
    brokenPins.concat((String)pin3);
    brokenPins.concat(",");
  }




}

void testNor() {
  pinMode(pins[0], INPUT);
  pinMode(pins[1], OUTPUT);
  pinMode(pins[2], OUTPUT);
  pinMode(pins[3], INPUT);
  pinMode(pins[4], OUTPUT);
  pinMode(pins[5], OUTPUT);
  pinMode(pins[11], INPUT);
  pinMode(pins[10], OUTPUT);
  pinMode(pins[9], OUTPUT);
  pinMode(pins[8], INPUT);
  pinMode(pins[7], OUTPUT);
  pinMode(pins[6], OUTPUT);

  brokenPins = "";
  int in1;
  int in2;
  int out;

  Serial.println("Starter test av NOR..");

  //tester pin 1 og 2
  out = pins[0];
  in1 = pins[1];
  in2 = pins[2];
  delay(500);
  runTestNor(in1, in2, out);

  //tester pin 4 og 5
  out = pins[3];
  in1 = pins[4];
  in2 = pins[5];
  delay(500);
  runTestNor(in1, in2, out);

  //tester pin 13 og 12
  out = pins[11];
  in1 = pins[10];
  in2 = pins[9];
  delay(500);
  runTestNor(in1, in2, out);

  //tester pin 10 og 9
  out = pins[8];
  in1 = pins[7];
  in2 = pins[6];
  delay(500);
  runTestNor(in1, in2, out);


  if (brokenPins != "") {
    Serial.print("Ødelagte pinns: ");
    Serial.println(brokenPins);

  } else {
    Serial.println("Alt gikk vell");
  }

  Serial.println("Restart program for å teste på nytt");
  while (1);


}


void runTestNand(int pin1, int pin2, int pin3) {
  bool pin1Broke = false;
  bool pin2Broke = false;
  bool pin3Broke = false;
  Serial.print("Tester pin ");
  if (pin1 == pins[0]) {
    Serial.print("1");
  }
  else {
    Serial.print(pin1);
  }
  Serial.print(" og ");
  Serial.print(pin2);
  Serial.println("...");


  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  delay(30);
  bool x = digitalRead(pin3);
  if (x == LOW) {
    Serial.print("Feil ved test av pin ");
    if (pin1 == pins[0]) {
      Serial.print("1");
    }
    else {
      Serial.print(pin1);
    }
    Serial.print(" og ");
    Serial.print(pin2);
    Serial.println("...");
    Serial.println("Prøver igjen..");
    delay(500);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    x = digitalRead(pin3);
    if (x == LOW) {
      Serial.print("Output ");
      Serial.print(pin3);
      Serial.println(" gir LOW selv om inputs er low...");
      pin3Broke = true;
    }
  }

  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  delay(30);
  x = digitalRead(pin3);
  if (x == LOW) {
    Serial.print("Feil ved test av pin ");
    if (pin1 == pins[0]) {
      Serial.print("1");
    }
    else {
      Serial.print(pin1);
    }
    Serial.print(" og ");
    Serial.print(pin2);
    Serial.println("...");
    Serial.println("Prøver igjen..");
    delay(500);
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    x = digitalRead(pin3);
    if (x == LOW) {
      Serial.print("Output ");
      Serial.print(pin3);
      Serial.print(" gir LOW selv om input ");
      Serial.print(pin2);
      Serial.println(" er low...");
      pin3Broke = true;
    }
  }

  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  delay(30);
  x = digitalRead(pin3);
  if (x == LOW) {
    Serial.print("Feil ved test av pin ");
    if (pin1 == pins[0]) {
      Serial.print("1");
    }
    else {
      Serial.print(pin1);
    }
    Serial.print(" og ");
    Serial.print(pin2);
    Serial.println("...");
    Serial.println("Prøver igjen..");
    delay(500);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    x = digitalRead(pin3);
    if (x == LOW) {
      Serial.print("Output ");
      Serial.print(pin3);
      Serial.println(" gir LOW selv om input ");
      if (pin1 == pins[0]) {
        Serial.print("1");
      }
      else {
        Serial.print(pin1);
      }
      Serial.println(" er low...");
      pin3Broke = true;
    }
  }

  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  delay(30);
  x = digitalRead(pin3);
  if (x == HIGH) {
    Serial.print("Feil ved test av pin ");
    if (pin1 == pins[0]) {
      Serial.print("1");
    }
    else {
      Serial.print(pin1);
    }
    Serial.print(" og ");
    Serial.print(pin2);
    Serial.println("...");
    Serial.println("Prøver igjen..");
    delay(500);
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    x = digitalRead(pin3);
    if (x == HIGH) {
      Serial.print("Output ");
      Serial.print(pin3);
      Serial.println(" gir HIGH selv om inputs er HIGH... ");
      pin3Broke = true;
    }
  }


  if (pin3Broke == true) {
    if (pin1 == pins[0]) {
      brokenPins.concat("1");
    }
    else {
      brokenPins.concat((String)pin1);
    }
    brokenPins.concat(",");
    brokenPins.concat((String)pin2);
    brokenPins.concat(",");
    brokenPins.concat((String)pin3);
    brokenPins.concat(",");
  } else if (pin1Broke == true && pin2Broke == false) {
    if (pin1 == pins[0]) {
      brokenPins.concat("1");
    }
    else {
      brokenPins.concat((String)pin1);
    }
    brokenPins.concat(",");
  } else if (pin2Broke == true && pin1Broke == false) {
    brokenPins.concat((String)pin2);
    brokenPins.concat(",");
  } else if (pin1Broke == true && pin2Broke == true) {
    if (pin1 == pins[0]) {
      brokenPins.concat("1");
    }
    else {
      brokenPins.concat((String)pin1);
    }
    brokenPins.concat(",");
    brokenPins.concat((String)pin2);
    brokenPins.concat(",");
    brokenPins.concat((String)pin3);
    brokenPins.concat(",");
  }
}

void testNand() {
  pinMode(pins[0], OUTPUT);
  pinMode(pins[1], OUTPUT);
  pinMode(pins[2], INPUT);
  pinMode(pins[3], OUTPUT);
  pinMode(pins[4], OUTPUT);
  pinMode(pins[5], INPUT);
  pinMode(pins[11], OUTPUT);
  pinMode(pins[10], OUTPUT);
  pinMode(pins[9], INPUT);
  pinMode(pins[8], OUTPUT);
  pinMode(pins[7], OUTPUT);
  pinMode(pins[6], INPUT);

  brokenPins = "";
  int in1;
  int in2;
  int out;
  Serial.println("Starter test av NAND..");

  //tester pin 1 og 2
  in1 = pins[0];
  in2 = pins[1];
  out = pins[2];
  delay(500);
  runTestNand(in1, in2, out);

  //tester pin 4 og 5
  in1 = pins[3];
  in2 = pins[4];
  out = pins[5];
  delay(500);
  runTestNand(in1, in2, out);

  //tester pin 13 og 12
  in1 = pins[11];
  in2 = pins[10];
  out = pins[9];
  delay(500);
  runTestNand(in1, in2, out);

  //tester pin 10 og 9
  in1 = pins[8];
  in2 = pins[7];
  out = pins[6];
  delay(500);
  runTestNand(in1, in2, out);

  if (brokenPins != "") {
    Serial.print("Ødelagte pinns: ");
    Serial.println(brokenPins);

  } else {
    Serial.println("Alt gikk vell");
  }

  Serial.println("Restart program for å teste på nytt");
  while (1);
}
