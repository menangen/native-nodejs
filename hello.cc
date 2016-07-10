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

    if (args[0]->IsObject()) {
        Local<Object> object = Local<Object>::Cast(args[0]);
        Local<Value> alphaFieldValue = object->Get(String::NewFromUtf8(isolate, "alpha"));
        Local<Value> aFieldValue = object->Get(String::NewFromUtf8(isolate, "a"));
        Local<Value> bFieldValue = object->Get(String::NewFromUtf8(isolate, "b"));

        double alpha = alphaFieldValue->NumberValue();
        double a = aFieldValue->NumberValue();
        double b = bFieldValue->NumberValue();

        double value = cosine_interpolate((float)alpha, (float)a, (float)b);

        args.GetReturnValue().Set(Number::New(isolate, value));

    }


    }

    void node_noise2(const FunctionCallbackInfo<Value> &args) {
        double x, y, value = 0.0;

        unsigned char octaves = 1;
        double persistence = 0.5;
        double lacunarity = 2.0;

        double repeatx = 1024; // arbitrary
        double repeaty = 1024; // arbitrary
        int base = 0;

        Isolate* isolate = args.GetIsolate();


        if (args[0]->IsObject()) {
            Local<Object> object = Local<Object>::Cast(args[0]);

            Local<Value> xFieldValue = object->Get(String::NewFromUtf8(isolate, "x"));
            Local<Value> yFieldValue = object->Get(String::NewFromUtf8(isolate, "y"));
            Local<Value> octavesFieldValue = object->Get(String::NewFromUtf8(isolate, "octaves"));
            Local<Value> persistenceFieldValue = object->Get(String::NewFromUtf8(isolate, "persistence"));
            Local<Value> lacunarityFieldValue = object->Get(String::NewFromUtf8(isolate, "lacunarity"));
            Local<Value> repeatxFieldValue = object->Get(String::NewFromUtf8(isolate, "repeatx"));
            Local<Value> repeatyFieldValue = object->Get(String::NewFromUtf8(isolate, "repeaty"));
            Local<Value> baseFieldValue = object->Get(String::NewFromUtf8(isolate, "base"));
            Local<Value> typeFieldValue = object->Get(String::NewFromUtf8(isolate, "type"));

            x = xFieldValue->NumberValue();
            y = yFieldValue->NumberValue();
            octaves = (unsigned char)octavesFieldValue->NumberValue();
            persistence = persistenceFieldValue->NumberValue();
            lacunarity = lacunarityFieldValue->NumberValue();
            base = (int)baseFieldValue->NumberValue();
            mountains = (unsigned char)typeFieldValue->NumberValue();

            //repeatx = (float)args[5]->NumberValue();
            //repeaty = (float)args[6]->NumberValue();

        }
        else {
            x = 0; y = 0;
        }


        if (octaves == 1) {
            // Single octave, return simple noise
            value = noise2(x, y, repeatx, repeaty, base);
        }
        else if (octaves > 1) {
            double freq = 1.0;
            double amp = 1.0;
            double max = 0.0;

            double signal;
            //value = 0.0;

            double gain = 1.1;
            double weight = 0.625;

            for (int i = 0; i < octaves; i++) {
                signal = noise2(x * freq, y * freq, repeatx * freq, repeaty * freq, base + i*3);

                if (mountains == 4) {
                    //signal *= signal; // Square the signal to increase the sharpness of the ridges.
                    signal *= weight;
                    weight = signal * gain;

                    if (weight > 1) {
                        weight = 1;
                    }
                    if (weight < 0) {
                        weight = 0;
                    }
                }

                else {
                    signal *= amp;
                    max += amp;
                    amp *= persistence;
                }

                freq *= lacunarity;
                value += signal;

            }

            if (mountains == 4) {
                value = value * 1.5 - 1.0;
            }
            else {
                value /= max;
            }

        }
        else {
            isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate, "Wrong arguments list:"
                                " (\"x\", \"y\", \"octaves\", \"persistence\", \"lacunarity\", \"repeatx\", \"repeaty\","
                                " \"base\", \"type\")")));
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