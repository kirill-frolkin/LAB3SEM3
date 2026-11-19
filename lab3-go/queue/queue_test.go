package queue

import (
	"os"
	"testing"
)

func TestQueueAll(t *testing.T) {
	q := New()
	q.Print()
	if !q.IsEmpty() {
		t.Fatal("Expected empty")
	}

	q.Push("A")
	q.Push("B")
	q.Push("C")
	q.Print()
	if q.Size() != 3 {
		t.Fatalf("Expected size 3, got %d", q.Size())
	}
	if v, ok := q.Front(); !ok || v != "A" {
		t.Fatalf("Unexpected front: %q, %v", v, ok)
	}

	q.Pop()
	q.Pop()
	q.Pop()
	q.Pop()
	if !q.IsEmpty() {
		t.Fatal("Expected empty")
	}
	if _, ok := q.Front(); ok {
		t.Fatal("Front on empty should fail")
	}
}

func TestQueueSerialization(t *testing.T) {
	q := New()
	q.Push("A")
	q.Push("B")

	if err := q.SaveToText("q.json"); err != nil {
		t.Fatalf("Text save error: %v", err)
	}
	defer os.Remove("q.json")

	newQ := New()
	if err := newQ.LoadFromText("q.json"); err != nil {
		t.Fatalf("Text load error: %v", err)
	}
	if front, ok := newQ.Front(); !ok || front != "A" {
		t.Fatalf("FIFO order broken after JSON load: got %q", front)
	}

	if err := q.SaveToBinary("q.bin"); err != nil {
		t.Fatalf("Binary save error: %v", err)
	}
	defer os.Remove("q.bin")

	newQb := New()
	if err := newQb.LoadFromBinary("q.bin"); err != nil {
		t.Fatalf("Binary load error: %v", err)
	}
	if front, ok := newQb.Front(); !ok || front != "A" {
		t.Fatalf("FIFO order broken after GOB load: got %q", front)
	}

	_ = newQ.LoadFromText("non_existent.json")
	_ = newQb.LoadFromBinary("non_existent.bin")
}

func BenchmarkQueuePush(b *testing.B) {
	for i := 0; i < b.N; i++ {
		q := New()
		for j := 0; j < 1000; j++ {
			q.Push("item")
		}
	}
}
