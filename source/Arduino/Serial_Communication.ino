void PcControl()
{
  if (Serial.available() > 0)
  {
    int incomingByte = Serial.read();
    char incomingChar = (char)incomingByte;

    if (incomingChar == '#')
    {
      woord = "";
      startAppend = true;
    }

    if (startAppend == true && stopAppend == false)
    {
      woord += incomingChar;
    }

    if (incomingChar == '%')
    {
      stopAppend = true;
    }

    if (startAppend == true && stopAppend == true)
    {
      startAppend = false;
      stopAppend = false;
      command = woord;
      woord = "";
    }

    if (arduinoControl == true && command == "#REMOTE_CONTROL%")
    {
      if (oudeWaardeCommand != command)
      {
        oudeWaardeCommand = command;
        Serial.println(command);
      }
      command = "";

      arduinoControl = false;
    }

    if (arduinoControl == false) //commands vanaf pc
    {
      if (command == "#MOVE_LEFT%" && moveRight != true)
      {
        moveLeft = true;
        moveRight = false;
        moveUp = false;
        moveDown = false;
        command = "#LEFT%";
        if (oudeWaardeCommand != command)
        {
          oudeWaardeCommand = command;
          Serial.println(command);
        }
      }
      else if (command == "#MOVE_RIGHT%" && moveLeft != true)
      {
        moveRight = true;
        moveLeft = false;
        moveUp = false;
        moveDown = false;
        command = "#RIGHT%";
        if (oudeWaardeCommand != command)
        {
          oudeWaardeCommand = command;
          Serial.println(command);
        }
      }
      else if (command == "#MOVE_UP%" && moveDown != true)
      {
        moveUp = true;
        moveLeft = false;
        moveRight = false;
        moveDown = false;
        command = "#UP%";
        if (oudeWaardeCommand != command)
        {
          oudeWaardeCommand = command;
          Serial.println(command);
        }
      }
      else if (command == "#MOVE_DOWN%" && moveUp != true)
      {
        moveDown = true;
        moveLeft = false;
        moveUp = false;
        moveRight = false;
        command = "#DOWN%";
        if (oudeWaardeCommand != command)
        {
          oudeWaardeCommand = command;
          Serial.println(command);
        }
      }
    }
  }
}
