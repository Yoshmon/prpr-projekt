#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int v1(FILE **fp_h, FILE **fp_r, FILE **fp_s);
int v(int *q_choice);
int h(FILE *fp_h, FILE *fp_r, FILE *fp_s);
void n(char ***hraci,char ***riesenia,char ***sudoku, FILE **fp_h, FILE **fp_r, FILE **fp_s, int *pocet_hracov, int *pocet_rieseni, int *pocet_sudoku);
void v2(char ***hraci, char ***riesenia, char ***sudoku, FILE *fp_h, FILE *fp_r, FILE *fp_s, int *pocet_hracov, int *pocet_rieseni);
void e(char ***hraci, char ***riesenia, char ***sudoku, FILE *fp_s, int *pocet_sudoku);
void w(char ***hraci, char ***riesenia, char ***sudoku, int *pocet_hracov, int *pocet_rieseni, int *pocet_sudoku);
void q(char ***hraci, char ***riesenia, char ***sudoku, int *pocet_rieseni, int *q_choice);

int main(void) {
    FILE *fp_h= NULL;
    FILE *fp_r= NULL;
    FILE *fp_s= NULL;
    char **hraci=NULL, **riesenia=NULL, **sudoku=NULL;
    int hodnota=6, i, pocet_hracov, pocet_rieseni, pocet_sudoku, q_choice;
    while (hodnota !=8) {
        int choice=v(&q_choice);
        if (choice == 1) {
            int v10=v1(&fp_h, &fp_r, &fp_s);
        }
        else if (choice == 2) {
            int h1=h(fp_h, fp_r, fp_s);
        } else if (choice == 3) {
            n(&hraci, &riesenia, &sudoku, &fp_h, &fp_r, &fp_s, &pocet_hracov, &pocet_rieseni, &pocet_sudoku);
        } else if (choice == 4) {
            v2(&hraci, &riesenia, &sudoku, fp_h, fp_r, fp_s, &pocet_hracov, &pocet_rieseni);
        } else if (choice == 5) {
            e(&hraci, &riesenia,&sudoku, fp_s, &pocet_sudoku);
        } else if (choice == 6) {
            w(&hraci, &riesenia, &sudoku, &pocet_hracov, &pocet_rieseni, &pocet_sudoku);
        } else if (choice == 7) {
            q(&hraci, &riesenia, &sudoku, &pocet_rieseni, &q_choice);
        }
    }
    return 0;
}

int v1(FILE **fp_h, FILE **fp_r, FILE **fp_s)
{
    char buffer[1000];
    memset(buffer, 0, sizeof(buffer));
    char *data;
    char *iden;
    //ak este neboli otvorene, pokusim sa ich otvorit
    if (*fp_h==NULL || *fp_r==NULL || *fp_s==NULL) {
        *fp_h=fopen("RegisterHracov.txt","r");
        *fp_r=fopen("RegisterRieseni.txt","r");
        *fp_s=fopen("Sudoku.txt","r");
    }
    if (*fp_h==NULL || *fp_r==NULL || *fp_s==NULL) {
        printf("V1: Neotvorene txt subory.\n");
        return 0;
    }
    int entry_count=0,i;
    char *parsed_piece;
    while (fgets(buffer, sizeof(buffer), *fp_r)) {
        entry_count++;
    }
    rewind(*fp_r);

    char riesenia[entry_count][50], idents[entry_count][50];

    entry_count=0;
    while (fgets(buffer, sizeof(buffer), *fp_r)) {
        if (strcmp(buffer, "\n")==0) {
            continue;
        }
        strcpy(riesenia[entry_count], buffer);
        parsed_piece = strtok(buffer, "#");
        parsed_piece= strtok(NULL, "#");
        strcpy(idents[entry_count], parsed_piece);
        entry_count++;

    }
    rewind(*fp_r);
    memset(buffer, 0, sizeof(buffer));
    while (fgets(buffer, sizeof(buffer), *fp_h)) {
        if (strcmp(buffer, "\n")==0) {
            continue;
        }
        iden = strtok(buffer, "#");
        if (iden!=NULL) {
            printf("\nIdentifikator: %s\n", iden);
        } else {
            printf("Identifikator:\n");
        }
        data = strtok(NULL, "#");
        if (data!=NULL) {
            printf("Meno a priezvisko: %s\n", data);
        } else {
            printf("Meno a priezvisko:\n");
        }
        data = strtok(NULL, "#");
        if (data!=NULL) {
            printf("Krajina: %s\n", data);
        } else {
            printf("Krajina:\n");
        }

        data= strtok(NULL, "#");
        if (data!=NULL) {
            printf("Rok: %s\n", data);
        } else {
            printf("Rok:\n");
        }
        printf("Vzorka:\n");
        for (i=0;i< entry_count; i++) {
            if (strcmp(iden,idents[i]) == 0) {
                riesenia[i][strlen(riesenia[i])-1] = '\0';
                printf("    %s\n", riesenia[i]);
                break;
            }
        }
    }
    rewind(*fp_h);
    return 1;
}

int v(int *q_choice) {
    char buffer[100];
    int choice;
    while (1) {
        fgets(buffer, sizeof(buffer),stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (buffer[0] == '\0') {
            continue;
        }
        if (buffer[0]=='h' || buffer[0]=='n'|| buffer[0]== 'v' || buffer[0]== 'n' || buffer[0]=='q' || buffer[0]=='w' || buffer[0]=='e') {
            break;
        } else {
            printf("V: Nespravna volba vypisu.\n");
            continue;
        }

    }
    printf("\n");
    char copy[200];
    strcpy(copy, buffer);
    char *num=strtok(copy, " ");
    num= strtok(NULL, " ");
    if (num==NULL) {
        choice =1;
    } else {
        choice = atoi(num);
    }
    if (buffer[0]== 'v' && choice ==1) {
        return 1;
    } else if (buffer[0]=='h' ) {
        return 2;
    } else if (buffer[0]=='n' ) {
        return 3;
    } else if (buffer[0]=='v' && choice == 2) {
        return 4;
    } else if (buffer[0]=='e' ) {
        return 5;
    } else if (buffer[0]=='w') {
        return 6;
    } else if (buffer[0]=='q') {
        *q_choice = choice;
        return 7;
    }
}

int h(FILE *fp_h, FILE *fp_r, FILE *fp_s) {

    if (fp_r==NULL) {
        fp_r=fopen("RegisterRieseni.txt", "r");
    }
    if (fp_r==NULL) {
        printf("Neotvorene txt subory\n");
        return 0;
    }
    int entry_count=0;
    char buffer4[100], buffer3[100];
    while (fgets(buffer4, sizeof(buffer4), fp_r)) {
        entry_count++;
    }
    rewind(fp_r);
    char riesenia[entry_count][50], idents[entry_count][50];

    char buffer2[100], copy3[100];
    char *sid, *parsed_piece;
    int i;
    entry_count=0;
    fgets(buffer4, sizeof(buffer4), stdin);
    if (strcmp(buffer4, "\n")==0) {
        printf("H: Neotvoreny txt subor.\n");
        return 0;
    }

    strcpy(buffer2, buffer4);
    strcpy(copy3, buffer4);
    buffer4[strcspn(buffer4, "\n")] = 0;
    copy3[strcspn(copy3, "\n")] = 0;

    if (strlen(buffer4)> 8) {
        printf("H: Nespravny vstup.\n");
        return 0;
    }
    char delim[2];
    delim[0] = buffer4[3];
    delim[1] = '\0';
    sid= strtok(copy3, delim);
    if (strcmp(sid, "SID")!=0) {
        printf("H: Nespravny vstup.\n");
        return 0;
    }
    char letter = buffer2[3];
    if (!(letter >= 'a' && letter <= 'z' || letter >= 'A' && letter <= 'Z')) {
        printf("H: Nespravny vstup.\n");
        return 0;
    }
    char *num;
    num= strtok(NULL, delim );
    int number = atoi(num);
    if (number<0 || number > 9999) {
        printf("H: Nespravny vstup.\n");
        return 0;
    }
    memset(buffer4, 0, sizeof(buffer4));
    while (fgets(buffer3, sizeof(buffer3), fp_r)) {
        if (strcmp(buffer3, "\n")==0) {
            continue;
        }
        strcpy(riesenia[entry_count], buffer3);
        parsed_piece = strtok(buffer3, "#");
        parsed_piece= strtok(NULL, "#");
        parsed_piece=strtok(NULL, "#");
        strcpy(idents[entry_count], parsed_piece);
        entry_count++;
    }
    rewind(fp_r);

    int found=0;
    buffer2[strcspn(buffer2, "\n")] = 0;
    for (i=0; i<entry_count; i++) {
        if (strcmp(buffer2,idents[i])==0) {
            FILE *fp_v=fopen("Výstup_H.txt", "w");
            if (fp_v==NULL) {
                printf("H: Neotvoreny txt subor.\n");
                return 0;
            }
            fprintf(fp_v, riesenia[i]);
            fclose(fp_v);
            found=1;
        }
    }
    if (found==1)
    printf("\nH: uspesne vytvoreny sumar.\n");
    if (found==0) {
        printf("H: Neotvoreny txt subor.\n");
    }
    fclose(fp_r);
    return 0;
}

void n(char ***hraci, char ***riesenia, char ***sudoku, FILE **fp_h, FILE **fp_r, FILE **fp_s, int *pocet_hracov, int *pocet_rieseni, int *pocet_sudoku) {
    char buffer[300];
    int i=0;
    if (*fp_h==NULL || *fp_r==NULL||*fp_s==NULL) {
        printf("N: Neotvoreny subor.\n");
        return;
    }
    *pocet_sudoku=0;
    *pocet_hracov=0, *pocet_rieseni=0;
    if (*hraci && *pocet_hracov!=0) {
        for (i = 0; i < *pocet_hracov; i++) {
            free((*hraci)[i]);
        }
        free(*hraci);
        *hraci = NULL;
    }
    if (*riesenia && *pocet_rieseni!=0) {
        for (i = 0; i < *pocet_rieseni; i++) {
            free((*riesenia)[i]);
        }
        free(*riesenia);
        *riesenia = NULL;
    }
    if (*sudoku && *pocet_sudoku!=0) {
        for (i = 0; i < *pocet_sudoku; i++) {
            free((*sudoku)[i]);
        }
        free(*sudoku);
        *sudoku = NULL;
    }
    while (fgets(buffer, sizeof(buffer), *fp_h)) {
        if (strcmp(buffer, "\n")!=0) {
            (*pocet_hracov)++;
        }

    }
    while (fgets(buffer, sizeof(buffer), *fp_r)) {
        if (strcmp(buffer, "\n")!=0) {
            (*pocet_rieseni)++;
        }
    }
    while (fgets(buffer, sizeof(buffer), *fp_s)) {
        if (strcmp(buffer, "\n")!=0) {
           (* pocet_sudoku)++;
        }
    }
    rewind(*fp_h);
    rewind(*fp_r);
    rewind(*fp_s);



    if (!*hraci && !*riesenia && !*sudoku ) {
        *hraci = calloc(*pocet_hracov,sizeof(char*));
        if (*hraci==NULL) {
            printf("Skill issue.\n");
        }
        *riesenia= calloc(*pocet_rieseni,sizeof(char*));
        if (*riesenia==NULL) {
            printf("Skill issue.\n");
        }
        *sudoku=calloc(*pocet_sudoku,sizeof(char*));
        if (*sudoku==NULL) {
            printf("Skill issue.\n");
        }
    }
    i=0;
    while (fgets(buffer, sizeof(buffer), *fp_h)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        (*hraci)[i]=malloc((strlen(buffer)+1)*sizeof(char));
        strcpy((*hraci)[i],buffer);
        i++;
    }
    i=0;
    while (fgets(buffer, sizeof(buffer), *fp_r)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        (*riesenia)[i]=malloc((strlen(buffer)+1)*sizeof(char));
        strcpy((*riesenia)[i],buffer);
        i++;
    }
    i=0;
    while (fgets(buffer, sizeof(buffer), *fp_s)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        (*sudoku)[i]=malloc((strlen(buffer)+1)*sizeof(char));
        strcpy((*sudoku)[i],buffer);
        i++;
    }
    rewind(*fp_h);
    rewind(*fp_r);
    rewind(*fp_s);
}
void v2(char ***hraci, char ***riesenia, char ***sudoku,FILE *fp_h, FILE *fp_r, FILE *fp_s, int *pocet_hracov, int *pocet_rieseni) {
    if (!*hraci || !*riesenia || !*sudoku ) {
        printf("V2: Nenaplnene polia.\n");
        return;
    }
    int i, j,k;
    for (i = 0; i < *pocet_hracov; i++) {
        char buffer[300];
        strcpy(buffer,(*hraci)[i]);
        char *pid= strtok(buffer, "#");
        if (pid == NULL) {
            pid = " ";
        }
        char *identita = strtok(NULL, "#");
        if (identita == NULL) {
            identita = " ";
        }
        char *krajina= strtok(NULL, "#");
        if (krajina == NULL) {
            krajina = " ";
        }
        char *rok = strtok(NULL, "#");
        if (rok == NULL) {
            rok = " ";
        }
        printf("PID: %s / %s / %s\n", pid, rok, krajina);
        printf("Identita: %s\n", identita);
        printf("Vysledok:\n    ");
        int found=0;
        for (j =0; j < *pocet_rieseni; j++) {
            char buffer2[200];
            strcpy(buffer2, (*riesenia)[j]);
            char *ident2= strtok(buffer2, "#");
            ident2= strtok(NULL, "#");
            if (strncmp(pid,ident2, 9)==0) {
                char copy[200];
                strcpy(copy,(*riesenia)[j]);
                for (k=0; k<strlen(copy); k++) {
                    if (copy[k] == '#') {
                        copy[k]='/';
                    }
                }
                printf("%s\n    ", copy);
                found = 1;
            }
        }
        printf("\n");

    }
}
void e(char ***hraci, char ***riesenia, char ***sudoku, FILE *fp_s, int *pocet_sudoku) {
    if (!*hraci || !*riesenia || !*sudoku) {
        printf("E: Polia nie su vytvorene.\n");
        return;
    }
    int choice;
    char buffer4[20];

    scanf("%s %d",buffer4, &choice);

    char copy3[20];
    strcpy(copy3, buffer4);
    if (choice > 5 || choice < 1) {
        printf("\nE: Nespravny vstup.\n");
        return ;
    }
    if (strlen(buffer4)> 9) {
        printf("\nE: Nespravny vstup.\n");
        return ;
    }
    char delim[2];
    delim[0] = buffer4[3];
    delim[1] = '\0';
    char *sid= strtok(copy3, delim);
    if (strcmp(sid, "SID")!=0) {
        printf("\nE: Nespravny vstup.\n");
        return ;
    }
    char letter = buffer4[3];
    if (!(letter >= 'a' && letter <= 'z' || letter >= 'A' && letter <= 'Z')) {
        printf("\nE: Nespravny vstup.\n");
        return ;
    }
    char *num;
    num= strtok(NULL, delim );
    int number = atoi(num);
    if (number<0 || number > 9999) {
        printf("\nE: Nespravny vstup.\n");
        return ;
    }
    srand(time(NULL));
    int i,j,k;
    FILE *vysledok=fopen("Výstup_E.txt", "w");
    if (vysledok == NULL) {
        printf("\nE: Nepodarilo sa vytvorit subor.\n");
        return;
    }

    char copy[200];
    int found=0,l;
    for (i = 0; i < *pocet_sudoku; i++) {
        strcpy(copy,(*sudoku)[i]);
        char *sid= strtok(copy, "#");
        if (strcmp(buffer4, sid)==0) {
            char table[10];
            for (k=0; k<9; k++) {
                int rand_nums[choice],w;
                for (l=0;l<choice; l++) {
                    rand_nums[l]= rand()%9;
                }
                fprintf(vysledok, "|");
                int start=9;
                table[start]='\0';
                strncpy(table, (*sudoku)[i]+start+k*start, start);
                table[9]='\0';
                for (j=0; j< 9; j++) {
                    for (w=0; w<choice;w++) {
                        if (j==rand_nums[w]) {
                            found =1;
                        }
                    }
                    if (found ==0) {
                        fprintf(vysledok, "%c|",table[j]);
                    }
                    else {
                        fprintf(vysledok, " |");
                    }
                   found =0;
                }
                fprintf(vysledok, "\n");
            }
            fclose(vysledok);
            break;
        }

    }
}

void w(char*** hraci, char ***riesenia, char ***sudoku, int *pocet_hracov, int *pocet_rieseni,int *pocet_sudoku) {
    if (!*hraci || !*riesenia || !*sudoku) {
        printf("W: Polia nie su vytvorene.\n");
        return;
    }
    char choice[200];
    char **resizer;
    int i,j,k, pocet_vymazani=0;
    scanf("%s",choice);

    for (i=0; i < *pocet_rieseni; i++) {
        char buffer[200];
        strcpy(buffer,(*riesenia)[i]);
        char *pid= strtok(buffer, "#");
        pid = strtok(NULL, "#");

        if (strncmp(pid,choice, 9)==0) {
            free((*riesenia)[i]);
            (*riesenia)[i]= NULL;
            for (j=i; j<*pocet_rieseni-1; j++) {
                (*riesenia)[j]=(*riesenia)[j+1];
            }
            (*riesenia)[*pocet_rieseni-1]=NULL;
            free((*riesenia)[*pocet_rieseni-1]);

            (*pocet_rieseni)--;
            pocet_vymazani++;
            resizer= realloc(*riesenia,*pocet_rieseni*sizeof(char *));
            if (resizer) {
                *riesenia=resizer;
            }
            else {
                printf("W: nepodarilo sa alokovat pamat pre realloc.\n");
                return;
            }
        }
    }
    printf("\nW: Vymazalo sa : %d zaznamov !\n", pocet_vymazani);
    return;
}
void q(char ***hraci, char ***riesenia, char ***sudoku, int *pocet_rieseni, int *q_choice) {
    if (!*hraci || !*riesenia || !*sudoku) {
        printf("Q: Polia nie su vytvorene.\n");
        return;
    }

    char **resizer;

    int choice,i, wrong_format=1;
    char volba[100], kopia[100];
    char *volby[4];
    for (i=0;i<4;i++) {
        if (i==3) {
            char year[9];
            char minutes[3];
            char seconds[3];
            scanf("%s %s %s", year, minutes, seconds);
            sprintf(volba, "%s %s %s", year, minutes, seconds);
        }
        else {
            scanf("%s",volba);
        }
        volba[strcspn(volba, "\n")]= '\0';
        if (i==0) {
            while (wrong_format) {
                if (strlen(volba)> 9) {
                    printf("Q: nespravny format vstupu, zadaj znova:");
                    scanf("%s",volba);
                    continue;
                }
                char delim[2];
                delim[0] = volba[3];
                delim[1] = '\0';
                strcpy(kopia, volba);
                char *gid= strtok(kopia, delim);
                if (strcmp(gid, "GID")!=0) {
                    printf("Q: nespravny format vstupu, zadaj znova:");
                    scanf("%s",volba);
                    continue;
                }
                char letter = volba[3];
                if (!(letter >= 'a' && letter <= 'z' || letter >= 'A' && letter <= 'Z')) {
                    printf("Q: nespravny format vstupu, zadaj znova:");
                    scanf("%s",volba);
                    continue;
                }
                char *num;
                num= strtok(NULL, delim );
                int number = atoi(num);
                if (number<0 || number > 999) {
                    printf("Q: nespravny format vstupu, zadaj znova:");
                    scanf("%s",volba);
                    continue;
                }
                wrong_format=0;
            }

        }
        volby[i]= malloc(strlen(volba)+1);
        strcpy(volby[i],volba);
    }
    char *zaznam = malloc(43*sizeof(char));
    char *date = strtok(volby[3], " ");
    char *minutes = strtok(NULL, " ");
    char *seconds = strtok(NULL, " ");
    sprintf(zaznam, "%s#%s#%s#%s#%s#%s#", volby[0], volby[1], volby[2], date, minutes, seconds);
    resizer = realloc(*riesenia, (*pocet_rieseni+1)*sizeof(char *));
    if (resizer) {
        *riesenia= resizer;
    } else {
        printf("Q: nepodarilo sa alokovat pamat pre realloc.\n");
        return;
    }
    if (*q_choice> *pocet_rieseni) {
        (*riesenia)[*pocet_rieseni] = zaznam;
    } else {
        for (i=*pocet_rieseni; i>*q_choice-1; i--) {
            (*riesenia)[i]=(*riesenia)[i-1];
        }
        (*riesenia)[*q_choice-1]=zaznam;
    }
    (*pocet_rieseni)++;
    for (i=0; i<4;i++) {
        free(volby[i]);
    }
    return;
}