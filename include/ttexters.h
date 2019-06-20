#pragma once

#define TextOK 0 /* Ошибок нет */
    /* коды ситуаций */
#define TextNoDown 101 //нет подуровня для текущей позиции
#define TextNoNext 102 //нет след. раздела текущего уровня
#define TextNoPrev 103 // текущая позиция в начале текста
 /* error codes */
#define TextError -102 /* ошибка в тексте */
#define TextNoMem -101 /* нет памяти */