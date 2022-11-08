// https://leetcode.com/problems/stream-of-characters/

#include <array>
#include <deque>
#include <memory>

class ReverseTrie {
public:
    template <class CharArray>
    void insert(const CharArray& word) {
        insertImpl(word, word.size() - 1);
    }
    
    template <class CharArray>
    bool contains(const CharArray& word) const {
        return containsImpl(word, word.size() - 1);
    }
private:
    template <class CharArray>
    void insertImpl(const CharArray& word, int pos);
    
    template <class CharArray>
    bool containsImpl(const CharArray& word, int pos) const;
    
    std::array<std::unique_ptr<ReverseTrie>, 26> children{};
    
    bool isTerminal{false};
};

template <class CharArray>
void ReverseTrie::insertImpl(const CharArray& word, int pos) {
    if (pos == -1) {
        isTerminal = true;
    }
    else if (pos >= 0 && pos < word.size()) {
        if (!children[word[pos] - 'a']) children[word[pos] - 'a'] = std::make_unique<ReverseTrie>();
        children[word[pos] - 'a']->insertImpl(word, pos - 1);
    }
}

template <class CharArray>
bool ReverseTrie::containsImpl(const CharArray& word, int pos) const {
    if (isTerminal) return true;
    else if (pos >= 0 && pos < word.size()) {
        if (!children[word[pos] - 'a']) return false;
        else return children[word[pos] - 'a']->containsImpl(word, pos - 1);
    }
    else return false;
}

class StreamChecker {
public:
    StreamChecker(vector<string>& words) : lookup(std::make_unique<ReverseTrie>()) {
        for (const auto word : words) lookup->insert(word);
    }
    
    bool query(char letter) {
        if (mostRecent.size() == MAX_WORD_LENGTH) mostRecent.pop_front();
        mostRecent.push_back(letter);
        return lookup->contains(mostRecent);
    }
    
private:
    std::unique_ptr<ReverseTrie> lookup;
    
    std::deque<char> mostRecent{};
    
    static constexpr int MAX_WORD_LENGTH = 200;
};

