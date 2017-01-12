#include <U8glib.h>

U8GLIB_ST7920_128X64 u8g(13, 11, 10, U8G_PIN_NONE); // SPI Com: SCK = en = 13, MOSI = rw = 11, CS = di = 0

//pin vars
const int btnLeft = 2;
const int btnUp = 3;
const int btnDown = 4;
const int btnRight = 5;

//console strings & command
String command;
String oudeWaardeCommand;
String woord;

bool startAppend = false;
bool stopAppend = false;
bool arduinoControl = true;

char oudechar;

//global button bools
bool moveLeft = false;
bool moveRight = false;
bool moveUp = false;
bool moveDown = false;

//playing field
int playfieldX = 128;
int playfieldY = 64;

//snake position & length
const int maxSnakeLength = 200;
int snakeLength = 1;

int snakeX[maxSnakeLength];
int snakeY[maxSnakeLength];

//food

int foodX;
int foodY;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Snake");
  pinMode(btnLeft, INPUT);
  pinMode(btnUp, INPUT);
  pinMode(btnDown, INPUT);
  pinMode(btnRight, INPUT);

  snakeX[0] = 20;
  snakeY[0] = 20;


  GenerateFood();
}

void loop() {
  // put your main code here, to run repeatedly:
  PcControl();
  Buttons();
  Control();
  
  //tekenen op het lcd
  u8g.firstPage();
  do {
    draw(); //teken wat in de draw functie staat
  } while ( u8g.nextPage() );
  delay(70);
}

void draw(void)
{
  drawSnake();
  drawFood();

}

void drawSnake()
{
  for (int i = 0; i < snakeLength; i++)
  {
    u8g.drawBox(snakeX[i], snakeY[i], 4, 4);
  }
}

void drawFood()
{
  if (OnScreen(foodX, foodY))
  {
    u8g.drawBox(foodX, foodY, 2, 2);
  }
}


void Control()
{
  if (moveLeft == true)
  {
    snakeX[0] = snakeX[0] - 1;
  }
  else if (moveUp == true)
  {
    snakeY[0] = snakeY[0] - 1;
  }
  else if (moveDown == true)
  {
    snakeY[0] = snakeY[0] + 1;
  }
  else if (moveRight == true)
  {
    snakeX[0] = snakeX[0] + 1;
  }
}

void GenerateFood()
{
  int x;
  int y;
  x = random(0, 128);
  y = random(0, 64);
  while (IsSnake(x, y))
  {
    x = random(0, 128);
    y = random(0, 64);
  }
  foodX = x;
  foodY = y;
}

bool IsSnake(int x, int y)
{
  for (int i = 0; i < snakeLength - 1; i++) {
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

bool OnScreen(int x, int y) //kijkt of de snake nog in het spelersveld(scherm bevind)
{
  if (x >= 0 && x < 128 && y >= 0 && y < 64)
  {
    return true;
  }
  else
  {
    return false;
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

void Dead()
{
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr( 20, 50, "You Died, Game Over");
  } while ( u8g.nextPage() );

  // rebuild the picture after some delay
  delay(70);
  loop();
}




