int side1 = 2;
int side2 = 3;
int side3 = 4;

int trig1 = 8;
int echo1 = 9;
int trig2 = 10;
int echo2 = 11;
int trig3 = 12;
int echo3 = 13;

long duration = 0;
int distance = 0;
long newDist[5] = {0};
//long oldDist[5] = {50};

int tripDist = 60;
long waitTime = 5000;

const int numSamples = 5;
long distances[numSamples]; 

void setup() {
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);

  pinMode(side1, OUTPUT);
  pinMode(side2, OUTPUT);
  pinMode(side3, OUTPUT);

  digitalWrite(side1,HIGH);
  digitalWrite(side2,HIGH);
  digitalWrite(side3,HIGH);

  Serial.begin(9600);
}

void loop() {
  dist(trig1,echo1,side1,1);
  dist(trig2,echo2,side2,2);
  dist(trig3,echo3,side3,3);

}


void dist(int trigPin,int echoPin, int side, int val)
{  
  long sumSampleDistance = 0;
  for (int i = 0; i < numSamples; i++)
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distances[i] = duration * 0.034 / 2;
    delay(100);

    Serial.print(i);
    Serial.print(" Distance ");
    Serial.print(val);
    Serial.print(": ");
    Serial.print(distances[i]);
    Serial.println(" cm");
    
    sumSampleDistance += distances[i];
  }
  long mode = calculateMode(distances, numSamples);
  Serial.print("Mode Distance: ");
  Serial.print(mode);
  Serial.println(" cm");
  
  newDist[val] = mode;
//  if((oldDist[val]-newDist[val])>tripDist)
  if(newDist[val]<tripDist)
  {
    Serial.println("Go");
    digitalWrite(side,LOW);
    delay(waitTime);
    dist(trigPin,echoPin,side,val);
  }
  else
  {return;}
  Serial.println("Stop");
  digitalWrite(side,HIGH);
//  oldDist[val] = newDist[val];
}

long calculateMode(long data[], int size)
{
  long modeValue = 0;
  int count[400] = {0};
  int maxCount = 0;
  for (int i = 0; i < size; i++)
  {
    ++count[data[i]];
    Serial.print("count for ");
    Serial.print(data[i]);
    Serial.print(" is ");
    Serial.println(count[data[i]]);
    if (count[data[i]] > maxCount)
    {
      maxCount = count[data[i]];
      modeValue = data[i];
    }
  }
  return modeValue;
}
