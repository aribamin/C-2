/* Purpose: To intake input file containing crops destroyed or crops survived and then calculating net profit
 * Author: Arib Amin
 * Date: 2023-09-30
 * Persons discussed w/: 
 * References: 
 */

#include <stdio.h>
int main(){
    char crops = ' ';
    double cost = 0;
    double profit = 0;
    double net_profit = 0;

    //Loop until character isn't end of file or new line
    while (crops != EOF && crops != '\n'){
        //Get character
        crops = getchar();

        //If character equals '/', it means next character is a surviving crop
        if (crops == '/'){
            //Get next character (The crop after '/')
            crops = getchar();
            switch(crops){
                case 'C':
                    cost += 0.05;
                    profit += 0.50;
                    break;
                case 'T':
                    cost += 0.25;
                    profit += 1.25;
                    break;
                case 'P':
                    cost += 0.70;
                    profit += 3.00;
                    break;
                case 'L':
                    cost += 0.30;
                    profit += 1.00;
                    break;
            }
        //If character equals '#', it means next character is destroyed crop
        }else if (crops == '#'){
            //Get next character (The crop after '#')
            crops = getchar();
            switch(crops){
                case 'C':
                    cost += 0.05;
                    break;
                case 'T':
                    cost += 0.25;
                    break;
                case 'P':
                    cost += 0.70;
                    break;
                case 'L':
                    cost += 0.30;
                    break;
            }
        }
    }

    //Calculating net profit (Profit - Cost)
    net_profit = profit - cost;
    if (net_profit >= 0) {
        printf("Net profit: $%.2f\n", net_profit);
    } else {
        printf("Net profit: -$%.2f\n", -net_profit);
    }

    return 0;
}