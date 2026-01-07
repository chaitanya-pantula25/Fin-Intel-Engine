import yfinance as yf
import os

def fetch_massive_dataset():
    # 30 Diverse Stocks (Tech, Finance, Retail, Energy)
    tickers = [
        "AAPL", "MSFT", "GOOGL", "AMZN", "TSLA", "META", "NVDA", "BRK-B", "JPM", "V",
        "JNJ", "WMT", "PG", "MA", "UNH", "HD", "DIS", "BAC", "VZ", "KO",
        "PEP", "ADBE", "CMCSA", "NFLX", "T", "XOM", "CVX", "COST", "ABT", "AMD"
    ]
    
    os.makedirs('data', exist_ok=True)
    
    for ticker in tickers:
        print(f"Downloading history for {ticker}...")
        # Start from 2016 to ensure we cover 'after 2015'
        data = yf.download(ticker, start="2016-01-01")
        
        if not data.empty:
            data.to_csv(f"data/{ticker}_raw.csv")
            print(f"  [Done] {len(data)} rows saved.")

if __name__ == "__main__":
    fetch_massive_dataset()