#include <napi.h>

Napi::Value set(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Error::New(env, Napi::String::New(env, "Not implemented")).ThrowAsJavaScriptException();

  return env.Null();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  return Napi::Function::New(env, set);
}

NODE_API_MODULE(addon, Init)
