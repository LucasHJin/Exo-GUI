import pandas as pd
import datetime
import os
import random
import time

# Set up CSV file for current session
LOG_FOLDER = "logs"
LOG_FILE = f"log_{datetime.datetime.now().strftime('%Y-%m-%d_%H-%M-%S')}.csv"
COLUMNS = ["Joint Angle", "Current", "Torque", "Angular Velocity", "Battery Voltage", "Battery Current", "Motor Temp"]

os.makedirs(LOG_FOLDER, exist_ok=True)
log_path = os.path.join(LOG_FOLDER, LOG_FILE)

df = pd.DataFrame(columns=COLUMNS)
df.to_csv(log_path)

try:
    while True:
        # Generate data as a test (will be replaced with real data)
        timestamp = pd.Timestamp.now(tz=None)
        angle = round(random.uniform(0, 10), 2)
        current = round(random.uniform(20, 30), 2)
        torque = round(random.uniform(0, 10), 2)
        velocity = round(random.uniform(10, 20), 2)
        voltage = round(random.uniform(20, 30), 2)
        current = round(random.uniform(0, 10), 2)
        temp = round(random.uniform(0, 10), 2)

        # Create a one-row DataFrame with timestamp as index
        new_row = pd.DataFrame([[angle, current, torque, velocity, voltage, current, temp]], columns=COLUMNS, index=[timestamp])

        # Append to CSV
        new_row.to_csv(log_path, mode='a', header=False)

        print(f"Logged: {timestamp} | {angle}, {current}, {current}")
        time.sleep(0.5)

except KeyboardInterrupt:
    print("\nLogging stopped.")
    print(f"Data saved to: {log_path}")