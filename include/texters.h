// Return codes
#pragma once

#define TextOK 0 // no errors
// codes of situations
#define TextNoDown 101 // there is no sublevel for the current position
#define TextNoNext 102 // there is no section of the current level
#define TextNoPrev 103 // current position is in the beginning of the text
// codes of errors
#define TextError -102 // error in the text
#define TextNoMem -101 // no memory

