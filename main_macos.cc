#include <nan.h>

void setTime(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::ThrowTypeError("Not implemented");
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("setTime").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(setTime)->GetFunction());
}

NODE_MODULE(addon, Init)
