#pragma once

#include <iostream>
#include <vector>
#include <map>

using namespace std;


class Courses {
    public:
        Courses(string course_file, string gpa_file);

    private:
        struct Node {
            string name_;
            double gpa_;
            vector<map<vector<string>, bool>> pre_; 
            // vector of maps containing prerequisite course name and whether or not it's concurrent

            Node(string name, double gpa, vector<map<vector<string>, bool>> prereq)
                : name_(name), gpa_(gpa), pre_(prereq){}

            // bool replacable(string c1, string c2);
        };

        vector<Node> nodes_;
        map<string, vector<string>> edges_;
        map<pair<string, string>, double> weights_;
};


//helper function to read file
map<string, vector<map<vector<string>,bool>>> readCourseFile(string filename);

map<string,double> readGPAFile(string filename);