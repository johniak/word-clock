#include "GifPlayer.h"
#define BRIGHT_SHIFT 0

GifPlayer *GifPlayer::instance = nullptr;

GifPlayer::GifPlayer(ClockDisplayHAL *clockDisplayHAL)
    : clockDisplayHAL(clockDisplayHAL)
{
    gif.begin(GIF_PALETTE_RGB888);
    instance = this;
}

void GifPlayer::GIFDraw(GIFDRAW *pDraw)
{
    if (instance && instance->clockDisplayHAL)
    {
        ClockDisplayHAL *hal = instance->clockDisplayHAL;

        uint8_t r, g, b, *s, *p, *pPal = (uint8_t *)pDraw->pPalette;
        int x, y = pDraw->iY + pDraw->y;

        s = pDraw->pPixels;
        if (pDraw->ucDisposalMethod == 2)
        {
            p = &pPal[pDraw->ucBackground * 3];
            r = p[0] >> BRIGHT_SHIFT;
            g = p[1] >> BRIGHT_SHIFT;
            b = p[2] >> BRIGHT_SHIFT;
            for (x = 0; x < pDraw->iWidth; x++)
            {
                if (s[x] == pDraw->ucTransparent)
                {
                    hal->setPixel(x, y, hal->pixels.Color(r, g, b));
                }
            }
            pDraw->ucHasTransparency = 0;
        }

        if (pDraw->ucHasTransparency)
        {
            const uint8_t ucTransparent = pDraw->ucTransparent;
            for (x = 0; x < pDraw->iWidth; x++)
            {
                if (s[x] != ucTransparent)
                {
                    p = &pPal[s[x] * 3];
                    hal->setPixel(x, y, hal->pixels.Color(p[0] >> BRIGHT_SHIFT, p[1] >> BRIGHT_SHIFT, p[2] >> BRIGHT_SHIFT));
                }
            }
        }
        else
        {
            for (x = 0; x < pDraw->iWidth; x++)
            {
                p = &pPal[s[x] * 3];
                hal->setPixel(x, y, hal->pixels.Color(p[0] >> BRIGHT_SHIFT, p[1] >> BRIGHT_SHIFT, p[2] >> BRIGHT_SHIFT));
            }
        }

        if (pDraw->y == pDraw->iHeight - 1)
        {
            hal->show();
        }
    }
}

bool GifPlayer::loadGIF(uint8_t *gifBuffer, size_t gifSize)
{
    int rc = gif.open(gifBuffer, gifSize, GIFDraw);
    return (rc != 0);
}

void GifPlayer::playGIF(unsigned long durationMs)
{
    unsigned long startTime = millis();

    while (millis() - startTime < durationMs)
    {
        if (!gif.playFrame(true, nullptr))
        {
            gif.reset();
        }
    }

    gif.close();
}
