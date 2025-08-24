#include "dictionary.h"

Dictionary::Dictionary() = default;
Dictionary::~Dictionary() = default;

const std::set<std::string>* Dictionary::FindTranslate(const std::string& aWord) const
{
    if(auto it = mDictionary.find(aWord); it != mDictionary.end())
    {
        return &(it->second);
    }
    return nullptr;
}

void Dictionary::AddWordTranslate(std::string aWord, std::string aTranslate)
{
    const auto [it, inserted] = mDictionary.try_emplace(std::move(aWord), std::set<std::string>{});
    it->second.insert(std::move(aTranslate));
    //return inserted ? nullptr : &it->second;
}

bool Dictionary::DeleteWordTranslate(const std::string& aWord)
{
    return mDictionary.erase(aWord);
}

bool Dictionary::DeleteWordTranslate(const std::string& aWord, std::string aTranslate)
{
    auto it = mDictionary.find(aWord);
    if(it == mDictionary.end())
    {
        return false;
    }

    bool delete_translate = it->second.erase(aTranslate);

    if(it->second.empty())
    {
        mDictionary.erase(it);
        return true;
    }
    return delete_translate;
}

const std::map<std::string, std::set<std::string>>& Dictionary::GetDictionary() const
{
    return mDictionary;
}
