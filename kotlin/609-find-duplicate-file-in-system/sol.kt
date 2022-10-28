// https://leetcode.com/problems/find-duplicate-file-in-system/

class Solution {
  fun findDuplicate(paths: Array<String>): List<List<String>> {
      fun fullPath(dirPath: String, fileName: String) = "${dirPath}/${fileName}"
      
      val fileHashMap = mutableMapOf<String, MutableList<String>>()
      for (path in paths) {
          val substrs = path.split(' ')
          val dirPath = substrs[0]
          for (id in 1..(substrs.size - 1)) {
              val closeParen = substrs[id].length - 1
              var openParen = closeParen - 1
              while (substrs[id][openParen] != '(') --openParen
              val fileName = substrs[id].substring(0, openParen)
              val fileContents = substrs[id].substring(openParen+1, closeParen)
              fileHashMap[fileContents]?.let { fileList ->
                  fileList.add(fullPath(dirPath, fileName))
              } ?: run {
                  fileHashMap[fileContents] = mutableListOf(fullPath(dirPath, fileName))
              }
          }
      }
      
      val ret = mutableListOf<List<String>>()
      for (list in fileHashMap.values) {
          if (list.size > 1) ret.add(list)
      }
      return ret
  }
}
