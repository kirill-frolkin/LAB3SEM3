package stack

import (
	"os"
	"testing"
)

func TestStackAll(t *testing.T) {
	s := New()
	s.Print()
	if !s.IsEmpty() {
		t.Fatal("Expected empty")
	}

	s.Push("10")
	s.Push("20")
	s.Print()
	if s.Size() != 2 {
		t.Fatalf("Expected size 2, got %d", s.Size())
	}
	if v, ok := s.Peek(); !ok || v != "20" {
		t.Fatalf("Unexpected peek: %q, %v", v, ok)
	}

	s.Pop()
	s.Pop()
	s.Pop()
	if !s.IsEmpty() {
		t.Fatal("Expected empty after pops")
	}
	if _, ok := s.Peek(); ok {
		t.Fatal("Peek on empty should fail")
	}
}

func TestStackSerialization(t *testing.T) {
	s := New()
	s.Push("A")
	s.Push("B")

	if err := s.SaveToText("s.json"); err != nil {
		t.Fatalf("Text save error: %v", err)
	}
	defer os.Remove("s.json")

	newS := New()
	if err := newS.LoadFromText("s.json"); err != nil {
		t.Fatalf("Text load error: %v", err)
	}
	if top, ok := newS.Peek(); !ok || top != "B" {
		t.Fatalf("LIFO order broken after JSON load: got %q", top)
	}

	if err := s.SaveToBinary("s.bin"); err != nil {
		t.Fatalf("Binary save error: %v", err)
	}
	defer os.Remove("s.bin")

	newSb := New()
	if err := newSb.LoadFromBinary("s.bin"); err != nil {
		t.Fatalf("Binary load error: %v", err)
	}
	if top, ok := newSb.Peek(); !ok || top != "B" {
		t.Fatalf("LIFO order broken after GOB load: got %q", top)
	}

	_ = newS.LoadFromText("non_existent.json")
	_ = newSb.LoadFromBinary("non_existent.bin")
}

func BenchmarkStackPush(b *testing.B) {
	for i := 0; i < b.N; i++ {
		s := New()
		for j := 0; j < 1000; j++ {
			s.Push("item")
		}
	}
}
