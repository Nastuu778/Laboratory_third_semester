#include "ip_filter.h"
#include <iostream>
#include <vector>

int main(int argc, char const *argv[])
{
    try
    {
        // Чтение IP-адресов
        auto ip_tuples = read_ips();

        // Сортировка
        sort_ips(ip_tuples);

        // Вывод всех отсортированных IP-адресов
        print_all_ips(ip_tuples);

        // Фильтр 1: первый байт равен 1 (используем LAMBDA)
        auto filter1 = [](const IPAddress &ip)
        {
            return std::get<0>(ip) == 1;
        };
        print_filtered_ips(ip_tuples, filter1);

        // Фильтр 2: первый байт 46, второй 70 (используем LAMBDA)
        auto filter2 = [](const IPAddress &ip)
        {
            return std::get<0>(ip) == 46 && std::get<1>(ip) == 70;
        };
        print_filtered_ips(ip_tuples, filter2);

        // Фильтр 3: любой байт равен 46 (используем LAMBDA)
        auto filter3 = [](const IPAddress &ip)
        {
            return std::get<0>(ip) == 46 || std::get<1>(ip) == 46 ||
                   std::get<2>(ip) == 46 || std::get<3>(ip) == 46;
        };
        print_filtered_ips(ip_tuples, filter3);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}