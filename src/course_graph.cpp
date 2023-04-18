#include "course_graph.h"

#include <fstream>
#include <sstream>

map<string, vector<map<vector<string>,bool>>> readCourseFile(string filename) {
    std::ifstream csv_file(filename);
    std::string line;
    // skip the header line
    std::getline(csv_file, line);

    for (std::string line; std::getline(ifs, line); line = "") {
        map<vector<string>,bool> pre;
        std::vector<std::string> input = utilities::GetSubstrs(line, ',');
        string name = input[3]+input[4];
        std::vector<std::string> each = utilities::GetSubstrs(input[8], ' '); 
    }



        // std::istringstream iss(line);
        std::getline(iss, course_name, ',');
        std::getline(iss, prereq_name, ',');
        std::getline(iss, prereq_gpa_str, ',');
        std::getline(iss, concurrently_registered_str, ',');
        if (prereq_name.empty()) {
            // course has no prerequisites
            if (catalog.find(course_name) == catalog.end()) {
                catalog[course_name] = new Course{course_name, 0.0, false, {}};
            }
        } else {
            // course has prerequisites
            if (catalog.find(prereq_name) == catalog.end()) {
                catalog[prereq_name] = new Course{prereq_name, std::stod(prereq_gpa_str), concurrently_registered_str == "true", {}};
            }
            if (catalog.find(course_name) == catalog.end()) {
                catalog[course_name] = new Course{course_name, 0.0, false, {}};
            }
            catalog[course_name]->prerequisites.push_back(catalog[prereq_name]);
        }
    }
    csv_file.close();
    return catalog;

}

vector<string,double> readGPAFile(string filename);