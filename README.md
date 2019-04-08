
# Set System Time

Only implemented for windows for now...

```js
const systemTime = require('system-time')

try {
  // Set time 1 hour back
  systemTime.set(new Date(Date.now() - 1000 * 60 * 60))
} catch (err) {
  // Failed
  console.log(err)
}
```
