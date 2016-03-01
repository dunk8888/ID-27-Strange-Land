/*
 GAME-NAME: http://www.team-arg.org/STRL-manual.html

 Arduboy version 0.1:  http://www.team-arg.org/STRL-downloads.html

 MADE by TEAM a.r.g. : http://www.team-arg.org/About.html

 2015 - creator name (name of helpers)

 Game License: MIT : https://opensource.org/licenses/MIT
  
 */

//determine the game
#define GAME_ID 00

#include <SPI.h>
#include <EEPROM.h>
#include "Arglib.h"
#include "menu_bitmaps.h"
#include "bitmaps.h"
#include "stage.h"
#include "blob.h"
#include "collision.h"

//define menu states (on main menu)
#define STATE_MENU_MAIN          0
#define STATE_MENU_HELP          1
#define STATE_MENU_INFO          3
#define STATE_MENU_SOUNDFX       4

//define menu choices (on main menu)
#define CHOOSE_HELP              1
#define CHOOSE_PLAY              2
#define CHOOSE_INFO              3
#define CHOOSE_CONF              4

//define game states (on main menu)
#define STATE_GAME_INIT          2
#define STATE_GAME_PLAYING       8
#define STATE_GAME_PAUSE         9
#define STATE_GAME_OVER          10

Arduboy arduboy;
SimpleButtons buttons (arduboy);

unsigned char gameState = STATE_MENU_MAIN;
boolean soundYesNo;
int menuSelection;

void setup()
{
  arduboy.start();
  arduboy.setFrameRate(60);
  arduboy.drawSprite(15, 16, TEAMarg, 96, 32,0, WHITE);
  arduboy.display();
  //delay(3000);
  gameState = STATE_MENU_MAIN;
  if (EEPROM.read(EEPROM_AUDIO_ON_OFF)) soundYesNo = true;
  menuSelection = CHOOSE_PLAY;
  Serial.begin(9600);
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  buttons.poll();
  if (soundYesNo == true) arduboy.audio.on();
  else arduboy.audio.off();
  arduboy.clearDisplay();
  switch (gameState)
  {
    case STATE_MENU_MAIN:
      // show the splash art
      arduboy.drawSprite(0, 0, splashScreen_bitmap, 128, 56, 0, WHITE);
      arduboy.drawSprite(19, 56, mainMenu_bitmaps, 90, 8,(menuSelection - 1), WHITE);
      if (buttons.justPressed(RIGHT_BUTTON) && (menuSelection < 4)) menuSelection++;
      if (buttons.justPressed(LEFT_BUTTON) && (menuSelection > 1)) menuSelection--;
      if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = menuSelection;
      break;
    case STATE_MENU_HELP: // QR code
      arduboy.drawSprite(32, 0, qrCode_bitmap, 64, 64,0,1);
      if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
      break;
    case STATE_MENU_INFO: // infoscreen
      arduboy.drawSprite(16, 20, info_bitmap, 96, 24,0, 1);
      if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
      break;
    case STATE_MENU_SOUNDFX: // soundconfig screen
      arduboy.drawSprite(0, 0, splashScreen_bitmap, 128, 56, 0, WHITE);
      arduboy.drawSprite(22, 56, soundYesNo_bitmaps, 84, 8,soundYesNo, WHITE);
      if (buttons.justPressed(RIGHT_BUTTON)) soundYesNo = true;
      if (buttons.justPressed(LEFT_BUTTON)) soundYesNo = false;
      if (buttons.justPressed(A_BUTTON | B_BUTTON))
      {
        arduboy.audio.save_on_off();
        gameState = STATE_MENU_MAIN;
      }
      if (soundYesNo == true) arduboy.audio.on();
      else arduboy.audio.off();
      break;
    case STATE_GAME_INIT:
      playerBlob.reset();
      gameState = STATE_GAME_PLAYING;
      break;
    case STATE_GAME_PLAYING:
      checkInputs();
      updateStage();
      if (checkGameOver())gameState = STATE_GAME_OVER;
      break;
    case STATE_GAME_OVER:
      //arduboy.drawSprite(0, 0, gameOver_bitmap, 128, 64, 0, WHITE);
      if (buttons.justPressed(A_BUTTON | B_BUTTON))
      {
        arduboy.clearDisplay();
        gameState = STATE_MENU_MAIN;
      }
      break;
    case STATE_GAME_PAUSE:
      if (buttons.justPressed(B_BUTTON))
      {
        //afterPause();
        gameState = STATE_GAME_PLAYING;
      }
      break;
  }
  arduboy.display();
}



void updateStage()
{
  drawBackground();
  //if (!playerBlob.jumping)checkFloor();
  drawPlayer();
  Serial.print(checkCurrentTile(playerBlob.posMapX,playerBlob.posMapY,POINT1, CHECK_CURRENT));
  Serial.print(":");
  Serial.print(checkCurrentTile(playerBlob.posMapX,playerBlob.posMapY,POINT2, CHECK_CURRENT));
  Serial.println("");
  Serial.print(checkCurrentTile(playerBlob.posMapX,playerBlob.posMapY,POINT3, CHECK_CURRENT));
  Serial.print(":");
  Serial.print(checkCurrentTile(playerBlob.posMapX,playerBlob.posMapY,POINT4, CHECK_CURRENT));
  Serial.println("");
  Serial.println("");
}



boolean checkGameOver()
{
  return false;
};

