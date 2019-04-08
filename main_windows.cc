#include <napi.h>
#include <windows.h>

Napi::Value setTime(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  HANDLE hToken;
  TOKEN_PRIVILEGES tp;
  TOKEN_PRIVILEGES oldtp;
  DWORD dwSize = sizeof(TOKEN_PRIVILEGES);
  LUID luid;

  SYSTEMTIME st{
    (WORD)info[0].As<Napi::Number>().Int32Value(),
    (WORD)info[1].As<Napi::Number>().Int32Value(),
    (WORD)info[2].As<Napi::Number>().Int32Value(),
    (WORD)info[3].As<Napi::Number>().Int32Value(),
    (WORD)info[4].As<Napi::Number>().Int32Value(),
    (WORD)info[5].As<Napi::Number>().Int32Value(),
    (WORD)info[6].As<Napi::Number>().Int32Value(),
    (WORD)info[7].As<Napi::Number>().Int32Value()
  };

  if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
    Napi::Error::New(env, "Failed Calling OpenProcessToken").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!LookupPrivilegeValue(NULL, SE_SYSTEMTIME_NAME, &luid)) {
    Napi::Error::New(env, "Failed Calling LookupPrivilegeValue").ThrowAsJavaScriptException();
    CloseHandle(hToken);
    return env.Null();
  }

  ZeroMemory(&tp, sizeof(tp));
  tp.PrivilegeCount = 1;
  tp.Privileges[0].Luid = luid;
  tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

  if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), &oldtp, &dwSize)) {
    Napi::Error::New(env, "Failed Calling AdjustTokenPrivileges").ThrowAsJavaScriptException();
    CloseHandle(hToken);
    return env.Null();
  }

  if (!SetSystemTime(&st)) {
    Napi::Error::New(env, "Failed Calling SetSystemTime").ThrowAsJavaScriptException();
    CloseHandle(hToken);
    return env.Null();
  }

  AdjustTokenPrivileges(hToken, FALSE, &oldtp, dwSize, NULL, NULL);
  if (GetLastError() != ERROR_SUCCESS) {
    Napi::Error::New(env, Napi::String::New(env, "Failed Calling AdjustTokenPrivileges")).ThrowAsJavaScriptException();
    CloseHandle(hToken);
    return env.Null();
  }

  CloseHandle(hToken);
  return env.Null();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("set", Napi::Function::New(env, setTime));
  return exports;
}

NODE_API_MODULE(addon, Init)
