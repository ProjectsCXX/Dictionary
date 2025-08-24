#include <gtest/gtest.h>
#include "dictionary.h"

class DictionaryTest : public testing::Test {
protected:
    DictionaryTest() {}
    ~DictionaryTest() {}

    Dictionary& FillingDictionary()
    {
        mDictionary.AddWordTranslate("cat", "кот");
        mDictionary.AddWordTranslate("cat", "кошечка");
        mDictionary.AddWordTranslate("cat", "котюгчик");
        mDictionary.AddWordTranslate("cat", "котя");
        mDictionary.AddWordTranslate("cat", "котюша");
        return mDictionary;
    }

protected:
    Dictionary mDictionary;
};

TEST(DictionaryOperationsTest, AddAndFindWord)
{
    Dictionary dict;
    dict.AddWordTranslate("cat", "кот");

    const std::set<std::string>* result = dict.FindTranslate("cat");
    ASSERT_NE(result, nullptr) << "Couldn't add a word\n";

    auto search = (*result).find("кот");
    ASSERT_NE(search, (*result).end()) << "Not fount 'kot'\n";

    dict.AddWordTranslate("cat", "кошечка");
    search = (*result).find("кошечка");
    ASSERT_NE(search, (*result).end()) << "Not fount 'koshechka'\n";
    EXPECT_EQ(result->size(), 2);

    dict.AddWordTranslate("cat", "кот");
    EXPECT_EQ(result->size(), 2);
    dict.AddWordTranslate("cat", "кошечка");
    EXPECT_EQ(result->size(), 2);
}

TEST_F(DictionaryTest, FindFunction)
{
    FillingDictionary();
    const std::set<std::string>* result = mDictionary.FindTranslate("dog");
    EXPECT_EQ(result, nullptr);

    result = mDictionary.FindTranslate("cat");
    ASSERT_NE(result, nullptr) << "Couldn't find a word\n";
}

TEST_F(DictionaryTest, DeleteFunction)
{
    FillingDictionary();

    bool isDeleted = mDictionary.DeleteWordTranslate("dog", "собака");
    EXPECT_EQ(isDeleted, false);

    isDeleted = mDictionary.DeleteWordTranslate("dog");
    EXPECT_EQ(isDeleted, false);

    const std::set<std::string>* result = mDictionary.FindTranslate("cat");
    EXPECT_EQ(result->size(), 5);

    isDeleted = mDictionary.DeleteWordTranslate("cat", "кот");
    EXPECT_EQ(isDeleted, true);
    EXPECT_EQ(result->size(), 4);

    isDeleted = mDictionary.DeleteWordTranslate("cat");
    EXPECT_EQ(isDeleted, true);

    result = mDictionary.FindTranslate("cat");
    EXPECT_EQ(result, nullptr);
}

TEST_F(DictionaryTest, GetDictionaryFunction)
{
    EXPECT_EQ(mDictionary.GetDictionary().empty(), true);
    FillingDictionary();
    EXPECT_EQ(mDictionary.GetDictionary().size(), 1);
}
