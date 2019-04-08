const systemTime = require('./build/Release/system-time')

module.exports.set = function(date) {
  date = new Date(date)
  systemTime.set(
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
