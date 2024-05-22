#!/usr/bin/python3

 ''' Functions to Add Users, Data Entries, and Logs '''


def add_user(name, email, password):
    conn = sqlite3.connect('showcase.db')
    cursor = conn.cursor()
    cursor.execute('''
        INSERT INTO Users (Name, Email, Password) VALUES (?, ?, ?)
    ''', (name, email, password))
    conn.commit()
    conn.close()

def add_data_entry(user_id, data):
    conn = sqlite3.connect('showcase.db')
    cursor = conn.cursor()
    cursor.execute('''
        INSERT INTO DataEntries (UserID, Data) VALUES (?, ?)
    ''', (user_id, data))
    conn.commit()
    conn.close()

def add_log(user_id, action):
    conn = sqlite3.connect('showcase.db')
    cursor = conn.cursor()
    cursor.execute('''
        INSERT INTO Logs (UserID, Action) VALUES (?, ?)
    ''', (user_id, action))
    conn.commit()
    conn.close()

