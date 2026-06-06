// C++ Code Challenges, LinkedIn Learning

// Challenge #8: IP Address Validation
// Write an application that reads a string from the terminal and responds with a message indicating whether the string is a valid IP address or not.
// Assume decimal IP addresses.
// 158.25.0.33
// All numbers between 0 and 255.

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// is_valid_ip()
// Summary: This function validates an IP address.
// Arguments:
//           ip: The string to analyze with a potential ip address.
// Returns: A boolean value. True for valid ip addresses, false otherwise.
bool is_valid_ip(std::string ip){
    //assume ip4 addresses which are 32 bit, all nums must be between 0 and 225. 
    //assume all are decimal split, will have 4 chunks of nums. 
    std::stringstream ip_address(ip);
    std::vector<int> ip_chunks;
    std::string chunk;
    int nchunk;

    while(std::getline(ip_address, chunk, '.')){
        if (chunk.size() > 3 || chunk.size() < 1) return false;
        try {
            nchunk = std::stoi(chunk);
        }
        catch (const std::invalid_argument& e){
            return false;
        }
        ip_chunks.push_back(nchunk);
    };

    if (ip_chunks.size() != 4) return false;

    for(auto c:ip_chunks){
        //check if c >= 0 and <= 255
        if (!(c >= 0 && c <= 255)) return false;
    }
    
    return true;
}

// Main function
int main(){
    std::vector<std::pair<std::string , bool>> test_cases = {
        {"158.25.0.33", true},   // valid
        {"0.0.0.0", true}, // valid
        {"255.255.255.255", true}, // valid
        {"192.168.1.1", true},   // valid
        {"1.2.3.04", true},      // valid (though not advised to start with 0)
        {"256.1.1.1", false},     // invalid (256 > 255)
        {"1.2.3.4.5", false },     // invalid (5 chunks)
        {"abc.def.ghi.jkl", false}, // invalid (not nums)
        {"1.2.3", false},         // invalid (3 chunks)
        {"-1.2.3.4", false},      // invalid (negative num)
        {"", false}               // invalid (empty string)
    };

    for(const auto& s : test_cases){
        auto result = is_valid_ip(s.first);
        std::cout << ((s.second == result) ? "TEST PASS" : "TEST FAIL") << ": " << s.first << " is " 
                  << (result ? "" : "not ") << "a valid IPv4 address." << "\n";
    }
    return 0;
}
