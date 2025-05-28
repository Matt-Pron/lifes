# Lifes

![screenshot](https://github.com/matt-pron/lifes/blob/main/assets/screenshot.png?raw=true)

**Lifes** is a minimalist TUI TTRPG Health Points tracker for Linux.

It's made in c++, using ncurses.

> Work In Progress
> Still missing Help window. Usage information below.

## Description

Add or remove characters to setup the tables for your encounter.
To modify a character's HP, select it, type the (-) damage or healing amount and confirm with <kbd>return</kbd>.
Both tables are saved in disk when you add or remove a character, or modify it's HP.

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
|<kbd>Return</kbd>|Confirms input.|
|<kbd>q</kbd>|Quits Lifes.|
|<kbd>a</kbd>|Adds a new character.|
|<kbd>r</kbd>|Removes a character. Confirm with <kbd>y</kbd> or <kbd>n</kbd>|
|<kbd>F1</kbd>|~Opens help menu.~|

## Example tables

To fill the tables with simple example data use:

```
cp -r ./assets/data ./bin/
```
