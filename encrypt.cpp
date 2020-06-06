#include <iostream>
#include <fstream>
#include <cstring>
#define BUFFLIMIT 8

int main(int argc, char* argv[]){
    if(argc!=2){
        std::cout << "[?] Usage: [./file] [filename/filepath]\n";
        exit(1);
    }
    std::fstream mfile(argv[1], std::ios::in|std::ios::out|std::ios::binary);
    // get size;
    mfile.seekg(0, std::ios::end);
    unsigned int fsize = mfile.tellg();
    std::cout << "[*] file size: " << fsize << std::endl;
    unsigned blockN = fsize / BUFFLIMIT;
    // getting number of blocks on size 8; meaning every line will only have 8 characters or bits
    if(fsize % BUFFLIMIT != 0){++blockN;}
    std::cout << "[*] Number of blocks: " << blockN << std::endl;
    // file position
    mfile.seekg(std::ios::beg);
    unsigned int filePos = mfile.tellg();
    // start position
    std::cout << "position: " << filePos << std::endl;
    // variable for every line of text
    char data[BUFFLIMIT];
    std::cout << "[+] Encrypting.\n";
    for(int i=0;i<blockN;i++){
        mfile.seekg(filePos);
        mfile.read(data, BUFFLIMIT);
        // std::cout << i << ": " << data << std::endl;
        // write
        mfile.seekp(filePos);
        for(int i=0;i<8;i++){
            data[i] = ((int)data[i] * -1);
        }
        mfile.write(data, BUFFLIMIT);
        // std::cout << i << ": " << data << std::endl;
        memset(&data, 0, sizeof(data));
        filePos+=BUFFLIMIT;
    }
    std::cout << "[+] Encryption success.\n";
    mfile.close();
}
