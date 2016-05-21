/*************************************
This file is for storing game data.
**************************************/

#ifndef DEFINE_H
#define DEFINE_H

//Basic map and game information.
#define MAP_HEIGHT 25
#define MAP_WIDE 79
#define CHAMBER_MAX_HEIGT 9
#define CHAMBER_MAX_WIDE 20
#define MAX_CHAMBERS 5

//Game elements representation.
#define STAIR '\\'
#define HERO '@'
#define HUMAN 'H'
#define DWARF 'W'
#define HALFLING 'L'
#define ORC 'O'
#define ELF 'E'
#define MERCHANT 'M'
#define DRAGON 'D'
#define GOLD 'G'
#define POTION 'P'

//Value of different gold.
#define NORMALGOLD 2
#define SMALLGOLD 1
#define MERCHANT_HOARD 4
#define DRAGONGOLD 6

//Enemies and items information/
#define ENEMY_SIZE 20
#define GOLD_SIZE 10
#define POTION_SIZE 10
#define POTION_KIND 6
#define MAXNEIGHBOURS 8
#define MISS_RATE 2

//Potion effect.
#define PHEFFECT 10
#define AHEFFECT 5
#define DHEFFECT 5

//Hero sill.
#define DROWPOTION 1.5
#define VAMPIREGAIN 5
#define GOBLINGOLD 5

#endif 
