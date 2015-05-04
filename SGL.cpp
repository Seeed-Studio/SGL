/*
* SGL.cpp
* A library for Seeed Graphical library
*
* Copyright (c) 2014 seeed technology inc.
* Author        :   lawliet.zou(lawliet.zou@gmail.com)
* Create Time   :   Jun 06, 2014
* Change Log    :
*
* The MIT License (MIT)
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#include "SGL.h"

SGL::SGL(uint16_t width, uint16_t height)
{
    _width = width;
    _height = height;
}

void SGL::drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    int x = x1-x0;
    int y = y1-y0;
    int dx = abs(x), sx = x0<x1 ? 1 : -1;
    int dy = -abs(y), sy = y0<y1 ? 1 : -1;
    int err = dx+dy, e2;
    for (;;){
        drawPixel(x0,y0,color);
        e2 = 2*err;
        if (e2 >= dy) {
            if (x0 == x1) break;
            err += dy; x0 += sx;
        }
        if (e2 <= dx) {
            if (y0 == y1) break;
            err += dx; y0 += sy;
        }
    }
}

void SGL::drawVerticalLine(uint16_t x, uint16_t y, uint16_t height,uint16_t color)
{
    uint16_t y1 = min(y+height,_height-1);
    for(int16_t i = y; i < y1; i++){
        drawPixel(x,i,color);
    }
}

void SGL::drawHorizontalLine(uint16_t x, uint16_t y, uint16_t width, uint16_t color)
{
    uint16_t x1 = min(x+width,_width-1);
    for(int16_t i = x; i < x1; i++){
        drawPixel(i,y,color);
    }
}

void SGL::drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
    drawHorizontalLine(x, y, width, color);
    drawHorizontalLine(x, y+height, width, color);
    drawVerticalLine(x, y, height, color);
    drawVerticalLine(x+width, y, height, color);
}

void SGL::fillRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
    for(uint16_t i = 0; i < height; i++){
        for(uint16_t j = 0; j < width; j++){
            drawPixel(x+j,y+i,color);
        }
    }
}

void SGL::drawCircle(uint16_t poX, uint16_t poY, uint16_t r, uint16_t color)
{
    int x = -r, y = 0, err = 2-2*r, e2;
    do{
        drawPixel(poX-x, poY+y,color);
        drawPixel(poX+x, poY+y,color);
        drawPixel(poX+x, poY-y,color);
        drawPixel(poX-x, poY-y,color);
        e2 = err;
        if(e2 <= y) {
            err += ++y*2+1;
            if(-x == y && e2 <= x) e2 = 0;
        }
        if(e2 > x) err += ++x*2+1;
    } while(x <= 0);
}

void SGL::fillCircle(uint16_t poX, uint16_t poY, uint16_t r, uint16_t color)
{
    int x = -r, y = 0, err = 2-2*r, e2;
    do{
        drawVerticalLine(poX-x, poY-y, 2*y, color);
        drawVerticalLine(poX+x, poY-y, 2*y, color);
        e2 = err;
        if(e2 <= y){
            err += ++y*2+1;
            if(-x == y && e2 <= x) e2 = 0;
        }
        if(e2 > x) err += ++x*2+1;
    }while(x <= 0);
}

void SGL::drawTraingle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,uint16_t x2, uint16_t y2, uint16_t color)
{
    drawLine(x0, y0, x1, y1,color);
    drawLine(x1, y1, x2, y2,color);
    drawLine(x2, y2, x0, y0,color);
}

void SGL::fillTraingle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,uint16_t x2, uint16_t y2, uint16_t color)
{
    uint16_t a, b, y, last;

    if(y0 > y1){ swap(&y0, &y1); swap(&x0, &x1); }
    if(y1 > y2){ swap(&y2, &y1); swap(&x2, &x1); }
    if(y0 > y1){ swap(&y1, &y0); swap(&x1, &x0); }

    if(y0 == y2){
        x0 = min(x0,x1)<x2?min(x0,x1):x2;
        x2 = max(x0,x1)>x2?max(x0,x1):x2;
        drawHorizontalLine(x0, y0, x2-x0, color);
        return;
    }

    int16_t dx01 = x1 - x0, dy01 = y1 - y0,
            dx02 = x2 - x0, dy02 = y2 - y0,
            dx12 = x2 - x1, dy12 = y2 - y1;
    int16_t sa   = 0,       sb   = 0;

    if(y1 == y2) last = y1;
    else last = y1-1;

    for(y=y0; y<=last; y++) {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        if(a > b) swap(&a,&b);
        drawHorizontalLine(a, y, b-a+1, color);
    }

    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for(; y<=y2; y++) {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        if(a > b) swap(&a,&b);
        drawHorizontalLine(a, y, b-a+1, color);
    }
}

void SGL::drawChar(uint8_t ascii, uint16_t x, uint16_t y, uint16_t size, uint16_t color)
{
    if((ascii<32)||(ascii>=127)){
        return;
    }

    for (int8_t i = 0; i < FONT_X; i++ ) {
        int8_t temp = pgm_read_byte(&simpleFont[ascii-0x20][i]);
        int8_t inrun = 0;
        int8_t runlen = 0;
        int8_t endrun = 0;

        for(int8_t f = 0; f < FONT_Y; f++){
            if((temp>>f)&0x01){
                if (inrun) runlen += 1;
                else {
                    inrun = 1;
                    runlen = 1;
                }
            } else if (inrun) {
                endrun = 1;
                inrun = 0;
            }

            if (f == FONT_Y - 1 && inrun) {
                endrun = 1;
                // need the +1 b/c we this code is normally
                // only triggered  when f == FONT_Y, due to the
                // edge-triggered nature of this algorithm
                f += 1;
            }
            
            if (endrun) {
                fillRectangle(x+i*size, y+(f-runlen)*size, size, runlen*size, color);
                inrun = 0;
                runlen = 0;
                endrun = 0;
            }
        }
    }
}

void SGL::drawString(char *string, uint16_t x, uint16_t y, uint16_t size, uint16_t color)
{
    while(*string){
        drawChar(*string, x, y, size, color);
        *string++;
        x += FONT_SPACE*size;
        if(x >= _width-1){
            y += FONT_Y*size;
            x = 0;
        }
    }
}

void SGL::drawBitMap(uint16_t x, uint16_t y, const uint8_t *bitmap, uint16_t width, int16_t height, uint16_t color)
{
    uint16_t i, j, byteWidth = (width + 7) / 8;
    for(j = 0; j < height; j++){
        for(i = 0; i < width; i++ ) {
            if(pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
                drawPixel(x+i, y+j, color);
            }
        }
    }
}

void SGL::fillScreen(uint16_t color)
{
    fillRectangle(0, 0, _width, _height, color);
}
