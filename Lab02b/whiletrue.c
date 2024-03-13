#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * whiletrue() {
        while(1) {continue;}
}

int main(int argc, char* argv[]){
        int num = strtol(argv[1], NULL, 10);

        pthread_t * thread_array = malloc(num * sizeof(pthread_t));
        for(int i = 0; i < num; i++) {
                pthread_create(&thread_array[i], NULL, whiletrue, NULL);
        }

        for(int i = 0; i < num; i++) {
                pthread_join(thread_array[i], NULL);
        }

        return 0;
}
