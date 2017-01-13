void GenerateFood()
{
  foodX = random(0, 128);
  foodY = random(0, 64);
}

bool FoodTouched()
{
  if (snakeX[0] == foodX && snakeY[0] == foodY)
  {
    if(snakeLength < maxSnakeLength)
    {
      snakeLength++;
    }
    return true;
  }
  else
  {
    return false;
  }
}
