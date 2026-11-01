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
## Lab_2 - Classes, composition and aggregation

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

## Lab_3 - Часть 2: C++ умные указатели

Что сделано:
Playlist::m_tracks переведён с std::vector<Track*> на std::vector<std::weak_ptr>
Track::m_audioFile остаётся AudioFile по значению (композиция из ЛР2)

В main.cpp:
std::unique_ptr — один владелец, уничтожение при выходе из блока;
передача владения через std::move;
std::shared_ptr — use_count() растёт при копировании и падает при уничтожении копии;
std::weak_ptr — lock() работает, пока жив объект, и возвращает nullptr после уничтожения;
массивы: std::vector<std::unique_ptr> и std::vector<std::shared_ptr>

Чего в проекте нет:
ни одного 'new';
ни одного 'delete'.
Проверка: 'grep -rn "\bnew\b|\bdelete\b" src/ include/'

Как проверить
cmake -S . -B build
cmake --build build
./build/lab03            # Linux/macOS
.\build\Debug\lab03.exe  # Windows
