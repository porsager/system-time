#include <napi.h>

Napi::Value setTime(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Error::New(env, Napi::String::New(env, "Not implemented")).ThrowAsJavaScriptException();

  return env.Null();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("set", Napi::Function::New(env, setTime));
  return exports;
}

NODE_API_MODULE(addon, Init)
