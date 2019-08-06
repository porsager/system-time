#include <nan.h>
#include <windows.h>

using namespace v8;

void setTime(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  HANDLE hToken;
  TOKEN_PRIVILEGES tp;
  TOKEN_PRIVILEGES oldtp;
  DWORD dwSize = sizeof(TOKEN_PRIVILEGES);
  LUID luid;

  SYSTEMTIME st{
    (WORD)info[0]->NumberValue(),
    (WORD)info[1]->NumberValue(),
    (WORD)info[2]->NumberValue(),
    (WORD)info[3]->NumberValue(),
    (WORD)info[4]->NumberValue(),
    (WORD)info[5]->NumberValue(),
    (WORD)info[6]->NumberValue(),
    (WORD)info[7]->NumberValue()
  };

  if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
    Nan::ThrowTypeError("Failed Calling OpenProcessToken");
    return;
  }

  if (!LookupPrivilegeValue(NULL, SE_SYSTEMTIME_NAME, &luid)) {
    Nan::ThrowTypeError("Failed Calling LookupPrivilegeValue");
    CloseHandle(hToken);
    return;
  }

  ZeroMemory(&tp, sizeof(tp));
  tp.PrivilegeCount = 1;
  tp.Privileges[0].Luid = luid;
  tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

  if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), &oldtp, &dwSize)) {
    Nan::ThrowTypeError("Failed Calling AdjustTokenPrivileges");
    CloseHandle(hToken);
    return;
  }

  if (!SetSystemTime(&st)) {
    Nan::ThrowTypeError("Failed Calling SetSystemTime");
    CloseHandle(hToken);
    return;
  }

  AdjustTokenPrivileges(hToken, FALSE, &oldtp, dwSize, NULL, NULL);
  if (GetLastError() != ERROR_SUCCESS) {
    Nan::ThrowTypeError("Failed Calling AdjustTokenPrivileges");
    CloseHandle(hToken);
    return;
  }

  CloseHandle(hToken);
  return;
}

void Init(v8::Local<v8::Object> exports) {
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(setTime);
  Local<Context> context = Nan::GetCurrentContext();
  exports->Set(Nan::New("setTime").ToLocalChecked(),
               tpl->GetFunction(context).ToLocalChecked());
}

NODE_MODULE(addon, Init)
