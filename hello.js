const addon = require('./build/Release/addon');

/*
console.log(addon.cosine(0.6, 0.5, 0.75)); // Cos interpolation
console.log(0.6 * (0.5 + 0.75)); // Linear interpolation
*/

const octaves = 1
let freq = 10.0 * octaves

const lacunarity = 2.0
const persistence = 0.5

let x = 1005
const y = 1005

for (let i = 0; i < 100; i++) {

	console.log(addon.perlin2(x / freq, y / freq, octaves, persistence, lacunarity, 1024, 1024, 0, 0)); // perlin

	x += i

}