// https://leetcode.com/problems/prefix-and-suffix-search/

#include <algorithm>
#include <array>
#include <iterator>
#include <memory>
#include <unordered_set>

class Trie
{
public:
    Trie() = default;
    
    void insert(const std::string& word, int id)
    {
        insertImpl(word, id, 0);
    }
    
    std::vector<int> search(const std::string& word)
    {
        return searchImpl(word, 0);
    }
    
private:
    void insertImpl(const std::string& word, int id, int pos)
    {
        ids_.push_back(id);
        if (pos < word.size())
        {
            if (!children_[word[pos]-'a'])
            {
                children_[word[pos]-'a'] = std::make_unique<Trie>();
            }
            children_[word[pos]-'a']->insertImpl(word, id, pos+1);
        }
    }
    
    std::vector<int> searchImpl(const std::string& word, int pos)
    {
        if (pos == word.size())
        {
            return ids_;
        }
        else if (pos < word.size() && children_[word[pos]-'a'])
        {
            return children_[word[pos]-'a']->searchImpl(word, pos+1);
        }
        else
        {
            return {};
        }
    }
    
    std::array<std::unique_ptr<Trie>, 26> children_{};
    std::vector<int> ids_{};
};

class WordFilter {
public:
    WordFilter(vector<string>& words)
      : words_(words)
    {
        std::unordered_set<std::string> insertedWords;
        prefixSearch_ = std::make_unique<Trie>();
        suffixSearch_ = std::make_unique<Trie>();
        // Iterate backwards so that largest id of repeated words is registered
        for (int id = words_.size()-1; id >= 0; --id)
        {
            auto word = words_[id];
            if (insertedWords.count(word) == 0)
            {
                insertedWords.insert(word);
                prefixSearch_->insert(word, id);
                std::reverse(word.begin(), word.end());
                suffixSearch_->insert(word, id);
            }
        }
    }
    
    int f(string prefix, string suffix) {
        auto prefixIds = prefixSearch_->search(prefix);
        std::reverse(suffix.begin(), suffix.end());
        auto suffixIds = suffixSearch_->search(suffix);
        std::vector<int> intersectionIds{};
        std::set_intersection(prefixIds.cbegin(), prefixIds.cend(), suffixIds.cbegin(),
            suffixIds.cend(), std::back_inserter(intersectionIds), std::greater<int>());
        return intersectionIds.empty() ? -1 : intersectionIds.front();
    }
    
private:
    std::vector<std::string> words_;
    std::unique_ptr<Trie> prefixSearch_;
    std::unique_ptr<Trie> suffixSearch_;
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(prefix,suffix);
 */
