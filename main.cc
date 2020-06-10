#include <iostream>
#include <fstream>
#include <stdint.h>
using namespace std;

void printDiskSignature(unsigned int *buffer) {
    printf("\nDisk Signature: ");
    for (int i = 440; i < 446; i++) {
      printf("%02X ", buffer[i]);
    }
    printf(" (hex)\n");
}

void printPartition(unsigned int *buffer, int partitionNumber) {
    printf("\nPartition Number: %u (hex)\n", partitionNumber);
    int start = 446 + 16 * partitionNumber;
    if (buffer[start+4]) {
        printf("- status: %02X\n", buffer[start]);
        printf("- starting head: %u (decimal)\n", buffer[start+1]);
        printf("- starting sector: %u (decimal)\n", buffer[start+2]&63);
        printf("- starting cylinder: %u (decimal)\n", ((buffer[start+2]&192) << 2) + buffer[start+3]);
        printf("- partition type: %02X (hex)\n", buffer[start+4]);
        printf("- ending head: %u (decimal)\n", buffer[start+5]);
        printf("- ending sector: %u (decimal)\n", buffer[start+6]&63);
        printf("- ending cylinder: %u (decimal)\n", ((buffer[start+6]&192) << 2) + buffer[start+7]);
        printf("- relative start sector: ");
        for (int i = start+8; i < start+12; i++) {
          printf("%02X ", buffer[i]);
        }
        printf("(hex)\n- total sectors: ");
        for (int i = start+12; i < start+16; i++) {
          printf("%02X ", buffer[i]);
        }
        printf("(hex)\n");
    } else {
        printf("- partition type: empty\n");
    }
}

int main (int argc, char * argv[]) {
  char buffer[512];
  printf("\nDevice File: %s", argv[1]);
  ifstream myFile(argv[1], ios::in | ios::binary);
  myFile.read(buffer, 512);

  // convert to unsigned int
  unsigned int bbuffer[512];
  for (int i = 0; i < 512; i++) {
    bbuffer[i] = (unsigned int)(unsigned char)buffer[i];
  }

  printDiskSignature(bbuffer);
  printPartition(bbuffer, 0);
  printPartition(bbuffer, 1);
  printPartition(bbuffer, 2);
  printPartition(bbuffer, 3);
  printf("\n");
  return 0;
}
