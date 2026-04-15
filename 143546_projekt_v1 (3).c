#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void v1(FILE *fp_h, FILE *fp_r);
void v(void);
void h(void);

int main(void) {
    v();
}


void v1(FILE *fp_h, FILE *fp_r)
{
    char buffer[1000];
    char riesenia[10][50], idents[10][50];
    char *data;
    char *iden;
    //ak este neboli otvorene, pokusim sa ich otvorit
    if (fp_h==NULL || fp_r==NULL ) {
        fp_h=fopen("RegisterHracov.txt","r");
        fp_r=fopen("RegisterRieseni.txt","r");
    }
    if (fp_h==NULL || fp_r==NULL ) {
        printf("V1: Neotvorene txt subory.\n");
        v();
    }
    int entry_count=0,i;
    char *parsed_piece;
    while (fgets(buffer, sizeof(buffer), fp_r)) {
        if (strcmp(buffer, "\n")==0) {
            continue;
        }
        strcpy(riesenia[entry_count], buffer);
        parsed_piece = strtok(buffer, "#");
        parsed_piece= strtok(NULL, "#");
        strcpy(idents[entry_count], parsed_piece);
        entry_count++;
    }

    memset(buffer, 0, sizeof(buffer));
    while (fgets(buffer, sizeof(buffer), fp_h)) {
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
    fclose(fp_r);
    fclose(fp_h);
    v();

}
void v(void) {
    char buffer[10];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    while (1) {
        if (strcmp(buffer, "v 1")==0 || strcmp(buffer, "h")==0) {
            break;
        }
        printf("V: Nespravna volba vypisu.\n");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
    }
    if (strcmp(buffer, "v 1")==0 ) {
        FILE *fp_h=fopen("RegisterHracov.txt", "r"), *fp_r=fopen("RegisterRieseni.txt", "r");
        v1(fp_h, fp_r);
    } else if (strcmp(buffer, "h")==0 ) {
        h();
    }
}

void h(void) {
    FILE *fp_r= fopen("RegisterRieseni.txt", "r");
    if (fp_r==NULL) {
        printf("H: Neotvoreny txt subor.\n");
        v();
    }
    char buffer4[100], riesenia[10][50], idents[10][50];

    char buffer2[100], copy3[100];
    char *sid, *parsed_piece;
    int entry_count=0,i;
    fgets(buffer4, sizeof(buffer4), stdin);
    if (strcmp(buffer4, "\n")==0) {
        printf("H: Neotvoreny txt subor.\n");
        v();
    }

    strcpy(buffer2, buffer4);
    strcpy(copy3, buffer4);
    buffer4[strcspn(buffer4, "\n")] = 0;
    copy3[strcspn(copy3, "\n")] = 0;

    if (strlen(buffer4)> 8) {
        printf("H: Nespravny vstup.\n");
        v();
    }
    char delim[2];
    delim[0] = buffer4[3];
    delim[1] = '\0';
    sid= strtok(copy3, delim);
    if (strcmp(sid, "SID")!=0) {
        printf("H: Nespravny vstup.\n");
        v();
    }
    char letter = buffer2[3];
    if (!(letter >= 'a' && letter <= 'z' || letter >= 'A' && letter <= 'Z')) {
        printf("H: Nespravny vstup.\n");
        v();
    }
    char *num;
    num= strtok(NULL, delim );
    int number = atoi(num);
    if (number<0 || number > 9999) {
        printf("H: Nespravny vstup.\n");
        v();
    }
    memset(buffer4, 0, sizeof(buffer4));
    while (fgets(buffer4, sizeof(buffer4), fp_r)) {
        if (strcmp(buffer4, "\n")==0) {
            continue;
        }
        strcpy(riesenia[entry_count], buffer4);
        parsed_piece = strtok(buffer4, "#");
        parsed_piece= strtok(NULL, "#");
        parsed_piece=strtok(NULL, "#");
        strcpy(idents[entry_count], parsed_piece);
        entry_count++;
    }

    int found=0;
    buffer2[strcspn(buffer2, "\n")] = 0;
    for (i=0; i<entry_count; i++) {
        if (strcmp(buffer2,idents[i])==0) {
            FILE *fp_v=fopen("Výstup_H.txt", "w");
            if (fp_v==NULL) {
                printf("H: Neotvoreny txt subor.\n");
                v();
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
    v();
}