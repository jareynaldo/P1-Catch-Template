// #include <iostream>
// #include "catch/catch_amalgamated.hpp"
// #include "../src/AVL.h"
// #define CATCH_CONFIG_MAIN
//
// using namespace std;
//
// TEST_CASE("Invalid Commands") {
//     MyAVLTree tree;
//
//     REQUIRE_FALSE(tree.insert("Invalid123", "12345678"));
//     REQUIRE_FALSE(tree.insert("ValidName", "12345"));
//     REQUIRE_FALSE(tree.insert("ValidName", "123456789"));
//     REQUIRE(tree.insert("ValidName", "12345678"));
//     REQUIRE_FALSE(tree.insert("Duplicate", "12345678"));  // duplicate UFID
// }
//
// TEST_CASE("Edge Cases") {
//     MyAVLTree tree;
//
//     REQUIRE(tree.insert("mark rover", "12345678"));         // valid insert
//     REQUIRE_FALSE(tree.remove("87654321"));               // remove non-existent UFID
//     REQUIRE(tree.searchByID("99999999") == "");           // search for non-existent UFID
// }
//
// TEST_CASE("Rotations") {
//     MyAVLTree tree;
//
//     tree.insert("Third", "12345670");
//     tree.insert("Second", "12345679");
//     tree.insert("First", "12345678");
//     REQUIRE(tree.getLevelCount() == 2); // right rotation
//
//     tree.insert("fourth", "60000000");
//     tree.insert("fith", "70000000");
//     REQUIRE(tree.getLevelCount() == 3); // left rotation
//
//     tree.insert("sicth", "55000000");
//     REQUIRE(tree.getLevelCount() == 3); // left-right rotation
//
//     tree.insert("seventh", "75000000");
//     tree.insert("eight", "72000000");
//     REQUIRE(tree.getLevelCount() == 4); // right-left rotation
// }
//
// TEST_CASE("Deletion") {
//     MyAVLTree tree;
//
//     tree.insert("A", "50000000");
//     tree.insert("B", "40000000");
//     tree.insert("C", "30000000");
//     tree.insert("D", "20000000");
//     REQUIRE(tree.remove("20000000"));
//     REQUIRE(tree.searchByID("20000000") == "");
//     REQUIRE(tree.remove("30000000"));
//     REQUIRE(tree.searchByID("30000000") == "");
//
//     tree.insert("E", "60000000");
//     tree.insert("F", "55000000");
//     REQUIRE(tree.remove("50000000"));
//     REQUIRE(tree.searchByID("50000000") == "");
// }
//
// TEST_CASE("Large Insert and Remove") {
//     MyAVLTree tree;
//     std::vector<std::string> ufids;
//     std::string name = "Student";
//
//     for (int i = 10000000; i < 10100000; i += 1000) {
//         std::string ufid = std::to_string(i);
//         ufids.push_back(ufid);
//         REQUIRE(tree.insert(name, ufid));
//     }
//
//     std::vector<std::string> ufidsToRemove = {"10001000", "10005000", "10009000", "10007000", "10003000",
//                                               "10011000", "10013000", "10015000", "10017000", "10019000"};
//     for (const auto& ufid : ufidsToRemove) {
//         REQUIRE(tree.remove(ufid));
//     }
//
//     std::vector<std::string> ufidList;
//     tree.getInorderUFIDs(ufidList);
//     REQUIRE(ufidList.size() == 90);
// }