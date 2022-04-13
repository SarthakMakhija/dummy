#include <iostream>
#include <gtest/gtest.h>
#include <benchmark/benchmark.h>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/make_persistent_array.hpp>


/**
int main() {

//    const char* filePath = "./tests.log";
//    PersistentMemoryPool::initialize(filePath);
//
//    SkipList* skipList = new SkipList(8, 0.5);
//    skipList -> put("HDD", "Hard disk drive");
//    skipList -> put("Pmem", "Persistent Memory");
//
//    std::cout << skipList -> get("HDD").first << std::endl;
//    std::cout << skipList -> get("Pmem").first << std::endl;
//    std::cout << skipList -> get("Unknown").first << std::endl;
//
//    remove(filePath);

    auto node = new SkipListInternalNode("", 10);

    std::string hdd = "HDD";
    auto putPositionHdd = node->putPositionOf(hdd.c_str(), 0.5);
    node->put(hdd.c_str(), putPositionHdd.positions, 4);

    std::string sdd = "SDD";
    auto putPositionSdd = node->putPositionOf(sdd.c_str(), 0.5);
    node->put(sdd.c_str(), putPositionSdd.positions, 3);

    std::cout << "HDD - " << node->getBy(hdd.c_str()).first << std::endl;
    std::cout << "SDD - " << node->getBy(sdd.c_str()).first << std::endl;

    std::string unknown = "unknown";
    std::cout << "Unknown - " << node->getBy("unknown").first << std::endl;
}
**/

struct Node {
    pmem::obj::p<int> id;
};

TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.

    auto ppp = pmem::obj::make_persistent<Node>();

    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}