const addon = require('./build/Release/addon');

console.log("Cosine vs Linear interpolation for noise:")

console.log(addon.cosine({"alpha": 0.6, "a": 0.5, "b": 0.75})); // Cos interpolation
console.log(0.6 * (0.5 + 0.75)); // Linear interpolation

console.log("Perlin noise:")

const octaves = 1
let freq = 10.0 * octaves

const lacunarity = 2.0
const persistence = 0.5

let x = 1005
const y = 1005

for (let i = 0; i < 10; i++) {

	console.log(i + " " + addon.perlin2({
		"x": (x + i) / freq,
		"y": (y + i) / freq,
		"octaves": octaves,
		"persistence": persistence,
		"lacunarity": lacunarity,
		"base": 0,
		"type": 0
		})); // perlin


}
