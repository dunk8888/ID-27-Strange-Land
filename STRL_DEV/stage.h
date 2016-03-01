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

///*
void drawBackground()
{
  int colMin = -(counterX / 8);
  int colMax = colMin + 16;
  int rowMin = -(counterY / 8);
  int rowMax = rowMin + 8;

  for (byte arrayX = 0; arrayX < 4; arrayX++)
  {
    if ((colMin > -1 + (16 * arrayX)) && (colMin < 16 + (16 * arrayX)))
    {
      for (byte nextCol = 0; nextCol < 2; nextCol++)
      {
        for (byte col = (1 - nextCol) * (colMin - (16 * arrayX)); col < (16 * (1 - nextCol)) + (nextCol * (colMax - (15 + (16 * arrayX)))); col++)
        {
          for (byte arrayY = 0; arrayY < 4; arrayY++)
          {
            if ((rowMin > -1 + (8 * arrayY)) && (rowMin < 8 + (8 * arrayY)))
            {
              for (byte nextRow = 0; nextRow < 2; nextRow++)
              {
                for (byte row = (1 - nextRow) * (rowMin - (8 * arrayY)); row <  (8 * (1 - nextRow)) + (nextRow * (rowMax - (7 + (8 * arrayY)))); row++)
                {
                  arduboy.drawSprite((col * 8) + (128 * (arrayX + nextCol)) + counterX, (row * 8) + (64 * (arrayY + nextRow)) + counterY, tilesheet_bitmap, 8, 8, pgm_read_byte(&tilemaps[((arrayY + nextRow) * 4) + (arrayX + nextCol)][((row * 16) + col)]), WHITE);
                }
              }
            }
          }
        }
      }
    }
  }
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
