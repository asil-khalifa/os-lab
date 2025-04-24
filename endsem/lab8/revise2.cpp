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
    
    int serverQ = msgget(server_key, IPC_CREAT | 0666);
    int clientQ = msgget(client_key, IPC_CREAT | 0666);

    Message msg;
    msg.type = 1;

    while(true) {
        msgrcv(serverQ, &msg, sizeof(msg.text), 1, 0);

        cout<<"Server got request: "<<msg.text<<endl;
        char res[] = "YOOOO";
        strncpy(msg.text, res, MAX_TEXT);

        msgsnd(clientQ, &msg, sizeof(msg.text), 0);
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
    cout<<"Received from server: "<<msg.text<<endl;

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