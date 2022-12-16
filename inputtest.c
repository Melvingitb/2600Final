#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "MQTTClient.h"

#define ADDRESS     "tcp://broker.emqx.io:1883"
#define CLIENTID    "emqx_test"
#define TOPIC       "esp32/led"
#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L
char input[] = "0";
int count = 0;

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: %.*s\n", message->payloadlen, (char*)message->payload);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

int main(int argc, char* argv[])
{
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
  
    // MQTT Connection parameters
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);
    }
    
    
    //pubmsg.qos = QOS;
    //pubmsg.retained = 0;
    // Publish message
    while (count < 9){
        printf("Please enter input:\n");
        scanf("%c", input);
        //PAYLOAD = input[0];
        /*
        if (input == "1" || input == "2" || input == "3" || input == "4" || input == "5" || input == "6" || input == "7" || input == "8" || input == "9"){
            count++;
        }
        */
       if (strcmp(input, "1") == 0 ||strcmp(input, "2") == 0 ||strcmp(input, "3") == 0 ||strcmp(input, "4") == 0 ||strcmp(input, "5") == 0 ||strcmp(input, "6") == 0 ||strcmp(input, "7") == 0 ||strcmp(input, "8") == 0 ||strcmp(input, "9") == 0){
        count++;
       }
        printf("%d", count);
        pubmsg.payload = input;
        pubmsg.payloadlen = strlen(input);
        pubmsg.qos = QOS;
        pubmsg.retained = 0;
        MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
        printf("Waiting for up to %d seconds for publication of %s\n"
            "on topic %s for client with ClientID: %s\n",
            (int)(TIMEOUT/1000), input, TOPIC, CLIENTID);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);
        //printf("")
    }
    if ((rc = MQTTClient_setCallbacks(client, NULL, NULL, msgarrvd, NULL)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to set callbacks, return code %d\n", rc);
        rc = EXIT_FAILURE;
        goto destroy_exit;
    }
    printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
           "Press Q<Enter> to quit\n\n", TOPIC, CLIENTID, QOS);
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
    /*
    pubmsg.payload = PAYLOAD;
    pubmsg.payloadlen = strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
    printf("Waiting for up to %d seconds for publication of %s\n"
            "on topic %s for client with ClientID: %s\n",
            (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);

    */
  
    // Disconnect
    MQTTClient_disconnect(client, 10000);
    destroy_exit:
    MQTTClient_destroy(&client);
    exit:
    return rc;
}
}
