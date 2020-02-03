#include<iostream>
#include<thread>
#include<unistd.h>
#include<vector>
#include<mutex>

using namespace std;
#define bnd() (usleep(252306))

class Semaphore{
    
public:
    std::mutex seb;
    
    Semaphore(int value) {
        if(value == 0) {
            seb.lock();
        }
    }
    
    void wait() {
        seb.lock();
        
    }
    
    void signal() {
        seb.unlock();
    }
};
Semaphore mtx(1);
Semaphore oxyQueue(0);
Semaphore hydroBonded(0);
Semaphore hydroQueue(0);

int oxygen = 0;
int hydrogen = 0;

void oxygen_func(int i);
void hydrogen_func(int i);

int main(int argc, char** argv) {
    int num_ox, num_hy;
    
    num_ox = stoi(argv[1]);
    num_hy = stoi(argv[2]);
    
    std::thread t[num_ox+num_hy];
    
    int oxindex = num_ox;
    int hyindex = num_hy;
    
    int oxindex2 = num_ox;

    int hyindex2 = num_hy;
    
    
    while(oxindex-1 >= 0 || hyindex-1>= 0) {
        
        if(oxindex-1 >= 0) {
            t[oxindex-1] = thread(oxygen_func, oxindex-1);
            oxindex--;
        }
        if(hyindex-1 >= 0) {
            t[num_ox+hyindex-1] = thread(hydrogen_func, hyindex-1);
            hyindex--;
        }
        
    }
    
    while(oxindex2-1 >= 0 || hyindex2-1 >= 0) {
        srand (time(NULL));
        
        if(oxindex2-1 >= 0) {
            int timer = rand() % 2000000;
            usleep(timer);
            t[oxindex2-1].join();
            oxindex2--;
        }
        if(hyindex2-1 >= 0) {
            int timer = rand() % 2000000;
            usleep(timer);
            t[num_ox + hyindex2-1].join();
            hyindex2--;
        }
        
    }
    
}
void oxygen_func(int i){
    mtx.wait();
    oxygen++;
    if (hydrogen >= 2){
        
        cout << "Oxygen " << i+1 << ": " <<  oxygen << " oxygen atoms and " <<  hydrogen <<  " hydrogen atoms are waiting, so I signal the next oxygen and hydrogen atoms in the queue." << "\n";
        hydroQueue.signal();
        hydrogen -= 2;
        oxygen--;
    
    }
    else{
        cout << "Oxygen " << i+1 << ": No available hydrogen atoms, so I wait. There are other " << oxygen << " oxygen atoms and " << hydrogen << " atoms are waiting. " << "\n";
        mtx.signal();
        oxyQueue.wait();
        
    }
    cout << "Oxygen " << i+1 << ": We are bonding together now." << "\n";
    
    usleep(500000);
    hydroBonded.wait();
    mtx.signal();
    cout << "I have bonded with two hydrogen atoms, and become a water molecule." << "\n";
    
}

void hydrogen_func(int i){
    mtx.wait();
    hydrogen++;
    if (hydrogen >= 2 && oxygen >= 1){
        cout << "Hydrogen " << i+1 << ": " << oxygen << " oxygen atoms and "<< hydrogen <<" hydrogen atoms are waiting, so I signal the next oxygen and hydrogen atoms in the queue." << "\n";
        hydrogen -= 2;
        hydroQueue.signal();
        oxygen -= 1;
        oxyQueue.signal();
        
    }
    else{
        cout << "Hydrogen " << i+1 << ": No available hydrogen or oxygen atoms, so I wait. There are other " << oxygen << " oxygen atoms and "<< hydrogen << " hydrogen atoms are waiting." << "\n";
        mtx.signal();
    }
    hydroQueue.wait();
    cout << "Hydrogen " << i+1 << ": We are bonding together now." << "\n";
    
    usleep(500000);
    bnd();
    hydroBonded.signal();
}




