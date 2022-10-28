// https://leetcode.com/problems/implement-magic-dictionary/

class MagicDictionary() {

  private val lookup = mutableMapOf<String, MutableSet<String>>()
  
  private fun String.toPattern(wildcardPos: Int): String {
      val builder = StringBuilder()
      builder.append(substring(0, wildcardPos))
      builder.append('*')
      builder.append(substring(wildcardPos + 1, length))
      return builder.toString()
  }
  
  fun buildDict(dictionary: Array<String>) {
      lookup.clear()
      for (word in dictionary) {
          for (id in word.indices) {
              val pattern = word.toPattern(id)
              lookup[pattern]?.let {
                  if (it.size == 1) it.add(word)
              } ?: run {
                  lookup[pattern] = mutableSetOf(word)
              }
          }
      }
  }

  fun search(searchWord: String): Boolean {
      var found = false
      for (id in searchWord.indices) {
          val searchPattern = searchWord.toPattern(id)
          lookup[searchPattern]?.let {
              if (it.size > 1 || !it.contains(searchWord)) found = true
          }
          if (found) break
      }
      return found
  }

}

/**
* Your MagicDictionary object will be instantiated and called as such:
* var obj = MagicDictionary()
* obj.buildDict(dictionary)
* var param_2 = obj.search(searchWord)
*/
