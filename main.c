#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <dirent.h>

#define MAX_ARGS 64
#define MAX_LINE 1024
#define iloscKolorow 6


char bar[50];
char numberOfColor = 0;
char numberOfTextColor = 0;
char numberOfTextColorNUser = 0;
char * welcomeMessage = "";

void handle_sigint(int sig) {
    printf("");
}

char * kolory[iloscKolorow][2] = {
    {"grey","%s"},
    {"pink","\e[95m%s"},
    {"green","\e[0;32m%s"},
    {"yellow","\e[0;33m%s"},
    {"blue","\e[0;94m%s"},
    {"cyan","\e[0;36m%s"}
};


char configFileUwU[] = "bar=uwuSH>\ncolor=pink\ntextColor=yellow\ntextColorNotUser=blue\nprintf=echo fortnite\nbinarySpace=/moje/\nwelcomeMessage=Meow Meow :3\n";

DIR * sciezka;
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
    int pZ=0,i=0;
    for (pZ = 0; z[pZ] == 32; pZ++);

    for (i=0; 1; i++)
    {
        if (!x[i] && (!z[i+pZ] || z[i+pZ] == ' ') ) return 1;
        else if (x[i] != z[i+pZ] ) return 0;
    }
}

int aliasyNyaAmout = 1;

typedef struct {char * x[2];} dwaStringi;

dwaStringi * aliasyNya;

char dirBack[400];


typedef char * string;

string * binaryFilesLocationNya;
int binaryFilesLocationNyaAmout;
char * user;

void reloadConfig()
{
    if(aliasyNya != NULL) free(aliasyNya); 
    aliasyNya = malloc(sizeof(dwaStringi));

    if(binaryFilesLocationNya != NULL) free(binaryFilesLocationNya); 
    binaryFilesLocationNya = malloc(sizeof(string));

    aliasyNyaAmout = 1;
    binaryFilesLocationNyaAmout = 1;

    char pathConfig[100];
    user = getenv("USER");
    
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
            for (int b=0;b<2;b++) { name[b][pierwszyN[b]] = 0; pierwszyN[b] = 0;}
            

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
            else if (stringCompare(name[0],"welcomeMessage" )) welcomeMessage = strdup(name[1]);
            else if (stringCompare(name[0],"binarySpace" )) {
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
    signal(SIGINT,handle_sigint);
    user = getenv("USER");

    char line[MAX_LINE];
    char *args[MAX_ARGS];
    reloadConfig();

    printf("%s\n",welcomeMessage);
    
    if (1)
    {
        char buffor[200];
        sprintf(buffor,"/home/%s/.config/test",user);
        FILE *  test = fopen(buffor,"w");
        sprintf(buffor,"mkdir /home/%s/.config/",user);
        if (test == NULL) system(buffor);
        else fclose(test);
        sprintf(buffor,"/home/%s/.config/config.txt",user);
        test = fopen(buffor,"r");
        if (test == NULL){
            test = fopen(buffor,"w");
            fprintf(test,"%s",configFileUwU);
        }
        fclose(test);
    }

    while (1) {
        char czyCd = 0;
        char waitOrNot = 0;

        while (1)
        {
            printf(kolory[numberOfColor][1],bar);
            printf(kolory[numberOfTextColor][1],"");
            fflush(stdout);
            fgets(line,sizeof(line),stdin);
            if (strlen(line) != 1 ) break;
            usleep(10000);
        }
        
        printf("\033[0m");

        printf(kolory[numberOfTextColorNUser][1],"");
        fflush(stdout);

        line[strcspn(line, "\n")] = 0;
        if (stringCompareX("exit",line) || stringCompare(line, "quit")) break;
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
        else if (stringCompareX("ls",line))
        {
            struct dirent * plik;

            sciezka = opendir(dir);

            if (sciezka != NULL)
            {
                struct winsize w;
                ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

                int najdluzsy = 0; 
                while(( plik = readdir( sciezka ) ) ) if (strlen(plik->d_name) > najdluzsy) najdluzsy = strlen(plik->d_name);

                int iloscZnakow = 0;

                rewinddir(sciezka);

                while(( plik = readdir( sciezka ) ) ) { 
                    int colorr = 2;
                    FILE * nyga = fopen((*plik).d_name, "r");
                    if (nyga == NULL) colorr++;
                    else fclose(nyga);
                    
                    iloscZnakow+=najdluzsy;
                    if (iloscZnakow+najdluzsy > w.ws_col) {iloscZnakow = 0; printf("\n");}

                    char buffor[200];
                    sprintf(buffor,"%s",plik->d_name);
                    #define bbb for (int i = 0; i < (najdluzsy - strlen(plik->d_name))/2; i++ ) printf(" ");
                    bbb printf(kolory[colorr][1],buffor); bbb

                }
            }
            printf("\n");
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
                    if (line[licznik] == ' ' || licznik+1 == strlen(line) ) czyByl = 1;
                }
                int lineLen = strlen(line);
                for (int b = licznik-1; b < lineLen; b++) line[b-licznik-1] = line[b];
                for (int b = lineLen-licznik-1; b < lineLen; b++) line[b] = 0;
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
                
                for (int i = 1; i < binaryFilesLocationNyaAmout; i++){
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
    for (int i = 1; i < aliasyNyaAmout; i++) for (int b = 0; b < 2; b++) free(aliasyNya->x[b]);
    for (int b = 0; b < binaryFilesLocationNyaAmout; b++)  free(binaryFilesLocationNya[b]);

    free(aliasyNya);
    free(binaryFilesLocationNya);
    closedir( sciezka ); 
    return 0;
}