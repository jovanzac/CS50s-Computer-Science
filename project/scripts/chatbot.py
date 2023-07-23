import random
import json
import pickle
import numpy as np

import nltk
from nltk.stem import WordNetLemmatizer

from tensorflow.keras.models import load_model

from scripts.similarity import most_similar_text


class ChatBot :
    def __init__(self) :
        self.lemmatizer = WordNetLemmatizer()
        self.intents = json.loads(open("data//intents.json").read())

        self.words = pickle.load(open("data//words.pkl", "rb"))
        self.classes = pickle.load(open("data//classes.pkl", "rb"))
        self.model = load_model("data//chatbot_model.h5")

    def cleanup_sentence(self, sentence) :
        sentence_words = nltk.word_tokenize(sentence)
        sentence_words = [self.lemmatizer.lemmatize(word) for word in sentence_words]
        return sentence_words


    def bag_of_words(self, sentence) :
        sentence_words = self.cleanup_sentence(sentence)
        bag = [0] * len(self.words)
        for word in sentence_words :
            for i, w in enumerate(self.words) :
                if word == w :
                    bag[i] = 1
        
        return np.array(bag)


    def predict_class(self, sentence) :
        bow = self.bag_of_words(sentence)
        res = self.model.predict(np.array([bow]))[0]
        ERROR_THRESHOLD = 0.25
        results = [[i, r] for i, r in enumerate(res) if r > ERROR_THRESHOLD]

        results.sort(key=lambda x: x[1], reverse=True)
        return_list = []
        for r in results :
            return_list.append({"intent": self.classes[r[0]], "probability": str(r[1])})
        
        return return_list


    def get_response(self, classes_probs, mssg) :
        """Returns a response and the pattern this response is based on.
           The pattern returned will be the one that is most similar to the user's command
        """
        tag = classes_probs[0]["intent"]
        for i, intent in enumerate(self.intents["intents"]) :
            if intent["tag"] == tag :
                result = most_similar_text(i, mssg)
                res = random.choice(result[2])
                break
        
        return res, result[1]


    def run_terminal(self) :
        """This function is not relavent to the persona assistant application
           It is simply a support command to run the chatbot in terminal
        """
        while True :
            message = input("->> ")
            intent = self.predict_class(message)
            res = self.get_response(intent, message)

            print(res[0])
            print(res[1])

            ch = input("Do you want to keep going(yes/no)? ")
            if ch.lower() not in ["yes", "y"] :
                break
        

chatbot = ChatBot()

if __name__ == "__main__" :
    chatbot.run_terminal()