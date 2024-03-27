// https://leetcode.com/problems/text-justification/

class Solution {
    
    private data class IntWrapper(var value: Int)
    
    private fun getNextLine(words: Array<String>, maxWidth: Int, pos: IntWrapper): String {
        val lineWords = mutableListOf(words[pos.value++])
        var len = lineWords[0].length
        while (pos.value < words.size && len + words[pos.value].length + 1 <= maxWidth) {
            lineWords.add(words[pos.value++])
            len += 1 + lineWords.last().length
        }
        
        val builder = StringBuilder(lineWords[0])
        if (pos.value == words.size || lineWords.size == 1) {
            for (id in 1 until lineWords.size) builder.append(' ').append(lineWords[id])
            builder.append(" ".repeat(maxWidth - builder.length)).toString()
        } else {
            val nonSpaces = len - lineWords.size + 1
            val spaces = maxWidth - nonSpaces
            val spacesPer = spaces / (lineWords.size - 1)
            var excess = spaces - spacesPer * (lineWords.size - 1)
            for (id in 1 until lineWords.size) {
                if (excess > 0) {
                    builder.append(' ')
                    --excess
                }
                builder.append(" ".repeat(spacesPer)).append(lineWords[id])
            }
        }
        return builder.toString()
    }
    
    fun fullJustify(words: Array<String>, maxWidth: Int): List<String> {
        val ret = mutableListOf<String>()
        val pos = IntWrapper(0)
        while (pos.value < words.size) {
            ret.add(getNextLine(words, maxWidth, pos))
        }
        return ret
    }
}
