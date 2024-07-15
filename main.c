#include "main.h"

int main(int argc, char *argv[]) {

    if (argc<5) {
        printf("%s\n%s", Messages[3], ErrorMessages[0]);
        return EXIT_FAILURE;
    }

    if (argc>5) {
        printf("%s\n%s", Messages[3], ErrorMessages[1]);
        return EXIT_FAILURE;
    }

    gmd_t GdLevel;

    if (strcmp(argv[4], "true") == 0) GdLevel.IsNewgrounds = true;

    else if (strcmp(argv[4], "false") == 0) GdLevel.IsNewgrounds = false;
    
    else {
        puts(ErrorMessages[11]);
        return EXIT_FAILURE;
    }

    if(strlen(argv[2]) > GDMAX) {
        puts(ErrorMessages[7]);
        return EXIT_FAILURE;
    }

    GdLevel.LevelName = malloc(strlen(argv[2]));

    strcpy(
            GdLevel.LevelName, 
            argv[2]
        );

    GdLevel.SongID = 0;
    GdLevel.SongID = atoi(argv[3]);

    FILE *File = fopen(argv[1], "r\0");

    if(File != NULL) {
        if (fseek(File, 0, SEEK_END) == 0) {
             GdLevel.RawBufferSize = ftell(File);
             rewind(File);

             printf(
                "\n%s\t%u\t%s", 
                Messages[0], 
                GdLevel.RawBufferSize, 
                Messages[1]
                );

                GdLevel.LevelBuffer = malloc(GdLevel.RawBufferSize);
                
                if(GdLevel.LevelBuffer == NULL) {
                    puts(ErrorMessages[4]);
                    return EXIT_FAILURE;
                }

                if (fread(GdLevel.LevelBuffer, 1, GdLevel.RawBufferSize, File) < 0) {
                    puts(ErrorMessages[6]);
                    fclose(File);
                    return EXIT_FAILURE;
                }

                bool StringStatus = GenerateString(&GdLevel);
                
                fclose(File);

                free(GdLevel.LevelBuffer);

                if (StringStatus) return EXIT_FAILURE;

                char *FileNameWithEx = malloc(strlen(GdLevel.LevelName) + GMDEX);

                strcpy(FileNameWithEx, GdLevel.LevelName);

                strcat(FileNameWithEx, ".gmd");

                File = fopen(FileNameWithEx, "w");

                if(File != NULL) {
                    if(fprintf(File, "%s", GdLevel.GmdOut) < 0 ) {
                        puts(ErrorMessages[9]);
                        exit(EXIT_FAILURE);
                    } 

                    free(GdLevel.GmdOut);
                    fclose(File);
                    free(GdLevel.LevelName);
                    free(FileNameWithEx);
                    puts(Messages[2]);
                } 

                else {
                    puts(ErrorMessages[3]);
                    return EXIT_FAILURE;
                }


            }

        else {
             fclose(File);
             puts(ErrorMessages[3]);
             return EXIT_FAILURE;
        }
    }

    else {
        puts(ErrorMessages[2]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

bool GenerateString(gmd_t *Level) {
    if(Level->IsNewgrounds == false) {
                if(Level->SongID > 0) {
                        if(Level->SongID > 22) {
                            puts(ErrorMessages[10]);
                            return false;
                        }

                    Level->GmdOutSize = snprintf(
                    NULL,
                    0,
                    "%s%s%s%s%s%u%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    Level->LevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    Level->LevelBuffer,
                    "</s><k>k8</k><i>\0",
                    Level->SongID,
                    "</i><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                Level->GmdOut = malloc(Level->GmdOutSize);

                if(Level->GmdOut == NULL) {
                    puts(ErrorMessages[5]);
                    return false;
                }

                sprintf(
                    Level->GmdOut,
                    "%s%s%s%s%s%u%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    Level->LevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    Level->LevelBuffer,
                    "</s><k>k8</k><i>\0",
                    Level->SongID,
                    "</i><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                printf("\n%s\t%u\t%s", Messages[4], Level->GmdOutSize, Messages[5]);
        }

                else {
                    Level->GmdOutSize = snprintf(
                    NULL,
                    0,
                    "%s%s%s%s%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    Level->LevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    Level->LevelBuffer,
                    "</s><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                Level->GmdOut = malloc(Level->GmdOutSize);

                if(Level->GmdOut == NULL) {
                    puts(ErrorMessages[5]);
                    return false;
                }

                sprintf(
                    Level->GmdOut,
                    "%s%s%s%s%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    Level->LevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    Level->LevelBuffer,
                    "</s><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                printf("\n%s\t%u\t%s", Messages[4], Level->GmdOutSize, Messages[5]);
            }
    }

    else {
                    Level->GmdOutSize = snprintf(
                    NULL,
                    0,
                    "%s%s%s%s%s%u%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    Level->LevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    Level->LevelBuffer,
                    "</s><k>k45</k><i>\0",
                    Level->SongID,
                    "</i><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                Level->GmdOut = malloc(Level->GmdOutSize);

                if(Level->GmdOut == NULL) {
                    puts(ErrorMessages[5]);
                    return false;
                }


                sprintf(
                    Level->GmdOut,
                    "%s%s%s%s%s%u%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    Level->LevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    Level->LevelBuffer,
                    "</s><k>k45</k><i>\0",
                    Level->SongID,
                    "</i><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                printf("\n%s\t%u\t%s", Messages[4], Level->GmdOutSize, Messages[5]);
    }
    
    return true;

}
