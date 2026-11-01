# Сервис музыкальных плейлистов

**Тема курсового проекта:** «Разработка сервиса музыкальных плейлистов»

**Реализация:**
- Консольное ядро на C++
- Telegram-бот на Python

## Автор

- ФИО: Лазарев Л.В.
- Группа: ПИ-51

## Структура репозитория
music-playlist-service/
--- cpp/ # Консольное ядро на C++
--- python/ # Telegram-бот
--- docs/ # Документация
--- .gitignore
--- README.md

## Сборка и запуск (планируется)

### C++

cd cpp
g++ -std=c++17 -Iinclude src/*.cpp -o app
./app
Python
bash

## Python
cd python
python -m venv .venv
.venv\Scripts\activate       # Windows
pip install -r requirements.txt
python -m bot.main

-----------------------------
## Lab 02 — Classes, composition and aggregation

Три класса предметной области:

- `AudioFile` — часть трека (композиция).
- `Track` — трек, владеет своим аудиофайлом.
- `Playlist` — агрегирует треки, созданные снаружи.

### Связи

- **Композиция**: `Track` → `AudioFile` (поле по значению). При уничтожении трека аудиофайл уничтожается автоматически.
- **Агрегация**: `Playlist` → `Track*` (указатели). Удаление плейлиста не удаляет треки.

### Сборка и запуск

cmake -S . -B build;
cmake --build build;
./build/lab02;

## Lab 03 — Part 2: C++ smart pointers

### Ownership

- `Track::m_audioFile` — `AudioFile` **by value** (composition, unchanged from Lab 02).
- `Playlist::m_tracks` — `std::vector<std::weak_ptr<Track>>` (aggregation, does not extend lifetime).
- In `main`:
  - `std::unique_ptr<Track>` — single owner, object destroyed at block exit;
  - `std::vector<std::shared_ptr<Track>>` — shared ownership, `use_count()` grows and shrinks;
  - `std::vector<std::unique_ptr<Track>>` — array of unique owners.

No `new` or `delete` remains in the project.

### Build & run

cmake -S . -B build;
cmake --build build;
./build/lab03;            # Linux / macOS
.\build\Debug\lab03.exe;  # Windows (Visual Studio generator)
