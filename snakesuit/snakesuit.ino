#include "FastLED.h"

#define NUM_LEDS 194
#define DATA_PIN 5

CRGB leds[NUM_LEDS];

#define rows 9
#define cols 30
#define MAX_SNAKE_LENGTH 20

int posX, posY, snakeLength;
int snake[MAX_SNAKE_LENGTH];

int lightarray[rows][cols] = {
  {111 ,110 ,109 ,108 ,107 ,106 ,105 ,104 ,103 ,102 ,101 ,100 ,99  ,98  ,97  ,     96  ,95  ,94  ,93  ,92  ,91  ,90  ,89  ,88  ,87  ,86  ,85  ,84  ,83  ,82  },
  {112 ,113 ,114 ,115 ,116 ,117 ,118 ,119 ,120 ,121 ,122 ,123 ,124 ,125 ,126 ,     67  ,68  ,69  ,70  ,71  ,72  ,73  ,74  ,75  ,76  ,77  ,78  ,79  ,80  ,81  },
  {-1  ,139 ,138 ,137 ,136 ,135 ,134 ,133 ,132 ,131 ,130 ,129 ,128 ,127 ,-1  ,     -1  ,66  ,65  ,64  ,63  ,62  ,61  ,60  ,59  ,58  ,57  ,56  ,55  ,54  ,-1  },
  {-1  ,-1  ,-1  ,140 ,141 ,142 ,143 ,144 ,145 ,146 ,147 ,148 ,-1  ,-1  ,-1  ,     -1  ,-1  ,-1  ,45  ,46  ,47  ,48  ,49  ,50  ,51  ,52  ,53  ,-1  ,-1  ,-1  },
  {-1  ,-1  ,-1  ,157 ,156 ,155 ,154 ,153 ,152 ,151 ,150 ,149 ,-1  ,-1  ,-1  ,     -1  ,-1  ,-1  ,44  ,43  ,42  ,41  ,40  ,39  ,38  ,37  ,36  ,-1  ,-1  ,-1  },
  {-1  ,-1  ,-1  ,158 ,159 ,160 ,161 ,162 ,163 ,164 ,165 ,166 ,-1  ,-1  ,-1  ,     -1  ,-1  ,-1  ,27  ,28  ,29  ,30  ,31  ,32  ,33  ,34  ,35  ,-1  ,-1  ,-1  },
  {-1  ,-1  ,-1  ,175 ,174 ,173 ,172 ,171 ,170 ,169 ,168 ,167 ,-1  ,-1  ,-1  ,     -1  ,-1  ,-1  ,26  ,25  ,24  ,23  ,22  ,21  ,20  ,19  ,18  ,-1  ,-1  ,-1  },
  {-1  ,-1  ,-1  ,176 ,177 ,178 ,179 ,180 ,181 ,182 ,183 ,184 ,-1  ,-1  ,-1  ,     -1  ,-1  ,-1  ,9   ,10  ,11  ,12  ,13  ,14  ,15  ,16  ,17  ,-1  ,-1  ,-1  },
  {-1  ,-1  ,-1  ,193 ,192 ,191 ,190 ,189 ,188 ,187 ,186 ,185 ,-1  ,-1  ,-1  ,     -1  ,-1  ,-1  ,8   ,7   ,6   ,5   ,4   ,3   ,2   ,1   ,0   ,-1  ,-1  ,-1  }
};

void setup() {
  // put your setup code here, to run once:
  LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
  LEDS.setBrightness(50);
  setBlack();
  FastLED.show();
  Serial.begin(9600);
//  posX = random8(rows);
//  posY = random8(cols);
  posX = 6;
  posY = 5;


  //initalize snake
  initSnake();
  addToSnake(lightarray[posY][posX]);

  setNextPosition();
  setNextPosition();
  setNextPosition();
  setNextPosition();
  setNextPosition();
  setNextPosition();
//  setNextPosition();
  //  setNextPosition();

  // really should be in loop
  paintSnake();
}

void loop() {
//   put your main code here, to run repeatedly:
//  paintSnake();
}

//sets all lights to black/off
void setBlack() {
   for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
   }
}

void initSnake() {
    for (int i=0; i<MAX_SNAKE_LENGTH; i++) {
        snake[i] = -2;
    }
    Serial.print("initialized snake\n");
    printSnake();
}

void printSnake() {
  for (int i=0; i<MAX_SNAKE_LENGTH; i++) {
    Serial.print(snake[i]);
    Serial.print(",");
  }
  Serial.print("\n");
}

void addToSnake(int light){
  Serial.print("adding to snake, current length: ");
  Serial.print(snakeLength);
  Serial.print("\n");
  Serial.print("preivious snake:\n");
  printSnake();
  snake[snakeLength] = light;
  snakeLength++;
  Serial.print("new snake:\n");
  printSnake();
}

void paintSnake(){
  for(int i = 0; i < MAX_SNAKE_LENGTH; i++) {
    leds[snake[i]] = CRGB::Blue;
  }
  FastLED.show();
}

void setNextPosition() {
  //dir = 0:up 1:right 2:down 3:left
  int dir = random8(4);
  Serial.print("New direction: ");
  Serial.print(dir);
  Serial.print("\n");
  int newY;
  int newX;

  if(dir == 0) { //up
    if(posY > 1) {
      newX = posX;
      newY = posY-1;
    } else { setNextPosition(); }
  } else if(dir == 1) { //right
    bool valid = false;
    newX = posX;
    newY = posY;
    while(valid == false){
      if(posX >= cols){ //maybe try cols-1 when everything breaks
        posX = 0;
       } else {
        newX++;
       }
      if(lightarray[newY][newX] != -1){
        valid = true;
      }
    }
  } else if(dir == 2) { //down
    if(posY < rows) {
      newX = posX;
      newY = posY+1;
    } else { setNextPosition(); }
  } else if(dir == 3) { //left
    bool valid = false;
    newY = posY;
    newX = posX;
    while(valid == false){
      if(newX == 0){
        newX = cols;
      } else {
        newX--;
      }
      if(lightarray[newY][newX] != -1){
        valid = true;
      }
    }
  }
  posX = newX;
  posY = newY;
  addToSnake(lightarray[posY][posX]);
}

