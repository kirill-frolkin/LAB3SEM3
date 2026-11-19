package hashtable

import (
	"fmt"
	"os"
	"testing"
)

func TestHashTableAll(t *testing.T) {
	h := New()
	if h.Size() != 0 {
		t.Fatal("Expected size 0")
	}

	h.Add("apple")
	h.Add("banana")
	h.Add("cherry")
	h.Add("apple")
	if h.Size() != 3 || !h.Contains("apple") || h.Contains("grape") {
		t.Fatal("Add/Contains failed")
	}

	h.Remove("banana")
	h.Remove("missing")
	if h.Size() != 2 || h.Contains("banana") {
		t.Fatal("Remove failed")
	}
	h.Print()
	h.Clear()
	if h.Size() != 0 {
		t.Fatal("Clear failed")
	}
}

func TestHashTableSerialization(t *testing.T) {
	h := New()
	h.Add("apple")
	h.Add("banana")

	if err := h.SaveToText("ht.json"); err != nil {
		t.Fatalf("Text save error: %v", err)
	}
	defer os.Remove("ht.json")

	newH := New()
	if err := newH.LoadFromText("ht.json"); err != nil {
		t.Fatalf("Text load error: %v", err)
	}
	if newH.Size() != 2 || !newH.Contains("apple") {
		t.Fatal("Text round-trip failed")
	}

	if err := h.SaveToBinary("ht.bin"); err != nil {
		t.Fatalf("Binary save error: %v", err)
	}
	defer os.Remove("ht.bin")

	newHb := New()
	if err := newHb.LoadFromBinary("ht.bin"); err != nil {
		t.Fatalf("Binary load error: %v", err)
	}
	if newHb.Size() != 2 || !newHb.Contains("banana") {
		t.Fatal("Binary round-trip failed")
	}

	_ = newH.LoadFromText("non_existent.json")
	_ = newHb.LoadFromBinary("non_existent.bin")
}

func BenchmarkHashTableAdd(b *testing.B) {
	keys := make([]string, 500)
	for i := range keys {
		keys[i] = fmt.Sprintf("key_%d", i)
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		h := New()
		for _, k := range keys {
			h.Add(k)
		}
	}
}
