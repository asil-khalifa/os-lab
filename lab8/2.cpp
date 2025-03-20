#include <bits/stdc++.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <unistd.h>

#define SERVER_QUEUE_KEY 1234
#define CLIENT_QUEUE_KEY 5678
#define MAX_TEXT 512

using namespace std;

struct Message {
    long type;
    char text[MAX_TEXT];
};

void server() {
    int serverQueue = msgget(SERVER_QUEUE_KEY, IPC_CREAT | 0666);
    int clientQueue = msgget(CLIENT_QUEUE_KEY, IPC_CREAT | 0666);
    
    if (serverQueue == -1 || clientQueue == -1) {
        cerr << "Error creating message queues." << endl;
        return;
    }
    
    Message msg;
    while (true) {
        if (msgrcv(serverQueue, &msg, sizeof(msg.text), 1, 0) == -1) {
            cerr << "Error receiving message." << endl;
            continue;
        }
        
        cout << "Server received: " << msg.text << endl;
        string response = "Processed: " + string(msg.text);
        strncpy(msg.text, response.c_str(), MAX_TEXT);
        msg.type = 1;
        
        if (msgsnd(clientQueue, &msg, sizeof(msg.text), 0) == -1) {
            cerr << "Error sending response." << endl;
        }
    }
}

void client(const string& request) {
    int serverQueue = msgget(SERVER_QUEUE_KEY, 0666);
    int clientQueue = msgget(CLIENT_QUEUE_KEY, 0666);
    
    if (serverQueue == -1 || clientQueue == -1) {
        cerr << "Error accessing message queues." << endl;
        return;
    }
    
    Message msg;
    msg.type = 1;
    strncpy(msg.text, request.c_str(), MAX_TEXT);
    
    if (msgsnd(serverQueue, &msg, sizeof(msg.text), 0) == -1) {
        cerr << "Error sending message." << endl;
        return;
    }
    
    if (msgrcv(clientQueue, &msg, sizeof(msg.text), 1, 0) == -1) {
        cerr << "Error receiving response." << endl;
        return;
    }
    
    cout << "Client received: " << msg.text << endl;
}

int main() {
    string choice;
    cout<<"Enter server or client: ";
    cin>>choice;

    if (choice == "server")
        server();
    else if (choice == "client"){
        cout<<"Enter message: ";
        string msg;
        cin>>msg;
        client(msg);
    }else {
        cout<<"Invalid!\n";
    }
    
    
    return 0;
}
