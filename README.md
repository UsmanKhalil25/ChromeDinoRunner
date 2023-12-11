# Chrome Dino Runner Clone

![Chrome Dino Runner Clone](screenshot.png)

## Overview

This is a simple clone of the popular Chrome Dino Runner game implemented in C++ using the SFML (Simple and Fast Multimedia Library). The game replicates the basic functionalities of the original Chrome Dino Runner, allowing players to jump over cacti and avoid obstacles to achieve a high score.

## Features

- Jumping: Press the spacebar to make the dino jump.
- Obstacles: Dodge oncoming obstacles, such as cacti, by timing your jumps.
- Score: The game keeps track of your score based on the distance covered.

## Prerequisites

Before running the game, ensure that you have the following installed:

- C++ compiler
- SFML library (Simple and Fast Multimedia Library)

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/UsmanKhalil25/ChromeDinoRunner.git
    ```

2. Compile the code using your C++ compiler. Make sure to link against the SFML libraries.

    ```bash
    g++ -o dino_runner main.cpp -lsfml-graphics -lsfml-window -lsfml-system
    ```

3. Run the compiled executable:

    ```bash
    ./dino_runner
    ```

## Controls

- **Spacebar:** Jump

## Gameplay

- Press the spacebar to make the dino jump over obstacles.
- Keep jumping to survive and accumulate points.
- The game ends when the dino's health reaches 0
- Each collision with an obstacles reduces the health by 25%


## Acknowledgments

- Inspired by the Chrome Dino Runner game.

