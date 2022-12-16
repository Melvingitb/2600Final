#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "MQTTClient.h"

#define ADDRESS     "tcp://broker.emqx.io:1883"
#define CLIENTID    "emqx_test"
#define TOPIC       "esp32/led"
#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L
char input[] = "0";
int count = 0;

void prntbrd();

char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
int playing = 1; //1 = playing, 0 = game ended
int terminate = 1; //1 = still going, 0 = terminate program
char input1[] = "00";
char input2[] = "00";

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    //printf("Message arrived\n");
    //printf("     topic: %s\n", topicName);
    printf("message: \n%.*s\n", message->payloadlen, (char*)message->payload);

    
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

int main(int argc, char* argv[]){
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    //MQTTClient_setCallbacks(client, NULL, NULL, msgarrvd, NULL);
    //MQTTClient_subscribe(client, TOPIC, QOS);
    int rc;

    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    
    MQTTClient_setCallbacks(client, NULL, NULL, msgarrvd, NULL);
    MQTTClient_subscribe(client, TOPIC, QOS);
  
    // MQTT Connection parameters
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);
    }
    
    int choice = 1;
    //char input1[] = "00";
    //char input2[] = "00";
    int move1, move2; //holds the players choices and moves
    int player = 1; //keeps track of which player is making a move
    int tie = 1; // keeps track if there is a tie, 0 = no tie, 1 = tie
    int taken = 0; //keeps track if a spot is taken for the computer's turn, 1 = not taken, 0 = taken
    time_t t;
    srand((unsigned) time(&t));

    //loop continues until user would like to stop playing
    while (terminate == 1){
        //prompt user for game they wish to play

        printf("\n================================");
        printf("\nWELCOME TO TIC TAC TOE!");

        if (choice == 1){
            printf("\n================================");

            //Have a loop that continues to display the board until a winner or tie occurs
            while (playing == 1){
                prntbrd();

                printf("\nPlayer%d: make your move\n", player);

                if(player % 2 == 1){
                    printf("Waiting on ESP32 Input...\n\n"
           "Press Q<Enter> to quit\n\n");
    if ((rc = MQTTClient_subscribe(client, TOPIC, QOS)) != MQTTCLIENT_SUCCESS)
    {
    	printf("Failed to subscribe, return code %d\n", rc);
    	rc = EXIT_FAILURE;
    }
    else
    {
    	int ch;
    	do
    	{
        	ch = getchar();
    	} while (ch!='Q' && ch != 'q');
                }
                player++;
                terminate = 0;
                playing = 0;
                }
                else{
                    scanf("%d %d", &move1, &move2);
                }

                //scanf("%d %d", &move1, &move2);

                //verify user input and determine which player is which
                if(player % 2 == 1 && board[move1 - 1][move2 - 1] == ' '){
                    board[move1 - 1][move2 - 1] = 'X';
                    printf("\nGood!");
                    player++;
                }
                else if (board[move1 - 1][move2 - 1] == ' '){
                    board[move1 - 1][move2 - 1] = 'O';
                    printf("\nGood!");
                    player--;
                }
                else{
                    printf("\ninvalid move, please try again");
                }

                //loops and checks if any player has won
                for (int i = 0; i < 3; i++){
                    if (board[i][0] != ' ' && board[i][1] != ' ' && board[i][2] != ' '){
                        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]){
                            if (player % 2 == 1){
                                prntbrd();
                                printf("\nPlayer 2 wins!");
                                playing = 0;
                            }
                            else{
                                prntbrd();
                                printf("\nPlayer 1 wins!");
                                playing = 0;
                            }
                        }
                    }
                }
                //checks vertically
                for (int i = 0; i < 3; i++){
                    if (board[0][i] != ' ' && board[1][i] != ' ' && board[2][i] != ' '){
                        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]){
                            if (player % 2 == 1){
                                prntbrd();
                                printf("\nPlayer 2 wins!");
                                playing = 0;
                            }
                            else{
                                prntbrd();
                                printf("\nPlayer 1 wins!");
                                playing = 0;
                            }
                        }
                    }
                }
                //checks diagonal case 1
                if (board[0][0] != ' ' && board[1][1] != ' ' && board[2][2] != ' '){
                    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]){
                        if (player % 2 == 1){
                            prntbrd();
                            printf("\nPlayer 2 wins!");
                            playing = 0;
                            }
                        else{
                            prntbrd();
                            printf("\nPlayer 1 wins!");
                            playing = 0;
                        }
                    }
                }
                //checks diagonal case 2
                if (board[0][2] != ' ' && board[1][1] != ' ' && board[2][0] != ' '){
                    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]){
                        if (player % 2 == 1){
                            prntbrd();
                            printf("\nPlayer 2 wins!");
                            playing = 0;
                            }
                        else{
                            prntbrd();
                            printf("\nPlayer 1 wins!");
                            playing = 0;
                        }
                    }
                }

                //checks if there is tie
                for (int i = 0; i < 3; i++){
                    for (int j = 0; j < 3; j++){
                        if (board[i][j] == ' '){
                            tie = 0;
                        }
                    }
                }
                //if tie, end game
                if (tie == 1 && playing == 1){
                    prntbrd();
                    printf("\nTie, no winner!");
                    playing = 0;
                }

                tie = 1;
            }

        }
        else{
            printf("\ninvalid input");
        }


        //Ends game and asks if player would like to play again
        printf("\nWould you like to play again?\n0 = No\n1 = Yes");
        scanf("%d", &terminate);

        //restarts game if player wants to play again
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                board[i][j] = ' ';
            }
        }

        playing = 1;
        player = 1;
        tie = 0;
        }

    return 0;
}

void prntbrd(){
    printf("\nThe current status is: ");
    printf("\n+-----------+");
    printf("\n| %c | %c | %c |", board[0][0], board[0][1], board[0][2]);
    printf("\n+-----------+");
    printf("\n| %c | %c | %c |", board[1][0], board[1][1], board[1][2]);
    printf("\n+-----------+");
    printf("\n| %c | %c | %c |", board[2][0], board[2][1], board[2][2]);
    printf("\n+-----------+");

}