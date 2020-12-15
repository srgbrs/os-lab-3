//
//  main.cpp
//  os_lab3
//
//  Created by Sergey on 02.12.2020.
//

#include <iostream>
#include <unistd.h>
#include <queue>
#include <list>
using namespace std;

struct Task {
    int duration;
    int Id;
    int priority;
    int waiting;
    
public:
    Task(int id, int dur, int pr) {
        this->Id = id;
        this->duration = dur;
        this->priority = pr;
        this->waiting;
    }
    
    Task();
    
    void Show() {
        cout << "TaskId:" << Id;
        cout << " Priority:" << priority;
        cout << " Duration: " << duration;
        cout << endl;
    }
    
    void ShowWithWaiting() {
        cout << "TaskId:" << Id;
        cout << " Priority:" << priority;
        cout << " Duration: " << duration;
        cout << " ---waiting: " << waiting;
        cout << endl;
    }
    
    int getDuration(int Id) {
        return this->duration;
    }
    int getPriority(int Id) {
        return this->priority;
    }
    
    void SetDuration(int Id) {
        
    }
    void SetWaiting(int wait) {
        this->waiting = wait;
    }
};

struct Comparator
{
    bool operator ()(const Task & a, const Task & b)
    {
        return a.priority < b.priority;
    }
};


class TaskSheduler {
public:
    //priority_queue<Task,Task,compare> tasks;
    list<Task> li;
    vector<Task> tas;
    TaskSheduler() {
        for (int i=0; i<50; i++)
        {
        
        int prior = rand() % 7 + 1;
        int dur = rand() % 120 + 1;
            
            li.push_front(Task(i, dur, prior));
            tas.push_back(Task(i, dur, prior));
        }
    }
    
    void Show() {
        li.reverse();
        for (auto v : li)
            v.Show();
        
        li.sort(Comparator());
        
            
    }

    void UpdateWaiting() {
        int waiting_time = 0;
        
        for (auto it = li.begin(); it != li.end(); ++it){
            it->waiting = waiting_time;
            waiting_time = waiting_time + it->duration;
        }
    }
    
    void Result() {
        for (auto v : li)
            v.ShowWithWaiting();
        
    }
    
    void Process() {
        while (li.size() != 0)
        {
            cout << "doing task #" <<li.back().Id << endl;
            usleep(li.end()->duration * 100000);
            li.pop_back();
        }
    }
    
    int countAvg (int prior) {
        int avg_time = 0;
        int count = 0;
        for (auto it = li.begin(); it != li.end(); ++it){
            if (it->priority == prior) {
                avg_time += it->waiting;
                count++;
            }
                
        }
        avg_time = int(round(avg_time / count));
        return avg_time;
    }
};


int main(int argc, const char * argv[]) {
    
    TaskSheduler task_sheduler = TaskSheduler();
    
    task_sheduler.Show();
    task_sheduler.UpdateWaiting();
    
    cout << endl << endl;
    task_sheduler.Result();
    cout << task_sheduler.countAvg(1) << endl;
    cout << task_sheduler.countAvg(2) << endl;
    cout << task_sheduler.countAvg(3) << endl;
    cout << task_sheduler.countAvg(4) << endl;
    cout << task_sheduler.countAvg(5) << endl;
    cout << task_sheduler.countAvg(6) << endl;
    cout << task_sheduler.countAvg(7) << endl;
    
    task_sheduler.Process();

    return 0;
}
