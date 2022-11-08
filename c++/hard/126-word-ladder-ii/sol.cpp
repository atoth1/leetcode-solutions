// https://leetcode.com/problems/word-ladder-ii/

#include <unordered_map>

namespace
{
    bool adjacent(const std::string& l, const std::string& r)
    {
        int differentCount = 0;
        for (int id = 0; id < l.size(); ++id)
        {
            if (l[id] != r[id])
            {
                ++differentCount;
            }
            if (differentCount > 1)
            {
                return false;
            }
        }
        return true;
    }
}

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        std::unordered_map<int, std::vector<int>> adjacentLists;

        int beginWordId = -1;
        int endWordId = -1;
        for (int i = 0; i < wordList.size(); ++i)
        {
            const auto& firstWord = wordList[i];
            if (firstWord == beginWord)
                beginWordId = i;
            if (firstWord == endWord)
                endWordId = i;
            
            for (int j = i+1; j < wordList.size(); ++j)
            {
                const auto& secondWord = wordList[j];
                if (adjacent(firstWord, secondWord))
                {
                    adjacentLists[i].push_back(j);
                    adjacentLists[j].push_back(i);
                }
            }
        }
        if (endWordId == -1 || adjacentLists[endWordId].empty())
            return {};
        
        if (beginWordId == -1)
        {
            // Let key -1 represents beginWord in map
            for (int i = 0; i < wordList.size(); ++i)
            {
                const auto& word = wordList[i];
                if (adjacent(beginWord, word))
                {
                    adjacentLists[beginWordId].push_back(i);
                }
            }
        }
        
        // Breadth-first search for endWord
        std::vector<std::vector<int>> currPaths{ {beginWordId} };
        std::vector<std::vector<int>> nextPaths;
        std::vector<bool> visited(wordList.size(), false);
        if (beginWordId != -1)
            visited[beginWordId] =  true;
        while (currPaths.size() > 0)
        {
            bool found = false;
            for (const auto& path : currPaths)
            {
                for (const auto id : adjacentLists[path.back()])
                {
                    if (id == endWordId)
                        found = true;
                    
                    if (!visited[id])
                    {
                        auto nextPath = path;
                        nextPath.push_back(id);
                        nextPaths.push_back(std::move(nextPath));
                    }
                }
            }
            if (found)
                break;
            
            std::swap(currPaths, nextPaths);
            nextPaths.clear();
            for (const auto& path : currPaths)
            {
                visited[path.back()] = true;
            }
        }
        
        if (nextPaths.size() > 0)
        {
            std::vector<std::vector<std::string>> result;
            result.reserve(nextPaths.size());
            for (int i = 0; i < nextPaths.size(); ++ i)
            {
                if(nextPaths[i].back() == endWordId)
                {
                    std::vector<std::string> path;
                    path.reserve(nextPaths[i].size());
                    path.push_back(beginWord);
                    for (int j = 1; j < nextPaths[i].size(); ++j)
                    {
                        path.push_back(wordList[nextPaths[i][j]]);
                    }
                    result.push_back(std::move(path));
                }
            }
            return result;
        }
        else
        {
            return {};
        }
    }
};
