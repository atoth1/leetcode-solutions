// https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays/

class Solution {
  fun kthSmallestProduct(nums1: IntArray, nums2: IntArray, k: Long): Long {
      // Equivalent of std::equal_range would be nice
      val nums1ZerosBegin = nums1.lowerBound(0)
      val nums1ZerosEnd = nums1.upperBound(0)
      val nums2ZerosBegin = nums2.lowerBound(0)
      val nums2ZerosEnd = nums2.upperBound(0)
      
      val nums1NegCount = nums1ZerosBegin
      val nums1PosCount = nums1.size - nums1ZerosEnd
      val nums2NegCount = nums2ZerosBegin
      val nums2PosCount = nums2.size - nums2ZerosEnd
      
      val negCount = nums1NegCount.toLong()*nums2PosCount + nums1PosCount.toLong()*nums2NegCount
      val posCount = nums1NegCount.toLong()*nums2NegCount + nums1PosCount.toLong()*nums2PosCount
      val zeroCount = nums1.size*nums2.size.toLong() - negCount - posCount
      
      val negRange1 = nums1.copyOfRange(0, nums1NegCount)
      val posRange1 = nums1.copyOfRange(nums1.size - nums1PosCount, nums1.size)
      val negRange2 = nums2.copyOfRange(0, nums2NegCount)
      val posRange2 = nums2.copyOfRange(nums2.size - nums2PosCount, nums2.size)
      
      return if (k <= negCount) {
          negImpl(negRange1, posRange1, negRange2, posRange2, k)
      } else if (k <= negCount + zeroCount) {
          0.toLong()
      } else {
          val count = k - negCount - zeroCount
          posImpl(negRange1, posRange1, negRange2, posRange2, count)
      }
  }
  
  private fun IntArray.lowerBound(value: Int): Int {
      var l = 0
      var r = size-1
      return if (get(l) >= value) l
      else if (get(r) < value) size
      else {
          while (l+1 != r) {
              val m = (l+r)/2
              if (get(m) < value) {
                  l = m
              } else {
                  r = m
              }
          }
          r
      }
  }
  
  private fun IntArray.upperBound(value: Int): Int {
      var l = 0
      var r = size-1
      return if (get(l) > value) 0
      else if (get(r) <= value) size
      else {
          while (l+1 != r) {
              val m = (l+r)/2
              if (get(m) <= value) {
                  l = m
              } else {
                  r = m
              }
          }
          r
      }
  }
  
  private fun Long.countLessEqual(range1: IntArray, range2: IntArray): Long {
      if (range1.isEmpty() || range2.isEmpty()) return 0.toLong()
      var count = 0.toLong()
      if (this < 0) {
          if (range1.first() < 0) {
              // One range is all > 0, other is all < 0. If needed relabel so range1 > 0
              count = countLessEqual(range2, range1)
          } else {
              var pos1 = 0
              var pos2 = 0
              while (pos1 < range1.size && range1[pos1].toLong() * range2[pos2] > this) ++pos1
              while (pos1 < range1.size) {
                  while (pos2 < range2.size && range1[pos1].toLong() * range2[pos2] <= this) ++pos2
                  count += pos2
                  ++pos1
              }
          }
      } else {
          if (range1.first() < 0) {
              // Both ranges are all < 0
              var pos2 = 0
              for (pos1 in range1.size-1 downTo 0) {
                  while (pos2 < range2.size && range1[pos1].toLong() * range2[pos2] > this) ++pos2
                  if (pos2 == range2.size) break
                  count += range2.size - pos2
              }
          } else {
              // Both ranges are all > 0
              var pos2 = range2.size
              for (num1 in range1) {
                  while (pos2 > 0 && num1.toLong() * range2[pos2-1] > this) --pos2
                  if (pos2 == 0) break
                  count += pos2
              }
          }
      }
      return count
  }
  
  private fun negImpl(
      negRange1: IntArray,
      posRange1: IntArray,
      negRange2: IntArray,
      posRange2: IntArray,
      count: Long
  ): Long {
      var lBound = 0.toLong()
      if (negRange1.size > 0 && posRange2.size > 0) {
          lBound = negRange1.first().toLong() * posRange2.last()
      }
      if (posRange1.size > 0 && negRange2.size > 0) {
          lBound = minOf(posRange1.last().toLong() * negRange2.first(), lBound)
      }
      --lBound
      var rBound = -1.toLong()
      
      while (lBound + 1 != rBound) {
          val m = (lBound + rBound)/2
          if (m.countLessEqual(negRange1, posRange2)
              + m.countLessEqual(posRange1, negRange2) < count
          ) {
              lBound = m
          } else {
              rBound = m
          }
      }
      return rBound
  }
  
  private fun posImpl(
      negRange1: IntArray,
      posRange1: IntArray,
      negRange2: IntArray,
      posRange2: IntArray,
      count: Long
  ): Long {
      var lBound = 0.toLong()
      var rBound = 0.toLong()
      if (negRange1.size > 0 && negRange2.size > 0) {
          rBound = negRange1.first().toLong() * negRange2.first()
      }
      if (posRange1.size > 0 && posRange2.size > 0) {
          rBound = maxOf(posRange1.last().toLong() * posRange2.last(), rBound)
      }
      
      while (lBound + 1 != rBound) {
          val m = (lBound + rBound)/2
          if (m.countLessEqual(negRange1, negRange2)
              + m.countLessEqual(posRange1, posRange2) < count
          ) {
              lBound = m
          } else {
              rBound = m
          }
      }
      return rBound
  }
}
