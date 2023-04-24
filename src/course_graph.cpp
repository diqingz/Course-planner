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



map<string, map<vector<string>,bool>> readCourseFile(string filename) {
    std::ifstream csv_file(filename);
    std::string line;
    // skip the header line
    std::getline(csv_file, line);
    map<string, map<vector<string>,bool>> out;

    for (std::string line; std::getline(ifs, line); line = "") {
        std::vector<std::string> input = utilities::GetSubstrs(line, ',');
        if (input[4] >= 500) continue;
        string name = input[3]+input[4];
        // std::vector<std::string> each = utilities::GetSubstrs(input[8], ' '); 
        string des = input[8];
        size_t found = des.find("Prerequisite");
        if (found != string::npos) {
            map<vector<string>,bool> prereq; ///prereq
            for (unsigned i = found + 12; i < des.length(); i++) {
                size_t oneof = des.find("One of");
                size_t ccurr_up = des.find("Concurrent ");
                size_t ccurr_low = des.find("concurrent ");
                size_t tmp = compare(ccurr_low, ccurr_up);


                while ((oneof > i && tmp > i) || (oneof == string::npos && tmp == string::npos)) {
                    string first = des.substr(i, (oneof < tmp) ? oneof : tmp);
                    size_t semi = first.find(";");
                    size_t per = first.find(".");

                    string sub = first.substr(i, (semi != -1) ? semi : per);
                    if (!helper(sub, i).empty())
                        prereq.push_back(make_pair<vector<string>,bool>(helper(des, i), false));
                }

                //check for oneof
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
                            oneof += 4;
                            course.clear();
                        }
                        oneof++;
                    }
                    prereq.push_back(make_pair<vector<string>,bool>(of, false));
                    
                }
                //check for concurrent
                if (ccurr_low != string::npos) {
                    string concurrent = des.substr(ccurr_low, des[des.length() - 1]);
                    size_t idx = ccurr_low;
                    if (!helper(concurrent, idx).empty())
                        prereq.push_back(make_pair<vector<string>,bool>(helper(des, i), true));
                }
                if (ccurr_up != string::npos) {
                    size_t semi = concurrent.find(";");
                    size_t per = concurrent.find(".");
                    size_t idx = ccurr_up;
                    string concurrent = des.substr(ccurr_up, (semi != -1) ? semi : per);
                    if (!helper(concurrent, idx).empty())
                        prereq.push_back(make_pair<vector<string>,bool>(helper(des, i), true));
                }
            }
            out.push_back(make_pair<string, map<vector<string>,bool>>(name, prereq));
        }
    }

    return out;
}

std::vector<std::string> GetSubstrs(const std::string& str, char delimiter) {
  size_t last = 0;
  std::vector<std::string> substrs;
  for (size_t i = 0; i != str.length(); ++i) {
    if (str.at(i) == delimiter) {
      std::string substr = str.substr(last, i - last);
      last = i + 1;
      substrs.push_back(substr);
    }
  }
  std::string substr = str.substr(last, str.length() - last);
  substrs.push_back(substr);

  return substrs;
}


size_t compare(size_t a, size_t b) {
    if (a != -1 && b != -1) {
        return (a <= b) ? a : b;
    } else if (a != -1) {
        return b;
    } else {
        return a;
    }
}

vector<string> helper(string input, size_t& idx) {
    string temp;
    vector<string> first_course;

    size_t or = input.find("or");

    int cout;

    for (size_t i = 0; i < input.length(); i++) {
        while (input[idx].isupper()) {
            temp += des[idx];
            idx++;
            count++;
        }
        if (count > 1) {
            temp += des[idx + 2] + des[idx + 3] + des[idx + 4];
            first_course.push_back(temp);
            idx += 4;
        }
        if (or == string::npos) return first_course;
    }
    return first_course;
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


