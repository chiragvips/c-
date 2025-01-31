#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

class SalesData {
    string productName;
    int unitsSold;
    double unitPrice;
public:
    void inputSalesData();
    void displaySalesData() const;
    double totalSales() const;
    string getProductName() const;
    int getUnitsSold() const;
    double getUnitPrice() const;
};

void SalesData::inputSalesData() {
    cout << "Enter Product Name: ";
    cin.ignore();
    getline(cin, productName);
    cout << "Enter Units Sold: ";
    cin >> unitsSold;
    cout << "Enter Unit Price: ";
    cin >> unitPrice;
}

void SalesData::displaySalesData() const {
    cout << left << setw(20) << productName << setw(15) << unitsSold << setw(15) << unitPrice << setw(15) << totalSales() << endl;
}

double SalesData::totalSales() const {
    return unitsSold * unitPrice;
}

string SalesData::getProductName() const {
    return productName;
}

int SalesData::getUnitsSold() const {
    return unitsSold;
}

double SalesData::getUnitPrice() const {
    return unitPrice;
}

void displayAllSalesData(SalesData sales[], int n);
double calculateTotalRevenue(SalesData sales[], int n);
double calculateAverageSales(SalesData sales[], int n);
void findHighestLowestSales(SalesData sales[], int n, SalesData &highest, SalesData &lowest);

int main() {
    int n;
    cout << "Enter the number of products: ";
    cin >> n;

    SalesData sales[n];

    for (int i = 0; i < n; ++i) {
        cout << "\nEnter data for product " << i + 1 << ":\n";
        sales[i].inputSalesData();
    }

    cout << "\n\nSales Data Summary:\n";
    cout << left << setw(20) << "Product Name" << setw(15) << "Units Sold" << setw(15) << "Unit Price" << setw(15) << "Total Sales" << endl;
    cout << "=========================================================================\n";
    displayAllSalesData(sales, n);

    double totalRevenue = calculateTotalRevenue(sales, n);
    double averageSales = calculateAverageSales(sales, n);
    
    SalesData highest, lowest;
    findHighestLowestSales(sales, n, highest, lowest);

    cout << "\n\nTotal Revenue: $" << totalRevenue;
    cout << "\nAverage Sales: $" << averageSales;
    cout << "\nHighest Sales: " << highest.getProductName() << " with $" << highest.totalSales();
    cout << "\nLowest Sales: " << lowest.getProductName() << " with $" << lowest.totalSales();

    return 0;
}

void displayAllSalesData(SalesData sales[], int n) {
    for (int i = 0; i < n; ++i) {
        sales[i].displaySalesData();
    }
}

double calculateTotalRevenue(SalesData sales[], int n) {
    double total = 0;
    for (int i = 0; i < n; ++i) {
        total += sales[i].totalSales();
    }
    return total;
}

double calculateAverageSales(SalesData sales[], int n) {
    double total = calculateTotalRevenue(sales, n);
    return total / n;
}

void findHighestLowestSales(SalesData sales[], int n, SalesData &highest, SalesData &lowest) {
    highest = sales[0];
    lowest = sales[0];
    for (int i = 1; i < n; ++i) {
        if (sales[i].totalSales() > highest.totalSales()) {
            highest = sales[i];
        }
        if (sales[i].totalSales() < lowest.totalSales()) {
            lowest = sales[i];
        }
    }
}

