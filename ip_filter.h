#ifndef IP_FILTER_H
#define IP_FILTER_H

#include <vector>
#include <string>
#include <tuple>
#include <functional>

// Объявление функций
std::vector<std::string> split(const std::string &str, char d);
std::tuple<int, int, int, int> ip_to_tuple(const std::vector<std::string> &ip_vec);
void print_ip(const std::tuple<int, int, int, int> &ip_tuple);

// Псевдоним типа для IP-адреса (кортеж из 4 int)
using IPAddress = std::tuple<int, int, int, int>;
using IPFilter = std::function<bool(const IPAddress &)>;

// Функции для работы с IP-адресами
std::vector<IPAddress> read_ips();
void sort_ips(std::vector<IPAddress> &ips);
void print_all_ips(const std::vector<IPAddress> &ips);
void print_filtered_ips(const std::vector<IPAddress> &ips, const IPFilter &filter);

#endif // IP_FILTER_H