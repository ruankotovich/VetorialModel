#include "document.hpp"

// TF(t) = (Number of times term t appears in a document) / (Total number of terms in the document).
void Document::calculateTF()
{
    for (auto& word : wordAmountOnDocument) {
        // tfMap.emplace(std::piecewise_construct, std::forward_as_tuple(word.first), std::forward_as_tuple(((double)word.second / (double)totalWordsCount) + 1.0f));
        tfMap.emplace(std::piecewise_construct, std::forward_as_tuple(word.first), std::forward_as_tuple((double)word.second));
    }
}

void Document::addWord(const std::string& word)
{
    auto tuple = wordAmountOnDocument.find(word);
    totalWordsCount++;
    
    if (tuple == wordAmountOnDocument.end()) {
        wordAmountOnDocument.emplace(word, 1);
    } else {
        wordAmountOnDocument[word]++;
    }
}

Document::Document()
{
    id = -1;
    totalWordsCount = 0;
}
