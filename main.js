
var bindings = require('bindings')
var addon = bindings('rpi_rgb_led_matrix')

var isStarted = false

var board = module.exports = {
	start: function(rows, columns, chain, paralel, clearOnClose) {
		if (!rows) rows = 32
		if (!columns) columns = 32
		if (!chain) chain = 1
		if (!parallel) parallel = 1
		clearOnClose = clearOnClose !== false

		addon.start(rows, columns, chain, parallel)
		isStarted = true

		if (clearOnClose) {
			process.on('exit', function() { addon.stop() })
			process.on('SIGINT', function() { addon.stop(); process.exit(0) })
		}
	},

	stop: function() {
		addon.stop()
		isStarted = false
	},

	setPixel: function(x, y, r, g, b) {
		if (!isStarted) throw new Error("'setPixel' called before 'start'")
		if (r > 255 || g > 255 || b > 255) throw new Error("Colors should be between 0 and 255")
		addon.setPixel(x, y, r, g, b)
	},

	fill: function(r, g, b) {
		if (!isStarted) throw new Error("'fill' called before 'start'")
		if (r > 255 || g > 255 || b > 255) throw new Error("Colors should be between 0 and 255")
		addon.fill(r, g, b)
	},

	drawCanvas: function(ctx, width, height) {
		// this is kind of slow but could be optimized by passing imageData.data directly
		// and copying it to the screen framebuffer
		if (!isStarted) throw new Error("'drawCanvas' called before 'start'")

		var imageData = ctx.getImageData(0, 0, width, height)
		var data = imageData.data

		for (var i = 0; i < data.length; i += 4) {
			var y = Math.floor(i / 4 / width) 
			var x = i / 4 - y * width
			board.setPixel(x, y, data[i], data[i + 1], data[i + 2])
		}
	},

	clear: function() {
		if (!isStarted) throw new Error("'clear' called before 'start'")
		addon.clear()
	}
}
