#include <benchmark/benchmark.h>
#include <string>

#include "DynamicArray.h"
#include "SinglyList.h"
#include "Stack.h"
#include "Queue.h"
#include "HashTable.h"
#include "CompleteBinaryTree.h"

static void BM_DynamicArray_PushBack(benchmark::State& state) {
    for (auto _ : state) {
        DynamicArray arr;
        for (int i = 0; i < state.range(0); ++i) {
            arr.pushBack("item");
        }
        benchmark::DoNotOptimize(arr.getSize());
    }
}
BENCHMARK(BM_DynamicArray_PushBack)->Range(1000, 64000);

static void BM_SinglyList_PushBack(benchmark::State& state) {
    for (auto _ : state) {
        SinglyList list;
        for (int i = 0; i < state.range(0); ++i) {
            list.pushBack("item");
        }
        benchmark::DoNotOptimize(list.getSize());
    }
}
BENCHMARK(BM_SinglyList_PushBack)->Range(1000, 64000);

static void BM_Stack_Push(benchmark::State& state) {
    for (auto _ : state) {
        Stack s;
        for (int i = 0; i < state.range(0); ++i) {
            s.push("item");
        }
        benchmark::DoNotOptimize(s.size());
    }
}
BENCHMARK(BM_Stack_Push)->Range(1000, 64000);

static void BM_Queue_Push(benchmark::State& state) {
    for (auto _ : state) {
        Queue q;
        for (int i = 0; i < state.range(0); ++i) {
            q.push("item");
        }
        benchmark::DoNotOptimize(q.size());
    }
}
BENCHMARK(BM_Queue_Push)->Range(1000, 64000);

static void BM_HashTable_Add(benchmark::State& state) {
    for (auto _ : state) {
        HashTable ht;
        for (int i = 0; i < state.range(0); ++i) {
            ht.add("key_" + std::to_string(i));
        }
        benchmark::DoNotOptimize(ht.size());
    }
}
BENCHMARK(BM_HashTable_Add)->Range(500, 8000);

static void BM_CompleteBinaryTree_Insert(benchmark::State& state) {
    for (auto _ : state) {
        CompleteBinaryTree tree;
        for (int i = 0; i < state.range(0); ++i) {
            tree.insert(i);
        }
        benchmark::DoNotOptimize(tree.size());
    }
}
BENCHMARK(BM_CompleteBinaryTree_Insert)->Range(256, 4096);

BENCHMARK_MAIN();
