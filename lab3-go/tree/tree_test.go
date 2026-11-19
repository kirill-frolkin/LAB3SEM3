package tree

import (
	"os"
	"testing"
)

func TestCBT(t *testing.T) {
	tr := New()
	tr.PrintByLevels()
	if tr.Size() != 0 || tr.Find(10) || !tr.IsComplete() {
		t.Fatal("Empty tree checks failed")
	}

	tr.Insert(10)
	tr.Insert(20)
	tr.Insert(30)
	tr.Insert(40)
	if tr.Size() != 4 || !tr.Find(20) || !tr.Find(40) || tr.Find(99) || !tr.IsComplete() {
		t.Fatal("Tree operations failed")
	}
	tr.PrintByLevels()
}

func TestTreeSerialization(t *testing.T) {
	tr := New()
	tr.Insert(10)
	tr.Insert(20)
	tr.Insert(30)
	tr.Insert(40)

	if err := tr.SaveToText("tree.json"); err != nil {
		t.Fatalf("Text save error: %v", err)
	}
	defer os.Remove("tree.json")

	newTr := New()
	if err := newTr.LoadFromText("tree.json"); err != nil {
		t.Fatalf("Text load error: %v", err)
	}
	if newTr.Size() != 4 || !newTr.Find(40) || !newTr.IsComplete() {
		t.Fatal("Text tree round-trip failed")
	}

	if err := tr.SaveToBinary("tree.bin"); err != nil {
		t.Fatalf("Binary save error: %v", err)
	}
	defer os.Remove("tree.bin")

	newTrb := New()
	if err := newTrb.LoadFromBinary("tree.bin"); err != nil {
		t.Fatalf("Binary load error: %v", err)
	}
	if newTrb.Size() != 4 || !newTrb.Find(30) || !newTrb.IsComplete() {
		t.Fatal("Binary tree round-trip failed")
	}

	_ = newTr.LoadFromText("non_existent.json")
	_ = newTrb.LoadFromBinary("non_existent.bin")
}

func BenchmarkTreeInsert(b *testing.B) {
	for i := 0; i < b.N; i++ {
		tr := New()
		for j := 0; j < 256; j++ {
			tr.Insert(j)
		}
	}
}
