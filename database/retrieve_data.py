#!/usr/bin/python3
"""Functions to Retrieve Data"""

def get_user_by_email(email):
    conn = sqlite3.connect('showcase.db')
    cursor = conn.cursor()
    cursor.execute('''
        SELECT * FROM Users WHERE Email = ?
    ''', (email,))
    user = cursor.fetchone()
    conn.close()
    return user

def get_data_entries_by_user(user_id):
    conn = sqlite3.connect('showcase.db')
    cursor = conn.cursor()
    cursor.execute('''
        SELECT * FROM DataEntries WHERE UserID = ?
    ''', (user_id,))
    entries = cursor.fetchall()
    conn.close()
    return entries

def get_logs_by_user(user_id):
    conn = sqlite3.connect('showcase.db')
    cursor = conn.cursor()
    cursor.execute('''
        SELECT * FROM Logs WHERE UserID = ?
    ''', (user_id,))
    logs = cursor.fetchall()
    conn.close()
    return logs

