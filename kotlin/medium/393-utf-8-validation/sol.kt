// https://leetcode.com/problems/utf-8-validation/

private val oneBitMask: UInt =   0b10000000.toUInt()
private val twoBitMask: UInt =   0b11000000.toUInt()
private val threeBitMask: UInt = 0b11100000.toUInt()
private val fourBitMask: UInt =  0b11110000.toUInt()
private val fiveBitMask: UInt =  0b11111000.toUInt()

class Solution {
    fun validUtf8(data: IntArray): Boolean {
        var pos = 0
        while (pos < data.size) {
            if (data[pos].toUInt() and oneBitMask == 0u) {
                ++pos
            } else if (pos == data.size || data[pos].toUInt() and threeBitMask == twoBitMask) {
                ++pos
                if (pos == data.size || !isContinuationByte(data[pos++])) return false
            } else if (data[pos].toUInt() and fourBitMask == threeBitMask) {
                ++pos
                repeat (2) {
                    if (pos == data.size || !isContinuationByte(data[pos++])) return false
                }
            } else if (data[pos].toUInt() and fiveBitMask == fourBitMask) {
                ++pos
                repeat (3) {
                    if (pos == data.size || !isContinuationByte(data[pos++])) return false
                }
            } else {
                // Should probably throw or something, I don't know
                return false
            }
        }
        return true
    }
    
    private fun isContinuationByte(data: Int): Boolean {
        return data.toUInt() and twoBitMask == oneBitMask
    }
}
