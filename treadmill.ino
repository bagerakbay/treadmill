unsigned long time;
int  training = 2500;

int pin = A0;
int value = 0;
int Pvalue = 0;
int lap = 0;
float speedx = 0.0;

int mind = 1000;
int maxd = 0 ;
int meand = 0 ;
int len = 2;
float lerp = 1.0;
int dataSpeed = 200;
int dataTime = 0;

boolean debug = false;

void setup() {
  Serial.begin(9600);
}

void loop() {

  if (training > millis()) {
    value = analogRead(pin);

    if ( value > maxd )
      maxd = value ;

    if ( value < mind )
      mind = value ;

    meand = ( mind * 0.7 + maxd * 0.3) ;
    lap = millis();
    speedx = 0;

    if (debug) {
      Serial.print ("training :    ");
      Serial.print (training - millis());
      Serial.print ("ms   : ");
      Serial.print (1);
      Serial.print (" - ");
      Serial.print (mind);
      Serial.print (" / ");
      Serial.println (maxd);
    }
  } else {

    Pvalue = value;
    value = Pvalue * (1 - lerp) + lerp * analogRead(pin);
    int elapsed = millis() - lap ;

    if ( Pvalue <= meand && value > meand && elapsed > 450) {
      int len = 330 ; // cm
      speedx = 36.0 * len / elapsed * 100;
      lap = millis() ;
      Serial.print(1);
      if (debug)
        Serial.print("-");
      Serial.print(int(speedx));
      if (debug) {
        Serial.print("       ");
        Serial.print(mind);
        Serial.print(" - ");
        Serial.print(meand);
        Serial.print(" - ");
        Serial.print(maxd);
        Serial.print(" - ");
        Serial.print(value);
      }
      Serial.println("");
      /*
        25 km / hour
        2.500.000 cm
        0. 694 cm/ ms
      */
    }
    elapsed = millis() - lap ;

    if (elapsed > 5000 && speedx > 100 ) {
      speedx = 0 ;
      Serial.print(1);
      if (debug)
        Serial.print("-");
      Serial.print(int(speedx));

      Serial.println("");
    }

    if (elapsed > 20000)
      elapsed = 20000;


  }

  while (Serial.available() > 0) {
    int msg = Serial.read();
    Serial.println ("training has started");
    maxd = 0;
    mind = 1000;
    training = millis() + 2500;
  }

  delay(5);


}
