#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
using namespace std;

enum Scale{
    Kelvin = 'K', Celsius = 'C', Fahrenheit = 'F'
};
struct temperature{
    Scale scale;
    double value;
};
istream & operator >> (istream & in, temperature & t){
    in >> t.value;
    char symbol;
    in >> symbol;
    switch (symbol){
    case 'K' : t.scale = Kelvin;
        break;
    case 'C' : t.scale = Celsius;
        break;
    case 'F' :  t.scale =  Fahrenheit;
        break;
    }
    return in;
}
void test_temperature_input() {
    //Создать поток в памяти со строкой-примером 10К
    stringstream in1 ("4K");
    //Завести переменную температуру и считать её
    temperature t;
    in1 >> t;
    //Проверить шкалу и значение
    assert (t.value == 4);
    assert (t.scale == Kelvin);

    stringstream in2 ("-273C");
    in2 >> t;
    assert (t.value == -273);
    assert (t.scale == Celsius);

    stringstream in3 ("421F");
    in3 >> t;
    assert (t.value == 421);
    assert (t.scale == Fahrenheit);

}
temperature convert (const temperature & from, Scale scale){
    double K;
    switch (from.scale) {
    case Kelvin:
        K = from.value;
        break;
    case Celsius:
        K = from.value + 273.15;
        break;
    case Fahrenheit:
        K = (from.value + 459.67) / 1.8;
        break;
    }
    temperature result;
    result.scale = scale;
    switch (scale){
    case Kelvin :
        result.value = K;
        break;
    case Celsius :
        result.value = K-273.15;
        break;
    case Fahrenheit :
        result.value = (K*1.8)-459.67;
        break;
    }
    return result;
};
int
main() {
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    cerr << "Enter numbers: ";
    vector<double> numbers(number_count);
    for (size_t i = 0; i < number_count; i++) {
        cin >> numbers[i];
    }

    size_t column_count;
    cerr << "Enter column count: ";
    cin >> column_count;

    double min = numbers[0];
    double max = numbers[0];
    for (double number : numbers) {
        if (number < min) {
            min = number;
        }
        if (number > max) {
            max = number;
        }
    }

    vector<size_t> counts(column_count);
    for (double number : numbers) {
        size_t column = (size_t)((number - min) / (max - min) * column_count);
        if (column == column_count) {
            column--;
        }
        counts[column]++;
    }

    const size_t screen_width = 80;
    const size_t axis_width = 4;
    const size_t chart_width = screen_width - axis_width;

    // Можно было бы считать в предыдущем цикле, но так более наглядно.
    size_t max_count = 0;
    for (size_t count : counts) {
        if (count > max_count) {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > chart_width;

    for (size_t count : counts) {
        if (count < 100) {
            cout << ' ';
        }
        if (count < 10) {
            cout << ' ';
        }
        cout << count << "|";

        size_t height = count;
        if (scaling_needed) {
            // Point: код должен быть в первую очередь понятным.
            const double scaling_factor = (double)chart_width / max_count;
            height = (size_t)(count * scaling_factor);
        }

        for (size_t i = 0; i < height; i++) {
            cout << '*';
        }
        cout << '\n';
    }

    return 0;
}