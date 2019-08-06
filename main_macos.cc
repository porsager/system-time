#include <nan.h>

using namespace v8;

void setTime(const Nan::FunctionCallbackInfo<Value>& info) {
  Nan::ThrowTypeError("Not implemented");
  return;
}

void Init(Local<Object> exports) {
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(setTime);
  Local<Context> context = Nan::GetCurrentContext();
  exports->Set(Nan::New("setTime").ToLocalChecked(),
               tpl->GetFunction(context).ToLocalChecked());
}

NODE_MODULE(addon, Init)
