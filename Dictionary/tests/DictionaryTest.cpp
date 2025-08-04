#include <gtest/gtest.h>
#include "dictionary.h"

TEST(DictionaryTest, AddAndFindWord) {
    Dictionary dict;
    dict.AddWordTranslate("cat", "кот");

    const std::string* result = dict.FindTranslate("cat");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, "кот");
}

TEST(DictionaryTest, FindNonExistentWord) {
    Dictionary dict;
    const std::string* result = dict.FindTranslate("dog");
    EXPECT_EQ(result, nullptr);
}
