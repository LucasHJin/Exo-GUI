import tkinter as tk
import serial
import threading

#TODO: serial setup
PORT = 'COM5'
BAUD_RATE = 115200

s = serial.Serial(port=PORT, baudrate=BAUD_RATE, timeout=1)

#GUI below
root = tk.Tk()
root.title("Exo Software")
root.geometry("500x300")


err_label = tk.Label(root)
#values read from encoder
pos_label = tk.Label(root, text="Position: 0.0 rev")
vel_label = tk.Label(root, text="Velocity: 0.0 rev/s")
torq_label = tk.Label(root, text="Torque: 0.0 Nm")

#make form to send target position 
target_pos_label = tk.Label(root, text="Target Pos: ")
pos_entry = tk.Entry(root)

def send_pos():
    pos_str = pos_entry.get()
    try:
        pos = float(pos_str)
        line = f"P{pos}\n" #start with P to siganl pos
        s.write(line.encode('utf-8'))
    except ValueError as err:
        err_label.config(text=f"Error: {err}")

send_btn = tk.Button(root, text='Set pos', command=send_pos)

#make form to send target velocity
target_vel_label = tk.Label(root, text="Target vel: ")
vel_entry = tk.Entry(root)

def send_vel():
    vel_str = vel_entry.get()
    try:
        vel = float(vel_str)
        line = f"V{vel}\n" #start with V to signal vel
        s.write(line.encode('utf-8'))
    except ValueError as err:
        err_label.config(text=f"Error: {err}")

send_vel_btn = tk.Button(root, text='Set vel', command=send_vel)

#make form to send target position 
target_torq_label = tk.Label(root, text="Target torque: ")
torq_entry = tk.Entry(root)

def send_torq():
    torq_str = torq_entry.get()
    try:
        torq = float(torq_str)
        line = f"T{torq}\n" #start with P to siganl pos
        s.write(line.encode('utf-8'))
    except ValueError as err:
        err_label.config(text=f"Error: {err}")

send_btn = tk.Button(root, text='Set torq', command=send_torq)

#run serial loop
def serial_loop():
    while True:
        line = s.readline().decode('utf-8').strip()
        if line:
            try:
                pos_str, vel_str, torq_str = line.split(',')
                pos = float(pos_str)
                vel = float(vel_str)
                torq = float(torq_str)
                pos_label.config(text=f"Pos: {pos:.3f} rev")
                vel_label.config(text=f"Velocity: {vel:.3f} rev/s")
                torq_label.config(text=f"Torque: {torq:.3f} Nm")
            except ValueError as err:
                err_label.config(text=F"Error: {err}")

thread = threading.Thread(target=serial_loop, daemon=True)
thread.start()

root.mainloop()