#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>

using namespace std;

int Round(double x) {
    if (x - int(x) >= 0.5) {
        return int(x) + 1;
    }
    else {
        return int(x);
    }
}

void Print(int x) {
    cout << x << endl;
}

void Print(double x) {
    cout << x << endl;
}

void Print(char x) {
    cout << x << endl;
}

void Print(string x) {
    cout << x << endl;
}

template <typename T>
void Print(T x [], int size) {
    for (int i = 0; i < size; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}

template <typename T>
T Abs(T x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

bool id_is_exist(int id, int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == id) return true;
    }
    return false;
}

template <typename T>
void Shufle_Array(T arr[], int size) {
    // Shuffling the array using Fisher-Yates algorithm (i didnt know such a thing already exist)
    // Create an array to store the indices of the original array
    int indxs[size] = {};
    // Initialize the indices array with -1
    // to indicate that no indices have been assigned yet
    for (int i = 0; i < size; ++i)
    indxs[i] = -1;
    // Fill the indices array with unique random indices
    // until all indices are assigned
    for (int i = 0; i < size; i++) {
        while (true) {
            // Generate a random index between 0 and (size - 1)
            int rand_index = rand() % size;
            // Check if the random index is already assigned
            // If not, assign it to the current position in the indices array
            if (!id_is_exist(rand_index, indxs, size)) {
                indxs[i] = rand_index;
                break;
            }
        }
    }
    // Create a new array to store the shuffled elements
    // and fill it with the elements from the original array
    // using the shuffled indices
    T newArr[size] = {};
    for (int i = 0; i < size; i++) {
        newArr[i] = arr[indxs[i]];
    }
    // Copy the shuffled elements back to the original array
    // to reflect the shuffling
    for (int i = 0; i < size; i++) {
    arr[i] = newArr[i];
    }
}

template <typename T>
T degree(T x, int y) {
    T result = 1;
    if (y < 0) {
        x = 1 / x;
        y = -y;
    }

    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

int sum_betwen(int a, int b) {
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }

    int sum = 0;
    for (int i = a + 1; i < b; i++) {
        sum += i;
    }
    return sum;
}

bool is_perfect_number(int n) {
    int sum = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum == n;
}

void perfect_numbers(int pos_1, int pos_2) {
    for (int i = pos_1; i <= pos_2; i++) {
        if (is_perfect_number(i)) {
            cout << i << " ";
        }
    }
}

char* arr[36] = {
    "6H", "7H", "8H", "9H", "10H",
    "JH", "QH", "KH", "AH",
    "6D", "7D", "8D", "9D", "10D",
    "JD", "QD", "KD", "AD",
    "6C", "7C", "8C", "9C", "10C",
    "JC", "QC", "KC", "AC",
    "6S", "7S", "8S", "9S", "10S",
    "JS", "QS", "KS", "AS"
};

void draw_card(int n) {
    cout << "You drew: " << ::arr[n] << endl;
}

int sum_of_digits(int n) {
    int c = 0;
    while (n > 0) {
        c += 1;
        n % 10;
        n /= 10;
    }
    return c;
}

bool is_palindrom_number(int n) {
    if (n < 1) return false;
    int temp = n;
    int n2 = 0;
    for (int i = 0; i < sum_of_digits(n); i++) {
        n2 += (temp % 10) * (degree(10, (sum_of_digits(n) - i - 1)));
        temp /= 10;
    }
    
    if (n2 == n) {
        return true;
    }
    else {
        return false;
    }
}

int main()
{
    srand(time(NULL));
    
    cout << "Enter any number to degree: ";
    double n = 0;
    cin >> n;

    cout << "Enter degree: ";
    int m = 0;
    cin >> m;

    double result = degree(n, m);
    cout << "Result: " << result << "\n";
    cout << "Rounded result: " << Round(result) << "\n\n";

    cout << "Enter two any numbers (for sum between): ";
    int a = 0, b = 0;
    cin >> a >> b;

    int v_sum_betwen = sum_betwen(a, b);
    cout << "Sum between: " << v_sum_betwen << "\n\n";

    cout << "Enter start and end of range (for perfect numbers): ";
    int start = 0, end = 0;
    cin >> start >> end;

    cout << "Perfect numbers in range: ";
    perfect_numbers(start, end);
    cout << "\n\n";

    cout << "Shuffle deck?:\n";
    cout << "1 - yes\n";
    cout << "0 - no\n";
    int choice = 0;
    cin >> choice;

    if (choice == 1) {
        Shufle_Array(arr, 36);
        cout << "Deck shuffled.\n\n";
    } else {
        cout << "Deck not shuffled.\n\n";
    }

    cout << "Enter number of card (1-36): ";
    int card_number = 0;
    cin >> card_number;
    if (card_number < 1 || card_number > 36) {
        cout << "Invalid card number.\n";
    } else {
        draw_card(card_number - 1);
    }
    
    cout << "enter number to check if it is palindrom: ";
    int palindrom_number = 0;
    cin >> palindrom_number;
    if (is_palindrom_number(palindrom_number)) {
        cout << palindrom_number << " is a palindrom number.\n";
    } else {
        cout << palindrom_number << " is not a palindrom number.\n";
    }

    return 0;
}