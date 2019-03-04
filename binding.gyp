{
  "targets": [
    {
      "target_name": "native",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "conditions":[
        ["OS=='linux'", {
          "sources": [ "native_linux.cc" ]
          }],
        ["OS=='mac'", {
          "sources": [ "native_mac.cc" ]
        }],
        ["OS=='win'", {
          "sources": [ "main_windows.cc" ]
        }]
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
      "defines": [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }
  ]
}
