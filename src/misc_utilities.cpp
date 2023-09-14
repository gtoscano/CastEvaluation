//
// Created by Gregorio Toscano on 4/1/23.
//

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

namespace fs = std::filesystem;

namespace misc_utilities {
    std::string get_env_var(std::string const &key, std::string const &default_value) {
        const char *val = std::getenv(key.c_str());
        return val == nullptr ? std::string(default_value) : std::string(val);
    }

    std::string find_file(std::string path, std::string prefix) {
        std::string found_filename;
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_regular_file()
                && entry.path().extension() == ".csv"
                && entry.path().stem().string().starts_with(prefix)) {
                found_filename = entry.path();
                break;
            }
        }
        return found_filename;
    }


    void split_str(std::string const &str, const char delim,
                   std::vector<std::string> &out) {

        std::stringstream s(str);

        std::string s2;

        while (std::getline(s, s2, delim)) {
            out.push_back(s2); // store the string in s2
        }
    }

    bool copy_file(const std::string& source, const std::string& destination) {
        try {
            // Check if the source file exists
            if (!fs::exists(source)) {
                std::cerr << "Error: Source file does not exist" << std::endl;
                return false;
            }

            // Copy the file to the destination
            fs::copy_file(source, destination, fs::copy_options::overwrite_existing);
            return true;
        } catch (const std::exception& ex) {
            std::cerr << "Error: " << ex.what() << std::endl;
            return false;
        }
    }
    std::string current_time() {
        // Get the current time
        auto now = std::chrono::system_clock::now();

        // Convert the time to a tm struct
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_c);

        // Format the time as a string
        std::ostringstream oss;
        oss << std::put_time(&now_tm, "%H:%M:%S");
        return oss.str();
    }
}