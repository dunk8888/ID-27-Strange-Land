#ifndef COLLISION_H
#define COLLISION_H

#define CHECK_CURRENT 0
#define CHECK_DOWN    1
#define CHECK_UP      2
#define CHECK_LEFT    3
#define CHECK_RIGHT   4

#define POINT1    1
#define POINT2    2
#define POINT3    3
#define POINT4    4

#include "Arglib.h"

byte checkCurrentTile(byte positionX, byte positionY, byte checkPoint, byte upDownLeftRight)
{
  byte tileMap;
  byte x;
  byte y;
  switch (checkPoint)
  {
    case POINT1:
    {
      switch (upDownLeftRight)
      {
        case CHECK_CURRENT:
        {
          tileMap = ((positionX) / 128) + (positionY / 64) * 4;
          x = (positionX) / 8;
          y = (positionY) / 8;
          break;
        }
        case CHECK_UP:
        {
          tileMap = ((positionX ) / 128) + ((positionY-1) / 64) * 4;
          x = (positionX) / 8;
          y = (positionY-1) / 8;
          break;
        }
        case CHECK_LEFT:
        {
          tileMap = ((positionX-1) / 128) + ((positionY) / 64) * 4;
          x = (positionX-1) / 8;
          y = (positionY) / 8;
          break;
        }
      }
      break;
    }
    case POINT2:
    {
      switch (upDownLeftRight)
      {
        case CHECK_CURRENT:
        {
          tileMap = ((positionX + 9 ) / 128) + ((positionY) / 64) * 4;
          x = (positionX + 9) / 8;
          y = (positionY) / 8;
          break;
        }
        case CHECK_UP:
        {
          tileMap = ((positionX + 9 ) / 128) + ((positionY-1) / 64) * 4;
          x = (positionX + 9) / 8;
          y = (positionY-1) / 8;
          break;
        }
        case CHECK_RIGHT:
        {
          tileMap = ((positionX + 10 ) / 128) + ((positionY) / 64) * 4;
          x = (positionX + 10) / 8;
          y = (positionY) / 8;
          break;
        }
      }
      break;
    }
    case POINT3:
    {
      switch (upDownLeftRight)
      {
        case CHECK_CURRENT:
        {
          tileMap = ((positionX) / 128) + ((positionY + 11) / 64) * 4;
          x = (positionX) / 8;
          y = (positionY + 11) / 8;
          break;
        }
        case CHECK_DOWN:
        {
          tileMap = ((positionX) / 128) + ((positionY + 12) / 64) * 4;
          x = (positionX) / 8;
          y = (positionY + 12) / 8;
          break;
        }
        case CHECK_LEFT:
        {
          tileMap = ((positionX-1) / 128) + ((positionY + 11) / 64) * 4;
          x = (positionX-1) / 8;
          y = (positionY + 11) / 8;
          break;
        }
      }
      break;
    }
    case POINT4:
    {
      switch (upDownLeftRight)
      {
        case CHECK_CURRENT:
        {
          tileMap = ((positionX + 9) / 128) + ((positionY + 11) / 64) * 4;
          x = (positionX + 9 ) / 8;
          y = (positionY + 11 ) / 8;
          break;
        }
        case CHECK_DOWN:
        {
          tileMap = ((positionX + 9) / 128) + ((positionY + 12) / 64) * 4;
          x = (positionX + 9 ) / 8;
          y = (positionY + 12 ) / 8;
          break;
        }
        case CHECK_RIGHT:
        {
          tileMap = ((positionX + 10) / 128) + ((positionY + 11) / 64) * 4;
          x = (positionX + 10 ) / 8;
          y = (positionY + 11 ) / 8;
          break;
        }
      }
      break;
    }
  }
  x = x % 16;
  y = y % 8;
  byte usedSprite = x + (y * 16);
  byte spriteNumber = pgm_read_byte(&tilemaps[tileMap][usedSprite]);
  return spriteNumber;
}

#endif
