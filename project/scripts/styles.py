import tkinter as tk
import tkinter.ttk as ttk


# The styles
class Styles(ttk.Style) :
    def __init__(self,**kwargs) :
        """Defining all the different widget styles."""
        ttk.Style.__init__(self,**kwargs)
        # the styles
        self.configure("head.TLabel", font=("lucida console",18), foreground="light sea green", anchor=tk.CENTER)

        self.configure("name_label.TLabel", font=("@hp simplified jpan", 18), foreground="#7AC5CD")

        self.configure("conversation.TLabel", font=("@hp simplified jpan", 16), foreground="#7AC5CD")

        self.configure("listen.TButton", font=("@malgun gothic",15), foreground="light sea green", cursor="@hand2", anchor=tk.CENTER)

        self.configure("listen.TLabel", font=("@malgun gothic",15), foreground="light sea green")

        self.configure("command-entry.TEntry", relief=tk.FLAT, foreground="light sea green")

        self.configure("text_btn.TButton", foreground="light sea green", relief=tk.FLAT, font=("@malgun gothic",15))

        self.configure("selection.TButton", foreground="light sea green", relief=tk.FLAT, font=("@malgun gothic",12))