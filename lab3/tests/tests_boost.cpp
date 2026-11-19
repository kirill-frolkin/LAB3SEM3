#define BOOST_TEST_MODULE Lab3BoostTests
#include <boost/test/included/unit_test.hpp>
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

BOOST_AUTO_TEST_CASE(DynamicArray_Basic) {
    DynamicArray arr(2);
    BOOST_CHECK(arr.isEmpty());
    arr.pushBack("one");
    arr.pushBack("two");
    arr.pushBack("three");
    BOOST_CHECK_EQUAL(arr.getSize(), 3);
    BOOST_CHECK_EQUAL(arr.get(1), "two");
    arr.set(1, "TWO");
    BOOST_CHECK_EQUAL(arr.get(1), "TWO");
    arr.removeAt(0);
    BOOST_CHECK_EQUAL(arr.getSize(), 2);
    BOOST_CHECK_EQUAL(arr.get(0), "TWO");
}

BOOST_AUTO_TEST_CASE(SinglyList_Basic) {
    SinglyList list;
    list.pushBack("a");
    list.pushFront("start");
    list.pushBack("end");
    BOOST_CHECK_EQUAL(list.getSize(), 3);
    BOOST_CHECK(list.find("a"));
    list.remove("a");
    BOOST_CHECK(!list.find("a"));
    BOOST_CHECK_EQUAL(list.getSize(), 2);
}

BOOST_AUTO_TEST_CASE(DoublyList_Basic) {
    DoublyList list;
    list.pushFront("first");
    list.pushBack("second");
    list.pushBack("third");
    BOOST_CHECK_EQUAL(list.getSize(), 3);
    list.remove("second");
    BOOST_CHECK_EQUAL(list.getSize(), 2);
    BOOST_CHECK(!list.find("second"));
}

BOOST_AUTO_TEST_CASE(Stack_And_Queue) {
    Stack s;
    s.push("1");
    s.push("2");
    BOOST_CHECK_EQUAL(s.peek(), "2");
    s.pop();
    BOOST_CHECK_EQUAL(s.peek(), "1");

    Queue q;
    q.push("first");
    q.push("second");
    BOOST_CHECK_EQUAL(q.front(), "first");
    q.pop();
    BOOST_CHECK_EQUAL(q.front(), "second");
}

BOOST_AUTO_TEST_CASE(HashTable_And_Tree) {
    HashTable ht;
    ht.add("key1");
    ht.add("key2");
    ht.add("key1");
    BOOST_CHECK_EQUAL(ht.size(), 2);
    BOOST_CHECK(ht.contains("key2"));
    ht.remove("key1");
    BOOST_CHECK(!ht.contains("key1"));

    CompleteBinaryTree tree;
    for (int i = 1; i <= 5; ++i) {
        tree.insert(i);
    }
    BOOST_CHECK_EQUAL(tree.size(), 5);
    BOOST_CHECK(tree.find(4));
    BOOST_CHECK(!tree.find(99));
    BOOST_CHECK(tree.isComplete());
}

BOOST_AUTO_TEST_CASE(Serialization_RoundTrip) {
    DynamicArray arr;
    arr.pushBack("hello");
    arr.pushBack("boost");
    BOOST_REQUIRE(Serializer::saveBinary(arr, "boost_arr.bin"));
    DynamicArray loadedArr = Serializer::loadBinary("boost_arr.bin");
    std::remove("boost_arr.bin");
    BOOST_CHECK_EQUAL(loadedArr.getSize(), 2);
    BOOST_CHECK_EQUAL(loadedArr.get(1), "boost");

    SinglyList list;
    list.pushBack("x");
    list.pushBack("y\nz");
    BOOST_REQUIRE(TextSerializer::saveText(list, "boost_list.txt"));
    SinglyList loadedList = TextSerializer::loadText("boost_list.txt");
    std::remove("boost_list.txt");
    BOOST_CHECK_EQUAL(loadedList.getSize(), 2);
    BOOST_CHECK_EQUAL(loadedList.get(1), "y\nz");
}
