<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Installation](#installation)
* [Usage](#usage)


<!-- ABOUT THE PROJECT -->
## About The Project
This is a maze game in which the player “Hero” tries to escape and avoids being captured by the computer “Minotaur”. If the "Hero" reaches the "<" in the maze, the player wins. However, if the "Hero" is captured by the "Minotaur", the player loses. 
We implemented two pathfinding algorithms for the “Minotaur” to increase the difficulty of the game. If the maze is loaded with a* pathfinding algorithm, the game is harder.

In this project, users can customize  the size, wall, the starting position of the "Hero", and the starting position of the "Minotaur" by modifying the .txt file in ./data.


### Built With
* [C++](https://isocpp.org/)



<!-- GETTING STARTED -->
## Getting Started

Here is how you set up this project locally

### Installation

1. Install the C++ language [GCC compiler](https://gcc.gnu.org/install/index.html)
2. Clone the repo 
```sh
git clone https://github.com/tottiliyt/escapeHero.git
```
3. Makefile
```sh
make all
```


## Usage
Choose the maze map you want to use in ./data and pass the maze as an argument

Take maze2.txt as an example

```sh
./minotaur ./data/maze2.txt 
```

You can control the "Hero" using keyboard input, or curses if you choose a different maze. 

<img src="https://github.com/tottiliyt/escapeHero/blob/master/demo.gif" width="450" height="250">
