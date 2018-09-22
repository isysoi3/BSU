
bool isOperationSuccess;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello, i`m calculator!!!!"); 
  Serial.println();
}

void loop() {
  while(Serial.available() > 0) {
    float number1 = Serial.parseFloat();
    char operation =  Serial.read();
    float number2 = Serial.parseFloat();
    Serial.read();
    
    float result = countOperation(number1, operation, number2);
    
    if (isOperationSuccess) {
      Serial.print("Result of (");
      Serial.print(number1);
      Serial.print(operation);
      Serial.print(number2);
      Serial.print(") is ");
      Serial.println(result);
      Serial.println(); 
    } else {
      Serial.println("Error count");
    }
  }
}

float countOperation(float n1, char operation, float  n2) { 
  float result = 0;
  isOperationSuccess = true;
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
    isOperationSuccess = false;
    break;
  }
  return result;
}
