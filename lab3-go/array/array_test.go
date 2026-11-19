package array

import (
	"os"
	"testing"
)

func TestDynamicArray(t *testing.T) {
	a := New(0)
	if a.Capacity() != 1 || a.Size() != 0 {
		t.Fatalf("unexpected initial cap/size: %d/%d", a.Capacity(), a.Size())
	}

	a.PushBack("first")
	a.PushBack("second")
	a.PushBack("third")
	if a.Size() != 3 || a.Get(1) != "second" {
		t.Fatal("PushBack/Get failed")
	}

	a.Set(1, "updated")
	if a.Get(1) != "updated" {
		t.Fatal("Set failed")
	}

	a.Set(-1, "bad")
	a.Set(10, "bad")
	if a.Get(-1) != "" || a.Get(10) != "" {
		t.Fatal("Out-of-bounds Get should return empty string")
	}
	a.RemoveAt(-1)
	a.RemoveAt(10)

	a.RemoveAt(1)
	if a.Size() != 2 || a.Get(1) != "third" {
		t.Fatal("RemoveAt failed")
	}

	a.Print()
	a.PopBack()
	a.Clear()
	a.PopBack()
	if a.Size() != 0 {
		t.Fatal("Expected empty array")
	}
}

func TestNewWithItem(t *testing.T) {
	a := NewWithItem(3, "x")
	if a.Size() != 3 || a.Get(2) != "x" {
		t.Fatalf("Expected 3 items of 'x', got size %d", a.Size())
	}
	b := NewWithItem(-5, "y")
	if b.Size() != 1 || b.Get(0) != "y" {
		t.Fatalf("Expected size 1, got %d", b.Size())
	}
}

func TestArraySerialization(t *testing.T) {
	da := New(4)
	da.PushBack("hello")
	da.PushBack("world")

	txtFile := "test_array.json"
	if err := da.SaveToText(txtFile); err != nil {
		t.Fatalf("Text save error: %v", err)
	}
	defer os.Remove(txtFile)

	loadedText := New(1)
	if err := loadedText.LoadFromText(txtFile); err != nil {
		t.Fatalf("Text load error: %v", err)
	}
	if loadedText.Size() != 2 || loadedText.Get(1) != "world" {
		t.Fatal("Text round-trip mismatch")
	}

	binFile := "test_array.bin"
	if err := da.SaveToBinary(binFile); err != nil {
		t.Fatalf("Binary save error: %v", err)
	}
	defer os.Remove(binFile)

	loadedBin := New(1)
	if err := loadedBin.LoadFromBinary(binFile); err != nil {
		t.Fatalf("Binary load error: %v", err)
	}
	if loadedBin.Size() != 2 || loadedBin.Get(0) != "hello" {
		t.Fatal("Binary round-trip mismatch")
	}

	if err := loadedText.LoadFromText("missing.json"); err == nil {
		t.Error("Expected error for missing JSON file")
	}
	if err := loadedBin.LoadFromBinary("missing.bin"); err == nil {
		t.Error("Expected error for missing GOB file")
	}
}

func BenchmarkDynamicArrayPushBack(b *testing.B) {
	for i := 0; i < b.N; i++ {
		a := New(8)
		for j := 0; j < 1000; j++ {
			a.PushBack("item")
		}
	}
}
