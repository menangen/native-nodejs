const addon = require('./build/Release/addon');

console.log(addon.cosine(0.6, 0.5, 0.75)); // Cos interpolation
console.log(0.6 * (0.5 + 0.75)); // Linear interpolation