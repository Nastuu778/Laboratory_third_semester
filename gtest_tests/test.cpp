#include "ip_filter.h"
#include <gtest/gtest.h>
#include <vector>
#include <sstream>

// Тест 1: Проверка функции split
TEST(IPFilterTest, SplitFunction)
{
    auto result1 = split("192.168.1.1", '.');
    std::vector<std::string> expected1 = {"192", "168", "1", "1"};
    EXPECT_EQ(result1, expected1);

    auto result2 = split("10.0.0.1", '.');
    std::vector<std::string> expected2 = {"10", "0", "0", "1"};
    EXPECT_EQ(result2, expected2);

    auto result3 = split("255.255.255.255", '.');
    std::vector<std::string> expected3 = {"255", "255", "255", "255"};
    EXPECT_EQ(result3, expected3);
}

// Тест 2: Проверка обратной лексикографической сортировки
TEST(IPFilterTest, ReverseLexicographicSort)
{
    std::vector<IPAddress> ips = {
        {1, 1, 1, 1},
        {1, 2, 1, 1},
        {1, 10, 1, 1},
        {2, 1, 1, 1}};

    std::vector<IPAddress> expected = {
        {2, 1, 1, 1},
        {1, 10, 1, 1},
        {1, 2, 1, 1},
        {1, 1, 1, 1}};

    sort_ips(ips);
    EXPECT_EQ(ips, expected);
}

// Тест 3: Проверка фильтров
TEST(IPFilterTest, FilterFunctions)
{
    std::vector<IPAddress> ips = {
        {1, 70, 44, 170},
        {46, 70, 225, 39},
        {186, 46, 222, 194},
        {192, 168, 1, 1}};

    // Фильтр по первому байту = 1
    auto filter1 = [](const IPAddress &ip)
    { return std::get<0>(ip) == 1; };
    std::vector<IPAddress> result1;
    for (const auto &ip : ips)
    {
        if (filter1(ip))
            result1.push_back(ip);
    }
    EXPECT_EQ(result1.size(), 1);
    EXPECT_EQ(result1[0], std::make_tuple(1, 70, 44, 170));

    // Фильтр по первому байту = 46 и второму = 70
    auto filter2 = [](const IPAddress &ip)
    {
        return std::get<0>(ip) == 46 && std::get<1>(ip) == 70;
    };
    std::vector<IPAddress> result2;
    for (const auto &ip : ips)
    {
        if (filter2(ip))
            result2.push_back(ip);
    }
    EXPECT_EQ(result2.size(), 1);
    EXPECT_EQ(result2[0], std::make_tuple(46, 70, 225, 39));

    // Фильтр по любому байту = 46
    auto filter3 = [](const IPAddress &ip)
    {
        return std::get<0>(ip) == 46 || std::get<1>(ip) == 46 ||
               std::get<2>(ip) == 46 || std::get<3>(ip) == 46;
    };
    std::vector<IPAddress> result3;
    for (const auto &ip : ips)
    {
        if (filter3(ip))
            result3.push_back(ip);
    }
    EXPECT_EQ(result3.size(), 2);
}