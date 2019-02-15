
/* 
 EAMON WOLFGRAM

 This is a C++ program that reads in a list of process names
 from stdin/cin and simulates round-robin CPU scheduling on the
 list.
 */

#include <unistd.h>
#include <signal.h>
#include <string>
#include <iostream>

using namespace std;

struct list_element {
        list_element * next;
        string name;
        int time;
};

list_element * new_process(string name, int time) { //returns a ptr to a new process
        list_element * return_val = new list_element;
        return_val->name = name;
        return_val->time = time;

        return return_val;
}

list_element * find_last_element(list_element * initial) {
        list_element * return_val = initial;
        bool end_found = false;

        while(end_found == false) {
                if (return_val->next == 0)
                        end_found = true;
                else
                        return_val = return_val->next;
        }

        return return_val;
}

void read_list(list_element * initial) {
        bool end_found = false;
        list_element * cur_element = initial;

        while(end_found == false) {
                if (cur_element->next == 0){
                        end_found = true;
                        cout << cur_element->name << endl;
                }
                else {
                        cout << cur_element->name;
                        cur_element = cur_element->next;
                }
        }
}

list_element * list = new_process("temp",0);

void process_scheduler(int signum) {

        if (list->time > 0) {
                cout << list->name << " " << list->time << endl;
                list->time -= 2;
        }
        else {
                cout << list->name << " Finished" << endl;
                if (list->next != 0)
                        list = list->next;
                else {
                        list = 0;
                        cout << "No processes left" << endl;
                }

        }

        if (list != 0)
                if (list->next != 0) {
                        list_element * last_node = find_last_element(list);
                        last_node->next = list;
                        list_element * next_node = list->next;
                        list->next = 0;
                        list = next_node;
                }
}



int main() {
        string input_name = "";
        int input_time = 0;
        bool new_list = true;

        while(!cin.eof()) {
                list_element * temp_process = new_process("temp",0);
                cin >> input_name >> input_time;

                if (new_list == true) {
                        new_list = false;
                        list->name = input_name;
                        list->time = input_time;
                        list->next = 0;
                }
                else if(!cin.eof()) {
                        temp_process->name = input_name;
                        temp_process->time = input_time;
                        list_element * last_element = find_last_element(list);
                        temp_process->next = 0;
                        last_element->next = temp_process;
                }
        }

        signal(SIGALRM, process_scheduler);

        while(list != 0) {
                alarm(2);
                sleep(5);
        }

        return 0;
}