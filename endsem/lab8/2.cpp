#include <bits/stdc++.h>
#include <sys/ipc.h>
#include <sys/msg.h>

const int MAX_TEXT = 100;
#define client_key 2012
#define server_key 2008

using namespace std;

struct Message {
    long type;
    char text[MAX_TEXT];
};

void server() {
    int clientQ = msgget(client_key, IPC_CREAT | 0666);
    int serverQ = msgget(server_key, IPC_CREAT | 0666);

    if (clientQ == -1 || serverQ == -1) {
        cout<<"OOpsies while creating server :(\n";
        return;
    }

    Message msg;

    while(true) {
        msgrcv(serverQ, &msg, sizeof(msg.text), 1, 0);

        cout<<"Server got: "<<msg.text<<endl;

        Message res;
        res.type = 1;
        // res.text = "Yo the server heard what you said homie, you said: "+msg.text;
        strncpy(res.text, "yo", MAX_TEXT);
        msgsnd(clientQ, &res, sizeof(res.text), 0);
    }

}

void client(char body[]) {
    int clientQ = msgget(client_key, IPC_CREAT | 0666);
    int serverQ = msgget(server_key, IPC_CREAT | 0666);

    Message msg;
    msg.type = 1;
    strncpy(msg.text, body, MAX_TEXT);

    msgsnd(serverQ, &msg, sizeof(msg.text), 0);

    msgrcv(clientQ, &msg, sizeof(msg.text), 1, 0);
    
}

int main() {
    cout<<"Choice 0 server 1 client: ";
    int n;
    cin>>n;
    if (n) {
        char message[MAX_TEXT];
        cout<<"enter: ";
        cin>>message;
        client(message);
    }
    else{
        server();
    }
}