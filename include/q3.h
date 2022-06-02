#ifndef Q3_H
#define Q3_H

#include <fstream>
#include <iostream>
#include <queue>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace q3 {
struct Flight {
    Flight(std::string _flight_number, size_t _duration, size_t _connections, size_t _connection_times, size_t _price)
        : flight_number { _flight_number }
        , duration { _duration }
        , connections { _connections }
        , connection_times { _connection_times }
        , price { _price }
    {
    }
    std::string flight_number;
    size_t duration;
    size_t connections;
    size_t connection_times;
    size_t price;
};

size_t transfer_to_time(std::string times)
{
    std::regex pattern(R"((\d+)h(\d+)?m?\,?)");
    std::smatch match;
    size_t daghighe {};
    while (std::regex_search(times, match, pattern)) {
        daghighe += static_cast<size_t>(std::stoi(match[1])) * 60;
        std::string sth { match[2] };
        if (sth.empty())
            daghighe += 0;
        else
            daghighe += static_cast<size_t>(std::stoi(match[2]));
        times = match.suffix().str();
    }
    return daghighe;
}

auto comparison { [](Flight first, Flight second) {
    return (first.connection_times + first.duration + 3 * first.price) > (second.connection_times + second.duration + 3 * second.price);
} };

auto gather_flights(std::string filename)
{
    std::priority_queue<Flight, std::vector<Flight>, decltype(comparison)> flights { comparison };
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string txt = buffer.str();

    std::regex pattern(R"(\d+\- \w+\:(\w+)\ - \w+\:(\d+\h\d*\m*)\ - \w+\:(\d+)\ - \w+\:(\d+\h\d*\m*)\,?(\d*\h*\d*\m*)\,?(\d*\h*\d*\m*) - \w+\:(\d+))");
    std::smatch match;
    while (std::regex_search(txt, match, pattern)) {

        std::string flight_number { match[1] };
        size_t duration { transfer_to_time(match[2]) };
        size_t connections { static_cast<size_t>(std::stoi(match[3])) };
        size_t connection_times { transfer_to_time(match[4]) + transfer_to_time(match[5]) + transfer_to_time(match[6]) };
        size_t price { static_cast<size_t>(std::stoi(match[7])) };

        flights.push(Flight { flight_number, duration, connections, connection_times, price });
        txt = match.suffix().str();
    }
    return flights;
}
};

#endif // Q3_H