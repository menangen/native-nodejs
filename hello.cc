// hello.cc
#include <node.h>
#include "test.h"

namespace demo {

    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Object;
    using v8::Number;
    using v8::String;
    using v8::Value;

    using v8::Exception;

    void InterpolationMethod(const FunctionCallbackInfo<Value> &args) {
      Isolate* isolate = args.GetIsolate();

      if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong arguments list: (Number, Number, Number)")));
        return;
      }

      double alpha = args[0]->NumberValue();
      double a = args[1]->NumberValue();
      double b = args[2]->NumberValue();

      double value = cosine_interpolate((float)alpha, (float)a, (float)b);

      args.GetReturnValue().Set(Number::New(isolate, value));
    }

    void node_noise2(const FunctionCallbackInfo<Value> &args) {
        double x, y, value;

        int octaves = 1;
        float persistence = 0.5f;
        float lacunarity = 2.0f;
        unsigned char msType = 0;

        float repeatx = 1024; // arbitrary
        float repeaty = 1024; // arbitrary
        int base = 0;

        Isolate* isolate = args.GetIsolate();

        /* "x", "y", "octaves", "persistence", "lacunarity", "repeatx", "repeaty", "base", "msType" */

        x = args[0]->NumberValue();
        y = args[1]->NumberValue();
        //octaves = (int)args[2]->NumberValue();
        //persistence = (float)args[3]->NumberValue();
        //lacunarity = (float)args[4]->NumberValue();
        //repeatx = (float)args[5]->NumberValue();
        //repeaty = (float)args[6]->NumberValue();
        //base = (int)args[7]->NumberValue();
        //msType = (unsigned char)args[8]->NumberValue();


        mountains = msType;

        if (octaves == 1 || 1) { /* TODO: remove it condition! */
            // Single octave, return simple noise
            value = noise2((float)x, (float)y, repeatx, repeaty, base);
        }

        // return perlin value
        args.GetReturnValue().Set(Number::New(isolate, value));
    }

    void init(Local<Object> exports) {
      NODE_SET_METHOD(exports, "cosine", InterpolationMethod);
      NODE_SET_METHOD(exports, "perlin2", node_noise2);
    }

NODE_MODULE(addon, init)

}