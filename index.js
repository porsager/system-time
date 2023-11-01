const systemTime = require('./build/Release/system-time')

module.exports.setTime = function(date) {
  date = new Date(date)

  if (process.platform === 'win32') {
    systemTime.setTime(
      date.getUTCFullYear(),
      date.getUTCMonth() + 1,
      date.getUTCDay(),
      date.getUTCDate(),
      date.getUTCHours(),
      date.getUTCMinutes(),
      date.getUTCSeconds(),
      date.getUTCMilliseconds()
    )
  } else if (process.platform === 'linux') {
    systemTime.setTime(
      Math.floor(date.getTime() / 1000),
      date.getTime() % 1000 * 1000000
    )
  } else {
    throw new Error('Not implemented')
  }
}
