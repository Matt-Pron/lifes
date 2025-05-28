# Lifes

![screenshot](https://github.com/matt-pron/lifes/blob/main/assets/screenshot.png?raw=true)

**Lifes** is a minimalist TUI TTRPG Health Points tracker for Linux.

> Work In Progress
> Still missing Help window. Usage information below.

It's made in c++, using ncurses.

## Building

### Build

```
make
```

### Run

```
./bin/lifes
```

### Clean Build

```
make clean
```

### Usage

## Movement

|Keybind|Command|
|:---:|:---|
|<kbd>h</kbd>|Moves to PJ table.|
|<kbd>j</kbd>|Moves DOWN in the current table.|
|<kbd>k</kbd>|Moves UP in the current table.|
|<kbd>l</kbd>|Moves to PNJ table.|

## Commands

|Keybind|Command|
|:---:|:---|
|<kbd>Return</kbd>|Adds a new character.|
|<kbd>q</kbd>|Adds a new character.|
|<kbd>a</kbd>|Adds a new character.|
|<kbd>r</kbd>|Adds a new character.|
|<kbd>F1</kbd>|~Opens help menu.~|

## Example tables

To fill the tables with simple example data use:

```
cp -r ./assets/data ./bin/
```
