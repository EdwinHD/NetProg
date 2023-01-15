#include <iostream>
#include <cstring>
#include <unistd.h> 
#include <arpa/inet.h>
using namespace std;
void Exception(const string & why, const int exitCode ){ // Исключения (возможные ошибки)
    cout << "ErrorCode:"<<exitCode <<endl<< why << endl;
    exit(exitCode);
}
int main(){

    // структура с адресом нашей программы (клиента)
    sockaddr_in * selfAddr = new (sockaddr_in);
    selfAddr->sin_family = AF_INET; // интернет протокол IPv4
    selfAddr->sin_port = 0;
    selfAddr->sin_addr.s_addr = 0;

    // структура с адресом "на той стороне" (сервера)
    sockaddr_in * remoteAddr = new (sockaddr_in);
    remoteAddr->sin_family = AF_INET;     // интернет протокол IPv4
    remoteAddr->sin_port = htons(44214);  // порт
    remoteAddr->sin_addr.s_addr = inet_addr("127.0.0.1"); //  адрес 

    // буфер для передачи и приема данных
    char *buffer = new char[4096];
    strcpy(buffer,"Дата и время:");   //копируем строку
    int msgLen = strlen(buffer);      //вычисляем длину строки

    // создаём сокет
    int mySocket = socket(AF_INET, SOCK_DGRAM, 0); //udp протокол
    if (mySocket == -1) {
        close(mySocket);                           //закрываем сокет
        Exception("Ошибка открытия сокета",11);
    }
    //связываем сокет с адрессом
    int socaddr = bind(mySocket,(const sockaddr *) selfAddr, sizeof(sockaddr_in));
    if (socaddr == -1) {
        close(mySocket);                            //закрываем сокет если сокет не привязался
        Exception("Ошибка привязки сокета с локальным адресом",12);
    }

    //установливаем соединение
    socaddr = connect(mySocket, (const sockaddr*) remoteAddr, sizeof(sockaddr_in));
    if (socaddr == -1) {
        close(mySocket);                            //закрываем сокет если соединение не установилось
        Exception("Ошибка подключения сокета к удаленному серверу.", 13);
    }

    // передаём сообщение из буффера
    socaddr = send(mySocket, buffer, msgLen, 0);
    if (socaddr == -1) {
        close(mySocket);                          
        Exception("Сообщение об ошибке отправки", 14);
    }
    cout << "Мы отправляем запрос на  " << buffer << endl;

    // принимаем ответ в буффер
    socaddr = recv(mySocket, buffer, 4096, 0);
    if (socaddr == -1) {
        close(mySocket);                            //закрываем сокет если не получен ответ из буффера
        Exception("Ошибка получения ответа.", 15);
    }
    buffer[socaddr] = '\0'; // конец принятой строки
    cout << "Мы получаем: " << buffer << endl;      // вывод полученного сообщения от сервера
    close(mySocket);                                // закрываем сокет

    delete selfAddr;                //очищаем все переменные после работы
    delete remoteAddr;
    delete[] buffer;
    return 0;
}