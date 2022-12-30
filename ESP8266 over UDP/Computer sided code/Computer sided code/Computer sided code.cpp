#include <string>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")
using namespace std;
char pkt[2000];
boolean cube[10][10][10][2];
int main() {
    while (1) {
        for (int c = 0; c < 2; c++) {
            for (int x = 0; x < 10; x++) {
                for (int y = 0; y < 10; y++) {
                    for (int z = 0; z < 10; z++) {

                        cube[x][y][z][c] = 1;

                        for (int x = 0; x < 10; x++) {
                            for (int y = 0; y < 10; y++) {
                                for (int z = 0; z < 10; z++) {
                                    for (int c = 0; c < 2; c++) {
                                        if (cube[x][y][z][c] == 1) {
                                            pkt[(x * 200 + y * 20 + z * 2 + c)] = '1';
                                        }
                                        else {
                                            pkt[(x * 200 + y * 20 + z * 2 + c)] = '0';
                                        }
                                    }
                                }
                            }
                        }
                        std::cout << "X=" << x << " Y=" << y << " Z=" << z << " C=" << c << "\n";
                        const char* srcIP = "localHost";
                        const char* destIP = "192.168.100.60";                              //IP of the esp8266
                        sockaddr_in dest;
                        sockaddr_in local;
                        WSAData data;
                        WSAStartup(MAKEWORD(2, 2), &data);

                        local.sin_family = AF_INET;
                        inet_pton(AF_INET, srcIP, &local.sin_addr.s_addr);
                        local.sin_port = htons(0);

                        dest.sin_family = AF_INET;
                        inet_pton(AF_INET, destIP, &dest.sin_addr.s_addr);
                        dest.sin_port = htons(8888);                                        //Port of the UDP server

                        SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
                        bind(s, (sockaddr*)&local, sizeof(local));

                        sendto(s, pkt, strlen(pkt), 0, (sockaddr*)&dest, sizeof(dest));

                        closesocket(s);
                        WSACleanup();

                        Sleep(1);
                        cube[x][y][z][c] = 0;
                    }
                }
            }
        }

    }
    return 0;
}
