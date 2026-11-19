package array

import "fmt"

type DynamicArray struct {
	items []string
}

func New(initialCapacity int) *DynamicArray {
	if initialCapacity < 1 {
		initialCapacity = 1
	}
	return &DynamicArray{items: make([]string, 0, initialCapacity)}
}

func NewWithItem(initialCapacity int, item string) *DynamicArray {
	if initialCapacity < 1 {
		initialCapacity = 1
	}
	items := make([]string, initialCapacity)
	for i := range items {
		items[i] = item
	}
	return &DynamicArray{items: items}
}

func (a *DynamicArray) PushBack(value string) {
	a.items = append(a.items, value)
}

func (a *DynamicArray) PopBack() {
	if len(a.items) > 0 {
		a.items = a.items[:len(a.items)-1]
	}
}

func (a *DynamicArray) Get(index int) string {
	if index < 0 || index >= len(a.items) {
		return ""
	}
	return a.items[index]
}

func (a *DynamicArray) Set(index int, value string) {
	if index < 0 || index >= len(a.items) {
		return
	}
	a.items[index] = value
}

func (a *DynamicArray) RemoveAt(index int) {
	if index < 0 || index >= len(a.items) {
		return
	}
	a.items = append(a.items[:index], a.items[index+1:]...)
}

func (a *DynamicArray) Clear() {
	a.items = a.items[:0]
}

func (a *DynamicArray) Size() int {
	return len(a.items)
}

func (a *DynamicArray) Capacity() int {
	return cap(a.items)
}

func (a *DynamicArray) Print() {
	fmt.Print("[")
	for i, v := range a.items {
		fmt.Print(v)
		if i < len(a.items)-1 {
			fmt.Print(", ")
		}
	}
	fmt.Println("]")
}
