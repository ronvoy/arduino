int feed = "A0";
int feedThreshold = 2;

int crank = 13;
int crankSeconds = 4;
int crankRestSeconds = 6;
int attempt = 3;

int siren = 12;
int sirenSeconds = 60;

int greenLamp = 11;
int redLamp = 10;

void setup()
{
  
  Serial.begin(9600);

  pinMode(feed, INPUT);
  pinMode(crank, OUTPUT);
  pinMode(siren, OUTPUT);
  pinMode(greenLamp, OUTPUT);
  pinMode(redLamp, OUTPUT);
  
  if(checkFeed(feed) < feedThreshold)
  {generatorOff(greenLamp, redLamp);}
  else
  {generatorOn(greenLamp, redLamp);}

  for(int i = 1; i<= attempt; i++)
  {
    if(checkFeed(feed) < feedThreshold)
    {startMotor(crank, crankSeconds, crankRestSeconds);}
  }

  if(checkFeed(feed) < feedThreshold)
  {startSiren(siren, sirenSeconds);}
  else
  {generatorOn(greenLamp, redLamp);}

}

void loop()
{
  if(checkFeed(feed) < feedThreshold)
  {generatorOff(greenLamp, redLamp);}
  else
  {generatorOn(greenLamp, redLamp);}
}

void generatorOff(int greenLamp, int redLamp)
{
  off(greenLamp);
  on(redLamp);
}

void generatorOn(int greenLamp, int redLamp)
{
  on(greenLamp);
  off(redLamp);
}

void on(int lamp)
{digitalWrite(lamp, HIGH);}

void off(int lamp)
{digitalWrite(lamp, LOW);}

void startMotor(int crank, int crankSeconds, int crankRestSeconds)
{
  digitalWrite(crank, HIGH);
  delay(crankSeconds * 1000);
  digitalWrite(crank, LOW);
  delay(crankRestSeconds * 1000);
}

void startSiren(int siren, int sirenSeconds)
{
  digitalWrite(siren, HIGH);
  delay(sirenSeconds * 1000);
  digitalWrite(siren, LOW);
}

float checkFeed(int feed)
{
  int sensorValue = analogRead(feed);
  float voltage = sensorValue * (5.0 / 1023.0);
  return voltage;
}