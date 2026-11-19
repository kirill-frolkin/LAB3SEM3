package array

import (
	"encoding/gob"
	"encoding/json"
	"os"
)

type arrayPayload struct {
	Items []string `json:"items"`
}

func (a *DynamicArray) SaveToText(filename string) error {
	payload := arrayPayload{Items: a.items}
	data, err := json.MarshalIndent(payload, "", "  ")
	if err != nil {
		return err
	}
	return os.WriteFile(filename, data, 0644)
}

func (a *DynamicArray) LoadFromText(filename string) error {
	data, err := os.ReadFile(filename)
	if err != nil {
		return err
	}
	var payload arrayPayload
	if err := json.Unmarshal(data, &payload); err != nil {
		return err
	}
	a.items = payload.Items
	return nil
}

func (a *DynamicArray) SaveToBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	payload := arrayPayload{Items: a.items}
	return gob.NewEncoder(file).Encode(payload)
}

func (a *DynamicArray) LoadFromBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var payload arrayPayload
	if err := gob.NewDecoder(file).Decode(&payload); err != nil {
		return err
	}
	a.items = payload.Items
	return nil
}
