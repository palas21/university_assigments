/**
 * BLG 336E - Analysis of Algorithms II
 * Assignment 3
 * Şafak Özkan Pala
 * 150210016
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>

/* YOU CAN INCLUDE ANY OTHER NECESSARY LIBRARIES */
#include <cmath>

/* YOU CAN DEFINE EXTRA FUNCTIONS AND MODIFY THE CODE TEMPLATE */

/* YOU HAVE TO CONSIDER THE OUTPUT FORMAT TO TEST YOUR CODE WITH CALICO */

using namespace std;


struct TimeIntervals {
    string floor_name;
    string room_no;
    int start; // time is millitary time like 13:00 -> 1300
    int end;
    int priority;
    string start_time;
    string end_time;
};

struct Priority {
    string floor_name;
    string room_no;
    int priority;
};

struct Item {
    string name;
    int price;
    float value;
};

/* START: WEIGHTED INTERVAL SCHEDULING (for each floor) */

struct Schedule
{
    string floor_name;
    vector<TimeIntervals> interval; // interval and Priority
};

int latest_non_conflict(vector<TimeIntervals> intervals, int index)
{
    for (int i = index - 1; i >= 0; i--) {
        if (intervals[i].end <= intervals[index].start) {
            return i;
        }
    }
    return -1;
}

Schedule wis(Schedule schedule)
{
    vector<TimeIntervals> intervals = schedule.interval;
    sort(intervals.begin(), intervals.end(), [](const TimeIntervals& a, const TimeIntervals& b) {
        return a.end < b.end;
    });

    vector<int> dp(intervals.size());
    dp[0] = intervals[0].priority;

    for (size_t i = 1; i < intervals.size(); i++) {
        int incl = intervals[i].priority;
        int l = latest_non_conflict(intervals, i);
        if (l != -1) {
            incl += dp[l];
        }
        dp[i] = max(incl, dp[i - 1]);
    }

    vector<TimeIntervals> selected_intervals;
    int i = intervals.size() - 1;
    while (i >= 0) {
        if (i == 0) {
            selected_intervals.push_back(intervals[i]);
            break;
        }
        if(latest_non_conflict(intervals, i) == -1){
            selected_intervals.push_back(intervals[i]);
            i--;
            continue;
        }
        if (intervals[i].priority + dp[latest_non_conflict(intervals, i)] >= dp[i - 1]) {
            selected_intervals.push_back(intervals[i]);
            i = latest_non_conflict(intervals, i);
        } else {
            i--;
        }
    }

    reverse(selected_intervals.begin(), selected_intervals.end());

    Schedule optimal_schedule;
    optimal_schedule.floor_name = schedule.floor_name;
    optimal_schedule.interval = selected_intervals;

    return optimal_schedule;
}

// function to find the best schedule for each floor
vector<Schedule> weighted_interval_scheduling(vector<Schedule> schedules)
{
    vector<Schedule> optimal_schedules;
    for(auto& s : schedules){
        optimal_schedules.push_back(wis(s));
    }

    return optimal_schedules;
}

// *** END ***


/* START: KNAPSACK (for items) */

// Function to select the most valuable items that can be purchased with a certain budget
vector<Item> knapsack(const vector<Item>& items, int budget) {

    int n = items.size();

    vector<vector<float>> dp(n + 1, vector<float>(budget + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= budget; j++) {
            if (items[i - 1].price <= j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - items[i - 1].price] + items[i - 1].value);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    vector<Item> selected_items;
    int i = n, j = budget;
    while (i > 0 && j > 0) {
        if (dp[i][j] != dp[i - 1][j]) {
            selected_items.push_back(items[i - 1]);
            j -= items[i - 1].price;
        }
        i--;
    }

    return selected_items;
}

// *** END ***


int main(int argc, char *argv[])
{
    string case_no = argv[1];
    string case_name = "case_" + case_no;
    string path = "./inputs/" + case_name;

    int total_budget = 200000; 

    // Read items
    vector<Item> items;
    
    ifstream file(path + "/items.txt");
    if (file.is_open())
    {
        string line;
        getline(file, line); 
        while (getline(file, line))
        {
            stringstream ss(line);
            string name;
            int price;
            float value;
            ss >> name >> price >> value;
            Item item;
            item.name = name;
            item.price = price;
            item.value = value;
            items.push_back(item);
        }
        file.close();
    }

    vector<Item> selected_items = knapsack(items, total_budget);
    float total_value = 0;

    for (const Item& item : selected_items) {
        total_value += item.value;
    }
    
    total_value = round(total_value * 10) / 10;

    // Read priorities
    vector<Priority> priorities;
    ifstream file2(path + "/priority.txt");

    if(file2.is_open())
    {
        string line;
        getline(file2, line); 
        while (getline(file2, line))
        {
            stringstream ss(line);
            string name;
            string room_no;
            size_t priority;
            ss >> name >> room_no >> priority;
            Priority p;
            p.floor_name = name;
            p.room_no = room_no;
            p.priority = priority;
            priorities.push_back(p);
        }
        file2.close();
    }

    // Read time intervals
    vector<TimeIntervals> time_intervals;
    ifstream file3(path + "/room_time_intervals.txt");

    if(file3.is_open())
    {
        string line;
        getline(file3, line); 
        while (getline(file3, line))
        {
            stringstream ss(line);
            string floor_name;
            string room_no;
            string start;
            string end;
            int start_time, end_time;
            ss >> floor_name >> room_no >> start >> end;
            int start_hour, start_minute, end_hour, end_minute;
            start_hour = stoi(start.substr(0, 2));
            start_minute = stoi(start.substr(3, 2));
            end_hour = stoi(end.substr(0, 2));
            end_minute = stoi(end.substr(3, 2));

            start_time = start_hour * 100 + start_minute;
            end_time = end_hour * 100 + end_minute;

            TimeIntervals t;
            t.floor_name = floor_name;
            t.room_no = room_no;
            t.start = start_time;
            t.end = end_time;
            t.start_time = start;
            t.end_time = end;
            for (const Priority& p : priorities) {
                if (p.floor_name == floor_name && p.room_no == room_no) {
                    t.priority = p.priority;
                    break;
                }
            }
            time_intervals.push_back(t);
        }
        file3.close();
    }

    vector<Schedule> schedules;

    for (const auto& t : time_intervals) {
        bool found = false;
        for (auto& s : schedules) {
            if (s.floor_name == t.floor_name) {
                s.interval.push_back(t);
                found = true;
                break;
            }
        }
        if (!found) {
            Schedule s;
            s.floor_name = t.floor_name;
            s.interval.push_back(t);
            schedules.push_back(s);
        }
    }

    vector<Schedule> optimal_schedules = weighted_interval_scheduling(schedules);
    
    std::cout << "Best Schedule for Each Floor" << std::endl;

    for (const auto& s : optimal_schedules){

        size_t priority_gain = 0;
        for (const auto& i : s.interval) {
            priority_gain += i.priority;
        }

        std::cout << s.floor_name << " --> Priority Gain: " << priority_gain << endl;
        for (const auto& i : s.interval) {
            std::cout << i.floor_name << "\t" << i.room_no << "\t" << i.start_time << "\t" << i.end_time << endl;
        }
    }

    std::cout << "Best Use of Budget\nTotal Value --> " << total_value << endl;
    for (const auto& item : selected_items) {
        std::cout << item.name << endl;
    }

    return 0;
}
