# Lifes

<img src="https://github.com/matt-pron/lifes/blob/main/assets/screenshot.png?raw=true" width="100%">

**Lifes** is a minimalist TUI TTRPG Health Points tracker for Linux.

It's made in c++, using ncurses.

> Work In Progress
> Still missing Help window. Usage information below.  
> TODO: Commands to save and load PNJ tables by name, so you can setup multiple encounters before your session.

<img src="https://github.com/Matt-Pron/lifes/blob/main/assets/showcase.gif?raw=true" width="100%">

## Description

Add or remove characters to setup the tables for your encounter.  
To modify a character's HP, select it, type the damage(-) or healing amount and confirm with <kbd>Return</kbd>.  
Characters between 1 and 9 HP will be displayed in yellow. Characters with 0 or less HP will be displayed in red.

Both tables are saved in disk when altered.

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
|<kbd>a</kbd>|Adds a new character.|
|<kbd>r</kbd>|Removes a character. Confirm with <kbd>y</kbd> or <kbd>n</kbd>|
|<kbd>Return</kbd>|Confirms input.|
|<kbd>Backspace</kbd>|Erases input.|
|<kbd>Escape</kbd>|Cancels current command.|
|<kbd>F1</kbd>|~Opens help menu.~|
|<kbd>q</kbd>|Quits Lifes.|

## Example tables

To fill the tables with simple example data use:

```
cp -r ./assets/data ./bin/
```
