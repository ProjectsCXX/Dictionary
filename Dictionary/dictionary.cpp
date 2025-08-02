#include "englishdictionary.h"

EnglishDictionary::EnglishDictionary() = default;
EnglishDictionary::~EnglishDictionary() = default;

const std::string* EnglishDictionary::FindTranslate(const std::string& aWord) const
{
    if(auto it = mDictionary.find(aWord); it != mDictionary.end())
    {
        return &(it->second);
    }
    return nullptr;
}

const std::string* EnglishDictionary::AddWordTranslate(std::string aWord, std::string aTranslate)
{
    const auto [it, inserted] = mDictionary.try_emplace(std::move(aWord), std::move(aTranslate));
    return inserted ? nullptr : &it->second;
}

bool EnglishDictionary::DeleteWordTranslate(const std::string& aWord)
{
    return mDictionary.erase(aWord);
}

const std::map<std::string, std::string>& EnglishDictionary::GetDictionary() const
{
    return mDictionary;
}
