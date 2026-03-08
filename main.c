#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 64
#define MAX_LINE 1024


char * newFolder[] = {"sh", "./uwu.sh" };
char bar[50];
char numberOfColor = 0;
char numberOfTextColor = 0;
char numberOfTextColorNUser = 0;

#define iloscKolorow 5


char * kolory[iloscKolorow][2] = {
    {"grey","%s"},
    {"pink","\e[95m%s"},
    {"green","\e[0;32m%s"},
    {"yellow","\e[0;33m%s"},
    {"blue","\e[0;94m%s"}

    
};


char dir[400] = "/";

typedef struct {unsigned char x : 2;} bit;


int stringCompare(char uwu [], char uwu2[] )
{
    for (int i = 0; 1; i++)
    {
        if (uwu[i] != uwu2[i]) return 0;
        else if (!uwu[i] && !uwu2[i]) return 1;
    }
}
int stringCompareX(char x[], char z[])
{
    for (int i = 0; 1; i++)
    {
        if (x[i] == 0 && (z[i] == 0 || z[i] == ' ') ) return 1;
        else if (x[i] != z[i] ) return 0;
    }
}

int aliasyNyaAmout = 1;

typedef struct {char * x[2];} dwaStringi;

dwaStringi * aliasyNya;

char dirBack[400];


typedef char * string;

string * binaryFilesLocationNya;
int binaryFilesLocationNyaAmout;


void reloadConfig()
{
    if(aliasyNya != NULL) free(aliasyNya); 
    aliasyNya = malloc(sizeof(dwaStringi));

    if(binaryFilesLocationNya != NULL) free(binaryFilesLocationNya); 
    binaryFilesLocationNya = malloc(sizeof(string));

    aliasyNyaAmout = 1;
    binaryFilesLocationNyaAmout = 1;

    char pathConfig[100];
    char * user = getenv("USER");
    
    sprintf(dir,"/home/%s/",user );
    
    sprintf(pathConfig,"/home/%s/.config/uwush/config.txt",user);

    FILE * configFile = fopen(pathConfig, "r");
    fseek(configFile, 0, SEEK_END);
    char name[2][50];
    char pierwszyN[2] = {0,0};

    int ostatni = ftell(configFile);
    
    char procent = 0;


    
    for (int i=0;i<ostatni;i++)
    {
        fseek(configFile,i,SEEK_SET);
        char znak = fgetc(configFile);
        if (znak == '=') procent=1;
        else if (znak == '\n' || i+1 == ostatni ){
            procent = 0;
            for (int b=0;b<2;b++){ name[b][pierwszyN[b]] = 0; pierwszyN[b] = 0;}
            

            if (stringCompare(name[0],"bar" )) for (int b=0;b<50;b++) bar[b] = name[1][b];
            else if (stringCompare(name[0],"color")) {
                for (int b = 0; b < iloscKolorow; b++) if (stringCompare(name[1],kolory[b][0])) {numberOfColor = b; break;}
            }
            else if (stringCompare(name[0],"textColor")) {
                for (int b = 0; b < iloscKolorow; b++) if (stringCompare(name[1],kolory[b][0])) {numberOfTextColor = b; break;}
            }
            else if (stringCompare(name[0],"textColorNotUser")) {
                for (int b = 0; b < iloscKolorow; b++) if (stringCompare(name[1],kolory[b][0])) {numberOfTextColorNUser = b; break;}
            }
            if (stringCompare(name[0],"binarySpace" )) {
                binaryFilesLocationNyaAmout++;
                string * tymczasowy = realloc(binaryFilesLocationNya,binaryFilesLocationNyaAmout * sizeof(string));
                binaryFilesLocationNya = tymczasowy;
                binaryFilesLocationNya[binaryFilesLocationNyaAmout-1] = strdup( name[1]);
            }
            else {
                aliasyNyaAmout++;
                dwaStringi * tymczasowy = realloc(aliasyNya,aliasyNyaAmout * sizeof(dwaStringi));
                aliasyNya = tymczasowy;
                for (int b=0;b<2;b++) aliasyNya[aliasyNyaAmout-1].x[b] = strdup( name[b]);
            }
        }
        else {
            name[procent][pierwszyN[procent]] = znak;
            pierwszyN[procent]++;
        }
    }
    fclose(configFile);
}

int main(int argc, char *argv[]) {
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    reloadConfig();

    pid_t nowyFolder = fork();
    if (!nowyFolder) execvp(newFolder[0],newFolder);
    else wait(0);

    while (1) {
        char czyCd = 0;
        char waitOrNot = 0;

        
        printf(kolory[numberOfColor][1],bar);
        printf(kolory[numberOfTextColor][1],"");
        fflush(stdout);
        if (!fgets(line, sizeof(line), stdin)) break;
        printf("\033[0m");

        printf(kolory[numberOfTextColorNUser][1],"");
        fflush(stdout);

        line[strcspn(line, "\n")] = 0;
        if (stringCompare(line, "exit")) break;
        else if (stringCompare(line, "back")) {
            czyCd = 1;
            for (int i = 0; i < strlen(dir)+1; i++) dirBack[i] = dir[i];
            int licznik = 0;
            
            for (int i = strlen(dir)-1; i > 0; i--)
            {
                if (dir[i] == '/' && licznik) break;
                else if (dir[i] == '/' ) licznik++; 
                dirBack[i] = 0;
            }

            if (strlen(dirBack) > 0){
                for (int i = 0; i <= strlen(dirBack); i++) dir[i] = dirBack[i];
            }
        }
        else if (stringCompare(line,"hardPwd")) {
            printf("%s\n",dir);
            czyCd = 1;
        }
        else if (stringCompare(line,"reload")) {reloadConfig(); czyCd = 1;}
        else if (stringCompare(line,"binarySpace")){
            for (int i = 1; i < binaryFilesLocationNyaAmout; i++) printf("%s\n",binaryFilesLocationNya[i]);
            czyCd = 1;
        }

        //alias
        for (int i = 1; i < aliasyNyaAmout; i++)
        {
            if (stringCompareX(aliasyNya[i].x[0], line))
            {
                char licznik = 0, czyByl = 0;
                while (!czyByl) {
                    licznik++;
                    if (line[licznik] == ' ' || licznik == strlen(line) ) czyByl = 1;
                }
                int lineLen = strlen(line);
                for (int b = licznik; b < lineLen; b++) line[b-licznik] = line[b];
                for (int b = lineLen-licznik; b < lineLen; b++) line[b] = 0;
                lineLen = strlen(line);
                for (int b = lineLen-1; b >= 0 ; b-- ) line[b+strlen(aliasyNya[i].x[1])] = line[b];
                for (int b = 0; b < strlen(aliasyNya[i].x[1]); b++ ) line[b] = aliasyNya[i].x[1][b];
                line[lineLen + strlen(aliasyNya[i].x[1]) + 1] = 0;
            }
        }
        //multi task
        if (line[strlen(line)-1] == '&' && line[strlen(line)-2] == '&' && line[strlen(line)-3] == ' ' ){ 
            for (int i=0;i<2;i++) line[strlen(line)-1] = 0;
            waitOrNot = 1;
        }

        //chaange location
        bit singleQuote = {0};
        for (int i = 0; i < strlen(line); i++)
        {
            if (line[i] == '/' || line[i] == '.' )
            {
                char doDodania[200] = "";
                for (int b = i+1; b < strlen(line); b++)
                {
                    if (line[b] == 39) singleQuote.x++;
                    else if (line[b] == ' ' && !singleQuote.x ) break;
                    doDodania[strlen(doDodania)+1] = 0;
                    doDodania[strlen(doDodania)] = line[b]; 
                }
                if (line[i] == '.')
                {
                    char zlaczane[300];
                    for (int b = 0; b <= strlen(doDodania)+1; b++ ) doDodania[b-1] = doDodania[b];
                    sprintf(zlaczane,"%s%s/",dir,doDodania);
                    if (!chdir(zlaczane)) {
                        for (int n = 0; n <= strlen(zlaczane); n++) dir[n] = zlaczane[n];
                        czyCd = 1;
                    }
                }
                else if (line[i] == '/') {
                    for (int b = strlen(doDodania); b >= 0; b-- )doDodania[b+1] = doDodania[b];
                    doDodania[0] = '/';
                    doDodania[strlen(doDodania)+1] = 0;
                    doDodania[strlen(doDodania)] = '/'; 
                    if (!chdir(doDodania)){ 
                        for (int n = 0; n <= strlen(doDodania); n++) dir[n] = doDodania[n];
                        czyCd = 1;
                    }
                }
            }
            if (line[i] != ' ' ) break;
        }
        
    
        // Dzielenie na argumenty
        int i = 0;
        args[i] = strtok(line, " ");
        while (args[i] != NULL && i < MAX_ARGS - 1) {
            i++;
            args[i] = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (!czyCd)
        {
            pid_t pid = fork();
            if (!pid) {
                chdir(dir);
                execvp(args[0], args);
                
                for (int i = 1; i < binaryFilesLocationNyaAmout; i++)
                {
                    char uwu[100];
                    sprintf(uwu,"%s%s",binaryFilesLocationNya[i],args[0]);
                    args[0] = uwu;
                    execvp(args[0], args);
                }
                perror("Program doesn't exist");
                exit(EXIT_FAILURE);
            } 
            else if (pid > 0 && !waitOrNot) wait(0); 
        }
        
    }
    free(aliasyNya);
    return 0;
}