#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

static void * func1_thread(void *arg){
    while(!(* (bool*) arg)){
        cout << "1";
        fflush(stdout);
        sleep(1);
    }
}

static void * func2_thread(void *arg){
    while(!(* (bool*) arg)){
        cout << "2";
        fflush(stdout);
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    bool thread1_ended = 0;
    bool thread2_ended = 0;

    pthread_t thread1;
    pthread_t thread2;

    if ( pthread_create( &thread1, NULL, func1_thread, &thread1_ended ) )
            return 1;
    if ( pthread_create( &thread2, NULL, func2_thread, &thread2_ended ) )
            return 1;

    getchar();
    thread1_ended = 1;
    thread2_ended = 1;

    if ( pthread_join( thread1, NULL ) )
            return 1;
    if ( pthread_join( thread2, NULL ) )
            return 1;

    return 0;
}
