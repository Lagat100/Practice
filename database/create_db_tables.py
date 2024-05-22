import sqlite3
from datetime import datetime

# Connect to the SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('showcase.db')
cursor = conn.cursor()

# Create Users table
cursor.execute('''
CREATE TABLE IF NOT EXISTS Users (
    UserID INTEGER PRIMARY KEY AUTOINCREMENT,
    Name TEXT NOT NULL,
    Email TEXT NOT NULL UNIQUE,
    Password TEXT NOT NULL,
    CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP
)
''')

# Create DataEntries table
cursor.execute('''
CREATE TABLE IF NOT EXISTS DataEntries (
    EntryID INTEGER PRIMARY KEY AUTOINCREMENT,
    UserID INTEGER NOT NULL,
    Data TEXT NOT NULL,
    Timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (UserID) REFERENCES Users(UserID)
)
''')

# Create Logs table
cursor.execute('''
CREATE TABLE IF NOT EXISTS Logs (
    LogID INTEGER PRIMARY KEY AUTOINCREMENT,
    UserID INTEGER NOT NULL,
    Action TEXT NOT NULL,
    Timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (UserID) REFERENCES Users(UserID)
)
''')

# Commit changes and close the connection
conn.commit()
conn.close()

