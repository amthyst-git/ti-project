#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


int main(int argc, char *argv[]){
    if (argc < 4){fprintf(stderr, "Usage: %s <dir_destino_1> <dir_destino_2> <dir_origem>\n", argv[0]); return 1;}

    srand(time(NULL));

    char* dir1 = argv[1];
    char* dir2 = argv[2];
    char* dirFiles = argv[3];

    char command[512];
    char buffer[256];

    snprintf(command, sizeof(command), "mkdir -p %s %s", dir1, dir2);
    system(command);

    snprintf(command, sizeof(command), "ls %s", dirFiles);
    FILE * dir = popen(command, "r");
    if (dir == NULL){perror("popen failed"); return 1;}

    char * destiny;
    while(fgets(buffer, sizeof(buffer), dir) != NULL){

        // Encontra a primeira ocurrência de '\n' na string e altera-a para ´\0´
        buffer[strcspn(buffer, "\n")] = '\0';

        // Verifica se os diretórios estão a ser selecionados, caso ocorra ignora a iteração atual
        if (strcmp(buffer, dir1) == 0 || strcmp(buffer, dir2) == 0) continue;

        // Se o buffer estiver vazio ignora a itereação atual
        if (strlen(buffer) == 0) continue;

        // Seleciona 'aleatóriamente' o diretório para onde copiar o ficheiro
        if (rand() % 2 == 0){destiny = dir1;}
        else{destiny = dir2;}

        // Copia o comando de cópia, e executa-o
        snprintf(command, sizeof(command), "cp %s/%s %s/", dirFiles, buffer, destiny);
        system(command);
    }

    pclose(dir);
    return 0;
}
