#include "dictionary.h"

Dictionary::Dictionary() = default;
Dictionary::~Dictionary() = default;

const std::string* Dictionary::FindTranslate(const std::string& aWord) const
{
    if(auto it = mDictionary.find(aWord); it != mDictionary.end())
    {
        return &(it->second);
    }
    return nullptr;
}

const std::string* Dictionary::AddWordTranslate(std::string aWord, std::string aTranslate)
{
    const auto [it, inserted] = mDictionary.try_emplace(std::move(aWord), std::move(aTranslate));
    return inserted ? nullptr : &it->second;
}

bool Dictionary::DeleteWordTranslate(const std::string& aWord)
{
    return mDictionary.erase(aWord);
}

const std::map<std::string, std::string>& Dictionary::GetDictionary() const
{
    return mDictionary;
}
