
void setup() {
  Serial.begin(9600);
  Serial.println("I`m calculator!!!!"); 
  Serial.println();
}

void loop() {
  while(Serial.available() > 0) {
    long result = countLine(Serial.parseInt(), Serial.read(), Serial.parseInt(););
    Serial.println("------Result of ------");
    Serial.println(result);
    Serial.println(); 
  }
}

long countLine(long n1, char operation, long n2) { 
  long result = 0;
  switch (operation) {
    case '+' :
    result = n1 + n2; 
    break;
    case '-' :
    result = n1 - n2; 
    break;
    case '*' : 
    result = n1 * n2;
    break; 
    case '/' : 
    result = n1 / n2;
    break;
    default :
  }
  return result;
}