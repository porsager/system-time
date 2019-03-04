
# Set System Time

Only implemented for windows for now...

```js
const setTime = require('set-time')

try {
  // Set time 1 hour back
  setTime(new Date(Date.now() - 1000 * 60 * 60))
} catch (err) {
  // Failed
  console.log(err)
}
```
