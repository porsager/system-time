const systemTime = require('./build/Release/system-time')

module.exports.setTime = function(date) {
  date = new Date(date)
  systemTime.setTime(
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
