// the setup function runs once when you press reset or power the board
void setup() { 
  // insert initialization here}// the loop function runs over and over again, forevervoidloop(){// insert program logic here}

pinMode(D1,OUTPUT);
pinMode(D2,OUTPUT);
pinMode(D3,OUTPUT);

analogWrite(D1,1000);
analogWrite(D2,500);
analogWrite(D3,100);


}

void loop() {

int inputValue = analogRead(A0);


  analogWrite(D1, inputValue);
  analogWrite(D2, inputValue);
  analogWrite(D3, inputValue);
  

}
