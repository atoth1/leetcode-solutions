// https://leetcode.com/problems/design-hashset/

class MyHashSet() {

  fun add(key: Int) {
      val bucketId = bucketId(key)
      if (!buckets[bucketId].contains(key)) buckets[bucketId].add(key)
  }

  fun remove(key: Int) {
      val bucketId = bucketId(key)
      buckets[bucketId].remove(key)
  }

  fun contains(key: Int): Boolean {
      val bucketId = bucketId(key)
      return buckets[bucketId].contains(key)
  }

  // Probably tune default value of this, definitely allow it specified through constructor
  private val numBuckets = 1000
  
  private val buckets = Array(numBuckets) { mutableListOf<Int>() }
  
  private fun bucketId(key: Int): Int {
      return key.hashCode() % numBuckets
  }
}

/**
* Your MyHashSet object will be instantiated and called as such:
* var obj = MyHashSet()
* obj.add(key)
* obj.remove(key)
* var param_3 = obj.contains(key)
*/
