#include <nan.h>

using namespace v8;

void setTime(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::ThrowTypeError("Not implemented");
  return;
}

void Init(v8::Local<v8::Object> exports) {
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(setTime);
  Local<Context> context = Nan::GetCurrentContext();
  exports->Set(Nan::New("setTime").ToLocalChecked(),
               tpl->GetFunction(context).ToLocalChecked());
}

NODE_MODULE(addon, Init)
