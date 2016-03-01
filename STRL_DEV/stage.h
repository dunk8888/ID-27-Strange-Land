#ifndef STAGE_H
#define STAGE_H

#include "Arglib.h"
#include "bitmaps.h"
#include "blob.h"


//#define NUMBER_OF_ROWS           8
//#define NUMBER_OF_COLS           16
//#define TILEMAP_ROWS             4
//#define TILEMAP_COLS             4
//#define TILESIZE                 8

extern Arduboy arduboy;
extern SimpleButtons buttons;

int counterX = 0;
int counterY = 0;

void newDraw(unsigned posX, unsigned posY)
{
  unsigned int intX = posX >> 3, subX = posX & 0x07;
  unsigned int intY = posY >> 3, subY = posY & 0x07;
  for(byte x = 0; x < (subX ? 17 : 16); x++)
  {
    for(byte y = 0; y < (subY ?  9 :  8); y++)
    {
      arduboy.drawSprite(((int)x << 3) - subX, ((int)y << 3) - subY, tilesheet_bitmap, 8, 8, pgm_read_byte(&tilemaps[(((intX + x) >> 3) + ((intY + y) & 0xF8)) >> 1][((intX + x) & 0x0F) + (((intY + y) & 0x07) << 4)]),WHITE);
    }
  }
}

void drawBackground() {
  newDraw(-counterX, -counterY);
}

void checkFloor() {
  //check Down
  playerBlob.faling = false;
  //if (check_tilemap(playerBlob.posMapX, playerBlob.posMapY + 4, CHECK_DOWN) < 13 && (check_tilemap(playerBlob.posMapX + 11, playerBlob.posMapY + 4, CHECK_DOWN)) < 13)
  {
    if (playerBlob.y < 24)
    {
      playerBlob.posMapY++;
      playerBlob.y++;
    }
    if (playerBlob.y > 23)
    {
      if (playerBlob.posMapY < 216)
      {

        playerBlob.posMapY++;
        counterY--;

      }
      if (playerBlob.posMapY > 215)
      {
        playerBlob.posMapY++;
        playerBlob.y++;
      }
    }
    playerBlob.faling = true;
  }
}


void checkInputs()
{
  if (buttons.pressed(LEFT_BUTTON))
  {
    if (playerBlob.x > 47)
    {
      playerBlob.posMapX--;
      playerBlob.x--;
    }
    if (playerBlob.x < 48)
    {
      if (playerBlob.posMapX > 47)
      {
        playerBlob.posMapX--;
        counterX++;
      }
      if (playerBlob.posMapX < 48)
      {
        playerBlob.posMapX--;
        playerBlob.x--;
      }
    }
  }

  if (buttons.pressed(RIGHT_BUTTON))
  {
    if (playerBlob.x < 68)  //(128 - 28) - 12
    {
      playerBlob.posMapX++;
      playerBlob.x++;
    }
    if (playerBlob.x > 67)
    {
      if (playerBlob.posMapX < 452)  //(512 - 48) - 12
      {
        playerBlob.posMapX++;
        counterX--;
      }
      if (playerBlob.posMapX > 451)
      {
        playerBlob.posMapX++;
        playerBlob.x++;
      }
    }
  }

  if (buttons.pressed(UP_BUTTON))
  {
    if (playerBlob.y > 15)
    {
      playerBlob.posMapY--;
      playerBlob.y--;
    }
    if (playerBlob.y < 16)
    {
      if (playerBlob.posMapY > 15)
      {
        playerBlob.posMapY--;
        counterY++;
      }
      if (playerBlob.posMapY < 16)
      {
        playerBlob.posMapY--;
        playerBlob.y--;
      }
    }
  }


  if (buttons.pressed(DOWN_BUTTON))
  {
    if (playerBlob.y < 36)
    {
      playerBlob.posMapY++;
      playerBlob.y++;
    }
    if (playerBlob.y > 35)
    {
      if (playerBlob.posMapY < 228) //(256 - 16) - 12 (blob height)
      {
        playerBlob.posMapY++;
        counterY--;
      }
      if (playerBlob.posMapY > 227)
      {
        playerBlob.posMapY++;
        playerBlob.y++;
      }
    }
  }

  if (buttons.justPressed(B_BUTTON))
  {
    if (!playerBlob.faling)playerBlob.jumping = true;
  }
}


#endif
