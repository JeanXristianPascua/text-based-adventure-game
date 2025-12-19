#include <vector>
#include <string>
#include "gtest/gtest.h"
#include "StringUtils.hpp"

// toLower

TEST(StringUtilsTest, ToLowerBasic) {
    EXPECT_EQ(StringUtils::toLower("HELLO"), "hello");
    EXPECT_EQ(StringUtils::toLower("World"), "world");
}

TEST(StringUtilsTest, ToLowerMixedCase) {
    EXPECT_EQ(StringUtils::toLower("HeLLo WoRLd"), "hello world");
}

TEST(StringUtilsTest, ToLowerEmptyString) {
    EXPECT_EQ(StringUtils::toLower(""), "");
}

// equalsIgnoreCase

TEST(StringUtilsTest, EqualsIgnoreCaseDifferentCase) {
    EXPECT_TRUE(StringUtils::equalsIgnoreCase("hello", "HELLO"));
    EXPECT_TRUE(StringUtils::equalsIgnoreCase("Sword", "sword"));
}

TEST(StringUtilsTest, EqualsIgnoreCaseDifferentStrings) {
    EXPECT_FALSE(StringUtils::equalsIgnoreCase("hello", "world"));
    EXPECT_FALSE(StringUtils::equalsIgnoreCase("test", "testing"));
}

TEST(StringUtilsTest, EqualsIgnoreCaseEmptyStrings) {
    EXPECT_TRUE(StringUtils::equalsIgnoreCase("", ""));
}

// containsIgnoreCase

TEST(StringUtilsTest, ContainsIgnoreCaseBasic) {
    EXPECT_TRUE(StringUtils::containsIgnoreCase("hello world", "world"));
    EXPECT_TRUE(StringUtils::containsIgnoreCase("hello world", "WORLD"));
}

TEST(StringUtilsTest, ContainsIgnoreCaseNotFound) {
    EXPECT_FALSE(StringUtils::containsIgnoreCase("hello world", "test"));
}

TEST(StringUtilsTest, ContainsIgnoreCasePartialMatch) {
    EXPECT_TRUE(StringUtils::containsIgnoreCase("Poison Flower", "poison"));
}

// trim

TEST(StringUtilsTest, TrimBothEnds) {
    EXPECT_EQ(StringUtils::trim("   hello   "), "hello");
    EXPECT_EQ(StringUtils::trim("  hello world  "), "hello world");
}

TEST(StringUtilsTest, TrimNoSpaces) {
    EXPECT_EQ(StringUtils::trim("hello"), "hello");
}

TEST(StringUtilsTest, TrimOnlySpaces) {
    EXPECT_EQ(StringUtils::trim("   "), "");
}

// join

TEST(StringUtilsTest, JoinBasic) {
    std::vector<std::string> words = {"hello", "world"};
    EXPECT_EQ(StringUtils::join(words), "hello world");
}

TEST(StringUtilsTest, JoinWithStartIndex) {
    std::vector<std::string> words = {"take", "poison", "flower"};
    EXPECT_EQ(StringUtils::join(words, " ", 1), "poison flower");
}

TEST(StringUtilsTest, JoinEmptyVector) {
    std::vector<std::string> words;
    EXPECT_EQ(StringUtils::join(words), "");
}
