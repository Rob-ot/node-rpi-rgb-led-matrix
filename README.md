
# node rpi rgb led matrix

## Installation

```
npm install rpi-rgb-led-matrix
```

## Usage

```javascript
var board = require('rpi-rgb-led-matrix')
```

#### start(rows=32, columns=32, chain=1, parallel=1, clearOnClose=true)

Start updating the board.

- rows 		- Vertical height of the board
- columns 	- Horizontal width of board

- chain - Number of boards chained together

- parallel - Number of chains running parralel

- clearOnClose - Automatically clear the display when node is shutting down

```javascript
board.start(16, 32,  1, 1, true)
```

#### stop()

Stop updating the board. Call `clear()` first to avoid random LEDs stuck on.

```javascript
board.stop()
```

#### setPixel(x, y, r, g, b)

Set the color of a pixel. Black = off.

- x y - Coordinates of the pixel, from the top left.

- r g b - Red, Green, and Blue, numbers between or exactly 0 and 255

```javascript
board.setPixel(2, 4, 255, 255, 0)
```

#### fill(r, g, b)

Fill the entire board with a solid color.

- r g b - Red, Green, and Blue, numbers between or exactly 0 and 255

```javascript
board.fill(255, 255, 0)
```


#### drawCanvas(ctx, width, height)

Draw a canvas 2d context to the board.

- ctx - Canvas context to draw.

- width height - size of the canvas

```javascript
board.drawCanvas(ctx, 32, 16)
```


#### clear()

Set all pixels to black.

```javascript
board.clear()
```



## License

GPLv2 and some Public Domain

Based on https://github.com/hzeller/rpi-rgb-led-matrix
