{
  "targets": [
    {
      "target_name": "system-time",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "conditions":[
        ["OS=='linux'", {
          "sources": [ "main_linux.cc" ]
          }],
        ["OS=='mac'", {
          "sources": [ "main_mac.cc" ]
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
