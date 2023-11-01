#include <time.h>
#include <nan.h>

using namespace v8;

void setTime(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  struct timespec when;

  when.tv_sec = info[0]->NumberValue(Nan::GetCurrentContext()).FromJust();
  when.tv_nsec = info[1]->NumberValue(Nan::GetCurrentContext()).FromJust();

  if (clock_settime(CLOCK_REALTIME, &when) != 0) {
    Nan::ThrowTypeError("Could not set time");
  }

  return;
}

void Init(v8::Local<v8::Object> exports) {
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(setTime);
  Local<Context> context = Nan::GetCurrentContext();
  exports->Set(context, Nan::New("setTime").ToLocalChecked(),
               tpl->GetFunction(context).ToLocalChecked());
}

NODE_MODULE(addon, Init)
