
#include<iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <time.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
using namespace std::literals::chrono_literals;
#define SONGUOI 5
#define THUCAN 500
#define DELAY 5000
void *Active (void *id);
void cam_dua (int,int,char *);
void tra_dua (int,int);
int food_con_lai ();

pthread_mutex_t chopstick[SONGUOI];
pthread_t philo[SONGUOI];
pthread_mutex_t food_lock;
int sleep_thread = 0;
int count1 =1;

int main (int argn,char **argv)
{   auto start = steady_clock::now();
    int i;
    
    
    if (argn == 2)
        sleep_thread = atoi (argv[1]);

    pthread_mutex_init (&food_lock, NULL);
    
    for (i = 0; i < SONGUOI; i++)
        pthread_mutex_init (&chopstick[i], NULL);
    for (i = 0; i < SONGUOI; i++)
        pthread_create (&philo[i], NULL, Active, (void*)i);
    for (i = 0; i < SONGUOI; i++)  
        pthread_join (philo[i], NULL);   
        
    
    cout<<"Thoi gian ngu: "<<sleep_thread<<endl;
    cout<<"so thuc an ban dau: "<<THUCAN<<endl;
    cout<<"so thuc an da dung: "<<count1<<endl;
    cout<<"Thuc an da het => KET THUC "<<endl;
    auto end = steady_clock::now();
    duration<double, std::milli> elapsed1 = end - start;
    std::cout << "Thoi gian thuc thi = " << elapsed1.count() << "ms\n"<<endl;
 
}

void *Active (void *num)
{
    int id;
    int i, left_chopstick, right_chopstick,left_chopstick1,right_chopstick1,f;

    id = (long)num;
    cout<<"Nguoi thu "<< id << " da san sang an."<<endl;
    right_chopstick = id;
    left_chopstick = id + 1;
    

    /* Wrap around the chopsticks. */
    if (left_chopstick == SONGUOI)
        left_chopstick = 0;

    while (f = food_con_lai ()) {

        
        if (id == 1)
        {}
        else{
        cam_dua (id, left_chopstick, "trai");
        cam_dua (id, right_chopstick, "phai");
        cout<<"Nguoi thu "<<id<<" dang an."<<endl;
        usleep (DELAY*(THUCAN - f +1) );
        tra_dua (right_chopstick,left_chopstick);}
        cout<<"Food on table:"<<f<<endl;  
        count1++;
        
      
    
    }
    
    cout<<"Nguoi thu "<< id << " da an XONG."<<endl;
    
    return (NULL);
    
}

int
food_con_lai ()
{
    static int food = THUCAN;
    int myfood;

    pthread_mutex_lock (&food_lock);
    if (food > 0) {
        food--;
        //cout<<"Food on table:"<<food<<endl;  
    }
    myfood = food;
    pthread_mutex_unlock (&food_lock);
    //cout<<"Thuc an con lai: "<<myfood<<endl;
    return food;  
}

void
cam_dua (int phil,int c,char *hand)
{
    pthread_mutex_lock (&chopstick[c]);
    cout<<"Nguoi thu "<<phil<<" co dua "<<hand<< c<<endl;
}

void
tra_dua (int c1,int c2)
{
    pthread_mutex_unlock (&chopstick[c1]);
    pthread_mutex_unlock (&chopstick[c2]);
    //end1 = clock();
}

