package doublelinkedlist

import (
	"os"
	"testing"
)

func TestDoubleLinkedListAll(t *testing.T) {
	l := New()
	l.PrintForward()
	l.PrintBackward()
	l.PopFront()
	l.PopBack()

	l.PushBack("A")
	l.PushBack("B")
	l.PushFront("C")
	if l.Size() != 3 {
		t.Fatalf("Expected size 3, got %d", l.Size())
	}

	l.PrintForward()
	l.PrintBackward()

	l.RemoveValue("X")
	l.RemoveValue("A")
	l.RemoveValue("C")
	l.RemoveValue("B")
	if l.Size() != 0 {
		t.Fatal("Expected empty list")
	}

	l.PushBack("E")
	l.PushFront("F")
	l.PopFront()
	l.PopBack()
	if l.Size() != 0 {
		t.Fatal("Expected size 0")
	}
}

func TestDoubleLinkedListSerialization(t *testing.T) {
	l := New()
	l.PushBack("A")
	l.PushBack("B")

	if err := l.SaveToText("dl.json"); err != nil {
		t.Fatalf("Text save error: %v", err)
	}
	defer os.Remove("dl.json")

	newL := New()
	if err := newL.LoadFromText("dl.json"); err != nil {
		t.Fatalf("Text load error: %v", err)
	}
	if newL.Size() != 2 {
		t.Fatalf("Expected size 2, got %d", newL.Size())
	}

	if err := l.SaveToBinary("dl.bin"); err != nil {
		t.Fatalf("Binary save error: %v", err)
	}
	defer os.Remove("dl.bin")

	newLb := New()
	if err := newLb.LoadFromBinary("dl.bin"); err != nil {
		t.Fatalf("Binary load error: %v", err)
	}
	if newLb.Size() != 2 {
		t.Fatalf("Expected size 2, got %d", newLb.Size())
	}

	_ = newL.LoadFromText("non_existent.json")
	_ = newLb.LoadFromBinary("non_existent.bin")
}

func BenchmarkDoubleLinkedListPushBack(b *testing.B) {
	for i := 0; i < b.N; i++ {
		l := New()
		for j := 0; j < 1000; j++ {
			l.PushBack("item")
		}
	}
}
