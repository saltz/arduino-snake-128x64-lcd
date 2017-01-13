void Control()
{
  for(int i = snakeLength; i  > 0; i--)
  {
    snakeX[i] = snakeX[i-1];
    snakeY[i] = snakeY[i-1];
  }
  if (moveLeft == true)
  {
    snakeX[0] =  snakeX[0] - 1;
  }
  else if (moveUp == true)
  {
    snakeY[0] =  snakeY[0] - 1;
  }
  else if (moveDown == true)
  {
    snakeY[0] =  snakeY[0] + 1;
  }
  else if (moveRight == true)
  {
    snakeX[0] =  snakeX[0] + 1;;
  }
}

bool IsSnake(int x, int y)
{
  for (int i = 0; i < snakeLength - 1; i++)
  {
    if ((x == snakeX[i]) && (y == snakeY[i]))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

void TouchedItSelf()
{
  for (int i = 1; i < snakeLength; i++)
  {
    if ((snakeX[0] == snakeX[i]) && (snakeY[0] == snakeY[i]))
    {
      Dead();
    }
  }
}
