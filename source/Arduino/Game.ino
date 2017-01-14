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
  Serial.begin(115200);
  Serial.println("Snake");
  pinMode(btnLeft, INPUT);
  pinMode(btnUp, INPUT);
  pinMode(btnDown, INPUT);
  pinMode(btnRight, INPUT);

  //random maken
  randomSeed(analogRead(0));

//default positie van de snake
  snakeX[0] = 20;
  snakeY[0] = 20;

//genereren van het eerste stukje eten
  GenerateFood();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (OnScreen(snakeX[0], snakeY[0]))
  {
    TouchedItSelf();
    if (FoodTouched()) //als er eten is aangeraakt
    {
      GenerateFood();
      PcControl();
      Buttons();
      Control();
    }
    else //geen eten aangeraakt
    {
      PcControl();
      Buttons();
      Control();
    }

    //tekenen op het lcd
    u8g.firstPage();
    do {
      draw(); //teken wat in de draw functie staat
    } while ( u8g.nextPage() );
    delay(70);
  }
  else
  {
    Dead();
  }
}

void draw(void) //tekenen van de snake op het scherm
{
  drawSnake();
  drawFood();
}

void drawSnake()
{
  for (int i = 0; i < snakeLength; i++)
  {
    u8g.drawBox(snakeX[i], snakeY[i], 1, 1);
  }
}

void drawFood()
{
  if (OnScreen(foodX, foodY))
  {
    u8g.drawBox(foodX, foodY, 1, 1);
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

void Dead()
{
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr( 20, 30, "You Died!");
    u8g.drawStr( 20, 50, "Game Over");
  } while ( u8g.nextPage() );

  // rebuild the picture after some delay
  delay(5000);
  snakeX[0] = 20;
  snakeY[0] = 20;
  snakeLength = 1;
  moveLeft = false;
  moveRight = false;
  moveUp = false;
  moveDown = false;

  GenerateFood();
}




