#include <gtest/gtest.h>
#include <cstdio>
#include <fstream>
#include <sstream>

#include "DynamicArray.h"
#include "SinglyList.h"
#include "DoublyList.h"
#include "Stack.h"
#include "Queue.h"
#include "HashTable.h"
#include "CompleteBinaryTree.h"
#include "Serializer.h"
#include "TextSerializer.h"

// ===== DynamicArray =====
TEST(DynamicArrayTest, InitiallyEmptyAndCapacity) {
    DynamicArray arr;
    EXPECT_TRUE(arr.isEmpty());
    EXPECT_EQ(arr.getSize(), 0);
    EXPECT_EQ(arr.getCapacity(), 8);

    DynamicArray minArr(0);
    EXPECT_EQ(minArr.getCapacity(), 1);
}

TEST(DynamicArrayTest, PushSetRemovePop) {
    DynamicArray arr(2);
    arr.pushBack("alpha");
    arr.pushBack("beta");
    arr.pushBack("gamma");
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_GE(arr.getCapacity(), 4);
    EXPECT_EQ(arr.get(0), "alpha");
    EXPECT_EQ(arr.get(2), "gamma");

    arr.set(1, "BETA");
    EXPECT_EQ(arr.get(1), "BETA");

    arr.removeAt(1);
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr.get(1), "gamma");

    arr.popBack();
    EXPECT_EQ(arr.getSize(), 1);
    arr.clear();
    EXPECT_TRUE(arr.isEmpty());
    arr.popBack();
    EXPECT_EQ(arr.getSize(), 0);
}

TEST(DynamicArrayTest, OutOfBoundsAndPrint) {
    DynamicArray arr;
    EXPECT_EQ(arr.get(-1), "");
    EXPECT_EQ(arr.get(50), "");
    arr.set(-1, "x");
    arr.set(50, "x");
    arr.removeAt(-1);
    arr.removeAt(50);

    std::ostringstream oss;
    arr.print(oss);
    EXPECT_EQ(oss.str(), "[]\n");

    arr.pushBack("A");
    arr.pushBack("B");
    oss.str("");
    arr.print(oss);
    EXPECT_EQ(oss.str(), "[A, B]\n");
}

TEST(DynamicArrayTest, MoveAndReuseAfterMove) {
    DynamicArray arr1(2);
    for (int i = 0; i < 10; ++i) {
        arr1.pushBack("item_" + std::to_string(i));
    }
    DynamicArray arr2(std::move(arr1));
    EXPECT_EQ(arr2.getSize(), 10);
    EXPECT_EQ(arr1.getSize(), 0);

    // Повторное использование перемещённого массива
    arr1.pushBack("after_move");
    EXPECT_EQ(arr1.getSize(), 1);
    EXPECT_EQ(arr1.get(0), "after_move");

    DynamicArray arr3;
    arr3 = std::move(arr2);
    EXPECT_EQ(arr3.getSize(), 10);
    EXPECT_EQ(arr2.getSize(), 0);
}

// ===== SinglyList =====
TEST(SinglyListTest, OperationsAndMove) {
    SinglyList list;
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.get(0), "");
    list.popFront();
    list.popBack();
    list.remove("none");

    std::ostringstream oss;
    list.print(oss);
    EXPECT_FALSE(oss.str().empty());

    list.pushFront("b");
    list.pushFront("a");
    list.pushBack("c");
    list.pushBack("d");
    EXPECT_EQ(list.getSize(), 4);
    EXPECT_EQ(list.get(0), "a");
    EXPECT_EQ(list.get(3), "d");
    EXPECT_EQ(list.get(-1), "");
    EXPECT_EQ(list.get(99), "");
    EXPECT_TRUE(list.find("c"));
    EXPECT_FALSE(list.find("z"));

    oss.str("");
    list.print(oss);
    EXPECT_EQ(oss.str(), "a -> b -> c -> d -> NULL\n");

    list.remove("a");
    list.remove("d");
    list.remove("c");
    EXPECT_EQ(list.getSize(), 1);
    list.popBack();
    EXPECT_TRUE(list.isEmpty());

    list.pushBack("x");
    list.pushBack("y");
    SinglyList moved(std::move(list));
    EXPECT_EQ(moved.getSize(), 2);
    EXPECT_TRUE(list.isEmpty());

    SinglyList assigned;
    assigned = std::move(moved);
    EXPECT_EQ(assigned.getSize(), 2);
    assigned.popFront();
    assigned.popFront();
    EXPECT_TRUE(assigned.isEmpty());
}

// ===== DoublyList =====
TEST(DoublyListTest, OperationsAndMove) {
    DoublyList list;
    EXPECT_TRUE(list.isEmpty());
    list.popFront();
    list.popBack();
    list.remove("missing");

    list.pushBack("b");
    list.pushFront("a");
    list.pushBack("c");
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_TRUE(list.find("a"));
    EXPECT_TRUE(list.find("c"));
    EXPECT_FALSE(list.find("z"));

    std::ostringstream fwd, bwd;
    list.printForward(fwd);
    list.printBackward(bwd);
    EXPECT_EQ(fwd.str(), "a b c \n");
    EXPECT_EQ(bwd.str(), "c b a \n");

    list.remove("b");
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_FALSE(list.find("b"));
    list.remove("a");
    list.remove("c");
    EXPECT_TRUE(list.isEmpty());

    list.pushBack("1");
    list.pushBack("2");
    DoublyList moved(std::move(list));
    EXPECT_EQ(moved.getSize(), 2);
    moved.popFront();
    moved.popBack();
    EXPECT_TRUE(moved.isEmpty());
}

// ===== Stack =====
TEST(StackTest, LIFOAndMove) {
    Stack s;
    EXPECT_TRUE(s.isEmpty());
    EXPECT_EQ(s.peek(), "");
    s.pop();

    s.push("10");
    s.push("20");
    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s.peek(), "20");

    Stack moved(std::move(s));
    EXPECT_TRUE(s.isEmpty());
    EXPECT_EQ(moved.size(), 2);

    moved.pop();
    EXPECT_EQ(moved.peek(), "10");
    moved.clear();
    EXPECT_TRUE(moved.isEmpty());
}

// ===== Queue =====
TEST(QueueTest, FIFOAndMove) {
    Queue q;
    EXPECT_TRUE(q.isEmpty());
    EXPECT_EQ(q.front(), "");
    q.pop();

    q.push("10");
    q.push("20");
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.front(), "10");

    Queue moved(std::move(q));
    EXPECT_TRUE(q.isEmpty());
    EXPECT_EQ(moved.size(), 2);

    moved.pop();
    EXPECT_EQ(moved.front(), "20");
    moved.pop();
    EXPECT_TRUE(moved.isEmpty());
}

// ===== HashTable =====
TEST(HashTableTest, AddContainsRemoveClear) {
    HashTable ht;
    EXPECT_TRUE(ht.isEmpty());
    EXPECT_FALSE(ht.contains("apple"));

    ht.add("apple");
    ht.add("banana");
    ht.add("apple");
    EXPECT_EQ(ht.size(), 2);
    EXPECT_TRUE(ht.contains("apple"));
    EXPECT_TRUE(ht.contains("banana"));

    ht.remove("apple");
    EXPECT_EQ(ht.size(), 1);
    EXPECT_FALSE(ht.contains("apple"));
    ht.remove("missing");
    ht.clear();
    EXPECT_TRUE(ht.isEmpty());
}

// ===== CompleteBinaryTree =====
TEST(CBTTest, InsertFindComplete) {
    CompleteBinaryTree tree;
    EXPECT_TRUE(tree.isEmpty());
    EXPECT_FALSE(tree.find(10));
    EXPECT_TRUE(tree.isComplete());

    for (int i = 1; i <= 7; ++i) {
        tree.insert(i * 10);
    }
    EXPECT_EQ(tree.size(), 7);
    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(70));
    EXPECT_FALSE(tree.find(999));
    EXPECT_TRUE(tree.isComplete());

    tree.clear();
    EXPECT_TRUE(tree.isEmpty());
}

// ===== Serialization =====
TEST(SerializationTest, BinaryDynamicArray) {
    DynamicArray arr;
    arr.pushBack("10");
    arr.pushBack("");
    arr.pushBack("hello world");

    const std::string path = "test_arr_gtest.bin";
    EXPECT_TRUE(Serializer::saveBinary(arr, path));
    DynamicArray loaded = Serializer::loadBinary(path);
    std::remove(path.c_str());

    EXPECT_EQ(loaded.getSize(), 3);
    EXPECT_EQ(loaded.get(0), "10");
    EXPECT_EQ(loaded.get(1), "");
    EXPECT_EQ(loaded.get(2), "hello world");

    DynamicArray missing = Serializer::loadBinary("non_existent_file.bin");
    EXPECT_TRUE(missing.isEmpty());

    // Проверка обрезанного файла
    const std::string badPath = "test_corrupt.bin";
    {
        std::ofstream bad(badPath, std::ios::binary);
        int fakeCount = 5;
        bad.write(reinterpret_cast<const char*>(&fakeCount), sizeof(fakeCount));
    }
    DynamicArray corrupt = Serializer::loadBinary(badPath);
    std::remove(badPath.c_str());
    EXPECT_TRUE(corrupt.isEmpty());
}

TEST(SerializationTest, TextSinglyListWithEscaping) {
    SinglyList list;
    list.pushBack("alpha");
    list.pushBack("line1\nline2");
    list.pushBack("path\\to\\file");

    const std::string path = "test_list_gtest.txt";
    EXPECT_TRUE(TextSerializer::saveText(list, path));
    SinglyList loaded = TextSerializer::loadText(path);
    std::remove(path.c_str());

    EXPECT_EQ(loaded.getSize(), 3);
    EXPECT_EQ(loaded.get(0), "alpha");
    EXPECT_EQ(loaded.get(1), "line1\nline2");
    EXPECT_EQ(loaded.get(2), "path\\to\\file");

    SinglyList missing = TextSerializer::loadText("non_existent_file.txt");
    EXPECT_TRUE(missing.isEmpty());
}
