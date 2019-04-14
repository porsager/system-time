{
  "targets": [
    {
      "target_name": "system-time",
      "conditions":[
        ["OS=='linux'", {
          "sources": [ "main_linux.cc" ]
          }],
        ["OS=='mac'", {
          "sources": [ "main_macos.cc" ]
        }],
        ["OS=='win'", {
          "sources": [ "main_windows.cc" ]
        }]
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
