#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <limits>
#include <deque>
#include <windows.h> // For Terminal UI colors

using namespace std;

// Function to handle colors: 10=Green, 12=Red, 14=Yellow, 11=Cyan, 15=White
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Helper to calculate Simple Moving Average (SMA)
double calculateSMA(const deque<double>& window) {
    if (window.empty()) return 0.0;
    double sum = 0;
    for (double p : window) sum += p;
    return sum / window.size();
}

int main() {
    bool running = true;

    while (running) {
        system("cls"); // Clears the screen for a fresh UI
        setColor(14); // Yellow Header
        cout << "========================================" << endl;
        cout << "   FIN-INTEL PRO: TRADING TERMINAL      " << endl;
        cout << "========================================" << endl;
        setColor(15);

        string ticker, targetStart, targetEnd;
        cout << " -> Enter Ticker (or 'exit' to quit): "; cin >> ticker;
        if (ticker == "exit") break;

        cout << " -> Start Date (YYYY-MM-DD): "; cin >> targetStart;
        cout << " -> End Date   (YYYY-MM-DD): "; cin >> targetEnd;

        ifstream file("data/" + ticker + "_raw.csv");
        if (!file.is_open()) {
            setColor(12);
            cout << "\n [ERROR] Data for " << ticker << " not found!" << endl;
            setColor(15);
            system("pause");
            continue;
        }

        string line;
        getline(file, line); // Skip header

        deque<double> shortWindow, longWindow;
        double prevClose = -1.0;
        string lastDate, dateHigh, dateLow;
        double fClose = 0, fSMA5 = 0, fSMA20 = 0, fChange = 0, fVol = 0;
        double overallHigh = 0, overallLow = numeric_limits<double>::max();
        bool foundData = false;

        // Processing Logic
        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string date, s_open, s_high, s_low, s_close;
            getline(ss, date, ','); getline(ss, s_open, ','); getline(ss, s_high, ','); 
            getline(ss, s_low, ','); getline(ss, s_close, ',');

            try {
                double o = stod(s_open), h = stod(s_high), l = stod(s_low), c = stod(s_close);

                if (h > overallHigh) { overallHigh = h; dateHigh = date; }
                if (l < overallLow) { overallLow = l; dateLow = date; }

                shortWindow.push_back(c); if (shortWindow.size() > 5) shortWindow.pop_front();
                longWindow.push_back(c);  if (longWindow.size() > 20) longWindow.pop_front();

                if (date >= targetStart && date <= targetEnd) {
                    foundData = true;
                    lastDate = date;
                    fClose = c;
                    fChange = (prevClose > 0) ? ((c - prevClose) / prevClose) * 100 : 0;
                    fVol = ((h - l) / l) * 100;
                    fSMA5 = calculateSMA(shortWindow);
                    fSMA20 = calculateSMA(longWindow);
                }
                prevClose = c;
            } catch (...) { continue; }
        }

        file.close();

        // UI DISPLAY
        if (foundData) {
            cout << fixed << setprecision(2);
            cout << "\n--- ANALYSIS RESULTS ---" << endl;
            cout << " TICKER: "; setColor(11); cout << ticker << endl; setColor(15);
            cout << " DATE  : " << lastDate << endl;
            cout << " PRICE : "; setColor(15); cout << "$" << fClose;
            
            // Daily Change Color logic
            if (fChange >= 0) { setColor(10); cout << " (+" << fChange << "%)"; }
            else { setColor(12); cout << " (" << fChange << "%)"; }
            setColor(15); cout << endl;

            cout << " VOLATILITY: " << fVol << "%" << endl;
            cout << "----------------------------------------" << endl;

            cout << " SIGNAL: ";
            if (fSMA5 > fSMA20) {
                setColor(10); // GREEN for Buy
                cout << " *** BUY (Bullish Crossover) *** " << endl;
            } else {
                setColor(12); // RED for Sell
                cout << " *** SELL (Bearish Crossover) *** " << endl;
            }
            setColor(15);
            cout << " SMA 5: $" << fSMA5 << " | SMA 20: $" << fSMA20 << endl;
            
            cout << "\n--- HISTORICAL RECORDS ---" << endl;
            cout << " High: $" << overallHigh << " (" << dateHigh << ")" << endl;
            cout << " Low : $" << overallLow << " (" << dateLow << ")" << endl;
        } else {
            setColor(12); cout << "\n [!] No data found for that period." << endl; setColor(15);
        }

        cout << "========================================" << endl;
        system("pause"); // Holds the screen until you press a key
    }

    return 0;
}