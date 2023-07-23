import speech_recognition as sr
import pyttsx3 as tts

class SpeechElements :
    def __init__(self) :
        # Initialize listener, speaker objects for the ai to listen to our commands and respond to them
        self.listener = sr.Recognizer()
        self.engine = tts.init()
        # Set the pa's voice.
        self.engine.setProperty("voice", self.engine.getProperty("voices")[1].id)
    
    def talk(self, command) :
        """ say whatever is passed in as argument to this function
        """
        print(f"PA: {command}")
        self.engine.say(command)
        self.engine.runAndWait()

    def listen(self) :
        """ Listen for commands from user
        """
        print("here in listen in speech")
        with sr.Microphone() as source :
            print("listening...")
            voice = self.listener.listen(source)
        try :
            command = self.listener.recognize_google(voice).lower().strip()
        except :
            command = None

        return command


speech = SpeechElements()