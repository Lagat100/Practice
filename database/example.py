#!/usr/bin/python3
"""A function that queries creates a db"""


# Adding a new user
add_user('Lagat', 'lagat@outlook.com', 'password123')

# Retrieving user by email
user = get_user_by_email('lagat@otlook.com')
print(f"User: {user}")

# Adding a data entry for the user
if user:
    add_data_entry(user[0], 'Sample data entry')
    add_log(user[0], 'Added data entry')

# Retrieving data entries for the user
entries = get_data_entries_by_user(user[0])
print(f"Data Entries: {entries}")

# Retrieving logs for the user
logs = get_logs_by_user(user[0])
print(f"Logs: {logs}")

