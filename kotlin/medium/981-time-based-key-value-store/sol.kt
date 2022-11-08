// https://leetcode.com/problems/time-based-key-value-store/

class TimeMap() {

  fun set(key: String, value: String, timestamp: Int) {
      storage[key]?.apply {
          add(TimestampToValue(timestamp, value))
      } ?: run { storage[key] = mutableListOf(TimestampToValue(timestamp, value)) }
  }

  fun get(key: String, timestamp: Int): String {
      return storage[key]?.let { pairs ->
          bs(pairs, timestamp)
      } ?: ""
  }
  
  private fun bs(touches: List<TimestampToValue>, timestamp: Int): String {
      var l = 0
      var r = touches.size - 1
      if (timestamp < touches[l].time) {
          return ""
      } else if (timestamp >= touches[r].time) {
          return touches[r].value
      } else {
          while (l+1 != r) {
              val m = (l+r)/2
              if (touches[m].time <= timestamp) l = m
              else r = m
          }
          return touches[l].value
      }
  }
  
  private data class TimestampToValue(val time: Int, val value: String)
  
  private val storage = mutableMapOf<String, MutableList<TimestampToValue>>()

}

/**
* Your TimeMap object will be instantiated and called as such:
* var obj = TimeMap()
* obj.set(key,value,timestamp)
* var param_2 = obj.get(key,timestamp)
*/
