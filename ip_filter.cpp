#include "ip_filter.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));
    return r;
}

// Функция для преобразования строки IP в кортеж
std::tuple<int, int, int, int> ip_to_tuple(const std::vector<std::string> &ip_vec)
{
    return std::make_tuple(
        std::stoi(ip_vec[0]),
        std::stoi(ip_vec[1]),
        std::stoi(ip_vec[2]),
        std::stoi(ip_vec[3]));
}

// Функция для вывода IP из кортежа
void print_ip(const std::tuple<int, int, int, int> &ip_tuple)
{
    std::cout << std::get<0>(ip_tuple) << "."
              << std::get<1>(ip_tuple) << "."
              << std::get<2>(ip_tuple) << "."
              << std::get<3>(ip_tuple) << std::endl;
}

// Чтение IP-адресов из стандартного ввода
std::vector<IPAddress> read_ips()
{
    std::vector<std::vector<std::string>> ip_pool;
    std::vector<IPAddress> ip_tuples;

    for (std::string line; std::getline(std::cin, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        ip_pool.push_back(split(v.at(0), '.'));
    }

    // Преобразование в кортежи
    for (const auto &ip : ip_pool)
    {
        ip_tuples.push_back(ip_to_tuple(ip));
    }

    return ip_tuples;
}

// Сортировка IP-адресов в обратном лексикографическом порядке
void sort_ips(std::vector<IPAddress> &ips)
{
    std::sort(ips.begin(), ips.end(),
              [](const IPAddress &a, const IPAddress &b)
              {
                  return std::make_tuple(std::get<0>(a), std::get<1>(a), std::get<2>(a), std::get<3>(a)) >
                         std::make_tuple(std::get<0>(b), std::get<1>(b), std::get<2>(b), std::get<3>(b));
              });
}

// Вывод всех IP-адресов
void print_all_ips(const std::vector<IPAddress> &ips)
{
    for (const auto &ip : ips)
    {
        print_ip(ip);
    }
}

// Вывод отфильтрованных IP-адресов
void print_filtered_ips(const std::vector<IPAddress> &ips, const IPFilter &filter)
{
    for (const auto &ip : ips)
    {
        if (filter(ip))
        {
            print_ip(ip);
        }
    }
}