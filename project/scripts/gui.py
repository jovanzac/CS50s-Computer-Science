import tkinter as tk
import tkinter.ttk as ttk
from ttkthemes import ThemedTk

from scripts.command_handle import handle
from scripts.speech import speech
from scripts.styles import Styles


class Root(ThemedTk) :
    def __init__(self, **kwargs) :
        ThemedTk.__init__(self, theme="Breeze", **kwargs)
        self.title("Personal Assistant")
        self.geometry("650x610")
        self.resizable(0, 0)
        self.columnconfigure(0,weight=1)
        self.input_type = "speech"
        self.command = tk.StringVar(value="")
        self.response = tk.StringVar(value="")
        self.speech_status = tk.StringVar(value="Ready!")

    def clear(self) :
        for widget in self.winfo_children() :
            widget.destroy()

    def main_page(self) :
        # The header label
        label1 = ttk.Label(self, text="Personal Assistant", style="head.TLabel")
        label1.grid(row=0, pady=20)

        # Frame to enclose the user and pa interchange
        frame = tk.Frame(self, width=550, height=380)
        frame.grid(row=1)
        # User tag and label for command
        user_label = ttk.Label(frame, text="User :", style="name_label.TLabel")
        user_label.place(relx=0, rely=0.2)
        user_command = ttk.Label(frame, textvariable=self.command, style="conversation.TLabel")
        # self.command.set("")
        user_command.place(relx=0.2, rely=0.205)
        # personal assistant tag and label for response
        pa_label = ttk.Label(frame, text="PA :", style="name_label.TLabel")
        pa_label.place(relx=0, rely=0.5)
        pa_response = ttk.Label(frame, textvariable=self.response, style="conversation.TLabel")
        # self.response.set("")
        pa_response.place(relx=0.2, rely=0.505)

        if self.input_type == "speech" :
            self.speech_status.set("Ready!")
            s_label = ttk.Label(self, textvariable=self.speech_status, style="listen.TLabel")
            s_label.grid(row=2)
            listen_btn = ttk.Button(self, text="Listen", style="listen.TButton", command=lambda: self.listen_btn())
            listen_btn.grid(row=3, ipadx=20, ipady=5)
        
        elif self.input_type == "entrybox" :
            text_frame = tk.Frame(self)
            text_frame.grid(row=2, sticky="N")
            textbox = ttk.Entry(text_frame, text="Enter your command", style="command-entry.TEntry", font=("@hp simplified jpan", 13))
            textbox.grid(row=0, column=0, pady=10, ipadx=50, ipady=4)
            text_btn = ttk.Button(text_frame, text="Submit", style="text_btn.TButton", command=lambda: self.entry_btn(textbox))
            text_btn.grid(row=0, column=1, ipadx=10, ipady=1, padx=10)

        divider = ttk.Separator(self, orient="horizontal")
        divider.grid(row=4, ipadx=200, pady=10)

        selection_frame = tk.Frame(self)
        selection_frame.grid(row=5)
        speech_select = ttk.Button(selection_frame, text="Speech", style="selection.TButton", command=lambda: self.input_change())
        speech_select.grid(row=0, column=0, padx=10)
        text_select = ttk.Button(selection_frame, text="Text Box", style="selection.TButton", command=lambda: self.input_change())
        text_select.grid(row=0, column=1, padx=10)
        speech_select.configure(state=tk.DISABLED) if self.input_type == "speech" else text_select.configure(state=tk.DISABLED)

    def listen_btn(self) :
        self.speech_status.set("Listening...")
        self.update()
        command, response = handle.listen()
        self.command.set(command)
        self.response.set(response)
        speech.talk(response)
        self.speech_status.set("Ready!")
        self.update()

    def entry_btn(self, entry) :
        command = entry.get()
        entry.delete(0, tk.END)
        self.update()
        command, response = handle.respond(command)
        self.command.set(command)
        self.response.set(response)
        speech.talk(response)

    def input_change(self) :
        self.input_type = "entrybox" if self.input_type == "speech" else "speech"
        self.clear()
        self.main_page()


root = Root()
styles = Styles()

if __name__ == "__main__" :
    root.main_page()
    root.mainloop()