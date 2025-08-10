import tkinter as tk
import tkinter.ttk as ttk
from tkinter import filedialog

import datetime
import serial.tools.list_ports
import threading
import queue
import time
import re
import mimetypes
import codecs
from enum import Enum

import sys
import os
sys.path.insert(0, os.getcwd().rsplit("\\", 1)[0])

from common.codeless import *
from common.common import *


APP_TITLE = "Codeless Host"
DEFAULT_ICON_PHOTO = "Dialog_D-Symbol_Color_RGB_Small_icon.ico"
BINARY_MODE_COLOR = "RoyalBlue1"
COMMAND_MODE_COLOR = "yellow"
REPLY_STRING_COLOR = "green"
LINESEP = "\r\n"


class ThreadMeassage:
    def __init__(self):
        self.operation = Operations.NOP
        self.message = None


class Operations(Enum):
    NOP = 0
    DATA = 1
    CONTROL = 2


class Application:
    def __init__(self):
        self.codeless_peer = None
        self.connection_status = CodelessStatus.CODELESS_ERROR
        self.get_active_ports = True
        self.binary_mode_buttons = []
        self.input_commands = []
        self.send_filename = ""
        timestamp = datetime.datetime.now()
        self.console_log_file = timestamp.strftime("%d%m%Y_%H%M%S_") + "console.log"
        self.in_binary_mode = False
        self.esctime1 = 1000
        self.local_bin_esc = "+++"
        self.esctime2 = 1000
        self.bin_log_enabled = False
        self.bin_log_file = "bin.log"
        self.bin_timestamp = ""
        self.binary_data = False
        self.stop_event = None
        self.receive_queue = queue.Queue()
        self.communication_queue = queue.Queue()
        self.stop_batch_event = None
        self.in_parse_batch_file = False
        self.enable_uart_echo = True
        self.command_flags = {"AT+BINREQACK": False,
                              "AT+BINREQEXIT": False,
                              "AT+BINREQEXITACK": False,
                              "AT+BINRESUME": False,
                              "AT+BINESC": False,
                              "AT+BINESC=": False,
                              "ATE": False,
                              "ATE=0": False,
                              "ATE=1": False,
                              "AT": False,
                              "ATR": False}
        self.is_binreqexitack_pending = False
        self.local_bin_esc_sent = False

        self.init_window()

    def update_window_icon(self, window=None, filename=DEFAULT_ICON_PHOTO):
        """
        Set the icon of the window/frame widget
        """
        if window is None:
            window = self.window
        icon_path = resource_path(filename) + "\\" + filename
        window.iconbitmap(icon_path)

    def init_menu(self):
        """
        Create a Setup menu bar with Connect and Disconnect options
        """
        menu_bar = tk.Menu(self.window)

        # create a pull-down menu, and add it to the menu bar
        menu_setup = tk.Menu(menu_bar, tearoff=0)
        menu_setup.add_command(label="Connect", command=self.connect_frame)
        menu_setup.add_command(label="Disconnect", command=self.disconnect)
        menu_setup.add_separator()
        menu_setup.add_command(label="Exit", command=self.window_quit)
        menu_bar.add_cascade(label="Setup", menu=menu_setup)

        # display the menu
        self.window.config(menu=menu_bar)

    def set_window_position(self, window, parent_window=None, width=None, height=None):
        """
        Set window possition in the center of the screen
        """
        # get screen width and height
        if parent_window is None:
            screen_width = self.window.winfo_screenwidth()
            screen_height = self.window.winfo_screenheight()

            # calculate position x and y coordinates
            x = (screen_width / 2) - (width / 2)
            y = (screen_height / 2) - (height / 2)
        else:
            x = parent_window.winfo_x()
            y = parent_window.winfo_y()

        if (width is not None) and (height is not None):
            window.geometry('%dx%d' % (width, height))
        window.geometry('+%d+%d' % (x, y))

    def init_window(self):
        """
        Create the main window
        """
        self.window = tk.Tk()

        self.set_window_position(self.window, parent_window=None, width=680, height=740)

        self.update_window_title()
        self.update_window_icon()

        self.init_menu()

        self.tab_control = ttk.Notebook(self.window)
        self.tab_control.grid(row=0, column=0, padx=5, pady=5, sticky=tk.NSEW)

        self.create_console_tab(self.tab_control)

        # Check if self.communication_queue has any message to consume
        self.periodicCall()

        # window has fixed size
        self.window.resizable(False, False)
        self.window.mainloop()

    def create_console_tab(self, tab_control):
        """
        Create Console Tab, pass AT command to the device, send batch files for automated testing, enter binary mode
        and exchange files (binary or ASCII) with another BLE connected device
        """
        # Console Tab
        tab_console = tk.Frame(tab_control)
        tab_console.grid(sticky=tk.NSEW)
        self.tab_control.add(tab_console, text="Console")

        # Create MonitorFrame
        frame_monitor = tk.Frame(tab_console, borderwidth=2, relief=tk.GROOVE)
        frame_monitor.grid(row=0, column=0, padx=5, pady=5, sticky=tk.NSEW)

        self.text = tk.Text(frame_monitor, background="black")
        self.text.grid(row=0, column=0, sticky=tk.NSEW)
        # make console read-only
        self.text.bind("<Key>", lambda e: "break")
        sb = tk.Scrollbar(frame_monitor)
        sb.grid(row=0, column=1, sticky=tk.NS)
        sb.config(command=self.text.yview)
        self.text.config(yscrollcommand=sb.set)
        self.text.tag_config("command_mode", foreground=COMMAND_MODE_COLOR)
        self.text.tag_config("reply_string", foreground=REPLY_STRING_COLOR)
        self.text.tag_config("binary_mode", foreground=BINARY_MODE_COLOR)

        self.text.bind("<Button-3>", self.show_right_click_menu)
        self.right_click_menu = tk.Menu(self.text.master, tearoff=0)
        self.right_click_menu.add_command(label="Copy", command=self.copy_selection)
        self.right_click_menu.add_command(label="Select All", command=self.select_all)
        self.right_click_menu.add_command(label="Clear Monitor", command=self.clear_monitor)

        # Command EntryFrame
        frame_command = tk.LabelFrame(tab_console, text="Send Text", borderwidth=2, relief=tk.GROOVE)
        frame_command.grid(row=1, column=0, padx=5, pady=5, sticky=tk.NSEW)

        tk.Label(frame_command, text="Command").grid(row=1, sticky=tk.NSEW)
        self.combobox_commands = ttk.Combobox(frame_command, textvariable=tk.StringVar(), width=75)
        self.combobox_commands.grid(row=1, column=1, columnspan=2, sticky=tk.E, padx=5, pady=5)
        self.combobox_commands.focus_set()
        self.combobox_commands.bind("<<ComboboxSelected>>", self.combobox_commands.get())
        self.combobox_commands.bind("<Return>", self.get_input_string)

        button_send_cmd = tk.Button(frame_command, text="Send", height=1, width=5)
        button_send_cmd.grid(row=1, column=3, sticky=tk.W, padx=5, pady=5)
        button_send_cmd.bind("<Button-1>", self.get_input_string)

        # Widget for sending Batch file to device
        tk.Label(frame_command, text="File to Send").grid(row=2, column=0, sticky=tk.NSEW)
        self.entry_send_batch_file = tk.Entry(frame_command, width=67)
        self.entry_send_batch_file.grid(row=2, column=1)

        button_browse_batch_file = tk.Button(frame_command, text="Browse",
                                                  command=lambda: self.browse(self.entry_send_batch_file, 67), height=1, width=7)
        button_browse_batch_file.grid(row=2, column=2)

        self.button_send_batch_file = tk.Button(frame_command, text="Send Batch File", command=self.send_batch_file, height=1, width=12)
        self.button_send_batch_file.grid(row=2, column=3, sticky=tk.W, padx=5, pady=5)

        # Create Binary Mode Frame with all related commands
        frame_binary_mode = tk.LabelFrame(tab_console, text="Binary Mode", borderwidth=2, relief=tk.GROOVE)
        frame_binary_mode.grid(row=2, column=0, padx=5, pady=5, sticky=tk.NSEW)

        tk.Label(frame_binary_mode, text="Binary State").grid(row=2, sticky=tk.W, padx=5, pady=5)
        self.entry_bin_state = tk.Label(frame_binary_mode, text="OFF", bg=COMMAND_MODE_COLOR, width=15)
        self.entry_bin_state.grid(row=2, column=1, sticky=tk.W, columnspan=2)

        tk.Label(frame_binary_mode, text="Commands").grid(row=3, sticky=tk.W, padx=5, pady=5)

        tk.Label(frame_binary_mode, text="BINESC").grid(row=4, column=1, sticky=tk.W)
        tk.Label(frame_binary_mode, text="ESCTIME1").grid(row=4, column=2, sticky=tk.W)
        self.entry_esctime1_var = tk.IntVar()
        self.entry_esctime1_var.set("")
        self.entry_esctime1 = tk.Entry(frame_binary_mode, width=5, textvariable=self.entry_esctime1_var).grid(row=4, column=3)

        tk.Label(frame_binary_mode, text="ESCCHAR").grid(row=4, column=4, sticky=tk.W)
        self.entry_esctchar_var = tk.StringVar()
        self.entry_esctchar_var.set("")
        self.entry_esctchar = tk.Entry(frame_binary_mode, width=8, textvariable=self.entry_esctchar_var).grid(row=4, column=5)

        tk.Label(frame_binary_mode, text="ESCTIME2").grid(row=4, column=6, sticky=tk.W)
        self.entry_esctime2_var = tk.IntVar()
        self.entry_esctime2_var.set("")
        self.entry_esctime2 = tk.Entry(frame_binary_mode, width=5, textvariable=self.entry_esctime2_var).grid(row=4, column=7)
        button_set_esc = tk.Button(frame_binary_mode, text="Send", command=self.set_esc_sequence, height=1, width=5)
        button_set_esc.grid(row=4, column=9, sticky=tk.W, padx=5, pady=5)

        tk.Label(frame_binary_mode, text="BINREQ").grid(row=5, column=1, sticky=tk.W, columnspan=2)
        button_binreq = tk.Button(frame_binary_mode, text="Send", command=self.send_binreq, height=1, width=5)
        button_binreq.grid(row=5, column=3, sticky=tk.W, padx=5, pady=5)

        tk.Label(frame_binary_mode, text="ESC").grid(row=5, column=4, sticky=tk.W)
        button_esc = tk.Button(frame_binary_mode, text="Send", command=self.send_esc_sequence, height=1, width=5, state=tk.DISABLED)
        button_esc.grid(row=5, column=5, sticky=tk.W, padx=5, pady=5)
        self.binary_mode_buttons.append(button_esc)

        tk.Label(frame_binary_mode, text="BINRESUME").grid(row=5, column=6, sticky=tk.W)
        self.button_binresume = tk.Button(frame_binary_mode, text="Send", command=self.send_binresume, height=1, width=5, state=tk.DISABLED)
        self.button_binresume.grid(row=5, column=7, sticky=tk.W, padx=5, pady=5)

        tk.Label(frame_binary_mode, text="BINREQEXIT").grid(row=5, column=8, sticky=tk.W)
        self.button_binreqexit = tk.Button(frame_binary_mode, text="Send", command=self.send_binreqexit, height=1, width=5, state=tk.DISABLED)
        self.button_binreqexit.grid(row=5, column=9, sticky=tk.W, padx=5, pady=5)

        # Send Binary/ASCII file to device while in binary mode
        tk.Label(frame_binary_mode, text="File to Send").grid(row=6, sticky=tk.W)
        self.entry_send_file = tk.Entry(frame_binary_mode, width=57, state=tk.DISABLED)
        self.entry_send_file.grid(row=6, column=1, columnspan=6, sticky=tk.W)

        button_browse = tk.Button(frame_binary_mode, text="Browse",
                                       command=lambda: self.browse(self.entry_send_file, 57), height=1, width=7, state=tk.DISABLED)
        button_browse.grid(row=6, column=7)
        self.binary_mode_buttons.append(button_browse)

        button_send_file = tk.Button(frame_binary_mode, text="Send File", command=self.send_file, height=1, width=9, state=tk.DISABLED)
        button_send_file.grid(row=6, column=8, sticky=tk.W, padx=5, pady=5)
        self.binary_mode_buttons.append(button_send_file)

        self.button_save_log = tk.Button(frame_binary_mode, text="Save Log", command=self.save_bin_log, height=1, width=9, state=tk.DISABLED)
        self.button_save_log.grid(row=6, column=9, sticky=tk.W, padx=5, pady=5)
        self.binary_mode_buttons.append(self.button_save_log)

    def periodicCall(self):
        """
        Check every 200 ms if there is something new in the queue.
        """
        # handle all messages currently in the queue, if any
        while self.communication_queue.qsize():
            try:
                callback = self.communication_queue.get(0)
                callback()
            except queue.Empty:
                pass

        self.window.after(200, self.periodicCall)

    def get_active_uart_ports(self):
        if self.connection_status == CodelessStatus.CODELESS_ERROR or self.get_active_ports:
            port_list = []
            ports = serial.tools.list_ports.comports()
            for port, desc, hwid in sorted(ports):
                port_list.append("{}: {}".format(port, desc.split("(")[0]))
            self.combobox_port_names.config(values=port_list)

            self.window.after(1000, self.get_active_uart_ports)

            return port_list

    def port_selected(self, event):
        """
        Get selected COM port event handler
        """
        self.get_active_ports = False
        if self.codeless_peer is not None:
            if self.codeless_peer.device.isOpen():
                self.codeless_peer.device.close()
                self.connection_status = CodelessStatus.CODELESS_ERROR
        selected_port = self.combobox_port_names.get()
        self.port = selected_port.split(":")[0]

    def speed_selected(self, event):
        """
        Get selected speed event handler
        """
        speed = self.combobox_speed.get()
        self.speed = speed.split()[0]

    def data_selected(self, event):
        """
        Get selected data bits event handler
        """
        self.data = self.combobox_data.get()

    def parity_selected(self, event):
        """
        Get selected parity bits event handler
        """
        self.parity = self.combobox_parity.get()

    def stopbits_selected(self, event):
        """
        Get selected stop bits event handler
        """
        stopbits = self.combobox_stopbits.get()
        self.stopbits = stopbits.split()[0]

    def fc_selected(self, event):
        """
        Get selected flowcontrol event handler
        """
        self.flow_control = self.combobox_fc.get()

    def copy_selection(self, event=None):
        self.text.clipboard_clear()
        try:
            text = self.text.get(tk.SEL_FIRST, tk.SEL_LAST)
        except:
            text = ""
        self.text.clipboard_append(text)

    def select_all(self):
        self.text.tag_add(tk.SEL, "1.0", tk.END)
        self.text.mark_set(tk.INSERT, "1.0")
        self.text.see(tk.INSERT)

        return "break"

    def clear_monitor(self):
        self.text.delete("1.0", tk.END)

    def show_right_click_menu(self, event):
        try:
            self.right_click_menu.tk_popup(event.x_root, event.y_root, 0)
        finally:
            self.right_click_menu.grab_release()

    def send_command(self, command, timeout=0.05, car_ret=True):
        """
        Send a string to connected device.
        When sending escape sequence carriage return character is not needed.
        """
        if car_ret:
            command = command + "\r"
        self.codeless_peer.device.write(command)

        # Add a small delay between UART write/read operations
        time.sleep(timeout)

    def append_to_console_text_widget(self, command, tag="command_mode"):
        """
        Append to console text widget with different colors, according to given tag, everything that is written or
        read from device's UART
        """
        prefix = ""
        suffix = ""
        if tag == "command_mode":
            prefix = "--> "
            suffix = "\n"
        elif tag == "reply_string": # or tag == "binary_string":
            prefix = "<-- "
            suffix = "\n"

        if isinstance(command, unicode):
            command = command.encode("ascii", "replace")

        f = open(self.console_log_file, "a+")
        f.write(prefix)
        self.text.insert(tk.END, prefix, tag)
        for line in command.splitlines():
            if line:
                f.write(line + suffix)
                self.text.insert(tk.END, line + suffix, tag)
        f.close()
        self.text.see(tk.END)

        if self.bin_log_enabled:
            if self.binary_data:
                f = open(self.bin_timestamp + self.bin_log_file, "ab+")
                self.binary_data = False
            else:
                f = open(self.bin_timestamp + self.bin_log_file, "a+")
            f.write(str(command))
            f.close()

    def get_input_string(self, event):
        """
        Get input string from Command widget and send it to device.
        If device is in binary mode just append the string to console widget without newline
        """
        # check connection status before sending anything to device
        if self.connection_status == CodelessStatus.CODELESS_OK:
            input_str = self.combobox_commands.get().strip()
            if len(input_str) > 0 and not self.in_binary_mode:
                # remove any white space at the beginning of the command
                if input_str.find("AT") > 0:
                    command = input_str[input_str.find("AT"):]
                else:
                    command = input_str

                if command == "AT+BINREQ":
                    self.send_binreq()
                else:
                    if self.command_flags.has_key(command):
                        self.command_flags[command] = True

                    if "AT+BINESC=" in command:
                        self.command_flags["AT+BINESC="] = True
                        if not self.enable_uart_echo:
                            self.new_escape_seq = command.split("=")[1]

                    self.append_to_console_text_widget(command)
                    # if input is in unicode encoding don't send it to Device
                    if not isinstance(command, unicode):
                        self.send_command(command, 0.5)
                    else:
                        self.append_to_console_text_widget("Invalid Input", "reply_string")

                # keep a list of all typed commands
                if input_str not in self.input_commands:
                    self.input_commands.append(input_str)

                self.combobox_commands["values"] = self.input_commands
                self.combobox_commands.delete(0, tk.END)
            elif self.in_binary_mode:
                if self.local_bin_esc in input_str:
                    self.send_esc_sequence()
                else:
                    self.append_to_console_text_widget(input_str, "binary_mode")
                    self.send_command(input_str, 0.1, False)

    def update_window_title(self, title=APP_TITLE):
        """
        Update main window title to indicate if any COM port is connected or not
        """
        self.window.title(title)

    def connect_frame(self):
        """
        Create a popup window to setup a serial connection
        """
        self.get_active_ports = True
        # create a separate top-level window
        self.top_level_connect_frame = tk.Toplevel(self.window)
        self.set_window_position(window=self.top_level_connect_frame, parent_window=self.window)
        self.top_level_connect_frame.focus_set()
        self.top_level_connect_frame.wm_title("Serial Port Setup")
        self.update_window_icon(self.top_level_connect_frame)
        # window has fixed size
        self.top_level_connect_frame.resizable(False, False)

        # Pop-down lists of retrieved Ports, Speed, Data Bits, Parity Bits, Stop Bits and Flow Control
        tk.Label(self.top_level_connect_frame, text="Port").grid(row=0, column=0, sticky=tk.W, padx=5, pady=(25, 5))
        self.combobox_port_names = ttk.Combobox(self.top_level_connect_frame, textvariable=tk.StringVar(), width=28)
        self.combobox_port_names.grid(row=0, column=1, sticky=tk.E, padx=5, pady=(25, 5))
        if self.connection_status == CodelessStatus.CODELESS_ERROR:
            self.port_list = self.get_active_uart_ports()
            try:
                self.port = self.port_list[0].split(":")[0]
            except:
                self.error_popup_window("Error", "No available port.")
            self.combobox_port_names["values"] = self.port_list
            self.combobox_port_names.current(0)
        else:
            if self.get_active_ports:
                self.get_active_uart_ports()
            idx = 0
            for port in self.port_list:
                if self.port in port:
                    break
                idx = idx + 1
            self.combobox_port_names["values"] = self.port_list
            self.combobox_port_names.current(idx)
        self.combobox_port_names.bind("<<ComboboxSelected>>", self.port_selected)

        tk.Label(self.top_level_connect_frame, text="Speed").grid(row=1, column=0, sticky=tk.W, padx=5, pady=5)
        self.combobox_speed = ttk.Combobox(self.top_level_connect_frame, textvariable=tk.StringVar(), width=28)
        self.combobox_speed.grid(row=1, column=1, sticky=tk.E, padx=5, pady=5)
        speed_list = ["110", "300", "600", "1200", "2400", "4800", "9600", "14400", "19200", "38400", "57600", "115200",
                      "230400", "460800", "921600"]
        self.combobox_speed["values"] = speed_list
        if self.connection_status == CodelessStatus.CODELESS_ERROR:
            self.combobox_speed.current(10)
        else:
            self.combobox_speed.current(speed_list.index(self.speed))
        self.speed = speed_list[10]
        self.combobox_speed.bind("<<ComboboxSelected>>", self.speed_selected)

        tk.Label(self.top_level_connect_frame, text="Data Bits").grid(row=2, column=0, sticky=tk.W, padx=5, pady=5)
        self.combobox_data = ttk.Combobox(self.top_level_connect_frame, textvariable=tk.StringVar(), width=28)
        self.combobox_data.grid(row=2, column=1, sticky=tk.E, padx=5, pady=5)
        data_list = ["5 bits", "6 bits", "7 bits", "8 bits"]
        self.combobox_data["values"] = data_list
        if self.connection_status == CodelessStatus.CODELESS_ERROR:
            self.combobox_data.current(3)
        else:
            idx = 0
            for data in data_list:
                if self.data in data:
                    break
                idx = idx + 1
            self.combobox_data.current(idx)
        self.data = data_list[3].split()[0]
        self.combobox_data.bind("<<ComboboxSelected>>", self.data_selected)

        tk.Label(self.top_level_connect_frame, text="Parity Bits").grid(row=3, column=0, sticky=tk.W, padx=5, pady=5)
        self.combobox_parity = ttk.Combobox(self.top_level_connect_frame, textvariable=tk.StringVar(), width=28)
        self.combobox_parity.grid(row=3, column=1, sticky=tk.E, padx=5, pady=5)
        parity_list = ["None", "Odd", "Even", "Mark", "Space"]
        self.combobox_parity["values"] = parity_list
        if self.connection_status == CodelessStatus.CODELESS_ERROR:
            self.combobox_parity.current(0)
        else:
            self.combobox_parity.current(parity_list.index(self.parity))
        self.parity = parity_list[0]
        self.combobox_parity.bind("<<ComboboxSelected>>", self.parity_selected)

        tk.Label(self.top_level_connect_frame, text="Stop Bits").grid(row=4, column=0, sticky=tk.W, padx=5, pady=5)
        self.combobox_stopbits = ttk.Combobox(self.top_level_connect_frame, textvariable=tk.StringVar(), width=28)
        self.combobox_stopbits.grid(row=4, column=1, sticky=tk.E, padx=5, pady=5)
        stopbits_list = ["1 bit", "2 bits"]
        self.combobox_stopbits["values"] = stopbits_list
        if self.connection_status == CodelessStatus.CODELESS_ERROR:
            self.combobox_stopbits.current(0)
        else:
            idx = 0
            for sbit in stopbits_list:
                if self.stopbits in sbit:
                    break
                idx = idx + 1
            self.combobox_stopbits.current(idx)
        self.stopbits = stopbits_list[0].split()[0]
        self.combobox_stopbits.bind("<<ComboboxSelected>>", self.stopbits_selected)

        tk.Label(self.top_level_connect_frame, text="Flow Control").grid(row=5, column=0, sticky=tk.W, padx=5, pady=5)
        self.combobox_fc = ttk.Combobox(self.top_level_connect_frame, textvariable=tk.StringVar(), width=28)
        self.combobox_fc.grid(row=5, column=1, sticky=tk.E, padx=5, pady=5)
        fc_list = ["None", "RTS/CTS", "DTR/DSR"]
        self.combobox_fc["values"] = fc_list
        if self.connection_status == CodelessStatus.CODELESS_ERROR:
            self.combobox_fc.current(0)
        else:
            self.combobox_fc.current(fc_list.index(self.flow_control))
        self.flow_control = fc_list[0]
        self.combobox_fc.bind("<<ComboboxSelected>>", self.fc_selected)

        # Connect button to perform serial connection
        button_connect = tk.Button(self.top_level_connect_frame, text="OK", command=self.com_connect)
        button_connect.grid(row=6, pady=20, columnspan=2)

    def com_connect(self):
        """
        Open connection with selected com port
        """
        self.codeless_peer = codeless(CodelessLink.UART, self.port)
        try:
            self.connection_status = self.codeless_peer.connect(self.speed,
                                                                self.data,
                                                                self.parity,
                                                                self.stopbits,
                                                                self.flow_control)
            if self.connection_status == CodelessStatus.CODELESS_OK:
                self.get_active_ports = False
                # Create a daemon thread that reads and parses everything that is received from selected com port
                self.stop_event = threading.Event()
                thread = threading.Thread(target=self.receive, args=())
                thread.daemon = True  # Daemonize thread
                thread.start()  # Start the execution

                # Update self.window title as a successful connection indication with selected port
                self.update_window_title(title="%s - %s" % (self.port, APP_TITLE))

                # Destroy popup window
                self.top_level_connect_frame.destroy()

                # get UART echo state
                self.get_uart_echo_state()

                # get escape sequence
                self.get_bin_esc_sequence()

                # show values in BINESC entry widgets
                self.update_binesc_entry_widgets()
            else:
                self.error_popup_window("Connection refused",
                                        "Connection Failed to %s.\n Try to select another COM port" % self.port)
        except:
            self.error_popup_window("Connection refused",
                                    "Connection Failed to %s.\n Try to select another COM port" % self.port)

    def disconnect(self):
        """
        Close connection with selected com port
        """
        if self.connection_status == CodelessStatus.CODELESS_OK:
            # Set self.stop_event flag to terminate while loop of receive thread
            self.stop_event.set()

            # stop batch file execution if running
            if self.stop_batch_event is not None:
                if not self.stop_batch_event.is_set():
                    self.stop_batch_file()

            # change view of button_save_log to Raised
            if self.button_save_log.config()["relief"][4] == tk.SUNKEN:
                self.bin_log_enabled = False
                self.button_save_log.config(relief=tk.RAISED)

            # Disconnect com port
            self.codeless_peer.stop()
            self.connection_status = CodelessStatus.CODELESS_ERROR
            self.get_active_ports = True

            # Restore binary mode and any other indications to default
            self.in_binary_mode = False
            self.bin_log_enabled = False
            self.binary_data = False
            self.in_parse_batch_file = False
            self.is_binreqexitack_pending = False
            self.local_bin_esc_sent = False

            # clear all command flags
            self.command_flags = self.command_flags.fromkeys(self.command_flags, False)

            # Update binary mode indication
            self.update_indication(COMMAND_MODE_COLOR)
            self.button_binresume["state"] = tk.DISABLED
            self.button_binreqexit["state"] = tk.DISABLED

            self.combobox_commands.set("")

            # remove displayed values in BINESC entry widgets
            self.update_binesc_entry_widgets(reset=True)

            self.update_window_title()

    def is_hex(self, value):
        try:
            int(value, 16)
            return True
        except:
            return False

    def is_ascii(self, value):
        try:
            value.decode("ascii")
            return True
        except:
            return False

    def validate_input(self, var):
        try:
            new_value = var.get()
            if isinstance(var, tk.IntVar) and new_value > 0:
                return True, new_value
            elif isinstance(var, tk.StringVar):
                if self.is_hex(new_value) and (len(new_value) >= 6) and (len(new_value) <= 8):
                    if not new_value.startswith("0x") and len(new_value) == 6:
                        new_value = "0x" + new_value
                    elif not (new_value.startswith("0x") and len(new_value) == 8):
                        return False, None
                    return True, new_value
                elif self.is_ascii(new_value) and len(new_value) == 3:
                    return True, "0x" + new_value.encode("hex")
                return False, None
            else:
                return False, None
        except :
            return False, None

    def window_quit(self):
        """
        Disconnect from COM port and the quit window
        """
        self.disconnect()
        self.window.quit()

    def send_binreq(self):
        """
        Send AT+BINREQ
        """
        # check connection status before sending anything to device
        if self.connection_status == CodelessStatus.CODELESS_OK:
            self.append_to_console_text_widget("AT+BINREQ")
            self.send_command("AT+BINREQ")

    def send_esc_sequence(self):
        """
        Send escape sequence to device to signal the exit from binary mode and enter local command mode.
        If AT+BINREQEXIT is issue after that escape sequence is sent to remote device as well.
        """
        # check connection status before sending anything to device
        if self.connection_status == CodelessStatus.CODELESS_OK:
            self.in_binary_mode = False
            self.local_bin_esc_sent = True

            self.append_to_console_text_widget(self.local_bin_esc, "binary_mode")
            self.send_command(self.local_bin_esc, 0.1, False)

            # update binary mode indication that device has left binary mode
            self.update_indication(COMMAND_MODE_COLOR)

    def set_esc_sequence(self, event=None):
        """
        Change the sequence that can exit device from binary mode
        eg.AT+BINESC=1000,0x2A2A2A,1000 for *** as escape sequence
        """
        # check connection status before sending anything to device
        if self.connection_status == CodelessStatus.CODELESS_OK:
            success_time1, esctime1 = self.validate_input(self.entry_esctime1_var)
            success_char, escchar = self.validate_input(self.entry_esctchar_var)
            success_time2, esctime2 = self.validate_input(self.entry_esctime2_var)
            if success_time1 and success_char and success_time2:
                parameters = str(esctime1) + "," + escchar + "," + str(esctime2)
                command = "AT+BINESC=" + parameters

                if not self.enable_uart_echo:
                    self.new_escape_seq = parameters
                self.command_flags["AT+BINESC="] = True
                self.append_to_console_text_widget(command)
                self.send_command(command)
            else:
                # update values in BINESC entry widgets with the current ones
                self.update_binesc_entry_widgets()
                self.error_popup_window("Error",
                                        "Please try again using following format\n "
                                        "<int(msec)>,<3 bytes hex/ascii value>,<int(msec)>")

    def send_binreqexit(self):
        """
        Send AT+BINREQEXIT to device and exit binary mode.
        """
        # check connection status before sending anything to device
        if self.connection_status == CodelessStatus.CODELESS_OK:
            self.command_flags["AT+BINREQEXIT"] = True
            self.append_to_console_text_widget("AT+BINREQEXIT")
            self.send_command("AT+BINREQEXIT")

    def send_binresume(self):
        """
        Send AT+BINRESUME to device to exit local command mode and enter binary mode again.
        """
        # check connection status before sending anything to device
        if self.connection_status == CodelessStatus.CODELESS_OK:
            self.command_flags["AT+BINRESUME"] = True
            self.append_to_console_text_widget("AT+BINRESUME")
            self.send_command("AT+BINRESUME")

    def browse(self, parent_widget, width):
        """
        Create a file dialog object to show a dialog and return the selected filename
        """
        self.send_filename = filedialog.askopenfilename(initialdir=os.getcwd(), title="Select A File",
                                               filetype=(("log files", "*.log"), ("log files", "*.txt"),
                                                         ("all files", "*.*")))
        filename = os.path.basename(self.send_filename)
        label = ttk.Label(parent_widget, text=filename, width=width)
        label.grid(column=1, row=2)
        label.configure(text=filename, background="white")

    def error_popup_window(self, title, text, parent_window=None):
        """
        Create a pop-up toplevel window to inform the user with an error message
        """
        if parent_window is None:
            parent_window = self.window
        top_level = tk.Toplevel(self.window)
        self.set_window_position(window=top_level, parent_window=parent_window)
        top_level.focus_set()
        top_level.wm_title(title)
        # window has fixed size
        top_level.resizable(False, False)

        self.update_window_icon(top_level)

        lbl = tk.Label(top_level, text=text, height=2)
        lbl.pack(pady=10, padx=60)
        button_exit = tk.Button(top_level, text="QUIT", command=top_level.destroy)
        button_exit.pack(pady=20)

    def send_file(self):
        """
        Send either binary or ascii file
        """
        # check connection status before sending anything to device
        if self.connection_status == CodelessStatus.CODELESS_OK:
            if self.send_filename:
                # Identify MIME type associated with the filename extension
                # application/octet-stream refers to binary files
                if mimetypes.guess_type(self.send_filename)[0] == "application/octet-stream":
                    self.append_to_console_text_widget(open(self.send_filename, "rb").read(), "binary_mode")
                    self.codeless_peer.device.write(open(self.send_filename, "rb").read())
                else:
                    self.append_to_console_text_widget(open(self.send_filename, "r").read(), "binary_mode")
                    self.codeless_peer.device.write(open(self.send_filename, "r").read())
            else:
                self.error_popup_window("Error", "Please select a file before trying to send it")

    def stop_batch_file(self):
        """
        Stops the execution of batch file before its actual end
        """
        self.in_parse_batch_file = False
        self.stop_batch_event.set()

        # change button configuration to indicate to the user that SEND BATCH FILE operation is active again
        self.button_send_batch_file.config(relief=tk.RAISED, text="SEND BATCH FILE")

    def send_batch_file(self):
        """
        Send a batch file to device.
        """
        if self.connection_status == CodelessStatus.CODELESS_OK:
            if self.send_filename:
                if not self.stop_batch_event:
                    # change button configuration to indicate the user that execution fo the file has started
                    self.button_send_batch_file.config(relief=tk.SUNKEN, text="Stop Execution")
                    self.stop_batch_event = threading.Event()

                    # create a thread to parse the file, wait for the command reply and validate the output
                    thread = threading.Thread(target=self.parse_batch_file, args=())
                    thread.daemon = True  # Daemonize thread
                    thread.start()  # Start the execution
                else:
                    message = ThreadMeassage()
                    message.operation = Operations.CONTROL
                    message.message = "Close"
                    self.receive_queue.put(message)
            else:
                self.error_popup_window("Error", "Please select a file before trying to send it")

    def parse_batch_file(self):
        """
        Parse batch file.
        Lines that start with --> indicate the input command that will be sent to device
        Lines that start with <-- indicate the output (reply string) of the above command
        Lines that end with OK or ERROR are the end of current command sequence
        Lines that start without any of the above indications are the values that need to be validated.
        eg. of a batch file
            --> AT+GAPSCAN
            <-- AT+GAPSCAN
            OK
            --> AT+GAPCONNECT=F4:3F:DF:34:31:89,R
            <-- AT+GAPCONNECT=F4:3F:DF:34:31:89,R
            +CONNECTED
            OK
            --> AT+GAPSTATUS
            <-- AT+GAPSTATUS
            1,1
            OK
        """
        reply_string = None
        self.in_parse_batch_file = True
        termination_list = ("OK", "ERROR")
        with open(self.send_filename, "r") as f:
            lines = f.readlines()

        thread_message = ThreadMeassage()
        for line in lines:
            reply_received = False
            if self.stop_batch_event.is_set():
                self.stop_batch_event = None
                break

            # Input: command that will be written to device
            if line.startswith("-->"):
                at_cmd_str = line[line.find("AT"):].rstrip("\r\n")
                self.append_to_console_text_widget(at_cmd_str)
                self.send_command(at_cmd_str)

                for i in range(0, 30):
                    try:
                        # block until an item is available, don't wait if timeout has passed
                        thread_message = self.receive_queue.get(block=True, timeout=1)
                        if thread_message:
                            reply_received = True
                            break
                    except: # if no item was available within timeout, Empty exception is raised
                        pass

                if not reply_received:
                    reply_string = "\r\n\r\nERROR\r\n"
                    thread_message.operation = Operations.CONTROL
                    thread_message.message = reply_string

                if thread_message.operation == Operations.CONTROL:
                    self.stop_batch_file()
                elif thread_message.operation == Operations.DATA:
                    reply_string = thread_message.message
                    no_newline = reply_string.replace("\n", "")

                    # keep only one occurrence of "\r" in reply_string
                    single_car_ret = re.sub(r"(\r)(?=\1)", "", no_newline)
                    reply_string = single_car_ret.splitlines()

            # Output: command reply, usually the command string itself
            elif line.startswith("<--"):
                cmd_str = line.replace("<-- ", "").strip()

                if cmd_str not in reply_string[0]:
                    self.stop_batch_file()

            # Command termination string
            elif line.strip() in termination_list:
                if reply_string:
                    termination_str = line.strip()
                    if termination_str not in reply_string[len(reply_string)-1]:
                        self.stop_batch_file()

            # Validation: check that reply string
            else:
                if reply_string:
                    validation_str = line.strip()
                    if validation_str not in reply_string[1]:
                        self.stop_batch_file()

        # Stop the execution since all commands are parsed
        self.in_parse_batch_file = False
        self.stop_batch_event = None
        self.button_send_batch_file.config(relief=tk.RAISED, text="Send Batch File")

    def receive(self):
        # # AT : for local commands with local reply terminating with any of \r\nOK\r\n or \r\nERROR\r\n
        # # LINESEP + UNSOLICITED_PREFIX + LINESEP: for the unsolicited notifications
        # # \r\nAT+BINREQ\r\r\n, \r\nAT+BINREQACK\r\r\n and \r\nAT+BINREQEXITACK\r\r\n: for notifications from remote
        unsolicited_str = ["\r\n+READY\r\n",
                           "\r\n+AWAKE\r\n",
                           "\r\n+CONNECTED\r\n",
                           "\r\n+DISCONNECTED\r\n",
                           "\r\n+BONDING SUCCESS\r\n",
                           "\r\n+PASSCODE REQ RECEIVED\r\n",
                           "\r\n+SECURITY REQ. AUTH LEVEL: ",
                           "\r\n+BINARY MODE SUPPORTED\r\n",
                           "\r\n+COMMAND MODE SUPPORTED\r\n",
                           "\r\n+ECHO ON\r\n",
                           "\r\n+ECHO OFF\r\n",
                           "\r\n+ESC SEQ\r\n"]
        binary_unsolicited_str = ["\r\n+BINREQ\r\n\r\n",
                                  "\r\n+BINREQACK\r\n\r\n",
                                  "\r\n+BINREQEXITACK\r\n\r\n",
                                  "\r\n+BINREQEXIT\r\n\r\n"]

        current_line = ""
        # start_time = time.time()
        thread_message = ThreadMeassage()
        while not self.stop_event.is_set():
            try:
                bytes_to_read = self.codeless_peer.device.inWaiting()
                if bytes_to_read > 0:

                    # Serial read
                    current_line = current_line + self.codeless_peer.device.read(self.codeless_peer.device.inWaiting())

                    # Parse and handle
                    if not len(current_line) > 0 or current_line.endswith("ERROR\r\n"):
                        # Append reply to widget
                        self.append_to_console_text_widget(current_line, "reply_string")

                        # execution of batch file, put command reply to the queue
                        if self.in_parse_batch_file:
                            thread_message.operation = Operations.DATA
                            thread_message.message = current_line
                            self.receive_queue.put(thread_message)

                        # Reset command flag if set, since command returned with Error
                        for key in self.command_flags.keys():
                            if self.command_flags[key]:
                                self.command_flags[key] = False

                        # Reset current line
                        current_line = ""
                        # # Calculate time elapsed
                        # start_time = time.time()

                    # When sending escape sequence or ATE command (in case of UART echo off),
                    # the reply is only \r\nOK\r\n
                    elif (self.local_bin_esc_sent and current_line == "\r\nOK\r\n") or \
                            ((self.command_flags["ATE"] or self.command_flags["ATE=1"] or self.command_flags["ATE=0"])
                             and current_line.endswith("\r\nOK\r\n")):
                        if self.command_flags["ATE"]:
                            self.command_flags["ATE"] = False
                            current_line_split = current_line.split()
                            self.enable_uart_echo = bool(int(current_line_split[len(current_line_split)-2]))
                        elif self.command_flags["ATE=1"]:
                            self.command_flags["ATE=1"] = False
                            self.enable_uart_echo = True
                        elif self.command_flags["ATE=0"]:
                            self.command_flags["ATE=0"] = False
                            self.enable_uart_echo = False
                        else:
                            self.local_bin_esc_sent = False

                        self.append_to_console_text_widget(current_line, "reply_string")

                        # Reset current line
                        current_line = ""
                        # # Calculate time elapsed
                        # start_time = time.time()

                    elif current_line.startswith("\r\n+PRINT:") and current_line.endswith(LINESEP):
                        self.append_to_console_text_widget(current_line, "reply_string")
                        # Reset current line
                        current_line = ""

                    # If unsolicited string is received then just append it to widget and clear current_line
                    # Check if current_line:
                    # 1. contains unsolicited_str
                    # 2. doesn't start with AT to skip AT+GAPCONNECT command reply and wait for OK
                    # "AT+GAPCONNECT=F4:3F:DF:34:31:89,R\r\r\nCONNECTING\r\n\r\n\r\n+CONNECTED\r\n"
                    # or ATR command is received - ATR\r\x00\r\n\r\n+READY\r\n
                    # 3. ends with LINESEP to wait until LINESEP is received and print whole message
                    elif any(x in current_line for x in unsolicited_str) and \
                            (not current_line.startswith("AT") or self.command_flags["ATR"]) and \
                            current_line.endswith(LINESEP):
                        self.append_to_console_text_widget(current_line, "reply_string")

                        # unsolicited_str indicating connection establishment, check binary mode state
                        if any(x in current_line for x in ("+READY", "+AWAKE", "+CONNECTED",
                                                           "+BINARY MODE SUPPORTED", "+COMMAND MODE SUPPORTED")):
                            if self.in_binary_mode:
                                self.in_binary_mode = False
                                self.update_indication(COMMAND_MODE_COLOR)

                        # local or remote platform reset, reset UART echo mode and escape sequence to default
                        if self.command_flags["ATR"] or "+READY" in current_line:
                            self.command_flags["ATR"] = False
                            self.enable_uart_echo = True
                            self.local_bin_esc = "+++"
                        # remote host/device changed enabled UART echo mode, update state
                        elif "ECHO ON" in current_line:
                            self.enable_uart_echo = True
                        # remote host/device changed disabled UART echo mode, update state
                        elif "ECHO OFF" in current_line:
                            self.enable_uart_echo = False
                        # remote host/device changed escape sequence, update sequence
                        elif "ESC SEQ" in current_line:
                            self.get_bin_esc_sequence()

                        # execution of batch file, put command reply to the queue
                        if self.in_parse_batch_file:
                            thread_message.operation = Operations.DATA
                            thread_message.message = current_line
                            self.receive_queue.put(thread_message)

                        # Reset current line
                        current_line = ""
                        # # Calculate time elapsed
                        # start_time = time.time()

                    # If the user writes to codeless device any of [AT+BINREQ, AT+BINREQACK, AT+BINREQEXITACK],
                    # which will be sent to remote peer over BLE, before COMMAND MODE SUPPORTED\r\n received,
                    # only echo string of typed command will be printed without executing the command
                    elif (current_line.startswith("AT+BINREQ\r") or current_line.startswith("AT+BINREQACK\r") or
                          current_line.startswith("AT+BINREQEXITACK\r")) and current_line.endswith("SUPPORTED\r\n") \
                            and "OK" not in current_line:
                        self.append_to_console_text_widget(current_line, "reply_string")

                        # Reset current line
                        current_line = ""
                        # # Calculate time elapsed
                        # start_time = time.time()

                    # # Binary mode unsolicited notifications
                    # # \r\n+BINREQ\r\n\r\n, \r\n+BINREQACK\r\n\r\n, \r\n+BINREQEXITACK\r\n\r\n
                    elif any(x in current_line for x in binary_unsolicited_str):
                        self.append_to_console_text_widget(current_line, "reply_string")

                        # received +BINREQ from remote, auto reply with AT+BINREQACK
                        if "\r\n+BINREQ\r\n\r\n" == current_line:
                            time.sleep(0.5)
                            self.command_flags["AT+BINREQACK"] = True
                            self.append_to_console_text_widget("AT+BINREQACK")
                            self.send_command("AT+BINREQACK")

                        # received +BINREQACK from remote, update binary mode indication
                        if "\r\n+BINREQACK\r\n\r\n" == current_line:
                            self.in_binary_mode = True
                            self.update_indication(BINARY_MODE_COLOR)

                        # received +BINREQEXITACK from remote, update binary mode indication
                        if "\r\n+BINREQEXITACK\r\n\r\n" == current_line:
                            self.in_binary_mode = False
                            self.update_indication(COMMAND_MODE_COLOR)

                        # Reset current line
                        current_line = ""
                        # # Calculate time elapsed
                        # start_time = time.time()

                    # # AT command in current_line, read until OK\r\n received
                    # # or AT command reply with UART echo off
                    elif (current_line.startswith("AT") and current_line.endswith("OK\r\n")) or\
                            (not self.enable_uart_echo and current_line.startswith(LINESEP) and current_line.endswith("OK\r\n")):
                        self.append_to_console_text_widget(current_line, "reply_string")

                        # execution of batch file, put command reply to the queue
                        if self.in_parse_batch_file:
                            thread_message.operation = Operations.DATA
                            thread_message.message = current_line
                            self.receive_queue.put(thread_message)

                        # received AT+BINREQACK or its reply, so update binary mode indication
                        if ("AT+BINREQACK\r" in current_line) or self.command_flags["AT+BINREQACK"]:
                            self.command_flags["AT+BINREQACK"] = False
                            self.in_binary_mode = True
                            self.update_indication(BINARY_MODE_COLOR)

                        # received AT+BINREQEXIT\r or its reply, so update binary mode indication
                        if ("AT+BINREQEXIT\r" in current_line) or self.command_flags["AT+BINREQEXIT"]:
                            self.command_flags["AT+BINREQEXIT"] = False
                            self.in_binary_mode = False
                            self.update_indication(COMMAND_MODE_COLOR)

                        # received AT+BINREQEXITACK or its reply, so update binary mode indication
                        if ("AT+BINREQEXITACK\r" in current_line) or self.command_flags["AT+BINREQEXITACK"]:
                            self.command_flags["AT+BINREQEXITACK"] = False
                            self.in_binary_mode = False
                            self.update_indication(COMMAND_MODE_COLOR)

                        # received AT reply or its reply, so send AT+BINREQEXITACK
                        if (("AT\r" in current_line) or not self.enable_uart_echo) and self.is_binreqexitack_pending:
                            self.is_binreqexitack_pending = False
                            if "+DISCONNECTED" in current_line:
                                self.in_binary_mode = False
                                self.update_indication(COMMAND_MODE_COLOR)
                            else:
                                self.command_flags["AT+BINREQEXITACK"] = True
                                self.append_to_console_text_widget("AT+BINREQEXITACK")
                                self.send_command("AT+BINREQEXITACK")

                        # receive AT+BINRESUME or its reply,so resume binary mode and update indication
                        if ("AT+BINRESUME\r" in current_line) or self.command_flags["AT+BINRESUME"]:
                            self.command_flags["AT+BINRESUME"] = False
                            self.in_binary_mode = True
                            self.update_indication(BINARY_MODE_COLOR)

                        # user changed binary escape sequence
                        if self.command_flags["AT+BINESC="] or self.command_flags["AT+BINESC"]:
                            if self.command_flags["AT+BINESC="] and not self.enable_uart_echo:
                                current_line = self.new_escape_seq + current_line
                            self.esctime1, self.local_bin_esc, self.esctime2 = self.parse_bin_esc_resp(current_line)
                            self.command_flags["AT+BINESC="] = False
                            self.command_flags["AT+BINESC"] = False
                            # update values in BINESC entry widgets with the new ones
                            self.update_binesc_entry_widgets()

                        # Reset current line
                        current_line = ""
                        # # Calculate time elapsed
                        # start_time = time.time()

                    # in case of AT+GAPDISCONNECT termination string is +DISCONNECTED\r\n
                    elif current_line.startswith("AT") and current_line.endswith("+DISCONNECTED\r\n"):
                        self.append_to_console_text_widget(current_line, "reply_string")

                        # execution of batch file, put command reply to the queue
                        if self.in_parse_batch_file:
                            thread_message.operation = Operations.DATA
                            thread_message.message = current_line
                            self.receive_queue.put(thread_message)

                        # Reset current line
                        current_line = ""
                        # # Calculate time elapsed
                        # start_time = time.time()

                    # in binary mode append everything that UART receives to console widget
                    elif self.in_binary_mode:
                        # identify if binary data are sent
                        try:
                            current_line.decode()
                        except UnicodeDecodeError:
                            self.binary_data = True

                        self.append_to_console_text_widget(current_line, "binary_mode")
                        if self.local_bin_esc in current_line:
                            self.is_binreqexitack_pending = True
                            self.in_binary_mode = False
                            self.command_flags["AT"] = True
                            # send AT command to prevent remote escape sequence printed repeatedly
                            self.append_to_console_text_widget("AT")
                            self.send_command("AT")

                        # Reset current line
                        current_line = ""
                        # # Calculate time elapsed
                        # start_time = time.time()

                    # #if for any reason remote_bin_esc is continuously received from UART just append it to console
                    elif self.local_bin_esc in current_line:
                        self.append_to_console_text_widget(current_line, "binary_mode")

                        # Reset current line
                        current_line = ""
                        # # Calculate time elapsed
                        # start_time = time.time()

                # # something has gone wrong and current_line is not empty for a while, just reset it
                # elapsed_time = time.time() - start_time
                # if elapsed_time > 180 and current_line:
                #     self.append_to_console_text_widget(current_line)
                #     # Reset current line
                #     current_line = ""
                #     # Calculate time elapsed
                #     start_time = time.time()

                # add a 10ms delay between uart write/read operations
                time.sleep(0.01)
            except:
                # update title message
                self.communication_queue.put(self.update_window_title)
                # update binary mode indication
                self.communication_queue.put(lambda: self.update_indication(COMMAND_MODE_COLOR))
                self.button_binresume["state"] = tk.DISABLED
                self.button_binreqexit["state"] = tk.DISABLED

                # stop batch file execution
                if self.stop_batch_event is not None:
                    if not self.stop_batch_event.is_set():
                        self.stop_batch_file()

                self.in_binary_mode = False
                self.stop_event.set()
                self.codeless_peer.stop()
                self.connection_status = CodelessStatus.CODELESS_ERROR
                self.get_active_ports = True

    def save_bin_log(self):
        # check connection status before sending anything to device
        if self.connection_status == CodelessStatus.CODELESS_OK:
            if self.button_save_log.config()["relief"][4] != tk.SUNKEN:
                self.button_save_log.config(relief=tk.SUNKEN)
                self.bin_log_enabled = True
                timestamp = datetime.datetime.now()
                self.bin_timestamp = timestamp.strftime("%d%m%Y_%H%M%S_")
            else:
                self.bin_log_enabled = False
                self.button_save_log.config(relief=tk.RAISED)

    def parse_bin_esc_resp(self, reply_string):
        # AT+BINESC: reply_string = 'AT+BINESC\r\r\n1000 2b2b2b 1000\r\n\r\nOK\r\n' or
        # '\r\n1000 2b2b2b 1000\r\n\r\nOK\r\n'
        # AT+BINESC=1000,0x2a2a2a,1000: reply_string = 'AT+BINESC=100,0x2b2b2b,1000\r\r\n\r\nOK\r\n'
        if self.command_flags["AT+BINESC"]:
            values = reply_string.split()
            esctime1 = values[len(values) - 4]
            escchar = values[len(values) - 3]
            esctime2 = values[len(values) - 2]
        else:
            if "AT+BINESC" in reply_string:
                pattern = "=(.*?)\\r"
            else:
                pattern = "^(.*?)\\r"
            reply_string = re.search(pattern, reply_string).group(1)
            values = reply_string.split(",")

            esctime1 = values[0]
            escchar = values[1][2:]
            esctime2 = values[2]

        try:
            escchar = codecs.decode(escchar, "hex_codec")
        except:
            # The device seems to return an one digit reply as escape character (eg.escchar is 0)
            # and the folloeing error is raised
            # output = binascii.a2b_hex(input)
            # TypeError: Odd-length string
            pass

        return [esctime1, escchar, esctime2]

    def get_bin_esc_sequence(self):
        self.command_flags["AT+BINESC"] = True
        self.append_to_console_text_widget("AT+BINESC")
        self.send_command("AT+BINESC")

    def get_uart_echo_state(self):
        self.command_flags["ATE"] = True
        self.append_to_console_text_widget("ATE")
        self.send_command("ATE")

    def update_binesc_entry_widgets(self, reset=False):
        esctime1 = ""
        escchar = ""
        esctime2 = ""
        if not reset:
            esctime1 = self.esctime1
            escchar = self.local_bin_esc
            esctime2 = self.esctime2
        self.entry_esctime1_var.set(esctime1)
        self.entry_esctchar_var.set(escchar)
        self.entry_esctime2_var.set(esctime2)

    def update_indication(self, color):
        if color == COMMAND_MODE_COLOR:
            self.entry_bin_state.config(text="OFF", bg=color)
            self.change_buttons_state(self.binary_mode_buttons, tk.DISABLED)
        elif color == BINARY_MODE_COLOR:
            self.entry_bin_state.config(text="ON", bg=color)
            self.change_buttons_state(self.binary_mode_buttons, tk.ACTIVE)

    def change_buttons_state(self, buttons, state):
        if self.button_binresume["state"] != tk.ACTIVE:
            self.button_binresume["state"] = tk.ACTIVE
        if self.button_binreqexit["state"] != tk.ACTIVE:
            self.button_binreqexit["state"] = tk.ACTIVE
        for button in buttons:
            button["state"] = state


Application()
