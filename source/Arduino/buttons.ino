void Buttons()
{
  if (arduinoControl == true)
  {
    if ((digitalRead(btnLeft)) == HIGH && moveRight != true && moveLeft != true)
    {
      delay(200);
      if ((digitalRead(btnLeft)) == LOW)
      {
        moveLeft = true;
        moveUp = false;
        moveDown = false;
        moveRight = false;
        Serial.println("Left");
      }
    }
    if ((digitalRead(btnUp)) == HIGH && moveDown != true && moveUp != true)
    {
      delay(200);
      if ((digitalRead(btnUp)) == LOW)
      {
        moveLeft = false;
        moveUp = true;
        moveDown = false;
        moveRight = false;
        Serial.println("Up");
      }
    }
    if ((digitalRead(btnDown)) == HIGH && moveUp != true && moveDown != true)
    {
      delay(200);
      if ((digitalRead(btnDown)) == LOW)
      {
        moveLeft = false;
        moveUp = false;
        moveDown = true;
        moveRight = false;
        Serial.println("Down");
      }
    }
    if ((digitalRead(btnRight)) == HIGH && moveLeft != true && moveRight != true)
    {
      delay(200);
      if ((digitalRead(btnRight)) == LOW)
      {
        moveLeft = false;
        moveUp = false;
        moveDown = false;
        moveRight = true;
        Serial.println("Right");
      }
    }
  }
}
