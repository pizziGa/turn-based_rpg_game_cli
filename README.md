# CLI Turn-Based RPG (C)

A tiny, text-based turn-based RPG I wrote in C to pass the time.  
It’s simple: fight one enemy. Either you win… or you don’t. Then the game closes.

---

## 🎮 Features
- **Turn-based combat** — You attack, they attack, repeat until someone’s HP hits zero.
- **Basic RPG stats** — Health points, attack power, defense and healing.
- **Runs in your terminal** — No graphics, no distractions, just pure combat.

---

## ⚠️ Disclaimer
Currently:
- There’s only **one** enemy.
- When you or the enemy wins, the game **immediately ends**.
- No restarts, no high scores, no loot — just glory (or defeat).

This is more of a “first round demo” than a full game.

---

## 📦 Requirements
- A C compiler (e.g., `gcc` or `clang`)
- A terminal/command line

---

## 🛠️ How to Build
```bash
# Clone this repository
git clone https://github.com/pizziGa/turn-based_rpg_game_cli.git
cd turn-based_rpg_game_cli

# Compile the game
gcc -o game main.c

# Run it
./game
