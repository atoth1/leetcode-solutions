// https://leetcode.com/problems/maximum-frequency-stack/

import java.util.TreeMap
import java.util.TreeSet

class FreqStack {

    private val idListLookup: MutableMap<Int, MutableList<Int>> = mutableMapOf()
    
    private val freqLookup: TreeMap<Int, TreeSet<Int>> = TreeMap()
    
    private var nextId = 0
    
    private val comp: Comparator<Int> = Comparator {
            x, y -> (idListLookup[x]?.last() ?: 0) - (idListLookup[y]?.last() ?: 0)
        }
    
    fun push(`val`: Int) {
        val idList = idListLookup.getOrPut(`val`) { mutableListOf() }
        freqLookup[idList.size]?.remove(`val`)
        
        idList.add(nextId++)
        freqLookup.getOrPut(idList.size) { TreeSet(comp) }.add(`val`)
    }

    fun pop(): Int {
        val popped = freqLookup.lastEntry()?.let { (freq, vals) ->
            val ret = vals.pollLast()
            if (vals.isEmpty()) {
                freqLookup.remove(freq)
            }
            ret
        } ?: Int.MIN_VALUE
        
        idListLookup[popped]?.let { idList ->
            idList.removeLast()
            if (idList.isEmpty()) {
                idListLookup.remove(popped)
            } else {
                freqLookup.getOrPut(idList.size) { TreeSet(comp) }.add(popped)
            }
        }
        return popped
    }

}

/**
 * Your FreqStack object will be instantiated and called as such:
 * var obj = FreqStack()
 * obj.push(`val`)
 * var param_2 = obj.pop()
 */
 