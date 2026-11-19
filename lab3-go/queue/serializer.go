package queue

import (
	"encoding/gob"
	"encoding/json"
	"os"
)

func (q *Queue) toSlice() []string {
	res := make([]string, 0, q.size)
	for cur := q.head; cur != nil; cur = cur.Next {
		res = append(res, cur.Data)
	}
	return res
}

func (q *Queue) SaveToText(filename string) error {
	data, err := json.MarshalIndent(q.toSlice(), "", "  ")
	if err != nil {
		return err
	}
	return os.WriteFile(filename, data, 0644)
}

func (q *Queue) LoadFromText(filename string) error {
	data, err := os.ReadFile(filename)
	if err != nil {
		return err
	}
	var values []string
	if err := json.Unmarshal(data, &values); err != nil {
		return err
	}
	q.Clear()
	for _, v := range values {
		q.Push(v)
	}
	return nil
}

func (q *Queue) SaveToBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()
	return gob.NewEncoder(file).Encode(q.toSlice())
}

func (q *Queue) LoadFromBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var values []string
	if err := gob.NewDecoder(file).Decode(&values); err != nil {
		return err
	}
	q.Clear()
	for _, v := range values {
		q.Push(v)
	}
	return nil
}
