#include "course_graph.h"

#include <fstream>
#include <sstream>


Courses::Courses(string course_file, string gpa_file) {
    // Read course file
    auto course_data = readCourseFile(course_file);/*map<string, vector<map<vector<string>, bool>>> */
    // Read GPA file
    auto gpa_data = readGPAFile(gpa_file);
    // Create nodes
    for (auto& course : course_data) {/*course type=vector<map<vector<string>, bool>>*/
        string name = course.first;
        double gpa = gpa_data[name];
        nodes_.push_back(Node(name, gpa, course.second));
    }
    for (Node node : nodes_) {
        for (map<vector<string>, bool> prereq_map : node.pre_) {
            for (vector<string> prereq_course : prereq_map) {
                prereq_map.second = false;
                for (string course_name : prereq_course.first) {
                    edges_[node.name_].push_back(course_name);
                    weights_[make_pair(course_name, node.name_)] = gpa_data[course_name];
                }
            }
        }
    }
}



map<string, vector<map<vector<string>,bool>>> readCourseFile(string filename) {
    std::ifstream csv_file(filename);
    std::string line;
    // skip the header line
    std::getline(csv_file, line);
    map<string, vector<map<vector<string>,bool>>> out;

    for (std::string line; std::getline(ifs, line); line = "") {
        std::vector<std::string> input = utilities::GetSubstrs(line, ',');
        if (input[4] >= 500) continue;
        string name = input[3]+input[4];
        // std::vector<std::string> each = utilities::GetSubstrs(input[8], ' '); 
        string des = input[8];
        size_t found = des.find("Prerequisite");
        if (found != string::npos) {
            vector<map<vector<string>,bool>> prereq;
            pair(name, prereq);
            for (unsigned i = found + 12; i < des.length(); i++) {
                size_t oneof = des.find("One of");
                if (oneof != string::npos) {
                    vector<string> of;
                    string course;
                    while (des[oneof] != ';' && des[oneof] != '.') {
                        while (des[oneof].isupper()) {
                            course += des[oneof];
                            oneof++;
                        }
                        if (!course.empty()) {
                            course += des[oneof + 2] + des[oneof + 3] + des[oneof + 4];
                            of.push_back(course);
                            oneof += 3;
                            course.clear();
                        }
                        oneof++;
                    }
                }
            }
        }
    }

    return out;
}

map<string,double> readGPAFile(string filename) {
    std::ifstream csv_file(filename);
    std::string line;
    // skip the header line
    std::getline(csv_file, line);

    vector<string,double> out;
    for (std::string line; std::getline(ifs, line); line = "") {
        std::vector<std::string> input = utilities::GetSubstrs(line, ',');
        if (input[1] >= 500) continue;
        string name = input[0]+input[1];
        double gpa = input[20];
        out.insert(pari<string, double>(name, gpa));
    }

}


