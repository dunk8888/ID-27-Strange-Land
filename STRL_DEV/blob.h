#ifndef BLOB_H
#define BLOB_H

#include "Arglib.h"
#include "bitmaps.h"


extern Arduboy arduboy;

struct Blob
{
  public:
    int x, y;
    byte width = 12;
    byte height = 12;
    byte facing;
    byte frame;
    boolean faling;
    boolean jumping;
    boolean climbing;
    byte timerJumping;
    int posMapX;
    int posMapY;

    void reset()
    {
      x = 48;
      y = 0;
      timerJumping = 6;
      jumping = false;
      climbing = false;
      faling = false;
      posMapX = x;
      posMapY = y;
      facing = 0;
      frame = 0;
    }

};

Blob playerBlob;


void drawPlayer()
{
  arduboy.drawSprite(playerBlob.x, playerBlob.y, blobMask_bitmaps, 10, 16, 0, BLACK);
  arduboy.drawSprite(playerBlob.x, playerBlob.y, blob_bitmaps, 10, 16, 0, WHITE);
}





#endif
