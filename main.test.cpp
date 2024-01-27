#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

extern void initialize_pop_repository();

TEST(PopTest, TestInitializePopRepository)
{

    std::filesystem::remove_all(".pop");

    initialize_pop_repository();

    ASSERT_TRUE(std::filesystem::exists(".pop"));

    ASSERT_TRUE(std::filesystem::exists(".pop/objects"));
    ASSERT_TRUE(std::filesystem::exists(".pop/refs/heads"));
    ASSERT_TRUE(std::filesystem::exists(".pop/refs/tags"));

    std::ifstream head_file(".pop/HEAD");
    std::string head_contents((std::istreambuf_iterator<char>(head_file)), std::istreambuf_iterator<char>());
    ASSERT_EQ(head_contents, "ref: refs/heads/master\n");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}