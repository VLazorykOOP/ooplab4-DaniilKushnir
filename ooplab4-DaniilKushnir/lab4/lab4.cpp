/*#include <iostream>
#include <cmath>
using namespace std;

class VectorDouble {
private:
    double* data;
    size_t size;
    bool codeError;

public:
    VectorDouble() : size(1) {
        data = new double[size];
        data[0] = 0.0;
        codeError = false;
    }

    VectorDouble(size_t newSize) : size(newSize) {
        data = new double[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = 0.0;
        }
        codeError = false;
    }

    VectorDouble(size_t newSize, double newValue) : size(newSize) {
        data = new double[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = newValue;
        }
        codeError = false;
    }

    VectorDouble(const VectorDouble& other) : size(other.size), codeError(other.codeError) {
        data = new double[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    ~VectorDouble() {
        delete[] data;
    }

    VectorDouble& operator++() {
        for (size_t i = 0; i < size; i++) {
            ++data[i];
        }
        return *this;
    }

    VectorDouble operator++(int) {
        VectorDouble temp(*this);
        ++(*this);
        return temp;
    }

    VectorDouble& operator--() {
        for (size_t i = 0; i < size; i++) {
            --data[i];
        }
        return *this;
    }

    VectorDouble operator--(int) {
        VectorDouble temp(*this);
        --(*this);
        return temp;
    }

    bool operator!() const {
        return (size == 0);
    }

    VectorDouble operator-() const {
        VectorDouble result(*this);
        for (size_t i = 0; i < size; i++) {
            result.data[i] = -result.data[i];
        }
        return result;
    }

    VectorDouble& operator=(const VectorDouble& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            codeError = other.codeError;
            data = new double[size];
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    VectorDouble operator+=(const VectorDouble& other) {
        if (size == other.size) {
            for (size_t i = 0; i < size; i++) {
                data[i] += other.data[i];
            }
        }
        else {
            codeError = true;
        }
        return *this;
    }

    VectorDouble operator-=(const VectorDouble& other) {
        if (size == other.size) {
            for (size_t i = 0; i < size; i++) {
                data[i] -= other.data[i];
            }
        }
        else {
            codeError = true;
        }
        return *this;
    }

    VectorDouble operator*=(double scalar) {
        for (size_t i = 0; i < size; i++) {
            data[i] *= scalar;
        }
        return *this;
    }

    VectorDouble operator/=(double scalar) {
        if (scalar != 0.0) {
            for (size_t i = 0; i < size; i++) {
                data[i] /= scalar;
            }
        }
        else {
            codeError = true;
        }
        return *this;
    }

    VectorDouble& operator%=(int modulus) {
        if (modulus != 0) {
            for (size_t i = 0; i < size; ++i) {
                data[i] = fmod(data[i], static_cast<double>(modulus));
            }
        }
        else {
            codeError = true;
        }
        return *this;
    }

    bool operator==(const VectorDouble& other) const {
        if (size != other.size) {
            return false;
        }

        for (size_t i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const VectorDouble& other) const {
        return !(*this == other);
    }

    double& operator[](const size_t index) {
        if (index >= size) {
            codeError = true;
            return data[size - 1];
        }
        else {
            codeError = false;
            return data[index];
        }
    }


    void* operator new(size_t size) {
        cout << "Custom new operator called" << endl;
        return ::operator new(size);
    }

    void operator delete(void* ptr) noexcept {
        cout << "Custom delete operator called" << endl;
        ::operator delete(ptr);
    }


    double operator()() const {
        if (!codeError) {
            double result = 0.0;
            for (size_t i = 0; i < size; ++i) {
                result += data[i];
            }
            return result;
        }
        else {
            cerr << "Error: Vector has an error code." << endl;
            return 0.0;
        }
    }


    bool operator>(const VectorDouble& other) const {
        return (*this)() > other();
    }

    bool operator>=(const VectorDouble& other) const {
        return (*this)() >= other();
    }

    bool operator<(const VectorDouble& other) const {
        return (*this)() < other();
    }

    bool operator<=(const VectorDouble& other) const {
        return (*this)() <= other();
    }

    friend VectorDouble operator+(const VectorDouble& v1, const VectorDouble& v2);
    friend VectorDouble operator-(const VectorDouble& v1, const VectorDouble& v2);
    friend VectorDouble operator*(const VectorDouble& v, double scalar);
    friend VectorDouble operator/(const VectorDouble& v, double divisor);
    friend VectorDouble operator%(const VectorDouble& v, double modulus);
    friend ostream& operator<<(ostream& out, const VectorDouble& vector);
    friend istream& operator>>(istream& in, VectorDouble& vector);
};

VectorDouble operator+(const VectorDouble& v1, const VectorDouble& v2) {
    VectorDouble result(v1);
    result += v2;
    return result;
}

VectorDouble operator-(const VectorDouble& v1, const VectorDouble& v2) {
    VectorDouble result(v1);
    result -= v2;
    return result;
}

VectorDouble operator*(const VectorDouble& v, double scalar) {
    VectorDouble result(v);
    result *= scalar;
    return result;
}

VectorDouble operator/(const VectorDouble& v, double scalar) {
    VectorDouble result(v);
    result /= scalar;
    return result;
}

VectorDouble operator%(const VectorDouble& v, double scalar) {
    VectorDouble result(v);
    result %= scalar;
    return result;
}

ostream& operator<<(ostream& out, const VectorDouble& vector) {
    out << "{";
    for (size_t i = 0; i < vector.size; ++i) {
        out << vector.data[i];
        if (i < vector.size - 1) {
            out << ", ";
        }
    }
    out << "}";
    return out;
}

istream& operator>>(istream& in, VectorDouble& vector) {
    for (size_t i = 0; i < vector.size; ++i) {
        in >> vector.data[i];
    }
    return in;
}

int main() {
    std::cout << "Enter the size of the first vector: ";
    size_t size1;
    std::cin >> size1;

    VectorDouble v1(size1);
    std::cout << "Enter values for the first vector:" << std::endl;
    std::cin >> v1;

    std::cout << "Enter the size of the second vector: ";
    size_t size2;
    std::cin >> size2;

    VectorDouble v2(size2);
    std::cout << "Enter values for the second vector:" << std::endl;
    std::cin >> v2;

    if (size1 == size2) {
        std::cout << "Vectors are equal." << std::endl;
    }
    else {
        std::cerr << "Error: Vectors are not equal." << std::endl;
        return -1;
    }

    std::cout << "First vector: " << v1 << std::endl;
    std::cout << "Second vector: " << v2 << std::endl;


    VectorDouble sum = v1 + v2;
    VectorDouble difference = v1 - v2;
    VectorDouble scaled = v1 * 2.5;
    VectorDouble divided = v2 / 3.0;
    VectorDouble modulated = v1 % 4.0;

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Difference: " << difference << std::endl;
    std::cout << "Scaled: " << scaled << std::endl;
    std::cout << "Divided: " << divided << std::endl;
    std::cout << "Modulated: " << modulated << std::endl;

    VectorDouble* dynamicVector = new VectorDouble(3, 1.5);
    cout << "Dynamic Vector: " << *dynamicVector << endl;
    delete dynamicVector;

    double result = v1();
    cout << "Result of function call on v1: " << result << endl;

    if (v1 > v2) {
        cout << "v1 is greater than v2" << endl;
    }

    if (v1 >= v2) {
        cout << "v1 is greater than or equal to v2" << endl;
    }

    if (v1 < v2) {
        cout << "v1 is less than v2" << endl;
    }

    if (v1 <= v2) {
        cout << "v1 is less than or equal to v2" << endl;
    }

    return 0;
}*/


#include <iostream>
#include <map>
#include <string>

using namespace std;

class DomainIPAssociation {
private:
    map<string, string> data;

public:
    int codeError;
    DomainIPAssociation() : codeError(0) {}

    void addAssociation(const string& domain, const string& ip) {
        data[domain] = ip;
    }

    string& operator[](const string& domain) {
        if (data.find(domain) != data.end()) {
            codeError = 0;
            return data[domain];
        }
        else {
            codeError = 1;
            static string emptyString;
            return emptyString;
        }
    }

    string operator()(const string& domain) {
        return data[domain];
    }

    friend ostream& operator<<(ostream& os, const DomainIPAssociation& obj) {
        for (const auto& entry : obj.data) {
            os << entry.first << ": " << entry.second << endl;
        }
        return os;
    }

    friend istream& operator>>(istream& is, DomainIPAssociation& obj) {
        string domain, ip;
        while (is >> domain >> ip) {
            if (domain == "end" && ip == "end") {
                break; 
            }
            obj.addAssociation(domain, ip);
        }
        return is;
    }
};

int main() {
    DomainIPAssociation associations;

    associations.addAssociation("example.com", "192.168.1.1");
    associations.addAssociation("example.net", "192.168.1.2");

    string ip1 = associations["example.com"];
    cout << "IP for example.com: " << ip1 << endl;

    if (associations.codeError == 1) {
        cout << "Error: Domain not found." << endl;
    }

    string ip2 = associations("example.net");
    cout << "IP for example.net: " << ip2 << endl;

    cout << "Associations:" << endl;
    cout << associations;

    cout << "Enter domain-ip associations (e.g., example.org 192.168.1.3), enter 'end end' to finish:" << endl;
    cin >> associations;

    cout << "Associations after input:" << endl;
    cout << associations;

    return 0;
}
