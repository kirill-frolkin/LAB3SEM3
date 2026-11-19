

# Структура проекта
- `lab3/` — многофайловый проект C++17 (`include/*.h`, `src/*.cpp`, `tests/`, `bench/`, `CMakeLists.txt`, `uml.puml`).
- `lab3-go/` — проект Go (`go.mod` и 7 пакетов: `array`, `linkedlist`, `doublelinkedlist`, `stack`, `queue`, `hashtable`, `tree`).
- `Makefile` — цели для сборки, тестов, бенчмарков, покрытия и линтеров.

## Основные команды
```bash
# Сборка и запуск тестов (C++ Google Test + Go testing)
make test

# Дополнительные тестовые фреймворки C++ (Boost.Test, Catch2)
make cpp-boost && ./lab3/build/run_boost
make cpp-catch2 && ./lab3/build/run_catch2

# Бенчмарки (C++ Google Benchmark + Go testing.B)
make bench

# HTML-отчёты о покрытии (lcov/genhtml для C++, go tool cover для Go)
make coverage

# Проверка линтерами (cppcheck + go vet)
make lint
```
