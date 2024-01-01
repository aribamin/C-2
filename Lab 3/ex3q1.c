/* Purpose: To play a game of Zanzibar, where two players will take turns rolling 3 randomized dice
 * Author: Arib Amin
 * Date: 2023-09-22
 * Persons discussed w/: TA's on Discord
 * References: Eclass demo C programs: rand.c, bubblesort.c
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 int main(){
    //Seeding rand using computer time, NULL because does not need to be saved
    srand(time(NULL));
    int player1_lives = 3;
    int player2_lives = 3;
    int points1 = 0;
    int points2 = 0;

    //Loop until one player's lives is 0
    while ((player1_lives != 0 && player2_lives != 0)){

        //Taking turns between player 1 and player 2        
        for (int current_player = 1; current_player <= 2; current_player++){
            
            //Playing until player uses 3 turns or breaks out using 's'
            for (int turn = 1; turn <= 3; turn++){
                
                char player_input;
                printf("Turn %d player %d: ", turn, current_player);
                scanf(" %c", &player_input);

                int dice[3] = {0, 0, 0};
                if (player_input == 'r'){
                    for (int i = 0; i < 3; i++){
                        //Random numbers from 0-5, +1 changes range to 1-6
                        dice[i] = ((rand() % 6) + 1);
                    }
                }else if (player_input == 's'){
                    //If player 1 turn 1 and 's', then set points to 0
                    if (turn == 1 && current_player == 1){
                        points1 = 0;
                    //If player 2 turn 1 and 's', then set points to 0    
                    }else if (turn == 1 && current_player == 2){
                        points2 = 0;
                    }
                    break;
                }

                //Bubble sort the dice from least to greatest
                for (int j = 0; j < 3; j++){
                    for (int k = 0; k < 2 - j; k++){
                        if (dice[k] > dice[k + 1]){
                            int temp = dice[k];
                            dice[k] = dice[k + 1];
                            dice[k + 1] = temp;
                        }
                    }
                }

                //Combinations of dice rolls and associated points
                int points = 0;
                if ((dice[0] == 4) && (dice[1] == 5) && (dice[2] == 6)){
                    points = 1000;
                }else if ((dice[0] == 1) && (dice[1] == 1) && (dice[2] == 1)){
                    points = 999;
                }else if ((dice[0] == 2) && (dice[1] == 2) && (dice[2] == 2)){
                    points = 998;
                }else if ((dice[0] == 3) && (dice[1] == 3) && (dice[2] == 3)){
                    points = 997;
                }else if ((dice[0] == 4) && (dice[1] == 4) && (dice[2] == 4)){
                    points = 996;
                }else if ((dice[0] == 5) && (dice[1] == 5) && (dice[2] == 5)){
                    points = 995;
                }else if ((dice[0] == 6) && (dice[1] == 6) && (dice[2] == 6)){
                    points = 994;
                }else if ((dice[0] == 1) && (dice[1] == 2) && (dice[2] == 3)){
                    points = 993;
                }else{
                    points = (100 * dice[2]) + (10 * dice[1]) + dice[0];
                }
                printf("You rolled: %d %d %d = %d points\n", dice[0], dice[1], dice[2], points);

                //Setting players' points for later comparison
                if (current_player == 1){
                    points1 = points;
                }else{
                    points2 = points;
                }

            }

        }

        //Comparisons for who won this round and taking away lives
        if (points1 > points2){
            player2_lives--;
            printf("Player 1 wins this round with %d points\n", points1);
        }else if (points2 > points1){
            player1_lives--;
            printf("Player 2 wins this round with %d points\n", points2);
        }else{
            printf("Both players tied this round with %d points\n", points1);
        }
        printf("Player 1 lives = %d\nPlayer 2 lives = %d\n\n", player1_lives, player2_lives);
        
    }

    //Determining winner after game ends
    if (player1_lives > player2_lives){
        printf("Player 1 wins!\n");
    }else{
        printf("Player 2 wins!\n");
    }

    return 0;
 }