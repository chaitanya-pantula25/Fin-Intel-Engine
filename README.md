# 📈 Fin-Intel Analytics Engine

A high-performance C++ and Python bridge for stock market analysis. This engine fetches real-world historical data and applies technical analysis to generate trading signals.

## 🚀 Key Features
* **Automated Data Fetching**: Uses Python (`yfinance`) to pull 5+ years of historical data for 30+ major stocks.
* **C++ Technical Engine**: Processes thousands of rows of CSV data in milliseconds.
* **Trend Analysis**: Implements 5-day and 20-day Simple Moving Averages (SMA) to identify crossovers.
* **Dynamic Trading Signals**: Generates real-time **BUY (Bullish)** and **SELL (Bearish)** recommendations.
* **Visual Terminal UI**: Color-coded output for better UX/UI within the command line.

## 🛠️ Tech Stack
- **Language**: C++, Python
- **Libraries**: `yfinance`, `pandas`, `windows.h` (for TUI colors)
- **Compiler**: g++

## 📦 Installation & Setup

1. **Clone the Repo**
   ```bash
   git clone [https://github.com/chaitanya-pantula25/Fin-Intel-Engine.git](https://github.com/chaitanya-pantula25/Fin-Intel-Engine.git)

2. **Fetch Market Data**
    ```bash 
    python scripts/fetch_data.py

3. **Compile and Launch Engine**
    ```
    g++ src/processor.cpp -o engine
    ./engine

## 📊 Logic & Methodology

The engine uses a sliding window approach. By storing the last 20 closing prices in a deque, it calculates the short-term and long-term trends.

Golden Cross (BUY): When the 5-day SMA rises above the 20-day SMA, indicating upward momentum.

Death Cross (SELL): When the 5-day SMA falls below the 20-day SMA, indicating a downward trend.

## 👤 Author
Chaitanya Pantula

GitHub: @chaitanya-pantula25
