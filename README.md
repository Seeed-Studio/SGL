##SGL
SGL is short for **Seeed Graphics Library**. It is the core graphics for displays which provide a common set of graphics primitives(points, lines, circles, etc.).

### Interface Introduction
**we offer some userful functions as follow:**
```c
//draw a line between two points
virtual void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
//draw a vertical line
virtual void drawVerticalLine(uint16_t x, uint16_t y, uint16_t height,uint16_t color);
//draw a horizontal line
virtual void drawHorizontalLine(uint16_t x, uint16_t y, uint16_t width, uint16_t color);
//draw a rectangle
virtual void drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
//fill a rectangle area
virtual void fillRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
//draw a circle
virtual void drawCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);
//fill a circle
virtual void fillCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);
//draw a traingle
virtual void drawTraingle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
//fill a traingle area
virtual void fillTraingle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);	
//draw char like 'a','b','c'
virtual void drawChar(uint8_t ascii, uint16_t x, uint16_t y, uint16_t size, uint16_t color);
//draw a string like "hello" 
virtual void drawString(char* string, uint16_t x, uint16_t y, uint16_t size, uint16_t color);
//draw bit map
virtual void drawBitMap(uint16_t x, uint16_t y, const uint8_t *bitmap, uint16_t width, int16_t height, uint16_t color);
//fill the whole screen with one color
virtual void fillScreen(uint16_t color);
```

----
This software is written by lawliet zou ([wei.zou@seeedstudio.com](wei.zou@seeedstudio.com)) for seeed studio<br>
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.<br>

Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed Studio is an open hardware facilitation company based in Shenzhen, China. <br>
Benefiting from local manufacture power and convenient global logistic system, <br>
we integrate resources to serve new era of innovation. Seeed also works with <br>
global distributors and partners to push open hardware movement.<br>



[![Analytics](https://ga-beacon.appspot.com/UA-46589105-3/SGL)](https://github.com/igrigorik/ga-beacon)

