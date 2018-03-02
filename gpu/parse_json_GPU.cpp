#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>


int main(int argc, char **argv)
{
   char inputFile[25];
   FILE *inPtr, *outPtr;
   char aux[10][25], timeStamp[3][30], dev_name[4][10], Tparse[4][4];
   int sensorData[5], dev_n[2], usage[4], stime[4], ctime[4], timems = 0;
   float memory[6];

   if(argc > 1)
   {
      strcpy(inputFile, argv[1]);
   }
   else
   {
      strcpy(inputFile, "sensor.out");
   }

   inPtr = fopen(inputFile, "rt");
   if(inPtr==NULL)
   {
      printf("Falha na abertura");
      return 1;
   }

   outPtr = fopen("parsed.json", "wt");
   if(outPtr==NULL)
   {
      printf("Falha na abertura");
      return 1;
   }

   fscanf(inPtr, "%s %s", aux[0], timeStamp[0]);
   fscanf(inPtr, "%s %d", aux[9], &sensorData[4]);
   fscanf(inPtr, "%s %s %d", aux[1], aux[2], &sensorData[0]);
   fscanf(inPtr, "%s %s %d", aux[3], aux[4], &sensorData[1]);
   fscanf(inPtr, "%s %s %d", aux[5], aux[6], &sensorData[2]);
   fscanf(inPtr, "%s %s %d", aux[7], aux[8], &sensorData[3]);

   fscanf(inPtr, "%s", timeStamp[1]);

   Tparse[0][0] = timeStamp[1][0];
   Tparse[0][1] = timeStamp[1][1];
   Tparse[0][2] = '\0';
   stime[0] = ctime[0] = atoi(Tparse[0]);
   Tparse[1][0] = timeStamp[1][3];
   Tparse[1][1] = timeStamp[1][4];
   Tparse[1][2] = '\0';
   stime[1] = ctime[1] = atoi(Tparse[1]);
   Tparse[2][0] = timeStamp[1][6];
   Tparse[2][1] = timeStamp[1][7];
   Tparse[2][2] = '\0';
   stime[2] = ctime[2] = atoi(Tparse[2]);
   Tparse[3][0] = timeStamp[1][9];
   Tparse[3][1] = timeStamp[1][10];
   Tparse[3][2] = timeStamp[1][11];
   Tparse[3][3] = '\0';
   stime[3] = ctime[3] = atoi(Tparse[3]);

   aux[2][0] = tolower(aux[2][0]);
   aux[4][0] = tolower(aux[4][0]);
   aux[6][0] = tolower(aux[6][0]);
   aux[8][0] = tolower(aux[8][0]);

   timems = (3600000*(ctime[0]-stime[0]))+(60000*(ctime[1]-stime[1]))+(1000*(ctime[2]-stime[2]))+(ctime[3]-stime[3]);  

   fscanf(inPtr, "%s %s", dev_name[0], dev_name[1]);
   fscanf(inPtr, "%d", &dev_n[0]);
   fscanf(inPtr, "%f %f %f", &memory[0], &memory[1], &memory[2]);
   fscanf(inPtr, "%d %d", &usage[0], &usage[1]);

   fscanf(inPtr, "%s", timeStamp[2]);
   fscanf(inPtr, "%s %s", dev_name[2], dev_name[3]);
   fscanf(inPtr, "%d", &dev_n[1]);
   fscanf(inPtr, "%f %f %f", &memory[3], &memory[4], &memory[5]);
   fscanf(inPtr, "%d %d", &usage[2], &usage[3]);


   fprintf(outPtr,"[\n");

 fprintf(outPtr,"{\"%s\": %d, \"%s_%s\": %d, \"%s_%s\": %d, \"%s_%s\": %d, \"core0_usage\": %d, \"memory0_usage\": %d, \"%s_%s\": %d, \"core1_usage\": %d, \"memory1_usage\": %d, \"%s\": %d}, \n",aux[0], timems, "cpu0",aux[2], sensorData[0], "cpu1",aux[4], sensorData[1], "gpu0",aux[6], sensorData[3], usage[1], usage[0], "gpu1",aux[8], sensorData[2],usage[3], usage[2], aux[9], sensorData[4]);

   while(!feof(inPtr))
   {
      fscanf(inPtr, "%s %s", aux[0], timeStamp[0]);
      fscanf(inPtr, "%s %d", aux[9], &sensorData[4]);
      fscanf(inPtr, "%s %s %d", aux[1], aux[2], &sensorData[0]);
      fscanf(inPtr, "%s %s %d", aux[3], aux[4], &sensorData[1]);
      fscanf(inPtr, "%s %s %d", aux[5], aux[6], &sensorData[2]);
      fscanf(inPtr, "%s %s %d", aux[7], aux[8], &sensorData[3]);

      fscanf(inPtr, "%s", timeStamp[1]);
      fscanf(inPtr, "%s %s", dev_name[0], dev_name[1]);
      fscanf(inPtr, "%d", &dev_n[0]);
      fscanf(inPtr, "%f %f %f", &memory[0], &memory[1], &memory[2]);
      fscanf(inPtr, "%d %d", &usage[0], &usage[1]);

      fscanf(inPtr, "%s", timeStamp[2]);
      fscanf(inPtr, "%s %s", dev_name[2], dev_name[3]);
      fscanf(inPtr, "%d", &dev_n[1]);
      fscanf(inPtr, "%f %f %f", &memory[3], &memory[4], &memory[5]);
      fscanf(inPtr, "%d %d", &usage[2], &usage[3]);

      aux[2][0] = tolower(aux[2][0]);
      aux[4][0] = tolower(aux[4][0]);
      aux[6][0] = tolower(aux[6][0]);
      aux[8][0] = tolower(aux[8][0]);


      Tparse[0][0] = timeStamp[1][0];
      Tparse[0][1] = timeStamp[1][1];
      Tparse[0][2] = '\0';
      ctime[0] = atoi(Tparse[0]);
      Tparse[1][0] = timeStamp[1][3];
      Tparse[1][1] = timeStamp[1][4];
      Tparse[1][2] = '\0';
      ctime[1] = atoi(Tparse[1]);
      Tparse[2][0] = timeStamp[1][6];
      Tparse[2][1] = timeStamp[1][7];
      Tparse[2][2] = '\0';
      ctime[2] = atoi(Tparse[2]);
      Tparse[3][0] = timeStamp[1][9];
      Tparse[3][1] = timeStamp[1][10];
      Tparse[3][2] = timeStamp[1][11];
      Tparse[3][3] = '\0';
      ctime[3] = atoi(Tparse[3]);

      timems = (3600000*(ctime[0]-stime[0]))+(60000*(ctime[1]-stime[1]))+(1000*(ctime[2]-stime[2]))+(ctime[3]-stime[3]);

      fprintf(outPtr,"{\"%s\": %d, \"%s_%s\": %d, \"%s_%s\": %d, \"%s_%s\": %d, \"core0_usage\": %d, \"memory0_usage\": %d, \"%s_%s\": %d, \"core1_usage\": %d, \"memory1_usage\": %d, \"%s\": %d}", aux[0], timems, "cpu0",aux[2], sensorData[0], "cpu1",aux[4], sensorData[1], "gpu0",aux[6], sensorData[3], usage[1], usage[0], "gpu1",aux[8], sensorData[2],usage[3], usage[2], aux[9], sensorData[4]);
      fprintf(outPtr, feof(inPtr) ? "] \n" : ", \n");
   }

   fclose(inPtr);
   fclose(outPtr);

   return 0;
}
