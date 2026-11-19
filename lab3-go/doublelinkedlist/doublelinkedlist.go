package doublelinkedlist

import "fmt"

type Node struct {
	Data string
	Prev *Node
	Next *Node
}

type DoubleLinkedList struct {
	head *Node
	tail *Node
	size int
}

func New() *DoubleLinkedList {
	return &DoubleLinkedList{}
}

func (l *DoubleLinkedList) PushFront(value string) {
	node := &Node{Data: value, Next: l.head}
	if l.head != nil {
		l.head.Prev = node
	} else {
		l.tail = node
	}
	l.head = node
	l.size++
}

func (l *DoubleLinkedList) PushBack(value string) {
	node := &Node{Data: value, Prev: l.tail}
	if l.tail != nil {
		l.tail.Next = node
	} else {
		l.head = node
	}
	l.tail = node
	l.size++
}

func (l *DoubleLinkedList) PopFront() {
	if l.head == nil {
		return
	}
	l.head = l.head.Next
	if l.head != nil {
		l.head.Prev = nil
	} else {
		l.tail = nil
	}
	l.size--
}

func (l *DoubleLinkedList) PopBack() {
	if l.tail == nil {
		return
	}
	l.tail = l.tail.Prev
	if l.tail != nil {
		l.tail.Next = nil
	} else {
		l.head = nil
	}
	l.size--
}

func (l *DoubleLinkedList) Find(value string) *Node {
	for cur := l.head; cur != nil; cur = cur.Next {
		if cur.Data == value {
			return cur
		}
	}
	return nil
}

func (l *DoubleLinkedList) RemoveValue(value string) {
	node := l.Find(value)
	if node == nil {
		return
	}
	if node == l.head {
		l.PopFront()
		return
	}
	if node == l.tail {
		l.PopBack()
		return
	}
	node.Prev.Next = node.Next
	node.Next.Prev = node.Prev
	l.size--
}

func (l *DoubleLinkedList) Clear() {
	l.head = nil
	l.tail = nil
	l.size = 0
}

func (l *DoubleLinkedList) Size() int {
	return l.size
}

func (l *DoubleLinkedList) PrintForward() {
	if l.head == nil {
		fmt.Println("список пуст")
		return
	}
	fmt.Print("NULL <- ")
	for cur := l.head; cur != nil; cur = cur.Next {
		fmt.Print(cur.Data)
		if cur.Next != nil {
			fmt.Print(" <-> ")
		}
	}
	fmt.Println(" -> NULL")
}

func (l *DoubleLinkedList) PrintBackward() {
	if l.tail == nil {
		fmt.Println("список пуст")
		return
	}
	fmt.Print("NULL <- ")
	for cur := l.tail; cur != nil; cur = cur.Prev {
		fmt.Print(cur.Data)
		if cur.Prev != nil {
			fmt.Print(" <-> ")
		}
	}
	fmt.Println(" -> NULL")
}
