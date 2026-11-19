package hashtable

import "fmt"

const (
	TableSize = 1021
	HashBase  = 131
)

type Node struct {
	Key  string
	Next *Node
}

type HashTable struct {
	buckets [TableSize]*Node
	count   int
}

func New() *HashTable {
	return &HashTable{}
}

func hashString(s string) int {
	h := 0
	for i := 0; i < len(s); i++ {
		h = (h*HashBase + int(s[i])) % TableSize
	}
	return h
}

func (h *HashTable) Add(key string) {
	idx := hashString(key)
	for cur := h.buckets[idx]; cur != nil; cur = cur.Next {
		if cur.Key == key {
			return
		}
	}
	h.buckets[idx] = &Node{Key: key, Next: h.buckets[idx]}
	h.count++
}

func (h *HashTable) Remove(key string) {
	idx := hashString(key)
	var prev *Node
	for cur := h.buckets[idx]; cur != nil; prev, cur = cur, cur.Next {
		if cur.Key == key {
			if prev != nil {
				prev.Next = cur.Next
			} else {
				h.buckets[idx] = cur.Next
			}
			h.count--
			return
		}
	}
}

func (h *HashTable) Contains(key string) bool {
	idx := hashString(key)
	for cur := h.buckets[idx]; cur != nil; cur = cur.Next {
		if cur.Key == key {
			return true
		}
	}
	return false
}

func (h *HashTable) Clear() {
	h.buckets = [TableSize]*Node{}
	h.count = 0
}

func (h *HashTable) Size() int {
	return h.count
}

func (h *HashTable) Print() {
	fmt.Print("{")
	first := true
	for i := 0; i < TableSize; i++ {
		for cur := h.buckets[i]; cur != nil; cur = cur.Next {
			if !first {
				fmt.Print(", ")
			}
			fmt.Print(cur.Key)
			first = false
		}
	}
	fmt.Println("}")
}
