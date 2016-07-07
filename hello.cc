// hello.cc
#include <node.h>
#include "test.h"

namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Number;
using v8::Value;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  double alpha = args[0]->NumberValue();
  double value = cosine_interpolate(alpha, 0.5f, 0.75f);

  args.GetReturnValue().Set(Number::New(isolate, value));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(addon, init)

}