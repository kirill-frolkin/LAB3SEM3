package tree

import (
	"encoding/gob"
	"encoding/json"
	"os"
)

// Обход по уровням (BFS), чтобы при повторной вставке сохранилась точная топология дерева
func (t *CompleteBinaryTree) toLevelOrderSlice() []int {
	if t.root == nil {
		return nil
	}
	res := make([]int, 0, t.size)
	queue := []*TreeNode{t.root}
	for len(queue) > 0 {
		cur := queue[0]
		queue = queue[1:]
		res = append(res, cur.Data)
		if cur.Left != nil {
			queue = append(queue, cur.Left)
		}
		if cur.Right != nil {
			queue = append(queue, cur.Right)
		}
	}
	return res
}

func (t *CompleteBinaryTree) SaveToText(filename string) error {
	data, err := json.MarshalIndent(t.toLevelOrderSlice(), "", "  ")
	if err != nil {
		return err
	}
	return os.WriteFile(filename, data, 0644)
}

func (t *CompleteBinaryTree) LoadFromText(filename string) error {
	data, err := os.ReadFile(filename)
	if err != nil {
		return err
	}
	var values []int
	if err := json.Unmarshal(data, &values); err != nil {
		return err
	}
	t.Clear()
	for _, v := range values {
		t.Insert(v)
	}
	return nil
}

func (t *CompleteBinaryTree) SaveToBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()
	return gob.NewEncoder(file).Encode(t.toLevelOrderSlice())
}

func (t *CompleteBinaryTree) LoadFromBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var values []int
	if err := gob.NewDecoder(file).Decode(&values); err != nil {
		return err
	}
	t.Clear()
	for _, v := range values {
		t.Insert(v)
	}
	return nil
}
