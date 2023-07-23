from scripts.speech import speech
from scripts.commands import commands
from scripts.chatbot import chatbot

class CommandHandle :
    def __init__(self) :
        pass

    def input_handle(self, command) :
        """This is the function that 'handles' the users input.
           It takes the input from user and handles it appropriately
           Finally returns the response for user's command    
        """
        matches = None

        intent = chatbot.predict_class(command)
        response, pattern = chatbot.get_response(intent, command)
        print(f"The most similar pattern in the set was: {pattern}")
        print(f"response was {response}")
        print(f"response[:8] is : {response[:8]}")

        if response[:8] == "command-" :
            response = commands.command_check(command, response)
            if isinstance(response, list) :
                matches = " or ".join([file.capitalize() for file in response])
        
        return response, matches

    def listen(self) :
        """This function is called when the listen button in the 
           Gui is clicked.
        """
        print("here in listen")
        command = speech.listen()
        
        return self.respond(command)

    def respond(self, command) :
        """ Handles the pa's response
        """
        if not command :
            command = "Not Recognized."
            response = "Sorry, I did not understand."
            return command, response

        response, matches = self.input_handle(command)
        if matches :
            response = f"Did you mean {matches} ?"
            return command, response

        return command, response


handle = CommandHandle()