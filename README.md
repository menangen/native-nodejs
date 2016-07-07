# Node.js 6.2 Native Addons example #


> hello.cc - C++ code

>test.h - C code

> test.js - Node.js javascript used current addon (C + C++ mix).

Compiled and tested under **node v6.2.2**, Clang [Apple LLVM version 8.0.0].

Usage in javascript as:
```javascript
const addon = require('./build/Release/addon');

console.log(addon.hello(0.5));
```

* `const addon` - addon(.so/.dll) (addon.node)
* `hello(0.5)` - call **Function** *hello* with (*0.5*) **Number** parameter.
* `hello` call C function `float cosine_interpolate()` from Node namespace module.


1. Install node-gyp: `sudo npm install -g node-gyp`
2. Configure with `node-gyp configure`
3. Compile with: `node-gyp build`