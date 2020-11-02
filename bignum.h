#pragma once

#include <string>
#include <stdint.h>
#include <algorithm>

std::string reverse_string(std::string input)
{
    std::string temp{ input };
    std::reverse(temp.begin(), temp.end());
    return temp;
}

std::string addition(std::string value1, std::string value2)
{
    std::string result, value1reversed = reverse_string(value1), value2reversed = reverse_string(value2);
    int remainder = 0;

    size_t i = 0;
    while (true)
    {
        if ((i >= value1reversed.size()) && (i >= value2reversed.size()) && (remainder == 0))
            break;

        int first = 0, second = 0, temp_result = 0;
        if (i < value1reversed.size())
            first = (value1reversed[i] - '0');
        if (i < value2reversed.size())
            second = (value2reversed[i] - '0');

        temp_result = first + second + remainder;
        // std::cout << first << " + " << second << " + remainder " << remainder << " = " << temp_result << "\n";
        if (temp_result >= 20)
        {
            remainder = 2;
            temp_result -= 20;
        }
        else if (temp_result >= 10)
        {
            remainder = 1;
            temp_result -= 10;
        }
        else
            remainder = 0;
        result += std::to_string(temp_result);
        //std::cout << result << '\n';
        i++;
    }
    return reverse_string(result);
}

bool check_if_first_number_is_bigger(std::string value1, std::string value2)
{
    bool first_is_bigger = true;

    if (value1.size() > value2.size())
        first_is_bigger = true;
    else if (value1.size() < value2.size())
        first_is_bigger = false;
    else if (value1.size() == value2.size())
    {
        size_t i = 0;
        while (i <= value1.size())
        {
            if ((value1[i] - '0') > (value2[i] - '0'))
            {
                first_is_bigger = true;
                break;
            }
            else if ((value1[i] - '0') < (value2[i] - '0'))
            {
                first_is_bigger = false;
                break;
            }
            i++;
        }
    }
    return first_is_bigger;
}

std::string subtraction(std::string value1, std::string value2)
{
    std::string result, value1reversed = reverse_string(value1), value2reversed = reverse_string(value2);
    int remainder = 0;
    bool first_is_bigger = check_if_first_number_is_bigger(value1, value2);

    size_t i = 0;
    while (true)
    {
        if ((i >= value1reversed.size()) && (i >= value2reversed.size()))
            break;

        int first = 0, second = 0, temp_result = 0;
        if (i < value1reversed.size())
            first = (value1reversed[i] - '0');
        if (i < value2reversed.size())
            second = (value2reversed[i] - '0');

        if (first_is_bigger)
        {
            temp_result = first - (second + remainder);
            // std::cout << first << " - " << second << " + remainder " << remainder << " = " << temp_result << "\n";
        }
        else
        {
            temp_result = second - (first + remainder);
            //std::cout << second << " - " << first << " + remainder " << remainder << " = " << temp_result << "\n";
        }
        //std::cout << first << " - " << second << " - remainder " << remainder << " = " << temp_result << "\n";
        if (temp_result < 0)
        {
            remainder = 1;
            temp_result = 10 + temp_result;
        }
        else
            remainder = 0;
        result += std::to_string(temp_result);
        //std::cout << result << '\n';
        i++;
    }
    std::string temp = "";
    if (first_is_bigger == false)
        temp += "-";
    temp += reverse_string(result);
    return temp;
}

std::string multiplication(std::string value1, std::string value2)
{
    if (value1 == "0" || value2 == "0")
        return "0";

    std::string result, value1reversed = reverse_string(value1), value2reversed = reverse_string(value2);

    size_t i = 0;
    while (true)
    {
        if (i >= value1.size())
        {
            break;
        }

        std::string one_row_multiplication;
        int remainder = 0;
        for (size_t j = 0; j < value2.size(); j++)
        {
            int first = 0, second = 0, one_number_multiplication = 0;
            first = (value1reversed[i] - '0');
            second = (value2reversed[j] - '0');
            one_number_multiplication = first * second + remainder;
            one_row_multiplication += std::to_string((one_number_multiplication) % 10);
            //std::cout << first << " * " << second << " + remainder " << remainder << " = " << one_number_multiplication << "\n";
            if (one_number_multiplication < 10)
                remainder = 0;
            else
                remainder = (std::to_string(one_number_multiplication)[0] - '0');
        }
        if (remainder != 0)
            one_row_multiplication += std::to_string(remainder);
        one_row_multiplication = reverse_string(one_row_multiplication);
        //std::cout << value1reversed[i] << " * " << value2 << " = " << one_row_multiplication << "\n";
        for (size_t j = 0; j < i; j++)
            one_row_multiplication += "0";

        result = addition(result, one_row_multiplication);
        i++;
    }
    return result;
}

class BigNum final
{
public:                                                             
    // constructors
    BigNum() : m_data("0"), m_is_negative(false) {}
    BigNum(int64_t n) : m_data(std::to_string(n)), m_is_negative(false)
    {
        if (n == 0)
        {
            m_is_negative = false;
            m_data = "0";
        }
        else
        {
            if (m_data[0] == '-')
            {
                m_is_negative = true;
                m_data = m_data.substr(1);
            }
        }
    }
    explicit BigNum(const std::string& str) : m_data(str), m_is_negative(false)
    {
        if (m_data.size() == 0)
            throw std::invalid_argument(" Invalid input format!");
      
        if (m_data[0] == '-')
        {
            m_is_negative = true;
            m_data = m_data.substr(1);
        }
        else if (m_data[0] == '+')
        {
            m_data = m_data.substr(1);
        }

        size_t zeros_on_start = 0;
        bool counting_start_zeros = true;
        for (size_t i = 0; i < m_data.size(); i++)
        {
            if (m_data[i] < '0' || m_data[i] > '9')
            {
                throw std::invalid_argument(" Invalid input format!");
            }
            else {
                if (counting_start_zeros == true)
                {
                    if (m_data[i] == '0')
                        zeros_on_start++;
                    else
                        counting_start_zeros = false;
                }
            }
        }
        m_data = m_data.substr(zeros_on_start);
        if (m_data == "" || m_data == "0")
        {
            m_data = "0";
            m_is_negative = false;
        }
    }

    // copy
    BigNum(const BigNum& other) : m_data(other.m_data), m_is_negative(other.m_is_negative) {}
    BigNum& operator=(const BigNum& rhs)
    {
        if (this != &rhs)
        {
            this->m_data = rhs.m_data;
            this->m_is_negative = rhs.m_is_negative;
        }
        return *this;
    }

    // unary operators
    const BigNum& operator+() const
    {
        return *this;
    }
    BigNum operator-() const
    {
        BigNum temp{ *this };
        temp.m_is_negative = !this->m_is_negative;
        return temp;
    }

    // binary arithmetics operators
    BigNum& operator+=(const BigNum& rhs)
    {
        std::string result = "";
        if ((m_is_negative == false && rhs.m_is_negative == false) || (m_is_negative == true && rhs.m_is_negative == true))
        {
            if (m_is_negative == true)
                result += "-";
            result.append(addition(m_data, rhs.m_data));
        }
        else  if (m_is_negative == false && rhs.m_is_negative == true)
            result = subtraction(m_data, rhs.m_data);
        else  if (m_is_negative == true && rhs.m_is_negative == false)
            result = subtraction(rhs.m_data, m_data);

        *this = BigNum{ result };
        return *this;

    }
    BigNum& operator-=(const BigNum& rhs)
    {
        std::string result = "";
        if (m_is_negative == true && rhs.m_is_negative == true)
        {
            result = subtraction(rhs.m_data, m_data);
        }
        else if (m_is_negative == false && rhs.m_is_negative == false)
        {
            result = subtraction(m_data, rhs.m_data);
        }

        else if (m_is_negative == true && rhs.m_is_negative == false)
        {
            result += "-";
            result.append(addition(m_data, rhs.m_data));
        }

        else if (m_is_negative == false && rhs.m_is_negative == true)
        {
            result = addition(m_data, rhs.m_data);
        }
        *this = BigNum{ result };
        return *this;
    }
    BigNum& operator*=(BigNum rhs)
    {
        std::string result = "";
        if ((m_is_negative == true && rhs.m_is_negative == false) || (m_is_negative == false && rhs.m_is_negative == true))
            result += "-";
        result += multiplication(m_data, rhs.m_data);

        *this = BigNum{ result };
        return *this;
    }

private:
    // here you can add private data and members, but do not add stuff to 
  // public interface, also you can declare friends here if you want
    bool m_is_negative;
    std::string m_data;

    friend BigNum operator+(BigNum lhs, const BigNum& rhs);
    friend BigNum operator-(BigNum lhs, const BigNum& rhs);
    friend BigNum operator*(BigNum lhs, const BigNum& rhs);
    friend bool operator==(const BigNum& lhs, const BigNum& rhs);
    friend bool operator!=(const BigNum& lhs, const BigNum& rhs);
    friend bool operator<(const BigNum& lhs, const BigNum& rhs);
    friend bool operator>(const BigNum& lhs, const BigNum& rhs);
    friend bool operator<=(const BigNum& lhs, const BigNum& rhs);
    friend bool operator>=(const BigNum& lhs, const BigNum& rhs);
    friend std::ostream& operator<<(std::ostream& lhs, const BigNum& rhs);
};

BigNum operator-(BigNum lhs, const BigNum& rhs);

BigNum operator+(BigNum lhs, const BigNum& rhs)
{
    std::string result = "";
    if ((lhs.m_is_negative == false && rhs.m_is_negative == false) || (lhs.m_is_negative == true && rhs.m_is_negative == true))
    {
        if (lhs.m_is_negative == true)
            result += "-";
        result.append(addition(lhs.m_data, rhs.m_data));
    }
    else  if (lhs.m_is_negative == false && rhs.m_is_negative == true)
        result = subtraction(lhs.m_data, rhs.m_data);
    else  if (lhs.m_is_negative == true && rhs.m_is_negative == false)
        result = subtraction(rhs.m_data, lhs.m_data);

    return BigNum{ result };
}
BigNum operator-(BigNum lhs, const BigNum& rhs)
{
    std::string result = "";
    if (lhs.m_is_negative == true && rhs.m_is_negative == true)
    {
        result = subtraction(rhs.m_data, lhs.m_data);
    }
    else if (lhs.m_is_negative == false && rhs.m_is_negative == false)
    {
        result = subtraction(lhs.m_data, rhs.m_data);
    }

    else if (lhs.m_is_negative == true && rhs.m_is_negative == false)
    {
        result += "-";
        result.append(addition(lhs.m_data, rhs.m_data));
    }

    else if (lhs.m_is_negative == false && rhs.m_is_negative == true)
    {
        result = addition(lhs.m_data, rhs.m_data);
    }
    return BigNum{ result };
}

BigNum operator*(BigNum lhs, const BigNum& rhs)
{
    std::string result = "";
    if ((lhs.m_is_negative == true && rhs.m_is_negative == false) || (lhs.m_is_negative == false && rhs.m_is_negative == true))
        result += "-";
    result += multiplication(lhs.m_data, rhs.m_data);
    return BigNum{ result };
}

bool operator==(const BigNum& lhs, const BigNum& rhs)
{
    if (lhs.m_is_negative == rhs.m_is_negative)
    {
        if (lhs.m_data.size() == rhs.m_data.size())
        {
            if (lhs.m_data.compare(rhs.m_data) == 0)
                return true;
        }
    }
    return false;
}

bool operator<(const BigNum& lhs, const BigNum& rhs)
{
    if (lhs.m_is_negative == true && rhs.m_is_negative == true)
    {
        return check_if_first_number_is_bigger(lhs.m_data, rhs.m_data);
    }
    else if (lhs.m_is_negative == false && rhs.m_is_negative == false)
    {
        return !check_if_first_number_is_bigger(lhs.m_data, rhs.m_data);
    }
    else if (lhs.m_is_negative == false && rhs.m_is_negative == true)
    {
        return false;
    }
    else if (lhs.m_is_negative == true && rhs.m_is_negative == false)
    {
        return true;
    }
    return true;
}
bool operator!=(const BigNum& lhs, const BigNum& rhs)
{
    return !(lhs == rhs);
}
bool operator>(const BigNum& lhs, const BigNum& rhs)
{
    return (rhs < lhs);
}
bool operator<=(const BigNum& lhs, const BigNum& rhs)
{
    return ((lhs < rhs) || (lhs == rhs));
}
bool operator>=(const BigNum& lhs, const BigNum& rhs)
{
    return ((rhs < lhs) || (lhs == rhs));
}

std::ostream& operator<<(std::ostream& lhs, const BigNum& rhs)
{
    if (rhs.m_is_negative == true) {
        std::string minus = "-";
        lhs << minus;
    }
    lhs << rhs.m_data;
    return lhs;
}
