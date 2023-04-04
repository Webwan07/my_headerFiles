//setting.h file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
char symbols[] = {'X','O','J'}, empty = ' ';
char developer[] = "Josuan Hulom";

void error_input(char ch){
    if(ch != symbols[0] && ch != symbols[1] && ch != symbols[2]){
        printf("\t\tInvalid Input!\n");
    }
}

bool position_error(char arr[], int index){
    return (arr[index] == 'X' || arr[index] == 'O');
}

bool isboard_full(char arr[]){
    return (arr[0] != ' ' && arr[1] != ' ' && 
    arr[2] != ' ' && arr[3] != ' ' && arr[4] != ' ' &&
    arr[5] != ' ' && arr[6] != ' ' && arr[7] != ' ' &&
    arr[8] != ' ');
}

bool is_winner(char arr[], char ch){
    return (arr[0] == ch && arr[1] == ch && arr[2] == ch) ||
    (arr[3] == ch && arr[4] == ch && arr[5] == ch) ||
    (arr[6] == ch && arr[7] == ch && arr[8] == ch) ||
    (arr[0] == ch && arr[3] == ch && arr[6] == ch) ||
    (arr[1] == ch && arr[4] == ch && arr[7] == ch) ||
    (arr[2] == ch && arr[5] == ch && arr[8] == ch) ||
    (arr[0] == ch && arr[4] == ch && arr[8] == ch) ||
    (arr[2] == ch && arr[4] == ch && arr[6] == ch);
}

void get_board(char arr[]){
    printf(" %c | %c | %c \n", arr[0],arr[1],arr[2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", arr[3],arr[4],arr[5]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", arr[6],arr[7],arr[8]);
}

void welcome_msg(char str[]){
    printf("Welcome to\n X | O | X \n");
    printf("---|---|---\n");
    printf(" O | X | O \n");
    printf("---|---|---\n");
    printf(" X | O | X \nTic Tac Toe Game!\n Created by %s\n\n",str);
}

char* getdev(char *argv[]){
    char* str = (char*)malloc(100 * sizeof(char));
    if(argv[1] != NULL){
        int dev = atoi(argv[1]);
        if(dev == 1101){
            strcpy(str, "Greated by: Josuan\n\n");
        }
    }else{
        strcpy(str, "\n\n");
    }
    return str;
}

int get_playerInput(bool *is_game,char str[], char ch){
    get_board(str);
    int num;
    do{
        if(isboard_full(str) == true){
            printf("\t\tThe board is full!\n");
            for(int i = 0; i < 9; i++){
                str[i] = ' ';
            }
            *is_game = false;
        }else{
            do{
                while(1){
                    printf("Enter a position for %c (1-9): ",ch);
                    if(scanf("%d", &num) == 1){
                        break;
                    }
                    printf("\t\tError: You entered a non-numeric value.\n");
                    while(getchar() != '\n'){}
                }
                if(num == 0 || num > 9){
                    printf("\t\tYou only allowed to enter a number from 1 to 9\n");
                }
            }while(num == 0 || num > 9);
            *is_game = true;
        }
        if(position_error(str,num-1) == true){
            printf("\t\tThat index already has a value!\n");
        }else{
            break;
        }
    }while(position_error(str,num-1) == true);
    return num-1;
}

bool quit_game(){
    char userinput;
    do{
        printf("Do you want to continue(y/n): ");
        scanf(" %c", &userinput);
        userinput = tolower(userinput);
    }while(userinput != 'y' && userinput != 'n');
    if(userinput == 'y'){
        return true;
    }else{
        return false;
    }
}

void get_token(char *sym1, char *sym2, bool *sym3){
    char token;
    do{
        printf("Choice X or O: ");
        scanf(" %c", &token);
        token = toupper(token);
        error_input(token);
    }while(token != symbols[0] && token != symbols[1] && token != symbols[2]);
    if(token == symbols[0]){
        *sym1 = symbols[0];
        *sym2 = symbols[1];
        *sym3 = true;
    }else if(token == symbols[2]){
        *sym1 = 'J';
        *sym2 = 'J';
        *sym3 = false;
    }else{
        *sym1 = symbols[1];
        *sym2 = symbols[0];
        *sym3 = true;
    }
}

void play_game(char str[], char ch1, char ch2, bool is_me){
    bool isgame = true;
    isgame = is_me;
    while(isgame){
        int num1, num2;
        num1 = get_playerInput(&isgame,str,ch1);
        str[num1] = ch1;
        if(is_winner(str,ch1) == true){
            get_board(str);
            printf("\n\tPlayer 1 wins! (%c)\n\n", ch1);
            break;
        }
        num2 = get_playerInput(&isgame,str,ch2);
        str[num2] = ch2;
        if(is_winner(str,ch2) == true){
            get_board(str);
            printf("\n\tPlayer 2 wins! (%c)\n\n", ch2);
            break;
        }
    }
}

void TicTacToe_Game(char wan[]){
    bool game = true, me;
    while(game)
    {
        if(strcmp(wan, "Josuan") == 0){
            char str[] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
            char a, b;
            welcome_msg("Josuan");
            get_token(&a, &b, &me);
            printf("Player 1: %c\nPlayer 2: %c\n\n", a,b);
            play_game(str,a,b,me);
        }
        game = quit_game();
    }
}