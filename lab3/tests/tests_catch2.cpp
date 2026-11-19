#include <catch2/catch_test_macros.hpp>
#include <cstdio>

#include "DynamicArray.h"
#include "SinglyList.h"
#include "DoublyList.h"
#include "Stack.h"
#include "Queue.h"
#include "HashTable.h"
#include "CompleteBinaryTree.h"
#include "Serializer.h"
#include "TextSerializer.h"

TEST_CASE("DynamicArray operations", "[array]") {
    DynamicArray arr(2);
    REQUIRE(arr.isEmpty());
    arr.pushBack("a");
    arr.pushBack("b");
    arr.pushBack("c");
    REQUIRE(arr.getSize() == 3);
    REQUIRE(arr.get(2) == "c");
    arr.popBack();
    REQUIRE(arr.getSize() == 2);
}

TEST_CASE("SinglyList and DoublyList", "[list]") {
    SinglyList sl;
    sl.pushBack("1");
    sl.pushBack("2");
    sl.popFront();
    REQUIRE(sl.getSize() == 1);
    REQUIRE(sl.find("2"));

    DoublyList dl;
    dl.pushFront("a");
    dl.pushBack("b");
    dl.popBack();
    REQUIRE(dl.getSize() == 1);
    REQUIRE(dl.find("a"));
}

TEST_CASE("Stack and Queue", "[adapters]") {
    Stack s;
    s.push("top1");
    s.push("top2");
    REQUIRE(s.peek() == "top2");
    s.pop();
    REQUIRE(s.peek() == "top1");

    Queue q;
    q.push("q1");
    q.push("q2");
    REQUIRE(q.front() == "q1");
    q.pop();
    REQUIRE(q.front() == "q2");
}

TEST_CASE("HashTable and CompleteBinaryTree", "[hash][tree]") {
    HashTable ht;
    ht.add("alpha");
    ht.add("beta");
    REQUIRE(ht.size() == 2);
    ht.remove("alpha");
    REQUIRE_FALSE(ht.contains("alpha"));

    CompleteBinaryTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    REQUIRE(tree.size() == 3);
    REQUIRE(tree.isComplete());
    REQUIRE(tree.find(20));
}

TEST_CASE("Serialization binary and text", "[serializer]") {
    DynamicArray arr;
    arr.pushBack("catch");
    arr.pushBack("two");
    REQUIRE(Serializer::saveBinary(arr, "catch_arr.bin"));
    DynamicArray loaded = Serializer::loadBinary("catch_arr.bin");
    std::remove("catch_arr.bin");
    REQUIRE(loaded.getSize() == 2);
    REQUIRE(loaded.get(0) == "catch");

    SinglyList list;
    list.pushBack("lineA");
    list.pushBack("lineB");
    REQUIRE(TextSerializer::saveText(list, "catch_list.txt"));
    SinglyList loadedList = TextSerializer::loadText("catch_list.txt");
    std::remove("catch_list.txt");
    REQUIRE(loadedList.getSize() == 2);
    REQUIRE(loadedList.get(1) == "lineB");
}
