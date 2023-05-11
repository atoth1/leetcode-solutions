// https://leetcode.com/problems/number-of-digit-one/

class Solution {
    
    private fun initialMap(): MutableMap<Int, Int> = mutableMapOf(
        0 to 0, 1 to 1, 2 to 1, 3 to 1, 4 to 1,
        5 to 1, 6 to 1, 7 to 1, 8 to 1, 9 to 1
    )
    
    private data class Data(val leading: Int, val remainder: Int, val tenToPow: Int)

    private fun Int.getData(): Data {
        var tenToPow = 1
        while (10 * tenToPow <= this) tenToPow *= 10
        val leading = this / tenToPow
        val remainder = this - leading * tenToPow
        return Data(leading, remainder, tenToPow)
    }
    
    private fun impl(n: Int, cache: MutableMap<Int, Int>): Int {
        return cache[n] ?: run {
            val data = n.getData()
            val ret = if (data.leading == 1) {
                impl(data.tenToPow - 1, cache) + impl(data.remainder, cache) + data.remainder + 1
            } else {
                data.leading * impl(data.tenToPow - 1, cache) + impl(data.remainder, cache) + data.tenToPow
            }
            cache[n] = ret
            ret
        }
    }
    
    fun countDigitOne(n: Int): Int {
        return impl(n, initialMap())
    }
}