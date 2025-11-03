#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "RedBlackTree.h"
#include <algorithm>

using namespace std;

TEST_CASE("Basic Insertion", "[Insertion]") {
    RedBlackTree tree;
    tree.addInplace("5", {}, 0);
    tree.addInplace("4", {}, 0);
    tree.addInplace("6", {}, 0);

    REQUIRE(tree.getPostorder() == "4, 6, 5");
    tree.clear();

    // LL case
    tree.addInplace("5", {}, 0);
    tree.addInplace("4", {}, 0);
    tree.addInplace("6", {}, 0);
    tree.addInplace("3", {}, 0);
    tree.addInplace("2", {}, 0);

    REQUIRE(tree.getPostorder() == "2, 4, 3, 6, 5");
    tree.clear();

    // LR case
    tree.addInplace("5", {}, 0);
    tree.addInplace("4", {}, 0);
    tree.addInplace("6", {}, 0);
    tree.addInplace("2", {}, 0);
    tree.addInplace("3", {}, 0);

    REQUIRE(tree.getPostorder() == "2, 4, 3, 6, 5");
    tree.clear();

    // RR case
    tree.addInplace("5", {}, 0);
    tree.addInplace("4", {}, 0);
    tree.addInplace("6", {}, 0);
    tree.addInplace("7", {}, 0);
    tree.addInplace("8", {}, 0);

    REQUIRE(tree.getPostorder() == "4, 6, 8, 7, 5");
    tree.clear();

    // RL case
    tree.addInplace("5", {}, 0);
    tree.addInplace("4", {}, 0);
    tree.addInplace("6", {}, 0);
    tree.addInplace("8", {}, 0);
    tree.addInplace("7", {}, 0);

    REQUIRE(tree.getPostorder() == "4, 6, 8, 7, 5");
    tree.clear();

    // Mixed recoloring cascade
    tree.addInplace("d", {}, 0);
    tree.addInplace("b", {}, 0);
    tree.addInplace("f", {}, 0);
    tree.addInplace("a", {}, 0);
    tree.addInplace("c", {}, 0);
    tree.addInplace("e", {}, 0);
    tree.addInplace("g", {}, 0);
    REQUIRE(tree.getPostorder() == "a, c, b, e, g, f, d");
    tree.clear();

    // Deep recoloring + rotation (RL inside right subtree)
    tree.addInplace("a", {}, 0);
    tree.addInplace("b", {}, 0);
    tree.addInplace("c", {}, 0);
    tree.addInplace("d", {}, 0);
    tree.addInplace("e", {}, 0);  // triggers RR rotation at top
    tree.addInplace("cc", {}, 0); // string between "c" and "d"
    REQUIRE(tree.getPostorder() == "a, cc, c, e, d, b");
    tree.clear();

    // Nested LR (zig-zag left-heavy)
    tree.addInplace("m", {}, 0);
    tree.addInplace("h", {}, 0);
    tree.addInplace("j", {}, 0);
    tree.addInplace("i", {}, 0);
    tree.addInplace("k", {}, 0);
    REQUIRE(tree.getPostorder() == "i, h, k, m, j");
    tree.clear();

    // Nested RL (zig-zag right-heavy)
    tree.addInplace("m", {}, 0);
    tree.addInplace("r", {}, 0);
    tree.addInplace("p", {}, 0);
    tree.addInplace("q", {}, 0);
    tree.addInplace("s", {}, 0);
    REQUIRE(tree.getPostorder() == "m, q, s, r, p");
    tree.clear();

    // Broad recoloring cascade (forces recolor up the tree)
    tree.addInplace("e", {}, 0);
    tree.addInplace("c", {}, 0);
    tree.addInplace("g", {}, 0);
    tree.addInplace("b", {}, 0);
    tree.addInplace("d", {}, 0);
    tree.addInplace("f", {}, 0);
    tree.addInplace("h", {}, 0);
    tree.addInplace("a", {}, 0);
    tree.addInplace("bb", {}, 0); // lexicographically between b and c
    REQUIRE(tree.getPostorder() == "a, bb, b, d, c, f, h, g, e");
    tree.clear();
}

TEST_CASE("Autocomplete", "[Autocomplete]") {
    RedBlackTree tree;

    tree.addInplace("cat", {}, 0);
    tree.addInplace("category", {}, 0);
    tree.addInplace("capillary", {}, 0);
    tree.addInplace("catalog", {}, 0);
    tree.addInplace("bike", {}, 0);
    tree.addInplace("catalyst", {}, 0);

    vector<string> res = tree.getAutoCompleteEntries("cat");
    vector<string> comp = {"cat", "catalog", "catalyst", "category"};
    REQUIRE(res == comp);
}