package linkedlist

import (
	"os"
	"testing"
)

func TestLinkedListAll(t *testing.T) {
	l := New()
	l.Print()
	l.RemoveValue("none")
	l.PopFront()
	l.PopBack()

	l.PushFront("A")
	l.PushBack("B")
	l.PushBack("C")
	l.PushFront("D")
	l.Print()

	if l.Size() != 4 || l.Find("B") == nil || l.Find("X") != nil {
		t.Fatal("Basic list operations failed")
	}

	l.RemoveValue("A")
	l.RemoveValue("D")
	l.RemoveValue("C")
	l.RemoveValue("X")
	l.RemoveValue("B")
	if l.Size() != 0 {
		t.Fatalf("Expected empty list, got %d", l.Size())
	}

	l.PushBack("Z")
	l.PopBack()
	l.PushBack("Y")
	l.PushBack("W")
	l.PopBack()
	l.PopFront()
	if l.Size() != 0 {
		t.Fatal("Expected empty after pops")
	}
}

func TestLinkedListSerialization(t *testing.T) {
	l := New()
	l.PushBack("A")
	l.PushBack("B")

	if err := l.SaveToText("l.json"); err != nil {
		t.Fatalf("Text save error: %v", err)
	}
	defer os.Remove("l.json")

	newL := New()
	newL.PushBack("old")
	if err := newL.LoadFromText("l.json"); err != nil {
		t.Fatalf("Text load error: %v", err)
	}
	if newL.Size() != 2 || newL.Find("B") == nil {
		t.Fatal("Text load mismatch")
	}

	if err := l.SaveToBinary("l.bin"); err != nil {
		t.Fatalf("Binary save error: %v", err)
	}
	defer os.Remove("l.bin")

	newLb := New()
	if err := newLb.LoadFromBinary("l.bin"); err != nil {
		t.Fatalf("Binary load error: %v", err)
	}
	if newLb.Size() != 2 || newLb.Find("A") == nil {
		t.Fatal("Binary load mismatch")
	}

	_ = newL.LoadFromText("non_existent.json")
	_ = newLb.LoadFromBinary("non_existent.bin")
}

func BenchmarkLinkedListPushBack(b *testing.B) {
	for i := 0; i < b.N; i++ {
		l := New()
		for j := 0; j < 1000; j++ {
			l.PushBack("item")
		}
	}
}
