#include <iostream>
#include <ThreadPool.h>
#include <unistd.h>
#include <string>
#include <vector>

using namespace std;
using namespace saran::base;


class Job {
public:
    explicit Job(const string &str) : log(str) {}
    void fun(void *arg) {
        Job *j = static_cast<Job *>(arg);
        if (nullptr == j) {
            return;
        }   
        cout << pthread_self() << "   "  << j->log << endl;
    }

    std::string log;
};

int main (int argc, char *argv[]) 
{
    cout << "Mian thread id " << pthread_self() << endl;  
    ThreadPool pool;
    pool.Init(10);

    for (int i = 0; i < 100; ++i) {
        Job* j = new Job(to_string(i));
        pool.pushTask(bind(&Job::fun, j, j));
    }

    getchar();
}