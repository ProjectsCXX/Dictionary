#pragma once
#include <map>
#include <string>
#include <set>

class Dictionary
{
private:
    std::map<std::string, std::set<std::string>> mDictionary{};

public:
    Dictionary();
    ~Dictionary();

    const std::set<std::string>* FindTranslate(const std::string& aWord) const;
    void AddWordTranslate(std::string aWord, std::string aTranslate);
    bool DeleteWordTranslate(const std::string& aWord);
    bool DeleteWordTranslate(const std::string& aWord, std::string aTranslate);
    const std::map<std::string, std::set<std::string>>& GetDictionary() const;
};
