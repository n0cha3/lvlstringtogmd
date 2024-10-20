#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define GDMAX 20
#define GMDEX 4

typedef struct {
    uint32_t SongID;
    char *LevelName;
    char *LevelBuffer;
    char *GmdOut;
    size_t GmdOutSize;
    size_t RawBufferSize;
    bool IsNewgrounds;
} gmd_t;


const char *ErrorMessages[12] = {
    "Not enough arguments. Usage: \
    \n[FILENAME]\
    \n[LEVELNAME] - Strictly ANSI name, only latin charecters\
    \n[SONGID]\
    \n[TRUE OR FALSE] - Use Newgrounds song ID\n\0",
    "Too many arguments. Usage: \
    \n[FILENAME]\
    \n[LEVELNAME] - Strictly ANSI name, only latin charecters\
    \n[SONGID]\
    \n[TRUE OR FALSE] - Use Newgrounds song ID.\n\0",
    "\nError: Such file does not exist.\n\0",
    "\nError: Can't read the file.\n\0",
    "\nCan't allocate memory to hold the original string.\n\0",
    "\nCan't allocate memory to hold the out string.\n\0",
    "\nLevel string size is 0.\n\0",
    "\nThe level name is too long.\n\0",
    "\nFailed to read file.\n\0",
    "\nExport fail.\n\0",
    "\nInvalid song id. default songs range from 0 to 20.\n\0",
    "\nInvalid choice. Use TRUE or FALSE.\n\0"
};

const char *Messages[6] = {
    "The file is:\n\0",
    "Bytes\n\0",
    "\nExported Successfully\n\0",
    "lvlstringtogmd\n\0",
    "Size of parsed string:\n\0",
    "Bytes\n\0"

};

bool GenerateString(gmd_t *StructLevel);
