#pragma once

#include <iostream>
#include <vector>
#include <map>

using namespace std;


class Courses {
    public:

    struct Node {
        string name_;
        double gpa_;

        vector<map<vector<string>,bool>>> pre; 
        //prerequiste course name, is conconcurrent
        //put all replacable courses in a vector

        Node(string name, double gpa, vector<map<vector<string>,bool>>> prerequiste);

        // bool replacable(string c1, string c2);
    }

    Courses();



}

//helper function to read file to vector
map<string, vector<map<vector<string>,bool>>> readCourseFile(string filename);

vector<string,double> readGPAFile(string filename);