#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <cstdint>

using namespace std;

class TaskManager {
private:
    class Task {
    public:
        explicit Task(const string& n) :
                name(n),
                active(true),
                t_begin(time(nullptr)),
                t_work_sec(0),
                time_of_work(){}

        void TaskEnd() {
            if (active) {
                active = false;
                t_work_sec = difftime(time(nullptr), t_begin);
                uint64_t t = t_work_sec;
                time_of_work+= to_string(t/3600);
                time_of_work+=':';
                unsigned min=(t%3600)/60;
                if(min==0)time_of_work+="00";
                else if(min<10){
                    time_of_work+='0';
                    time_of_work+= to_string(min);
                }
                else time_of_work+= to_string(min);
                time_of_work+=':';
                unsigned sec = (t%3600)%60;
                if(sec==0)time_of_work+="00";
                else if(sec<10){
                    time_of_work+='0';
                    time_of_work+= to_string(sec);
                }
                else time_of_work+= to_string(sec);
            }
        }

        string TimeOfWork() const {
            return time_of_work;
        }

        bool Active() const {
            return active;
        }

        const string name;
    private:
        bool active;
        const time_t t_begin;
        double t_work_sec;
        string time_of_work;
    };

public:
    void Begin(const string& n) {
        if (!tasks.empty())tasks.back().TaskEnd();
        tasks.push_back(Task(n));
    }

    void TaskEnd() {
        if (!tasks.empty())tasks.back().TaskEnd();
    }

    void PrintStatus() {
        if (tasks.empty())cout << "The task list is empty" << endl;
        else {
            for (size_t i = 0; i + 1 < tasks.size(); ++i) {
                cout << "Task " << tasks[i].name << " has worked: " << tasks[i].TimeOfWork() << endl;
            }
            const Task& ref_back_tasks = tasks.back();
            if (ref_back_tasks.Active())cout << "Current task: " << ref_back_tasks.name << endl;
            else cout << "Task " << ref_back_tasks.name << " has worked " << ref_back_tasks.TimeOfWork() << endl;
        }
    }

private:
    vector<Task> tasks;
};


int main() {
    string input_str;
    TaskManager tsk_mngr;
    while (cin >> input_str && input_str != "exit") {
        if (input_str == "begin") {
            cin >> input_str;
            tsk_mngr.Begin(input_str);
        }
        else if(input_str=="end"){
            tsk_mngr.TaskEnd();
        }
        else if(input_str=="status"){
            tsk_mngr.PrintStatus();
        }
        else cout<<"Unknown command"<<endl;
    }
    return 0;
}
