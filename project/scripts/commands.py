import datetime
import os


class Commands :
    def command_check(self, user_input, command) :
        """ Check for any commands from the user
        """
        if command == "command-time" :
            time = datetime.datetime.now().strftime("%I:%M %p")
            return_val = f"The time right now is {time}"

        elif command == "command-date" :
            date = datetime.datetime.now().strftime("%A, %B %d, %Y")
            return_val = f"The date today is {date}"

        elif command == "command-application" :
            result = self.find_exe(user_input)
            if result :
                return_val = f"Opening {result}"
            
            else :
                return_val = f"Sorry, I could not find the application you were looking for"
        
        else :
            return_val = "Sorry, I don't recognise the command"

        return return_val


    def find_exe(self, command) :
        """Finds all exe files within the program files directory on the system
        """
        command = command.split(" ")
        
        all_files = os.popen("cd C://Program Files & where *.exe").read().split("\n")
        all_files.pop(-1)
        all_files += os.popen("cd C://Program Files (x86) & where *.exe").read().split("\n")
        all_files.pop(-1)
        
        possible_apps = list()
        for word in command :
            for file in all_files :
                file = file.replace('\\', "//").split("//")
                exe = file[-1][:-4]
                if word == exe.lower() :
                    try :
                        print(word)
                        os.popen(word)
                        return exe
                    except Exception as ex :
                        print("In Exception")
                        print(ex)
                        return False
                
                elif word in exe :
                    possible_apps.append(exe)
        
        print(f"Here in the end and possible_apps is: {possible_apps}")
        return possible_apps if possible_apps != [] else None

commands = Commands()