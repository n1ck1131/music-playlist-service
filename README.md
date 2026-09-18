# Сервис музыкальных плейлистов

**Тема курсового проекта:** Сервис музыкальных плейлистов с публикацией, подбором и воспроизведением аудио.

**Реализация:**
- Консольное ядро на C++
- Telegram-бот на Python

## Автор

- **ФИО:** Иванов Иван Иванович
- **Группа:** XX-11

## Структура репозитория
music-playlist-service/
├── cpp/ # Консольное ядро на C++
├── python/ # Telegram-бот
├── docs/ # Документация
├── .gitignore
└── README.md

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

