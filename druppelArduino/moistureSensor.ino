
 int getMoistureValue() {

  delay(2000);

  float sensor0 = analogRead(A0);

  Serial.print("Vochtigheid: ");

  Serial.println(sensor0);

  float sensor0P = 100.00 - ( ( 100.00 * sensor0 ) / 1023.00 );

  int sensorInt = (int) sensor0P;

  Serial.print("Vochtigheid procent: ");

  Serial.println(sensorInt);
  return sensorInt;

}
