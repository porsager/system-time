const set = require('./build/Release/native')

module.exports = function(date) {
  date = new Date(date)
  set(
    date.getUTCFullYear(),
    date.getUTCMonth() + 1,
    date.getUTCDay(),
    date.getUTCDate(),
    date.getUTCHours(),
    date.getUTCMinutes(),
    date.getUTCSeconds(),
    date.getUTCMilliseconds(),
  )
}
