#pragma once
#include <map>
#include <string>

class EnglishDictionary
{
private:
    std::map<std::string, std::string> mDictionary{};
public:
    EnglishDictionary();
    ~EnglishDictionary();

    const std::string* FindTranslate(const std::string& aWord) const;
    const std::string* AddWordTranslate(std::string aWord, std::string aTranslate);
    bool DeleteWordTranslate(const std::string& aWord);
    const std::map<std::string, std::string>& GetDictionary() const;
};
