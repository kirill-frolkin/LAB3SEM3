package stack

import (
	"encoding/gob"
	"encoding/json"
	"os"
)

func (s *Stack) toSlice() []string {
	res := make([]string, 0, s.size)
	for cur := s.head; cur != nil; cur = cur.Next {
		res = append(res, cur.Data)
	}
	return res
}

func (s *Stack) loadSlice(values []string) {
	s.Clear()
	// Восстанавливаем в обратном порядке, чтобы сохранить LIFO-вершину
	for i := len(values) - 1; i >= 0; i-- {
		s.Push(values[i])
	}
}

func (s *Stack) SaveToText(filename string) error {
	data, err := json.MarshalIndent(s.toSlice(), "", "  ")
	if err != nil {
		return err
	}
	return os.WriteFile(filename, data, 0644)
}

func (s *Stack) LoadFromText(filename string) error {
	data, err := os.ReadFile(filename)
	if err != nil {
		return err
	}
	var values []string
	if err := json.Unmarshal(data, &values); err != nil {
		return err
	}
	s.loadSlice(values)
	return nil
}

func (s *Stack) SaveToBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()
	return gob.NewEncoder(file).Encode(s.toSlice())
}

func (s *Stack) LoadFromBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var values []string
	if err := gob.NewDecoder(file).Decode(&values); err != nil {
		return err
	}
	s.loadSlice(values)
	return nil
}
