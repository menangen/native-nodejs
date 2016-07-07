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

    void init(Local<Object> exports) {
      NODE_SET_METHOD(exports, "cosine", InterpolationMethod);
    }

NODE_MODULE(addon, init)

}