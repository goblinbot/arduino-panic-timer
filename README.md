# Panic Timer
An Arduino based minigame for escape-rooms & hobby player-vs-player events.

## disclaimer
This minigame is about "defusing a fake bomb in time". This project does not involve or relate actual dangerous/harmful devices, nor encourage anything of the sort.

## The project

Live Demo: https://wokwi.com/projects/336510517582496340

A simple Arduino Nano project, using multiple smaller push buttons, single larger push button, buzzer and a bright red LED.

Originally built as an objective for a 5v5 airsoft event. Starting a game starts a (250ms tick based) countdown based on pre-defined gametimes (current default: 10 minutes) in which one team defends the prop, while the opposing team tries to defuse the timer by holding the defuse button for 10 seconds.

If the timer runs out, defending team wins while a distorted tune plays! If defused, opposing team wins with a much gentler tune.

### Current diagram

<adding picture soon>

### Version 1.0

Features:
- Pre-defined game rounds (5, 10, 15, 20 minutes countdown)
- Start/Stop button (starts and exits a game round, playing the E1M1 doom Riff or a custom tune)
- Toggle button to switch gamerounds, playing short Tetris notes to indicate selected gameround duration.
- A disarm/defuse button, can be pushed during a game (hold for 10 seconds) to "defuse" the timer triggering Defuse Victory.
- Buzzer beeping, that dynamically scales/accelerates based on defined Beep Delays, Game Time Remaining and Total Game Time.

### Roadmap for v2
- Additional/shorter game rounds (after testing multiple 5 minute rounds)
- Implementing SDcard+speaker module
- Implement/Custom keypad support
- Implement segmented number display


